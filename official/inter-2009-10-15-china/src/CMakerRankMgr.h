#pragma once
#include "CMakerRankDB.h"


class CMakerRankMgr
{
	enum
	{
		TYPE_BLACKSMITH  = 0,
		TYPE_ALCHEMIST   = 1,
		TYPE_TAEKWON     = 2,
		TYPE_KILLER      = 3,
		TYPE_GANGSI      = 4,
		TYPE_DEATHKNIGHT = 5,
		TYPE_COLLECTOR   = 6,
	};

	/* this+   0 */ public: //const CMakerRankMgr::`vftable';
	/* this+   4 */ private: CMakerRankDB m_MakerRankDB;
	/* this+  24 */ public: MAKER_RANKING m_BlackSmith[12];
	/* this+ 408 */ public: MAKER_RANKING m_Alchemist[12];
	/* this+ 792 */ public: MAKER_RANKING m_Taekwon[12];
	/* this+1176 */ public: MAKER_RANKING m_Killer[12];
	/* this+1560 */ public: MAKER_RANKING m_Gangsi[12];
	/* this+1944 */ public: MAKER_RANKING m_DeathKnight[12];
	/* this+2328 */ public: MAKER_RANKING m_Collector[12];

	public: int CMakerRankMgr::Init(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type);
	public: int CMakerRankMgr::Setup(void);
	public: void CMakerRankMgr::Sort(int Type);
	public: void CMakerRankMgr::UpdateMakeRank(int Type, unsigned long GID, char* Name, int Point);
	public: void CMakerRankMgr::SendZoneMakerRanking(int Type);
	public: CMakerRankMgr::CMakerRankMgr(void);
	public: virtual CMakerRankMgr::~CMakerRankMgr(void);

private:
	static hook_method<int (CMakerRankMgr::*)(const char* DSN, const char* UID, const char* PASS, const char* DB, unsigned char type)> CMakerRankMgr::_Init;
	static hook_method<int (CMakerRankMgr::*)(void)> CMakerRankMgr::_Setup;
	static hook_method<void (CMakerRankMgr::*)(int Type)> CMakerRankMgr::_Sort;
	static hook_method<void (CMakerRankMgr::*)(int Type, unsigned long GID, char* Name, int Point)> CMakerRankMgr::_UpdateMakeRank;
	static hook_method<void (CMakerRankMgr::*)(int Type)> CMakerRankMgr::_SendZoneMakerRanking;
};
