#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
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
		Handle_C_TEST(buffer, len);
		break;

	default:
		break;
	}
}

// header[4] [ ID(1), hp(100), atk(5), 2 ,사랑니, 1.0, 마취, 2.0]
// 
// 
// Player Id : 1, hp : 100, atk : 5, buff[사랑니, 1.0], buff[마취, 2.0]
void ClientPacketHandler::Handle_C_TEST(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PacketHeader header;
	br >> header;

	// 헤더 읽음...
	int64 id;
	int32 hp;
	int16 atk;
	br >> id >> hp >> atk;
	// id, hp, atk 읽음
	
	vector<BuffData> buffs;
	int16 buffCount = 0;
	br >> buffCount;
	buffs.resize(buffCount);

	for (int32 i = 0; i < buffCount; i++)
	{
		br >> buffs[i].buffId >> buffs[i].remainTime;
	}

	wstring name;
	uint16 nameSize;
	br >> nameSize;
	name.resize(nameSize);

	br.Read((void*)name.data(), nameSize * sizeof(WCHAR));

	cout << "ID : " << id << " HP : " << hp << " ATK : " << atk << endl;
	for (auto& buff : buffs)
	{
		cout << "Buff ID : " << buff.buffId << endl;
		cout << "Buff Remain Time : " << buff.remainTime << endl;
	}

	//wstring temp = L"gggg";
	//wcout << temp << endl;
	wcout.imbue(std::locale("kor"));
	wcout << name << endl;
}

shared_ptr<SendBuffer> ClientPacketHandler::Make_C_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs)
{
	shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(1000);
	PlayerInfo_Protocol p;
	p.id = id;
	p.hp = hp;
	p.atk = atk;

	BufferWriter bw(buf->Buffer(), buf->Capacity());

	PacketHeader* header = bw.Reserve<PacketHeader>();
	header->id = S_TEST;
	header->size = (sizeof(p) + sizeof(PacketHeader));
	bw << p;

	buf->Ready(bw.WriteSize());

	return buf;
}
