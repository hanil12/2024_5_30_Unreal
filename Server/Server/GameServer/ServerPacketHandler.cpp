#include "pch.h"
#include "ServerPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"

void ServerPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	// TODO : Recv했을 때 패킷 파싱하고 분석
	BufferReader br(buffer, len);

	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case 0: // id가 이였다..?
		break;

	case S_TEST:
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

shared_ptr<SendBuffer> ServerPacketHandler::Make_S_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs, wstring name)
{	shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(1000);

	BufferWriter bw(buf->Buffer(), buf->Capacity());

	PacketHeader* header = bw.Reserve<PacketHeader>();

	bw << id << hp << atk;

	struct VectorHeader
	{
		uint32 offset;
		uint32 count;
	};
	VectorHeader* buffHeader = bw.Reserve<VectorHeader>();
	VectorHeader* nameHeader = bw.Reserve<VectorHeader>();

	buffHeader->offset = bw.WriteSize();
	buffHeader->count = buffs.size();

	// 버프 배열 작성
	for (BuffData& data : buffs)
	{
		bw << data.buffId << data.remainTime;
	}

	nameHeader->offset = bw.WriteSize();
	nameHeader->count = name.size();

	// name 작성
	for (WCHAR c : name)
	{
		bw << c;
	}

	header->id = S_TEST;
	header->size = bw.WriteSize();

	buf->Ready(bw.WriteSize());

	return buf;
}
