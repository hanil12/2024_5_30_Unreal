#include "pch.h"

// Socket 만들기
// - ipv6
// - port
// - protocol

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

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
			NetAddress(L"127.0.0.1", 7777),
			MakeShared<IocpCore>(),
			MakeShared<ServerSession>,
			1
		);

	service->Start();

	for (int i = 0; i < 2; i++)
	{
		TM_M->Launch([=]()
			{
				while (true)
				{
					service->GetIocpCore()->Dispatch();
				}
			});
	}

	// Main Thread 
	while (true)
	{
		// 현재 방에 입장했냐?
		string sendMsg;

		cin >> sendMsg;

		Protocol::C_ChatMsg pkt;
		pkt.set_id(0);
		pkt.set_msg(u8"Hello !!!");
	}


	TM_M->Join();

	CoreGlobal::Delete();

	return 0;
}
