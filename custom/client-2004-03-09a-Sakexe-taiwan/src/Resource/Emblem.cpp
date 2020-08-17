#include "Globals.h"
#include "Base/File.h"
#include "Base/ResMgr.h"
#include "Resource/Emblem.h"


CEmblemRes::CEmblemRes(Exemplar __formal, const char* resid, const char* baseDir) // line 10 (Resource/Emblem.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CEmblemRes::CEmblemRes(void) // line 9
{
}


hook_method<CRes* (CEmblemRes::*)(void) const> CEmblemRes::_Clone(SAKEXE, "CEmblemRes::Clone");
CRes* CEmblemRes::Clone(void) const // line 10 (Resource/Emblem.h)
{
	return (this->*_Clone)();

	return new CEmblemRes();
}


hook_method<bool (CEmblemRes::*)(const char* fName)> CEmblemRes::_Load(SAKEXE, "CEmblemRes::Load");
bool CEmblemRes::Load(const char* fName) // line 13
{
	return (this->*_Load)(fName);

	CFile fp;
	if( !fp.CFile::Open(fName, 0) )
		return false;

	unsigned char emblem[8192];
	unsigned char bitmap[8192];
	int bitmapSize = sizeof(emblem);

	fp.CFile::Read(emblem, fp.CFile::GetLength()); //FIXME: no size check
	if( !this->CEmblemRes::UnCompressEmblem(bitmap, *(unsigned long*)&bitmapSize, emblem, fp.CFile::GetLength()) )
		return false;
		
	if( bitmapSize == sizeof(bitmap) || !m_bitmap.LoadFromBuffer("_emblem.bmp", bitmap, bitmapSize) )
	{// fill with dummy data
		m_bitmap.CBitmapRes::CreateNull(24, 24);
		return true;
	}

	m_bitmap.m_width = max(m_bitmap.m_width, 24);
	m_bitmap.m_height = max(m_bitmap.m_height, 24);
	return true;
}


hook_method<void (CEmblemRes::*)(void)> CEmblemRes::_Reset(SAKEXE, "CEmblemRes::Reset");
void CEmblemRes::Reset(void) // line 47
{
	return (this->*_Reset)();

	m_bitmap.Reset();
}


//hook_method<CBitmapRes* (CEmblemRes::*)(void)> CEmblemRes::_GetBitmap(SAKEXE, "CEmblemRes::GetBitmap");
CBitmapRes* CEmblemRes::GetBitmap(void) // line ??
{
//	return (this->*_GetBitmap)();

	return &m_bitmap;
}


hook_method<bool (CEmblemRes::*)(unsigned char* bitmap, unsigned long& bitmapSize, unsigned char* emblem, int emSize)> CEmblemRes::_UnCompressEmblem(SAKEXE, "CEmblemRes::UnCompressEmblem");
bool CEmblemRes::UnCompressEmblem(unsigned char* bitmap, unsigned long& bitmapSize, unsigned char* emblem, int emSize) // line 51
{// uses exceptions!
	return (this->*_UnCompressEmblem)(bitmap, bitmapSize, emblem, emSize);

	//TODO
}


hook_method<void (CEmblemRes::*)(const char* fName)> CEmblemRes::_OnLoadError(SAKEXE, "CEmblemRes::OnLoadError");
void CEmblemRes::OnLoadError(const char* fName) // line 18 (Resource/Emblem.h)
{
	return (this->*_OnLoadError)(fName);

	;
}
