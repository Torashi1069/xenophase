#pragma once


class CSkinMgr
{
	/* this+ 0 */ public: //const CSkinMgr::`vftable';
	/* this+ 4 */ public: mystd::string m_savedSkinName;
	/* this+20 */ private: mystd::vector<mystd::string> m_skinFolderNameList;
	/* this+24 */ private: mystd::vector<mystd::string> m_skinNameList;
	/* this+52 */ private: mystd::vector<int> m_isZipSkinList;
	/* this+68 */ private: mystd::vector<int> m_isZipSkinExtractedList;
	/* this+84 */ private: int m_curSkinNum;

	public: CSkinMgr::CSkinMgr(void);
	public: virtual CSkinMgr::~CSkinMgr(void);
	public: void CSkinMgr::Init(void);
	public: int CSkinMgr::GetNumSkin(void);
	//public: void CSkinMgr::SetCurrentSkinNum(int);
	public: int CSkinMgr::GetCurrentSkinNum(void);
	public: const char* CSkinMgr::GetSkinCurrentFolderName(void);
	//public: const char* CSkinMgr::GetSkinFolderName(int);
	//public: const char* CSkinMgr::GetSkinName(int);
	//public: const char* CSkinMgr::GetCurrentSkinName();
	public: void CSkinMgr::GetColorChipColor(int x, int y, unsigned long& r, unsigned long& g, unsigned long& b);
	public: void CSkinMgr::ExtractFilesIfZipSkin(void);
	public: void CSkinMgr::DeleteTmpSkinFolder(void);

private:
	static hook_method<void (CSkinMgr::*)(void)> CSkinMgr::_Init;
	static hook_method<int (CSkinMgr::*)(void)> CSkinMgr::_GetNumSkin;
	static hook_method<int (CSkinMgr::*)(void)> CSkinMgr::_GetCurrentSkinNum;
	static hook_method<const char* (CSkinMgr::*)(void)> CSkinMgr::_GetSkinCurrentFolderName;
	static hook_method<void (CSkinMgr::*)(int x, int y, unsigned long& r, unsigned long& g, unsigned long& b)> CSkinMgr::_GetColorChipColor;
	static hook_method<void (CSkinMgr::*)(void)> CSkinMgr::_ExtractFilesIfZipSkin;
	static hook_method<void (CSkinMgr::*)(void)> CSkinMgr::_DeleteTmpSkinFolder;
};
