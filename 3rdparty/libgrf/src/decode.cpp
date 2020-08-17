#include "decode.h"
#include "des.h" // des_decrypt(), des_decrypt_block(), BIT64
#include "libgrf.h" // GRF_FLAG_*
#include <platform/stdc.h> // stricmp(), size_t, uint8_t
#include <platform/macro.h> // countof()


/// Substitutes some specific values for others, leaves rest intact. Obfuscation.
/// NOTE: Operation is symmetric (calling it twice gives back the original input).
static uint8_t grf_substitution(uint8_t in)
{
	uint8_t out;
	
	switch( in )
	{
	case 0x00: out = 0x2B; break;
	case 0x2B: out = 0x00; break;
	case 0x6C: out = 0x80; break;
	case 0x01: out = 0x68; break;
	case 0x68: out = 0x01; break;
	case 0x48: out = 0x77; break;
	case 0x60: out = 0xFF; break;
	case 0x77: out = 0x48; break;
	case 0xB9: out = 0xC0; break;
	case 0xC0: out = 0xB9; break;
	case 0xFE: out = 0xEB; break;
	case 0xEB: out = 0xFE; break;
	case 0x80: out = 0x6C; break;
	case 0xFF: out = 0x60; break;
	default:   out = in;   break;
	}

	return out;
}


static void grf_shuffle_enc(BIT64* src)
{
	BIT64 out;

	out.b[0] = src->b[3];
	out.b[1] = src->b[4];
	out.b[2] = src->b[5];
	out.b[3] = src->b[0];
	out.b[4] = src->b[1];
	out.b[5] = src->b[6];
	out.b[6] = src->b[2];
	out.b[7] = grf_substitution(src->b[7]);

	*src = out;
}


static void grf_shuffle_dec(BIT64* src)
{
	BIT64 out;

	out.b[0] = src->b[3];
	out.b[1] = src->b[4];
	out.b[2] = src->b[6];
	out.b[3] = src->b[0];
	out.b[4] = src->b[1];
	out.b[5] = src->b[2];
	out.b[6] = src->b[5];
	out.b[7] = grf_substitution(src->b[7]);

	*src = out;
}


static void grf_decode_header(unsigned char* buf, size_t len)
{
	BIT64* p = (BIT64*)buf;
	size_t nblocks = len / sizeof(BIT64);
	size_t i;

	// first 20 blocks are all des-encrypted
	for( i = 0; i < 20 && i < nblocks; ++i )
		des_decrypt_block(&p[i]);

	// the rest is plaintext, done.
}


static void grf_decode_full(unsigned char* buf, size_t len, int cycle)
{
	BIT64* p = (BIT64*)buf;
	size_t nblocks = len / sizeof(BIT64);
	int dcycle, scycle;
	size_t i, j;

	// first 20 blocks are all des-encrypted
	for( i = 0; i < 20 && i < nblocks; ++i )
		des_decrypt_block(&p[i]);

	// after that only one of every 'dcycle' blocks is des-encrypted
	dcycle = cycle;

	// and one of every 'scycle' plaintext blocks is shuffled (starting from the 0th but skipping the 0th)
	scycle = 7;

	// so decrypt/de-shuffle periodically
	j = -1; // 0, adjusted to fit the ++j step
	for( i = 20; i < nblocks; ++i )
	{
		if( i % dcycle == 0 )
		{// decrypt block
			des_decrypt_block(&p[i]);
			continue;
		}

		++j;
		if( j % scycle == 0 && j != 0 )
		{// de-shuffle block
			grf_shuffle_dec(&p[i]);
			continue;
		}

		// plaintext, do nothing.
	}
}


/// Decodes grf data.
/// @param buf data to decode (in-place)
/// @param len length of the data
/// @param entry_type flags associated with the data
/// @param entry_len true (unaligned) length of the data
void grf_decode_data(uint8_t* buf, size_t len, uint8_t entry_type, int entry_len)
{
	if( entry_type & GRF_FLAG_MIXCRYPT )
	{// fully encrypted
		int digits;
		int cycle;
		int i;

		// compute number of digits of the entry length
		digits = 1;
		for( i = entry_len / 10; i != 0; i /= 10 )
			++digits;

		// choose size of gap between two encrypted blocks
		// digits:  0  1  2  3  4  5  6  7  8  9 ...
		//  cycle:  1  1  1  4  5 14 15 22 23 24 ...
		cycle = ( digits < 3 ) ? 1
		      : ( digits < 5 ) ? digits + 1
		      : ( digits < 7 ) ? digits + 9
		      :                  digits + 15;

		grf_decode_full(buf, len, cycle);
	}
	else
	if( entry_type & GRF_FLAG_DES )
	{// header encrypted
		grf_decode_header(buf, len);
	}
	else
	{// plaintext
		;
	}
}


static void NibbleSwap(uint8_t* src, int len)
{
	for( int i = 0; i < len; ++i )
		*src++ = (*src >> 4) | (*src << 4);
}


uint8_t* grf_decode_filename(uint8_t* buf, int len)
{
	for( int lop = 0; lop < len; lop += 8 )
	{
		NibbleSwap(&buf[lop],8);
		des_decrypt(&buf[lop],8);
	}

	return buf;
}


/// Compares file extension against known large file types.
/// @return true if the file should undergo full mixed mode decryption, and false otherwise.
bool grf_file_is_mixcrypt(const char* fname)
{
	// The file types below only use GRF_FLAG_DES, for performance reasons.
	static const char* nocrypt_list[] = { ".gnd", ".gat", ".act", ".str" };

	const char* ext = strrchr(fname, '.');
	if( ext != NULL )
		for( size_t i = 0; i < countof(nocrypt_list); ++i )
			if( stricmp(ext, nocrypt_list[i]) == 0 )
				return false;

	return true;
}
