#include "pch.h"
#include "GameSessionManager.h"
#include "GameSession.h"

GameSessionManager* G_GameSessionManager = nullptr;

void GameSessionManager::Add(shared_ptr<GameSession> session)
{
	WRITE_LOCK;

	_sessions.insert(session);
	// TODO: 예외처리
}

void GameSessionManager::Remove(shared_ptr<GameSession> session)
{
	WRITE_LOCK;
	_sessions.erase(session);
}

void GameSessionManager::BroadCast(shared_ptr<SendBuffer> sendBuffer)
{
	WRITE_LOCK;
	for (auto session : _sessions)
	{
		session->Send(sendBuffer);
	}
}
