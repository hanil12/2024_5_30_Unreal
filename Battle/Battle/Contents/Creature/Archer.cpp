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
	// 30프로 확률
	// 0~100까지의 난수를 뽑고
	// 100으로 나눔
	this->Creature::PreAttack(other); // 멤버함수를 호출하기 위한 조건... 객체가 항상 있어야한다.
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
