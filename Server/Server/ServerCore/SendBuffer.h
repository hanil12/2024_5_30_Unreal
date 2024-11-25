#pragma once
class SendBuffer : enable_shared_from_this<SendBuffer>
{
public:
	SendBuffer(int32 bufferSize);
	~SendBuffer();

	BYTE* Buffer() { return _buffer.data(); }
	int32 WriteSize() {return _writeSize; }
	int32 Capacity() { return static_cast<int32>(_buffer.size()); }

	void CopyData(void* data, int32 len);
	void CopyData_Packet(void* data, int32 len);
	void Ready(int32 writeSize) { _writeSize = writeSize; }

private:
	Vector<BYTE> _buffer; // [H][e][l][l][l][][][][][]
	int32 _writeSize = 0;
};

