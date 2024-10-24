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

	SOCKET serverSocket = ::socket(AF_INET, SOCK_DGRAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErroCode: " << errCode << endl;
		return 0;
	}

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY);
	serverAddr.sin_port = ::htons(7777);

	if (::bind(serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout <<"Bind ErrorCode : " << errCode << endl;
		return 0;
	}

	// UDP
	// ServerSocket.
	// - 여러명의 socket들이 serverSocket한테 직접 정보를 전달
	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);

		this_thread::sleep_for(1s);

		char recvBuffer[1000];

		// UDP
		// 1:1 연결이 아니라, 1: 다 연결 가능
		// listener가 없고 SeverSocket으로 나한테 정보를 보낸 것을 Recv한다.
		int32 recvLen = ::recvfrom(serverSocket, recvBuffer, sizeof(recvBuffer), 0, (SOCKADDR*)&clientAddr, &addrLen);
		if (recvLen <= 0)
		{
			int32 errCode = ::WSAGetLastError();
			cout << "Recv ErrorCode " << endl;
			return 0;
		}

		cout << "Recv Data : " << recvBuffer << endl;
		cout << "Recv Len : " << recvLen;

		char sendBuffer[100] = "Hello Client I'm Server";
		int32 sendCode = ::sendto(serverSocket, sendBuffer, sizeof(sendBuffer), 0, (SOCKADDR*)&clientAddr, sizeof(clientAddr));
		if (sendCode == SOCKET_ERROR)
		{
			int32 errorCode = ::WSAGetLastError();
			cout << "Send ErrorCode : " << errorCode << endl;
			return 0;
		}
	}
	::WSACleanup();

	return 0;
}