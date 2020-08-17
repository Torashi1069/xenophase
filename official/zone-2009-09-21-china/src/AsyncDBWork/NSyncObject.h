#pragma once


struct NSyncObject
{
	/* this+0x0 */ //const NSyncObject::`vftable'
	/* this+0x4 */ private: RTL_CRITICAL_SECTION& m_CS;

	public: NSyncObject::NSyncObject(RTL_CRITICAL_SECTION& in_CS);
	public: virtual NSyncObject::~NSyncObject(void);
};
