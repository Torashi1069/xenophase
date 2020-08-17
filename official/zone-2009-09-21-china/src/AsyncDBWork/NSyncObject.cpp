#include "AsyncDBWork/NSyncObject.h"


NSyncObject::NSyncObject(RTL_CRITICAL_SECTION& in_CS) // line 9
: m_CS(in_CS)
{
	::EnterCriticalSection(&m_CS);
}


NSyncObject::~NSyncObject(void) // line 15
{
	::LeaveCriticalSection(&m_CS);
}
