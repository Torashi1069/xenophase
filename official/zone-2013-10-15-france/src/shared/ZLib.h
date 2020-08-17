#pragma once


class CZLib
{
public:
	CZLib();
	virtual ~CZLib();

public:
	int Compress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned int sourceLen, int level);
	int Uncompress(unsigned char* dest, unsigned long* destLen, const unsigned char* source, unsigned long sourceLen);
};
