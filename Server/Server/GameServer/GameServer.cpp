#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

#include "ThreadManager.h"
#include "Lock.h"
#include "RefCounting.h"


class Player : public RefCountable
{
public:
	void Attack()
	{
		if (_target != nullptr)
		{
			_target->_hp -= _atk;
		}
	}

	bool IsDead()
	{
		return _hp <= 0;
	}

public:
	Player* _target;

	int _hp;
	int _atk;
};

int main()
{
	CoreGlobal::Create();

	Player* p1 = new Player();
	p1->_hp = 10000;
	p1->_atk = 15;

	Player* p2 = new Player();
	p2->_hp = 20000;
	p2->_atk = 15;
	p2->_target = p1;
	p1->AddRef();

	TSharedPtr<Player> p3 = TSharedPtr<Player>(new Player());

	while (true)
	{
		if (p1 != nullptr)
		{
			p2->Attack();

			if (p1->IsDead())
			{
				p1->ReleaseRef(); // t1 t2
				break;
			}
		}
	}

	CoreGlobal::Delete();

	return 0;
}