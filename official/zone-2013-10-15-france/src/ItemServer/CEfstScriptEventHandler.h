#pragma once
#include "ScriptEventHandler.h"


class CEfstScriptEventHandler : public CScriptEventHandler
{
public:
	void Set(const int in_OwnerID, const unsigned int in_Identity);

private:
	virtual bool OnFunc(int in_func, std::deque<TokenData>& in_parm, TokenData& in_ret);

public:
	CEfstScriptEventHandler();
	virtual ~CEfstScriptEventHandler();

private:
	/* this+  0 */ //CScriptEventHandler baseclass_0;
	/* this+120 */ unsigned int m_Identity;
};
