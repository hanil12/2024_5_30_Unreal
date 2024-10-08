#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

// Lock based Stack
// Lock based Queue
#include "LockBasedQueue.h"
#include "LockBasedStack.h"

#include "ThreadManager.h"
#include "Lock.h"

class TestJob
{
	USE_LOCK;

public:
	int TestRead()
	{
		READ_LOCK;

		if(q.empty() == false)
			return q.front();
	}

	void TestPush()
	{
		WRITE_LOCK;

		q.push(rand() % 100);
	}

	void TestPop()
	{
		WRITE_LOCK;

		if(q.empty() == false)
			q.pop();
	}

private:
	queue<int> q;
};

TestJob GJob;
void ThreadRead()
{
	while (true)
	{
		int num = GJob.TestRead();
		cout << num << endl;
	}
}

void ThreadWrite()
{
	while (true)
	{
		GJob.TestPush();
		this_thread::sleep_for(100ms);
		GJob.TestPop();
	}
}

int main()
{
	CoreGlobal::Create();

	for(int i=0; i < 2; i++)
		CoreGlobal::Instance()->TM()->Launch(ThreadWrite);

	for (int i = 0; i < 5; i++)
		CoreGlobal::Instance()->TM()->Launch(ThreadRead);

	CoreGlobal::Delete();

	return 0;
}