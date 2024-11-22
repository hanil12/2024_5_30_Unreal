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
		BUFF_SIZE = 0x10000, // 64KB => 6��5õ����Ʈ
	};

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
	void Send(shared_ptr<SendBuffer> buffer);
	void DisConnect(const WCHAR* cause);

	// ���ο����� �� �Լ���
private:
	// CP(Completion Port)�� ���
	bool RegisterConnect(); // �մ��� ��Ź�� �ɱ�.
	bool RegisterDisConnect();
	void RegisterRecv(); // �մ��� �ִ� �޽���-> Ŀ���� RecvBuffer -> ���������� Session::recvBuffer�� ����
	void RegisterSend(); // ���� �մ����� �� �޽���

	// CP�� ��ϵǾ��ִ� Event�� DisPatch(������)
	void ProcessConnect();
	void ProcessDisConnect();
	void ProcessRecv(int32 numOfBytes);
	void ProcessSend(int32 numOfBytes);

	void HandleError(int32 errorCode);

protected:
	// ServerSession , ClientSession���� �ʿ��� ��� �������̵�
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
	// ���� ����
	RecvBuffer _recvBuffer;

	// �۽� ����
	Queue<shared_ptr<SendBuffer>> _sendQueue;
	Atomic<bool> _sendRegistered = false;

	SendEvent				 _sendEvent;
	RecvEvent				 _recvEvent;
	ConnectEvent			 _connectEvent;
	DisConnectEvent			 _disConnectEvent;
};


// PacketSession
// Packet�� �� �ʿ��Ѱ�...
// SendBuffer�� �����͸� ������ �� TCP ȯ�濡���� ������ �� ������ �� ���޵ȴٴ� ������ ����.

// Packet���� Ȯ���ؾ��� ��.
// 1. � �뵵�� ����������
// 2. �� �������� �� ũ��� ��� �Ǵ���
struct PacketHeader
{
	uint16 size;
	uint16 id; // �������� ID : (ex 1 : �α���, 2 : �̵�)
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