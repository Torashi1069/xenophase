#include "CHPAmount.h"


CHPAmount::CHPAmount()
: m_Amount(0), m_RecoveryProhibitionRefCnt(0)
{
}


CHPAmount::~CHPAmount()
{
}


CHPAmount::operator int()
{
	return m_Amount;
}


CHPAmount& CHPAmount::operator+=(const int in_Amount)
{
	if( m_RecoveryProhibitionRefCnt > 0 && in_Amount > 0 )
		return *this; // recovery prohibited.

	m_Amount += in_Amount;
	return *this;
}


CHPAmount& CHPAmount::operator=(const int in_Amount)
{
	if( m_RecoveryProhibitionRefCnt > 0 && in_Amount > m_Amount )
		return *this; // recovery prohibited.

	m_Amount = in_Amount;
	return *this;
}


void CHPAmount::Init()
{
	m_Amount = 0;
	m_RecoveryProhibitionRefCnt = 0;
}


void CHPAmount::RecoveryProhibitionSet()
{
	++m_RecoveryProhibitionRefCnt;
}


void CHPAmount::RecoveryProhibitionReset()
{
	--m_RecoveryProhibitionRefCnt;
}


void CHPAmount::SetForceAmout(const int in_Amount)
{
	m_Amount = in_Amount;
}
