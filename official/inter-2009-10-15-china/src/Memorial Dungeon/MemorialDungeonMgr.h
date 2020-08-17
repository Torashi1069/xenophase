#pragma once
#include "N2System/N2DualKeyMap.h"
#include "MemorialDungeon.h"
#include "MemorialDungeonReservedPlayer.h"
#include "Common/Packet.h"


class CMemorialDungeonMgr
{
	/* this+0x0  */ void* vtable;
	/* static    */ private: static hook_ptr<CMemorialDungeonMgr*> m_cpSelf;
	/* this+0x4  */ private: bool m_bOK;
	/* this+0x5  */ private: bool m_bOpen;
	/* this+0x8  */ private: unsigned long m_Previous_Create_RequestTM;
	/* this+0xC  */ private: N2DualKeyMap<unsigned long,unsigned int,CMemorialDungeon *> m_MemorialDungeonContainer2;
	/* this+0x28 */ private: N2DualKeyMap<unsigned long,unsigned long,CMemorialDungeonReservedPlayer> m_SubscriptionPlayerContainer;

	typedef N2DualKeyMap<unsigned long,unsigned int,CMemorialDungeon *>::Iterator MEMORIALDUNGEON_CONTAINER_ITER2;
	typedef N2DualKeyMap<unsigned long,unsigned long,CMemorialDungeonReservedPlayer>::Iterator SUBSCRIPTION_PLAYER_CONTAINER_ITER;

	//private: bool CMemorialDungeonMgr::Create();
	//private: void CMemorialDungeonMgr::Destroy();
	//private: int CMemorialDungeonMgr::CreateMemorialDungeonR2(class CMemorialDungeonReservedPlayer &);
	//private: void CMemorialDungeonMgr::NotifySubscriptionPriority();
	//private: void CMemorialDungeonMgr::Command_SubscriptionCancel(const unsigned long);
	//private: void CMemorialDungeonMgr::Command_Destroy(const unsigned long);
	//public: const bool CMemorialDungeonMgr::isOK();
	public: void CMemorialDungeonMgr::Process(void);
	public: const int CMemorialDungeonMgr::GetNum(void);
	public: void CMemorialDungeonMgr::Subscription(const int in_RequestAID, const int in_RequestGID, const mystd::string in_Name, const mystd::string in_NickName, const int in_hParty, const mystd::string in_PartyName);
	//public: void CMemorialDungeonMgr::CreateResult(const unsigned long, const bool);
	//public: void CMemorialDungeonMgr::DisconnectZSVR(const int);
	public: void CMemorialDungeonMgr::Command(const unsigned long in_hParty, const enum PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND in_Command);
	//public: void CMemorialDungeonMgr::NotifyAllMemorialDunbeon(const int, const unsigned long &);
	//public: void CMemorialDungeonMgr::Visa(const unsigned long, const unsigned long, const unsigned long);
	public: void CMemorialDungeonMgr::OnNewbie(const unsigned long in_GID, const unsigned long in_AID, const unsigned long in_hParty, const mystd::string in_mapName);
	public: void CMemorialDungeonMgr::OnEnter(const unsigned long in_PartyID, const unsigned long in_GID, const unsigned long in_AID, const mystd::string in_mapName);
	public: void CMemorialDungeonMgr::OnLeave(const unsigned long in_GID, const unsigned long in_AID, const mystd::string in_mapName);
	public: bool CMemorialDungeonMgr::isSubscription(const unsigned long in_hParty);
	//public: bool CMemorialDungeonMgr::isOpen();
	//public: void CMemorialDungeonMgr::Open();
	//public: void CMemorialDungeonMgr::Close();
	public: void CMemorialDungeonMgr::PartyLeave(const unsigned long in_hPartyID, const unsigned long in_AID, const unsigned long in_GID);
	public: void CMemorialDungeonMgr::PartyDestroy(const unsigned long in_hPartyID);
	public: static bool CMemorialDungeonMgr::CreateInstance(void);
	public: static void CMemorialDungeonMgr::DestroyInstance(void);
	public: static CMemorialDungeonMgr* CMemorialDungeonMgr::GetObj(void);
	//private: void CMemorialDungeonMgr::CMemorialDungeonMgr();
	//private: void CMemorialDungeonMgr::~CMemorialDungeonMgr();

private:
	static hook_method<void (CMemorialDungeonMgr::*)(void)> CMemorialDungeonMgr::_Process;
	static hook_method<const int (CMemorialDungeonMgr::*)(void)> CMemorialDungeonMgr::_GetNum;
	static hook_method<void (CMemorialDungeonMgr::*)(const int in_RequestAID, const int in_RequestGID, const mystd::string in_Name, const mystd::string in_NickName, const int in_hParty, const mystd::string in_PartyName)> CMemorialDungeonMgr::_Subscription;
	static hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_hParty, const enum PACKET_CZ_MEMORIALDUNGEON_COMMAND::enumCOMMAND in_Command)> CMemorialDungeonMgr::_Command;
	static hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_GID, const unsigned long in_AID, const unsigned long in_hParty, const mystd::string in_mapName)> CMemorialDungeonMgr::_OnNewbie;
	static hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_PartyID, const unsigned long in_GID, const unsigned long in_AID, const mystd::string in_mapName)> CMemorialDungeonMgr::_OnEnter;
	static hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_GID, const unsigned long in_AID, const mystd::string in_mapName)> CMemorialDungeonMgr::_OnLeave;
	static hook_method<bool (CMemorialDungeonMgr::*)(const unsigned long in_hParty)> CMemorialDungeonMgr::_isSubscription;
	static hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_hPartyID, const unsigned long in_AID, const unsigned long in_GID)> CMemorialDungeonMgr::_PartyLeave;
	static hook_method<void (CMemorialDungeonMgr::*)(const unsigned long in_hPartyID)> CMemorialDungeonMgr::_PartyDestroy;
	static hook_method<bool (__cdecl *)(void)> CMemorialDungeonMgr::_CreateInstance;
	static hook_method<void (__cdecl *)(void)> CMemorialDungeonMgr::_DestroyInstance;
};


