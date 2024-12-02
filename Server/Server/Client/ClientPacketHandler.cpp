#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	// TODO : Recv���� �� ��Ŷ �Ľ��ϰ� �м�
	BufferReader br(buffer, len);
	int32 t = sizeof(PlayerInfo_Protocol);
	PacketHeader header;
	br.Peek(&header);

	switch (header.id)
	{
	case 0: // id�� �̿���..?
		break;

	case S_TEST:
		Handle_C_TEST(buffer, len);
		break;

	default:
		break;
	}
}

// header[4] [ ID(1), hp(100), atk(5), 2 ,�����, 1.0, ����, 2.0]
// 
// 
// Player Id : 1, hp : 100, atk : 5, buff[�����, 1.0], buff[����, 2.0]
void ClientPacketHandler::Handle_C_TEST(BYTE* buffer, int32 len)
{
	BufferReader br(buffer, len);

	PlayerInfo_Protocol pkt;
	br >> pkt;
	
	if(pkt.IsValid() == false)
		return;

	vector<BuffData> buffDataes;
	buffDataes.resize(pkt.buffCount);
	for (int i = 0; i < pkt.buffCount; i++)
	{
		br >> buffDataes[i];
	}

	wstring name;
	name.resize(pkt.nameCount);
	for (int i = 0; i < pkt.nameCount; i++)
	{
		br >> name[i];
	}

	wcout.imbue(std::locale("kor"));
	wcout << name << endl;

	cout << "BuffCount : " << buffDataes.size() << endl;
	for (auto buff : buffDataes)
	{
		cout << "BuffId : " << buff.buffId << "  /   BuffRemain : " << buff.remainTime << endl;
	}
}

shared_ptr<SendBuffer> ClientPacketHandler::Make_C_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs)
{
	shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(1000);
	//PlayerInfo_Protocol p;
	//p.id = id;
	//p.hp = hp;
	//p.atk = atk;

	//BufferWriter bw(buf->Buffer(), buf->Capacity());

	//PacketHeader* header = bw.Reserve<PacketHeader>();
	//header->id = S_TEST;
	//header->size = (sizeof(p) + sizeof(PacketHeader));
	//bw << p;

	//buf->Ready(bw.WriteSize());

	return buf;
}
