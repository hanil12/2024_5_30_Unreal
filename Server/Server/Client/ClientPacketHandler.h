#pragma once

// 규약
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
};

class ClientPacketHandler
{
public:
	// Packet형태로 들어왔을 때 => Recv했을 떄 처리 방법
	static void HandlePacket(BYTE* buffer, int32 len);

	static void Handle_C_TEST(BYTE* buffer, int32 len);

	// Packet형태로 SendBuffer 만들기
	static shared_ptr<SendBuffer> Make_C_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs);
};

