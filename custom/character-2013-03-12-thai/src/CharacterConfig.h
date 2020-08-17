#pragma once
#include "Common/InfoScript.h"


class CCharacterConfig : public CInfoScript
{
public:
	int GetCHARACTER_DELETE_DELAY_SECOND();
	virtual void Open(const char* pszScript);

	CCharacterConfig();
	virtual ~CCharacterConfig();

private:
	/* this+ 0 */ //CInfoScript baseclass_0;
	/* this+44 */ int m_CHARACTER_DELETE_DELAY_SECOND;
};
