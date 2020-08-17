#pragma once


class RegKey
{
public:
	RegKey();
	~RegKey();

public:
	bool open(HKEY predKey, LPCSTR subKeyName);
	bool create(HKEY predKey, LPCSTR subKeyName);
	void close();
	bool setValue(LPCSTR valueName, DWORD regType, const BYTE* value, DWORD valueLen);
	bool queryValue(LPCSTR valueName, DWORD regType, BYTE* value, DWORD valueLen);
	bool queryValueSize(LPCSTR valueName, DWORD* valueLen);

protected:
	/* this+0 */ HKEY m_key;
};
