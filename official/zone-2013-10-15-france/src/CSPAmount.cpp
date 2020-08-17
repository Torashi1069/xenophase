#include "CSPAmount.h"


CSPAmount::CSPAmount()
: m_Amount(0), m_RecoveryProhibitionRefCnt(0)
{
}


CSPAmount::~CSPAmount()
{
}


CSPAmount::operator int()
{
	return m_Amount;
}


CSPAmount& CSPAmount::operator+=(const int in_Amount)
{
	if( m_RecoveryProhibitionRefCnt > 0 && in_Amount > 0 )
		return *this; // recovery prohibited.

	m_Amount += in_Amount;
	return *this;
}


CSPAmount& CSPAmount::operator=(const int in_Amount)
{
	if( m_RecoveryProhibitionRefCnt > 0 && in_Amount > m_Amount )
		return *this; // recovery prohibited.

	m_Amount = in_Amount;
	return *this;
}


void CSPAmount::Init()
{
	m_Amount = 0;
	m_RecoveryProhibitionRefCnt = 0;
}


void CSPAmount::RecoveryProhibitionSet()
{
	++m_RecoveryProhibitionRefCnt;
}


void CSPAmount::RecoveryProhibitionReset()
{
	--m_RecoveryProhibitionRefCnt;
}


void CSPAmount::SetForceAmout(const int in_Amount)
{
	m_Amount = in_Amount;
}
