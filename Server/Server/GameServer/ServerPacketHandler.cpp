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
		break;

	default:
		break;
	}
}

// Player Id : 1, hp : 100, atk : 5, buff[사랑니, 1.0], buff[마취, 2.0]
// header[4] [ ID(1), hp(100), atk(5), 2 ,사랑니, 1.0, 마취, 2.0]
shared_ptr<SendBuffer> ServerPacketHandler::Make_S_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs, wstring name)
{
	shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(1000);
	PlayerInfo_Protocol p;
	p.id = id;
	p.hp = hp;
	p.atk = atk;

	BufferWriter bw(buf->Buffer(), buf->Capacity());
	// Header Reserve, packet 아이디 설정
	PacketHeader* header = bw.Reserve<PacketHeader>();
	header->id = S_TEST;

	bw << p.id << p.hp << p.atk;

	// 가변데이터 넣기
	bw << (uint16)buffs.size();
	for (auto& buff : buffs)
	{
		bw << buff.buffId << buff.remainTime;
	}

	// FString... wchar;
	// WString 전송
	bw << (uint16)name.size();
	bw.Write((void*)name.data(), name.size() * sizeof(WCHAR));

	// 패킷 준비완료, kg 재서 출하준비
	header->size = bw.WriteSize();

	// 출하준비
	buf->Ready(bw.WriteSize());

	return buf;
}
