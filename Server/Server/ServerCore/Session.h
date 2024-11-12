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

	// ���� ����
	shared_ptr<Service> GetService() { return _service.lock(); }
	void SetService(shared_ptr<Service> service) { _service = service; }
	void SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress GetAddress() { return _netAddress; }
	SOCKET	GetSocket() { return _socket; }
	virtual HANDLE GetHandle() override;
	virtual void DisPatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) override;
	bool IsConnected() { return _connected; }
	shared_ptr<Session> GetSessionShared() { return static_pointer_cast<Session>(shared_from_this()); }

	// ���� ����
	// - �ܺ�(Client, Server)���� �� �Լ�
	bool Connect();
	void Send(BYTE* buffer, int32 len);
	void DisConnect(const WCHAR* cause);

	bool RegisterConnect(); // �մ��� ��Ź�� �ɱ�.
	void RegisterRecv(); // �մ��� �ִ� �޽���-> Ŀ���� RecvBuffer -> ���������� Session::recvBuffer�� ����
	void RegisterSend(SendEvent* event); // ���� �մ����� �� �޽���

	void ProcessConnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(SendEvent* event, int32 numOfBytes);

	void HandleError(int32 errorCode);

	char _recvBuffer[1000] = {};
	char _sendBuffer[1000] = {};

protected:
	// ServerSession , ClientSession���� �ʿ��� ��� �����ε�
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
	// ���� ����

	// �۽� ����

	RecvEvent _recvEvent;
};

