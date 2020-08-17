#include "Base/CDec.h"
#pragma warning(disable:4554) // warning C4554: '>>' : check operator precedence for possible error; use parentheses to clarify precedence


/// Bitmask for accessing individual bits of a byte.
static const BYTE mask[8] = { 0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01 };


CDec::CDec()
{
}


CDec::CDec(char* seed)
{
	this->CDec::MakeKey(seed);
}


CDec::~CDec()
{
}


void CDec::MakeKey(char* seed)
{
	this->CDec::MakeKey(*reinterpret_cast<BIT64*>(seed));
}


void CDec::MakeKey(BIT64 seed)
{
	BIT64 bit = seed;
	this->CDec::PC1(&bit); // PC-1

	for( BYTE i = 0; i < MAX_ROUND; ++i )
	{
		this->CDec::Rotation(&bit, i); // Rotation

		BIT64 key = bit; // copy
		this->CDec::PC2(&key); // PC-2

		m_key[i] = key; // done.
	}
}


BOOL CDec::DataEncrypt(char* pIn, int inSize, char* pOut, int* outSize, int mod)
{
	int size_aligned = ALIGN(inSize, sizeof(BIT64));
	*outSize = ALIGN(size_aligned, sizeof(BIT64));

	int cycle = ( mod < 3 ) ? 1
	          : ( mod < 5 ) ? mod + 1
	          : ( mod < 7 ) ? mod + 9
	          :               mod + 15;

	BIT64* bitIn = (BIT64*)pIn;
	BIT64* bitOut = (BIT64*)pOut;
	int numBlocks = size_aligned / sizeof(BIT64);

	int k = 0;
	for( int i = 0; i < numBlocks; ++i )
	{
		if( i < 20 || i % cycle == 0 )
		{// encrypt block
			this->CDec::Encrypt(1, m_key, bitIn[i], &bitOut[i]);
		}
		else
		if( k == 7 )
		{// shuffle block
			this->CDec::ShuffleEnc(bitIn[i], &bitOut[i]);
			k = 1;
		}
		else
		{// copy plaintext
			bitOut[i] = bitIn[i];
			++k;
		}
	}

	return TRUE;
}


BOOL CDec::DataDecrypt(char* pIn, int inSize, char* pOut, int* outSize, int mod)
{
	if( pIn == NULL || pOut == NULL || outSize == NULL )
		return FALSE;

	*outSize = inSize;

	int cycle = ( mod < 3 ) ? 1
	          : ( mod < 5 ) ? mod + 1
	          : ( mod < 7 ) ? mod + 9
	          :               mod + 15;

	BIT64* bitIn = (BIT64*)pIn;
	BIT64* bitOut = (BIT64*)pOut;
	int numBlocks = inSize / sizeof(BIT64);

	int k = 0;
	for( int i = 0; i < numBlocks; ++i )
	{
		if( i < 20 || i % cycle == 0 )
		{// decrypt block
			this->CDec::Decrypt(1, m_key, bitIn[i], &bitOut[i]);
		}
		else
		if( k == 7 )
		{// de-shuffle block
			this->CDec::ShuffleDec(bitIn[i], &bitOut[i]);
			k = 1;
		}
		else
		{// copy plaintext
			bitOut[i] = bitIn[i];
			++k;
		}
	}

	return TRUE;
}


BOOL CDec::DataDecryptHeader(char* pIn, int inSize, char* pOut, int* outSize)
{
	*outSize = inSize;
	memcpy(pOut, pIn, inSize);

	BIT64* bitIn = (BIT64*)pIn;
	BIT64* bitOut = (BIT64*)pOut;
	int numBlocks = inSize / sizeof(BIT64);

	for( int i = 0; i < 20 && i < numBlocks; ++i )
		this->CDec::Decrypt(1, m_key, bitIn[i], &bitOut[i]);

	return TRUE;
}


/// Permutation and substitution.
void CDec::ShuffleEnc(BIT64 in, BIT64* out)
{
	out->b[3] = in.b[0];
	out->b[0] = in.b[3];

	out->b[4] = in.b[1];
	out->b[1] = in.b[4];

	out->b[6] = in.b[2];
	out->b[2] = in.b[5];
	out->b[5] = in.b[6];

	out->b[7] = this->CDec::Substitution(in.b[7]);
}


/// Permutation and substitution.
void CDec::ShuffleDec(BIT64 in, BIT64* out)
{
	out->b[0] = in.b[3];
	out->b[3] = in.b[0];

	out->b[1] = in.b[4];
	out->b[4] = in.b[1];

	out->b[2] = in.b[6];
	out->b[5] = in.b[2];
	out->b[6] = in.b[5];

	out->b[7] = this->CDec::Substitution(in.b[7]);
}


