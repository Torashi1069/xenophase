#include "Skin.h"


// globals
CSkinMgr& g_skinMgr = VTOR<CSkinMgr>(SymDB::Find("g_skinMgr"));


hook_func<void (CSkinMgr::*)(void)> CSkinMgr::_Init("CSkinMgr::Init");
void CSkinMgr::Init()
{
	return (this->*_Init)();

	//TODO
}


int CSkinMgr::GetNumSkin()
{
	return m_skinFolderNameList.size();
}


int CSkinMgr::GetCurrentSkinNum()
{
	return m_curSkinNum;
}


hook_func<const char* (CSkinMgr::*)()> CSkinMgr::_GetSkinCurrentFolderName("CSkinMgr::GetSkinCurrentFolderName");
const char* CSkinMgr::GetSkinCurrentFolderName()
{
	return (this->*_GetSkinCurrentFolderName)();

	//TODO
}


hook_func<void (CSkinMgr::*)(int x, int y, unsigned long& r, unsigned long& g, unsigned long& b)> CSkinMgr::_GetColorChipColor("CSkinMgr::GetColorChipColor");
void CSkinMgr::GetColorChipColor(int x, int y, unsigned long& r, unsigned long& g, unsigned long& b)
{
	return (this->*_GetColorChipColor)(x, y, r, g, b);

	//TODO
}


hook_func<void (CSkinMgr::*)()> CSkinMgr::_ExtractFilesIfZipSkin("CSkinMgr::ExtractFilesIfZipSkin");
void CSkinMgr::ExtractFilesIfZipSkin()
{
	return (this->*_ExtractFilesIfZipSkin)();

	//TODO
}
