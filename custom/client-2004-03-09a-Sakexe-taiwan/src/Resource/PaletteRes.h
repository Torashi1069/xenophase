#pragma once
#include "Base/Res.h"


class CPaletteRes : public CRes
{
	struct vtable_t
	{
		void* (CPaletteRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (CPaletteRes::* Clone)(void) const;
		bool (CPaletteRes::* Load)(const char* fName);
		void (CPaletteRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ public: unsigned long m_pal[256];

	public: CPaletteRes::CPaletteRes(Exemplar __formal, const char* resid, const char* baseDir);
	public: CPaletteRes::CPaletteRes(void);
	public: virtual CRes* CPaletteRes::Clone(void) const;
	public: virtual bool CPaletteRes::Load(const char* fName);
	public: virtual void CPaletteRes::Reset(void);
	//public: void Unload(void);

private:
	static hook_method<CRes* (CPaletteRes::*)(void) const> CPaletteRes::_Clone;
	static hook_method<bool (CPaletteRes::*)(const char* fName)> CPaletteRes::_Load;
	static hook_method<void (CPaletteRes::*)(void)> CPaletteRes::_Reset;
};
