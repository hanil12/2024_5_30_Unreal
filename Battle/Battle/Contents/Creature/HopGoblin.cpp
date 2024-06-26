#include "pch.h"
#include "HopGoblin.h"

HopGoblin::HopGoblin()
: Monster("Hop", 50000, 30)
{
	_aggroSystem = new AggroSystem();
}

HopGoblin::~HopGoblin()
{
	delete _aggroSystem;
}

void HopGoblin::Attack_Hop()
{
	vector<Creature*> players_for_attack = _aggroSystem->Pop(_attackRange);

	for (auto player : players_for_attack)
	{
		player->TakeDamage(_atk);
	}
}

void HopGoblin::TakeDamage(int amount, Creature* attacker)
{
	Creature::TakeDamage(amount, attacker);

	_aggroSystem->Push(attacker, amount);
}
