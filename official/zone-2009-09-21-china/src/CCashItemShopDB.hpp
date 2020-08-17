#pragma once
#include "ODBCV2.h"


class CCashItemShopDB : public CODBCV2
{
public:
	/* this+0x0 */ //CODBCV2
	/* static   */ private: static hook_ptr<CCashItemShopDB *> m_cpSelf;

	private: CCashItemShopDB::CCashItemShopDB(void);
	private: CCashItemShopDB::~CCashItemShopDB(void);
	//private: bool CCashItemShopDB::InsertLog(CCashItemShopLogRecord& in_LogRecord);
	public: static CCashItemShopDB* __cdecl CCashItemShopDB::GetObj(void);
	public: bool CCashItemShopDB::GetCash(const int in_AID, const char* in_pAccountName, int& out_Error_code, int& out_Cash);
	public: bool CCashItemShopDB::PlusUpdateCash(const int in_AID, const char* in_pAccountName, const int in_plusValue, const int in_item_id, const int in_item_count, int& out_Error_code, int& out_Cash_Before, int& out_Cash_After);
	public: bool CCashItemShopDB::MinusUpdateCash(const int in_AID, const char* in_pAccountName, const int in_minusValue, const int in_item_id, const int in_item_count, int& out_Error_code, int& out_Cash_Before, int& out_Cash_After);
	//public: void CCashItemShopDB::Log(const enum CCashItemShopLogRecord::enumACTION in_Action, CPC* in_pPC, CNPC* in_pNPC, IVItItem* in_pItem, const int in_PriceCash, const int in_ViewCash, const int in_BeforCash, const int in_AfterCash);

private:
	static hook_method<static CCashItemShopDB* (__cdecl *)(void)> CCashItemShopDB::_GetObj;
	static hook_method<bool (CCashItemShopDB::*)(const int in_AID, const char* in_pAccountName, int& out_Error_code, int& out_Cash)> CCashItemShopDB::_GetCash;
	static hook_method<bool (CCashItemShopDB::*)(const int in_AID, const char* in_pAccountName, const int in_plusValue, const int in_item_id, const int in_item_count, int& out_Error_code, int& out_Cash_Before, int& out_Cash_After)> CCashItemShopDB::_PlusUpdateCash;
	static hook_method<bool (CCashItemShopDB::*)(const int in_AID, const char* in_pAccountName, const int in_minusValue, const int in_item_id, const int in_item_count, int& out_Error_code, int& out_Cash_Before, int& out_Cash_After)> CCashItemShopDB::_MinusUpdateCash;
};
