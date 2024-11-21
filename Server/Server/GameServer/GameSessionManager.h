#pragma once

class GameSession;

class GameSessionManager
{
public:
	void Add(shared_ptr<GameSession> session);
	void Remove(shared_ptr<GameSession> session);
	void BroadCast(shared_ptr<SendBuffer> sendBuffer);

private:
	USE_LOCK;

	Set<shared_ptr<GameSession>> _sessions;
};

extern GameSessionManager* G_GameSessionManager;
