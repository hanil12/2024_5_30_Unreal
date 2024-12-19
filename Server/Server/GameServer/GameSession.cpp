#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"
#include "Protocol.pb.h"

GameSession::GameSession()
{
	
}

GameSession::~GameSession()
{
}

void GameSession::OnConnected()
{
	G_GameSessionManager->Add(static_pointer_cast<GameSession>(shared_from_this()));
}


void GameSession::OnSend(int32 len)
{
	cout << "Send ¼º°ø : " << len << endl;
}

int32 GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader header = *((PacketHeader*)buffer);

	cout << "Paket ID : " << header.id << "  Size : " << header.size << endl;

	Server_PacketHandler::HandlePacket(static_pointer_cast<PacketSession>(shared_from_this()), buffer, len);

	return len;
}

void GameSession::DisConnected()
{
	G_GameSessionManager->Remove(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "DisConnected" << endl;
}