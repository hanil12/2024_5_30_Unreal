#include "pch.h"
#include "Player.h"

Player::Player(string name, int hp, int atk)
// : Creature()
: Creature(name, hp, atk)
, _exp(0)
{
}

Player::~Player()
{
}

void Player::MultiAttack(vector<Creature*> arr)
{
	for (int i = 0; i < arr.size(); i++)
	{
		this->Attack(arr[i]);
	}
}

void Player::GainExp(int exp)
{
	if (exp <= 0)
		return;

	_exp += exp;
}

void Player::LevelUp()
{
	if (_exp < _maxExp)
		return;

	_exp -= _maxExp;

	float maxHp = (float)_maxHp;
	float atk = (float)_atk;

	_maxHp += maxHp * (0.2f);
	_atk += atk * (0.2f);

	cout << "레벨업!!" << endl;
}
