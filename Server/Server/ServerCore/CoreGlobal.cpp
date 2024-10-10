#include "pch.h"
#include "CoreGlobal.h"

#include "ThreadManager.h"
#include "DeadLockProfiler.h"

CoreGlobal* CoreGlobal::_instance = nullptr;

CoreGlobal::CoreGlobal()
{
	_threadManager = new ThreadManager();
	_deadLockProfiler = new DeadLockProfiler();
}

CoreGlobal::~CoreGlobal()
{
	delete _deadLockProfiler;
	delete _threadManager;
}
