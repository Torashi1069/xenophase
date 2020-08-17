#pragma once


namespace MSGpar
{


struct tagRG_STRIPWEAPON {
	/* this+0 */ bool bBlockClientNotify;
};

struct tagRG_STRIPHELM {
	/* this+0 */ bool bBlockClientNotify;
};

struct tagWL_CHAINLIGHTNING_ATK {
	/* this(bf)+0:0 len(8)   */ int MaxCnt : 8,
	/* this(bf)+0:8 len(8)   */     Cnt : 8,
	/* this(bf)+0:16 len(16) */     unused : 16;
};

struct tagWM_REVERBERATION_MELEE {
	/* this+0 */ int AtkPercent;
};

struct tagWM_REVERBERATION_MAGIC {
	/* this+0 */ int AtkPercent;
};

struct tagWM_SEVERE_RAINSTORM_MELEE {
	/* this+0 */ int AtkPercent;
};

struct tagSR_CRESCENTELBOW_AUTOSPELL {
	/* this+0 */ int Damage;
};

struct tagINT {
	/* this+0 */ int value;
};


class CVar
{
public:
	union VAR_UNION
	{
	/* this+0 */ MSGpar::tagRG_STRIPWEAPON m_RG_STRIPWEAPON;
	/* this+0 */ MSGpar::tagRG_STRIPHELM m_RG_STRIPHELM;
	/* this+0 */ MSGpar::tagWL_CHAINLIGHTNING_ATK m_WL_CHAINLIGHTNING_ATK;
	/* this+0 */ MSGpar::tagWM_REVERBERATION_MELEE m_WM_REVERBERATION_MELEE;
	/* this+0 */ MSGpar::tagWM_REVERBERATION_MAGIC m_WM_REVERBERATION_MAGIC;
	/* this+0 */ MSGpar::tagWM_SEVERE_RAINSTORM_MELEE m_WM_SEVERE_RAINSTORM_MELEE;
	/* this+0 */ MSGpar::tagSR_CRESCENTELBOW_AUTOSPELL m_SR_CRESCENTELBOW_AUTOSPELL;
	/* this+0 */ MSGpar::tagINT m_INT;
	};

	/* this+0 */ public: union MSGpar::CVar::VAR_UNION m_Var;

	/// custom helper constructor
	public: MSGpar::CVar::CVar(int value)
	{
		this->m_Var.m_INT.value = value;
	}

	public: MSGpar::CVar::CVar(const MSGpar::CVar& in_rhs)
	{
		this->m_Var.m_INT.value = in_rhs.m_Var.m_INT.value;
	}

	public: MSGpar::CVar::CVar(void)
	{
		this->m_Var.m_INT.value = 0;
	}

	public: MSGpar::CVar::~CVar(void)
	{
	}
};


};
