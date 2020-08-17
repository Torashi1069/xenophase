#include "3dLib/Prim.h"
#include "Base/ResMgr.h"
#include "Resource/Attr.h"
const float infinity = 999999.0f;


C3dAttr::C3dAttr(Exemplar __formal, const char* resid, const char* baseDir) // line 26 (Resource/Attr.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CAttrCell::CAttrCell(void) // line 10
{
}


C3dAttr::C3dAttr(void) // line 15
{
	m_width = 0;
	m_height = 0;
	m_zoom = 5;
}


hook_method<CRes* (C3dAttr::*)(void) const> C3dAttr::_Clone(SAKEXE, "C3dAttr::Clone");
CRes* C3dAttr::Clone(void) const // line 26 (Resource/Attr.h)
{
	return (this->*_Clone)();

	return new C3dAttr();
}


hook_method<void (C3dAttr::*)(int w, int h)> C3dAttr::_Create(SAKEXE, "C3dAttr::Create");
void C3dAttr::Create(int w, int h) // line 22
{
	return (this->*_Create)(w, h);

	//TODO
}


hook_method<bool (C3dAttr::*)(const char* fName)> C3dAttr::_Load(SAKEXE, "C3dAttr::Load");
bool C3dAttr::Load(const char* fName) // line 40
{
	return (this->*_Load)(fName);

	//TODO
}


hook_method<void (C3dAttr::*)(void)> C3dAttr::_Reset(SAKEXE, "C3dAttr::Reset");
void C3dAttr::Reset(void) // line 35
{
	return (this->*_Reset)();

	//TODO
}


hook_method<float (C3dAttr::*)(float x, float z)> C3dAttr::_GetHeight(SAKEXE, "C3dAttr::GetHeight");
float C3dAttr::GetHeight(float x, float z) // line 97
{
	return (this->*_GetHeight)(x, z);

	//TODO
}


//hook_method<CAttrCell* (C3dAttr::*)(int Cellx, int Celly)> C3dAttr::_GetCell(SAKEXE, "C3dAttr::GetCell");
CAttrCell* C3dAttr::GetCell(int Cellx, int Celly) // line ??
{
//	return (this->*_GetCell)(Cellx, Celly);

	return ( Cellx >= 0 && Cellx < m_width && Celly >= 0 && Celly < m_height ) ? &m_cells[Cellx + Celly * m_width] : NULL;
}


hook_method<float (C3dAttr::*)(const ray3d& ray, int x, int y)> C3dAttr::_RayTest(SAKEXE, "C3dAttr::RayTest");
float C3dAttr::RayTest(const ray3d& ray, int x, int y) // line 119-148
{
	return (this->*_RayTest)(ray, x, y);

	CAttrCell* cell = this->C3dAttr::GetCell(x, y);
	if( cell == NULL )
		return 0.0;

	float nearest = infinity;

	x -= m_width / 2;
	y -= m_height / 2;
	vector3d vec[4];

	vec[0].x = (float) x * m_zoom;
	vec[0].y = (float) cell->h1;
	vec[0].z = (float) y * m_zoom;

	vec[1].x = (float) (x + 1) * m_zoom;
	vec[1].y = (float) cell->h2;
	vec[1].z = (float) y * m_zoom;

	vec[2].x = (float) x * m_zoom;
	vec[2].y = (float) cell->h3;
	vec[2].z = (float) (y + 1) * m_zoom;

	vec[3].x = (float) (x + 1) * m_zoom;
	vec[3].y = (float) cell->h4;
	vec[3].z = (float) (y + 1) * m_zoom;

	float u, v, t;
	if( CheckRayTriIntersect(ray, vec[0], vec[1], vec[2], &u, &v, &t) && t < nearest )
		nearest = t;
	if( CheckRayTriIntersect(ray, vec[1], vec[3], vec[2], &u, &v, &t) && t < nearest )
		nearest = t;

	return nearest;
}


hook_method<void (C3dAttr::*)(int Type, int Cellx, int Celly)> C3dAttr::_SetCellInfo(SAKEXE, "C3dAttr::SetCellInfo");
void C3dAttr::SetCellInfo(int Type, int Cellx, int Celly) // line 54 (Attr.h)
{
	return (this->*_SetCellInfo)(Type, Cellx, Celly);

	this->C3dAttr::GetCell(Cellx, Celly)->flag = Type; //FIXME: possible null pointer write // inlined
}
