#include "ImportantItem.h"
#include "Path.h"
#include "globals.hpp"


hook_method<void (CImportantItem::*)(void)> CImportantItem::_LoadImportantItem(SERVER, "CImportantItem::LoadImportantItem");
void CImportantItem::LoadImportantItem(void) // line 25 (ImportantItem.h)
{
	return (this->*_LoadImportantItem)();

	g_pathData->CPathData::SetFileName("Importantitem.txt");
	FILE* fp = fopen(g_pathData, "r");
	if( fp == NULL )
	{
		MessageBoxA(NULL, "CImportantItem::LoadImportantItem() Fail!\n", "", MB_OK);
		return;
	}

	int dwItemID = 0;
	char szBuffer[256];
	memset(szBuffer, 0, sizeof(szBuffer));

	while( !feof(fp) )
	{
		fgets(szBuffer, sizeof(szBuffer), fp);

		if( strlen(szBuffer) < 3 )
			continue;

		sscanf(szBuffer, "%d\n", &dwItemID);
		m_mapImportantItem[dwItemID] = 0;
	}

	fclose(fp);
}


//hook_method<int (CImportantItem::*)(DWORD dwItemID)> CImportantItem::_IsImportantItem(SERVER, "CImportantItem::IsImportantItem");
int CImportantItem::IsImportantItem(DWORD dwItemID) // line ??
{
//	return (this->*_IsImportantItem)(dwItemID);

	mystd::map<DWORD,DWORD>::iterator iItem = m_mapImportantItem.find(dwItemID);
	return ( iItem != m_mapImportantItem.end() );
}
