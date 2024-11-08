#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#include "Listener.h"

const int32 BuffSize = 1000;

struct Session
{
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[BuffSize] = {};
	char sendBuffer[100] = "Hello Im Server!!!";
	int32 recvBytes = 0;
	int32 sendBytes = 0;
};

enum IO_TYPE
{
	READ,
	WRITE,
	ACCEPT,
	CONNET
};

struct OverlappedEx
{
	WSAOVERLAPPED overlapped = {};
	int32 type = 0;
};

void WorkerThreadMain(HANDLE iocpHandle)
{
	while (true)
	{	
		DWORD bytesTranferred = 0;
		Session* session = nullptr;
		OverlappedEx* overlappedEx = nullptr;

		BOOL ret = ::GetQueuedCompletionStatus(iocpHandle, &bytesTranferred, /*Key*/(ULONG_PTR*)&session,
		(LPOVERLAPPED*)&overlappedEx, INFINITE);

		if (ret == FALSE || bytesTranferred == 0)
		{
			continue;
		}

		switch (overlappedEx->type)
		{
		case IO_TYPE::READ :
		{
			cout << session->recvBuffer << endl;

			WSABUF wsaBuf;
			wsaBuf.buf = session->recvBuffer;
			wsaBuf.len = BuffSize;

			DWORD recvLen = 0;
			DWORD flags = 0;
			::WSARecv(session->socket, &wsaBuf, 1, &recvLen, &flags, &overlappedEx->overlapped, NULL);

			break;
		}


		default:
			break;
		}
	}
}

int main()
{
	// IOCP
	// 1. CP(Completion Port)에 Socket을 등록 => Completion Port에서 Socket을 관찰
	// 2. Dispatch : CallBack를 호출해서 해당 작업을 진행

	CoreGlobal::Create();

	Listener listener;
	NetAddress netAddress(L"127.0.0.1", 7777);
	listener.StartAccept(netAddress);

	for (int i = 0; i < 5; i++)
	{
		TM_M->Launch([=]()
			{
				while (true)
				{
					CoreGlobal::Instance()->GetIocpCore()->Dispatch();
				}
			});
	}


	TM_M->Join();

	CoreGlobal::Delete();

	return 0;
}