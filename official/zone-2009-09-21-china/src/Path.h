#pragma once
#include "std/string"


class CPath
{
	/* this+0 */ public: //const CPath::`vftable';

	public: CPath::CPath(void);
	public: virtual CPath::~CPath(void);
	public: static bool CPath::AddBackslash(const char* src, char* dest);
	public: static bool CPath::IsRemotePath(const char* path);
	public: static DWORD CPath::AddConnection(const char* path, const char* account, const char* password);
	public: static DWORD CPath::CancelConnection(const char* path);

private:
	static hook_method<static bool (__cdecl *)(const char* src, char* dest)> CPath::_AddBackslash;
	static hook_method<static bool (__cdecl *)(const char* path)> CPath::_IsRemotePath;
	static hook_method<static DWORD (__cdecl *)(const char* path, const char* account, const char* password)> CPath::_AddConnection;
	static hook_method<static DWORD (__cdecl *)(const char* path)> CPath::_CancelConnection;
};


class CPathData : public CPath
{
	/* this+ 0 */ public: //CPath baseclass_0;
	/* this+ 4 */ private: mystd::string m_path;
	/* this+32 */ private: mystd::string m_fileName;
	/* this+60 */ private: mystd::string m_filePath;

	public: CPathData::CPathData(void);
	public: virtual CPathData::~CPathData(void);
	public: void CPathData::Init(const char* path);
	public: CPathData& CPathData::SetFileName(const char* filename);
	public: operator const char *(void);
	public: operator const mystd::string(void);

private:
	static hook_method<void (CPathData::*)(const char* path)> CPathData::_Init;
	static hook_method<CPathData& (CPathData::*)(const char* filename)> CPathData::_SetFileName;
	static hook_method<char* (CPathData::*)(void)> CPathData::_operator_const_char_ptr;
	static hook_method<const mystd::string (CPathData::*)(void)> CPathData::_operator_const_mystd__string;
};
