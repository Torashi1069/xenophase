#pragma once
#include "shared/N3System/N3RecycleIDGenerator.h"


class CInstantMapIDGenerator : public CN3RecycleIDGenerator
{
public:
	static bool CreateInstance();
	static void DestoryInstance();
	static CInstantMapIDGenerator* GetObj(); /// @custom

private:
	CInstantMapIDGenerator();
	virtual ~CInstantMapIDGenerator();
	CInstantMapIDGenerator(CInstantMapIDGenerator&); // = delete;
	CInstantMapIDGenerator& operator=(CInstantMapIDGenerator&); // = delete;

private:
	/* static */ static CInstantMapIDGenerator*& m_cpSelf; //TODO
	/* this+0 */ //CN3RecycleIDGenerator baseclass_0;
};
