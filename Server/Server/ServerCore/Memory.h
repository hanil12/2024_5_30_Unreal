#pragma once
#include "Allocator.h"

class MemoryPool;

class Memory
{
	enum			//  32                             8                     8
	{				 // 0 ~ 1024 ... 32단위 / 1024 ~ 2048 ... 128단위 / 2048 ~ 4096 ... 256 단위
		POOL_COUNT = (1024 /32) + (1024 / 128) + (2048 / 256),
		MAX_ALLOC_SIZE = 4096
	};

public:
	Memory();
	~Memory();

	void* Allocate(int32 size);
	void  Release(void* ptr);

private:
	vector<MemoryPool*> _pools; // 48개의 메모리 풀

	// 메모리 풀을 빠르게 탐색하기 위한 Table
	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];
};

template<typename T, typename... Args>
T* xnew(Args... args)
{
	T* memory = static_cast<T*>(xalloc(sizeof(T)));

	new(memory)T(std::forward<Args>(args)...);

	return memory;
}

template<typename T>
void xdelete(T* obj)
{
	obj->~T();
	xrelease(obj);
}

template<typename T, typename... Args>
shared_ptr<T> MakeShared(Args&&... args)
{
	return shared_ptr<T>{ xnew<T>(forward<Args>(args)...), xdelete<T> };
}