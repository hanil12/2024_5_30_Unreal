#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

#include "ThreadManager.h"
#include "Lock.h"
#include "RefCounting.h"


using PlayerRef = shared_ptr<class Player>;

class Player
{
public:
	Player() : _hp(0), _atk(0) 
	{
		cout << "생성자 호출" << endl;
	}

	Player(int hp, int atk)
	: _hp(hp), _atk(atk)
	{
		cout << "타입변환 생성자 호출" << endl;
	}

	~Player()
	{
		cout << "소멸자 호출" << endl;
	}

	bool IsDead()
	{
		return _hp <= 0;
	}

public:

	int _hp;
	int _atk;
};

class Knight : public Player
{
public:
	int _stamina = 0;
};


int main()
{
	CoreGlobal::Create();



	CoreGlobal::Delete();

	return 0;
}