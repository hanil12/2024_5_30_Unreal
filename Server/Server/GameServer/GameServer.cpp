#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

// 메모리 모델
// 1. 여러 쓰레드가 동일한 메모리(공용 변수)에 동시에 접근, 쓰기(write)할 때 생기는 문제들 파악
// 2. 이 때 경합조건(Race Condition)
// 3. Race Condition을 어떻게 막을 것이냐
// ... Undefined Behavior(정의되지 않은 행동)
// => atomic
// => Lock(mutex) ,,, Mutual Exclusion(상호 베타)

// 우리의 메모리 정책
// 1. atomic을 이용해서 코드 재배치를 막고, 가시성을 지킨다.

// atomic 연산에 한해, 모든 쓰레드가 동일 객체에 대해서 '동일한 수정 순서'를 관찰.
// => 가시성

// atomic... 메모리 정책
// => 코드재배치

int main()
{
	atomic<bool> flag = false;
	
	// atomic 변수 flag에 값을 저장 => 쓰기
	flag.store(true, memory_order::memory_order_seq_cst);

	// atomic 변수를 읽어오는 것 => 읽기
	bool val = flag.load(memory_order::memory_order_seq_cst);

	// prev에다 flag의 바꾸기 전 값을 넣고 , flag를 수정
	{
		bool prev = flag.exchange(true);
	}

	// 조건부 수정 : condition variable
	// => cv라는 객체가 내 예상이 맞으면 바꿔주고, 아니면 말고
	{
		bool expected = false; // 내 예상은 이게 false일 것이다.
		bool desired = true; // 내 예상이 맞으면 desired로 바꿔줘.

		flag.compare_exchange_strong(expected, desired);
		// flag.compare_exchange_weak(expected, desired); => while(true)
	}

	return 0;
}