#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

int main()
{
	// 윈속 초기화(ws2_32 라이브러리 초기화)
	// 관련 정보가 wsaData에 채워짐
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// 1. Listener Socket 만들기 => 연결 시도를 받아줄
	// AF_INET vs AT_INET6 ... IPv4 vs IPv6
	// SOCK_STREAM vs SOCK_DGRAM ... TCP vs UDP => 면접문제
	// 0 : 자동으로 protocol 설정
	SOCKET listener = ::socket(AF_INET, SOCK_STREAM, 0); // socket의 번호를 발급
	if (listener == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout << "Socket ErroCode: " << errCode << endl;
		return 0;
	}

	// 2. 내가 어떻게 받아야할지... Listener에 세팅
	SOCKADDR_IN serverAddr; // IPv4
	::memset(&serverAddr, 0, sizeof(serverAddr)); // serverAddr 0으로 다 밀어버리기
	serverAddr.sin_family = AF_INET; // IPv4
	//::inet_pton(AF_INET, "192.168.0.9", &serverAddr.sin_addr);
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // < 니가 알아서 IP주소 써줘  192.168.0.9
	serverAddr.sin_port = ::htons(7777); // 1 ~ 1000 여기는 건들면 안됌.

	// 3. Listener 세팅
	if (::bind(listener, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout <<"Bind ErrorCode : " << errCode << endl;
		return 0;
	}

	// 4. 연결(Listen) 준비
	// backlog : 대기자
	if (::listen(listener, 10) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout <<"Listen ErrorCode : " << errCode << endl;
		return 0;
	}

	// -----------연결 준비 끝-----------

	while (true)
	{
		// 5. Accept
		SOCKADDR_IN clientAddr; // IPv4
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);

		// listner한테 현재 대기 중인 클라이언트를 받아서 정보 추출(client Addr)
		SOCKET clientSocket = ::accept(listener, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			int32 errCode = ::WSAGetLastError();
			cout <<"Accept ErrorCode : " << errCode << endl;

			return 0;
		}

		// ---- 손님 입장(Client Accept) ----
		char ipAddress[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ipAddress, sizeof(ipAddress));
		cout << "Client Connected! Client IP = " << ipAddress << endl;

		// ... TODO
	}

	// 6. 윈속 종료
	::closesocket(listener);
	::WSACleanup();

	return 0;
}