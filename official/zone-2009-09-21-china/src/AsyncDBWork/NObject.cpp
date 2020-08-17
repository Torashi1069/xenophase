#include "AsyncDBWork/NIDAllocator.h"
#include "AsyncDBWork/NObject.h"


NObject::NObject(const mystd::string in_strOBJname) // line 12
: m_strOBJname(in_strOBJname), m_MyID(NIDAllocator::GetObj()->NIDAllocator::Alloc(m_strOBJname))
{
}


NObject::~NObject(void) // line 17
{
	NIDAllocator::GetObj()->NIDAllocator::Free(m_strOBJname, m_MyID);
}


//hook_method<mystd::string (NObject::*)(void) const> NObject::_GetOBJName(SERVER, "NObject::GetOBJName");
mystd::string NObject::GetOBJName(void) const // line ??
{
//	return (this->*_GetOBJName)();

	return m_strOBJname;
}


//hook_method<const unsigned int (NObject::*)(void) const> NObject::_GetMyID(SERVER, "NObject::GetMyID");
const unsigned int NObject::GetMyID(void) const // line ??
{
//	return (this->*_GetMyID)();

	return m_MyID;
}
