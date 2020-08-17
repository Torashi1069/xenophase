#pragma once


class CMemFile
{
public:
	CMemFile() { }
	virtual ~CMemFile() { }

public:
	virtual DWORD size() = 0;
	virtual const BYTE* read(DWORD offset, DWORD size) = 0;
};


class CMemMapFile : public CMemFile
{
public:
	CMemMapFile(const char* name);
	virtual ~CMemMapFile();

public:
	bool open(const char* name);
	void close();
	virtual DWORD size();
	virtual const BYTE* read(DWORD offset, DWORD size);

protected:
	void init();

protected:
	/* this+ 0 */ //CMemFile baseclass_0;
	/* this+ 4 */ HANDLE m_hFile;
	/* this+ 8 */ HANDLE m_hFileMap;
	/* this+12 */ DWORD m_dwFileSize;
	/* this+16 */ DWORD m_dwOpenOffset;
	/* this+20 */ DWORD m_dwOpenSize;
	/* this+24 */ DWORD m_dwFileMappingSize;
	/* this+28 */ DWORD m_dwAllocationGranuarity; // mask
	/* this+32 */ const BYTE* m_pFile;
	/* this+36 */ mystd::vector<BYTE> m_pFileBuf;
};
