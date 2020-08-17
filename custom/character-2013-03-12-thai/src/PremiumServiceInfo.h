#pragma once


namespace PERSONAL_PREMIUM_INFO
{
struct PREMIUM_SVC_INFO;
struct PCBANG_PREMIUM_INFO;
};


struct PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO
{
	/* this+ 0 */ float fExp;
	/* this+ 4 */ float fDeath;
	/* this+ 8 */ float fDrop;
	/* this+12 */ int nMaxStoreCnt;

	PREMIUM_SVC_INFO() : fExp(0), fDeath(0), fDrop(0), nMaxStoreCnt(0) { }
	PREMIUM_SVC_INFO(const float in_fExp, const float in_fDeath, const float in_fDrop, const int in_nMaxStoreCnt) : fExp(in_fExp), fDeath(in_fDeath), fDrop(in_fDrop), nMaxStoreCnt(in_nMaxStoreCnt) { }
};


struct PERSONAL_PREMIUM_INFO::PCBANG_PREMIUM_INFO
{
	/* this+0 */ float fExp;
	/* this+4 */ float fDeath;
	/* this+8 */ float fDrop;

	PCBANG_PREMIUM_INFO(const float in_fExp, const float in_fDeath, const float in_fDrop) : fExp(in_fExp), fDeath(in_fDeath), fDrop(in_fDrop) { }
};


class CPremiumServiceInfo
{
public:
	bool SetPremiumFlag(const BOOL bPrmFlag);
	bool SetPCBangFlag(const BOOL bPCBangPrmFlag);
	bool SetGravityPublicIP(const char* szGravityPublicIP);
	bool SetNonePremiumSvcInfo(const float in_fExp, const float in_fDeath, const float in_fDrop, const float in_fMaxStoreCnt);
	bool SetCommonPremiumSvcInfo(const float in_fExp, const float in_fDeath, const float in_fDrop, const int in_fMaxStoreCnt);
	bool SetPremiumSvcInfo(const int in_nGrade, const float in_fExp, const float in_fDeath, const float in_fDrop, const int in_nMaxStoreCnt);
	bool SetPCBangGradeInfo(const int in_nPCBangGrade, const float in_fExp, const float in_fDeath, const float in_fDrop);
//	bool GetInfo_KR(__SUSER__*, PACKET_HZ_PERSONAL_INFORMATION*);
	bool GetInfo(const int in_nGrade, PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO* out_pInfo);
//	bool GetPCBangInfo(__SUSER__*, PACKET_HZ_PERSONAL_INFORMATION*, int);
//	bool GetPrmType();
//	bool GetInfo_KR_2ND(__SUSER__*, PACKET_HZ_PERSONAL_INFORMATION_2ND&, PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO&, const PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO&, const PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO&);
//	bool GetPCBangInfo_2ND(__SUSER__*, PACKET_HZ_PERSONAL_INFORMATION_2ND&, PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO&, int);

	bool isOK() const;
	bool Init();

	static bool CreateInstance();
//	static void DestroyInstance();
	static CPremiumServiceInfo* GetObj();

private:
//	bool LoadTbl();
	CPremiumServiceInfo();
//	~CPremiumServiceInfo();

private:
	/* this+ 0 */ bool m_bOK;
	/* this+ 1 */ bool m_bPrmFlag;
	/* this+ 2 */ bool m_bPCBangPrmFlag;
	/* this+ 4 */ DWORD m_dwGravityPublicIP;
	/* this+ 8 */ std::map<int,PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO> m_mapPrmInfo;
	/* this+24 */ std::map<int,PERSONAL_PREMIUM_INFO::PCBANG_PREMIUM_INFO> m_mapPCBangInfo;
	/* this+40 */ PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO* m_stCommonPrmInfo;
	/* this+44 */ PERSONAL_PREMIUM_INFO::PREMIUM_SVC_INFO* m_stNonePrmInfo;
	/* this+48 */ RTL_CRITICAL_SECTION m_cs;
	/* static  */ static CPremiumServiceInfo* m_cpSelf;
};
