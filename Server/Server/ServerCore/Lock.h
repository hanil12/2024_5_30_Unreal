#pragma once

// [WWWWWWWW] [WWWWWWWW] : Write Lock을 걸은 ThreadID를 기입
// [RRRRRRRR] [RRRRRRRR] : Read Lock을 걸었을 때 몇번이나 걸었는지 횟수
// [WWWWWWWW] [WWWWWWWW] [RRRRRRRR] [RRRRRRRR] => 32비트 플래그
// W : Write Flag (상호배타적, Thread ID)
// R : Read Flag (Shared Lock Count)

class Lock
{
	enum : uint32
	{
		ACQUIRE_TIMEOUT_TICK = 10000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'0000,
		READ_COUNT_MASK = 0x0000'FFFF,
		EMPTY_FLAG = 0x0000'0000
	};

public:
	void WriteLock();
	void WriteUnlock();
	void ReadLock();
	void ReadUnlock();

private:
	Atomic<uint32> _lockFlag = EMPTY_FLAG;
	uint16 _writeCount = 0;
};

