#include "Base/CDec.h"
#include "Base/GPak.h"
#include <zlib/zlib.h>
////////////////////////////////////////


#pragma pack(push,1)
struct GrfHeader
{
	/* this+ 0 */ char magic[16];
	/* this+16 */ char key[14];
	/* this+30 */ DWORD offset;
	/* this+34 */ DWORD seed;
	/* this+38 */ DWORD filecount;
	/* this+42 */ DWORD version;
};
C_ASSERT( sizeof GrfHeader == 46 );
#pragma pack(pop)


#pragma pack(push,1)
struct PakPackFile
{
	/* this+ 0 */ DWORD m_compressSize;
	/* this+ 4 */ DWORD m_dataSize;
	/* this+ 8 */ DWORD m_size;
	/* this+12 */ BYTE m_type;
	/* this+13 */ DWORD m_Offset;
};
C_ASSERT( sizeof PakPackFile == 17 );
#pragma pack(pop)


class PakPrtLess : public mystd::binary_function<const PakPack&, const PakPack&, bool>
{
public:
	bool operator()(const PakPack& left, const CHash& right)
	{
		return ( left.m_fName < right );
	}

	bool operator()(const PakPack& left, const PakPack& right)
	{
		return ( left.m_fName < right.m_fName );
	}
};


////////////////////////////////////////


CGPak::CGPak()
{
	this->CGPak::Init();
}


CGPak::~CGPak()
{
}


bool CGPak::Open(CMemFile* memFile)
{
	if( memFile == NULL )
		return false;

	m_memFile = memFile;
	GrfHeader* grf = (GrfHeader*)memFile->read(0, sizeof(GrfHeader));

	if( memcmp(grf->magic, "Master of Magic", sizeof(grf->magic)) != 0 )
		return false;

	m_FileVer = grf->version;
	m_FileCount = grf->filecount - grf->seed - 7;
	m_PakInfoOffset = sizeof(GrfHeader) + grf->offset;

	if( (m_FileVer & 0xFF00) == 0x100 && this->CGPak::OpenPak01() == true )
		return true;
	else
	if( (m_FileVer & 0xFF00) == 0x200 && this->CGPak::OpenPak02() == true )
		return true;
	else
	{// reset state
		this->CGPak::Init();
		return false;
	}
}


bool CGPak::GetInfo(const CHash& fName, PakPack* pakPack)
{
	mystd::vector<PakPack>::const_iterator it = mystd::lower_bound(m_PakPack.begin(), m_PakPack.end(), fName, PakPrtLess());
	if( it == m_PakPack.end() || it->m_fName != fName )
		return false;

	if( pakPack != NULL )
		memcpy(pakPack, &*it, sizeof(*pakPack));

	return true;
}


bool CGPak::GetData(const PakPack& pakPack, void* buffer)
{
	const BYTE* encdata = m_memFile->read(sizeof(GrfHeader) + pakPack.m_Offset, pakPack.m_dataSize);
	if( encdata == NULL )
		return false;

	char seed[8];
	CDec dec(this->CGPak::MakeSeed(pakPack.m_fName.c_str(), seed));

	const BYTE* compdata;
	DWORD DecodedSize = 0;

	if( pakPack.m_type & PAKPACK_TYPE_FULLENCRYPT )
	{
		int mod = 0;
		for( DWORD i = pakPack.m_compressSize; i != 0; i = i / 10 )
			++mod;
		if( mod < 1 )
			mod = 1;

		dec.CDec::DataDecrypt((char*)encdata, pakPack.m_dataSize, (char*)&m_pDecBuf.front(), (int*)&DecodedSize, mod);
		compdata = &m_pDecBuf.front();
	}
	else
	if( pakPack.m_type & PAKPACK_TYPE_HEADERENCRYPT )
	{
		dec.CDec::DataDecryptHeader((char*)encdata, pakPack.m_dataSize, (char*)&m_pDecBuf.front(), (int*)&DecodedSize);
		compdata = &m_pDecBuf.front();
	}
	else
	{
		DecodedSize = pakPack.m_compressSize;
		compdata = encdata;
	}

	if( pakPack.m_type & PAKPACK_TYPE_FILE )
	{
		DWORD size = pakPack.m_size;
		uncompress((BYTE*)buffer, &size, compdata, DecodedSize);
	}
	else
	{// directory?
		memcpy(buffer, &m_pDecBuf.front(), pakPack.m_size); //FIXME: should be 'compdata' (m_pDecBuf is not filled on all code paths)
	}

	return true;
}


void CGPak::Init()
{
	m_FileVer = 0;
	m_FileCount = 0;
	m_PakInfoOffset = 0;
	m_PakInfoSize = 0;
	m_PakPack.clear();
	m_memFile = NULL;
}


BOOL CGPak::IsNeverEncrypt(const char* fileName)
{
	static const char EncExtString[4][5] = { ".gnd", ".gat", ".act", ".str" };

	const char* ext = strrchr(fileName, '.');

	if( ext != NULL )
		for( int i = 0; i < countof(EncExtString); ++i )
			if( stricmp(ext, EncExtString[i]) == 0 )
				return TRUE;

	return FALSE;
}


char* CGPak::MakeSeed(const char* fileName, char* seed)
{
	const char* name = fileName;
	const char* name_end = fileName + strlen(fileName);

	for( const char* p = name; p < name_end; ++p )
		if( *p == '\\' || *p == '/' )
			name = p + 1;

	int len = name_end - name;
	if( len >= 6 )
	{
		seed[0] = 'n';
		memcpy(&seed[1], name, 6);
		seed[7] = 'k';
	}
	else
	{
		seed[0] = 'n';
		memcpy(&seed[1], name, len);
		memcpy(&seed[1 + len], name, 6 - len); //FIXME: OOB-read when len < 3
		seed[7] = 'k';
	}

	return seed;
}


