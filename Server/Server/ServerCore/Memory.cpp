#include "pch.h"
#include "Memory.h"

Memory::Memory()
{
	int32 size = 0;
	int32 tableIndex = 0;

	// 32개의 32바이트짜리 메모리풀 만들기
	for (size = 32; size <= 1024; size += 32)
	{
		MemoryPool* pool = new MemoryPool(size);
		_pools.push_back(pool);

		while (tableIndex <= size)
		{
			_poolTable[tableIndex] = pool;
			tableIndex++;
		}
	}

	// 8개의 128바이트짜리 메모리풀 만들기
	for (size = 1024; size <= 2048; size += 128)
	{
		if(size == 1024) continue;

		MemoryPool* pool = new MemoryPool(size);
		_pools.push_back(pool);

		while (tableIndex <= size)
		{
			_poolTable[tableIndex] = pool;
			tableIndex++;
		}
	}

	// 8개의 256바이트짜리 메모리풀 만들기
	for (size = 2048; size <= 4096; size += 256)
	{
		if (size == 2048) continue;

		MemoryPool* pool = new MemoryPool(size);
		_pools.push_back(pool);

		while (tableIndex <= size)
		{
			_poolTable[tableIndex] = pool;
			tableIndex++;
		}
	}
}

Memory::~Memory()
{
	for(MemoryPool* pool : _pools)
		delete pool;

	_pools.clear();
}

void* Memory::Allocate(int32 size)
{
	MemoryHeader* head = nullptr;
	const int32 allocSize = size + sizeof(MemoryHeader);

	if (allocSize > MAX_ALLOC_SIZE)
	{
		// 메모리 풀링 최대 크기 벗어나면 일반 할당
		head = reinterpret_cast<MemoryHeader*>(std::malloc(allocSize));
	}
	else
	{
		// 메모리풀에서 꺼내오기
		head = _poolTable[allocSize]->Pop();
	}

	return MemoryHeader::AttachHeader(head, allocSize);
}

void Memory::Release(void* ptr)
{
	MemoryHeader* head = MemoryHeader::DetachHeader(ptr);

	const int32 allocSize = head->_allocSize;

	if (allocSize > MAX_ALLOC_SIZE)
	{
		// 메모리 풀링 최대 크기 벗어나면 일반 해제
		std::free(head);
	}
	else
	{
		// 메모리풀에 반납
		_poolTable[allocSize]->Push(head);
		// 32바이트짜리 메모리 풀을 찾고 싶다.
		// _poolTable[32]
		// 1000바이트짜리 메모리 풀 찾기
		// _poolTable[1000]
	}
}
