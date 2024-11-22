#pragma once

extern thread_local uint32 LThreadID;
extern thread_local std::stack<int32> LLockStack;