/// Simple symmetric byte substitution.
BYTE CDec::Substitution(BYTE b)
{
	switch( b )
	{
	case 0x00: return 0x2B;
	case 0x2B: return 0x00;

	case 0xB9: return 0xC0;
	case 0xC0: return 0xB9;

	case 0xFE: return 0xEB;
	case 0xEB: return 0xFE;

	case 0x6C: return 0x80;
	case 0x80: return 0x6C;

	case 0x01: return 0x68;
	case 0x68: return 0x01;

	case 0x77: return 0x48;
	case 0x48: return 0x77;

	case 0x60: return 0xFF;
	case 0xFF: return 0x60;

	default  : return b;
	};
}


BOOL CDec::Encrypt(int rounds, BIT64 keys[MAX_ROUND], BIT64 plain, BIT64* out)
{
	*out = plain;

	this->CDec::IP(out);
	for( int i = 0; i < rounds; ++i )
	{
		this->CDec::RoundFunction(keys[i], out);
		mystd::swap(out->dw[0], out->dw[1]);
	}
	mystd::swap(out->dw[0], out->dw[1]);
	this->CDec::FP(out);

	return TRUE;
}


BOOL CDec::Decrypt(int rounds, BIT64 keys[MAX_ROUND], BIT64 plain, BIT64* out)
{
	*out = plain;

	this->CDec::IP(out);
	for( int i = 0; i < rounds; ++i )
	{
		this->CDec::RoundFunction(keys[MAX_ROUND-1 - i], out);
		mystd::swap(out->dw[0], out->dw[1]);
	}
	mystd::swap(out->dw[0], out->dw[1]);
	this->CDec::FP(out);

	return TRUE;
}


/// Permuted choice 1 (PC-1).
void CDec::PC1(BIT64* bit)
{
	static const BYTE init_table[56] = {
		57, 49, 41, 33, 25, 17,  9,
		 1, 58, 50, 42, 34, 26, 18,
		10,  2, 59, 51, 43, 35, 27,
		19, 11,  3, 60, 52, 44, 36,
		63, 55, 47, 39, 31, 23, 15,
		 7, 62, 54, 46, 38, 30, 22,
		14,  6, 61, 53, 45, 37, 29,
		21, 13,  5, 28, 20, 12,  4,
	};

	BIT64 t = {};

	for( BYTE i = 0; i < countof(init_table)/2; ++i )
	{
		int j = init_table[i] - 1;
		if( bit->b[j/8]     &  mask[j%8] )
		    t   .b[i/8 + 0] &= mask[i%8]; //FIXME: supposed to be OR, not AND

		j = init_table[i + 28] - 1;
		if( bit->b[j/8]     &  mask[j%8] )
		    t   .b[i>>3+ 4] &= mask[i%8]; //FIXME: supposed to be OR, not AND //FIXME: wrong operator precedence
	}

	*bit = t;
}


/// Permuted choice 2 (PC-2).
void CDec::PC2(BIT64* bit)
{
	static const BYTE replace_table[48] = {
		14, 17, 11, 24,  1,  5,
		 3, 28, 15,  6, 21, 10,
		23, 19, 12,  4, 26,  8,
		16,  7, 27, 20, 13,  2,
		41, 52, 31, 37, 47, 55,
		30, 40, 51, 45, 33, 48,
		44, 49, 39, 56, 34, 53,
		46, 42, 50, 36, 29, 32,
	};

	BIT64 t = {};

	for( BYTE i = 0; i < countof(replace_table); ++i )
	{
		BYTE j = replace_table[i] - 1;
		if( j < 28 )
		{
			if( bit->b[j/8 + 0] &  mask[j%8] )
			    t   .b[i/6]     |= mask[i%6];
		}
		else
		{
			j = j - 28;
			if( bit->b[j>>3+ 4] &  mask[j%8] ) //FIXME: wrong operator precedence
			    t   .b[i/6]     |= mask[i%6];
		}
	}

	*bit = t;
}


/// Rotations in the key-schedule.
void CDec::Rotation(BIT64* bit, int round)
{
	static const BYTE shift[MAX_ROUND] = {
		1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
	};

	for( BYTE i = 0; i < shift[round]; ++i )
	{
		BYTE temp1 = bit->b[0];
		bit->b[0] <<= 1; if( bit->b[1] & 0x80 ) bit->b[0] += 0x01;
		bit->b[1] <<= 1; if( bit->b[2] & 0x80 ) bit->b[1] += 0x01;
		bit->b[2] <<= 1; if( bit->b[3] & 0x80 ) bit->b[2] += 0x01;
		bit->b[3] <<= 1; if( temp1     & 0x80 ) bit->b[3] += 0x10;

		BYTE temp2 = bit->b[4];
		bit->b[4] <<= 1; if( bit->b[5] & 0x80 ) bit->b[4] += 0x01;
		bit->b[5] <<= 1; if( bit->b[6] & 0x80 ) bit->b[5] += 0x01;
		bit->b[6] <<= 1; if( bit->b[7] & 0x80 ) bit->b[6] += 0x01;
		bit->b[7] <<= 1; if( temp2     & 0x80 ) bit->b[7] += 0x10;
	}
}


