#include "Base/ResMgr.h"
#include "Resource/Ground.h"


CGndRes::CGndRes(Exemplar __formal, const char* resid, const char* baseDir) // line 67 (Resource/Ground.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CGndRes::CGndRes(void) // line 62
{
	m_width = 0;
	m_height = 0;
	m_newVer = 0;
	m_zoom = 10.0;
}


hook_method<CRes* (CGndRes::*)(void) const> CGndRes::_Clone(SAKEXE, "CGndRes::Clone");
CRes* CGndRes::Clone(void) const // line 67 (Resource/Ground.h)
{
	return (this->*_Clone)();

	return new CGndRes();
}


hook_method<bool (CGndRes::*)(const char* fName)> CGndRes::_Load(SAKEXE, "CGndRes::Load");
bool CGndRes::Load(const char* fName) // line 71
{
	return (this->*_Load)(fName);

	//TODO
}


hook_method<void (CGndRes::*)(void)> CGndRes::_Reset(SAKEXE, "CGndRes::Reset");
void CGndRes::Reset(void) // line 93
{
	return (this->*_Reset)();

	m_texNameTable.clear();
	m_lminfo = NULL;
	m_surface = NULL;
	m_V17cells = NULL;
}


hook_method<bool (CGndRes::*)(void)> CGndRes::_LoadGnd(SAKEXE, "CGndRes::LoadGnd");
bool CGndRes::LoadGnd(void) // line 100
{
	return (this->*_LoadGnd)();

	//TODO
}


hook_method<void (CGndRes::*)(int n, CLMInfo* lminfo)> CGndRes::_GetLMInfo(SAKEXE, "CGndRes::GetLMInfo");
void CGndRes::GetLMInfo(int n, CLMInfo* lminfo) // line 172
{
	return (this->*_GetLMInfo)(n, lminfo);

	//TODO
}
