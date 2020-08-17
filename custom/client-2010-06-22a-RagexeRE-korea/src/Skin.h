#pragma once


class CSkinMgr
{
public:
	void Init();
	int GetNumSkin();
	int GetCurrentSkinNum();
	const char* GetSkinCurrentFolderName();
	void GetColorChipColor(int x, int y, unsigned long& r, unsigned long& g, unsigned long& b);
	void ExtractFilesIfZipSkin();

private:
	/* this+ 0 */ BYTE dummy_0[20];
	/* this+20 */ int m_curSkinNum;
	/* this+24 */ BYTE field_24[16];
	/* this+40 */ mystd::vector<mystd::string> m_skinFolderNameList;
	/* this+56 */ //TODO

private:
	static hook_func<void (CSkinMgr::*)()> CSkinMgr::_Init;
	static hook_func<const char* (CSkinMgr::*)()> CSkinMgr::_GetSkinCurrentFolderName;
	static hook_func<void (CSkinMgr::*)(int x, int y, unsigned long& r, unsigned long& g, unsigned long& b)> CSkinMgr::_GetColorChipColor;
	static hook_func<void (CSkinMgr::*)()> CSkinMgr::_ExtractFilesIfZipSkin;
};


extern CSkinMgr& g_skinMgr;
