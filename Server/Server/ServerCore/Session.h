#pragma once

#include "IocpCore.h"
#include "IocpEvent.h"

class Service;

class Session : public IocpObject
{
	friend class Listener;

public:
	Session();
	virtual ~Session();

public:

	// ���� ����
	shared_ptr<Service> GetService() { return _service.lock(); }
	void SetService(shared_ptr<Service> service);

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

	// ���ο����� �� �Լ���
private:
	bool RegisterConnect(); // �մ��� ��Ź�� �ɱ�.
	bool RegisterDisConnect();
	void RegisterRecv(); // �մ��� �ִ� �޽���-> Ŀ���� RecvBuffer -> ���������� Session::recvBuffer�� ����
	void RegisterSend(SendEvent* event); // ���� �մ����� �� �޽���

	void ProcessConnect();
	void ProcessDisConnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(SendEvent* event, int32 numOfBytes);

	void HandleError(int32 errorCode);

protected:
	// ServerSession , ClientSession���� �ʿ��� ��� �������̵�
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual int32 OnRecv(BYTE* buffer, int32 len) { return len; }
	virtual void OnSend(int32 len) {}
	virtual void DisConnected() {}


	char _recvBuffer[1000] = {};
	char _sendBuffer[1000] = {};
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
	ConnectEvent _connectEvent;
	DisConnectEvent _disConnectEvent;
};

