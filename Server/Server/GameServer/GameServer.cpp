#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#include "Service.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "Room.h";
// temp
#include "Protocol.pb.h"
#include "ServerPacketHandler.h"

// GameSession : 서버에서 클라이언트가 접속하면 안내할 식탁
// GameSessionManager : 모든 클라이언트가 앉아있는 식탁들을 관리하는 수단

Room* G_Room = nullptr;

int main()
{
	Server_PacketHandler::Init();

	CoreGlobal::Create();
	G_GameSessionManager = new GameSessionManager();


	shared_ptr<ServerService> service = MakeShared<ServerService>
	(
		NetAddress(L"192.168.0.9", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,
		100
	);

	service->Start();

	G_Room = new Room();

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

	TM_M->Join();

	//delete G_GameSessionManager;
	CoreGlobal::Delete();

	return 0;
}