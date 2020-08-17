#pragma once
#include "std/string"


class NObject
{
	/* this+0x0  */ //const NObject::`vftable'
	/* this+0x4  */ private: const mystd::string m_strOBJname;
	/* this+0x20 */ private: const unsigned int m_MyID;

	public: mystd::string NObject::GetOBJName(void) const;
	public: const unsigned int NObject::GetMyID(void) const;
	public: NObject::NObject(const mystd::string in_strOBJname);
	public: virtual NObject::~NObject(void);

private:
	static hook_method<mystd::string (NObject::*)(void) const> NObject::_GetOBJName;
	static hook_method<const unsigned int (NObject::*)(void) const> NObject::_GetMyID;
};
