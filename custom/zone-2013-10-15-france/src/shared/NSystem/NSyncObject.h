#pragma once


class NSyncObject
{
public:
	NSyncObject(RTL_CRITICAL_SECTION& in_CS);
	virtual ~NSyncObject();
	NSyncObject(const NSyncObject&); // = delete;
	NSyncObject& operator=(const NSyncObject&); // = delete;

private:
	/* this+0 */ //const NSyncObject::`vftable';
	/* this+4 */ RTL_CRITICAL_SECTION& m_CS;
};