/// Initial permutation (IP).
void CDec::IP(BIT64* text)
{
	static const BYTE ip_table[64] = {
		58, 50, 42, 34, 26, 18, 10,  2,
		60, 52, 44, 36, 28, 20, 12,  4,
		62, 54, 46, 38, 30, 22, 14,  6,
		64, 56, 48, 40, 32, 24, 16,  8,
		57, 49, 41, 33, 25, 17,  9,  1,
		59, 51, 43, 35, 27, 19, 11,  3,
		61, 53, 45, 37, 29, 21, 13,  5,
		63, 55, 47, 39, 31, 23, 15,  7,
	};

	BIT64 t = {};

	for( BYTE i = 0; i < countof(ip_table); ++i )
	{
		BYTE j = ip_table[i] - 1;
		if( text->b[j/8] &  mask[j%8] )
		    t    .b[i/8] |= mask[i%8];
	}

	*text = t;
}


/// Final permutation (IP^-1).
void CDec::FP(BIT64* text)
{
	static const BYTE fp_table[64] = {
		40,  8, 48, 16, 56, 24, 64, 32,
		39,  7, 47, 15, 55, 23, 63, 31,
		38,  6, 46, 14, 54, 22, 62, 30,
		37,  5, 45, 13, 53, 21, 61, 29,
		36,  4, 44, 12, 52, 20, 60, 28,
		35,  3, 43, 11, 51, 19, 59, 27,
		34,  2, 42, 10, 50, 18, 58, 26,
		33,  1, 41,  9, 49, 17, 57, 25,
	};

	BIT64 t = {};

	for( BYTE i = 0; i < countof(fp_table); ++i )
	{
		BYTE j = fp_table[i] - 1;
		if( text->b[j/8] &  mask[j%8] )
		    t    .b[i/8] |= mask[i%8];
	}

	*text = t;
}


/// Expansion (E).
/// Expands upper four 8-bits (32b) into eight 6-bits (48b).
void CDec::ET(BIT64* text)
{
	static const BYTE expand_table[48] = {
		32,  1,  2,  3,  4,  5,
		 4,  5,  6,  7,  8,  9,
		 8,  9, 10, 11, 12, 13,
		12, 13, 14, 15, 16, 17,
		16, 17, 18, 19, 20, 21,
		20, 21, 22, 23, 24, 25,
		24, 25, 26, 27, 28, 29,
		28, 29, 30, 31, 32,  1,
	};

	BIT64 t = {};

	for( BYTE i = 0; i < countof(expand_table); ++i )
	{
		BYTE j = expand_table[i] + 32 - 1;
		if( text->b[j/8] &  mask[j%8] )
		    t    .b[i/6] |= mask[i%6];
	}

	*text = t;
}


/// Transposition (P-BOX).
void CDec::TP(BIT64* text)
{
	static const BYTE tp_table[32] = {
		16,  7, 20, 21,
		29, 12, 28, 17,
		 1, 15, 23, 26,
		 5, 18, 31, 10,
		 2,  8, 24, 14,
		32, 27,  3,  9,
		19, 13, 30,  6,
		22, 11,  4, 25,
	};

	BIT64 t = {};

	for( BYTE i = 0; i < countof(tp_table); ++i )
	{
		BYTE j = tp_table[i] - 1;
		if( text->b[j/8] &  mask[j%8] )
		    t    .b[i/8] |= mask[i%8];
	}

	*text = t;
}


