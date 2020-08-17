#pragma once


class CPath
{
public:
	CPath() { };
	virtual ~CPath() { };

public:
	static bool AddBackslash(const char* src, char* dest);
	static bool IsRemotePath(const char* path);
	static DWORD AddConnection(const char* path, const char* account, const char* password);
	static DWORD CancelConnection(const char* path);
};


class CPathData : public CPath
{
private:
	/* this+ 0 */ //CPath baseclass_0;
	/* this+ 4 */ std::string m_path;
	/* this+32 */ std::string m_fileName;
	/* this+60 */ std::string m_filePath;

public:
	CPathData() { };
	virtual ~CPathData() { };

public:
	void Init(const char* path);
	CPathData& SetFileName(const char* filename);
	operator const char*();
	operator const std::string();
};
