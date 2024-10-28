#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// 블로킹 소켓
	// 블로킹 함수들
	// accept -> 접속한 클라가 있을 때
	// connect -> 서버에 접속이 성공했을 때
	// send -> sendBuff에 요청한 데이터를 복사했을 때
	// recv -> recvBuff에 도착한 데이터가 있고, 이를 성공적으로 복사했을 때

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if(listenSocket == INVALID_SOCKET)
		return 0;

	u_long on = 1;
	if(::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET) // 논블로킹 소켓 만드는 함수
		return 0;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	// listenSocket Setting
	if(::bind(listenSocket, (sockaddr*)(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	if(::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
		return 0;

	cout << "Accept" << endl;

	SOCKADDR_IN clientAddr;
	int32 addrLen = sizeof(clientAddr);

	while (true)
	{
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			// 넌블로킹 함수의 예외처리
			if(::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;

			// Error를 잡는 코드
			// => 클라이언트가 뭔가 이상하다? ... 예외처리
			break;
		}

		cout << "Client Conntected" << endl;

		// Recv
		while (true)
		{
			char recvBuffer[100]; // 복사할 곳
			int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);

			if (recvLen == SOCKET_ERROR)
			{
				if(::WSAGetLastError() == WSAEWOULDBLOCK)
					continue;

				// Error
				break;
			}
			else if (recvLen == 0)
			{
				// 연결 끊김
				break;
			}

			// 송신 성공
			cout << "Recv Data Len = " << recvLen << endl;

			// Send
			while (true)
			{
				char sendBuff[100] = "Im Server!!";
				if (::send(clientSocket, sendBuff, sizeof(sendBuff), 0) == SOCKET_ERROR)
				{
					if(::WSAGetLastError() == WSAEWOULDBLOCK)
						continue;

					break;
				}

				cout << "Send Data Succeed Len = " << sizeof(sendBuff) << endl;
				break;
			}
		}
	}

	
	::WSACleanup();

	return 0;
}