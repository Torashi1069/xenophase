#include "N2System/N2IDAllocator.h"
#include "N2System/N2Object.h"


N2Object::N2Object(const unsigned short in_GroupID) // line 10
: m_MyID(N2IDAllocator::GetObj()->N2IDAllocator::Alloc(in_GroupID))
{
}


N2Object::~N2Object(void) // line 16
{
	N2IDAllocator::GetObj()->N2IDAllocator::Free(m_MyID);
}


hook_method<const unsigned int (N2Object::*)(void) const> N2Object::_GetMyID(SERVER, "N2Object::GetMyID");
const unsigned int N2Object::GetMyID(void) const
{
	return (this->*_GetMyID)();

	return m_MyID;
}


hook_method<const unsigned short (N2Object::*)(void) const> N2Object::_GetMyGroupID(SERVER, "N2Object::GetMyGroupID");
const unsigned short N2Object::GetMyGroupID(void) const
{
	return (this->*_GetMyGroupID)();

	return HIWORD(m_MyID);
}
