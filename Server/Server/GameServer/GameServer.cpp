#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

const int32 BuffSize = 1000;

struct Session
{
	SOCKET socket = INVALID_SOCKET;
	char recvBuffer[BuffSize] = {};
	char sendBuffer[100] = "Hello Im Server!!!";
	int32 recvBytes = 0;
	int32 sendBytes = 0;
};

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// SELECT 기반 소켓프로그래밍 
	// 소켓 함수 호출이 성공할 시점을 미리 알 수 있다.
	// ...문제
	// recvBuff에 데이터가 없는데 recv해서 읽을려고한다. (X)
	// sendBuff(커널)에 꽉 찼는데 send함수(유저레벨 sendBuffer -> 커널레벨 sendBuffer에 복사) 호출 (X)

	// socket set
	// 1) 읽기, 쓰기, 예외... 관찰 대상 등록
	// 2) select(readSet, writeSet, exceptSet); => 관찰
	// 3) 적어도 하나의 소켓이 준비되면 리턴
	// 4) 남은 소켓 체크해서 진행

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

	// Select 기반 Socket

	vector<Session> sessions;
	sessions.reserve(100);
	
	// 소켓 Set
	fd_set reads;
	fd_set writes;

	while (true)
	{
		// 소켓 셋 초기화
		FD_ZERO(&reads);
		FD_ZERO(&writes);

		// ListenSocket 등록
		FD_SET(listenSocket, &reads);

		// clients 소켓 등록
		for (auto& session : sessions)
		{
			if(session.recvBytes <= session.sendBytes)
				FD_SET(session.socket, &reads);
			else
				FD_SET(session.socket, &writes);
		}


		int32 retVal = ::select(0, &reads, &writes, nullptr, nullptr);
		if(retVal == SOCKET_ERROR)
			break;

		// Listener 소켓 체크
		if (FD_ISSET(listenSocket, &reads))
		{
			SOCKADDR_IN clientAddr;
			int32 addrLen = sizeof(clientAddr);
			SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
			if (clientSocket != INVALID_SOCKET)
			{
				// 클라이언트 접속
				cout << "Client Connected" << endl;
				sessions.push_back(Session{clientSocket});
			}
		}

		// 나머지 소켓 체크
		for (Session& session : sessions)
		{
			// Read
			if (FD_ISSET(session.socket, &reads))
			{
				int32 recvLen = ::recv(session.socket, session.recvBuffer, BuffSize, 0);
				if (recvLen <= 0)
				{
					// TODO : session Disconnect
					continue;
				}

				session.recvBytes = recvLen;
				cout << "RecvSize : " << session.recvBytes << endl;
			}

			// 현재 상황 
			// - client가 10개짜리 문자열을 보냈고, 10개를 받은 상황
			// - 처음 recv 받고, 첫 send하기 시작
			// recvBytes = 100
			// sendBytes = 0

			// write
			if (FD_ISSET(session.socket, &writes))
			{
				// 블로킹 모드 -> 모든 데이터를 다 보낼 때까지 대기
				// 논블로킹 모드-> 일부만 보낼 수 있음. (상대방의 recvBuff에 따라서)
				int32 sendLen = ::send(session.socket, session.recvBuffer, session.recvBytes - session.sendBytes, 0); // 
				// sendLen : 보냈을 때 그 길이... 30
				if (sendLen == SOCKET_ERROR)
				{
					// TODO : DisConnect
					continue;
				}

				session.sendBytes += sendLen;
				cout << "SendSize : " << session.sendBytes << endl;

				if (session.recvBytes == session.sendBytes)
				{
					session.sendBytes = 0;
					session.recvBytes = 0;
				}
			}
		}
	}

	
	::WSACleanup();

	return 0;
}