#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"
#include "Protocol.pb.h"

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

shared_ptr<SendBuffer> ClientPacketHandler::MakeSendBuffer(Protocol::C_PlayerInfo& pkt)
{
	return _MakeSendBuffer(pkt, PacketID::C_PLAYER_INFO);
}
