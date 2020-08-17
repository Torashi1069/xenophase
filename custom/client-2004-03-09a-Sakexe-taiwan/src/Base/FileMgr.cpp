#include "Globals.h" // g_readFolderFirst
#include "Base/FileMgr.h"
#include "Base/GPak.h"
#include "Base/Hash.h"
#include "Base/MemFile.h"


CFileMgr::CFileMgr()
{
}


CFileMgr::~CFileMgr()
{
	for( mystd::list<mystd::pair<CMemFile*,CGPak*>>::iterator it = m_pakList.begin(); it != m_pakList.end(); ++it )
	{
		delete it->first;
		delete it->second;
	}
}


bool CFileMgr::AddPak(const char* name)
{
	m_pakList.push_front(mystd::pair<CMemFile*,CGPak*>(new CMemMapFile(name), new CGPak()));
	return m_pakList.front().second->CGPak::Open(m_pakList.front().first);
}


void* CFileMgr::GetData(const char* name, DWORD* size)
{
	void* data;

	if( g_readFolderFirst )
	{
		data = this->CFileMgr::GetFile(name, size);
		if( data == NULL )
			data = this->CFileMgr::GetPak(name, size);
	}
	else
	{
		data = this->CFileMgr::GetPak(name, size);
		if( data == NULL )
			data = this->CFileMgr::GetFile(name, size);
	}

	return data;
}


void* CFileMgr::AllocData(DWORD size) /// @custom
{
	return VirtualAlloc(NULL, size, MEM_COMMIT, PAGE_READWRITE);
}


void CFileMgr::ReleaseData(void* data)
{
	VirtualFree(data, 0, MEM_RELEASE);
}


bool CFileMgr::IsDataExist(const char* name)
{
	for( mystd::list<mystd::pair<CMemFile*,CGPak*>>::iterator it = m_pakList.begin(); it != m_pakList.end(); ++it )
		if( it->second->CGPak::GetInfo(CHash(name), NULL) )
			return true;

	return this->CFileMgr::IsFileExist(name);
}


void* CFileMgr::GetPak(const char* name, DWORD* size)
{
	for( mystd::list<mystd::pair<CMemFile*,CGPak*>>::iterator it = m_pakList.begin(); it != m_pakList.end(); ++it )
	{
		CGPak* gpak = it->second;

		PakPack pakPack;
		if( !gpak->CGPak::GetInfo(CHash(name), &pakPack) )
			continue;

		*size = pakPack.m_size;
		void* data = this->CFileMgr::AllocData(*size + 8); //FIXME: unnecessary(?) padding
//		if( data == NULL ) //FIXME
//			continue;

		if( !gpak->CGPak::GetData(pakPack, data) )
		{
			this->CFileMgr::ReleaseData(data);
			continue;
		}

		return data; // done.
	}

	return NULL;
}


void* CFileMgr::GetFile(const char* name, DWORD* size)
{
	HANDLE hFile = CreateFileA(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if( hFile == INVALID_HANDLE_VALUE )
		return NULL;

	*size = GetFileSize(hFile, NULL);
	if( size == 0 ) //FIXME: should be *size
	{
		CloseHandle(hFile);
		return NULL;
	}

	void* data = this->CFileMgr::AllocData(*size);
	if( data == NULL )
	{
		this->CFileMgr::ReleaseData(data); //NOTE: nullptr
		CloseHandle(hFile);
		return NULL;
	}

	DWORD RByte;
	ReadFile(hFile, data, *size, &RByte, NULL);
	CloseHandle(hFile);

	return data;
}


bool CFileMgr::IsFileExist(const char* name)
{
	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(name, &findData);

	if( hFind == INVALID_HANDLE_VALUE )
		return false;

	FindClose(hFind);
	return true;
}
