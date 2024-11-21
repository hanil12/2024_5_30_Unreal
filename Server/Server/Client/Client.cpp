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

class ServerSession : public Session
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

		shared_ptr<SendBuffer> sendBuf = make_shared<SendBuffer>(100);
		string temp = "Hello Server!! I'm Client";
		sendBuf->CopyData((void*)temp.data(), temp.size());
		Send(sendBuf);
	} 

	// string temp = "Hello Client Connected";
	// recvBuf :["Hello Client Connected"]

	virtual int32 OnRecv(BYTE* buffer, int32 len) override 
	{ 
		for (int i = 0; i < len; i++)
		{
			cout << buffer[i];
		}
		cout << endl;


		//this_thread::sleep_for(100ms);
		//shared_ptr<SendBuffer> sendBuf = make_shared<SendBuffer>(100);
		//string temp = "Hello Server!! I'm Client~~~~~~~";
		//sendBuf->CopyData((void*)temp.data(), temp.size());
		//Send(sendBuf);

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
