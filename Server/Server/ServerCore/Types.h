#pragma once
#include <queue>
#include <stack>
#include <thread>
#include <mutex>
#include <atomic>

using int8 =  __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 =  unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

template<typename T>
using Atomic = std::atomic<T>;
using Mutex = std::mutex;
using ConditionV = std::condition_variable;
using UniqueLock = std::unique_lock<Mutex>;
using LockGuard = std::lock_guard<Mutex>;

#define sizeof16(val)		static_cast<int16>(sizeof(val))
#define sizeof32(val)		static_cast<int32>(sizeof(val))
#define sizeof64(val)		static_cast<int64>(sizeof(val))
#define len16(arr)			static_cast<int16>(sizeof(arr)/sizeof(arr[0]))
#define len32(arr)			static_cast<int32>(sizeof(arr)/sizeof(arr[0]))