#pragma once
#include "ODBCV2.h"


class CMercenaryDBV2 : public CODBCV2
{
public:
	struct DBINFO
	{
		/* this+0x0  */ int TypicalJob;
		/* this+0x4  */ int Job;
		/* this+0x8  */ int RemainLifeSECOND;
		/* this+0xC  */ int Property;
		/* this+0x10 */ int BodyState;
		/* this+0x14 */ int HealthState;
		/* this+0x18 */ int EffectState;
		/* this+0x1C */ int approval_monster_kill_counter;
		/* this+0x20 */ int hp;
		/* this+0x24 */ int sp;
	};

	/* this+0x0  */ //CODBCV2
	/* static    */ private: static hook_ptr<CMercenaryDBV2 *> m_cpSelf;
	/* this+0x10 */ private: bool m_bOK;

	public: bool CMercenaryDBV2::isOK(void);
	//public: static CMercenaryDBV2* CMercenaryDBV2::GetObj(void);
	public: static bool __cdecl CMercenaryDBV2::CreateInstance(const mystd::string in_strDSNname, const mystd::string in_strUserID, const mystd::string in_strPWD, const mystd::string in_strDBname, const enum CODBCV2Connector::enumConnectType in_eConnectType);
	public: static void __cdecl CMercenaryDBV2::DestroyInstance(void);
	private: CMercenaryDBV2::CMercenaryDBV2(const mystd::string in_strDSNname, const mystd::string in_strUserID, const mystd::string in_strPWD, const mystd::string in_strDBname, const enum CODBCV2Connector::enumConnectType in_eConnectType);
	private: virtual CMercenaryDBV2::~CMercenaryDBV2(void);

private:
	static hook_method<bool (CMercenaryDBV2::*)(void)> CMercenaryDBV2::_isOK;
	static hook_method<static bool (__cdecl *)(const mystd::string in_strDSNname, const mystd::string in_strUserID, const mystd::string in_strPWD, const mystd::string in_strDBname, const enum CODBCV2Connector::enumConnectType in_eConnectType)> CMercenaryDBV2::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CMercenaryDBV2::_DestroyInstance;
};
