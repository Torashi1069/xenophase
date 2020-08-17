#include "Common/NSyncObject.h"


NSyncObject::NSyncObject(RTL_CRITICAL_SECTION& in_CS)
: m_CS(in_CS)
{
	EnterCriticalSection(&m_CS);
}


NSyncObject::~NSyncObject()
{
	LeaveCriticalSection(&m_CS);
}
