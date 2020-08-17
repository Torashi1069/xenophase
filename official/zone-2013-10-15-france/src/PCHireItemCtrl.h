#pragma once
#include "Enum.h"
class CPC;
class IVItItem;


class CPCHireItemCtrl
{
	enum
	{
		MILISECONDperSECOND = 1000,
		MILISECONDperMINUTE = 60000,
		MILISECONDperHOUR   = 3600000,

		SECONDperMINUTE = 60,
		SECONDperHOUR   = 3600,
		SECONDperDAY    = 86400,
	};

	class CRequest
	{
	public:
		/* this+0 */ enumInventoryType m_InventoryType;
		/* this+4 */ unsigned long m_RequestCheckTime;
		/* this+8 */ int m_ErrorCount;

	public:
		CRequest(const enumInventoryType in_InventoryType, const unsigned long in_RequestCheckTime) : m_InventoryType(in_InventoryType), m_RequestCheckTime(in_RequestCheckTime), m_ErrorCount(0) { }
	};

private:
	/* this+ 0 */ //const CPCHireItemCtrl::`vftable';
	typedef std::map<__int64,CRequest> REQUESTCONTAINER;
	typedef std::map<__int64,CRequest>::iterator REQUESTCONTAINERITOR;
	/* this+ 4 */ REQUESTCONTAINER m_ReqContainer;
	/* this+20 */ CPC* m_cpMyOwnerPC;

private:
	bool RequestProcess(const __int64 in_ItemUID, CRequest& in_Request);
	DWORD GetNexCheckTime(const time_t in_CurDate, const DWORD in_CurTime, const IVItItem* const in_pItem) const;

protected:
	void Init(CPC* in_cpOwnerPC);
	void Reset();
	void Process();

public:
	void RequestAdd(const enumInventoryType in_InventoryType, IVItItem* in_pItem);
	void RequestRemove(IVItItem* const in_pItem);

public:
	CPCHireItemCtrl();
	virtual ~CPCHireItemCtrl();

	friend class CPC;
};