bool CGPak::OpenPak01()
{
	m_PakInfoSize = m_memFile->size() - m_PakInfoOffset;
	const BYTE* pData = m_memFile->read(m_PakInfoOffset, m_PakInfoSize);
	m_PakPack.resize(m_FileCount);

	DWORD decBufSize = 0;
	const BYTE* pFileIter = pData;

	for( unsigned int a = 0; a < m_FileCount; ++a )
	{
		char fName[256];

		DWORD nameEntryLen = *reinterpret_cast<const DWORD*>(pFileIter);
		pFileIter += 4;

		if( m_FileVer <= 0x100 )
		{
			const char* name = reinterpret_cast<const char*>(pFileIter + 0);
			const DWORD nameLen = nameEntryLen;
			this->CGPak::ModifyString(fName, name); //FIXME: may exit too early due to '\0' bytes in data
		}
		else
		if( m_FileVer <= 0x103 )
		{
//			const WORD unknown1 = *reinterpret_cast<const WORD*>(pFileIter + 0);
			const char* name = reinterpret_cast<const char*>(pFileIter + 2);
			const DWORD nameLen = nameEntryLen - 2 - 4;
//			const DWORD unknown2 = *reinterpret_cast<const DWORD*>(pFileIter + 2 + nameLen);
			this->CGPak::ModifyString(fName, name, nameLen);

			int seednum;
			if( m_FileVer == 0x101 )
				seednum = 95001 - 2 * a;
			else
				seednum = 95007 - 3 * ((5 * a + 1) / 2);

			if( seednum < 10000 )
				seednum += 85000;

			char strbuf[20];
			itoa(seednum, strbuf, 10);

			char seed[8];
			seed[0] = 'P';
			seed[1] = 'r';
			memcpy(&seed[2], strbuf, 5);
			seed[7] = 'e';

			CDec dec(seed);
			char validfName[256];
			int DecSize;

			dec.CDec::DataDecrypt(fName, nameLen, validfName, &DecSize, 1);
			strcpy(fName, validfName);
		}
		else
		{// > 0x103
			return false;
		}

		pFileIter += nameEntryLen;

		const PakPackFile* file = (const PakPackFile*)pFileIter;
		pFileIter += sizeof(PakPackFile);

		PakPack* pack = &m_PakPack[a];
		pack->m_compressSize = file->m_compressSize - file->m_size - 715;
		pack->m_dataSize     = file->m_dataSize - 37579;
		pack->m_size         = file->m_size;
		pack->m_type         = file->m_type;
		pack->m_Offset       = file->m_Offset;
		pack->m_fName.CHash::SetString(fName);
		pack->m_type |= ( this->CGPak::IsNeverEncrypt(fName) ) ? PAKPACK_TYPE_HEADERENCRYPT : PAKPACK_TYPE_FULLENCRYPT;

		if( decBufSize <= pack->m_dataSize )
			decBufSize  = pack->m_dataSize;
	}

	mystd::sort(m_PakPack.begin(), m_PakPack.end(), PakPrtLess());
	m_pDecBuf.resize(decBufSize);

	return true;
}


bool CGPak::OpenPak02()
{
	const BYTE* pPakHeader = m_memFile->read(m_PakInfoOffset, 8);
	const DWORD dwCompressedSize = *reinterpret_cast<const DWORD*>(pPakHeader + 0);
	const DWORD dwRealSize = *reinterpret_cast<const DWORD*>(pPakHeader + 4);

	m_PakInfoSize = 8 + dwCompressedSize;
	const BYTE* pCompressedData = m_memFile->read(8 + m_PakInfoOffset, dwCompressedSize);

	DWORD size = 8 + dwRealSize;
	mystd::vector<BYTE> pakInfoBuffer(size);
	if( uncompress(&pakInfoBuffer.front(), &size, pCompressedData, dwCompressedSize) != Z_OK )
		return false;

	m_PakPack.resize(m_FileCount);

	DWORD decBufSize = 0;
	const BYTE* pFileIter = &pakInfoBuffer.front();

	for( DWORD a = 0; a < m_FileCount; ++a )
	{
		const char* name = (const char*)pFileIter;
		pFileIter += strlen(name) + 1;
		const PakPackFile* file = (const PakPackFile*)pFileIter;
		pFileIter += sizeof(PakPackFile);

		PakPack* pack = &m_PakPack[a];
		pack->m_compressSize = file->m_compressSize;
		pack->m_dataSize     = file->m_dataSize;
		pack->m_size         = file->m_size;
		pack->m_type         = file->m_type;
		pack->m_Offset       = file->m_Offset;
		pack->m_fName.CHash::SetString(name);

		if( decBufSize <= pack->m_dataSize )
			decBufSize  = pack->m_dataSize;
	}

	mystd::sort(m_PakPack.begin(), m_PakPack.end(), PakPrtLess());
	m_pDecBuf.resize(decBufSize);

	return true;
}


char CGPak::ChangeLHBit_BYTE(char ch)
{
	return (ch << 4) & 0xF0 | (ch >> 4) & 0x0F;
}


void CGPak::ModifyString(char* dest, const char* src)
{
	int bufferSize = strlen(src) + 1;
	for( int i = 0; i < bufferSize; ++i )
		dest[i] = this->CGPak::ChangeLHBit_BYTE(src[i]);
}


void CGPak::ModifyString(char* dest, const char* src, int bufferSize)
{
	for( int i = 0; i < bufferSize; ++i )
		dest[i] = this->CGPak::ChangeLHBit_BYTE(src[i]);
}
