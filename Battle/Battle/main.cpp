#include "pch.h"

// 과제
// World_1으로 프로그램 돌리기.
// Raw Pointer -> smart Pointer로 교체하는 작업
// 이 때 멤버함수의 RawPointer 매개변수들은 유지하되, 함수 오버로딩해서

int main()
{
	shared_ptr<World_1> world = make_shared<World_1>();

	while (true)
	{
		world->Battle();

		if(world->End())
			break;
	}

	return 0;
}