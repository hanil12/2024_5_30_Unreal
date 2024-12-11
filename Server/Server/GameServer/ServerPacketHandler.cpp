#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "GameSession.h"
#include "Room.h"
#include "Player.h"

void ServerPacketHandler::HandlePacket(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
	// TODO : Recv했을 때 패킷 파싱하고 분석
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case 0: // id가 이였다..?
		break;

	case C_PLAYER_INFO:
		Handle_C_PlayerInfo(session,buffer, len);
		break;

	default:
		break;
	}
}

void ServerPacketHandler::Handle_C_PlayerInfo(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
	shared_ptr<GameSession> gameSession = static_pointer_cast<GameSession>(session);

	Protocol::C_PlayerInfo pkt;

	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	cout <<"클라이언트가 보낸 정보" << endl;
	cout << "ID : " << pkt.id() << endl;
	cout << "HP : " << pkt.hp() << endl;
	cout << "ATK : " << pkt.atk() << endl;

	shared_ptr<Player> newPlayer = make_shared<Player>();
	newPlayer->playerId = pkt.id();
	newPlayer->hp = pkt.hp();
	newPlayer->atk = pkt.atk();
	// TODO  newPlayer->name
	newPlayer->_ownerSession = gameSession;

	gameSession->_curPlayer = newPlayer;
	// TODO : Room에 Player들 저장
	G_Room->Enter(newPlayer);

	return ;
}

shared_ptr<SendBuffer> ServerPacketHandler::MakeSendBuffer(Protocol::S_PlayerInfo& pkt)
{
	return _MakeSendBuffer<Protocol::S_PlayerInfo>(pkt, S_PLAYER_INFO);
}
