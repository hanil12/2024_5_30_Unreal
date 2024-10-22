#include "pch.h"
#include "Memory.h"

Memory::Memory()
{
	int32 size = 0;
	int32 tableIndex = 0;

	// 32���� 32����Ʈ¥�� �޸�Ǯ �����
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

	// 8���� 128����Ʈ¥�� �޸�Ǯ �����
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

	// 8���� 256����Ʈ¥�� �޸�Ǯ �����
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
		// �޸� Ǯ�� �ִ� ũ�� ����� �Ϲ� �Ҵ�
		head = reinterpret_cast<MemoryHeader*>(std::malloc(allocSize));
	}
	else
	{
		// �޸�Ǯ���� ��������
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
		// �޸� Ǯ�� �ִ� ũ�� ����� �Ϲ� ����
		std::free(head);
	}
	else
	{
		// �޸�Ǯ�� �ݳ�
		_poolTable[allocSize]->Push(head);
		// 32����Ʈ¥�� �޸� Ǯ�� ã�� �ʹ�.
		// _poolTable[32]
		// 1000����Ʈ¥�� �޸� Ǯ ã��
		// _poolTable[1000]
	}
}
