#pragma once
#include "std/string"
#include "Instant Map/IMWTWork.h"
class CInstantMapRes;


class CIMWTWork_LoadMap : public CIMWTWork
{
public:
	struct vtable_t //const CIMWTWork_LoadMap::`vftable'
	{
		void (CIMWTWork_LoadMap::* Run)(void);
		void* (CIMWTWork_LoadMap::* vector_deleting_destructor)(unsigned int);
	};

	enum enumResult
	{
		RESULT_NONE    = 0x0,
		RESULT_SUCCESS = 0x1,
		RESULT_ERROR   = 0x2,
	};

	// this+0x0  */ //CIMWTWork
	/* this+0x8  */ private: CInstantMapRes* const m_cpInstantMapRes;
	/* this+0xC  */ private: bool m_bOK;
	/* this+0x10 */ private: const mystd::string m_MapName;
	/* this+0x2C */ private: const int m_MapID;
	/* this+0x30 */ private: const int m_MapType;
	/* this+0x34 */ private: enum CIMWTWork_LoadMap::enumResult m_Result;

	//public: const bool CIMWTWork_LoadMap::isOK(void);
	//public: CInstantMapRes* CIMWTWork_LoadMap::GetMapResPtr(void);
	//public: const enum CIMWTWork_LoadMap::enumResult GetResult(void);
	public: virtual void CIMWTWork_LoadMap::Run(void);
	public: CIMWTWork_LoadMap::CIMWTWork_LoadMap(const int in_MapID, const mystd::string in_MapName, const int in_MapType, CInstantMapRes* const in_cpInstantMapRes);
	public: virtual CIMWTWork_LoadMap::~CIMWTWork_LoadMap(void);

private:
	static hook_method<void (CIMWTWork_LoadMap::*)(void)> CIMWTWork_LoadMap::_Run;
};
