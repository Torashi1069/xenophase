#pragma once
#include "shared/ODBCV2.h"
#include "shared/ODBCV2Connector.h"


class CMercenaryDBV2 : public CODBCV2
{
public:
	struct DBINFO
	{
		/* this+ 0 */ int TypicalJob;
		/* this+ 4 */ int Job;
		/* this+ 8 */ int RemainLifeSECOND;
		/* this+12 */ int Property;
		/* this+16 */ int BodyState;
		/* this+20 */ int HealthState;
		/* this+24 */ int EffectState;
		/* this+28 */ int approval_monster_kill_counter;
		/* this+32 */ int hp;
		/* this+36 */ int sp;
	};

private:
	/* static  */ static CMercenaryDBV2*& m_cpSelf; //TODO
	/* this+16 */ bool m_bOK;

public:
	bool isOK() const;

public:
	static CMercenaryDBV2* GetObj();
	static bool CreateInstance(const std::string in_strFileDSN, const std::string in_strPWD, const CODBCV2Connector::enumConncetType in_eConnectType);
	static void DestoryInstance();

private:
	CMercenaryDBV2(const std::string in_strFileDSN, const std::string in_strPWD, const CODBCV2Connector::enumConncetType in_eConnectType);
	virtual ~CMercenaryDBV2();
};
