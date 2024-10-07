#include "pch.h"

#include "AccountManager.h"
#include "UserManager.h"

// Lock based Stack
// Lock based Queue
#include "LockBasedQueue.h"
#include "LockBasedStack.h"

#include "ThreadManager.h"

LockBasedStack<int32> s;
LockBasedQueue<int32> q;

void Push()
{
	while (true)
	{
		int32 value = rand() % 100;
		q.Push(value);

		this_thread::sleep_for(100ms);
	}
}

void Pop()
{
	while (true)
	{
		int32 data = 0;
		
		//s.WaitPop(data);

		if (q.TryPop(data))
		{
			cout << data << endl;
		}
	}
}

int main()
{
	CoreGlobal::Create();

	// Read And Write Lock

	CoreGlobal::Instance()->TM()->Launch(&Push);
	CoreGlobal::Instance()->TM()->Launch(&Pop);
	CoreGlobal::Instance()->TM()->Launch(&Pop);

	CoreGlobal::Delete();

	return 0;
}