#pragma once
#include "Base/Res.h"
#include "std/vector"
struct ray3d;


struct CAttrCell
{
	/* this+ 0 */ float h1;
	/* this+ 4 */ float h2;
	/* this+ 8 */ float h3;
	/* this+12 */ float h4;
	/* this+16 */ int flag;
};


class C3dAttr : public CRes
{
	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ public: int m_width;
	/* this+276 */ public: int m_height;
	/* this+280 */ public: int m_zoom;
	/* this+284 */ public: mystd::vector<CAttrCell> m_cells;

	public: CAttrCell* C3dAttr::GetCell(int Cellx, int Celly);
	public: float C3dAttr::RayTest(const ray3d& ray, int x, int y);

public:
	static hook_func<CAttrCell* (C3dAttr::*)(int Cellx, int Celly)> C3dAttr::_GetCell;
	static hook_func<float (C3dAttr::*)(const ray3d& ray, int x, int y)> C3dAttr::_RayTest;
};
C_ASSERT( sizeof C3dAttr == 300 );
