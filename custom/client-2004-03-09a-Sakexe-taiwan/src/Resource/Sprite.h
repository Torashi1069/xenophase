#pragma once
#include "3dLib/Texture.h"
#include "Base/Res.h"


struct SprImg
{
	/* this +0 */ short width;
	/* this +2 */ short height;
	/* this+ 4 */ short isHalfW;
	/* this+ 6 */ short isHalfH;
	/* this+ 8 */ CTexture* tex;
	/* this+12 */ unsigned char* m_8bitImage;
};


class CSprRes : public CRes
{
	struct vtable_t
	{
		void* (CSprRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (CSprRes::* Clone)(void) const;
		bool (CSprRes::* Load)(const char* fName);
		void (CSprRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	/* this+   0 */ public: //CRes baseclass_0;
	/* this+ 272 */ public: unsigned long m_pal[256];
	/* this+1296 */ public: mystd::vector<SprImg*> m_sprites[2];
	/* this+1328 */ public: int m_count;

	public: CSprRes::CSprRes(Exemplar __formal, const char* resid, const char* baseDir);
	public: CSprRes::CSprRes(void);
	public: virtual CRes* CSprRes::Clone(void) const;
	public: virtual bool CSprRes::Load(const char* fName);
	public: virtual void CSprRes::Reset(void);
	//public: void Unload();
	//public: unsigned char* CSprRes::ZeroCompression(unsigned char *, int, int, unsigned short &);
	//public: unsigned char* CSprRes::ZeroDecompression(unsigned char *, int, int);
	//public: unsigned char* CSprRes::HalfImage(unsigned char *, int, int, int, int);

private:
	static hook_method<CRes* (CSprRes::*)(void) const> CSprRes::_Clone;
	static hook_method<bool (CSprRes::*)(const char* fName)> CSprRes::_Load;
	static hook_method<void (CSprRes::*)(void)> CSprRes::_Reset;
};
