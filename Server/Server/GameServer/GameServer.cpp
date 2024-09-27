#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

// Lock 구현
// 1. Spin Lock(Busy Waiting)
// 2. Sleep 기반 Lock
// 3. Event 기반 Lock

queue<int32> q;
mutex m;
HANDLE handle;

void Producer()
{
	while (true)
	{
		{
			unique_lock<std::mutex> lock(m);
			q.push(100);
		}

		::SetEvent(handle);

		this_thread::sleep_for(10000ms);
	}
}

void Consumer()
{
	while (true)
	{
		::WaitForSingleObject(handle, INFINITE);

		unique_lock<std::mutex> lock(m);

		if (q.empty() == false)
		{
			int32 data = q.front();
			q.pop();
			cout << data << endl;
		}
	}
}

int main()
{
						// 보안속성, 매뉴얼 리셋 관련, 초기상태
						//			Manual : 수동의
	handle = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();

	::CloseHandle(handle);

	return 0;
}