#include "pch.h"
#include "HopGoblin.h"

HopGoblin::HopGoblin()
: Monster("Hop", 1000, 30)
{
}

HopGoblin::~HopGoblin()
{
}

void HopGoblin::Attack_Hop()
{
	
}

void HopGoblin::TakeDamage(int amount, Creature* attacker)
{
	Creature::TakeDamage(amount, attacker);

	// 방금 날 때린 얘가 table에 이미 존재한다.
	auto iter = std::find_if(_aggroTable.begin(), _aggroTable.end(), [attacker](const AggroInfo info) ->bool
	{
		if(info.player == attacker)
			return true;
		return false;
	});

	// 이미 있다.
	if (iter != _aggroTable.end())
	{
		iter->damageAmount += amount;
	}
	// 처음 때렸다.
	else
	{
		AggroInfo info;
		info.player = attacker;
		info.damageAmount = amount;
		_aggroTable.push_back(info);
	}
}
