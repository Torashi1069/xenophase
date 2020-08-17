#pragma once
#include "SSIList.h"
#include "SSIReqList.h"


class CSSIMgr
{
public:
	void CreateDummyList(); //TODO
	void TestDelete(); //TODO
	void TestInsert(); //TODO
	void InsertDummyList(); //TODO

public:
	static bool CreateInstance();
	static void DestoryInstance();
	static CSSIMgr* GetObj(); /// @custom

public:
	void Proc();

private:
	/* static  */ static CSSIMgr*& m_pSelf; //TODO
	/* this+ 0 */ //const CSSIMgr::`vftable';
	/* this+ 4 */ CSSIList m_SSIList;
	/* this+76 */ CSSIReqList m_SSIRequest;

private:
	CSSIMgr();
	virtual ~CSSIMgr();

	friend class CPC; // ClearSearchStoreInfo()
};
