#pragma once
class Player : public Creature
{
public:
	Player(string name, int hp, int atk);
	virtual ~Player();

	void MultiAttack(vector<Creature*> arr);
	void GainExp(int exp);
	void LevelUp();

protected:
	const int _maxExp = 100;
	int _exp;
};

