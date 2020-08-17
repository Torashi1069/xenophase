#pragma once
#include "Base/Hash.h"
#include "Base/MemFile.h"


struct PakPack
{
	/* this+ 0 */ DWORD m_dataSize;
	/* this+ 4 */ DWORD m_compressSize;
	/* this+ 8 */ DWORD m_size;
	/* this+12 */ DWORD m_Offset;
	/* this+16 */ char m_type;
	/* this+20 */ CHash m_fName;

	#define PAKPACK_TYPE_FILE          0x01
	#define PAKPACK_TYPE_FULLENCRYPT   0x02
	#define PAKPACK_TYPE_HEADERENCRYPT 0x04
};


class CGPak
{
public:
	CGPak();
	virtual ~CGPak();

public:
	bool Open(CMemFile* memFile);
	bool GetInfo(const CHash& fName, PakPack* pakPack);
	bool GetData(const PakPack& pakPack, void* buffer);

protected:
	void Init();
	char ChangeLHBit_BYTE(char ch);
	void ModifyString(char* dest, const char* src);
	void ModifyString(char* dest, const char* src, int bufferSize);
	BOOL IsNeverEncrypt(const char* fileName);
	char* MakeSeed(const char* fileName, char* seed);
	bool OpenPak01();
	bool OpenPak02();

protected:
	/* this+ 0 */ //const CGPak::`vftable';
	/* this+ 4 */ DWORD m_FileVer;
	/* this+ 8 */ DWORD m_FileCount;
	/* this+12 */ DWORD m_PakInfoOffset;
	/* this+16 */ DWORD m_PakInfoSize;
	/* this+20 */ mystd::vector<PakPack> m_PakPack;
	/* this+36 */ mystd::vector<BYTE> m_pDecBuf;
	/* this+52 */ CMemFile* m_memFile;
};
