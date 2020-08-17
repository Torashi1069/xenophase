#pragma once
#include "CDiaClass.hpp"
struct IDiaSymbol;
struct IDiaDataSource;
struct IDiaSession;


class CDia
{
public:
	CDia::CDia(void);
	CDia::~CDia(void);
	bool CDia::Open(const char exePath[]);
	bool CDia::Open(const wchar_t exePath[]);
	bool CDia::Close(void);

	CDiaClass CDia::findClass(wchar_t className[]) const;

private:
	IDiaSymbol* CDia::findSymbol(wchar_t symbol[]) const;

	static int m_nInitCount; // COM
	IDiaDataSource* m_pDiaDataSource;
	IDiaSession* m_pDiaSession;
	IDiaSymbol* m_pGlobalSymbol;
};
