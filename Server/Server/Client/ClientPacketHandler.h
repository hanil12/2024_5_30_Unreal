#pragma once

// �Ծ�
enum PacketID
{
	NONE,
	S_TEST = 1,
};

enum BuffID
{
	BUFF_NONE,
	BUFF_LOVE = 1,
	BUFF_ANESTHESIA = 2
};

struct BuffData
{
	uint32 buffId;
	float remainTime;
};

#pragma pack(1)
struct PlayerInfo_Protocol
{
	// �������
	PacketHeader header; // 4
	// id ����(S_TEST)
	// size ����(18)

	int64 id; // 8
	int32 hp; // 4
	int16 atk; // 2
	// 16 + 8 + 4 + 2 + 4 =>

	uint32 buffOffset; // �迭�� �����̴� �޸� offset
	uint32 buffCount;

	uint32 nameOffset;
	uint32 nameCount;

	bool IsValid()
	{
		uint32 size = 0;
		size += sizeof(PlayerInfo_Protocol);
		size += buffCount * sizeof(BuffData);
		size += nameCount * sizeof(WCHAR);

		// �ʰ� ������ ũ�Ⱑ ���� ��Ŷũ��� ����.
		if(size != header.size)
			return false;

		// �귯��ġ�� ���Դ�? ���� �̻���
		if(nameOffset + nameCount * sizeof(WCHAR) > header.size)
			return false;

		return true;
	}
};
#pragma pack()

// [packetSize, packetId] [id hp atk] : 

class ClientPacketHandler
{
public:
	// Packet���·� ������ �� => Recv���� �� ó�� ���
	static void HandlePacket(BYTE* buffer, int32 len);

	static void Handle_C_TEST(BYTE* buffer, int32 len);

	// Packet���·� SendBuffer �����
	static shared_ptr<SendBuffer> Make_C_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs);
};

