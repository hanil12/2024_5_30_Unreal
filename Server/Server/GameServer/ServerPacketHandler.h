#pragma once

#include "BufferWriter.h"
#include "Protocol.pb.h"

// 
using PacketHandlerFunc = std::function<bool(shared_ptr<PacketSession>&, BYTE*, int32)>; 
extern PacketHandlerFunc G_PacketHandler[UINT16_MAX]; // 32767 + 32768

// 규약
enum PacketID
{
	NONE,
	S_PLAYER_INFO = 1,
	S_ENTEROOM = 2,
	S_CHATMSG = 3,

	C_PLAYER_INFO = 101,
	C_CHATMSG = 102
};

// 우리가 만들 핸들러함수
// Custom Handlders
bool Handler_INVALID(shared_ptr<PacketSession>& session, BYTE* buffer, int32 len);

bool Handle_C_PlayerInfo(shared_ptr<PacketSession>& session, Protocol::C_PlayerInfo& pkt);
bool Handle_C_ChatMsg(shared_ptr<PacketSession>& session, Protocol::C_ChatMsg& pkt);

class Server_PacketHandler
{
public:
	static void Init()
	{
		for (int i = 0; i < UINT16_MAX; i++)
		{
			G_PacketHandler[i] = Handler_INVALID;
		}

		G_PacketHandler[C_PLAYER_INFO] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_PlayerInfo>(Handle_C_PlayerInfo, session, buffer, len); };
		G_PacketHandler[C_CHATMSG] = [](shared_ptr<PacketSession>& session, BYTE* buffer, int32 len) { return HandlePacket<Protocol::C_ChatMsg>(Handle_C_ChatMsg, session, buffer, len); };
	}

	static bool HandlePacket(shared_ptr<PacketSession> session, BYTE* buffer, int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		return G_PacketHandler[header->id](session, buffer, len);
	}

	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_PlayerInfo& pkt) { return _MakeSendBuffer(pkt, S_PLAYER_INFO); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_EnterRoom& pkt) { return _MakeSendBuffer(pkt, S_ENTEROOM); }
	static shared_ptr<SendBuffer> MakeSendBuffer(Protocol::S_ChatMsg& pkt) { return _MakeSendBuffer(pkt, S_CHATMSG); }

private:
	template<typename T>
	static shared_ptr<SendBuffer> _MakeSendBuffer(T& pkt, uint16 pktId)
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

	// process : Deletegate로 Packet 처리
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, shared_ptr<PacketSession>& session, BYTE* buffer, int32 len)
	{
		PacketType pkt;
		if(pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;


		return func(session, pkt);
	}
};



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