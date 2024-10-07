#include "pch.h"
#include "ThreadManager.h"

Atomic<uint32> ThreadManager::SThreadID = 1;

ThreadManager::ThreadManager()
{
	InitTLS();
}

ThreadManager::~ThreadManager()
{
	Join();
}

void ThreadManager::Launch(function<void(void)> callback)
{
	LockGuard guard(_lock);

	_threads.push_back(thread([=]() -> void
		{
			InitTLS();
			callback();
			DestroyTLS();
		}
	));
}

void ThreadManager::Join()
{
	for(auto& thread : _threads)
	{
		if(thread.joinable())
			thread.join();
	}

	_threads.clear();
}

void ThreadManager::InitTLS()
{
	LThreadID = SThreadID.fetch_add(1);
}

void ThreadManager::DestroyTLS()
{

}
