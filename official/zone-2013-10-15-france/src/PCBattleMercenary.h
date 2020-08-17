#pragma once
#include "MercenaryDBV2.h"


class CPCBattleMercenary
{
public:
	struct TypicalJobInfo
	{
		/* this+0 */ int tatal_call_number;
		/* this+4 */ int faith;

		TypicalJobInfo() : tatal_call_number(0), faith(0) { }
	};

	struct tagDBData
	{
		/* this+ 0 */ int m_Call;
		/* this+ 4 */ TypicalJobInfo m_arch;
		/* this+12 */ TypicalJobInfo m_spear;
		/* this+20 */ TypicalJobInfo m_sword;
	};

private:
	typedef std::map<int,TypicalJobInfo> TYPICALJOBINFOCONTAINER;
	typedef std::map<int,TypicalJobInfo>::iterator TYPICALJOBINFOCONTAINERITOR;

public:
	enum enumWorkStep
	{
		WORKSTEP_NONE   = 0,
		WORKSTEP_DELETE = 1,
		WORKSTEP_CREATE = 2,
	};

private:
	/* this+ 0 */ //const CPCBattleMercenary::`vftable';
	/* this+ 4 */ bool m_bCall;
	/* this+ 5 */ bool m_bModify;
	/* this+ 8 */ TYPICALJOBINFOCONTAINER m_TypicalJobInfoContainer;
	/* this+24 */ enumWorkStep m_WorkStep;

public:
	class CProxyDB
	{
	public:
		/* this+   0 */ bool m_bLoad;
		/* this+   4 */ CMercenaryDBV2::DBINFO m_Info;
		/* this+  44 */ unsigned char m_EffectData[512];
		/* this+ 556 */ int m_EffectLength;
		/* this+ 560 */ unsigned char m_StateData[512];
		/* this+1072 */ int m_StateLength;

	public:
		CProxyDB() : m_bLoad(false) { }
		~CProxyDB() { }
	};

public:
	/* this+28 */ CProxyDB m_ProxyDB;

public:
	void Clear();
//	const enumWorkStep GetWorkStep();
//	void SetWorkStep(const enumWorkStep );
//	bool isCall();
//	bool GetTypicalJobInfo(const int, TypicalJobInfo& );
//	bool InsertTypicalJobInfo(const int , TypicalJobInfo );
//	void UpdateTypicalJobInfo(const int , TypicalJobInfo );
//	void SetCall(int );
//	int GetTotalSummonNum(const int );
//	int GetFaith(const int );
//	void SubFaith(const int , const int );
//	void AddFaith(const int , const int );
//	CPCBattleMercenary& operator=(const tagDBData& );
//	operator tagDBData();

public:
	CPCBattleMercenary();
	virtual ~CPCBattleMercenary();
};
