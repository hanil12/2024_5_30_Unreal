#pragma once

// IocpObject를 상속받아서 Socket
class IocpObject : public enable_shared_from_this<IocpObject> 
{
public:
	virtual HANDLE GetHandle() abstract;
	virtual void DisPatch(class IocpEvent* iocpEvent, int32 numOfBytes = 0) abstract;
};

class IocpCore
{
public:
	IocpCore();
	~IocpCore();

	HANDLE GetHandle() { return _iocpHandle; }

	// Completion Port에 Socket 등록
	bool Register(shared_ptr<IocpObject> iocpObj);

	// 실행 준비 후 실행
	bool Dispatch(uint32 timeOutMs = INFINITE);

private:
	HANDLE _iocpHandle;
};

