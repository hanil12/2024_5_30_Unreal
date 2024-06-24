#pragma once
class Monster : public Creature
{
public:
	Monster(string name, int hp, int atk);
	virtual ~Monster();

	virtual void Attack(Creature* other) override;
};

