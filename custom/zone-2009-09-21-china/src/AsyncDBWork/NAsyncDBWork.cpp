#include "AsyncDBWork/NAsyncDBWork.h"
#include "AsyncDBWork/NAsyncDBWorkIdentityGenerator.h"


namespace
{
CNAsyncDBWorkIdentityGenerator& NAsyncDBWorkIdentityGenerator = *(CNAsyncDBWorkIdentityGenerator*)DetourFindFunction(SERVER, "?NAsyncDBWorkIdentityGenerator@?A0x71998df7@@3VCNAsyncDBWorkIdentityGenerator@1@A");
}


NAsyncDBWork::NAsyncDBWork(const enum NAsyncDBWork::enumType in_Type, const unsigned int in_ID) // line 42
: m_Type(in_Type), m_ID(in_ID), m_StartTM(timeGetTime()), m_Identity(NAsyncDBWorkIdentityGenerator())
{
}


NAsyncDBWork::~NAsyncDBWork(void) // line 47
{
}


//hook_method<const enum NAsyncDBWork::enumType (NAsyncDBWork::*)(void)> NAsyncDBWork::_GetType(SERVER, "NAsyncDBWork::GetType");
const enum NAsyncDBWork::enumType NAsyncDBWork::GetType(void)
{
//	return (this->*_GetType)();

	return m_Type;
}


//hook_method<const unsigned int (NAsyncDBWork::*)(void)> NAsyncDBWork::_GetID(SERVER, "NAsyncDBWork::GetID");
const unsigned int NAsyncDBWork::GetID(void)
{
//	return (this->*_GetID)();

	return m_ID;
}


//hook_method<const unsigned long (NAsyncDBWork::*)(void)> NAsyncDBWork::_GetStartTM(SERVER, "NAsyncDBWork::GetStartTM");
const unsigned long NAsyncDBWork::GetStartTM(void)
{
//	return (this->*_GetStartTM)();

	return m_StartTM;
}


//hook_method<const int (NAsyncDBWork::*)(void)> NAsyncDBWork::_GetIdentity(SERVER, "NAsyncDBWork::GetIdentity");
const int NAsyncDBWork::GetIdentity(void)
{
//	return (this->*_GetIdentity)();

	return m_Identity;
}
