#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

// Lock 구현
// 1. Spin Lock(Busy Waiting)
// 2. Sleep 기반 Lock
// 3. Event 기반 Lock

// Spin Lock

class SpinLock
{
public:
	void lock()
	{
		// 둘이 경합이 동시에 일어났다.

		// check하고 setting하는 작업이 원자적으로 처리되어야한다.
		// => Compare And Swap(CAS)

		bool expected = false; // flag의 예상값은 false
		bool desired = true; // flag가 true였으면 좋겠다.

		// compare_exchange_strong 의사코드
		//if (flag == expected) 
		//{
		//	expected = flag;
		//	flag = desired;
		//	return true;
		//}
		//else // flag가 desired와 같다.
		//{
		//	expected = flag;
		//	return false;
		//}

		while (flag.compare_exchange_strong(expected, desired) == false)
		{
			expected = false;

			// Sleep Lock
			this_thread::sleep_for(std::chrono::seconds(5));
		}
	}

	void unlock()
	{
		flag =  false;
	}

private:
	atomic<bool> flag = false;
};


int32 sum = 0;
SpinLock myLock;

void Add()
{
	for (int32 i = 0; i < 100'0000; i++)
	{
		// lock...flag -> false
		std::lock_guard<SpinLock> lg(myLock); 
		// lock...flag -> true

		sum++;
	}
}

void Sub()
{
	for (int32 i = 0; i < 100'0000; i++)
	{
		// lock...flag -> true
		std::lock_guard<SpinLock> lg(myLock);
		sum--;
	}
}

int main()
{
	std::thread t1(Add);
	std::thread t2(Sub);

	t1.join();
	t2.join();

	cout << sum << endl;

	return 0;
}