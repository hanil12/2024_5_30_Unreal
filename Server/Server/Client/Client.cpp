#include "pch.h"

// Socket 만들기
// - ipv6
// - port
// - protocol

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#include "Session.h"
#include "SendBuffer.h"
#include "Service.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "ClientPacketHandler.h"
#include "ServerSession.h"

Player G_Player;

int main()
{
	this_thread::sleep_for(1s);

	CoreGlobal::Create();

	shared_ptr<ClientService> service = MakeShared<ClientService>
		(
			NetAddress(L"192.168.0.9", 7777),
			MakeShared<IocpCore>(),
			MakeShared<ServerSession>,
			1
		);

	service->Start();

	for (int i = 0; i < 5; i++)
	{
		TM_M->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	// 5초 대기 : Server에 EnterRoom하기 전에 메시지 패킷 보내면 X
	// => 5초 안에 PlayerInfo pkt을 날려줘야한다.
	this_thread::sleep_for(10s);
	cout << "메시지를 입력하세요 : " << endl;

	// main
	while (true)
	{
		string sendMsg;

		//cin >> sendMsg; // block - 동기
		std::getline(std::cin, sendMsg); // non block - 비동기

		Protocol::C_ChatMsg sendPkt;
		sendPkt.set_id(G_Player.id);
		sendPkt.set_msg(sendMsg);

		auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPkt);
		service->BroadCast(sendBuffer); // client에서 BroadCast 해도 서버 밖에 없음.
	}

	TM_M->Join();

	CoreGlobal::Delete();

	return 0;
}
