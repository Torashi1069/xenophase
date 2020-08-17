#pragma once
#include "Base/Hash.h"
#include "std/map"
#include "std/string"
#include "std/vector"


class Exemplar
{
	/* this+0 */ char dummy;
};


class CRes
{
	/* this+ 0 */ private: //const CRes::`vftable';
	/* this+ 4 */ protected: int m_lockCnt;
	/* this+ 8 */ protected: unsigned long m_timeStamp;
	/* this+12 */ protected: int m_extIndex;
	/* this+16 */ protected: CHash m_fName;

	struct vtable_t
	{
		void* (CRes::* scalar_deleting_destructor)(unsigned int __flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (CRes::* Clone)(void); // __purecall
		bool (CRes::* Load)(const char* fName); // __purecall
		void (CRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	public: CRes::CRes(void);
	public: virtual CRes::~CRes(void);
	public: virtual bool CRes::LoadFromBuffer(const char* fName, const unsigned char* buffer, int size);
	public: const char* CRes::GetName(void);
	protected: virtual CRes* CRes::Clone(void) = 0;
	protected: virtual bool CRes::Load(const char* fName) = 0;
	protected: virtual void CRes::Reset(void);
	protected: virtual void CRes::OnLoadError(const char* fName);
	public: int CRes::Lock();
	public: int CRes::Unlock();

public:
	static hook_func<bool (CRes::*)(const char* fName, const unsigned char* buffer, int size)> CRes::_LoadFromBuffer;
	static hook_func<void (CRes::*)(void)> CRes::_Reset;
};
C_ASSERT( sizeof CRes == 272 );


struct ResPtrLess : public std::binary_function<CHash *,CHash *,bool>
{
	public: bool ResPtrLess::operator()(CHash* left, CHash* right) const
	{
		if( *left == *right )
			return true;

		return( *left < *right );
	}
};


class CResMgr
{
	/* this+  0 */ private: mystd::map<const char*,int> m_resExt;
	/* this+ 16 */ private: mystd::vector<const char*> m_typeDir;
	/* this+ 32 */ private: mystd::vector<CRes*> m_objTypes;
	/* this+ 48 */ private: mystd::vector<mystd::map<CHash*,CRes*,ResPtrLess>> m_fileList;
	/* this+ 64 */ private: RTL_CRITICAL_SECTION m_GetResSection;
	/* this+ 88 */ private: mystd::map<mystd::string,mystd::string> m_realResName;
	/* this+104 */ public: unsigned long m_usedForSprTexture;
	/* this+108 */ public: unsigned long m_usedForModelTexture;
	/* this+112 */ public: unsigned long m_usedForGNDTexture;
	/* this+116 */ public: unsigned long m_usedForSprite;
	/* this+120 */ public: unsigned long m_usedForSprAction;
	/* this+124 */ public: unsigned long m_usedForGAT;
	/* this+128 */ public: unsigned long m_usedForGND;
	/* this+132 */ public: unsigned long m_usedForIMF;
	/* this+136 */ public: unsigned long m_usedForModel;
	/* this+140 */ public: unsigned long m_ResMemAmount;
	/* this+144 */ public: unsigned long m_ResSprAmount;
	/* this+148 */ public: unsigned long m_ResTexAmount;
	/* this+152 */ public: unsigned long m_ResGatAmount;
	/* this+156 */ public: unsigned long m_ResGndAmount;
	/* this+160 */ public: unsigned long m_ResRswAmount;
	/* this+164 */ public: unsigned long m_ResModAmount;
	/* this+168 */ public: unsigned long m_ResWavAmount;

	public: void CResMgr::Reset(void);
	public: CRes* CResMgr::Get(const char* fNameInput);
	public: int CResMgr::IsExist(const char* fNameInput);
	public: void CResMgr::ReadResNameTable(const char* resNameTable);
	public: void CResMgr::RegisterType(const char* resId, const char* baseDir, CRes* t);

public:
	static hook_func<void (CResMgr::*)(void)> CResMgr::_Reset;
	static hook_func<CRes* (CResMgr::*)(const char* fNameInput)> CResMgr::_Get;
	static hook_func<int (CResMgr::*)(const char* fNameInput)> CResMgr::_IsExist;
	static hook_func<void (CResMgr::*)(const char* resNameTable)> CResMgr::_ReadResNameTable;
	static hook_func<void (CResMgr::*)(const char* resId, const char* baseDir, CRes* t)> CResMgr::_RegisterType;
};
C_ASSERT( sizeof CResMgr == 172 );


CResMgr& __cdecl g_resMgr();
