#pragma once
namespace MSGpar {


struct tagSC_STRIPACCESSARY {
	/* this+0 */ bool bBlockClientNotify;
};

struct tagRG_STRIPWEAPON {
	/* this+0 */ bool bBlockClientNotify;
};

struct tagRG_STRIPHELM {
	/* this+0 */ bool bBlockClientNotify;
};

struct tagRG_STRIPSHIELD {
	/* this+0 */ bool bBlockClientNotify;
};

struct tagRG_STRIPARMOR {
	/* this+0 */ bool bBlockClientNotify;
};

struct tagWL_CHAINLIGHTNING_ATK {
	/* this(bf)+0: 0 len( 8) */ int MaxCnt : 8;
	/* this(bf)+0: 8 len( 8) */ int Cnt    : 8;
	/* this(bf)+0:16 len(16) */ int unused : 16;
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
		tagSC_STRIPACCESSARY m_SC_STRIPACCESSARY;
		tagRG_STRIPWEAPON m_RG_STRIPWEAPON;
		tagRG_STRIPHELM m_RG_STRIPHELM;
		tagRG_STRIPSHIELD m_RG_STRIPSHIELD;
		tagRG_STRIPARMOR m_RG_STRIPARMOR;
		tagWL_CHAINLIGHTNING_ATK m_WL_CHAINLIGHTNING_ATK;
		tagWM_REVERBERATION_MELEE m_WM_REVERBERATION_MELEE;
		tagWM_REVERBERATION_MAGIC m_WM_REVERBERATION_MAGIC;
		tagWM_SEVERE_RAINSTORM_MELEE m_WM_SEVERE_RAINSTORM_MELEE;
		tagSR_CRESCENTELBOW_AUTOSPELL m_SR_CRESCENTELBOW_AUTOSPELL;
		tagINT m_INT;
	};

public:
	/* this+0 */ VAR_UNION m_Var;

public:
	CVar() { memset(&m_Var, 0, sizeof(m_Var)); }
	CVar(int in_value) { m_Var.m_INT.value = in_value; } /// @custom
	CVar(const CVar& in_rhs) { m_Var.m_INT.value = in_rhs.m_Var.m_INT.value; }
	~CVar() { }
};


bool IsNotifySkillAck(const int in_SKID, CVar in_par);


}; // namespace
