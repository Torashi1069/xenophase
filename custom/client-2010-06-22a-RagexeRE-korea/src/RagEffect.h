#pragma once
#include "GameActor.h"
class CEffectPrim;


class CRagEffect : public CRenderObject
{
	/* this+    0 */ //CRenderObject baseclass_0;
	/* this+  248 */ CRenderObject* m_master;
	/* this+  252 */ char field_FC[36];
	/* this+  288 */ int field_120;
	/* this+  292 */ int field_124;
	/* this+  296 */ int m_type;
	/* this+  300 */ int field_12C;
	/* this+  304 */ int field_130;
	/* this+  308 */ int m_count;
	/* this+  312 */ int m_stateCnt;
	/* this+  316 */ int m_duration;
	/* this+  320 */ vector3d m_deltaPos;
	/* this+  332 */ vector3d m_deltaPos2;
	/* this+  344 */ int field_158;
	/* this+  348 */ int field_15C;
	/* this+  352 */ int field_160;
	/* this+  356 */ char m_primList[12];
	/* this+  368 */ char field_170[1600];
	/* this+ 1968 */ int m_ezEffectRes;
	/* this+ 1972 */ int m_aniClips_TODO;
	/* this+ 1976 */ char field_7B8[14848];
	/* this+16824 */ char m_rp[55296];
	/* this+72120 */ int m_iCurLayer;
	/* this+72124 */ int m_cEndLayer;
	/* this+72128 */ char field_119C0[128];
	/* this+72256 */ int m_aiCurAniKey[128];
	/* this+72768 */ CEffectPrim* m_prim;
};
C_ASSERT( sizeof CRagEffect == 72772 );
