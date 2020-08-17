#pragma once
#include "3dLib/Texture.h"
#include "Base/Res.h"
#include "std/vector"


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
	/* this+   0 */ public: //CRes baseclass_0;
	/* this+ 272 */ public: unsigned long m_pal[256];
	/* this+1296 */ public: mystd::vector<SprImg*> m_sprites[2];
	/* this+1328 */ public: int m_count;
};
