#include "CBuffInfoMgr.hpp"
#include "ItemReuseLimit.h"
#include "Path.h"
#include "globals.hpp"
#include "shared.h"


hook_method<bool (CItemReuseLimit::*)(void)> CItemReuseLimit::_Init(SERVER, "CItemReuseLimit::Init");
bool CItemReuseLimit::Init(void) // line 15
{
	return (this->*_Init)();

	FILE* fp = fopen(g_pathData->CPathData::SetFileName("ItemReuseLimit.txt"), "r");
	if( fp == NULL )
	{
		Trace("ItemReuseLimit.txt 파일이 존재하지 않습니다"); // "ItemReuseLimit.txt file does not exist"
		return true;
	}

	while( !feof(fp) )
	{
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		if( !fgets(buf, sizeof(buf), fp) )
			break;

		char temp[256];
		memset(&temp, 0, sizeof(temp));
		sscanf(buf, "%s", temp);

		if( strstr(temp, "//") != NULL )
			continue;

		if( strlen(temp) == 0 )
			continue;

		int itemID = 0;
		int time = 0;
		char groupBuffID[256];
		memset(&groupBuffID, 0, sizeof(groupBuffID));
		sscanf(buf, "%d%s%d", &itemID, &groupBuffID, &time);

		int type = g_buffInfoMgr->CBuffInfoMgr::GetBuffType(groupBuffID);
		if( type == -1 )
		{
			Trace("%s 가 BuffInfoMgr에 정의되어 있지 않음", groupBuffID); // "%s is not defined in the BuffInfoMgr"
			fclose(fp);
			return 0;
		}

		mystd::pair<unsigned long,ITEMREUSE> _Val;
		_Val.first = itemID;
		_Val.second.groupBuffID = type;
		_Val.second.time = 1000 * time;
		m_info.insert(_Val);
	}

	fclose(fp);
	return true;
}


hook_method<bool (CItemReuseLimit::*)(unsigned long itemID, ITEMREUSE& info)> CItemReuseLimit::_GetItemReuseLimit(SERVER, "CItemReuseLimit::GetItemReuseLimit");
bool CItemReuseLimit::GetItemReuseLimit(unsigned long itemID, ITEMREUSE& info) // line 71
{
	return (this->*_GetItemReuseLimit)(itemID, info);

	mystd::map<unsigned long,ITEMREUSE>::const_iterator iter = m_info.find(itemID);
	if( iter == m_info.end() )
		return false;

	info.groupBuffID = iter->second.groupBuffID;
	info.time = iter->second.time;
	return true;
}
