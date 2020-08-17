#pragma once


class N2SyncObject
{
	/* this+0 */ public: //const N2SyncObject::`vftable';
	/* this+4 */ private: RTL_CRITICAL_SECTION& m_CS;

	public: N2SyncObject::N2SyncObject(RTL_CRITICAL_SECTION& in_CS);
	public: N2SyncObject::~N2SyncObject(void);
};
