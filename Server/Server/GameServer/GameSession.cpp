#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"

GameSession::GameSession()
{
	
}

GameSession::~GameSession()
{
}

void GameSession::OnConnected()
{
	// �����ϸ� �������ִ� ��� Ŭ���̾�Ʈ�鿡�� �����ߴٰ� ��۰���
	
	vector<BuffData> buffs;
	buffs.push_back({1, 48.0f});
	buffs.push_back({2, 2.0f});

	shared_ptr<SendBuffer> sendBuffer = ServerPacketHandler::Make_S_TEST(1234,10,5, buffs, L"Hanil");
	G_GameSessionManager->BroadCast(sendBuffer);

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

	ServerPacketHandler::HandlePacket(buffer, len);

	return len;
}

void GameSession::DisConnected()
{
	G_GameSessionManager->Remove(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "DisConnected" << endl;
}