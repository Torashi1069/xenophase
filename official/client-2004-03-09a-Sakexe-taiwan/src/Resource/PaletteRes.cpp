#include "Globals.h"
#include "Base/File.h"
#include "Base/ResMgr.h"
#include "Resource/PaletteRes.h"


CPaletteRes::CPaletteRes(Exemplar __formal, const char* resid, const char* baseDir) // line 17 (Resource/PaletteRes.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CPaletteRes::CPaletteRes(void) // line 9
{
}


hook_method<CRes* (CPaletteRes::*)(void) const> CPaletteRes::_Clone(SAKEXE, "CPaletteRes::Clone");
CRes* CPaletteRes::Clone(void) const // line 17 (Resource/PaletteRes.h)
{
	return (this->*_Clone)();

	return new CPaletteRes();
}


hook_method<bool (CPaletteRes::*)(const char* fName)> CPaletteRes::_Load(SAKEXE, "CPaletteRes::Load");
bool CPaletteRes::Load(const char* fName) // line 17
{
	return (this->*_Load)(fName);

	CFile fp;
	if( !fp.CFile::Open(fName, 0) )
	{
		ErrorMsg((mystd::string("CPaletteRes :: Cannot find File : ") + fName).c_str());
		return false;
	}

	PALETTEENTRY paletteEntry[256];
	fp.CFile::Read(paletteEntry, 1024);
	g_3dDevice.C3dDevice::ConvertPalette(m_pal, paletteEntry, 256);

	fp.CFile::Close();
	return true;
}


hook_method<void (CPaletteRes::*)(void)> CPaletteRes::_Reset(SAKEXE, "CPaletteRes::Reset");
void CPaletteRes::Reset(void) // line 14
{
	return (this->*_Reset)();

	;
}
