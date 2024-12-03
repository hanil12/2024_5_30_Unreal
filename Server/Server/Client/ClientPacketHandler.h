#pragma once

/////////////////
// Packet List //
/////////////////
template<typename T, typename C>
class PacketList_Iterator
{
public:
	PacketList_Iterator(C& container, uint16 index) : _container(container), _index(index) {}

	bool			operator!=(const PacketList_Iterator& other) { return _index != other._index; }
	const T&		operator*() const { return _container[_index]; }
	T&				operator*() { return _container[_index]; }
	T*				operator->() { return &_container[_index]; }
	PacketList_Iterator& operator++() { _index++; return *this; }
	PacketList_Iterator operator++(int32) { PacketList_Iterator temp = *this; _index++; return temp; }

private:
	C&		_container;
	uint16	_index;
};

template<typename T>
class PacketList
{
public:
	PacketList() : _data(nullptr), _count(0) {}
	PacketList(T* data, uint16 count) : _data(data), _count(count) {}

	T& operator[](uint16 index)
	{
		ASSERT_CRASH(index < _count);
		return _data[index];
	}

	uint16 size() { return _count; }
	PacketList_Iterator<T, PacketList<T>> begin() { return PacketList_Iterator<T,PacketList<T>>(*this, 0); }
	PacketList_Iterator<T, PacketList<T>> end() { return PacketList_Iterator<T, PacketList<T>>(*this, _count); }

private:
	T* _data;
	uint16		 _count;
};

// 규약
enum PacketID
{
	NONE,
	S_TEST = 1,
};

enum BuffID
{
	BUFF_NONE,
	BUFF_LOVE = 1,
	BUFF_ANESTHESIA = 2
};

struct BuffData
{
	uint32 buffId;
	float remainTime;
};

#pragma pack(1)
struct PlayerInfo_Packet
{
	// 공용헤더
	PacketHeader header; // 4
	// id 고정(S_TEST)
	// size 고정(18)

	int64 id; // 8
	int32 hp; // 4
	int16 atk; // 2
	// 16 + 8 + 4 + 2 + 4 =>

	uint32 buffOffset; // 배열이 시작이는 메모리 offset
	uint32 buffCount;

	uint32 nameOffset;
	uint32 nameCount;

	bool IsValid()
	{
		uint32 size = 0;
		size += sizeof(PlayerInfo_Packet);
		if(header.size < size) // 그냥 이상함
			return false;

		size += buffCount * sizeof(BuffData);
		size += nameCount * sizeof(WCHAR);


		// 너가 기입한 크기가 실제 패킷크기랑 동일.
		if(size != header.size)
			return false;

		// 흘러넘치게 들어왔다? 뭔가 이상함
		if(nameOffset + nameCount * sizeof(WCHAR) > header.size)
			return false;

		return true;
	}

	using BuffList = PacketList<BuffData>;
	using Name = PacketList<WCHAR>;

	BuffList GetBuffList()
	{
		// 현재 메모리 주소에서 + buffOffset =>
		BYTE* data = reinterpret_cast<BYTE*>(this);
		data += buffOffset;

		return BuffList(reinterpret_cast<BuffData*>(data), buffCount);
	}
};
#pragma pack()

// [packetSize, packetId] [id hp atk] : 

class ClientPacketHandler
{
public:
	// Packet형태로 들어왔을 때 => Recv했을 떄 처리 방법
	static void HandlePacket(BYTE* buffer, int32 len);

	static void Handle_C_TEST(BYTE* buffer, int32 len);

	// Packet형태로 SendBuffer 만들기
	static shared_ptr<SendBuffer> Make_C_TEST(int64 id, int32 hp, int16 atk, vector<BuffData> buffs);
};

