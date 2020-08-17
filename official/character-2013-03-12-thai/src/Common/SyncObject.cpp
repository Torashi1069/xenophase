#include "Common/SyncObject.h"


SyncObject::SyncObject(CCriticalSection& in_CS)
: m_CS(in_CS)
{
	m_CS.Enter();
};


SyncObject::~SyncObject()
{
	m_CS.Leave();
}
