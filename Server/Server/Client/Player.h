#pragma once

class Player
{
public:
	string name;
	uint64 id;
	uint32 hp;
	uint32 atk;

	shared_ptr<class ServerSession> _session;
};