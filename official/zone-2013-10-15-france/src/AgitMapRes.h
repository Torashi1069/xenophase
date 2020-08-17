#pragma once
#include "MapRes.h"
struct AGIT_DBINFO; // #include "AgitDB.h"
class CNPC; // #include "NPC.h"


enum enumAGITFUNC /// @custom
{
	AF_INVEST_ECONOMY   = 0,
	AF_INVEST_DEFENSE   = 1,
	AF_SCHEDULE_PAYTIME = 2,
	AF_FLUSH_GDID       = 3,
	AF_CHANGE_DEFENSE   = 4,
};


enum enumAGITSCHEDULE /// @custom
{
	AS_FLUSH = 0,
	AS_INC   = 1,
	AS_PAY   = 2,
	AS_3     = 3,
	AS_4     = 4,
	AS_SAVE  = 5,
	AS_6     = 6,
	AS_7     = 7,
	AS_8     = 8,
};


struct FLAG_INFO
{
	/* this+ 0 */ int GDID;
	/* this+ 4 */ char agitName[24];
	/* this+28 */ std::vector<CNPC*> vt;
};


class CAgitMapRes : public CMapRes
{
public:
	CAgitMapRes(const int in_mapType);
	virtual ~CAgitMapRes();
	virtual void Reset();

private:
	/* this+   0 */ //CMapRes baseclass_0;
	/* this+1860 */ int m_guildID;
	/* this+1864 */ char m_agitName[24];
	/* this+1888 */ int m_economy;
	/* this+1892 */ int m_defense;
	/* this+1896 */ int m_triggerE;
	/* this+1900 */ int m_triggerD;
	/* this+1904 */ time_t m_incTime;
	/* this+1908 */ time_t m_payTime;
	/* this+1912 */ int m_noGuardian;
	/* this+1916 */ CNPC* m_guardianArray[8];
	/* this+1948 */ CNPC* m_npcArray[3];
	/* this+1960 */ unsigned char m_visibleC;
	/* this+1961 */ unsigned char m_visibleG[8];
	/* this+1972 */ std::vector<CNPC*> m_flagNpc;
	/* this+1988 */ std::vector<CNPC*> m_treasureNpc;
	/* this+2004 */ std::multimap<time_t,int> m_timerQ;
	/* this+2020 */ BOOL m_isPKTime;
	/* this+2024 */ int m_isDisableSkill;
	/* this+2028 */ int m_createCount;
	/* this+2032 */ int m_siegeTimeVersion;
	/* this+2036 */ char m_empeliumConqueror[24];
	/* this+2060 */ bool m_bInstantMapBlockRequest;

public:
	virtual void OnTimer();
	virtual BOOL Load(const char* fileName, int mapID, int mapType);
	static bool SetSiegeTime(const char* timeString, int hour);
	static time_t GetNextSigeTime();
	static bool SetSiegeTime_v15(const char* timeString, int hour);
	static time_t GetNextSigeTime_v15();
	void InitAgit(const AGIT_DBINFO& info);
	int GetProperty(int n, int& type);
	BOOL SetProperty(int n, int data);
	BOOL Method(int func, int parm1, int parm2);
	BOOL NpcGetProperty(int no, int n, int* data, int* type);
	BOOL NpcSetProperty(int no, int n, int data);
	BOOL RegisterNPC(int type, CNPC* npc, BOOL* isVisible);
	void RegisterNPC(CNPC* npc);
	CNPC* GetNPC(int no);
//	void ChangeOwner(unsigned long );
	void OnRcvAckFromInter(unsigned char ret);
	virtual unsigned long GetGDID();
	void UnlinkNPC();
	void Schedule(time_t t, int event);
//	int IsPKTime();
//	bool IsAigitMapInit(const unsigned long );
//	static int GetLastSiegemsg(int );
	static void UpdateLastSiegeMsg(int mapId, int state);
//	static bool RegisterFlag(const char* , CNPC* );
	static void InsertTable(const char* mapName, int GDID, const char* agitName);
	static void OnNotifyFromInter(const char* mapName, int GDID);
	static BOOL IsSiegeTime();
	static BOOL IsSiegeTime(CMapRes* mapRes);
//	static int IsSiegeTime_ByMapType(int );
	static BOOL IsSiegeTime_v15();
//	static int OpenHour_SiegeMode(short , unsigned long );
//	static int GetProPertyByMapName(char* , int , int& );
	static bool IsAgitMap(const char* mapName);
	virtual bool IsAgit();

private:
	void TimerProc(time_t time, unsigned long event);
	int GetInvestMoney(int percent, int* table, int count);
	int GetEMoney();
	int GetECondition();
	void InvestEconomy();
	int GetDMoney();
	int GetDCondition();
	void InvestDefense();
	void OnChangeDefense(BOOL isInit);
	void MakeTreasure();
	void Flush(int target);
	void OnChangeOwner(int old);
//	void SendZenyReqest(unsigned char , int );
	void SetNextSaveTime();
	void Save(const bool bNextSave);
//	void SetEmpeliumCreateTime();
	int GetTreasureBoxCount();
//	void ExpelOtherGuild();

private:
	/* static */ static std::map<std::string,FLAG_INFO*>& m_agitTable; //TODO
};
