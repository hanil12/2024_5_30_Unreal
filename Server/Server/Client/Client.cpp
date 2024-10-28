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

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr , 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET,"127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777);




	::closesocket(clientSocket);
	::WSACleanup();
}
