#pragma once

#include "Types.h"
#include <algorithm>
#include <future>

#include <Windows.h>
#include <iostream>

using namespace std;

// Network
#include <winsock2.h>
#include <MSWSock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "SocketUtility.h"

// CORE
#include "CoreTLS.h"
#include "CoreGlobal.h"
#include "CoreMacro.h"
#include "MyContainer.h"

// Multi Thread
#include "ThreadManager.h"
#include "Lock.h"

// Memomry
#include "Memory.h"
#include "MemoryPool.h"

// MyNetWork
#include "SendBuffer.h"
#include "Session.h"
