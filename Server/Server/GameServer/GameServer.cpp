#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

// CPU PipeLine
int32 x;
int32 y;
int32 result1;
int32 result2;

volatile bool ready;

// 1. 실제 메모리에 정말 x,y가 1이라고 되어있을까?
// 코어 마다 cache가 있다.
// 멀티쓰레드환경에서만 발생할 수 있는 문제
// => 캐쉬를 통해서 메모리에 접근해서 값을 넣기 전에 동시에 실행됬다면?

// ---> 가시성 문제

// 2. CPU 파이프라인
// - Fetch			: 읽기
// - Decode			: 해석
// - Excute			: 실행
// - Memory Access	: 메모리 접근
// 일감을 병렬로 처리하기 위해서 큰 작업부터 실행한다.

// ---> 코드 재배치

void Thread_1()
{
	while(ready)
	;

	y = 1;
	result1 = x; // x의 값을 가져와서 대입하는게 좀 더 시간이 걸리는 작업
}

void Thread_2()
{
	while(ready)
	;

	x = 1;
	result2 = y;
}

int main()
{
	int32 count = 0;

	while (true)
	{
		ready = true;
		count++;

		x = y = result1 = result2 = 0;

		thread t1(Thread_1);
		thread t2(Thread_2);

		ready = false;

		t1.join();
		t2.join();

		if(result1 == 0 && result2 == 0)
			break;
	}

	cout << count << "번만에 탈출 성공!!!" << endl;

	return 0;
}