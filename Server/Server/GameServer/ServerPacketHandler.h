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

struct PlayerInfo_Protocol
{
	int64 id; // 8
	int32 hp; // 4
	int16 atk; // 2
	int16 padding = -1;

	vector<BuffData> buffs;
	wstring name;
	//string str_s;
	//wstring str_w;

	// �ٷ�Ʃ�� => ��ǻ�Ͱ� �˾Ƶ��� �� �ִ� ���� 0,1�ۿ� ����.
	// �����̸� => �̱�(�޸� ��)
	// => ���ڴ� ��� ����
	// �ƽ�Ű�ڵ�
	// �����ڵ� (�ƽ�Ű�ڵ� ����) 
	// UTF-8
	// UTF-16
};

class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, int32 len);

	static shared_ptr<SendBuffer> Make_S_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs, wstring name);
};

