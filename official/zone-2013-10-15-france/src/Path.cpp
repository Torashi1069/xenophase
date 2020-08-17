#include "Path.h"
//#include <WinNetWk.h>
////////////////////////////////////////


/// Duplicates all backslashes in 'src' and writes output to 'dest'.
bool CPath::AddBackslash(const char* src, char* dest)
{
	if( src == NULL || dest == NULL )
		return false;

	char temp[512];
	size_t p = 0;
	for( size_t i = 0; i < strlen(src); ++i )
	{
		temp[p++] = src[i];
		if( src[i] == '\\' )
			temp[p++] = '\\';
	}
	temp[p] = '\0';

	strcpy(dest, temp);
	return true;
}


bool CPath::IsRemotePath(const char* path)
{
	return ( path != NULL && path[0] == '\\' && path[1] == '\\' );
}


DWORD CPath::AddConnection(const char* path, const char* account, const char* password)
{
	if( path == NULL || account == NULL || password == NULL )
		return -1;

	char temp[MAX_PATH];
	memcpy_s(temp, sizeof(temp), path, MAX_PATH);
	temp[countof(temp)-1] = '\0';

	NETRESOURCEA nr;
	nr.dwType = RESOURCETYPE_ANY;
	nr.lpLocalName = NULL;
	nr.lpProvider = NULL;
	nr.lpRemoteName = temp;

	DWORD ret = WNetAddConnection2A(&nr, password, account, 0);
	if( ret == ERROR_SESSION_CREDENTIAL_CONFLICT )
	{
		CPath::CancelConnection(temp);
		ret = WNetAddConnection2A(&nr, password, account, 0);
	}
	return ret;
}


DWORD CPath::CancelConnection(const char* path)
{
	if( path == NULL )
		return -1;

	char temp[MAX_PATH];
	memcpy_s(temp, sizeof(temp), path, MAX_PATH);
	temp[countof(temp)-1] = '\0';

	DWORD ret = WNetCancelConnection2A(temp, CONNECT_UPDATE_PROFILE, TRUE);
	return ret;
}


////////////////////////////////////////


void CPathData::Init(const char* path)
{
	if( path == NULL )
		return;

	m_path = path;
	if( m_path.size() != 0 )
		m_path += "/";

	mkdir("./itemdata");
	mkdir("./npcdata");
	mkdir("./scriptdata");
}


CPathData::operator const char*()
{
	m_filePath = m_path + m_fileName;
	return m_filePath.c_str();
}


CPathData::operator const std::string()
{
	m_filePath = m_path + m_fileName;
	return m_filePath;
}


CPathData& CPathData::SetFileName(const char* filename)
{
	if( filename == NULL )
		return *this;

	m_fileName = filename;
	return *this;
}


////////////////////////////////////////
