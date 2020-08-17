#include "Base/MemFile.h"
#pragma warning(disable:4146) //warning C4146: unary minus operator applied to unsigned type, result still unsigned


CMemMapFile::CMemMapFile(const char* name)
{
	this->CMemMapFile::init();
	this->CMemMapFile::open(name);
}


CMemMapFile::~CMemMapFile()
{
	this->CMemMapFile::close();
}


bool CMemMapFile::open(const char* name)
{
	m_hFile = CreateFileA(name, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if( m_hFile == INVALID_HANDLE_VALUE )
	{
		m_hFile = NULL;
		return false;
	}

	m_dwFileSize = GetFileSize(m_hFile, NULL);
	m_dwOpenOffset = 0;
	m_dwOpenSize = 0;

	m_hFileMap = CreateFileMappingA(m_hFile, NULL, PAGE_READONLY, 0, 0, name);
	if( m_hFileMap == NULL )
	{
		m_dwFileMappingSize = 0;
		return false;
	}

	return true;
}


void CMemMapFile::close()
{
	if( m_dwFileMappingSize != 0 && m_pFile != NULL )
	{
		UnmapViewOfFile(m_pFile);
		m_pFile = NULL;
	}

	if( m_hFileMap != NULL )
	{
		CloseHandle(m_hFileMap);
		m_hFileMap = NULL;
	}

	if( m_hFile != NULL )
	{
		CloseHandle(m_hFile);
		m_hFile = NULL;
	}
}


DWORD CMemMapFile::size()
{
	return m_dwFileSize;
}


const BYTE* CMemMapFile::read(DWORD offset, DWORD size)
{
	if( m_dwFileMappingSize != 0 )
	{
		if( offset >= m_dwOpenOffset && offset + size <= m_dwOpenOffset + m_dwOpenSize )
			return &m_pFile[offset - m_dwOpenOffset];

		if( m_pFile != NULL )
		{
			UnmapViewOfFile(m_pFile);
			m_pFile = NULL;
		}

		while( m_dwFileMappingSize != 0 && m_dwFileMappingSize >= size )
		{
			m_dwOpenOffset = offset & m_dwAllocationGranuarity;
			m_dwOpenSize = m_dwFileMappingSize;

			if( m_dwOpenOffset + m_dwFileMappingSize <= m_dwFileSize )
			{
				m_pFile = (BYTE*)MapViewOfFile(m_hFileMap, FILE_MAP_READ, 0, m_dwOpenOffset, m_dwFileMappingSize);
			}
			else
			{
				m_pFile = (BYTE*)MapViewOfFile(m_hFileMap, FILE_MAP_READ, 0, m_dwOpenOffset, 0);
				m_dwOpenSize = m_dwFileSize - m_dwOpenOffset;
			}

			if( m_pFile != NULL )
				return &m_pFile[offset - m_dwOpenOffset];

			m_dwFileMappingSize = m_dwFileMappingSize / 2;
		}

		CloseHandle(m_hFileMap);
		m_hFileMap = NULL;
		m_pFile = NULL;
		m_dwOpenSize = 0;
		m_dwFileMappingSize = 0;
	}

	if( m_dwOpenSize < size )
	{
		m_dwOpenSize = size;
		m_pFileBuf.resize(size);
		m_pFile = &m_pFileBuf.front();
	}

	DWORD dwRead;
	SetFilePointer(m_hFile, offset, NULL, FILE_BEGIN);
	ReadFile(m_hFile, &m_pFileBuf.front(), size, &dwRead, NULL);

	return m_pFile;
}


void CMemMapFile::init()
{
	SYSTEM_INFO systemInfo;
	GetSystemInfo(&systemInfo);

	m_dwFileMappingSize = 512 * 1024 * 1024;
	m_dwAllocationGranuarity = -systemInfo.dwAllocationGranularity; // mask
	m_hFile = NULL;
	m_hFileMap = NULL;
	m_pFile = NULL;
	m_dwFileSize = 0;
	m_dwOpenOffset = 0;
	m_dwOpenSize = 0;
}
