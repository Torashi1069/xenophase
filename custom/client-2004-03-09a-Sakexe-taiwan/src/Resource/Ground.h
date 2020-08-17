#pragma once
#include "Base/File.h"
#include "Base/Res.h"
struct CLMInfo;
struct LMIndex;
struct ColorChannel;
struct GndSurfaceFmt;
struct GndCellFmt17;


class CGndRes : public CRes
{
	struct vtable_t
	{
		void* (CGndRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (CGndRes::* Clone)(void) const;
		bool (CGndRes::* Load)(const char* fName);
		void (CGndRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ public: int m_newVer;
	/* this+276 */ public: unsigned char m_verMajor;
	/* this+277 */ public: unsigned char m_verMinor;
	/* this+280 */ public: int m_width;
	/* this+284 */ public: int m_height;
	/* this+288 */ public: float m_zoom;
	/* this+292 */ public: int m_numTexture;
	/* this+296 */ public: int m_numSurface;
	/* this+300 */ public: int m_numLightmap;
	/* this+304 */ protected: mystd::vector<const char*> m_texNameTable;
	/* this+320 */ protected: CLMInfo* m_lminfo;
	/* this+324 */ protected: LMIndex* m_lmindex;
	/* this+328 */ protected: ColorChannel* m_colorchannel;
	/* this+332 */ protected: GndSurfaceFmt* m_surface;
	/* this+336 */ protected: GndCellFmt17* m_V17cells;
	/* this+340 */ protected: CFile m_fp;

	public: CGndRes::CGndRes(Exemplar __formal, const char* resid, const char* baseDir);
	public: CGndRes::CGndRes(void);
	public: virtual CRes* CGndRes::Clone(void) const;
	public: virtual bool CGndRes::Load(const char* fName);
	public: virtual void CGndRes::Reset(void);
	public: bool CGndRes::LoadGnd(void);
	public: void CGndRes::GetLMInfo(int n, CLMInfo* lminfo);
	//public: const char* GetTextureName(int);
	//public: GndSurfaceFmt* GetSurface(int);
	//public: const GndCellFmt17& GetCells(int);

private:
	static hook_method<CRes* (CGndRes::*)(void) const> CGndRes::_Clone;
	static hook_method<bool (CGndRes::*)(const char* fName)> CGndRes::_Load;
	static hook_method<void (CGndRes::*)(void)> CGndRes::_Reset;
	static hook_method<bool (CGndRes::*)(void)> CGndRes::_LoadGnd;
	static hook_method<void (CGndRes::*)(int n, CLMInfo* lminfo)> CGndRes::_GetLMInfo;
};
