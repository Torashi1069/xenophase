#pragma once
#include "QVar.h"


class CFuncExtraction
{
public:
	CFuncExtraction();
	virtual ~CFuncExtraction();

private:
	/* this+0 */ //const CFuncExtraction::`vftable';
	/* this+4 */ CQVar m_data;

public:
	bool SetData(const char* data);
	bool GetFuncValue(const char* func, std::vector<CQVar>& value);
};
