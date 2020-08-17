#include "ItemServer/specialitemdef.h"


CSendSpecialItemInfoMsg::CSendSpecialItemInfoMsg()
{
}


CSendSpecialItemInfoMsg::~CSendSpecialItemInfoMsg()
{
}


void CSendSpecialItemInfoMsg::SetCharId(int nCharId)
{
	m_nCharId = nCharId;
}


void CSendSpecialItemInfoMsg::SetItemId(int nItemId)
{
	m_nItemId = nItemId;
}


void CSendSpecialItemInfoMsg::SetEvent(int nEvent)
{
	m_nEvent = nEvent;
}


int CSendSpecialItemInfoMsg::GetCharId()
{
	return m_nCharId;
}


int CSendSpecialItemInfoMsg::GetItemId()
{
	return m_nItemId;
}


int CSendSpecialItemInfoMsg::GetEvent()
{
	return m_nEvent;
}


CReceiveSpecialItemInfoMsg::CReceiveSpecialItemInfoMsg()
{
}


CReceiveSpecialItemInfoMsg::~CReceiveSpecialItemInfoMsg()
{
}


void CReceiveSpecialItemInfoMsg::SetFunc(int nFunc, int nIdx)
{
	m_nFunc[nIdx] = nFunc;
}


void CReceiveSpecialItemInfoMsg::SetParam(int* pParamArr, int nIdx)
{
	memcpy(m_nParamArr[nIdx], pParamArr, sizeof(m_nParamArr[nIdx]));
}


void CReceiveSpecialItemInfoMsg::GetFunc(int* pFuncArr)
{
	memcpy(pFuncArr, m_nFunc, sizeof(m_nFunc));
}


void CReceiveSpecialItemInfoMsg::GetParam(void* pParamArr)
{
	memcpy(pParamArr, m_nParamArr, sizeof(m_nParamArr));
}
