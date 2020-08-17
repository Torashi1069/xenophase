#include "shared/N2System/N2IDGenerator36.h"


/// singleton instance
N2IDGenerator36*& N2IDGenerator36::m_cpSelf = VTOR<N2IDGenerator36*>(DetourFindFunction(EXEPATH(), "N2IDGenerator36::m_cpSelf"));

/// locals
static const char Gen36TBL[36] = { '0','o','q','e','f','6','u','k','9','4','d','7','r','2','s','y','t','5','3','i','v','1','w','l','p','j','x','c','z','g','m','n','a','h','b','8' };


N2IDGenerator36::N2IDGenerator36()
{
	m_bOK = true;
}


N2IDGenerator36::~N2IDGenerator36()
{
}


bool N2IDGenerator36::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) N2IDGenerator36();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->N2IDGenerator36::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void N2IDGenerator36::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


N2IDGenerator36* N2IDGenerator36::GetObj() /// @custom
{
	return m_cpSelf;
}


bool N2IDGenerator36::isOK() const
{
	return m_bOK;
}


std::string N2IDGenerator36::Generate36(const DWORD in_dwID)
{
	std::string result;

	int val = in_dwID;
	int remain;
	std::list<int> RemainList;

	do
	{
		remain = val % countof(Gen36TBL);
		val = val / countof(Gen36TBL);
		RemainList.push_front(remain);
	}
	while( val != 0 );

	for( std::list<int>::iterator iter = RemainList.begin(); iter != RemainList.end(); ++iter )
		result += Gen36TBL[*iter];

	RemainList.clear();

	return result;
}


int N2IDGenerator36::ReverseDecimal(const char* in_szValue)
{
	if( in_szValue == NULL )
		return 0;

	int nLength = strlen(in_szValue);
	int nResultValue = 0;

	for( int i = 0; i < nLength; ++i )
	{
		int digit;
		for( digit = 0; digit < countof(Gen36TBL); ++digit )
			if( in_szValue[i] == Gen36TBL[digit] )
				break;

		if( digit >= countof(Gen36TBL) )
			continue;

		int position = nLength - 1 - i;
		int val = ( position >= 0 ) ? position : -position;

		float base = countof(Gen36TBL);
		float exp = 1;
		while( 1 )
		{
			if( val & 1 )
				exp = exp * base;
			val >>= 1;

			if( val == 0 )
				break;

			base = base * base;
		}

		float order = ( position >= 0 ) ? exp : 1.0f / exp;

		nResultValue += digit * (int)order;
	}

	return nResultValue;
}
