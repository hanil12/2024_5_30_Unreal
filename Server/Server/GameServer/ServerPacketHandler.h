#pragma once

#include "BufferWriter.h"
#include "Protocol.pb.h"

// 규약
enum PacketID
{
	NONE,
	S_PLAYER_INFO = 1,
	C_PLAYER_INFO = 2,
};

///////////////////
/// Packet_List ///
///////////////////

template<typename T, typename C>
class PacketList_Iterator
{
public:
	PacketList_Iterator(C& container, uint16 index) : _container(container), _index(index) {}

	bool			operator!=(const PacketList_Iterator& other) { return _index != other._index; }
	const T& operator*() const { return _container[_index]; }
	T& operator*() { return _container[_index]; }
	T* operator->() { return &_container[_index]; }
	PacketList_Iterator& operator++() { _index++; return *this; }
	PacketList_Iterator operator++(int32) { PacketList_Iterator temp = *this; _index++; return temp; }

private:
	C& _container;
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
	PacketList_Iterator<T, PacketList<T>> begin() { return PacketList_Iterator<T, PacketList<T>>(*this, 0); }
	PacketList_Iterator<T, PacketList<T>> end() { return PacketList_Iterator<T, PacketList<T>>(*this, _count); }

private:
	T* _data;
	uint16		 _count;
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

	//vector<int32> victims;
	uint32 victimOffset;
	uint32 victimCount;
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

	uint32 buffOffset; // 배열이 시작이는 메모리 offset
	uint32 buffCount;

	uint32 wCharOffset;
	uint32 wCharCount;

	bool IsValid()
	{
		uint32 size = 0;
		size += sizeof(PlayerInfo_Packet);
		size += buffCount * sizeof(BuffData);
		size += wCharCount * sizeof(WCHAR);

		// 너가 기입한 크기가 실제 패킷크기랑 동일.
		if (size != header.size)
			return false;

		// 흘러넘치게 들어왔다? 뭔가 이상함
		if (wCharOffset + wCharCount * sizeof(WCHAR) > header.size)
			return false;

		return true;
	}
};
#pragma pack()

class ServerPacketHandler
{
public:
	static void HandlePacket(BYTE* buffer, int32 len);

	static void Handle_S_TEST(BYTE* buffer, int32 len);

	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_PlayerInfo& pkt);
};

template<typename T>
shared_ptr<SendBuffer> _MakeSendBuffer(T& pkt, uint16 pktId)
{
	// 공용header 만들기
	const uint16 dataSize = static_cast<uint16>(pkt.ByteSizeLong()); // ByteSizeLong
	const uint16 packetSize = dataSize + sizeof(PacketHeader);

	shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(packetSize);
	PacketHeader* header = reinterpret_cast<PacketHeader*>(sendBuffer->Buffer());
	header->id = pktId;
	header->size = packetSize;

	ASSERT_CRASH(pkt.SerializeToArray(&(header[1]), dataSize));

	sendBuffer->Ready(packetSize);
	return sendBuffer;
}

/* Packet Writer

class PKT_S_TEST_WRITE
{
public:
	PKT_S_TEST_WRITE(int64 id, int32 hp, int16 atk)
	{
		_sendBuffer = make_shared<SendBuffer>(1000);
		_bw = BufferWriter(_sendBuffer->Buffer(), _sendBuffer->Capacity());

		_pkt = _bw.Reserve<PlayerInfo_Packet>();
		_pkt->header.id = S_PLAYER_INFO;
		_pkt->header.size = 0; // TODO
		_pkt->id = id;
		_pkt->hp = hp;
		_pkt->atk = atk;
		_pkt->buffCount = 0;
		_pkt->buffOffset = 0;
		_pkt->wCharCount = 0;
		_pkt->wCharOffset = 0;
	}

	PacketList<BuffData> ReserveBuffList(uint16 buffCount)
	{
		BuffData* buffListBegin = _bw.Reserve<BuffData>(buffCount);
		_pkt->buffOffset = (uint64)buffListBegin - (uint64)_pkt;
		_pkt->buffCount = buffCount;
		return PacketList<BuffData>(buffListBegin, buffCount);
	}

	PacketList<int32> ReserveVictimList(BuffData* buff, uint16 victimCount)
	{
		int32* victimBegin = _bw.Reserve<int32>(victimCount);
		buff->victimOffset = (uint64)victimBegin - (uint64)_pkt;
		buff->victimCount = victimCount;
		return PacketList<int32>(victimBegin, victimCount);
	}

	PacketList<WCHAR> Reserve_WCHARList(uint16 wcharCount)
	{
		WCHAR* strBegin = _bw.Reserve<WCHAR>(wcharCount);
		_pkt->wCharOffset = (uint64)strBegin - (uint64)_pkt;
		_pkt->wCharCount = wcharCount;
		return PacketList<WCHAR>(strBegin, wcharCount);
	}

	shared_ptr<SendBuffer> Ready()
	{
		_pkt->header.size = _bw.WriteSize();
		_sendBuffer->Ready(_bw.WriteSize());

		return _sendBuffer;
	}

private:
	PlayerInfo_Packet* _pkt = nullptr;
	shared_ptr<SendBuffer> _sendBuffer;
	BufferWriter _bw;
};
*/