#pragma once

class Session;

enum class EventType : uint8
{
	CONNECT,
	ACCEPT,
	RECV,
	SEND
};

// OVERLAPPED 정보는 운영체제가 만들어준다.
class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);

	void		 Init();
	EventType	 GetType() { return _eventType; }

protected:
	EventType _eventType; // RECV, SEND, ACCEPT
};

// ------------------------
//		 Connect
// ------------------------
class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() : IocpEvent(EventType::CONNECT) {}
};

// ------------------------
//		 Accept
// ------------------------
class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::ACCEPT) {}

	void SetSession(Session* session) { _session = session; }
	Session* GetSession() { return _session; }

private:
	Session* _session = nullptr;
};

// ------------------------
//		 Recv
// ------------------------
class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(EventType::RECV) {}
};

// ------------------------
//		 Send
// ------------------------
class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::SEND) {}
};
