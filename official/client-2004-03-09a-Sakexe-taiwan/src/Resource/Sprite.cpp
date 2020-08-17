#include "Base/ResMgr.h"
#include "Resource/Sprite.h"


CSprRes::CSprRes(Exemplar __formal, const char* resid, const char* baseDir) // line 30 (Resource/Sprite.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CSprRes::CSprRes(void) // line 23
{
	m_count = 0;
}


hook_method<CRes* (CSprRes::*)(void) const> CSprRes::_Clone(SAKEXE, "CSprRes::Clone");
CRes* CSprRes::Clone(void) const // line 30 (Resource/Sprite.h)
{
	return (this->*_Clone)();

	return new CSprRes();
}


hook_method<bool (CSprRes::*)(const char* fName)> CSprRes::_Load(SAKEXE, "CSprRes::Load");
bool CSprRes::Load(const char* fName) // line 48
{
	return (this->*_Load)(fName);

	//TODO
}


hook_method<void (CSprRes::*)(void)> CSprRes::_Reset(SAKEXE, "CSprRes::Reset");
void CSprRes::Reset(void) // line 28
{
	return (this->*_Reset)();

	//TODO
}
