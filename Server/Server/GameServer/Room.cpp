#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "GameSession.h"

void Room::Enter(shared_ptr<Player> player)
{
	WRITE_LOCK; // LOCK... �ڷᱸ���� ������ �� ���� Lock�� ��´�.
	_playersTable[player->playerId] = player;
}

void Room::Leave(shared_ptr<Player> player)
{
	WRITE_LOCK;
	_playersTable.erase(player->playerId);
}

void Room::BroadCast(shared_ptr<SendBuffer> sendBuff)
{
	WRITE_LOCK;

	for (auto& p : _playersTable)
	{
		p.second.lock()->_ownerSession.lock()->Send(sendBuff);
	}
}
