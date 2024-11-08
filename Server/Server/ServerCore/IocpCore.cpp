#include "pch.h"
#include "IocpCore.h"
#include "Session.h"
#include "IocpEvent.h"

IocpCore::IocpCore()
{
	// Completion Port ����
	_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	ASSERT_CRASH(_iocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	::CloseHandle(_iocpHandle);
}

// Completion Port ���� ����:
// - ��Ƽ�����忡 �����ϴϱ�
//  => �����帶�� �����ִ� APCť�� ���� ó���ϴ°� �ƴ϶�, Completion Port�� ��Ƽ� ó���ϱ� ����.
bool IocpCore::Register(IocpObject* iocpObj)
{
	// * �����Ȳ : iocpObj�� Session��.

	return ::CreateIoCompletionPort(iocpObj->GetHandle(), _iocpHandle, reinterpret_cast<ULONG_PTR>(iocpObj), 0);
}

bool IocpCore::Dispatch(uint32 timeOutMs)
{
	// CompletionPort�� �ִ� �Լ��� ����

	DWORD numOfBytes = 0;
	IocpObject* iocpObject = nullptr;
	IocpEvent* iocpEvent = nullptr;

	if(::GetQueuedCompletionStatus(
			_iocpHandle,
			&numOfBytes,
			reinterpret_cast<PULONG_PTR>(&iocpObject),
			reinterpret_cast<LPOVERLAPPED*>(&iocpEvent),
			timeOutMs
		))
	{
		iocpObject->DisPatch(iocpEvent, numOfBytes);
	}
	else
	{
		int32 errCode = ::WSAGetLastError();
		switch (errCode)
		{
		case WAIT_TIMEOUT:
			return false;

		default:
			// TODO : �� �ȉ���� �ڵ�м�
			iocpObject->DisPatch(iocpEvent, numOfBytes);
			break;
		}
	}

	return true;
}
