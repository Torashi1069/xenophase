#pragma once


class CFile
{
public:
	enum OpenFlags
	{
		modeRead       = 0x0,
		modeWrite      = 0x1,
		modeReadWrite  = 0x2,

		shareCompat    = 0x00,
		shareExclusive = 0x10,
		shareDenyWrite = 0x20,
		shareDenyRead  = 0x30,
		shareDenyNone  = 0x40,

		modeNoInherit  = 0x80,
		modeCreate     = 0x1000,
		modeNoTruncate = 0x2000,

		typeText       = 0x4000,
		typeBinary     = 0x8000,
	};

public:
	enum SeekPosition
	{
		begin   = 0,
		current = 1,
		end     = 2,
	};

public:
	CFile();
	~CFile();

public:
	bool Open(const char* fName, unsigned int nOpenFlags);
	bool Read(void* lpBuf, size_t nCount);
	bool Write(const void* lpBuf, size_t nCount);
	bool Seek(off_t lOff, size_t nFrom);
	void Close();
	char* GetFileName();
	DWORD GetLength();
	const unsigned char* GetBuf();
	const void* GetCurBuf(int nOffset);
	static bool IsFileExist(const char* fName);

protected:
	static void MakeFileName(char* output, const char* input);

protected:
	/* this+ 0 */ HANDLE m_hFile;
	/* this+ 4 */ char* m_buf;
	/* this+ 8 */ DWORD m_cursor;
	/* this+12 */ DWORD m_size;
	/* this+16 */ char m_fileName[128];
};
