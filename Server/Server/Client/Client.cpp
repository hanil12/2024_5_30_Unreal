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
	// 윈속 초기화(ws2_32 라이브러리 초기화)
	// 관련 정보가 wsaData에 채워짐
	WSAData wsaData;
	if(::WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		return 0;

	// 1. Clinet Socket 만들기 => 서버에 연결 시킬 Sck 만들기
	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0); // socket의 번호를 발급
	if (clientSocket == INVALID_SOCKET)
	{
		int32 errCode = ::WSAGetLastError();
		cout <<"Socket ErroCode: " << errCode << endl;
		return 0;
	}

	// 2. Server에 어디에 연결할지 (IP주소 + 포트번호)
	SOCKADDR_IN serverAddr; // IPv4
	::memset(&serverAddr , 0, sizeof(serverAddr)); // serverAddr 0으로 다 밀어버리기
	serverAddr.sin_family = AF_INET; // IPv4
	::inet_pton(AF_INET,"192.168.0.9", &serverAddr.sin_addr); // 127.0.0.1 => Loop back : 자기 PC의 주소
	serverAddr.sin_port = ::htons(7777); // 1 ~ 1000 여기는 건들면 안됌.
	// 네트워크 정수 표현 => 빅엔디언
	
	// 3. 연결(Connect)
	if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		int32 errCode = ::WSAGetLastError();
		cout <<"Connet ErrorCode : " << errCode << endl;
		return 0;
	}

	// ------------ 연결 성공 --------------
	cout << "Conneted To Server!" << endl;

	while (true)
	{
		// ... 서버에서 데이터 들어온 것 분석, 혹은 클라이언트 코드 실행
		this_thread::sleep_for(1s);
	}

	// 4. 소켓 리소스 반환 및 윈속 종료
	::closesocket(clientSocket);
	::WSACleanup();
}
