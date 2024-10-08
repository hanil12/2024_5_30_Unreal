#pragma once

// LOCK
#define USE_MANY_LOCKS(count)		Lock _locks[count];
#define USE_LOCK					USE_MANY_LOCKS(1)
#define READ_LOCK_IDX(idx)			ReadLockGuard readLockGuard_##idx(_locks[idx]);
#define READ_LOCK					READ_LOCK_IDX(0)
#define WRITE_LOCK_IDX(idx)			WriteLockGuard writeLockGuard_##idx(_locks[idx]);
#define WRITE_LOCK					WRITE_LOCK_IDX(0)

// CRASH
#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 0xDEADBEEF;					\
}											\

#define ASSERT_CRASH(expr)					\
{											\
	if(!(expr))								\
	{										\
		CRASH("ASSET_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}											\