#include "Version.h"
#include "hash/crc.hpp"
#include "network/SocketAddress.hpp"


////////////////////////////////////////


static uint32_t HashFile(const char* path)
{
	uint32_t result;

	HANDLE hFile = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ|FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if( hFile == INVALID_HANDLE_VALUE )
	{
		FatalAppExitA(0, "DLL init fatal error.");
		return NULL;
	}

	DWORD size = GetFileSize(hFile, NULL);
	BYTE* buf = (BYTE*)malloc(size);

	DWORD read;
	ReadFile(hFile, buf, size, &read, NULL);
	CloseHandle(hFile);

	result = CRC::crc32(buf, size);
	free(buf);

	return result;
}


/// CRC32 hash of main application's executable.
uint32_t EXEHASH()
{
#ifdef NDEBUG
	static uint32_t hash = HashFile(EXEPATH());
#else
	static uint32_t hash = HashFile("rfexe.exe");
#endif
	return hash;
}


/// CRC32 hash of this dll module.
uint32_t DLLHASH()
{
#ifdef NDEBUG
	static uint32_t hash = HashFile(DLLPATH());
#else
	static uint32_t hash = HashFile("rfexe.dll");
#endif
	return hash;
}


////////////////////////////////////////


/// Fetch the PE header timestamp from memory.
uint32_t EXEDATE()
{
	const IMAGE_DOS_HEADER* dh = (IMAGE_DOS_HEADER*)GetModuleHandleA(NULL);
	const IMAGE_NT_HEADERS* nh = (IMAGE_NT_HEADERS*)((char*)dh + dh->e_lfanew);
	return (uint32_t)nh->FileHeader.TimeDateStamp;
}


/// Identify local executable version using PE header timestamp.
std::string LOCALVER()
{
	static const struct {
		uint32_t timestamp;
		const char* version;
	} verdb[] = {
		{ 1078812469, "Client 2004-03-09a Sakexe Taiwan" },
		{ 1253607942, "Client 2009-09-22a Ragexe China" },
		{ 1277195531, "Client 2010-06-22a RagexeRE Korea" },
		{ 1328588105, "Client 2012-02-07b RagexeRE Korea" },
		{ 1382409260, "Client 2013-10-22a Ragexe France" },
	};

	uint32_t timestamp = EXEDATE();

	for( size_t i = 0; i < countof(verdb); ++i )
		if( verdb[i].timestamp == timestamp )
			return verdb[i].version;

	return "unknown";
}


// Identify remote server version using address and port.
std::string REMOTEVER(SOCKET s)
{
	static const struct {
		SocketAddress addr;
		const char* version;
	} verdb[] = {
		// defaults (Ragnarok Frontier)
		{ "0.0.0.0:6900", "Account 2006-03-07 USA" },
		{ "0.0.0.0:6901", "Account 2006-03-07 USA" },
		{ "0.0.0.0:7000", "Character 2007-04-27 Brazil" },
		{ "0.0.0.0:7001", "Character 2007-04-27 Brazil" },
		{ "0.0.0.0:4501", "Zone 2009-09-21 China" },
		{ "0.0.0.0:4503", "Zone 2009-09-21 China" },
		{ "0.0.0.0:4504", "Zone 2009-09-21 China" },
		{ "0.0.0.0:4505", "Zone 2009-09-21 China" },
	};

	SocketAddress addr;
	if( !addr.fromsock(s) )
		return "error";

	for( size_t i = 0; i < countof(verdb); ++i )
		if( verdb[i].addr == addr )
			return verdb[i].version;

	return "unknown";
}


////////////////////////////////////////
