#pragma once
#include "Common/CriticalSection.h"


class SyncObject
{
public:
	SyncObject(CCriticalSection& in_CS);
	~SyncObject();

private:
	/* this+0 */ //const SyncObject::`vftable';
	/* this+4 */ CCriticalSection& m_CS;
};
