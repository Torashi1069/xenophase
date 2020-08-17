#pragma once
#include "ScriptEventHandler.h"
class CSpecialItemMgr; //#include "ItemServer/specialitemmgr.h"


class CItemScriptEventHandler : public CScriptEventHandler
{
public:
	void Set(CSpecialItemMgr* ptrItemMgr, int* pParam, int CharId, int scanItem, const unsigned int in_Identity);
	int GetAID(); //TODO
	bool Run(CBinBuf* binBuf, int beginPos);

public:
	CItemScriptEventHandler();
	virtual ~CItemScriptEventHandler();

private:
	virtual bool OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret);
	virtual void OnError(const char* str);
	virtual void Free();

private:
	/* this+  0 */ //CScriptEventHandler baseclass_0;
	/* this+120 */ int* m_pParam;
	/* this+124 */ int m_nRetParam[10];
	/* this+164 */ CSpecialItemMgr* m_ptrItemMgr;
	/* this+168 */ int m_CharId;
	/* this+172 */ int m_nScanItem;
	/* this+176 */ unsigned int m_Identity;
};
