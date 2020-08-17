#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"
#include "Common/Singleton.h"


struct SExtraExp
{
	/* this+0 */ float fExp1;
	/* this+4 */ float fExp2;
	/* this+8 */ float fdrp;
};


struct sExtraExp
{
	/* this+ 0 */ int nAcafe_ID;
	/* this+ 4 */ float fExp;
	/* this+ 8 */ float fDeath;
	/* this+12 */ float fDrp;
	/* this+16 */ int nLimitNum;

	sExtraExp(int nAcafe_ID, float fExp, float fDeath, float fDrp, int nLimitNum) : nAcafe_ID(nAcafe_ID), fExp(fExp), fDeath(fDeath), fDrp(fDrp), nLimitNum(nLimitNum) { }
};


struct sCurIPBonusUser
{
	/* this+0 */ int nAcafe_ID;
	/* this+4 */ DWORD dwAID;
	/* this+8 */ DWORD dwIP;

	sCurIPBonusUser(int nAcafe_ID, DWORD dwAID, DWORD dwIP) : nAcafe_ID(nAcafe_ID), dwAID(dwAID), dwIP(dwIP) { }
};


class CPremiumServiceDB : public CDatabase, public CSingleton<CPremiumServiceDB>
{
private:
	/* this+  0 */ //CDatabase baseclass_0;
	/* this+ 37 */ //CSingleton<CPremiumServiceDB> baseclass_37;
	/* this+ 40 */ CCriticalSection m_csPremiumServiceDB;

	/* this+ 64 */ int m_nCountOfGrade;
	/* this+ 68 */ SExtraExp m_expInfoByIPGrade[12];

public:
	CPremiumServiceDB();
	~CPremiumServiceDB();
//	int IsRegistedAddress(char*);
//	int GetExtraExpInfo(char*, SExtraExp*);
//	int GetExtraExpInfo(char*, SExtraExp*, const unsigned long&);
//	float TestFloat(char*);

//	int LoadIPGradeInfo();

	/* this+212 */ std::list<DWORD> m_listPCBangIPList[3][10];
	/* this+572 */ int m_nCurrPos;

//	int GetDefaultExtraExpInfo(SExtraExp*);

	/* this+576 */ SExtraExp m_defaultExp;
	/* this+588 */ SExtraExp m_defaultExpNotListed;

//	int GetIPGrade(char*);
//	int GetValuesByGrade(int, SExtraExp*);
//	int InitPCBangIPList();
//	int DeleteUser(unsigned long&, const unsigned long&);
	int ReloadPCBangIPList();
//	bool Get(char*);
	bool Get(DWORD dwIP);
	std::pair<bool,std::string> InitIPBonusList();
	bool ReloadIPBonusList();
	bool InitPCBonusInit();
//	bool InsertPCBonusLog(const DWORD, const int, const char*, const int);
	bool DeletePCBonusLog(const DWORD in_dwAID);
//	std::tr1::tuple<bool,int,unsigned long,unsigned long,int> GetUserPCBonusInfo(const unsigned long, const unsigned long);
//	std::tr1::tuple<float,float,float,int> GetDefaultExp();
	std::tr1::tuple<bool,float,float,float,int> GetExp(const DWORD in_dwAID, const DWORD in_dwIP);
	std::tr1::tuple<bool,int,int> DeleteUserPcbonusEFSTList(const DWORD in_dwAID, const DWORD in_dwIP);
	std::tr1::tuple<bool,float,float,float> GetPremiumIPBonus(const DWORD in_dwAID);

private:
	/* this+600 */ std::map<unsigned long,sExtraExp> m_mapIPBonusList;
	/* this+616 */ std::list<sCurIPBonusUser> m_listCurIPBonusUser;
	/* this+628 */ float m_fDefaultExp;
	/* this+632 */ float m_fDefaultDeath;
	/* this+636 */ float m_fDeafultDrp;
	/* this+640 */ int m_nLimitNum;
	/* this+644 */ int m_nAcafeID;
};
