#include "pch.h"
#include "Session.h"
#include "Service.h"

Session::Session()
{
	_socket = SocketUtility::CreateSocket();
}

Session::~Session()
{
	SocketUtility::Close(_socket);
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
	case EventType::ACCEPT:
	{
		// TODO
		break;
	}

	default:
		break;
	}
}

void Session::DisConnect(const WCHAR* cause)
{
}

void Session::RegisterConnect()
{
	// TODO : 
}

void Session::RegisterRecv()
{
	if(IsConnected() == false)
		return;

	_recvEvent.Init();
	_recvEvent.SetOwner(shared_from_this()); // event의 주인이 IocpObject... Session의 refCount + 1

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

void Session::RegisterSend()
{
	// TODO
}

void Session::ProcessConnect()
{
	_connected.store(true);

	GetService()->AddSession(GetSession());

	OnConnected();

	// 연결 됬으니까 수신하겠다.
	RegisterRecv();
}

void Session::ProcessRecv(int32 numOfBytes)
{
	_recvEvent.SetOwner(nullptr); // Session의 refCount - 1

	if (numOfBytes == 0)
	{
		DisConnect(L"Recv : 0");
		return;
	}

	// TODO...
	cout << "Recv Data Len : " << numOfBytes << endl;

	// 재 수신 등록
	RegisterRecv();
}

void Session::ProcessSend(int32 numOfBytes)
{
	// TODO
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
