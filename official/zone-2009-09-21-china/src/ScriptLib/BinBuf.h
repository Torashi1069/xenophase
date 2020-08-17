#pragma once


class CBinBuf
{
	/* this+0 */ private: char* m_buf;
	/* this+4 */ private: int m_bufSize;

	public: CBinBuf::CBinBuf(void);
	public: CBinBuf::~CBinBuf(void);
	public: void CBinBuf::Clear(void);
	public: bool CBinBuf::Load(const char* fName);
	public: char* CBinBuf::GetBase(void);
	public: int CBinBuf::GetSize(void);

private:
	static hook_method<void (CBinBuf::*)(void)> CBinBuf::_CBinBuf;
	static hook_method<void (CBinBuf::*)(void)> CBinBuf::__CBinBuf;
	static hook_method<void (CBinBuf::*)(void)> CBinBuf::_Clear;
	static hook_method<bool (CBinBuf::*)(const char* fName)> CBinBuf::_Load;
	static hook_method<char* (CBinBuf::*)(void)> CBinBuf::_GetBase;
	static hook_method<int (CBinBuf::*)(void)> CBinBuf::_GetSize;
};
