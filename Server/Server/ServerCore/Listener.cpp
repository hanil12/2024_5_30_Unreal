#include "pch.h"
#include "Listener.h"
#include "IocpEvent.h"
#include "Session.h"

Listener::~Listener()
{
	SocketUtility::Close(_socket);

	for (AcceptEvent* acceptEvent : _acceptEvents)
	{
		// TODO

		xdelete(acceptEvent);
	}

	_service = nullptr;
}

bool Listener::StartAccept(shared_ptr<ServerService> service)
{
	_socket = SocketUtility::CreateSocket();
	if (_socket == INVALID_SOCKET) return false;

	// Listener를 Completion Port에 등록
	shared_ptr<IocpObject> temp = shared_from_this();
	if (service->GetIocpCore()->Register(shared_from_this()) == false)
		return false;

	if (SocketUtility::SetReuseAddress(_socket, true) == false)
		return false;

	if (SocketUtility::SetLinger(_socket, 0, 0) == false)
		return false;

	if (SocketUtility::Bind(_socket, service->GetNetAddress()) == false)
		return false;

	if (SocketUtility::Listen(_socket) == false)
		return false;

	_service = service;

	const int32 acceptCount = service->GetMaxSessionCount();
	for (int32 i = 0; i < acceptCount; i++)
	{
		AcceptEvent* acceptEvent = xnew<AcceptEvent>();
		acceptEvent->SetOwner(shared_from_this());
		_acceptEvents.push_back(acceptEvent);
		RegisterAccept(acceptEvent);
	}

	return true;
}

void Listener::CloseSocket()
{
	SocketUtility::Close(_socket);
}

HANDLE Listener::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Listener::DisPatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	ASSERT_CRASH(iocpEvent->GetType() == EventType::ACCEPT);
	AcceptEvent* acceptEvent = static_cast<AcceptEvent*>(iocpEvent);
	ProcessAccept(acceptEvent);
}

void Listener::RegisterAccept(AcceptEvent* acceptEvent)
{
	shared_ptr<Session> session = _service->CreateSession();

	acceptEvent->Init();
	acceptEvent->SetSession(session);

	DWORD bytesRecived = 0;

	if (false == SocketUtility::AcceptEx(_socket, session->GetSocket(), session->_recvBuffer.WritePos(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &bytesRecived, static_cast<LPOVERLAPPED>(acceptEvent)))
	{
		const int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			// TODO : 이상함
			
			RegisterAccept(acceptEvent); // 
		}
	}
}

void Listener::ProcessAccept(AcceptEvent* acceptEvent)
{
	shared_ptr<Session> session = acceptEvent->GetSession();

	if(false == SocketUtility::SetUpdateAcceptSocket(session->GetSocket(), _socket))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	// session
	// - 식탁

	SOCKADDR_IN sockAddress;
	int32 sizeofSockAddr = sizeof(sockAddress);
	if (SOCKET_ERROR == ::getpeername(session->GetSocket(), reinterpret_cast<SOCKADDR*>(&sockAddress), &sizeofSockAddr))
	{
		RegisterAccept(acceptEvent);
		return;
	}

	OnAccept(session, acceptEvent);
}

void Listener::OnAccept(shared_ptr<Session> session, IocpEvent* iocpEvent)
{
	session->SetNetAddress(NetAddress(session->GetAddress()));
	session->ProcessConnect();

	RegisterAccept(reinterpret_cast<AcceptEvent*>(iocpEvent));
}
