#pragma once
class CGPak;
class CMemFile;


class CFileMgr
{
public:
	CFileMgr();
	~CFileMgr();

public:
	bool AddPak(const char* name);
	void* GetData(const char* name, DWORD* size);
	void* AllocData(DWORD size); /// @custom
	void ReleaseData(void* data);
	bool IsDataExist(const char* name);

protected:
	void* GetPak(const char* name, DWORD* size);
	void* GetFile(const char* name, DWORD* size);
	bool IsFileExist(const char* name);

protected:
	/* this+0 */ mystd::list<mystd::pair<CMemFile*,CGPak*>> m_pakList;
};