namespace MemorialDungeon
{


void __cdecl SendPacket_IZ_MEMORIALDUNGEON_MSG(unsigned long in_PartyID, enum PACKET_IZ_MEMORIALDUNGEON_MSG::enumNotify in_Notify, mystd::string in_MemorialDungeonName);
void __cdecl Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO(unsigned long in_PartyID, short in_PriorityOrderNum, mystd::string in_MemorialDungeonName);
void __cdecl Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY(unsigned long in_hParty, short in_hPriorityNum);
void __cdecl Send_PACKET_IZ_MEMORIALDUNGEON_INFO(unsigned long in_hParty, mystd::string in_MemorialDungeonName, unsigned long in_DestroyData, unsigned long in_EnterTimeOutDate);
void __cdecl Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY(const unsigned int in_hParty, enum PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE in_Type, const unsigned int in_EnterLimitDate);


extern hook_method<void (__cdecl *)(unsigned long in_PartyID, enum PACKET_IZ_MEMORIALDUNGEON_MSG::enumNotify in_Notify, mystd::string in_MemorialDungeonName)> _SendPacket_IZ_MEMORIALDUNGEON_MSG;
extern hook_method<void (__cdecl *)(unsigned long in_PartyID, short in_PriorityOrderNum, mystd::string in_MemorialDungeonName)> _Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_INFO;
extern hook_method<void (__cdecl *)(unsigned long in_hParty, short in_hPriorityNum)> _Send_PACKET_IZ_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY;
extern hook_method<void (__cdecl *)(unsigned long in_hParty, mystd::string in_MemorialDungeonName, unsigned long in_DestroyData, unsigned long in_EnterTimeOutDate)> _Send_PACKET_IZ_MEMORIALDUNGEON_INFO;
extern hook_method<void (__cdecl *)(const unsigned int in_hParty, enum PACKET_ZC_MEMORIALDUNGEON_NOTIFY::enumTYPE in_Type, const unsigned int in_EnterLimitDate)> _Send_PACKET_IZ_MEMORIALDUNGEON_NOTIFY;


};//namespace MemorialDungeon
