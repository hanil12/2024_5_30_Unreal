#pragma once
#include "IocpCore.h"
#include "NetAddress.h"
#include "Service.h"
#include "IocpEvent.h"

class AcceptEvent;
// ���� :
// Ŭ���̾�Ʈ�� ���� �õ�(�Ĵ翡 ����) �� ��
// Accept�Ѵ�. (����̼� ���̾��?)
class Listener : public IocpObject
{
public:
	Listener() = default;
	~Listener();

	bool StartAccept(shared_ptr<class ServerService> service);
	void CloseSocket();

	virtual HANDLE GetHandle() override;
	virtual void DisPatch(IocpEvent* iocpEvent, int32 numOfBytes) override;

	void RegisterAccept(AcceptEvent* acceptEvent);
	void ProcessAccept(AcceptEvent* acceptEvent);

protected:
	SOCKET _socket = INVALID_SOCKET;
	Vector<AcceptEvent*> _acceptEvents;
	shared_ptr<class ServerService> _service;
};
