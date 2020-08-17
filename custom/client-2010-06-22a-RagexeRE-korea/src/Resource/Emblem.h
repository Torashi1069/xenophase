#pragma once
#include "Base/Res.h"
#include "Resource/Bitmap.h"


class CEmblemRes : public CRes
{
	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ private: CBitmapRes m_bitmap;

	public: virtual bool CEmblemRes::Load(const char* fName);

public:
	static hook_func<bool (CEmblemRes::*)(const char* fName)> CEmblemRes::_Load;
};
