#include "pch.h"
#include "CoreGlobal.h"

#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "Memory.h"

CoreGlobal* CoreGlobal::_instance = nullptr;

CoreGlobal::CoreGlobal()
{
	_threadManager = new ThreadManager();
	_deadLockProfiler = new DeadLockProfiler();
	_memory = new Memory();
}

CoreGlobal::~CoreGlobal()
{
	delete _deadLockProfiler;
	delete _threadManager;
	delete _memory;
}
