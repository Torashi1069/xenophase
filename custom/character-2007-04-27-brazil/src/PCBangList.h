#pragma once
#include "Common/Singleton.h"


template<typename K, typename V> class CMyHash_Map
{
public:
//	int Clear();
//	void Insert(const K&, V&);
//	void Delete(const K&);
//	int GetCount();
//	int Bring(const K&, V*);
//	V Bring(const K&);
//	int Get(const K&, V**);
//	int Get(const K&, V*);
//	V Get(const K&);
//	int IsObject(const K&);

public:
	/* this+0 */ stdext::hash_map<K,V> m_mapMap;
};


struct SPCBANGINFO
{
	/* this+ 0 */ WORD wIPStart;
	/* this+ 2 */ WORD wIPEnd;
	/* this+ 4 */ float fExp1;
	/* this+ 8 */ float fExp2;
	/* this+12 */ float fDrop;
};


struct SPCBANGINFOLIST
{
	/* this+0 */ std::list<SPCBANGINFO> m_list;
};


class CListedPCBangIPList : public CSingleton<CListedPCBangIPList>
{
public:
	CListedPCBangIPList();
	~CListedPCBangIPList();

	class lessthan
	{
	public:
//		bool operator()(const unsigned long, const unsigned long);
//		bool operator()(const int, const int);
	};

public:
//	bool Find(unsigned long &);
//	int Init(const char *);
//	int Get(unsigned long, struct SPCBANGINFO *);

private:
//	DWORD GetDWORDIP(char *);
//	void Insert(unsigned long &, struct SPCBANGINFO &);

public:
	/* this+ 0 */ //CSingleton<CListedPCBangIPList> baseclass_0;
	/* this+ 0 */ float m_fDefaultExp1;
	/* this+ 4 */ float m_fDefaultExp2;
	/* this+ 8 */ float m_fDefaultDrop;
private:
	/* this+12 */ std::set<DWORD,lessthan> m_setIPList;
	/* this+24 */ CMyHash_Map<DWORD,SPCBANGINFOLIST> m_hashmapIPList;
};
