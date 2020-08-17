#include "MsgInfo.h"


void CMsgInfo::AddString(int col, const char* Msg, ...) // line 2663-2686 (character.cpp)
{
	va_list va;
	va_start(va, Msg);

	char szMessage[1024] = {};
	_vsnprintf_s(szMessage, sizeof(szMessage), _TRUNCATE, Msg, va);

	size_t msgLen = strlen(szMessage);
	if( msgLen >= countof(m_MsgInfo[nCurPos].m_szMsg) )
		return; // no more room.

	strncpy(m_MsgInfo[nCurPos].m_szMsg, szMessage, msgLen);
	m_MsgInfo[nCurPos++].col = col;
}
