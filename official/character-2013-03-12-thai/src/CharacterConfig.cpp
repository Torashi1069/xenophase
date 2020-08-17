#include "CharacterConfig.h"


CCharacterConfig::CCharacterConfig()
{
	m_CHARACTER_DELETE_DELAY_SECOND = 60;
}


CCharacterConfig::~CCharacterConfig()
{
}


int CCharacterConfig::GetCHARACTER_DELETE_DELAY_SECOND()
{
	return m_CHARACTER_DELETE_DELAY_SECOND;
}


void CCharacterConfig::Open(const char* pszScript)
{
	this->CInfoScript::Open(pszScript);

	const char* szDeleteDelay = this->CInfoScript::GetInfo("CHARACTER_DELETE_DELAY_SECOND");
	if( szDeleteDelay != NULL )
		m_CHARACTER_DELETE_DELAY_SECOND = atoi(szDeleteDelay);
}
