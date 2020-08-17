#pragma once
#include "common.h" // CharPrtLess
#include "Base/Res.h"


class CResMgr
{
public:
	CResMgr();
	~CResMgr();

public:
	void Reset();
	CRes* Get(const char* fNameInput);
	int IsExist(const char* fNameInput);
	void Unload(CRes* res);
	void UnloadAll();
	void UnloadRarelyUsedRes();
	void UnloadUnlockedRes();
	void UnloadResByExt(const char* ext);
	void RegisterType(const char* resId, const char* baseDir, CRes* t);
	void ReadResNameTable(const char* resNameTable);
	void PrintRes(const char* fileName);

private:
	CRes* FindRes(int ext, const char* name);
	void MakeOpenName(char* openName, const char* fName, const char* typeDir);
	const char* ExtractExt(const char* fName);
	int FindExtIndex(const char* ext_str);
	const char* GetRealResName(const char* resName);
	char* ToLower(char* text);

private:
	typedef mystd::map<const char*, int, CharPrtLess> ext_map;
	typedef mystd::map<const char*, int, CharPrtLess>::iterator ext_map_iter;
	typedef mystd::pair<const char* const, int> ext_map_value;

	typedef mystd::map<CHash*, CRes*, ResPtrLess> res_map;
	typedef mystd::map<CHash*, CRes*, ResPtrLess>::iterator res_map_iter;
	typedef mystd::pair<CHash* const, CRes*> res_map_value;

private:
	/* this+  0 */ ext_map m_resExt;
	/* this+ 16 */ mystd::vector<const char*> m_typeDir;
	/* this+ 32 */ mystd::vector<CRes*> m_objTypes;
	/* this+ 48 */ mystd::vector<res_map> m_fileList;
	/* this+ 64 */ RTL_CRITICAL_SECTION m_GetResSection;
	/* this+ 88 */ mystd::map<mystd::string,mystd::string> m_realResName;
public:
	/* this+104 */ unsigned long m_usedForSprTexture;
	/* this+108 */ unsigned long m_usedForModelTexture;
	/* this+112 */ unsigned long m_usedForGNDTexture;
	/* this+116 */ unsigned long m_usedForSprite;
	/* this+120 */ unsigned long m_usedForSprAction;
	/* this+124 */ unsigned long m_usedForGAT;
	/* this+128 */ unsigned long m_usedForGND;
	/* this+132 */ unsigned long m_usedForIMF;
	/* this+136 */ unsigned long m_usedForModel;
	/* this+140 */ unsigned long m_ResMemAmount;
	/* this+144 */ unsigned long m_ResSprAmount;
	/* this+148 */ unsigned long m_ResTexAmount;
	/* this+152 */ unsigned long m_ResGatAmount;
	/* this+156 */ unsigned long m_ResGndAmount;
	/* this+160 */ unsigned long m_ResRswAmount;
	/* this+164 */ unsigned long m_ResModAmount;
	/* this+168 */ unsigned long m_ResWavAmount;
};


CResMgr& g_resMgr();
