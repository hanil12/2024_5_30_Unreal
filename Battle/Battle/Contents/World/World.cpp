#include "pch.h"	
#include "World.h"

World::World()
: _player(nullptr)
, _computer(nullptr)
{
	Input();

	_monsters.reserve(10);

	for (int i = 0; i < 10; i++)
	{
		Monster* monster = new Monster("Goblin", 50, 10);
		_monsters.push_back(monster);
	}

	Init();
}

World::~World()
{
	if(_player != nullptr)
		delete _player;
	if(_computer != nullptr)
		delete _computer;

	for (int i = 0; i < _monsters.size(); i++)
	{
		delete _monsters[i];
	}
}

void World::Init()
{
	_player->Init();
	_computer->Init();

	for (int i = 0; i < _monsters.size(); i++)
	{
		_monsters[i]->Init();
	}
}

bool World::End()
{
	if (_player->IsDead() || _computer->IsDead()|| MonstersCheck())
		return true;

	return false;
}

bool World::MonstersCheck()
{
	for (int i = 0; i < _monsters.size(); i++)
	{
		if (!_monsters[i]->IsDead())
			return false;
	}

	return true;
}

void World::SelectPlayer(int num, string name, Creature** creature)
{
	switch (num)
	{
	case PlayerType::NONE:
	{
		cout << "다시 입력해주세요." << endl;
		break;
	}

	case PlayerType::KNIGHT:
	{
		*creature = new Knight(name, 500, 15);
	}
	break;
	case PlayerType::ARCHER:
	{
		*creature = new Archer(name, 300, 35);
	}
	break;

	default:
	{
		cout << "다시 입력해주세요." << endl;
		break;
	}
	break;
	}
}

void World::Input()
{
	int playerNum = 0;
	int cumNum = 0;
	string name;
	
	cout << "이름을 입력해주세요." << endl;
	cin >> name;
	cout << "1 기사, 2 궁수" << endl;
	cin >> playerNum;
	cumNum = rand() % 2 + 1; // 1 ~ 2
	SelectPlayer(playerNum, name, &_player);
	SelectPlayer(cumNum, "computer", &_computer);
}

void World::Battle1()
{
	while (true)
	{
		_player->Attack(_computer);
		_computer->Attack(_player);

		if (End())
		{
			Init();
			break;
		}
	}
}

void World::Battle2()
{
	while (true)
	{
		Player* p = dynamic_cast<Player*>(_player);
		if (p == nullptr)
			continue;

		p->MultiAttack(_monsters);

		for (int i = 0; i < _monsters.size(); i++)
		{
			_monsters[i]->Attack(p);
		}

		if (End())
		{
			Init();
			break;
		}
	}
}
