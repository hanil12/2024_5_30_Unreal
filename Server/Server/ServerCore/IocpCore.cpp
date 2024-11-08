#include "pch.h"
#include "IocpCore.h"
#include "Session.h"
#include "IocpEvent.h"

IocpCore::IocpCore()
{
	// Completion Port 생성
	_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	ASSERT_CRASH(_iocpHandle != INVALID_HANDLE_VALUE);
}

IocpCore::~IocpCore()
{
	::CloseHandle(_iocpHandle);
}

// Completion Port 쓰던 이유:
// - 멀티쓰레드에 적합하니까
//  => 쓰레드마다 갖고있던 APC큐로 일을 처리하는게 아니라, Completion Port에 담아서 처리하기 때문.
bool IocpCore::Register(shared_ptr<IocpObject> iocpObj)
{
	// * 현재상황 : iocpObj가 Session임.
	//                    or Listener

	// session을 Event에서 물고있도록...
	// => iocpEvent에서 현재 내 세션을 멤버변수로 갖고있겠다.
	// ==> 세션 refCount + 1
	//    	 														  key
	return ::CreateIoCompletionPort(iocpObj->GetHandle(), _iocpHandle, 0, 0);
}

bool IocpCore::Dispatch(uint32 timeOutMs)
{
	// CompletionPort에 있는 함수들 실행

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
			// TODO : 왜 안됬는지 코드분석
			iocpObject = iocpEvent->GetOwner();
			iocpObject->DisPatch(iocpEvent, numOfBytes);
			break;
		}
	}

	return true;
}
