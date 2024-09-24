#include "pch.h"

atomic<int32> sum = 0; // all or nothing

void AddSum()
{
	for (int i = 0; i < 100000; i++)
	{
		sum.fetch_add(1);
	}
}

void SubSum()
{
	for (int i = 0; i < 100000; i++)
	{
		sum.fetch_sub(1);
	}
}

int main()
{
	vector<std::thread> threads;
	threads.resize(10);

	// 5개의 쓰레드가 AddSum 일감을 각각 갖는다.
	for (int i = 0; i < 5; i++)
	{
		threads[i] = std::thread(AddSum);
	}

	// 5개의 쓰레드가 SubSum 일감을 각각 갖는다.
	for (int i = 5; i < 10; i++)
	{
		threads[i] = std::thread(SubSum);
	}


	for (int i = 0; i < 10; i++)
	{
		threads[i].join();
	}

	cout << sum << endl;
}