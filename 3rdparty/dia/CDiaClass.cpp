#include "CDiaClass.hpp"
#include "dia2.h"


CDiaClass::CDiaClass(IDiaSymbol* symbol)
{
	m_symbol = symbol;
}


CDiaClass::~CDiaClass(void)
{
	m_symbol->Release();
}


CDiaClassMember CDiaClass::findMember(wchar_t memberName[]) const
{
	IDiaEnumSymbols* pEnumSymbols = NULL;

	if( FAILED(m_symbol->findChildren(SymTagData, memberName, nsfCaseSensitive, &pEnumSymbols)) )
		throw;

	IDiaSymbol* pSymbol;
	ULONG celt = 0;
	if( FAILED(pEnumSymbols->Next(1, &pSymbol, &celt)) || (celt != 1) )
	{
		pEnumSymbols->Release();
		throw;
	}

	pEnumSymbols->Release();

	return CDiaClassMember(pSymbol);
}


CDiaClassMethod CDiaClass::findMethod(wchar_t methodName[]) const
{
	IDiaEnumSymbols* pEnumSymbols = NULL;

	if( FAILED(m_symbol->findChildren(SymTagFunction, methodName, nsfCaseSensitive, &pEnumSymbols)) )
		throw;

	IDiaSymbol* pSymbol;
	ULONG celt = 0;
	if( FAILED(pEnumSymbols->Next(1, &pSymbol, &celt)) || (celt != 1) )
	{
		pEnumSymbols->Release();
		throw;
	}

	pEnumSymbols->Release();

	return CDiaClassMethod(pSymbol);
}


int CDiaClass::size(void) const
{
	//FIXME: If the LocationType of the symbol is LocIsBitField, the length returned by this method is in bits
	ULONGLONG ullLength;
	return( m_symbol->get_length(&ullLength) == S_OK ) ? (int)ullLength : -1;
}
