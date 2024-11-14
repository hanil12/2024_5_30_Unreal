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
	void Send(BYTE* buffer, int32 len);
	void DisConnect(const WCHAR* cause);

	// 내부에서만 쓸 함수들
private:
	// CP(Completion Port)에 등록
	bool RegisterConnect(); // 손님이 식탁에 앉기.
	bool RegisterDisConnect();
	void RegisterRecv(); // 손님이 주는 메시지-> 커널의 RecvBuffer -> 유저영역에 Session::recvBuffer에 복사
	void RegisterSend(SendEvent* event); // 내가 손님한테 줄 메시지

	// CP에 등록되어있던 Event들 DisPatch(보낸다)
	void ProcessConnect();
	void ProcessDisConnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(SendEvent* event, int32 numOfBytes);

	void HandleError(int32 errorCode);

protected:
	// ServerSession , ClientSession에서 필요할 경우 오버라이딩
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual int32 OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void OnSend(int32 len) {}
	virtual void DisConnected() {}

	// TODO
	char _sendBuffer[1000] = {};

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


	RecvEvent _recvEvent;
	ConnectEvent _connectEvent;
	DisConnectEvent _disConnectEvent;
};

