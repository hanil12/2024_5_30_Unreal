#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

atomic<int32> flag;
int32 value;

void Producer()
{
	value = 10;

	flag.store(1, memory_order_release); // seq_cst ... 이 위로 모든 값들이 보장
}

void Consumer()
{
	while (flag.load(memory_order_acquire) != 1)
	{

	};

	cout << value << endl;
}

int main()
{
	flag.store(0);
	value = 0;

	thread t1(Producer);
	thread t2(Consumer);

	t1.join();
	t2.join();

	//Memory 정책
	// 1. seq_cst (sequential consistency) // 순서적 일관성 => 매우 엄격
	// - 코드 재배치X, 가시성 O
	// 
	// 2. acquire - release => 중도
	// 3. relaxed => 컴파일러 최적화 여지가 많다.


	return 0;
}