#pragma once
#include "Base/Res.h"


class CPaletteRes : public CRes
{
	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ public: unsigned long m_pal[256];
};
C_ASSERT( sizeof CPaletteRes == 1296 );
