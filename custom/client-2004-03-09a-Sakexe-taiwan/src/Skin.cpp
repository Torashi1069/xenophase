#include "Globals.h"
#include "Skin.h"
#include "Base/Util.h"


CSkinMgr::CSkinMgr(void) // line 18
{
	m_savedSkinName = s_basicSkinName;
}


CSkinMgr::~CSkinMgr(void) // line 23
{
	this->CSkinMgr::DeleteTmpSkinFolder();
}


hook_method<void (CSkinMgr::*)(void)> CSkinMgr::_Init(SAKEXE, "CSkinMgr::Init");
void CSkinMgr::Init(void) // line 28
{
	return (this->*_Init)();

	//TODO
}


//hook_method<int (CSkinMgr::*)(void)> CSkinMgr::_GetNumSkin(SAKEXE, "CSkinMgr::GetNumSkin");
int CSkinMgr::GetNumSkin(void) // ???
{
//	return (this->*_GetNumSkin)();

	return m_skinFolderNameList.size();
}


//hook_method<int (CSkinMgr::*)(void)> CSkinMgr::_GetCurrentSkinNum(SAKEXE, "CSkinMgr::GetCurrentSkinNum");
int CSkinMgr::GetCurrentSkinNum(void) // ???
{
//	return (this->*_GetCurrentSkinNum)();

	return m_curSkinNum;
}


hook_method<const char* (CSkinMgr::*)(void)> CSkinMgr::_GetSkinCurrentFolderName(SAKEXE, "CSkinMgr::GetSkinCurrentFolderName");
const char* CSkinMgr::GetSkinCurrentFolderName(void) // line 159
{
	return (this->*_GetSkinCurrentFolderName)();

	return( m_curSkinNum != -1 ) ? m_skinFolderNameList[m_curSkinNum].c_str() : s_basicSkinName.c_str();
}


hook_method<void (CSkinMgr::*)(int x, int y, unsigned long& r, unsigned long& g, unsigned long& b)> CSkinMgr::_GetColorChipColor(SAKEXE, "CSkinMgr::GetColorChipColor");
void CSkinMgr::GetColorChipColor(int x, int y, unsigned long& r, unsigned long& g, unsigned long& b)
{
	return (this->*_GetColorChipColor)(x, y, r, g, b);

	//TODO
}


hook_method<void (CSkinMgr::*)(void)> CSkinMgr::_ExtractFilesIfZipSkin(SAKEXE, "CSkinMgr::ExtractFilesIfZipSkin");
void CSkinMgr::ExtractFilesIfZipSkin(void) // line 166
{
	return (this->*_ExtractFilesIfZipSkin)();

	//TODO
}


hook_method<void (CSkinMgr::*)(void)> CSkinMgr::_DeleteTmpSkinFolder(SAKEXE, "CSkinMgr::DeleteTmpSkinFolder");
void CSkinMgr::DeleteTmpSkinFolder(void)
{
	return (this->*_DeleteTmpSkinFolder)();

	char tmp[2048];
	sprintf(tmp, "%s\\_tmpskin_", g_baseDir3);

	if( !access(tmp, 0) )
		DeleteDirectory(tmp);
}
