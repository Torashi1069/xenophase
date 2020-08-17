#pragma once
#include "Common/CriticalSection.h"
#include "Common/Singleton.h"


struct _tagCONNECT_INFO
{
	/* this+0 */ DWORD dwConnectCount;
	/* this+4 */ time_t tFirstConnectTimePerHour;
};


template<typename K, typename V> class CMyHashMap
{
public:
//	int Clear();
//	void Insert(K&, V&);
//	void Delete(const K&);
//	int GetCount();
//	int Bring(const K&, V*);
//	V Bring(const K&);
//	int Get(const K&, V**);
//	int Get(const K&, V*);
//	V Get(const K&);
//	int IsObject(const K&);

public:
	stdext::hash_map<K,V> m_mapMap;
};


class DuplicatedIPBlockList : public CSingleton<DuplicatedIPBlockList>
{
public:
	DuplicatedIPBlockList();
	~DuplicatedIPBlockList();
//	int IsBlock(unsigned long, unsigned long);
//	int Clear();
//	int GetCount();
//	void SetDuplicatedIPLimitedCount(const int);
//	void SetDuplicatedIPBlockTime(const int);

private:
	/* this+ 0 */ //const DuplicatedIPBlockList::`vftable';
	/* this+ 4 */ //CSingleton<DuplicatedIPBlockList> baseclass_4;
	/* this+ 4 */ private: CMyHashMap<DWORD,_tagCONNECT_INFO> m_mapAID;
	/* this+48 */ public: CCriticalSection m_csSyncObject;
	/* this+72 */ private: int nDuplicatedIP_Limited_Connect_Count;
	/* this+76 */ private: int nDuplicatedIP_Block_Time;
};
