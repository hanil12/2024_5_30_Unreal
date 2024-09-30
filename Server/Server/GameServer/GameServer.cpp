#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

// Lock 구현
// 1. Spin Lock(Busy Waiting)
// 2. Sleep 기반 Lock
// 3. Event 기반 Lock ...=> CV(conditon variable)
//
// 3... Linux에서도,,?
// => cv(condition_variable)
// ... 조건을 걸고 조건이 참일 때만 락을 걸어잠그고 실행
// => 멀티쓰레드 환경에서 Sleep을 시키지 않으면 올바르게 동작하지 않을 수도 있다.
// ... 동시성이 생길 때 Produce를 더 할 수도 있다.

// 디자인 패턴
// Produce And Consumer 패턴... Queue

queue<int32> q;
mutex m;
//HANDLE handle;
condition_variable cv;

void Producer()
{
	while (true)
	{
		// P_A_C P...
		// 1. Lock을 잡고 (lock(m))
		// 2. 공유 변수 값을 수정 (q.push(100))
		// 3. Lock을 풀고
		// 4. 조건변수를 통해 다른 쓰레드에게 통지

		{
			unique_lock<std::mutex> lock(m); // 1

			q.push(100); // 2
		} // 3

		// wait 중인 Thread가 있으면 딱 1개를 깨운다.
		cv.notify_one(); // 4
	}
}

void Consumer()
{
	while (true)
	{
		// P_A_C : Consumer
		// 1. Lock을 잡고
		// 2. 조건확인
		// - 만족했다 => 이어서 코드진행
		// - 불만족 => 'Lock을 풀어주고' 대기상태

		unique_lock<std::mutex> lock(m); // 1

		cv.wait(lock, []()->bool { return q.empty() == false; }); // 2

		{
			int32 data = q.front();
			q.pop();
			//cout << data << endl;
			cout << q.size() << endl;
		}
	}
}

int main()
{
						// 보안속성, 매뉴얼 리셋 관련, 초기상태
						//			Manual : 수동의
	//handle = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();

	//::CloseHandle(handle);

	return 0;
}