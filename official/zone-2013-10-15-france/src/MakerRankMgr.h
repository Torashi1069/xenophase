#pragma once
class CPC;


enum enumMAKERRANKTYPE
{
	BLACKSMITH_VERSION  = 0,
	ALCHEMIST_VERSION   = 1,
	TAEKWON_VERSION     = 2,
	KILLER_VERSION      = 3,
	GANGSI_VERSION      = 4,
	DEATHKNIGHT_VERSION = 5,
	COLLECTOR_VERSION   = 6,
	MAKERRANKTYPE_MAX /// @custom
};


enum { MAKERRANKPOS_MAX = 10 }; /// @custom


struct MAKERINFO
{
	/* this+ 0 */ int rank;
	/* this+ 4 */ char charname[24];
	/* this+28 */ int point;
};


struct MAKER_RANKING
{
	/* this+ 0 */ unsigned long GID;
	/* this+ 4 */ char charname[24];
	/* this+28 */ int point;
};


class CMakerRankMgr
{
public:
	CMakerRankMgr();
	~CMakerRankMgr();

public:
	void ResetMakerRankList(int type);
	void SortMakerRankList(int type);
	void Get_TOP_MakerRank(int type);
	BOOL UpdateMakerRank(CPC* pc, int type, int value, int& point);
	void GetMakerRank(unsigned long GID, int& point, int JobType);
	int GetMakerPower(unsigned long GID, int type);
	void SetMakerRankList(char* buf);
	int GetRankFromTop10(CPC* pc);

public:
	/* this+  0 */ std::map<unsigned long,MAKERINFO> m_MakerRankList[MAKERRANKTYPE_MAX];
	/* this+112 */ MAKER_RANKING m_MakerRank[MAKERRANKTYPE_MAX][MAKERRANKPOS_MAX];
};
