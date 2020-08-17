#pragma once


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
	stdext::hash_map<K,V> m_mapMap;
};


struct SPCBANGINFO
{
	/* this+0 */ DWORD dwIPID;
};


struct SPCBANGINFOLIST
{
	/* this+0 */ std::list<SPCBANGINFO> m_list;
};


class CListedPCBangIPList
{
public:
	CListedPCBangIPList();
	~CListedPCBangIPList();

	class lessthan
	{
	public:
//		bool operator()(const int, const int);
//		bool operator()(const unsigned long, const unsigned long);
	};

public:
//	bool Find(unsigned long&);
//	int Init(const char*);
//	int Get(unsigned long, SPCBANGINFO*);
//	int Add(unsigned long&, SPCBANGINFO&);

private:
//	unsigned long GetDWORDIP(char*);
//	void Insert(unsigned long&, SPCBANGINFO&);

public:
	/* this+ 0 */ float m_fDefaultExp1;
	/* this+ 4 */ float m_fDefaultExp2;
	/* this+ 8 */ float m_fDefaultDrop;
	/* this+12 */ int m_nCountListed;
	/* this+16 */ float m_fListedIPsExp1;
	/* this+20 */ float m_fListedIPsExp2;
	/* this+24 */ float m_fListedIPsDrop;
private:
	/* this+28 */ std::set<DWORD,lessthan> m_setIPList;
	/* this+44 */ CMyHash_Map<DWORD,SPCBANGINFO> m_hashmapIPList;

};
