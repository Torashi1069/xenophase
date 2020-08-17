#pragma once
#include "Common/Packet.h"
#include "Memorial Dungeon/MemorialDungeon.h"
#include "Memorial Dungeon/MemorialDungeonReservedPlayer.h"
#include "shared/N2System/N2DualKeyMap.h"


namespace MemorialDungeon
{
void Send_PACKET_IZ_MEMORIALDUNGEON_SYNC2(const int in_HsvrID, const int in_ToZSID, const unsigned long in_hMemorialDungeonID, std::string in_MemorialDungeonName, const unsigned long in_hPartyID, std::string in_PartyName, const unsigned long in_ExistZSID, const int in_Factor, PACKET_IZ_MEMORIALDUNGEON_SYNC2::enumEVENT in_Event); // 322-360
void SendPacket_IZ_MEMORIALDUNGEON_MSG2(const int in_HsvrID, const unsigned long in_PartyID, PACKET_IZ_MEMORIALDUNGEON_MSG2::enumNotify in_Notify, std::string in_MemorialDungeonName); // 394-418
void Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO2(const int in_HsvrID, const unsigned long in_PartyID, const short in_PriorityOrderNum, std::string in_MemorialDungeonName); // 450-475
void Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(const int in_HsvrID, const unsigned long in_hParty, const short in_hPriorityNum); // 480-486
void Send_PACKET_IZ_MEMORIALDUNGEON_INFO2(const int in_HsvrID, const unsigned long in_hParty, std::string in_MemorialDungeonName, const unsigned long in_DestroyData, const unsigned long in_EnterTimeOutDate); // 510-536
void Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(const int in_HsvrID, const unsigned long in_hParty, PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE in_Type, const unsigned long in_EnterLimitDate); // 541-548
void Send_PACKET_IZ_MEMORIALDUNGEON_COMMAND(const int in_HsvrID, const unsigned long in_AID, const unsigned long in_GID, PACKET_IZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND in_Command); // 553-564
};


class CMemorialDungeonMgr
{
private:
	/* static  */ static CMemorialDungeonMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const CMemorialDungeonMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	/* this+ 5 */ bool m_bOpen;
	/* this+ 8 */ unsigned long m_Previous_Create_RequestTM;

	typedef N2DualKeyMap<unsigned long,unsigned int,CMemorialDungeon*> MEMORIALDUNGEON_CONTAINER2;
	typedef N2DualKeyMap<unsigned long,unsigned int,CMemorialDungeon*>::Iterator MEMORIALDUNGEON_CONTAINER_ITER2;
	/* this+12 */ N2DualKeyMap<unsigned long,unsigned int,CMemorialDungeon*> m_MemorialDungeonContainer2;

	typedef N2DualKeyMap<unsigned long,unsigned long,CMemorialDungeonReservedPlayer> SUBSCRIPTION_PLAYER_CONTAINER;
	typedef N2DualKeyMap<unsigned long,unsigned long,CMemorialDungeonReservedPlayer>::Iterator SUBSCRIPTION_PLAYER_CONTAINER_ITER;
	/* this+80 */ N2DualKeyMap<unsigned long,unsigned long,CMemorialDungeonReservedPlayer> m_SubscriptionPlayerContainer;

private:
	bool Create();
	void Destroy();

private:
	int CreateMemorialDungeonR2(CMemorialDungeonReservedPlayer& in_ReservedPlayer);
	void NotifySubscriptionPriority();
	void Command_SubscriptionCancel(const unsigned long in_hParty);
	void Command_Destroy(const unsigned long in_hPartyID);

public:
	const bool isOK() const;
	void Process();
	const int GetNum() const;
	void Subscription(const int in_HsvrID, const int in_RequestAID, const int in_RequestGID, const std::string in_Name, const std::string in_NickName, const int in_hParty, const std::string in_PartyName);
	void CreateResult(const unsigned long in_hParty, const bool in_bResult);
	void DisconnectZSVR(const int in_ZSID);
	void Command(const unsigned long in_hParty, const PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND in_Command);
	void NotifyAllMemorialDunbeon(const int in_ZSVR, const unsigned long& in_ZSVRRegisteredMgrFUCnt);
	void Visa(const unsigned long in_GID, const unsigned long in_AID, const unsigned long in_hPartyID);
	void OnNewbie(const int in_HsvrID, const unsigned long in_GID, const unsigned long in_AID, const unsigned long in_hParty, const std::string in_mapName);
	void OnEnter(const unsigned long in_PartyID, const unsigned long in_GID, const unsigned long in_AID, const std::string in_mapName);
	void OnLeave(const unsigned long in_GID, const unsigned long in_AID, const std::string in_mapName);
	bool isSubscription(const unsigned long in_hParty);
	bool isOpen() const;
	void Open();
	void Close();
	void PartyLeave(const unsigned long in_hPartyID, const unsigned long in_AID, const unsigned long in_GID);
	void PartyDestroy(const unsigned long in_hPartyID);

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CMemorialDungeonMgr* GetObj(); /// @custom

private:
	CMemorialDungeonMgr();
	virtual ~CMemorialDungeonMgr();
};
