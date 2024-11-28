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

	case S_TEST:
		break;

	default:
		break;
	}
}

// Player Id : 1, hp : 100, atk : 5, buff[�����, 1.0], buff[����, 2.0]
// header[4] [ ID(1), hp(100), atk(5), 2 ,�����, 1.0, ����, 2.0]
shared_ptr<SendBuffer> ServerPacketHandler::Make_S_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs, wstring name)
{
	shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(1000);
	PlayerInfo_Protocol p;
	p.id = id;
	p.hp = hp;
	p.atk = atk;

	BufferWriter bw(buf->Buffer(), buf->Capacity());
	// Header Reserve, packet ���̵� ����
	PacketHeader* header = bw.Reserve<PacketHeader>();
	header->id = S_TEST;

	bw << p.id << p.hp << p.atk;

	// ���������� �ֱ�
	bw << (uint16)buffs.size();
	for (auto& buff : buffs)
	{
		bw << buff.buffId << buff.remainTime;
	}

	// FString... wchar;
	// WString ����
	bw << (uint16)name.size();
	bw.Write((void*)name.data(), name.size() * sizeof(WCHAR));

	// ��Ŷ �غ�Ϸ�, kg �缭 �����غ�
	header->size = bw.WriteSize();

	// �����غ�
	buf->Ready(bw.WriteSize());

	return buf;
}
