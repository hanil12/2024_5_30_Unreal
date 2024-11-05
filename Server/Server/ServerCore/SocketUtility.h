#pragma once
#include "NetAddress.h"

// 정적 멤버함수 모음집
class SocketUtility
{
public:
	// TODO : 비동기 AccpetEx, 등등..
	static LPFN_CONNECTEX	ConnectEx;
	static LPFN_DISCONNECTEX DisConnectEx;
	static LPFN_ACCEPTEX AcceptEx;

public:
	static void Init();
	static void Clear();

	static SOCKET CreateSocket();
	static bool BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn);

	// Sck Option
	static bool SetLinger(SOCKET socket, uint16 onoff, uint16 linger);
	static bool SetReuseAddress(SOCKET socket, bool flag);
	static bool SetRecvBufferSize(SOCKET socket, uint32 size);
	static bool SetSendBufferSize(SOCKET socket, uint32 size);
	static bool SetTCPNoDelay(SOCKET socket, bool flag);
	static bool SetUpdateAcceptSocket(SOCKET socket, SOCKET listenSocket);

	static bool Bind(SOCKET socket, NetAddress netAddr);
	static bool BindAnyAddress(SOCKET socket, uint16 port);
	static bool Listen(SOCKET socket, int32 backLog = SOMAXCONN);
	static void Close(SOCKET& socket);
};

template<typename T>
static inline bool SetSockOpt(SOCKET socket, int32 level, int32 optName, T optValue)
{
	return SOCKET_ERROR != ::setsockopt(socket, level, optName, reinterpret_cast<char*>(&optValue), sizeof(T));
}
