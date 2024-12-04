#pragma once

// shared_ptr<SendBuffer> buf = make_shared<SendBuffer>(100);
// string temp = "client entered!!!";
// 
// BYTE* buffer = buf->Buffer();
// ((PacketHeader*)buffer)->id = 1; // id : 1 이면 Hello MSG
// ((PacketHeader*)buffer)->size = (sizeof(temp) + sizeof(PacketHeader));
// 
// // sendBuffer의 writePos에 접근 불가
// // ::memcpy(&buffer[4], temp.data(), sizeof(temp));
// buf->CopyData_Packet((BYTE*)temp.data(), sizeof(temp));

class BufferWriter
{
public:
	BufferWriter();
	BufferWriter(BYTE* buffer, uint32 size, uint32 pos = 0);
	~BufferWriter();

	BYTE* Buffer() { return _buffer; }
	uint32 Size() { return _size; }
	uint32 WriteSize() { return _pos; }
	uint32 FreeSize() { return _size - _pos; }

	template<typename T>
	bool Write(T* src) { return Write(src, sizeof(T)); }
	bool Write(void* src, uint32 len);

	template<typename T>
	T* Reserve();
	template<typename T>
	T* Reserve(uint16 count);

	// 우측값 참조를 Template이랑 같이 쓰면 보편참조(왼쪽값, 우측값)
	template<typename T>
	BufferWriter& operator<<(T&& src);

private:
	BYTE* _buffer = nullptr;
	uint32 _size = 0;
	uint32 _pos = 0;
};

template<typename T>
inline T* BufferWriter::Reserve()
{
	if(FreeSize() < sizeof(T))
		return nullptr;

	T* ret = reinterpret_cast<T*>(&_buffer[_pos]);
	_pos += sizeof(T);

	return ret;
}

template<typename T>
inline T* BufferWriter::Reserve(uint16 count)
{
	if (FreeSize() < sizeof(T) * count)
		return nullptr;

	T* ret = reinterpret_cast<T*>(&_buffer[_pos]);
	_pos += sizeof(T) * count;

	return ret;
}


// 보편참조
template<typename T>
inline BufferWriter& BufferWriter::operator<<(T&& src)
{
	using DataType = std::remove_reference_t<T>;
	*reinterpret_cast<DataType*>(&_buffer[_pos]) = std::forward<DataType>(src);
	_pos += sizeof(T);

	return *this;
}
