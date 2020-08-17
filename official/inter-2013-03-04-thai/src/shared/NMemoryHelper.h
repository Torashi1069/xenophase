#pragma once


class NMemoryHelper
{
public:
	void* Get(const int in_bytes)
	{
		if( m_usedbytes + in_bytes > m_maxbytes )
			return NULL;

		void* result = &m_pBuffer[m_usedbytes];
		m_usedbytes += in_bytes;
		return result;
	}

	int GetUsedBytes()
	{
		return m_usedbytes;
	}

public:
	NMemoryHelper(void* in_pBuffer, const unsigned int in_maxbytes) : m_pBuffer((BYTE*)in_pBuffer), m_maxbytes(in_maxbytes), m_usedbytes(0) { }
	virtual ~NMemoryHelper() { }
	NMemoryHelper(NMemoryHelper&); // = delete;
	NMemoryHelper& operator=(NMemoryHelper&); // = delete;

private:
	/* this+ 0 */ //const NMemoryHelper::`vftable';
	/* this+ 4 */ BYTE* m_pBuffer;
	/* this+ 8 */ int m_maxbytes;
	/* this+12 */ int m_usedbytes;
};
