#include "pch.h"

vector<int> v;
// mutual exclusion : 상호배제
// -> lock
std::mutex m; // 자물쇠 역할

// RAII
template<typename T>
class LockGuard
{
public:
	LockGuard(T* mutex) : _mutex(mutex) { _mutex->lock(); }
	~LockGuard() { _mutex->unlock(); }

private:
	T* _mutex;
};

void Push(int count)
{
	LockGuard<std::mutex> lockguard(&m);

	for (int i = 0; i < count; i++)
	{
		// 이중 락
		v.push_back(1);
	}

	return;
}

int main()
{
	v.reserve(100000);

	vector<std::thread> threads;
	threads.resize(10);

	for (int i = 0; i < 10; i++)
	{
		threads[i] = std::thread(Push, 1000);
	}

	for (int i = 0; i < 10; i++)
	{
		threads[i].join();
	}

	cout << v.size() << endl;
}