#include "pch.h"

// Socket 만들기
// - ipv6
// - port
// - protocol

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSAData wsaData;
	if(::WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout <<"Socket ErroCode: " << errCode << endl;
		return 0;
	}

	u_long on = 1;
	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET) // 논블로킹 소켓 만드는 함수
		return 0;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr , 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET,"127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777);

	this_thread::sleep_for(2s);

	// Connect
	while (true)
	{
		auto connectValue = ::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
		if (connectValue == SOCKET_ERROR)
		{
			// 블록상태였어야 했음(연결이 아직 되지 않았음)
			if(::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;

			// 이미 연결되어있음
			if(::WSAGetLastError() == WSAEISCONN)
				break;

			// Error

			break;
		}
	}

	cout << "Connected to Server" << endl;
	
	// - Session -
	char sendBuffer[100] = "Hello Server!";
	// Overlapped
	WSAEVENT wsaEvent = WSACreateEvent();
	WSAOVERLAPPED overlapped = {};
	overlapped.hEvent = wsaEvent;

	// Send
	while (true)
	{
		WSABUF wsaBuf;
		wsaBuf.buf = sendBuffer;
		wsaBuf.len = sizeof(sendBuffer);

		DWORD sendLen = 0;
		DWORD flags = 0;

		if (::WSASend(clientSocket, &wsaBuf, 1, &sendLen, flags, &overlapped, nullptr) == SOCKET_ERROR)
		{
			// WSARecv가 실패
			if (::WSAGetLastError() == WSA_IO_PENDING)
			{
				// Pending : 보류하고 나중에 확인
				::WSAWaitForMultipleEvents(1, &wsaEvent, TRUE, WSA_INFINITE, FALSE);
				::WSAGetOverlappedResult(clientSocket, &overlapped, &sendLen, FALSE, &flags);
			}
			else
			{
				// TODO : 문제가 있는 상황
				break;
			}
		}

		cout << "Send Data! Len = " << sizeof(sendBuffer) << endl;

		// Recv

		this_thread::sleep_for(1s);
	}


	::WSACloseEvent(wsaEvent);
	::closesocket(clientSocket);
	::WSACleanup();
}
