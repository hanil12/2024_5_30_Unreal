#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#include "Service.h"

class GameSession : public Session
{
public:
	GameSession()
	{
	}

	~GameSession()
	{
		cout << "Session DisConnected" << endl;
	}
	
	virtual void OnConnected() override
	{
		cout << "클라이언트가 서버에 접속 성공!!!" << endl;

		string temp = "Hello Client Connected";

		shared_ptr<SendBuffer> sendBuf = make_shared<SendBuffer>(100);
		sendBuf->CopyData((void*)temp.data(), temp.size());
		Send(sendBuf);
	}
	
	virtual int32 OnRecv(BYTE* buffer, int32 len)
	{
		for (int i = 0; i < len; i++)
		{
			cout << buffer[i];
		}
		cout << endl;


		this_thread::sleep_for(1s);

		string temp = "Hello Client!!!";

		shared_ptr<SendBuffer> sendBuf = make_shared<SendBuffer>(100);
		sendBuf->CopyData((void*)temp.data(), temp.size());
		Send(sendBuf);
		
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
	CoreGlobal::Create();

	shared_ptr<ServerService> service = MakeShared<ServerService>
	(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<GameSession>,
		100
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


	TM_M->Join();

	CoreGlobal::Delete();

	return 0;
}