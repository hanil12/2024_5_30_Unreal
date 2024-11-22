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
	// �����ϸ� �������ִ� ��� Ŭ���̾�Ʈ�鿡�� �����ߴٰ� ��۰���

	shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(100);
	string temp = "client entered!!!";

	BYTE* buffer = buf->Buffer();
	((PacketHeader*)buffer)->id = 1; // id : 1 �̸� Hello MSG
	((PacketHeader*)buffer)->size = (sizeof(temp) + sizeof(PacketHeader));

	// sendBuffer�� writePos�� ���� �Ұ�
	// ::memcpy(&buffer[4], temp.data(), sizeof(temp));
	buf->CopyData_Packet((BYTE*)temp.data(), sizeof(temp));

	G_GameSessionManager->BroadCast(buf);

	G_GameSessionManager->Add(static_pointer_cast<GameSession>(shared_from_this()));
}


void GameSession::OnSend(int32 len)
{
	cout << "Send ���� : " << len << endl;
}

int32 GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader header = *((PacketHeader*)buffer);

	cout << "Paket ID : " << header.id << "  Size : " << header.size << endl;

	return len;
}

void GameSession::DisConnected()
{
	G_GameSessionManager->Remove(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "DisConnected" << endl;
}