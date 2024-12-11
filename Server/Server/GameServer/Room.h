#pragma once

class Player;

class Room
{
public:
	void Enter(shared_ptr<Player> player);
	void Leave(shared_ptr<Player> player);
	void BroadCast(shared_ptr<SendBuffer> sendBuff);

private:
	USE_LOCK;

	HashTable<uint64,weak_ptr<Player>> _playersTable;
};
