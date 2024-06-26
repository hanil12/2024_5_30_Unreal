#include "pch.h"
#include "Archer.h"

Archer::Archer(string name, int hp, int atk)
: Player(name, hp, atk)
{
}

Archer::~Archer()
{
}

void Archer::Attack(Creature* other)
{
	this->Creature::PreAttack(other);
	int num = rand() % 100;
	float ratio = num / (float)100;
	if (ratio < 0.3f)
	{
		other->TakeDamage(_atk * 3.0f, this);
	}
	else
	{
		other->TakeDamage(_atk, this);
	}
}

void Archer::Attack(shared_ptr<Creature> other)
{
	this->Creature::PreAttack(other);
	int num = rand() % 100;
	float ratio = num / (float)100;
	if (ratio < 0.3f)
	{
		other->TakeDamage(_atk * 3.0f, this);
	}
	else
	{
		other->TakeDamage(_atk, this);
	}
}
