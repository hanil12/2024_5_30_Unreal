#include "pch.h"
#include "ClientPacketHandler.h"
#include "BufferReader.h"
#include "BufferWriter.h"

void ClientPacketHandler::HandlePacket(BYTE* buffer, int32 len)
{
	// TODO : Recv했을 때 패킷 파싱하고 분석
	BufferReader br(buffer, len);
	int32 t = sizeof(PlayerInfo_Packet);
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

	PlayerInfo_Packet* pkt = reinterpret_cast<PlayerInfo_Packet*>(buffer);
	
	if(pkt->IsValid() == false)
		return;

	// buffer + pkt.buffOffset
	PacketList<BuffData> buffDataes = pkt->GetBuffList();
	//for (int i = 0; i < pkt->buffCount; i++)
	//{
	//	br >> buffDataes[i];
	//}

	cout << "BuffCount : " << buffDataes.Size() << endl;
	for (int i = 0; i < buffDataes.Size(); i++)
	{
		cout << "BuffId : " << buffDataes[i].buffId << "  /   BuffRemain : " << buffDataes[i].remainTime << endl;
	}

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
