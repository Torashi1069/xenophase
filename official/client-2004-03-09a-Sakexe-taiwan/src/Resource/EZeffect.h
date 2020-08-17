#pragma once
#include "Struct.h"
#include "Base/File.h"
#include "Base/Res.h"


struct KAC_XFORMDATA
{
	/* this+  0 */ float x;
	/* this+  4 */ float y;
	/* this+  8 */ float u;
	/* this+ 12 */ float v;
	/* this+ 16 */ float us;
	/* this+ 20 */ float vs;
	/* this+ 24 */ float u2;
	/* this+ 28 */ float v2;
	/* this+ 32 */ float us2;
	/* this+ 36 */ float vs2;
	/* this+ 40 */ float ax[4];
	/* this+ 56 */ float ay[4];
	/* this+ 72 */ float aniframe;
	/* this+ 76 */ unsigned long anitype;
	/* this+ 80 */ float anidelta;
	/* this+ 84 */ float rz;
	/* this+ 88 */ float crR;
	/* this+ 92 */ float crG;
	/* this+ 96 */ float crB;
	/* this+100 */ float crA;
	/* this+104 */ unsigned long srcalpha;
	/* this+108 */ unsigned long destalpha;
	/* this+112 */ unsigned long mtpreset;
};


struct KAC_KEYFRAME
{
	/* this+0 */ int iFrame;
	/* this+4 */ unsigned long dwType;
	/* this+8 */ KAC_XFORMDATA XformData;
};


struct KAC_LAYER
{
	/* this+  0 */ int cTex;
	/* this+  4 */ int iCurAniFrame;
	/* this+  8 */ CTexture* m_tex[110];
	/* this+448 */ const char* m_texName[110];
	/* this+888 */ int cAniKey;
	/* this+892 */ KAC_KEYFRAME* aAniKey;

	public: KAC_LAYER::KAC_LAYER(void);
	public: KAC_LAYER::~KAC_LAYER(void);
	public: CTexture* KAC_LAYER::GetTexture(int iTex);
};


struct KANICLIP
{
	/* this+ 0 */ int nFPS;
	/* this+ 4 */ int cFrame;
	/* this+ 8 */ int cLayer;
	/* this+12 */ int cEndLayer;
	/* this+16 */ KAC_LAYER aLayer[60];
};


class CEZeffectRes : public CRes
{
	struct vtable_t //const CEZeffectRes::`vftable'
	{
		void* (CEZeffectRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (CEZeffectRes::* Clone)(void) const;
		bool (CEZeffectRes::* Load)(const char* fName);
		void (CEZeffectRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	/* this+    0 */ public: //CRes baseclass_0;
	/* this+  272 */ public: KANICLIP m_aniClips;
	/* this+54048 */ public: int m_nMaxLayer;
	/* this+54052 */ protected: CFile m_fp;

	public: CEZeffectRes::CEZeffectRes(Exemplar __formal, const char* resid, const char* baseDir); // line 89
	public: CEZeffectRes::CEZeffectRes(void);
	public: virtual CRes* CEZeffectRes::Clone(void) const; // line 89
	public: virtual bool CEZeffectRes::Load(const char* fName);
	public: virtual void CEZeffectRes::Reset(void);

private:
	static hook_method<CRes* (CEZeffectRes::*)(void) const> CEZeffectRes::_Clone;
	static hook_method<bool (CEZeffectRes::*)(const char* fName)> CEZeffectRes::_Load;
	static hook_method<void (CEZeffectRes::*)(void)> CEZeffectRes::_Reset;
};
