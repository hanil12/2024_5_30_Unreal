#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"

GameSession::GameSession()
{
	
}

GameSession::~GameSession()
{
}

void GameSession::OnConnected()
{
	// 입장하면 입장해있던 모든 클라이언트들에게 입장했다고 방송고지
	{
		shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(100);
		string temp = "client entered!!!";
		buf->CopyData((void*)temp.data(), temp.size());

		G_GameSessionManager->BroadCast(buf);
	}
	G_GameSessionManager->Add(static_pointer_cast<GameSession>(shared_from_this()));

	//string temp2 = "Hello Client Connected";

	//shared_ptr<SendBuffer> sendBuf = make_shared<SendBuffer>(100);
	//sendBuf->CopyData((void*)temp2.data(), temp2.size());
	//Send(sendBuf);
}

int32 GameSession::OnRecv(BYTE* buffer, int32 len)
{
	for (int i = 0; i < len; i++)
	{
		cout << buffer[i];
	}
	cout << endl;


	this_thread::sleep_for(1s);

	//string temp = "Hello Client!!!";

	//shared_ptr<SendBuffer> sendBuf = make_shared<SendBuffer>(100);
	//sendBuf->CopyData((void*)temp.data(), temp.size());
	//Send(sendBuf);

	return len;
}

void GameSession::OnSend(int32 len)
{
	cout << "Send 성공 : " << len << endl;
}

void GameSession::DisConnected()
{
	G_GameSessionManager->Remove(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "DisConnected" << endl;
}