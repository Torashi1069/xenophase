#pragma once
#include "MapRes.h"
#include "std/map"
#include "std/string"
#include "std/vector"
class CNPC;


struct FLAG_INFO
{
	/* this+ 0 */ int GDID;
	/* this+ 4 */ char agitName[24];
	/* this+28 */ mystd::vector<CNPC*> vt;
};


class CAgitMapRes : public CMapRes
{
public:
	struct vtable_t // const CAgitMapRes::`vftable'
	{
		const bool (CMapRes::* isInstantMap)(void) const;
		void* (CAgitMapRes::* vector_deleting_destructor)(unsigned int);
		int (CAgitMapRes::* Load)(const char *, int, int);
		void (CAgitMapRes::* Reset)(void);
		void (CAgitMapRes::* OnTimer)(void);
		unsigned long (CAgitMapRes::* GetGDID)(void);
		int (CMapRes::* AddCharacter)(int, int, CCharacter *);
		mystd::string (CMapRes::* GetLoadFileName)(void);
		bool (CMapRes::* IsBattleField)(void);
		bool (CAgitMapRes::* IsAgit)(void);
	};

	/* this+0x0   */ public: //CMapRes baseclass_0;
	/* this+0x71C */ private: int m_guildID;
	/* this+0x720 */ private: char m_agitName[24];
	/* this+0x738 */ private: int m_economy;
	/* this+0x73C */ private: int m_defense;
	/* this+0x740 */ private: int m_triggerE;
	/* this+0x744 */ private: int m_triggerD;
	/* this+0x748 */ private: long m_incTime;
	/* this+0x74C */ private: long m_payTime;
	/* this+0x750 */ private: int m_noGuardian;
	/* this+0x754 */ private: CNPC* m_guardianArray[8];
	/* this+0x774 */ private: CNPC* m_npcArray[3];
	/* this+0x780 */ private: unsigned char m_visibleC;
	/* this+0x781 */ private: unsigned char m_visibleG[8];
	/* this+0x78C */ private: mystd::vector<CNPC*> m_flagNpc;
	/* this+0x79C */ private: mystd::vector<CNPC*> m_treasureNpc;
	/* this+0x7AC */ private: mystd::multimap<long,int> m_timerQ;
	/* this+0x7B8 */ private: int m_isPKTime;
	/* this+0x7BC */ private: int m_isDisableSkill;
	/* this+0x7C0 */ private: int m_createCount;
	/* this+0x7C4 */ private: int m_siegeTimeVersion;
	/* this+0x7C8 */ private: char m_empeliumConqueror[24];
	/* this+0x7E0 */ private: bool m_bInstantMapBlockRequest;
	/* static     */ private: static hook_val<mystd::map<mystd::string,FLAG_INFO*> > m_agitTable;

