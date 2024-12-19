#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "GameSession.h"
#include "Room.h"
#include "Player.h"

/*
void Server_PacketHandler::HandlePacket(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
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

	case C_CHATMSG:
		Handle_C_ChatMsg(session, buffer, len);
		break;

	default:
		break;
	}
}

void Server_PacketHandler::Handle_C_PlayerInfo(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
	shared_ptr<GameSession> gameSession = static_pointer_cast<GameSession>(session);

	Protocol::C_PlayerInfo pkt;

	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	cout <<"클라이언트가 보낸 정보" << endl;
	cout << "Name : " << pkt.name() << endl;
	cout << "ID : " << pkt.id() << endl;
	cout << "HP : " << pkt.hp() << endl;
	cout << "ATK : " << pkt.atk() << endl;

	shared_ptr<Player> newPlayer = make_shared<Player>();
	newPlayer->name = pkt.name();
	newPlayer->playerId = pkt.id();
	newPlayer->hp = pkt.hp();
	newPlayer->atk = pkt.atk();
	newPlayer->_ownerSession = gameSession;

	gameSession->_curPlayer = newPlayer;
	G_Room->Enter(newPlayer);

	Protocol::S_EnterRoom sendPkt;
	sendPkt.set_success(true);

	session->Send(MakeSendBuffer(sendPkt));

	return ;
}

void Server_PacketHandler::Handle_C_ChatMsg(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
	shared_ptr<GameSession> gameSession = static_pointer_cast<GameSession>(session);

	Protocol::C_ChatMsg pkt;
	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	uint64 id = pkt.id();
	string msg = pkt.msg();

	Protocol::S_ChatMsg sendPkt;
	sendPkt.set_msg(msg);

	string name = G_Room->GetPlayerName(id);
	if(name == "")	return;

	sendPkt.set_name(name);

	G_Room->BroadCast(MakeSendBuffer(sendPkt));
}
*/

////////////////////
///  Delegate //////
///////////////////

PacketHandlerFunc G_PacketHandler[UINT16_MAX];

bool Handler_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int32 len)
{
	PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
	// header->id...??
	// Log

	return false;
}

bool Handle_C_PlayerInfo(shared_ptr<PacketSession>& session, Protocol::C_PlayerInfo& pkt)
{
	cout << "클라이언트가 보낸 정보" << endl;
	cout << "Name : " << pkt.name() << endl;
	cout << "ID : " << pkt.id() << endl;
	cout << "HP : " << pkt.hp() << endl;
	cout << "ATK : " << pkt.atk() << endl;

	shared_ptr<GameSession> gameSession = static_pointer_cast<GameSession>(session);

	shared_ptr<Player> newPlayer = make_shared<Player>();
	newPlayer->name = pkt.name();
	newPlayer->playerId = pkt.id();
	newPlayer->hp = pkt.hp();
	newPlayer->atk = pkt.atk();
	newPlayer->_ownerSession = gameSession;

	gameSession->_curPlayer = newPlayer;
	G_Room->Enter(newPlayer);

	Protocol::S_EnterRoom sendPkt;
	sendPkt.set_success(true);

	session->Send(Server_PacketHandler::MakeSendBuffer(sendPkt));

	return true;
}

bool Handle_C_ChatMsg(shared_ptr<PacketSession>& session, Protocol::C_ChatMsg& pkt)
{
	uint64 id = pkt.id();
	string msg = pkt.msg();

	Protocol::S_ChatMsg sendPkt;
	sendPkt.set_msg(msg);

	string name = G_Room->GetPlayerName(id);
	if (name == "")	return false;

	sendPkt.set_name(name);

	G_Room->BroadCast(Server_PacketHandler::MakeSendBuffer(sendPkt));

	return true;
}
