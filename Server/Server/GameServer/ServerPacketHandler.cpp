#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"

void ServerPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	// TODO : Recv���� �� ��Ŷ �Ľ��ϰ� �м�
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case 0: // id�� �̿���..?
		break;

	case C_PLAYER_INFO:
		Handle_S_TEST(buffer, len);
		break;

	default:
		break;
	}
}

void ServerPacketHandler::Handle_S_TEST(BYTE* buffer, int32 len)
{
	// TODO

	return ;
}

shared_ptr<SendBuffer> ServerPacketHandler::MakeSendBuffer(Protocol::S_PlayerInfo& pkt)
{
	return _MakeSendBuffer<Protocol::S_PlayerInfo>(pkt, S_PLAYER_INFO);
}
