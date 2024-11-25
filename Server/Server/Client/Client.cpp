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

		//shared_ptr<SendBuffer> sendBuf = make_shared<SendBuffer>(100);
		//string temp = "Hello Server!! I'm Client";
		//sendBuf->CopyData((void*)temp.data(), temp.size());
		//Send(sendBuf);
	} 

	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) override
	{
		Player p;

		BufferReader br(buffer, len);

		PacketHeader header;
		br >> header;

		int64 id;
		int32 hp;
		int16 atk;
		br >> id >> hp >> atk;

		cout << "ID : " << id << " HP : " << hp << " ATK : " << atk << endl;

		p.id = id;
		p.hp = hp;
		p.atk = atk;

		//BYTE recvBuffer[1000];
		//br.Read(recvBuffer, header.size);
		
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