	public: CAgitMapRes::CAgitMapRes(const int in_mapType);
	public: CAgitMapRes::~CAgitMapRes(void);
	public: void CAgitMapRes::Reset(void);
	public: void CAgitMapRes::OnTimer(void);
	public: int CAgitMapRes::Load(const char* fileName, int mapID, int mapType);
	//public: static bool CAgitMapRes::SetSiegeTime(const char* timeString, int hour);
	public: static long CAgitMapRes::GetNextSigeTime(void);
	//public: static bool CAgitMapRes::SetSiegeTime_v15(const char* timeString, int hour);
	public: static long CAgitMapRes::GetNextSigeTime_v15(void);
	public: void CAgitMapRes::InitAgit(const AGIT_DBINFO& info);
	public: int CAgitMapRes::GetProperty(int n, int& type);
	public: int CAgitMapRes::SetProperty(int n, int data);
	public: int CAgitMapRes::Method(int func, int parm1, int parm2);
	public: int CAgitMapRes::NpcGetProperty(int no, int n, int* data, int* type);
	public: int CAgitMapRes::NpcSetProperty(int no, int n, int data);
	public: void CAgitMapRes::RegisterNPC(CNPC* npc);
	public: int CAgitMapRes::RegisterNPC(int type, CNPC* npc, int* isVisible);
	public: CNPC* CAgitMapRes::GetNPC(int no);
	public: void CAgitMapRes::ChangeOwner(unsigned long newOwner);
	public: void CAgitMapRes::OnRcvAckFromInter(unsigned char ret);
	public: unsigned long CAgitMapRes::GetGDID(void);
	public: void CAgitMapRes::UnlinkNPC(void);
	public: void CAgitMapRes::Schedule(long t, int event);
	public: int CAgitMapRes::IsPKTime(void);
	//public: static int CAgitMapRes::GetLastSiegemsg(int mapID);
	//public: static void CAgitMapRes::UpdateLastSiegeMsg(int mapId, int state);
	//public: static bool CAgitMapRes::RegisterFlag(const char* mapName, CNPC* npc);
	public: static void CAgitMapRes::InsertTable(const char* mapName, int GDID, const char* agitName);
	//public: static void CAgitMapRes::OnNotifyFromInter(const char* mapName, int GDID);
	public: static int __cdecl CAgitMapRes::IsSiegeTime(CMapRes* mapRes);
	public: static int __cdecl CAgitMapRes::IsSiegeTime(void);
	public: static int __cdecl CAgitMapRes::IsSiegeTime_ByMapType(int mapType);
	public: static int __cdecl CAgitMapRes::IsSiegeTime_v15(void);
	//public: static int CAgitMapRes::GetProPertyByMapName(char* mapName, int n, int& type);
	//public: static bool CAgitMapRes::IsAgitMap(const char* mapName);
	public: bool CAgitMapRes::IsAgit(void);
	private: void CAgitMapRes::TimerProc(long time, unsigned long event);
	private: int CAgitMapRes::GetInvestMoney(int percent, int* table, int count);
	private: int CAgitMapRes::GetEMoney(void);
	private: int CAgitMapRes::GetECondition(void);
	private: void CAgitMapRes::InvestEconomy(void);
	private: int CAgitMapRes::GetDMoney(void);
	private: int CAgitMapRes::GetDCondition(void);
	private: void CAgitMapRes::InvestDefense(void);
	private: void CAgitMapRes::OnChangeDefense(int isInit);
	private: void CAgitMapRes::MakeTreasure(void);
	private: void CAgitMapRes::Flush(int target);
	private: void CAgitMapRes::OnChangeOwner(int old);
	private: void CAgitMapRes::SendZenyReqest(unsigned char type, int data);
	private: void CAgitMapRes::SetNextSaveTime(void);
	private: void CAgitMapRes::Save(void);
	private: void CAgitMapRes::SetEmpeliumCreateTime(void);
	private: int CAgitMapRes::GetTreasureBoxCount(void);

private:
	static hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_Reset;
	static hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_OnTimer;
	static hook_method<int (CAgitMapRes::*)(const char* fileName, int mapID, int mapType)> CAgitMapRes::_Load;
	static hook_method<static long (__cdecl *)(void)> CAgitMapRes::_GetNextSigeTime;
	static hook_method<static long (__cdecl *)(void)> CAgitMapRes::_GetNextSigeTime_v15;
	static hook_method<void (CAgitMapRes::*)(const AGIT_DBINFO& info)> CAgitMapRes::_InitAgit;
	static hook_method<int (CAgitMapRes::*)(int n, int& type)> CAgitMapRes::_GetProperty;
	static hook_method<int (CAgitMapRes::*)(int n, int data)> CAgitMapRes::_SetProperty;
	static hook_method<int (CAgitMapRes::*)(int func, int parm1, int parm2)> CAgitMapRes::_Method;
	static hook_method<int (CAgitMapRes::*)(int no, int n, int* data, int* type)> CAgitMapRes::_NpcGetProperty;
	static hook_method<int (CAgitMapRes::*)(int no, int n, int data)> CAgitMapRes::_NpcSetProperty;
	static hook_method<void (CAgitMapRes::*)(CNPC* npc)> CAgitMapRes::_RegisterNPC;
	static hook_method<int (CAgitMapRes::*)(int type, CNPC* npc, int* isVisible)> CAgitMapRes::_RegisterNPC2;
	static hook_method<CNPC* (CAgitMapRes::*)(int no)> CAgitMapRes::_GetNPC;
	static hook_method<void (CAgitMapRes::*)(unsigned long newOwner)> CAgitMapRes::_ChangeOwner;
	static hook_method<void (CAgitMapRes::*)(unsigned char ret)> CAgitMapRes::_OnRcvAckFromInter;
	static hook_method<unsigned long (CAgitMapRes::*)(void)> CAgitMapRes::_GetGDID;
	static hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_UnlinkNPC;
	static hook_method<void (CAgitMapRes::*)(long t, int event)> CAgitMapRes::_Schedule;
	static hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_IsPKTime;
	static hook_method<static void (__cdecl *)(const char* mapName, int GDID, const char* agitName)> CAgitMapRes::_InsertTable;
	static hook_method<static int (__cdecl *)(CMapRes* mapRes)> CAgitMapRes::_IsSiegeTime;
	static hook_method<static int (__cdecl *)(void)> CAgitMapRes::_IsSiegeTime2;
	static hook_method<static int (__cdecl *)(int mapType)> CAgitMapRes::_IsSiegeTime_ByMapType;
	static hook_method<static int (__cdecl *)(void)> CAgitMapRes::_IsSiegeTime_v15;
	static hook_method<bool (CAgitMapRes::*)(void)> CAgitMapRes::_IsAgit;
	static hook_method<void (CAgitMapRes::*)(long time, unsigned long event)> CAgitMapRes::_TimerProc;
	static hook_method<int (CAgitMapRes::*)(int percent, int* table, int count)> CAgitMapRes::_GetInvestMoney;
	static hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetEMoney;
	static hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetECondition;
	static hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_InvestEconomy;
	static hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetDMoney;
	static hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetDCondition;
	static hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_InvestDefense;
	static hook_method<void (CAgitMapRes::*)(int isInit)> CAgitMapRes::_OnChangeDefense;
	static hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_MakeTreasure;
	static hook_method<void (CAgitMapRes::*)(int target)> CAgitMapRes::_Flush;
	static hook_method<void (CAgitMapRes::*)(int old)> CAgitMapRes::_OnChangeOwner;
	static hook_method<void (CAgitMapRes::*)(unsigned char type, int data)> CAgitMapRes::_SendZenyReqest;
	static hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_SetNextSaveTime;
	static hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_Save;
	static hook_method<void (CAgitMapRes::*)(void)> CAgitMapRes::_SetEmpeliumCreateTime;
	static hook_method<int (CAgitMapRes::*)(void)> CAgitMapRes::_GetTreasureBoxCount;
};
