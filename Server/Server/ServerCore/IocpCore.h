#pragma once

// IocpObject�� ��ӹ޾Ƽ� Socket
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

	// Completion Port�� Socket ���
	bool Register(shared_ptr<IocpObject> iocpObj);

	// ���� �غ� �� ����
	bool Dispatch(uint32 timeOutMs = INFINITE);

private:
	HANDLE _iocpHandle;
};

