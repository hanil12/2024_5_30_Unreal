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

// 선수지식
// - 허상포인터로 인한 메모리 오염
// - 가상메모리와 물리적메모리
// - 사실 new delete는 바로바로 일을 해준 것이 아니였다. => delete가 실제로 바로 삭제하는게 아니였다.
//   => 허상포인터에 데이터를 수정할 수 있었다.

// Stomp Allocator의 의미
// 1. DEBUG 환경에서 메모리 오염 방지
// 2. DEBUG 환경에서 다운캐스팅 후 메모리 오버플로우 방지

int main()
{
	CoreGlobal::Create();

	#pragma region 가상메모리, 운영체제 이론
	Player* p = new Player();

	// 허상포인터(Dangling Ptr)
	p->_atk = 10;
	p->_hp = 20;

	delete p;

	p->_hp = 50; // 메모리 오염

	// 가상메모리
	p = nullptr;
	p = new Player(); // 0x0000019B32DC2310

	// ---- 다른 프로그램 ------
	//int64* temp = (int64*)(0x0000019B32DC2310);
	//*temp = 500;
	// ------------------------

	// 물리 메모리 
	
	// 운영체제 페이징
	// 운영체제가 메모리를 할당하고 관리할 때는 페이지 단위로 관리를 한다.
	// 각 프로세스한테 가상메모리를 주고 유저레벨에서 서로 간섭할 수 없게 만든다.
	// => 물리적 메모리는 운영체제가 담당한다.
	#pragma endregion

	SYSTEM_INFO s_info;
	::GetSystemInfo(&s_info);

	s_info.dwPageSize; // 페이지 한 개당 사이즈 4KB
	s_info.dwAllocationGranularity; // 메모리를 할당할 때 이 숫자의 배수로 할당이 된다. 2

	// window API
	int* temp = (int*)::VirtualAlloc(nullptr, 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	*temp = 100;

	::VirtualFree(temp, 0, MEM_RELEASE);

	// *temp = 200; // 런타임 에러 바로 남.
	// => new / delete 바로 VirtualAlloc, VirtualFree를 바로 해주지 않는다.

	// test
	Knight* k = reinterpret_cast<Knight*>(new Player());
	// k->_stamina = 100; => 메모리 오버플로우
	// std:: new/ delete Allocator 경우 상속 구조에서 메모리 오버플로우를 허용하지 않음

	delete k;

	k->_hp = 100;

	// 4096 bytes
	// [[p2]100                      ]
	// [                         [p2]]
	Knight* p2 = reinterpret_cast<Knight*>(xnew<Player>());
	p2->_stamina = 100; // 메모리 오버플로우 막음

	xdelete(p2);

	// vector<Player*, StompAllocator> v;

	CoreGlobal::Delete();

	return 0;
}