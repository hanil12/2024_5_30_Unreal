#include "pch.h"
#include "Allocator.h"

void* BaseAllocator::Alloc(size_t size)
{
	void* ptr = std::malloc(size);
	return ptr;
}

void BaseAllocator::Release(void* ptr)
{
	std::free(ptr);
}

void* StompAllocator::Alloc(int32 size)
{
	const int64 pageCount = (size + PAGE_SIZE - 1) / PAGE_SIZE;

	const int64 dataOffset = pageCount * PAGE_SIZE - size;

	void* address = ::VirtualAlloc(NULL, pageCount * PAGE_SIZE, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	return static_cast<void*>(static_cast<int8*>(address) + dataOffset);
}

void StompAllocator::Release(void* ptr)
{
	const int64 address = reinterpret_cast<int64>(ptr);
	const int64 baseAddress = address - (address % PAGE_SIZE);

	::VirtualFree(reinterpret_cast<void*>(baseAddress), 0, MEM_RELEASE);
}

void* PoolAllocator::Alloc(int32 size)
{
	return CoreGlobal::Instance()->GetMemory()->Allocate(size);
}

void PoolAllocator::Release(void* ptr)
{
	CoreGlobal::Instance()->GetMemory()->Release(ptr);
}
