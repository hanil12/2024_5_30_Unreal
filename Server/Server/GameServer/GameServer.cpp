#include "pch.h"

#include <WinSock2.h>
#include <MSWSock.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib")

#include "Service.h"

int main()
{
	CoreGlobal::Create();

	shared_ptr<ServerService> service = MakeShared<ServerService>
	(
		NetAddress(L"127.0.0.1", 7777),
		MakeShared<IocpCore>(),
		MakeShared<Session>,
		100
	);

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