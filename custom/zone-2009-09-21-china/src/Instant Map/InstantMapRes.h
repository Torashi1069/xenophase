#pragma once
#include "MapRes.h"
#include "std/string"


class CInstantMapRes : public CMapRes
{
public:
	struct vtable_t //const CInstantMapRes::`vftable'
	{
		const bool (CInstantMapRes::* isInstantMap)(void) const;
		void* (CInstantMapRes::* scalar_deleting_destructor)(unsigned int);
		int (CMapRes::* Load)(const char*, int, int);
		void (CMapRes::* Reset)(void);
		void (CMapRes::* OnTimer)(void);
		unsigned long (CMapRes::* GetGDID)(void);
		int (CMapRes::* AddCharacter)(int, int, CCharacter *);
		mystd::string (CInstantMapRes::* GetLoadFileName)(void);
		bool (CMapRes::* IsBattleField)(void);
		bool (CMapRes::* IsAgit)(void);
	};

	/* this+0x0   */ //CMapRes
	/* this+0x71C */ private: bool m_bOK;
	
	public: CInstantMapRes::CInstantMapRes(const int in_mapType);
	public: virtual CInstantMapRes::~CInstantMapRes(void);
	private: virtual mystd::string CInstantMapRes::GetLoadFileName(void);
	public: virtual const bool CInstantMapRes::isInstantMap(void) const;
	//public: const bool CInstantMapRes::isOK() const;

private:
	static hook_method<mystd::string (CInstantMapRes::*)(void)> CInstantMapRes::_GetLoadFileName;
	static hook_method<const bool (CInstantMapRes::*)(void) const> CInstantMapRes::_isInstantMap;
};
