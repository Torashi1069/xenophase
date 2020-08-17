#include "codepage.h"
#include <memory> // std::auto_ptr<>
#include "common.h" // MSVC
#include "stdc.h" // size_t, stricmp()


#if defined(WITH_ICONV)
#include <iconv.h>
#elif defined(MSVC)
#include <windows.h>
#define CP_UHC 949
#define CP_EUCKR 51949
UINT cpname2cpid(const char* cpname)
{// poor man's codepage id lookup
	return ( stricmp(cpname, "utf-8"   ) == 0 ) ? CP_UTF8
	     : ( stricmp(cpname, "uhc"     ) == 0 ) ? CP_UHC
	     : ( stricmp(cpname, "euc-kr"  ) == 0 ) ? CP_EUCKR
	     :                                        -1;
}
#endif


/// Convert a string from one character encoding to another.
///
/// @param in_buf Input string
/// @param in_size Input string size, in bytes
/// @param in_cpname Input string codepage name
/// @param out_buf Output string buffer
/// @param out_size Output string buffer size, in bytes
/// @param out_cpname Output string codepage name
/// 
bool MultiByteToMultiByte(const char* in_buf, size_t in_size, const char* in_cpname, char* out_buf, size_t out_size, const char* out_cpname)
{
#if defined(WITH_ICONV)

	iconv_allocation_t ica;
	iconv_t ic = (iconv_t)&ica;

	if( iconv_open_into(out_cpname, in_cpname, &ica) != 0 )
		return false;

	const char* inp = in_buf;
	char* outp = out_buf;
	size_t insz = in_size;
	size_t outsz = out_size;
	if( iconv(ic, &inp, &insz, &outp, &outsz) != 0 || insz != 0 )
		return false;

	return true;

#elif defined(MSVC)

	UINT in_cp = cpname2cpid(in_cpname);
	UINT out_cp = cpname2cpid(out_cpname);
	if( in_cp == -1 || out_cp == 1 )
		return false;

	int wlen = MultiByteToWideChar(in_cp, MB_ERR_INVALID_CHARS, in_buf, in_size, NULL, 0);
	if( wlen == 0 )
		return false;

	wchar_t* wbuf = new wchar_t[wlen];
	std::auto_ptr<wchar_t> autorelease(wbuf);
	if( wbuf == NULL )
		return false;

	int wlen2 = MultiByteToWideChar(in_cp, MB_ERR_INVALID_CHARS, in_buf, in_size, wbuf, wlen);
	if( wlen2 == 0 || wlen2 != wlen )
		return false; // shouldn't happen

	BOOL bInvalidChar = FALSE;
	BOOL* pInvalidChar = &bInvalidChar;
	if( out_cp == CP_UTF8 ) pInvalidChar = NULL; // must be null

	int cblen = WideCharToMultiByte(out_cp, 0, wbuf, wlen, out_buf, out_size, NULL, pInvalidChar);
	if( cblen == 0 || bInvalidChar == TRUE )
		return false;

	return true;

#else

	return false; // no codepage conversion mechanism available

#endif
}
