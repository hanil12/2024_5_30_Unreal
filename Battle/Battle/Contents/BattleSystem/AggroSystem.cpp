#include "pch.h"
#include "AggroSystem.h"

void AggroSystem::Push(Creature* attacker, int damage)
{
	// 방금 날 때린 얘가 table에 이미 존재한다.
	auto iter = std::find_if(_aggroTable.begin(), _aggroTable.end(), [attacker](const AggroInfo info) ->bool
		{
			if (info.player == attacker)
				return true;
			return false;
		});

	// 이미 있다.
	if (iter != _aggroTable.end())
	{
		iter->damageAmount += damage;
	}
	// 처음 때렸다.
	else
	{
		AggroInfo info;
		info.player = attacker;
		info.damageAmount = damage;
		_aggroTable.push_back(info);
	}
}

vector<Creature*> AggroSystem::Pop(int count)
{
	vector<Creature*> result;

	// 죽은 player _aggroTable에서 삭제
	auto removeIter = std::remove_if(_aggroTable.begin(), _aggroTable.end(), [](const AggroInfo& info)-> bool 
	{
		if(info.player->IsDead())
			return true;
		return false;
	});

	_aggroTable.erase(removeIter, _aggroTable.end());

	// 정렬... 람다
	std::sort(_aggroTable.begin(), _aggroTable.end(), [](const AggroInfo& infoA, const AggroInfo& infoB)-> bool
	{
			if(infoA.damageAmount > infoB.damageAmount)
				return true;
			return false;
	});
	//std::sort(_aggroTable.begin(), _aggroTable.end(), greater<AggroInfo>());

	if(_aggroTable.size() < count)
		count = _aggroTable.size();

	// 현재 _aggroTable.size() >= count
	for (int i = 0; i < count; i++)
	{
		Creature* attacker = _aggroTable[i].player;
		result.push_back(attacker);
	}

	return result;
}
