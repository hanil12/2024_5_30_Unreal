#pragma once

class HopGoblin : public Monster
{
public:
	HopGoblin();
	~HopGoblin();

	// virtual void Attack(Creature* other) override;
	void Attack_Hop();
	virtual void TakeDamage(int amount, Creature* attacker) override;

	// 디자인 패턴 ... 컴포넌트 패턴
	AggroSystem* _aggroSystem;
	int _attackRange = 4;
};

