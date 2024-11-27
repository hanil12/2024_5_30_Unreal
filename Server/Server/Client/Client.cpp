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

struct Player
{
	int32 mesh;
	int32 material;

	int64 id;
	int32 hp;
	int16 atk;
};

class ServerSession : public PacketSession
{
public:
	ServerSession()
	{
	}

	~ServerSession()
	{
		cout << "Session DisConnected" << endl;
	}

	virtual void OnConnected() override 
	{
		cout <<"Server에 접속 성공!!!" << endl;
	} 

	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) override
	{
		ClientPacketHandler::HandlePacket(buffer, len);
		
		return len;
	}

	virtual void OnSend(int32 len) override 
	{
		cout << "Send 성공 : " << len << endl;
	}

	virtual void DisConnected() override 
	{
		cout << "DisConnected" << endl;
	}
};

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


	TM_M->Join();

	CoreGlobal::Delete();

	return 0;
}
