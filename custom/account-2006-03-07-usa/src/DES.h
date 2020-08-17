// This file is part of the smb++ library, (C) 1999 GPLv2  Nicolas Brodu (nicolas.brodu@free.fr)
// http://nicolas.brodu.numerimoire.net/en/programmation/libsmb/index.html
#pragma once


class DES
{
protected:
	unsigned char key[64];
	unsigned char K[16][48];
	// Encrypt (encdec=0) or decrypt (encdec=1)
	void doIt(unsigned char* data, const unsigned long length, int encdec);

public:
	// key must be 56 bits
	// Anyway, the parity bits introduced in the des-how-to are discarded by the
	// first permutation function
	DES(const unsigned char* k = 0);
	~DES();
	void setKey(const unsigned char* k = 0);
	// Data should always be aligned to a 64 bit multiple
	// If not, discard the junk (hence force the caller to paddle...)
	void encrypt(unsigned char* data, const unsigned long length);
	void decrypt(unsigned char* data, const unsigned long length);
};
