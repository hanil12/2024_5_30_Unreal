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
bool IocpCore::Register(shared_ptr<IocpObject> iocpObj)
{
	// * �����Ȳ : iocpObj�� Session��.
	//                    or Listener

	// session�� Event���� �����ֵ���...
	// => iocpEvent���� ���� �� ������ ��������� �����ְڴ�.
	// ==> ���� refCount + 1
	//    	 														  key
	return ::CreateIoCompletionPort(iocpObj->GetHandle(), _iocpHandle, 0, 0);
}

bool IocpCore::Dispatch(uint32 timeOutMs)
{
	// CompletionPort�� �ִ� �Լ��� ����

	DWORD numOfBytes = 0;
	ULONG_PTR key = 0;
	shared_ptr<IocpObject> iocpObject = nullptr;
	IocpEvent* iocpEvent = nullptr;

	if(::GetQueuedCompletionStatus(
			_iocpHandle,
			&numOfBytes,
			&key, // key... 0
			reinterpret_cast<LPOVERLAPPED*>(&iocpEvent),
			timeOutMs
		))
	{
		iocpObject = iocpEvent->GetOwner();
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
			iocpObject = iocpEvent->GetOwner();
			iocpObject->DisPatch(iocpEvent, numOfBytes);
			break;
		}
	}

	return true;
}
