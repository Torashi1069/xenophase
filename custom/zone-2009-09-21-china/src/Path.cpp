#include "Path.h"
////////////////////////////////////////


CPath::CPath(void) // line ??
{
}


CPath::~CPath(void) // line 34 (Path.h)
{
}


/// Duplicates all backslashes in 'src' and writes output to 'dest'.
//hook_method<static bool (__cdecl *)(const char* src, char* dest)> CPath::_AddBackslash(SERVER, "CPath::AddBackslash");
bool CPath::AddBackslash(const char* src, char* dest) // line ??
{
//	return (_AddBackslash)(src, dest);

	if( src == NULL || dest == NULL )
		return false;

	char temp[512];
	size_t pos = 0;
	for( size_t i = 0; i < strlen(src); ++i )
	{
		temp[pos++] = src[i];
		if( src[i] == '\\' )
			temp[pos++] = '\\';
	}
	temp[pos] = '\0';
	strcpy(dest, temp);
	return true;
}


hook_method<static bool (__cdecl *)(const char* path)> CPath::_IsRemotePath(SERVER, "CPath::IsRemotePath");
bool CPath::IsRemotePath(const char* path) // line 40
{
	return (_IsRemotePath)(path);

	return ( path != NULL && path[0] == '\\' && path[1] == '\\' );
}


hook_method<static DWORD (__cdecl *)(const char* path, const char* account, const char* password)> CPath::_AddConnection(SERVER, "CPath::AddConnection");
DWORD CPath::AddConnection(const char* path, const char* account, const char* password) // line 55
{
	return (_AddConnection)(path, account, password);

	if( path == NULL || account == NULL || password == NULL )
		return -1;

	char temp[MAX_PATH];
	memcpy(temp, path, sizeof(temp));
	temp[sizeof(temp)-1] = '\0';

	NETRESOURCEA nr; //NOTE: some fields uninitialized
	nr.dwType = RESOURCETYPE_ANY;
	nr.lpLocalName = NULL;
	nr.lpProvider = NULL;
	nr.lpRemoteName = temp;

	DWORD err = WNetAddConnection2A(&nr, password, account, 0);
	if( err == ERROR_SESSION_CREDENTIAL_CONFLICT )
	{
		CPath::CancelConnection(temp);
		err = WNetAddConnection2A(&nr, password, account, 0);
	}

	return err;
}


hook_method<static DWORD (__cdecl *)(const char* path)> CPath::_CancelConnection(SERVER, "CPath::CancelConnection");
DWORD CPath::CancelConnection(const char* path) // line 88
{
	return (_CancelConnection)(path);

	if( path == NULL )
		return -1;

	char temp[MAX_PATH];
	memcpy(temp, path, sizeof(temp));
	temp[sizeof(temp)-1] = '\0';

	DWORD err = WNetCancelConnection2A(temp, CONNECT_UPDATE_PROFILE, TRUE);
	return err;
}


////////////////////////////////////////


CPathData::CPathData(void) // line 49 (Path.h)
{
}


CPathData::~CPathData(void) // line 50 (Path.h)
{
}


hook_method<void (CPathData::*)(const char* path)> CPathData::_Init(SERVER, "CPathData::Init");
void CPathData::Init(const char* path) // line 121
{
	return (this->*_Init)(path);

	if( path != NULL )
	{
		m_path = path;
		if( m_path.size() != 0 )
			m_path += "/";

		mkdir("./itemdata");
		mkdir("./npcdata");
		mkdir("./scriptdata");
	}
}


hook_method<CPathData& (CPathData::*)(const char* filename)> CPathData::_SetFileName(SERVER, "CPathData::SetFileName");
CPathData& CPathData::SetFileName(const char* filename) // line 150
{
	return (this->*_SetFileName)(filename);

	if( filename != NULL )
		m_fileName = filename;

	return *this;
}


hook_method<char* (CPathData::*)(void)> CPathData::_operator_const_char_ptr(SERVER, "??BCPathData@@QAEPBDXZ");
CPathData::operator const char *(void) // line 135
{
	return (this->*_operator_const_char_ptr)();

	m_filePath = m_path + m_fileName;
	return m_filePath.c_str();
}


hook_method<const mystd::string (CPathData::*)(void)> CPathData::_operator_const_mystd__string(SERVER, "??BCPathData@@QAE?BV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ");
CPathData::operator const mystd::string(void) // line 142
{
	return (this->*_operator_const_mystd__string)();

	m_filePath = m_path + m_fileName;
	return m_filePath;
}


////////////////////////////////////////
