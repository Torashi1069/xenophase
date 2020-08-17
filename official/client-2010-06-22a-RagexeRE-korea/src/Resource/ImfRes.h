#pragma once
#include "Base/Res.h"
#include "std/vector"


struct ImfData
{
	/* this+ 0 */ mystd::vector<int> m_Priority;
	/* this+16 */ mystd::vector<int> m_cx;
	/* this+32 */ mystd::vector<int> m_cy;
};


class CImfRes : public CRes
{
	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ protected: mystd::vector<mystd::vector<ImfData>> m_ImfData;
	/* this+288 */ protected: int m_maxAction[15];
	/* this+348 */ protected: int m_maxMotion[15][104];

	public: int CImfRes::GetLayer(int Priority, int Act, int Mot);

public:
	static hook_func<int (CImfRes::*)(int Priority, int Act, int Mot)> CImfRes::_GetLayer;
};
