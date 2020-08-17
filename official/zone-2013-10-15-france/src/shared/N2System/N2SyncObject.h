#pragma once


class N2SyncObject
{
private:
	/* this+0 */ //const N2SyncObject::`vftable';
	/* this+4 */ RTL_CRITICAL_SECTION& m_CS;

private:
	N2SyncObject(const N2SyncObject&); // = delete;
	N2SyncObject& operator=(const N2SyncObject&); // = delete;

public:
	N2SyncObject(RTL_CRITICAL_SECTION& in_CS);
	virtual ~N2SyncObject();
};
