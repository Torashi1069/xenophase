#pragma once
#include "ScriptLib/Interpreter.h"
#include "ItemServer/specialitem.h"
#include "ItemServer/specialitemmgr.h"


class CSpecialItemScanner : public CInterpretHandler
{
public:
	CSpecialItemScanner(CSpecialItemMgr* itemMgr, CBinBuf* binBuf);
	virtual ~CSpecialItemScanner();
	bool Run();

private:
	virtual bool OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret);
	virtual void OnError(const char* str);
	bool FuncItem(int itemID, bool isUseEvent);

private:
	/* this+  0 */ //CInterpretHandler baseclass_0;
	/* this+  8 */ CInterpreter m_interpreter;
	/* this+ 72 */ bool m_isError;
	/* this+ 76 */ SpecialItemEvent* m_event;
	/* this+ 80 */ CSpecialItem* m_item;
	/* this+ 84 */ CSpecialItemMgr* m_itemMgr;
	/* this+ 88 */ char* m_strScanItem;
	/* this+ 92 */ int m_nScanEvent;
	/* this+ 96 */ int m_nItemParam[10];
	/* this+136 */ int m_nRetItemFunc;
	/* this+140 */ int m_nRetItemFuncParam[10];
	/* this+180 */ bool m_bFindItem;
	/* this+181 */ bool m_bFindEvent;
	/* this+182 */ unsigned short m_currentItemID;
};
