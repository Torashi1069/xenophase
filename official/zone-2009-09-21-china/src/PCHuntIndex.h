#pragma once
#include "std/list"
#include "std/map"


class CNode
{
public:
	typedef mystd::list<int> TNODE_LIST;

public:
	CNode();
	virtual ~CNode();

private:
	/* this+ 0 */ //const CNode::`vftable';
	/* this+ 4 */ TNODE_LIST m_list;
	/* this+16 */ unsigned long m_mobGID;

public:
	void Init(unsigned long mobGID);
	void Clear();
	void DeleteNode(int huntIdent);
	bool Set(int huntIdent);
	int GetIdent(mystd::list<int>& identList);
	int GetCount();
};


class CPCHuntIndex
{
public:
	typedef mystd::map<unsigned long,CNode*> THUNT_INDEX_MAP;

public:
	CPCHuntIndex();
	virtual ~CPCHuntIndex();

private:
	/* this+0 */ //const CPCHuntIndex::`vftable';
	/* this+4 */ THUNT_INDEX_MAP m_map;

public:
	void Clear();
//	void DeleteHunt(unsigned long);
	void EraseHuntIdent(unsigned long mobGID, int huntIdent);
	bool AddHuntList(unsigned long mobGID, int huntIdent);
	int GetHuntIdentList(unsigned long mobGID, mystd::list<int>& identList);
};
