#include "pch.h"
#include "Session.h"
#include "Service.h"
#include "SocketUtility.h"

Session::Session()
{
	_socket = SocketUtility::CreateSocket();
}

Session::~Session()
{
	SocketUtility::Close(_socket);
}

void Session::SetService(shared_ptr<Service> service)
{
	_service = service;

	u_long on = 1;
	if(::ioctlsocket(_socket, FIONBIO, &on) == INVALID_SOCKET)
		return;

	_netAddress = service->GetNetAddress();

	//SocketUtility::Bind(_socket, _service.lock()->GetNetAddress());
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(_socket);
}

void Session::DisPatch(IocpEvent* iocpEvent, int32 numOfBytes)
{
	EventType eventType = iocpEvent->GetType();
	switch (eventType)
	{
	case EventType::CONNECT:
	{
		ProcessConnect();
		break;
	}

	case EventType::RECV:
	{
		ProcessRecv(numOfBytes);
		break;
	}

	case EventType::SEND:
	{
		ProcessSend(static_cast<SendEvent*>(iocpEvent),numOfBytes);
		break;
	}

	default:
		break;
	}
}

bool Session::Connect()
{
	while (true)
	{
		if (::connect(GetSocket(), (SOCKADDR*)&_netAddress, sizeof(_netAddress)) == SOCKET_ERROR)
		{
			// ���� ����߾�� �ߴµ�... �ʰ� ����ŷ���� �϶��?
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			// �̹� ����� ���¶�� break
			if (::WSAGetLastError() == WSAEISCONN)
				break;
			// Error
			return false;
		}
	}

	ProcessConnect();

	return RegisterConnect();
}

void Session::Send(BYTE* buffer, int32 len)
{
	// TODO : Scatter Gathering

	SendEvent* sendEvent = xnew<SendEvent>();
	sendEvent->SetOwner(GetSessionShared());

	::memcpy(_sendBuffer, buffer, len);

	WRITE_LOCK;
	RegisterSend(sendEvent);
}

void Session::DisConnect(const WCHAR* cause)
{
	if (_connected.exchange(false) == false) // _connected�� ���ʿ� false
	{
		return;
	}

	wcout << "DisConnected : " << cause << endl;

	// TODO : OnDisConnected �������̵�
	SocketUtility::Close(_socket);
	GetService()->ReleaseSession(GetSessionShared()); // refCount --
}

bool Session::RegisterConnect()
{
	// TODO : IOCP ��� Connect �񵿱�, ��Ƽ������ ������� Connect
	return false;
}

void Session::RegisterRecv()
{
	if(IsConnected() == false)
		return;

	_recvEvent.Init();
	_recvEvent.SetOwner(shared_from_this()); // event�� ������ IocpObject... Session�� refCount + 1

	WSABUF wsaBuf;
	wsaBuf.buf = reinterpret_cast<char*>(_recvBuffer);
	wsaBuf.len = len32(_recvBuffer);

	DWORD numOfBytes = 0;
	DWORD flags = 0;

	if (SOCKET_ERROR == ::WSARecv(_socket, &wsaBuf, 1, OUT & numOfBytes, &flags, &_recvEvent, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			_recvEvent.SetOwner(nullptr); // refCount - 1
		}
	}
}

void Session::RegisterSend(SendEvent* event)
{
	if(IsConnected() == false)
		return;

	WSABUF wsaBuf;
	wsaBuf.buf = _sendBuffer;
	wsaBuf.len = 1000; // TODO

	DWORD numOfBytes = 0;
	if (SOCKET_ERROR == ::WSASend(_socket, &wsaBuf, 1, OUT & numOfBytes, 0, event, nullptr))
	{
		int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			event->SetOwner(nullptr); // session RefCount--
			xdelete(event);
		}
	}
}

void Session::ProcessConnect()
{
	_connected.store(true);

	GetService()->AddSession(GetSessionShared());

	OnConnected();

	// ���� �����ϱ� �����ϰڴ�.
	RegisterRecv();
}

// ������ �� �ϳ���
void Session::ProcessRecv(int32 numOfBytes)
{
	_recvEvent.SetOwner(nullptr); // Session�� refCount - 1

	if (numOfBytes == 0)
	{
		DisConnect(L"Recv : 0");
		return;
	}

	OnRecv(reinterpret_cast<BYTE*>(_recvBuffer), numOfBytes);

	// �� ���� ���
	RegisterRecv();
}

void Session::ProcessSend(SendEvent* event, int32 numOfBytes)
{
	event->SetOwner(nullptr); // session Refcount --
	xdelete(event);

	if (numOfBytes == 0)
	{
		DisConnect(L"Send 0");
		return;
	}

	OnSend(numOfBytes);
}

void Session::HandleError(int32 errorCode)
{
	switch (errorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
	{
		DisConnect(L"Handler Error");
		break;
	}
	default:
		cout <<"Handle Error : " << errorCode << endl;

		break;
	}
}
