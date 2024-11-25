#pragma once
#include "Session.h"

struct Player
{
	int64 id;
	int32 hp;
	int16 atk;
};

class GameSession : public PacketSession
{
public:
	GameSession();
	~GameSession();

	virtual void OnConnected() override;
	virtual void OnSend(int32 len) override;
	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) override;
	virtual void DisConnected() override;
};