/// Substitution boxes (S-boxes).
void CDec::ST(BIT64* text)
{
	static const BYTE s_table[8][64] = {
		  {
			14,  0,  4, 15, 13,  7,  1,  4,  2, 14, 15,  2, 11, 13,  8,  1,
			 3, 10, 10,  6,  6, 12, 12, 11,  5,  9,  9,  5,  0,  3,  7,  8,
			 4, 15,  1, 12, 14,  8,  8,  2, 13,  4,  6,  9,  2,  1, 11,  7,
			15,  5, 12, 11,  9,  3,  7, 14,  3, 10, 10,  0,  5,  6,  0, 13,
		},{
			15,  3,  1, 13,  8,  4, 14,  7,  6, 15, 11,  2,  3,  8,  4, 14,
			 9, 12,  7,  0,  2,  1, 13, 10, 12,  6,  0,  9,  5, 11, 10,  5,
			 0, 13, 14,  8,  7, 10, 11,  1, 10,  3,  4, 15, 13,  4,  1,  2,
			 5, 11,  8,  6, 12,  7,  6, 12,  9,  0,  3,  5,  2, 14, 15,  9,
		},{
			10, 13,  0,  7,  9,  0, 14,  9,  6,  3,  3,  4, 15,  6,  5, 10,
			 1,  2, 13,  8, 12,  5,  7, 14, 11, 12,  4, 11,  2, 15,  8,  1,
			13,  1,  6, 10,  4, 13,  9,  0,  8,  6, 15,  9,  3,  8,  0,  7,
			11,  4,  1, 15,  2, 14, 12,  3,  5, 11, 10,  5, 14,  2,  7, 12,
		},{
			 7, 13, 13,  8, 14, 11,  3,  5,  0,  6,  6, 15,  9,  0, 10,  3,
			 1,  4,  2,  7,  8,  2,  5, 12, 11,  1, 12, 10,  4, 14, 15,  9,
			10,  3,  6, 15,  9,  0,  0,  6, 12, 10, 11,  1,  7, 13, 13,  8,
			15,  9,  1,  4,  3,  5, 14, 11,  5, 12,  2,  7,  8,  2,  4, 14,
		},{
			 2, 14, 12, 11,  4,  2,  1, 12,  7,  4, 10,  7, 11, 13,  6,  1,
			 8,  5,  5,  0,  3, 15, 15, 10, 13,  3,  0,  9, 14,  8,  9,  6,
			 4, 11,  2,  8,  1, 12, 11,  7, 10,  1, 13, 14,  7,  2,  8, 13,
			15,  6,  9, 15, 12,  0,  5,  9,  6, 10,  3,  4,  0,  5, 14,  3,
		},{
			12, 10,  1, 15, 10,  4, 15,  2,  9,  7,  2, 12,  6,  9,  8,  5,
			 0,  6, 13,  1,  3, 13,  4, 14, 14,  0,  7, 11,  5,  3, 11,  8,
			 9,  4, 14,  3, 15,  2,  5, 12,  2,  9,  8,  5, 12, 15,  3, 10,
			 7, 11,  0, 14,  4,  1, 10,  7,  1,  6, 13,  0, 11,  8,  6, 13,
		},{
			 4, 13, 11,  0,  2, 11, 14,  7, 15,  4,  0,  9,  8,  1, 13, 10,
			 3, 14, 12,  3,  9,  5,  7, 12,  5,  2, 10, 15,  6,  8,  1,  6,
			 1,  6,  4, 11, 11, 13, 13,  8, 12,  1,  3,  4,  7, 10, 14,  7,
			10,  9, 15,  5,  6,  0,  8, 15,  0, 14,  5,  2,  9,  3,  2, 12,
		},{
			13,  1,  2, 15,  8, 13,  4,  8,  6, 10, 15,  3, 11,  7,  1,  4,
			10, 12,  9,  5,  3,  6, 14, 11,  5,  0,  0, 14, 12,  9,  7,  2,
			 7,  2, 11,  1,  4, 14,  1,  7,  9,  4, 12, 10, 14,  8,  2, 13,
			 0, 15,  6, 12, 10,  9, 13,  0, 15,  3,  3,  5,  5,  6,  8, 11,
		}
	};

	BIT64 t = {};

	for( BYTE i = 0; i < countof(s_table); ++i )
	{
		if( i % 2 == 0 )
			t.b[i/2]  = s_table[i][text->b[i]>>2] << 4;
		else
			t.b[i/2] += s_table[i][text->b[i]>>2];
	}

	*text = t;
}


/// XORs all eight bytes.
void CDec::XOR64(BIT64* left, BIT64 right)
{
	for( BYTE i = 0; i < 8; ++i )
		left->b[i] ^= right.b[i];
}


/// XORs the lower four bytes.
void CDec::XOR32(BIT64* left, BIT64 right)
{
	for( BYTE i = 0; i < 4; ++i )
		left->b[i] ^= right.b[i];
}


void CDec::RoundFunction(BIT64 key, BIT64* text)
{
	BIT64 t = *text;
	this->CDec::ET(&t); // Expand
	this->CDec::XOR64(&t, key); // XOR key
	this->CDec::ST(&t); // S-BOX
	this->CDec::TP(&t); // Transpose
	this->CDec::XOR32(text, t); // XOR output
}
