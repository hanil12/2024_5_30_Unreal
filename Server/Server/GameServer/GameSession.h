#pragma once
#include "Session.h"

class GameSession : public Session
{
public:
	GameSession();
	~GameSession();

	virtual void OnConnected() override;
	virtual int32 OnRecv(BYTE* buffer, int32 len);
	virtual void OnSend(int32 len) override;
	virtual void DisConnected() override;

};

