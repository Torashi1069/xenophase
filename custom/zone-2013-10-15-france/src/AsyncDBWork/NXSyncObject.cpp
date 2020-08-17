#include "AsyncDBWork/NXSyncObject.h"


NXSyncObject::NXSyncObject(RTL_CRITICAL_SECTION& in_CS)
: m_CS(in_CS)
{
	EnterCriticalSection(&m_CS);
}


NXSyncObject::~NXSyncObject()
{
	LeaveCriticalSection(&m_CS);
}
