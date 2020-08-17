#include "Resource/Attr.h"


//hook_func<CAttrCell* (C3dAttr::*)(int Cellx, int Celly)> C3dAttr::_GetCell("C3dAttr::GetCell");
CAttrCell* C3dAttr::GetCell(int Cellx, int Celly)
{
//	return (this->*_GetCell)(Cellx, Celly);

	return ( Cellx >= 0 && Cellx < m_width && Celly >= 0 && Celly < m_height ) ? &m_cells[Cellx + Celly * m_width] : NULL;
}


hook_func<float (C3dAttr::*)(const ray3d& ray, int x, int y)> C3dAttr::_RayTest("C3dAttr::RayTest");
float C3dAttr::RayTest(const ray3d& ray, int x, int y)
{
	return (this->*_RayTest)(ray, x, y);
}
