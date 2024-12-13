#pragma once
#include "ClientPacketHandler.h"
#include "Protocol.pb.h"
#include "Player.h"

extern Player G_Player;

class ServerSession : public PacketSession
{
public:
	ServerSession()
	{
	}

	~ServerSession()
	{
		cout << "Session DisConnected" << endl;
	}

	virtual void OnConnected() override
	{
		cout << "Server에 접속 성공!!!" << endl;

		uint64 id;
		uint32 hp;
		uint32 atk;
		string name;

		cout << "Name 입력" << endl;
		cin >> name;

		cout << "ID , HP , ATK 입력" << endl;
		cin >> id >> hp >> atk;

		// Player Setting
		G_Player.id = id;
		G_Player.hp = hp;
		G_Player.atk = atk;
		G_Player.name = name;

		Protocol::C_PlayerInfo pkt;
		pkt.set_id(id);
		pkt.set_hp(hp);
		pkt.set_atk(atk);
		pkt.set_name(name);

		Send(ClientPacketHandler::MakeSendBuffer(pkt));
	}

	virtual int32 OnRecvPacket(BYTE* buffer, int32 len) override
	{
		ClientPacketHandler::HandlePacket(static_pointer_cast<PacketSession>(shared_from_this()),buffer, len);

		return len;
	}

	virtual void OnSend(int32 len) override
	{
		cout << "Send 성공 : " << len << endl;
	}

	virtual void DisConnected() override
	{
		cout << "DisConnected" << endl;
	}
};