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

	SOCKET serverSocket = ::socket(AF_INET, SOCK_STREAM, 0);
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

	// Socket level
	// 옵션을 해석, 처리하는 주체
	// 소켓 코드-> SOL_SOCKET
	// IPv4 -> IPPROTO_IP
	// TCP -> IPPROTO_TCP

	// Socket 옵션
	// SO_KEEPALIVE => 주기적으로 연결이 끊겼는지 확인하는 옵션
	bool enable = true;
	::setsockopt(serverSocket, SOL_SOCKET, SO_KEEPALIVE, (char*)(&enable), sizeof(enable));

	// 소켓 만들기
	// => 운영체제 ... Socket 번호
	// => 운영체제 ... SendBuff, RecvBuff

	// 우리가 하던 거
	// sendBuff를 stack이나 heap에 사용자정의로 만든다.
	char arr[100] = "temp";
	// send(serverSocket, arr, 100, nullptr); => 사용자가 만든 sendBuffer를 운영체제가 만들어놓은 sendBuffer에 복사

	// 소켓을 닫을려고함
	// -> Send("~~")
	// -> SendBuff에 복사
	// -> Socket이 닫힘
	LINGER linger;
	linger.l_onoff = 1;
	linger.l_linger = 5;
	::setsockopt(serverSocket, SOL_SOCKET, SO_LINGER, (char*)(&linger), sizeof(linger));

	// SendBuff의 크기 가져오기
	int32 sendBuffSize;
	int32 optionLen = sizeof(sendBuffSize);

	::getsockopt(serverSocket, SOL_SOCKET, SO_SNDBUF, (char*)(&sendBuffSize), &optionLen);
	cout <<"SendBuffer Size : " << sendBuffSize << endl;

	// recvBuff의 크기 가져오기
	int32 recvBuffSize;
	optionLen = sizeof(recvBuffSize);

	::getsockopt(serverSocket, SOL_SOCKET, SO_RCVBUF, (char*)(&recvBuffSize), &optionLen);
	cout << "SendBuffer Size : " << recvBuffSize << endl;

	// SO_REUSEADDR
	// IP 주소 및 포트번호 재사용
	{
		bool enable = true;
		::setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)(&enable), sizeof(enable));
	}

	// 네이글 알고리즘
	// 작은 패킷들을 한번에 모아서 보내는 알고리즘
	// 장점 : 작은 패킷이 불필요하게 많이 생성되는 일을 방지
	// 단점 : 반응 시간 손해
	// => 네이글 알고리즘이 처리하기 전에 프로그래머(우리)가 알아서 패킷 설계를 하고 보낼 거기 때문에
	{
		bool enable = false;
		::setsockopt(serverSocket, IPPROTO_TCP, TCP_NODELAY, (char*)(&enable), sizeof(enable));
	}

	::WSACleanup();

	return 0;
}