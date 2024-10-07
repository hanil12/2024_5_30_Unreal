#include "pch.h"
#include "CoreGlobal.h"

#include "ThreadManager.h"

CoreGlobal* CoreGlobal::_instance = nullptr;

CoreGlobal::CoreGlobal()
{
	_threadManager = new ThreadManager();
}

CoreGlobal::~CoreGlobal()
{
	delete _threadManager;
}
