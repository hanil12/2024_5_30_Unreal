#pragma once

// ±Ô¾à
enum PacketID
{
	NONE,
	S_TEST = 1,
};

struct PlayerInfo_Protocol
{
	int64 id;
	int32 hp;
	int16 atk;
};

class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, int32 len);

	static shared_ptr<SendBuffer> Make_S_TEST(int64 id, int32 hp, int16 atk);
};

