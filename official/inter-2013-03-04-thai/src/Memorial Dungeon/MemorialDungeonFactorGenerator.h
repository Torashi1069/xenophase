#pragma once
#include "shared/N3System/N3RecycleIDGenerator.h"


class CMemorialDungeonFactorGenerator : public CN3RecycleIDGenerator
{
public:
	static bool CreateInstance();
	static void DestoryInstance();
	static CMemorialDungeonFactorGenerator* GetObj(); /// @custom

private:
	CMemorialDungeonFactorGenerator();
	~CMemorialDungeonFactorGenerator();
	CMemorialDungeonFactorGenerator(CMemorialDungeonFactorGenerator&); // = delete;
	CMemorialDungeonFactorGenerator& operator=(CMemorialDungeonFactorGenerator&); // = delete;

private:
	/* static */ static CMemorialDungeonFactorGenerator*& m_cpSelf; //TODO
	/* this+0 */ //CN3RecycleIDGenerator baseclass_0;
};
