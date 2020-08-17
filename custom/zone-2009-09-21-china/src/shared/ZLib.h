#pragma once


class CZLib
{
	/* this+0 */ //const CZLib::`vftable'

	public: CZLib::CZLib(void);
	public: virtual CZLib::~CZLib(void);

	/// Compresses the source buffer into the destination buffer.
	/// Upon exit, destLen is the actual size of the compressed buffer.
	/// @param sourceLen byte length of the source buffer
	/// @param destLen total size of the destination buffer (at least compressBound(sourceLen))
	/// @param level compression level, 0..9 (0 = no compression, 1 = best speed, 9 = best compression)
	/// @return Z_OK if success, Z_MEM_ERROR if not enough memory, Z_BUF_ERROR if not enough room in the output buffer, Z_STREAM_ERROR if level parameter is invalid
	public: int CZLib::Compress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen, int level);

	/// Decompresses the source buffer into the destination buffer.
	/// Upon exit, destLen is the actual size of the compressed buffer.
	/// @param sourceLen byte length of the source buffer
	/// @param destLen total size of the destination buffer (large enough to hold the entire uncompressed data)
	/// @return Z_OK if success, Z_MEM_ERROR if not enough memory, Z_BUF_ERROR if not enough room in the output buffer, Z_DATA_ERROR if input data was corrupted or incomplete
	public: int CZLib::Uncompress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen);

private:
	static hook_method<void (CZLib::*)(void)> CZLib::_CZLib;
	static hook_method<void (CZLib::*)(void)> CZLib::__CZLib;
	static hook_method<int (CZLib::*)(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen, int level)> CZLib::_Compress;
	static hook_method<int (CZLib::*)(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen)> CZLib::_Uncompress;
};
