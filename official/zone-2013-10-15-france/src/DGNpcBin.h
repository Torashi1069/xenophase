#pragma once
#include "ScriptLib/BinBuf.h"

class CDGNpcBin
{
public:
	CDGNpcBin();
	virtual ~CDGNpcBin();

public:
	/* this+0 */ //const CDGNpcBin::`vftable';
	/* this+4 */ CBinBuf m_binBuf;

public:
	void ClearBinBuff();
	bool LoadScriptBin(const char* mapName);
	CBinBuf* GetBinBuff();
};
