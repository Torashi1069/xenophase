#pragma once
#include "AsyncMonopolyProcess.h"
class CLogonPermitADBWork;
class CPC;


class CAmpLogonPermit : public CAsyncMonopolyProcess
{
public:
	virtual bool operator()();

private:
	bool preliminary_inspection();
	bool mercenary();
	bool actor_infomation_first();
	bool actor_infomation_second();
	bool protect();
	bool unknown_first();
	bool skill();
	bool item();
	bool quest();
	bool wedding();
	bool unknown_second();
	bool effect();
	bool expost();

public:
	CAmpLogonPermit(CPC* in_cpPlayer, CLogonPermitADBWork* in_cpLogonPermitADBWork);
	virtual ~CAmpLogonPermit();

private:
	/* this+ 0 */ //CAsyncMonopolyProcess baseclass_0;
	/* this+ 8 */ CPC* m_cpPlayer;
	/* this+12 */ CLogonPermitADBWork* m_cpLogonPermitADBWork;
	/* this+16 */ const unsigned long m_AID;
	/* this+20 */ const unsigned long m_GID;

	enum enumStep
	{
		STEP_PRELIMINARY_INSPECTION  = 0,
		STEP_MERCENARY               = 1,
		SETP_ACTOR_INFOMATION_FIRST  = 2, //TYPO
		STEP_ACTOR_INFOMATION_SECOND = 3,
		STEP_PROTECT                 = 4,
		STEP_UNKNOWN_FIRST           = 5,
		STEP_SKILL                   = 6,
		STEP_ITEM                    = 7,
		STEP_QUEST                   = 8,
		STEP_WEDDING                 = 9,
		STEP_UNKNOWN_SECOND          = 10,
		STEP_EFFECT                  = 11,
		STEP_EXPOST                  = 12,
	};

private:
	/* this+24 */ enumStep m_Step;
};
