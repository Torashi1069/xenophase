#include "shared/N2System/N2SyncObject.h"


N2SyncObject::N2SyncObject(RTL_CRITICAL_SECTION& in_CS)
: m_CS(in_CS)
{
	EnterCriticalSection(&m_CS);
}


N2SyncObject::~N2SyncObject()
{
	LeaveCriticalSection(&m_CS);
}
