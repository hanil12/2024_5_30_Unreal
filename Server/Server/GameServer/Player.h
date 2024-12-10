#pragma once
class Player
{
public:
	
	uint64 playerId;
	string name;
	uint32 hp;
	uint32 atk;

	weak_ptr<class GameSession> _ownerSession;
};

