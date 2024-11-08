#include "pch.h"
#include "CoreGlobal.h"

#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "Memory.h"
#include "IocpCore.h"
#include "SocketUtility.h"

CoreGlobal* CoreGlobal::_instance = nullptr;

CoreGlobal::CoreGlobal()
{
	_threadManager = new ThreadManager();
	_deadLockProfiler = new DeadLockProfiler();
	_memory = new Memory();

	SocketUtility::Init();
	_iocpCore = new IocpCore();
}

CoreGlobal::~CoreGlobal()
{
	delete _deadLockProfiler;
	delete _threadManager;
	delete _memory;

	delete _iocpCore;
	SocketUtility::Clear();
}
