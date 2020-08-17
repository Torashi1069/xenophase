#pragma once
#include "QVar.h"
#include "NetLib/MemoryMgr.h"


struct TPROVISO
{
	/* this+ 0 */ unsigned long t_qid;
	/* this+ 4 */ short t_questType;
	/* this+ 8 */ unsigned long t_hiLV;
	/* this+12 */ unsigned long t_lowLV;
	/* this+16 */ short t_sex;
	/* this+18 */ short t_homun_minLv;
	/* this+20 */ short t_homun_maxLv;
	/* this+22 */ short t_homun_evolution;
	/* this+24 */ std::vector<unsigned long> t_jobList;
	/* this+40 */ std::map<unsigned long,int> t_itemList;
	/* this+56 */ std::map<unsigned long,int> t_completeItemList;
};


class CQuestProviso
{
private:
	typedef std::map<unsigned long,TPROVISO*> TPROVISO_MAP;

public:
	CQuestProviso();
	virtual ~CQuestProviso();

private:
	/* this+ 0 */ //const CQuestProviso::`vftable';
	/* this+ 4 */ TPROVISO_MAP m_proviso_map;
	/* this+20 */ CMemoryMgr<TPROVISO> m_pool;

public:
	bool Init();
	void Filnalize();
	bool LoadQuestProviso(const char* file_name);
	bool AddProviso(unsigned long qid);
	bool InsertQuestType(unsigned long qid, short type);
	bool InsertSex(unsigned long qid, short sex);
	bool InsertLevel(unsigned long qid, unsigned long lowLv, unsigned long hiLv);
	bool InsertJobList(unsigned long qid, std::vector<CQVar> data);
	bool InsertItem(unsigned long qid, std::vector<CQVar> data);
	bool InsertCompleteItem(unsigned long qid, std::vector<CQVar> data);
	bool InsertHomunLevel(const unsigned long qid, const int minLv, const int max_lv);
	bool InsertEvolution(const unsigned long qid, const int type);
	TPROVISO* SelectProviso(unsigned long qid);
};
