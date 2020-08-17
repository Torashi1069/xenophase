#include "Instant Map/IMWTWork.h"


CIMWTWork::CIMWTWork(const enum CIMWTWork::enumTYPE in_Type) // line 14
: m_Type(in_Type)
{
}


CIMWTWork::~CIMWTWork(void) // line 19
{
}


hook_method<void (CIMWTWork::*)(void)> CIMWTWork::_Run(SERVER, "CIMWTWork::Run");
void CIMWTWork::Run(void) // line ??
{
	return (this->*_Run)();

	;
}


//hook_method<const enum CIMWTWork::enumTYPE (CIMWTWork::*)(void)> CIMWTWork::_GetType(SERVER, "CIMWTWork::GetType");
const enum CIMWTWork::enumTYPE CIMWTWork::GetType(void) // line ??
{
//	return (this->*_GetType)();

	return m_Type;
}
