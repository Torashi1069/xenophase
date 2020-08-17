#include "ImportantItem.h"
#include "Path.h"
#include "ZoneProcess.h"


CImportantItem::CImportantItem()
{
}


CImportantItem::~CImportantItem()
{
}


void CImportantItem::LoadImportantItem()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("Importantitem.txt"), "r");
	if( fp == NULL )
	{
		MessageBoxA(NULL, "CImportantItem::LoadImportantItem() Fail!\n", "", MB_OK);
		return;
	}

	char szBuffer[256] = {};
	DWORD dwItemID = 0;

	while( !feof(fp) )
	{
		fgets(szBuffer, countof(szBuffer), fp);
		if( strlen(szBuffer) < 3 )
			continue;

		sscanf(szBuffer, "%d\n", &dwItemID);
		m_mapImportantItem[dwItemID] = 0;
	}

	fclose(fp);
}


BOOL CImportantItem::IsImportantItem(DWORD dwItemID)
{
	std::map<DWORD,DWORD>::iterator iItem = m_mapImportantItem.find(dwItemID);
	return ( iItem != m_mapImportantItem.end() );
}
