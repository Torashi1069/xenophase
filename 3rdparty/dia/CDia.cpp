#include "CDia.hpp"
#include "dia2.h"
#include <stdio.h>
#include <stdlib.h> // abort()


int CDia::m_nInitCount = 0;


CDia::CDia(void)
{
	m_pDiaDataSource = NULL;
	m_pDiaSession = NULL;
	m_pGlobalSymbol = NULL;

	if( m_nInitCount == 0 )
		CoInitialize(NULL);

	++m_nInitCount;

	HRESULT hr = CoCreateInstance(__uuidof(DiaSource), NULL, CLSCTX_INPROC_SERVER, __uuidof(IDiaDataSource), (void **)&m_pDiaDataSource);
	if( FAILED(hr) )
	{
		fprintf(stderr, "CoCreateInstance failed - HRESULT = %08X\n", hr);
		abort();
	}
}


CDia::~CDia(void)
{
	this->CDia::Close();

	--m_nInitCount;

	if( m_nInitCount == 0 )
		CoUninitialize();
}


bool CDia::Open(const char exePath[])
{
	wchar_t wszPath[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, exePath, -1, wszPath, ARRAYSIZE(wszPath));
	return this->CDia::Open(wszPath);
}


bool CDia::Open(const wchar_t exePath[])
{
	if( !m_pDiaDataSource )
		return false;

	if( m_pDiaSession )
		this->CDia::Close();

	HRESULT hr = m_pDiaDataSource->loadDataForExe(exePath, L".", NULL);
	if( FAILED(hr) )
	{
		fprintf(stderr, "loadDataForExe failed - HRESULT = %08X\n", hr);
		return false;
	}

	// open a session for querying symbols
	HRESULT hr2 = m_pDiaDataSource->openSession(&m_pDiaSession);
	if( FAILED(hr2) )
	{
		fprintf(stderr, "openSession failed - HRESULT = %08X\n", hr2);
		abort();
		return false;
	}

	// retrieve a reference to the global scope
	HRESULT hr3 = m_pDiaSession->get_globalScope(&m_pGlobalSymbol);
	if( FAILED(hr3) )
	{
		fprintf(stderr, "get_globalScope failed - HRESULT = %08X\n", hr3);
		abort();
		return false;
	}

	return true;
}


bool CDia::Close(void)
{
	if( m_pGlobalSymbol )
	{
		m_pGlobalSymbol->Release();
		m_pGlobalSymbol = NULL;
	}

	if( m_pDiaSession )
	{
		m_pDiaSession->Release();
		m_pDiaSession = NULL;
	}

	if( m_pDiaDataSource )
	{
		m_pDiaDataSource->Release();
		m_pDiaDataSource = NULL;
	}

	return true;
}


CDiaClass CDia::findClass(wchar_t className[]) const
{
	IDiaSymbol* sym = this->CDia::findSymbol(className);
	if( sym == NULL )
		MessageBoxW(NULL, className, NULL, MB_OK);
	//TODO: check type
	return CDiaClass(sym);
}


IDiaSymbol* CDia::findSymbol(wchar_t symbol[]) const
{
	IDiaEnumSymbols* pEnumSymbols;

	if( FAILED(m_pGlobalSymbol->findChildren(SymTagUDT, symbol, nsfCaseSensitive, &pEnumSymbols)) )
		return NULL;

	IDiaSymbol* pSymbol;
	ULONG celt = 0;
	if( !SUCCEEDED(pEnumSymbols->Next(1, &pSymbol, &celt)) || (celt != 1) )
	{
		pEnumSymbols->Release();
		return NULL;
	}

	pEnumSymbols->Release();

	return pSymbol;
}
