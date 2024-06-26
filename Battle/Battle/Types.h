#pragma once

struct AggroInfo
{
	Creature* player;
	int damageAmount;

	bool operator<(const AggroInfo& info) const // 함수 뒤에 오는 const
	{
		if(this->damageAmount < info.damageAmount)
			return true;
		return false;
	}

	bool operator>(const AggroInfo& info) const
	{
		if (this->damageAmount > info.damageAmount)
			return true;
		return false;
	}
};