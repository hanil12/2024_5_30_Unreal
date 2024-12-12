#pragma once

#include "NetAddress.h"
#include "IocpCore.h"
#include "SendBuffer.h"
#include "Listener.h"
#include "Session.h"
#include <functional>

using SessionFactory = function<shared_ptr<Session>(void)>;

enum class ServiceType : uint8
{
	SERVER,
	CLIENT
};

class Service : public enable_shared_from_this<Service>
{
public:
	Service(ServiceType type, NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~Service();

	// 技记 积己 规过
	virtual bool			Start() abstract;
	bool					CanStart() { return _sessionFactory != nullptr; }
	virtual void			CloseService();
	void					SetSessionFactory(SessionFactory func) { _sessionFactory = func; }
	

	// Session 包府
	shared_ptr<Session>		CreateSession();
	void					AddSession(shared_ptr<Session> session);
	void					ReleaseSession(shared_ptr<Session> session);

	int32					GetCurSessionCount() { return _sessionCount; }
	int32					GetMaxSessionCount() { return _maxSessionCount; }

	ServiceType				GetServiceType() { return _type; }
	NetAddress				GetNetAddress() { return _netAddress; }
	shared_ptr<IocpCore>&	GetIocpCore() { return _iocpCore; }

	// Send
	void BroadCast(shared_ptr<class SendBuffer> buffer);

protected:
	USE_LOCK;

	ServiceType _type;
	NetAddress _netAddress = {};
	shared_ptr<IocpCore> _iocpCore;

	Set<shared_ptr<Session>> _sessions;
	int32 _sessionCount = 0;
	int32 _maxSessionCount = 0;
	SessionFactory _sessionFactory; // session阑 父甸 锭 静绰 窃荐
};

class ClientService : public Service
{
public:
	ClientService(NetAddress target, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~ClientService();

	virtual bool Start() override;
};

class ServerService : public Service
{
public:
	ServerService(NetAddress target, shared_ptr<IocpCore> core, SessionFactory factory, int32 maxSessionCount = 1);
	virtual ~ServerService();

	virtual bool Start() override;
	virtual void CloseService() override;

private:
	shared_ptr<class Listener> _listener = nullptr;
};