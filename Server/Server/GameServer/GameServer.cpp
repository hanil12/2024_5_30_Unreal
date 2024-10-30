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

	// 1. Select 기반 Socket IO(소켓 입출력)
	// 2. WSAEventSelect 기반 Socket IO

	// WSAEventSelect 기반 => WSAEventSelect가 핵심
	// (소켓 - 이벤트객체) 네트워크 이벤트를 (이벤트 객체로) 감지
	
	// 이벤트 객체 관련 함수
	// 생성 : WSACreateEvent
	// 삭제 : WSACloseEvent
	// (여러 이벤트들의)신호상태감지 : WSAWaitforMultipleEvents
	// 구체적인 네트워크 이벤트 확인 : WSAEnumNetworkEvents

	// (소켓 - 이벤트객체) 연동
	// WSAEventSelect(socket, event, netWorkEvents);
	// - 주로쓰는 네트워크 이벤트
	// -- FD_ACCPET => accept
	// -- FD_READ => recv
	// -- FD_WRITE => send
	// -- FD_CLOSE : 상대가 접속 종료
	// -- FD_CONNECT : 상대 접속 확인

	vector<WSAEVENT> wsaEvents;
	vector<Session> sessions;
	sessions.reserve(100);
	
	WSAEVENT listenEvent = WSACreateEvent(); // Listen 이벤트객체 생성
	wsaEvents.push_back(listenEvent);
	sessions.push_back(Session{listenSocket}); // 0 인덱스로 연동
	if(::WSAEventSelect(listenSocket, listenEvent, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR) // 소켓, 이벤트객체 연동
		return 0;

	while (true)
	{
		// 여러 Event 객체들의 신호상태 감지
		int32 index = ::WSAWaitForMultipleEvents(wsaEvents.size(), wsaEvents.data(), FALSE, WSA_INFINITE, FALSE);
		if(index == WSA_WAIT_FAILED)
			continue;

		index -= WSA_WAIT_EVENT_0; // 소켓과 이벤트 객체를 1:1 대응시킨 인덱스 찾기
								   // sessions, wsaEvents

		// 구체적인 네트워크 이벤트 알아내기
		WSANETWORKEVENTS networkEvents;
		if(::WSAEnumNetworkEvents(sessions[index].socket, wsaEvents[index], &networkEvents) == SOCKET_ERROR)
			continue;

		// Listener 소켓 체크
		if (networkEvents.lNetworkEvents & FD_ACCEPT)
		{
			SOCKADDR_IN clientAddr;
			int32 addrLen = sizeof(clientAddr);
			SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
			if (clientSocket != INVALID_SOCKET)
			{
				// 클라이언트 접속
				cout << "Client Connected" << endl;

				WSAEVENT clientEvent = ::WSACreateEvent();
				sessions.push_back(Session{ clientSocket });
				wsaEvents.push_back(clientEvent);

				if (::WSAEventSelect(clientSocket, clientEvent, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR) // socket, eventObj 연동
				{
					return 0;
				}
			}
		}

		// Client Socket 체크
		if (networkEvents.lNetworkEvents & FD_READ || networkEvents.lNetworkEvents & FD_WRITE)
		{
			// Error Check
			if ((networkEvents.lNetworkEvents & FD_READ) && (networkEvents.iErrorCode[FD_READ_BIT] != 0))
				continue;

			if ((networkEvents.lNetworkEvents & FD_WRITE) && (networkEvents.iErrorCode[FD_WRITE_BIT] != 0))
				continue;

			Session& session = sessions[index];

			// Recv
			if (session.recvBytes == 0)
			{
				int32 recvLen = ::recv(session.socket, session.recvBuffer, BuffSize,0);
				if (recvLen == SOCKET_ERROR && ::WSAGetLastError() != WSAEWOULDBLOCK )
				{
					// TODO : Disconnect 
					continue;
				}

				if(recvLen < 0)
					continue;

				session.recvBytes = recvLen;
				cout << "Recv Data Size = " << recvLen << endl;
			}
			
			// Send
			if (session.recvBytes > session.sendBytes)
			{
				int32 sendLen = ::send(session.socket, &session.recvBuffer[session.sendBytes], session.recvBytes - session.sendBytes, 0);
				if (sendLen == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
				{
					// TODO : Disconnect
					continue;
				}

				session.sendBytes += sendLen;
				if (session.recvBytes == session.sendBytes)
				{
					session.recvBytes = 0;
					session.sendBytes = 0;
				}

				cout << "Send Data = " << sendLen << endl;
			}
		}

		if (networkEvents.lNetworkEvents & FD_CLOSE)
		{
			// TODO : Remove Socket
			// Disconnect
		}
	}

	
	::WSACleanup();

	return 0;
}