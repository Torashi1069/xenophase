/// 
/// DES algorithm, ECB mode, Gravity version.
/// Based on code in des.c "DES (Data Encrytion Standard)" by Yu Jinyang, 1998-07-08.
/// 
/// The implementation differs from the DES standard:
/// * Key schedule generates all-zeroed keys because PC1() uses AND instead of OR for bit setting.
/// * Key schedule would generate nonstandard keys because of wrong bit shift operator precedence.
/// * Public functions only do 1 round of DES instead of the full 16 rounds.
/// * Public functions only change some of the input, in a pattern; most blocks remain plain text.
/// 
#pragma once


union BIT64
{
	DWORD dw[2];
	WORD  w[4];
	BYTE  b[8];
};


class CDec
{
public:
	CDec();
	CDec(char* seed);
	~CDec();

public:
	void MakeKey(char* seed);
	void MakeKey(BIT64 seed);

public:
	BOOL DataEncrypt(char* pIn, int inSize, char* pOut, int* outSize, int mod);
	BOOL DataDecrypt(char* pIn, int inSize, char* pOut, int* outSize, int mod);
	BOOL DataDecryptHeader(char* pIn, int inSize, char* pOut, int* outSize);

protected:
	/// Obfuscation
	void ShuffleEnc(BIT64 in, BIT64* out); /// @custom
	void ShuffleDec(BIT64 in, BIT64* out); /// @custom
	BYTE Substitution(BYTE b); /// @custom

protected:
	enum { CRYPT_SIZE = 8 };
	enum { RANDOM_SPAN_SIZE = 13 };
	enum { MAX_ROUND = 16 };

protected:
	/// DES crypto
	BOOL Encrypt(int rounds, BIT64 keys[MAX_ROUND], BIT64 plain, BIT64* out);
	BOOL Decrypt(int rounds, BIT64 keys[MAX_ROUND], BIT64 plain, BIT64* out);

protected:
	/// DES key schedule
	void PC1(BIT64* bit); /// @custom
	void PC2(BIT64* bit); /// @custom
	void Rotation(BIT64* bit, int round); /// @custom

protected:
	/// DES round function
	void IP(BIT64* text);
	void FP(BIT64* text);
	void ET(BIT64* text); /// @custom
	void TP(BIT64* text); /// @custom
	void ST(BIT64* text); /// @custom
	void XOR64(BIT64* left, BIT64 right); /// @custom
	void XOR32(BIT64* left, BIT64 right); /// @custom
	void RoundFunction(BIT64 key, BIT64* text);

protected:
	BIT64 m_key[MAX_ROUND];
};
