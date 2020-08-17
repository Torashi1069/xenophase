#pragma once
#include "Pc.h"
class CRagEffect;


enum PROCEEDTYPE
{
	PT_NOTHING     = 0,
	PT_ATTACK      = 1,
	PT_PICKUPITEM  = 2,
	PT_SKILL       = 3,
	PT_GROUNDSKILL = 4,
	PT_ATTACK_2    = 5,
	PT_TOUCH_SKILL = 6,
};


class CPlayer : public CPc
{
	/* this+   0 */ public: //CPc baseclass_0;
	/* this+ 996 */ public: int m_destCellX;
	/* this+1000 */ public: int m_destCellZ;
	/* this+1004 */ public: unsigned long m_attackReqTime;
	/* this+1008 */ public: unsigned long m_preMoveStartTick;
	/* this+1012 */ public: PROCEEDTYPE m_proceedType;
	/* this+1016 */ public: int m_preMoveOn;
	/* this+1020 */ public: int m_attackMode;
	/* this+1024 */ public: int m_isAttackRequest;
	/* this+1028 */ public: int m_isWaitingMoveAck;
	/* this+1032 */ public: int m_isPreengageStateOfMove;
	/* this+1036 */ public: unsigned long m_proceedTargetGid;
	/* this+1040 */ public: unsigned long m_totalAttackReqCnt;
	/* this+1044 */ public: unsigned long m_tickOfMoveForAttack;
	/* this+1048 */ public: unsigned long m_moveReqTick;
	/* this+1052 */ public: unsigned long m_standTick;
	/* this+1056 */ public: int m_skillId;
	/* this+1060 */ public: int m_skillAttackRange;
	/* this+1064 */ public: int m_skillUseLevel;
	/* this+1068 */ public: int m_gSkillDx;
	/* this+1072 */ public: int m_gSkillDy;
	/* this+1076 */ public: int m_preengageXOfMove;
	/* this+1080 */ public: int m_preengageYOfMove;
	/* this+1084 */ public: CRagEffect* m_statusEffect;

	//TODO
};
C_ASSERT( sizeof CPlayer == 1088 );
