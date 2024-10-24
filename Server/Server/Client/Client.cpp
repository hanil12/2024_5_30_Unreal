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

	SOCKET clientSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout <<"Socket ErroCode: " << errCode << endl;
		return 0;
	}

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr , 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET,"127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777);

	while (true)
	{
		for (int i = 0; i < 10; i++)
		{
			char sendBuffer[100] = "Hello World!!";
			int32 sendCode = ::sendto(clientSocket, sendBuffer, sizeof(sendBuffer), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
			if (sendCode == SOCKET_ERROR)
			{
				int32 errorCode = ::WSAGetLastError();
				cout << "Send ErrorCode : " << errorCode << endl;
				return 0;
			}
		}

		SOCKADDR_IN recvAddr;
		::memset(&recvAddr, 0, sizeof(recvAddr));
		int32 addrLen = sizeof(recvAddr);

		char recvBuffer[1000];

		// UDP
		// 1:1 연결이 아니라, 1: 다 연결 가능
		// listener가 없고 SeverSocket으로 나한테 정보를 보낸 것을 Recv한다.

		int32 recvLen = ::recvfrom(clientSocket, recvBuffer, sizeof(recvBuffer), 0, (SOCKADDR*)&recvAddr, &addrLen);
		if (recvLen <= 0)
		{
			int32 errCode = ::WSAGetLastError();
			cout << "Recv ErrorCode " << endl;
			return 0;
		}

		cout << "Recv Data : " << recvBuffer << endl;
		cout << "Recv Len : " << recvLen;

		this_thread::sleep_for(1s);
	}

	::closesocket(clientSocket);
	::WSACleanup();
}
