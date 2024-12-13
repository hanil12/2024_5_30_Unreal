#pragma once

class Player;

class Room
{
public:
	void Enter(shared_ptr<Player> player);
	void Leave(shared_ptr<Player> player);
	void BroadCast(shared_ptr<SendBuffer> sendBuff);
	string GetPlayerName(uint64 id);

private:
	USE_LOCK;

	HashTable<uint64,shared_ptr<Player>> _playersTable;
};
