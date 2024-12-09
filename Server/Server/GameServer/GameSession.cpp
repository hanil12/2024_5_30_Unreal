#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ServerPacketHandler.h"
#include "Protocol.pb.h"

GameSession::GameSession()
{
	
}

GameSession::~GameSession()
{
}

void GameSession::OnConnected()
{
	// 입장하면 입장해있던 모든 클라이언트들에게 입장했다고 방송고지

	//////////////////
	/// Packet 제작 //
	//////////////////
	/* Cumtom Packet Seriallize
	PKT_S_TEST_WRITE pkt_writer(1234,10,5);
	auto buffList = pkt_writer.ReserveBuffList(2);
	auto wCharList = pkt_writer.Reserve_WCHARList(6);

	// buff
	{
		buffList[0] = { 241203, 6 };
		auto victimList0 = pkt_writer.ReserveVictimList(&buffList[0], 2);
		{
			victimList0[0] = 100;
			victimList0[1] = 101;
		}

		buffList[1] = { 240528, 23 };
		auto victimList1 = pkt_writer.ReserveVictimList(&buffList[1], 4);
		{
			victimList1[0] = 614;
			victimList1[1] = 622;
			victimList1[2] = 1109;
			victimList1[3] = 1211;
		}
	}

	// name
	{
		wCharList[0] = L'H'; 
		wCharList[1] = L'a'; 
		wCharList[2] = L'n'; 
		wCharList[3] = L'i'; 
		wCharList[4] = L'l'; 
		wCharList[5] = L'\0'; 
	}
	*/

	Protocol::PlayerInfo pkt;

	pkt.set_id(1234);
	pkt.set_hp(10);
	pkt.set_atk(5);

	{
		auto buff = pkt.add_buffs();
		// { 241203, 6 }
		buff->set_buffid(241203);
		buff->set_remaintime(6);

		buff->add_victims(100);
		buff->add_victims(101);
	}
	{
		auto buff = pkt.add_buffs();
		// 240528, 23
		buff->set_buffid(240528);
		buff->set_remaintime(23);

		buff->add_victims(614);
		buff->add_victims(622);
		buff->add_victims(1109);
		buff->add_victims(1211);
	}

	//G_GameSessionManager->BroadCast(pkt_writer.Ready());

	G_GameSessionManager->Add(static_pointer_cast<GameSession>(shared_from_this()));
}


void GameSession::OnSend(int32 len)
{
	cout << "Send 성공 : " << len << endl;
}

int32 GameSession::OnRecvPacket(BYTE* buffer, int32 len)
{
	PacketHeader header = *((PacketHeader*)buffer);

	cout << "Paket ID : " << header.id << "  Size : " << header.size << endl;

	ServerPacketHandler::HandlePacket(buffer, len);

	return len;
}

void GameSession::DisConnected()
{
	G_GameSessionManager->Remove(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "DisConnected" << endl;
}