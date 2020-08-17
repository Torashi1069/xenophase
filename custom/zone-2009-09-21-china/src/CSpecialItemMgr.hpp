#pragma once
#include "ScriptLib/BinBuf.h"
#include "std/map"
class CReceiveSpecialItemInfoMsg;
class CSendSpecialItemInfoMsg;
class CSpecialItem;


class CSpecialItemMgr
{
	/* this+  0 */ public: //const CSpecialItemMgr::`vftable';
	/* this+  4 */ public: CSendSpecialItemInfoMsg* m_pITZMsg;
	/* this+  8 */ public: CReceiveSpecialItemInfoMsg* m_pZITMsg;
	/* this+ 12 */ private: CBinBuf m_binBuf;
	/* this+ 20 */ private: mystd::map<int,CSpecialItem*> m_itemMap;
	/* this+ 32 */ private: char* m_strScanItem;
	/* this+ 36 */ private: int m_nScanItem;
	/* this+ 40 */ private: int m_nScanEvent;
	/* this+ 44 */ private: int m_nItemParam[10];
	/* this+ 84 */ private: int m_nItemFuncIdx;
	/* this+ 88 */ private: int m_nRetItemFunc[10];
	/* this+128 */ private: int m_nRetItemFuncParam[10][10];

	public: CSpecialItemMgr::CSpecialItemMgr(void);
	public: virtual CSpecialItemMgr::~CSpecialItemMgr(void);
	public: bool CSpecialItemMgr::Init(void);
	//public: bool CSpecialItemMgr::Load();
	//public: bool CSpecialItemMgr::Run(int, int, int, int);
	public: void CSpecialItemMgr::SendMsg(unsigned long ITID, unsigned long EventID, unsigned long senderAID);
	//public: bool CSpecialItemMgr::GetItemSpecialStatus(CSendSpecialItemInfoMsg *, CReceiveSpecialItemInfoMsg *);
	//public: void CSpecialItemMgr::SetScanItem(char *);
	//public: void CSpecialItemMgr::SetScanEvent(int);
	//public: void CSpecialItemMgr::SetItemParam(int *, int);
	//public: void CSpecialItemMgr::SetRetItemFunc(int, int);
	//public: void CSpecialItemMgr::SetRetItemParam(int *, int);
	//public: int CSpecialItemMgr::GetItemFuncIdx();
	//public: void CSpecialItemMgr::AddItemFuncIdx();
	//private: bool CSpecialItemMgr::Compile();
	//private: bool CSpecialItemMgr::GetItem(int, CSpecialItem * &);
	//private: bool CSpecialItemMgr::DestroyItem(int);
	//private: CSpecialItem* CSpecialItemMgr::CreateItem(int);
	//private: bool CSpecialItemMgr::AddEvent(int, int, int);
	//private: bool CSpecialItemMgr::RunEvent(int, int, int);

private:
	static hook_method<bool (CSpecialItemMgr::*)(void)> CSpecialItemMgr::_Init;
	static hook_method<void (CSpecialItemMgr::*)(unsigned long ITID, unsigned long EventID, unsigned long senderAID)> CSpecialItemMgr::_SendMsg;
};
