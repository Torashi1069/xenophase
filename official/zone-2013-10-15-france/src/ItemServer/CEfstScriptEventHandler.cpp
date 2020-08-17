#include "ItemServer/CEfstScriptEventHandler.h"


CEfstScriptEventHandler::CEfstScriptEventHandler()
: m_Identity(0)
{
}


CEfstScriptEventHandler::~CEfstScriptEventHandler()
{
}


void CEfstScriptEventHandler::Set(const int in_OwnerID, const unsigned int in_Identity)
{
	m_Identity = in_Identity;
	this->CScriptEventHandler::Init(in_OwnerID);
}


bool CEfstScriptEventHandler::OnFunc(int in_func, std::deque<TokenData>& in_parm, TokenData& in_ret)
{
	if( in_func >= FUNC_SETAUTOSPELL2 && in_func <= FUNC_RESUMEAUTOSPELL2_RANGEATK )
	{
		TokenData a;
		a = (int)m_Identity;
		in_parm.push_back(a);
	}

	return this->CScriptEventHandler::OnFunc(in_func, in_parm, in_ret);
}
