#pragma once
class ThreadManager
{
public:
	ThreadManager();
	~ThreadManager();

	void Launch(function<void(void)> callback);
	void Join();

	static void InitTLS();
	static void DestroyTLS();

private:
	static Atomic<uint32> SThreadID;

	Mutex _lock;
	vector<thread> _threads;
};

