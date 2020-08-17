#include "RegMgr.h"


RegKey::RegKey()
{
	m_key = NULL;
}


RegKey::~RegKey()
{
	this->RegKey::close();
}


bool RegKey::open(HKEY predKey, LPCSTR subKeyName)
{
	return( RegOpenKeyExA(predKey, subKeyName, 0, KEY_ALL_ACCESS, &m_key) == ERROR_SUCCESS );
}


bool RegKey::create(HKEY predKey, LPCSTR subKeyName)
{
	DWORD dwDisposition;
	return( RegCreateKeyExA(predKey, subKeyName, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_key, &dwDisposition) == ERROR_SUCCESS );
}


void RegKey::close()
{
	RegCloseKey(m_key);
	m_key = NULL;
}


bool RegKey::setValue(LPCSTR valueName, DWORD regType, const BYTE* value, DWORD valueLen)
{
	return( m_key != NULL && RegSetValueExA(m_key, valueName, 0, regType, value, valueLen) == ERROR_SUCCESS );
};


bool RegKey::queryValueSize(LPCSTR valueName, DWORD* valueLen)
{
	return( m_key != NULL && RegQueryValueExA(m_key, valueName, NULL, NULL, NULL, valueLen) == ERROR_SUCCESS );
}


bool RegKey::queryValue(LPCSTR valueName, DWORD regType, BYTE* value, DWORD valueLen)
{
	DWORD type;
	return( m_key != NULL && RegQueryValueExA(m_key, valueName, NULL, &type, value, &valueLen) == ERROR_SUCCESS && type == regType );
}
