#pragma once
#include "CMakerRankDB.h"


class CMakerRankMgr
{
public:
	enum
	{
		TYPE_BLACKSMITH = 0,
		TYPE_ALCHEMIST  = 1,
		TYPE_TAEKWON    = 2,
		TYPE_KILLER     = 3,
	};

private:
	/* this+   4 */ CMakerRankDB m_MakerRankDB;

public:
	/* this+  24 */ MAKER_RANKING m_BlackSmith[12];
	/* this+ 408 */ MAKER_RANKING m_Alchemist[12];
	/* this+ 792 */ MAKER_RANKING m_Taekwon[12];
	/* this+1176 */ MAKER_RANKING m_Killer[12];

public:
	BOOL Init(const char* FileDsn, const char* PASS);
	BOOL Setup();
	void Sort(int Type);
	void UpdateMakeRank(int Type, unsigned long GID, char* Name, int Point);
	void SendZoneMakerRanking(int Type);

public:
	CMakerRankMgr();
	virtual ~CMakerRankMgr();
};
