#pragma once
#include "std/map"
#include "enum.hpp"
class CPC;
struct IVItItem;


class CPCHireItemCtrl
{
public:
	enum
	{
		MILISECONDperSECOND = 1000,
		MILISECONDperMINUTE = 60000,
		MILISECONDperHOUR   = 3600000,
		SECONDperMINUTE     = 60,
		SECONDperHOUR       = 3600,
		SECONDperDAY        = 86400,
	};

	class CRequest
	{
	public:
		/* this+0x0 */ enum enumInventoryType m_InventoryType;
		/* this+0x4 */ unsigned long m_RequestCheckTime;
		/* this+0x8 */ int m_ErrorCount;

		//public: void CRequest::CRequest(const enum enumInventoryType, const unsigned long);
	};

	/* this+0x0  */ void* vtable;
	/* this+0x4  */ mystd::map<__int64,CPCHireItemCtrl::CRequest> m_ReqContainer;
	/* this+0x10 */ CPC* m_cpMyOwnerPC;

	private: bool CPCHireItemCtrl::RequestProcess(const __int64 in_ItemUID, CPCHireItemCtrl::CRequest& in_Request);
	private: unsigned long CPCHireItemCtrl::GetNexCheckTime(const long in_CurDate, const unsigned long in_CurTime, const IVItItem* const in_pItem);
	protected: void CPCHireItemCtrl::Init(CPC* in_cpOwnerPC);
	protected: void CPCHireItemCtrl::Reset(void);
	protected: void CPCHireItemCtrl::Process(void);
	public: void CPCHireItemCtrl::RequestAdd(const enum enumInventoryType in_InventoryType, IVItItem* in_pItem);
	public: void CPCHireItemCtrl::RequestRemove(IVItItem* const in_pItem);
	//public: void CPCHireItemCtrl::CPCHireItemCtrl(void);
	//public: void CPCHireItemCtrl::~CPCHireItemCtrl(void);

private:
	static hook_method<bool (CPCHireItemCtrl::*)(const __int64 in_ItemUID, CPCHireItemCtrl::CRequest& in_Request)> CPCHireItemCtrl::_RequestProcess;
	static hook_method<unsigned long (CPCHireItemCtrl::*)(const long in_CurDate, const unsigned long in_CurTime, const IVItItem* const in_pItem)> CPCHireItemCtrl::_GetNexCheckTime;
	static hook_method<void (CPCHireItemCtrl::*)(CPC* in_cpOwnerPC)> CPCHireItemCtrl::_Init;
	static hook_method<void (CPCHireItemCtrl::*)(void)> CPCHireItemCtrl::_Reset;
	static hook_method<void (CPCHireItemCtrl::*)(void)> CPCHireItemCtrl::_Process;
	static hook_method<void (CPCHireItemCtrl::*)(const enum enumInventoryType in_InventoryType, IVItItem* in_pItem)> CPCHireItemCtrl::_RequestAdd;
	static hook_method<void (CPCHireItemCtrl::*)(IVItItem* const in_pItem)> CPCHireItemCtrl::_RequestRemove;

	friend class CPC;
	friend void Hook();
};
