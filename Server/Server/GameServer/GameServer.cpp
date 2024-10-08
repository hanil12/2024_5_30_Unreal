#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

// Lock based Stack
// Lock based Queue
#include "LockBasedQueue.h"
#include "LockBasedStack.h"

#include "ThreadManager.h"
#include "Lock.h"

const int MAX_NUMBER = 100'0000;

// 17
bool IsPrime(int num)
{
	if(num == 0 || num == 1) return false;
	if(num == 2 || num == 3) return true;

	int findNum = (int)sqrtf(num);

	for (int i = 2; i <= findNum; i++)
	{
		if(num % i == 0)
			return false;
	}

	return true;
}

atomic<int> result = 0;

void PrimeRange(int start, int end)
{
	for (int i = start; i < end; i++)
	{
		if (IsPrime(i))
		{
			result.fetch_add(1);
		}
	}
}

int solution()
{
	vector<thread> threads;

	int coreCount = thread::hardware_concurrency();
	int temp = MAX_NUMBER / coreCount; // 20만

	for (int i = 0; i < coreCount; i++)
	{
		// 0 ~ MAX
		int start = temp * i;
		int end = temp * (i + 1);
		if(end > MAX_NUMBER || i == coreCount - 1) end = MAX_NUMBER;
		threads.push_back(thread(PrimeRange, start, end));
	}

	for(auto& thread : threads)
		thread.join();

	return result;
}

int main()
{
	CoreGlobal::Create();

	int64 start = ::GetTickCount64();

	int answer = 0;

	answer = solution();

	cout << answer << endl;

	int64 end = ::GetTickCount64();

	cout << "걸린 시간 : " << end - start << "ms" << endl;

	CoreGlobal::Delete();

	return 0;
}