#pragma once


class N2Object
{
	/* this+0x0 */ //const N2Object::`vftable'
	/* this+0x4 */ private: const unsigned int m_MyID;

	public: const unsigned int N2Object::GetMyID(void) const;
	public: const unsigned short N2Object::GetMyGroupID(void) const;
	public: N2Object::N2Object(const unsigned short in_GroupID);
	public: virtual N2Object::~N2Object(void);

private:
	static hook_method<const unsigned int (N2Object::*)(void) const> N2Object::_GetMyID;
	static hook_method<const unsigned short (N2Object::*)(void) const> N2Object::_GetMyGroupID;
};
