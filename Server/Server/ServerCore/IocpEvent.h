#pragma once

class Session;
class IocpObject;

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

	shared_ptr<IocpObject> GetOwner() { return _owner; }
	void				   SetOwner(shared_ptr<IocpObject> owner) { _owner = owner; }

protected:
	EventType				_eventType; // RECV, SEND, ACCEPT
	shared_ptr<IocpObject>	_owner = nullptr;
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

	void SetSession(shared_ptr<Session> session) { _session = session; }
	shared_ptr<Session> GetSession() { return _session; }

private:
	shared_ptr<Session> _session = nullptr;
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
