#include "pch.h"
#include "Lock.h"

// Lock 정책
// 1. Read는 상호베타적일 필요없이 공유Count만 올린다(ReadCount)
// 2. Write는 무조건 상호베타적이여야한다.
// => Write중에는 다른 쓰레드에서 Read할 수 없다.
// => Read중에 다른 쓰레드에서 Write를 시도할 수 없다.
//    * 내 Thread에서 Write하고 Read는 가능하다.
//    * 하지만 내 Thread에서 Read하고 Write는 불가능하다.

// [WWWWWWWW] [WWWWWWWW] [RRRRRRRR] [RRRRRRRR]
// &
// [11111111] [11111111] [00000000] [00000000]

void Lock::WriteLock()
{
	// [WWWWWWWW] [WWWWWWWW] [RRRRRRRR] [RRRRRRRR]
	// &
	// [11111111] [11111111] [00000000] [00000000]
	// [WWWWWWWW] [WWWWWWWW] [00000000] [00000000]

	const uint32 lockThreadID = (_lockFlag & WRITE_THREAD_MASK) >> 16;

	// 같은 Thread가 WriteLock을 재귀로 잡았을 때 통과
	if (LThreadID == lockThreadID)
	{
		_writeCount++;
		return;
	}

	const int64 beginTick = ::GetTickCount64();

	// 한번도 Lock이 안걸려있었거나, 다른 쓰레드에서 이미 Lock을 잡아놨을 때
	// Spin Lock : CAS (Compare And Swap)
	// 한번도 Lock 안걸려있었으면(expected) writeCount++ 하고 통과
	// 그러나 그게 아니면(다른 얘가 lock) spin
	const int32 desired = (LThreadID << 16) & WRITE_THREAD_MASK;
	while (true)
	{
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			uint32 expected = EMPTY_FLAG;
			if (_lockFlag.compare_exchange_strong(OUT expected, desired))
			{
				_writeCount++;
				return;
			}
		}

		if(::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
			CRASH("Lock TimeOut");

		this_thread::yield();
	}

}

void Lock::WriteUnlock()
{
	// 자기 자신이 ReadLock을 건 다음에 WriteLock이 걸리면 안되는데 걸렸을 때 예외처리
	if((_lockFlag.load() & READ_COUNT_MASK) != 0)
		CRASH("INVALID_UNLOCK_ORDER")

	const int32 lockCount = --_writeCount;
	if(lockCount == 0)
		_lockFlag.store(EMPTY_FLAG);
}

void Lock::ReadLock()
{
	// writelock건 얘가 자기 자신이면 통과
	const uint32 lockThreadID = (_lockFlag & WRITE_THREAD_MASK) >> 16;

	// 같은 Thread가 WriteLock을 재귀로 잡았을 때 통과
	if (LThreadID == lockThreadID)
	{
		_writeCount++;
		return;
	}

	// writelock을 건 얘가 따로 있으면.. 불통과
	// readlock만 걸려있거나 아무도 lock을 잡지 않으면 통과
	const int64 beginTick = ::GetTickCount64();
	while (true)
	{
		for (uint64 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			// ThreadID를 0으로 밀어버리고 ReadCount만 체크
			uint32 expected = (_lockFlag.load() & READ_COUNT_MASK);
			if(_lockFlag.compare_exchange_strong(expected, expected + 1))
				return;
		}

		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
			CRASH("Lock TimeOut");

		this_thread::yield();
	}
}

void Lock::ReadUnlock()
{
	// READ을 동시에 두번 풀어주면 안되는데 그렇게 되면 CRASH
	if((_lockFlag.fetch_sub(1) & READ_COUNT_MASK) == 0)
		CRASH("MULTIPLE_UNLOCK");
}
