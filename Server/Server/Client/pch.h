#pragma once

#define WIN32_LEAN_AND_MEAN

#ifdef _DEBUG
#pragma comment(lib,"ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib,"Protobuf\\Debug\\TODO.lib")
#else
#pragma comment(lib,"ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib,"Protobuf\\Release\\TODO.lib")
#endif


#include "CorePch.h"
