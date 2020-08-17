#include "shared/N3System/N3SyncObject.h"


N3SyncObject::N3SyncObject(RTL_CRITICAL_SECTION& in_CS)
: m_CS(in_CS)
{
	EnterCriticalSection(&m_CS);
}


N3SyncObject::~N3SyncObject()
{
	LeaveCriticalSection(&m_CS);
}
