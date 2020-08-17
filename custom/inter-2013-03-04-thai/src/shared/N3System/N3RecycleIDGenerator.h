#pragma once


class CN3RecycleIDGenerator
{
public:
	bool isOK() const;
	int Alloc();
	void Free(const unsigned int in_nID);

public:
	CN3RecycleIDGenerator(const unsigned int in_nFirstIDValue, const unsigned int in_nLastIDValue, const unsigned int in_nMinimumObjCnt);
	virtual ~CN3RecycleIDGenerator();
	CN3RecycleIDGenerator(CN3RecycleIDGenerator&); // = delete;
	CN3RecycleIDGenerator& operator=(CN3RecycleIDGenerator&); // = delete;

private:
	/* this+ 0 */ //const CN3RecycleIDGenerator::`vftable';
	/* this+ 4 */ bool m_bOK;
	typedef std::deque<unsigned int> RECYCLEIDCONTAINER;
	/* this+ 8 */ RECYCLEIDCONTAINER m_RecycleIDContainer;
	/* this+40 */ const unsigned int m_nFirstIDValue;
	/* this+44 */ const unsigned int m_nLastIDValue;
	/* this+48 */ const unsigned int m_nMinimumObjCnt;
	/* this+52 */ unsigned int m_nNextID;
};
