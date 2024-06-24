#pragma once

class HopGoblin : public Monster
{
public:
	HopGoblin();
	~HopGoblin();

	// virtual void Attack(Creature* other) override;
	void Attack_Hop();
	virtual void TakeDamage(int amount, Creature* attacker) override;

	// Table
	vector<class AggroInfo> _aggroTable;
};

