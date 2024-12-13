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
		p.second->_ownerSession.lock()->Send(sendBuff);
	}
}

string Room::GetPlayerName(uint64 id)
{
	if(_playersTable.size() == 0) return "";

	if(_playersTable.count(id) == 0) { CRASH("CANNOT FIND ID") }

	return _playersTable[id]->name;
}
