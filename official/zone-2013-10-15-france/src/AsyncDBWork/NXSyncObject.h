#pragma once


class NXSyncObject
{
public:
	NXSyncObject(RTL_CRITICAL_SECTION& in_CS);
	virtual ~NXSyncObject();
	NXSyncObject(const NXSyncObject&); // = delete;
	NXSyncObject& operator=(const NXSyncObject&); // = delete;

private:
	/* this+0 */ //const NXSyncObject::`vftable';
	/* this+4 */ RTL_CRITICAL_SECTION& m_CS;
};
