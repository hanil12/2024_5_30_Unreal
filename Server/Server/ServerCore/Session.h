#pragma once

#include "IocpCore.h"
#include "IocpEvent.h"
#include "RecvBuffer.h"

class Service;

class Session : public IocpObject
{
	friend class Listener;

	enum
	{
		BUFF_SIZE = 0x10000, // 64KB => 6만5천바이트
	};

public:
	Session();
	virtual ~Session();

public:

	// 정보 관련
	shared_ptr<Service> GetService() { return _service.lock(); }
	void SetService(shared_ptr<Service> service);

	void SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress GetAddress() { return _netAddress; }
	SOCKET	GetSocket() { return _socket; }
	virtual HANDLE GetHandle() override;
	virtual void DisPatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;
	bool IsConnected() { return _connected; }
	shared_ptr<Session> GetSessionShared() { return static_pointer_cast<Session>(shared_from_this()); }

	// 전송 관련
	// - 외부(Client, Server)에서 쓸 함수
	bool Connect();
	void Send(shared_ptr<SendBuffer> buffer);
	void DisConnect(const WCHAR* cause);

	// 내부에서만 쓸 함수들
private:
	// CP(Completion Port)에 등록
	bool RegisterConnect(); // 손님이 식탁에 앉기.
	bool RegisterDisConnect();
	void RegisterRecv(); // 손님이 주는 메시지-> 커널의 RecvBuffer -> 유저영역에 Session::recvBuffer에 복사
	void RegisterSend(); // 내가 손님한테 줄 메시지

	// CP에 등록되어있던 Event들 DisPatch(보낸다)
	void ProcessConnect();
	void ProcessDisConnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(int32 numOfBytes);

	void HandleError(int32 errorCode);

protected:
	// ServerSession , ClientSession에서 필요할 경우 오버라이딩
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual int32 OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void OnSend(int32 len) {}
	virtual void DisConnected() {}

private:
	weak_ptr<Service> _service;
	SOCKET _socket = INVALID_SOCKET;
	NetAddress _netAddress = {};

	Atomic<bool> _connected = false;

private:
	USE_LOCK;
	// 수신 관련
	RecvBuffer _recvBuffer;

	// 송신 관련
	Queue<shared_ptr<SendBuffer>> _sendQueue;
	Atomic<bool> _sendRegistered = false;

	SendEvent				 _sendEvent;
	RecvEvent				 _recvEvent;
	ConnectEvent			 _connectEvent;
	DisConnectEvent			 _disConnectEvent;
};


// PacketSession
// Packet이 왜 필요한가...
// SendBuffer로 데이터를 전달할 때 TCP 환경에서는 데이터 한 묶음이 다 전달된다는 보장이 없다.

// Packet으로 확인해야할 것.
// 1. 어떤 용도의 데이터인지
// 2. 이 데이터의 총 크기는 어떻게 되는지
struct PacketHeader
{
	uint16 size;
	uint16 id; // 프로토콜 ID : (ex 1 : 로그인, 2 : 이동)
};

class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

	shared_ptr<PacketSession> GetPacketSession() { return static_pointer_cast<PacketSession>(shared_from_this()); }

protected:
	virtual int32 OnRecv(BYTE* buffer, int32 len) sealed;
	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) abstract;
};