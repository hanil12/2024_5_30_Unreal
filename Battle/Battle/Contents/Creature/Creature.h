#pragma once
class Creature
{
public:
	Creature(string name, int hp, int atk);
	virtual ~Creature();

	void Init();

	void PrintInfo();
	void PreAttack(Creature* other);
	void PreAttack(shared_ptr<Creature> other);
	virtual void Attack(Creature* other) abstract;
	virtual void Attack(shared_ptr<Creature> other) abstract;

	virtual void TakeDamage(int amount, Creature* attacker = nullptr);

	bool IsDead();

	bool isActive = false;

protected:
	string _name;
	int _curHp;
	int _maxHp;
	int _atk;
};

