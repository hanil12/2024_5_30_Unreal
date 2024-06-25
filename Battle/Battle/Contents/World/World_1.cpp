#include "pch.h"
#include "World_1.h"

World_1::World_1()
: _player1(nullptr)
, _player2(nullptr)
{
	CreatePlayer();

	// player2 생성
	_player2 = new Knight("player2", 100, 5);
}

World_1::~World_1()
{
	delete _player1;
	delete _player2;
}

void World_1::CreatePlayer()
{
	int input = 0;
	cin >> input;

	string name = "Hanil";

	switch (input)
	{
	case 1:
		_player1 = new Knight(name, 5000, 30);
		break;
	case 2:
		_player1 = new Archer(name , 1000, 60);
		break;
	default:
		break;
	}
}

void World_1::Battle()
{
	_player1->Attack(_player2);
	_player2->Attack(_player1);
}

bool World_1::End()
{
	return _player1->IsDead() || _player2->IsDead();
}
