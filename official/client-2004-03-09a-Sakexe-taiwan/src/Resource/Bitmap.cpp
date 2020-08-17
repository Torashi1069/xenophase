#include "Globals.h"
#include "Base/File.h"
#include "Base/ResMgr.h"
#include "Resource/Bitmap.h"


CBitmapRes::CBitmapRes(Exemplar __formal, const char* resid, const char* baseDir) // line 19 (Resource/Bitmap.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CBitmapRes::CBitmapRes(void) // line 19
{
	m_isAlpha = 0;
	m_data = NULL;
}


hook_method<CRes* (CBitmapRes::*)(void) const> CBitmapRes::_Clone(SAKEXE, "CBitmapRes::Clone");
CRes* CBitmapRes::Clone(void) const // line 19 (Resource/Bitmap.h)
{
	return (this->*_Clone)();

	return new CBitmapRes();
}


hook_method<bool (CBitmapRes::*)(const char* fName)> CBitmapRes::_Load(SAKEXE, "CBitmapRes::Load");
bool CBitmapRes::Load(const char* fName) // line 25
{
	return (this->*_Load)(fName);

	CFile fp;

	if( !fp.CFile::Open(fName, CFile::modeRead) )
		return false;
	
	if( !this->LoadFromBuffer(fName, (const unsigned char*)fp.CFile::GetCurBuf(0), fp.CFile::GetLength()) )
		return false;

	return true;
}


hook_method<bool (CBitmapRes::*)(const char* fName, const unsigned char* buffer, int size)> CBitmapRes::_LoadFromBuffer(SAKEXE, "CBitmapRes::LoadFromBuffer");
bool CBitmapRes::LoadFromBuffer(const char* fName, const unsigned char* buffer, int size) // line 35
{
	return (this->*_LoadFromBuffer)(fName, buffer, size);

	const char* ext = strrchr(fName, '.');
	if( ext == NULL )
		return false;

	if( strcmp(ext, ".bmp") == 0 )
		return this->CBitmapRes::LoadBMPData(buffer, size);

	if( strcmp(ext, ".tga") == 0 )
		return this->CBitmapRes::LoadTGAData(buffer, size);

	if( strcmp(ext, ".jpg") == 0 )
		return this->CBitmapRes::LoadJPGData(buffer, size);

	ErrorMsg("Unsupport fileformat!");
	return false;
}


hook_method<void (CBitmapRes::*)(void)> CBitmapRes::_Reset(SAKEXE, "CBitmapRes::Reset");
void CBitmapRes::Reset(void) // line 54
{
	return (this->*_Reset)();

	delete m_data;
	m_width = 0;
	m_height = 0;
	m_data = NULL;
}


hook_method<unsigned long (CBitmapRes::*)(int x, int y)> CBitmapRes::_GetColor(SAKEXE, "CBitmapRes::GetColor");
unsigned long CBitmapRes::GetColor(int x, int y) // line 64
{
	return (this->*_GetColor)(x, y);

	//TODO
}


hook_method<bool (CBitmapRes::*)(const char* fName)> CBitmapRes::_SetAlphaWithBMP(SAKEXE, "CBitmapRes::SetAlphaWithBMP");
bool CBitmapRes::SetAlphaWithBMP(const char* fName) // line 73
{
	return (this->*_SetAlphaWithBMP)(fName);

	//TODO
}


hook_method<void (CBitmapRes::*)(int x, int y)> CBitmapRes::_CreateNull(SAKEXE, "CBitmapRes::CreateNull");
void CBitmapRes::CreateNull(int x, int y) // line 104
{
	return (this->*_CreateNull)(x, y);

	m_isAlpha = 0;
	m_width = x;
	m_height = y;
	m_data = new unsigned long[x*y];
	memset(m_data, 0xFF, x*y*sizeof(unsigned long));
}


hook_method<bool (CBitmapRes::*)(const unsigned char* bitmap, int size)> CBitmapRes::_LoadBMPData(SAKEXE, "CBitmapRes::LoadBMPData");
bool CBitmapRes::LoadBMPData(const unsigned char* bitmap, int size) // line 116
{
	return (this->*_LoadBMPData)(bitmap, size);

	//TODO
}


hook_method<bool (CBitmapRes::*)(const unsigned char* bitmap, int size)> CBitmapRes::_LoadTGAData(SAKEXE, "CBitmapRes::LoadTGAData");
bool CBitmapRes::LoadTGAData(const unsigned char* bitmap, int size) // line 485
{
	return (this->*_LoadTGAData)(bitmap, size);

	//TODO
}


hook_method<bool (CBitmapRes::*)(const unsigned char* bitmap, int size)> CBitmapRes::_LoadJPGData(SAKEXE, "CBitmapRes::LoadJPGData");
bool CBitmapRes::LoadJPGData(const unsigned char* bitmap, int size) // line 597
{
	return (this->*_LoadJPGData)(bitmap, size);

	//TODO
}
