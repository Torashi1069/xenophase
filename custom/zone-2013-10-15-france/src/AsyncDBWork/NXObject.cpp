#include "AsyncDBWork/NIDAllocator.h"
#include "AsyncDBWork/NXObject.h"


NXObject::NXObject(const std::string in_strOBJname)
: m_strOBJname(in_strOBJname), m_MyID(NIDAllocator::GetObj()->NIDAllocator::Alloc(in_strOBJname))
{
}


NXObject::~NXObject()
{
	NIDAllocator::GetObj()->NIDAllocator::Free(m_strOBJname, m_MyID);
}


std::string NXObject::GetOBJName() const
{
	return m_strOBJname;
}


const unsigned int NXObject::GetMyID() const
{
	return m_MyID;
}
