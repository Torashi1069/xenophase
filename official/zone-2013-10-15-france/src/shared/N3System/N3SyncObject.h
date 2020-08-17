#pragma once


class N3SyncObject
{
public:
	N3SyncObject(RTL_CRITICAL_SECTION& in_CS);
	virtual ~N3SyncObject();
	N3SyncObject(const N3SyncObject&); // = delete;
	N3SyncObject& operator=(const N3SyncObject&); // = delete;

private:
	/* this+0 */ //const N3SyncObject::`vftable';
	/* this+4 */ RTL_CRITICAL_SECTION& m_CS;
};
