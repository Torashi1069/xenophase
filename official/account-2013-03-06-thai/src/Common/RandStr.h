#pragma once


class CRandStr
{
private:
	/* this+0 */ char m_RandStr[10000][16];

public:
	CRandStr()
	{
		srand((unsigned int)time(NULL));

		for( int n = 0; n < countof(m_RandStr); ++n )
			for( int i = 0; i < countof(m_RandStr[n]); ++i )
				m_RandStr[n][i] = rand() % 256;
	}

	const char* operator[](int n) const
	{
		if( n >= countof(m_RandStr) )
			n = 0; // bounds check

		return m_RandStr[n];
	}
};
