#include "shared/N2System/N2IDAllocator.h"
#include "shared/N2System/N2Object.h"


N2Object::N2Object(const unsigned short in_GroupID)
: m_MyID(N2IDAllocator::GetObj()->N2IDAllocator::Alloc(in_GroupID))
{
}


N2Object::~N2Object()
{
	N2IDAllocator::GetObj()->N2IDAllocator::Free(m_MyID);
}


const unsigned int N2Object::GetMyID()
{
	return m_MyID;
}


const unsigned short N2Object::GetMyGroupID()
{
	return HIWORD(m_MyID);
}
