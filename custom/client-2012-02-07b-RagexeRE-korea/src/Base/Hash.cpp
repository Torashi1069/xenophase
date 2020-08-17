#include "Base/Hash.h"


CHash::CHash()
{
	this->CHash::SetString("");
}


CHash::CHash(const char* str)
{
	this->CHash::SetString(str);
}


void CHash::SetString(const char* str)
{
	strcpy(m_String, str);
	strlwr(m_String);
	this->CHash::CreateHashCode();
}


const char* CHash::c_str() const
{
	return m_String;
}


bool CHash::operator< (const CHash& hash) const
{
	return ( m_HashCode != hash.m_HashCode ) ? ( m_HashCode < hash.m_HashCode ) : ( strcmp(m_String, hash.m_String) < 0 );
}


bool CHash::operator==(const CHash& hash) const
{
	return !this->CHash::operator!=(hash);
}


bool CHash::operator!=(const CHash& hash) const
{
	return( m_HashCode != hash.m_HashCode || strcmp(m_String, hash.m_String) != 0 );
}


void CHash::CreateHashCode()
{
	size_t len = strlen(m_String);
	unsigned long hash = 5381;

	for( size_t i = 0; i < len; ++i )
		hash = hash * 33 + m_String[i];

	m_HashCode = hash;
}
