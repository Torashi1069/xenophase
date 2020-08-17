#pragma once
#include "NpcMob.h"


class CNpcMobRecycleMgr
{
public:
	CNpcMob* Get();
	void Put(CNpcMob* in_cpNpcMob);
	int GetMgrNum(); //TODO
	void Process();
	bool isOK() const;

public:
	static bool CreateInstance();
	static void DestroyInstance();
	static CNpcMobRecycleMgr* GetObj(); /// @custom

private:
	CNpcMobRecycleMgr(const int in_MaxGeneratorNum);
	~CNpcMobRecycleMgr();

private:
	/* static  */ static CNpcMobRecycleMgr*& m_cpSelf; //TODO
	typedef std::list<CNpcMob*> WASTEPAPERBASKER;
	/* this+ 0 */ WASTEPAPERBASKER m_WastepaperBasket;
	/* this+12 */ bool m_bOK;
	/* this+16 */ const int m_MaxGeneratorNum;
	/* this+20 */ int m_GeneratorCnt;
};
