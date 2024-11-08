#include "pch.h"
#include "SocketUtility.h"

LPFN_CONNECTEX      SocketUtility::ConnectEx = nullptr;
LPFN_DISCONNECTEX   SocketUtility::DisConnectEx = nullptr;
LPFN_ACCEPTEX       SocketUtility::AcceptEx = nullptr;

void SocketUtility::Init()
{
    WSAData wsaData;
    ASSERT_CRASH(::WSAStartup(MAKEWORD(2, 2), OUT &wsaData) == 0);

    // 런타임에 주소 얻어오는 API
    SOCKET dummySocket = CreateSocket();
    BindWindowsFunction(dummySocket, WSAID_CONNECTEX, reinterpret_cast<LPVOID*>(&ConnectEx));
    BindWindowsFunction(dummySocket, WSAID_DISCONNECTEX, reinterpret_cast<LPVOID*>(&DisConnectEx));
    BindWindowsFunction(dummySocket, WSAID_ACCEPTEX, reinterpret_cast<LPVOID*>(&AcceptEx));

    Close(dummySocket);
}

void SocketUtility::Clear()
{
    ::WSACleanup();
}

SOCKET SocketUtility::CreateSocket()
{
    return ::WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
}

bool SocketUtility::BindWindowsFunction(SOCKET socket, GUID guid, LPVOID* fn)
{
    DWORD bytes = 0;
    return SOCKET_ERROR != ::WSAIoctl(socket, SIO_GET_EXTENSION_FUNCTION_POINTER, &guid, sizeof(guid), fn, sizeof(*fn), OUT & bytes, NULL, NULL);
}

bool SocketUtility::SetLinger(SOCKET socket, uint16 onoff, uint16 linger)
{
    LINGER option;
    option.l_onoff = onoff;
    option.l_linger = linger;

    return SetSockOpt(socket, SOL_SOCKET, SO_LINGER, option);
}

bool SocketUtility::SetReuseAddress(SOCKET socket, bool flag)
{
    return SetSockOpt(socket, SOL_SOCKET, SO_REUSEADDR, flag);
}

bool SocketUtility::SetRecvBufferSize(SOCKET socket, uint32 size)
{
    return SetSockOpt(socket, SOL_SOCKET, SO_RCVBUF, size);
}

bool SocketUtility::SetSendBufferSize(SOCKET socket, uint32 size)
{
    return SetSockOpt(socket, SOL_SOCKET, SO_SNDBUF, size);
}

bool SocketUtility::SetTCPNoDelay(SOCKET socket, bool flag)
{
    return SetSockOpt(socket, SOL_SOCKET, TCP_NODELAY, flag);
}

// ListenSocket의 옵션을 그대로 Client소켓에 적용
bool SocketUtility::SetUpdateAcceptSocket(SOCKET socket, SOCKET listenSocket)
{
    return SetSockOpt(socket, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT, listenSocket);
}

bool SocketUtility::Bind(SOCKET socket, NetAddress netAddr)
{
    return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const SOCKADDR*>(&netAddr.GetSockAddr()), sizeof(SOCKADDR_IN));
}

bool SocketUtility::BindAnyAddress(SOCKET socket, uint16 port)
{
    SOCKADDR_IN myAddress;
    myAddress.sin_family = AF_INET;
    myAddress.sin_addr.s_addr = ::htonl(INADDR_ANY);
    myAddress.sin_port = ::htons(port);

    return SOCKET_ERROR != ::bind(socket, reinterpret_cast<const SOCKADDR*>(&myAddress), sizeof(myAddress));
}

bool SocketUtility::Listen(SOCKET socket, int32 backLog)
{
    return SOCKET_ERROR != ::listen(socket, backLog);
}

void SocketUtility::Close(SOCKET& socket)
{
    if(socket != INVALID_SOCKET)
        ::closesocket(socket);
    socket = INVALID_SOCKET;
}
