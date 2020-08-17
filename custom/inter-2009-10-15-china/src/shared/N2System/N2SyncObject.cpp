#include "N2System/N2SyncObject.h"


N2SyncObject::N2SyncObject(RTL_CRITICAL_SECTION& in_CS) // line 8
: m_CS(in_CS)
{
	EnterCriticalSection(&m_CS);
}


N2SyncObject::~N2SyncObject(void) // line 14
{
	LeaveCriticalSection(&m_CS);
}
