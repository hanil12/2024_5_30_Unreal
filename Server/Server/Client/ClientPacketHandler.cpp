#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "Protocol.pb.h"
#include "ServerSession.h"

void ClientPacketHandler::HandlePacket(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);
	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case 0: // id가 이였다..?
		break;

	case S_PLAYER_INFO:
		Handle_S_PlayerInfo(session, buffer, len);
		break;

	case S_ENTEROOM:
		Handle_S_EnterRoom(session, buffer, len);
		break;

	case S_CHATMSG:
		Handle_S_ChatMsg(session, buffer, len);
		break;

	default:
		break;
	}
}

void ClientPacketHandler::Handle_S_PlayerInfo(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
	Protocol::S_PlayerInfo pkt;

	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	cout << "ID: " << pkt.id() << "  HP : " << pkt.hp() << "  ATK : " << pkt.atk() << endl;
	cout << "BUFFS SIZE : " << pkt.buffs_size() << endl;

	for (auto& buff : pkt.buffs())
	{
		cout << "BUFF ID : " << buff.buffid() << endl;
		cout << "REMAIN TIME : " << buff.remaintime() << endl;
		cout << "VICTIMS SIZE : " << buff.victims_size() << endl;

		for (auto& victim : buff.victims())
		{
			cout << "VICTIM ID : " << victim << endl;
		}

		cout << endl;
	}

	// 다시 서버한테 C_PLAYER_INFO
	// id, hp, atk
}

void ClientPacketHandler::Handle_S_EnterRoom(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
	// TODO : 씬 이동
	// 실패했으면 ASSERT 시켜서 종료
	Protocol::S_EnterRoom pkt;

	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	bool success = pkt.success();

	if (success == false)
	{
		CRASH("CAN NOT ENTER");
	}

	string sendMsg;

	Protocol::C_ChatMsg sendPkt;
	sendPkt.set_id(G_Player.id);
	sendPkt.set_msg(u8"Hello !!!");

	auto sendBuffer = ClientPacketHandler::MakeSendBuffer(sendPkt);
	session->Send(sendBuffer);

	return;
}

void ClientPacketHandler::Handle_S_ChatMsg(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
{
	Protocol::S_ChatMsg pkt;

	pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader));

	string name = pkt.name();
	string msg = pkt.msg();

	cout << name << ": " << msg << endl;
}

shared_ptr<SendBuffer> ClientPacketHandler::MakeSendBuffer(Protocol::C_PlayerInfo& pkt)
{
	return _MakeSendBuffer(pkt, PacketID::C_PLAYER_INFO);
}

shared_ptr<SendBuffer> ClientPacketHandler::MakeSendBuffer(Protocol::C_ChatMsg& pkt)
{
	return _MakeSendBuffer(pkt, PacketID::C_CHATMSG);
}
