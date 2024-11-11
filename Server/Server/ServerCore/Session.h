#pragma once

#include "IocpCore.h"
#include "IocpEvent.h"

class Service;

class Session : public IocpObject
{
public:
	Session();
	virtual ~Session();

public:

	// 정보 관련
	shared_ptr<Service> GetService() { return _service.lock(); }
	void SetService(shared_ptr<Service> service) { _service = service; }
	void SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress GetAddress() { return _netAddress; }
	SOCKET	GetSocket() { return _socket; }
	virtual HANDLE GetHandle() override;
	virtual void DisPatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;
	bool IsConnected() { return _connected; }
	shared_ptr<Session> GetSession() { return static_pointer_cast<Session>(shared_from_this()); }

	// 전송 관련
	void DisConnect(const WCHAR* cause);

	void RegisterConnect(); // 손님이 식탁에 앉기.
	void RegisterRecv(); // 손님이 주는 메시지
	void RegisterSend(); // 내가 손님한테 줄 메시지

	void ProcessConnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(int32 numOfBytes);

	void HandleError(int32 errorCode);

	char _recvBuffer[1000] = {};
	char _sendBuffer[1000] = {};

protected:
	// ServerSession , ClientSession에서 필요할 경우 오버로딩
	virtual void OnConnected() {}
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

	// 송신 관련

	RecvEvent _recvEvent;
};

