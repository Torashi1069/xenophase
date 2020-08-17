#include "Mapinfo.h"
#include "NpcServer/NpcSvr.h"
#include "CharacterMgr.h"
#include "MonParameterMgr.h"
#include "ScriptEventHandler.h"
#include "Common/Packet.h"
#include "globals.hpp"
#include "struct.hpp"
#include "shared.h" // Trace()


hook_method<bool (CScriptEventHandler::*)(int func, mystd::deque<TokenData>& parm, TokenData& ret)> CScriptEventHandler::_OnFunc(SERVER, "CScriptEventHandler::OnFunc");
bool CScriptEventHandler::OnFunc(int func, mystd::deque<TokenData>& parm, TokenData& ret)
{
	return (this->*_OnFunc)(func, parm, ret);

	//TODO
}


hook_method<void (CScriptEventHandler::*)(const char* str)> CScriptEventHandler::_OnError(SERVER, "CScriptEventHandler::OnError");
void CScriptEventHandler::OnError(const char* str)
{
	return (this->*_OnError)(str);

	//TODO
}


hook_method<void (CScriptEventHandler::*)(void)> CScriptEventHandler::_Free(SERVER, "CScriptEventHandler::Free");
void CScriptEventHandler::Free(void)
{
	return (this->*_Free)();

	//TODO
}


hook_method<unsigned int (CScriptEventHandler::*)(bool isOnce)> CScriptEventHandler::_Proc(SERVER, "CScriptEventHandler::Proc");
unsigned int CScriptEventHandler::Proc(bool isOnce)
{
	return (this->*_Proc)(isOnce);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(mystd::deque<TokenData>& parm, int n)> CScriptEventHandler::_CheckFixedVarNum(SERVER, "CScriptEventHandler::CheckFixedVarNum");
bool CScriptEventHandler::CheckFixedVarNum(mystd::deque<TokenData>& parm, int n)
{
	return (this->*_CheckFixedVarNum)(parm, n);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(const char* zone, int x, int y, int w, int h, int num, int mobId, int regenMin, int regenMax, int regenType, char* name, bool isBoss)> CScriptEventHandler::_FuncPutMob(SERVER, "CScriptEventHandler::FuncPutMob");
bool CScriptEventHandler::FuncPutMob(const char* zone, int x, int y, int w, int h, int num, int mobId, int regenMin, int regenMax, int regenType, char* name, bool isBoss) // line 20 (ScriptEventHandlerFunc.cpp)
{
	return (this->*_FuncPutMob)(zone, x, y, w, h, num, mobId, regenMin, regenMax, regenType, name, isBoss);

	char mapName[256];
	SetMapName(mapName, zone);

	int SID = g_mapInfo->CMapInfo::GetServerID(mapName);
	if( GetLocalServerID() != SID )
		return true; // not for this server. done.

	if( num < 1 )
	{
		this->EventLog("PutMob: count is zero or minus value[%d]\n", num);
		return false;
	}

	if( w < 0 )
	{
		this->EventLog("PutMob: width is minus value[%d]\n", w);
		return false;
	}

	if( h < 0 )
	{
		this->EventLog("PutMob: height is minus value[%d]\n", h);
		return false;
	}

	const char* npcName = g_monParameter->CMonParameterMgr::GetMonsterName(mobId);
	if( npcName == NULL )
	{
		this->EventLog("PutMob: mob id invalid[%d]\n", mobId);
		return false;
	}

	this->EventLog("PutMob zone[%s] x%d y%d w%d h%d n%d mob:%s regMin: %d regMax %d regType %d\n",
		zone, x, y, w, h, num, npcName, regenMin, regenMax, regenType);

	NpcSvrNpcInfo mobInfo;
	mobInfo.zone = zone;
	mobInfo.name = ( name != NULL ) ? name : npcName;
	mobInfo.type = g_monParameter->CMonParameterMgr::GetMonsterType(mobId);
	mobInfo.x = x;
	mobInfo.y = y;
//	mobInfo.dx;
//	mobInfo.dy;
	mobInfo.w = w;
	mobInfo.h = h;
	mobInfo.sprite = mobId;
	mobInfo.direction = 0;
	mobInfo.regenMax = regenMax;
	mobInfo.regenMin = regenMin;
	mobInfo.regenType = regenType;
//	mobInfo.npcType;

	for( int i = 0; i < num; ++i )
	{
		if( w != 0 && h != 0 )
		{
			int dx = rand() % w;
			int dy = rand() % h;
			mobInfo.dx = ( rand() % 2 == 0 ) ? dx : -dx;
			mobInfo.dy = ( rand() % 2 == 0 ) ? dy : -dy;
		}
		else
		{
			mobInfo.dx = 0;
			mobInfo.dy = 0;
		}

		int npcID = g_npcSvr->CNpcSvr::GetNpcMgr()->CNpcMgr::GetNewID();
		CNPC* npc = this->CScriptEventHandler::AddNpc(npcID, mapName, &mobInfo);
		if( npc != NULL && isBoss == 1 )
			g_characterMgr->CCharacterMgr::RegisterBossInMap(npc);
	}

	return true;
}


hook_method<bool (CScriptEventHandler::*)(int part, TokenData& ret, bool isAdvanced)> CScriptEventHandler::_FuncGetEquipIsSuccessRefinery(SERVER, "CScriptEventHandler::FuncGetEquipIsSuccessRefinery");
bool CScriptEventHandler::FuncGetEquipIsSuccessRefinery(int part, TokenData& ret, bool isAdvanced)
{
	return (this->*_FuncGetEquipIsSuccessRefinery)(part, ret, isAdvanced);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(int part, TokenData& ret, bool isAdvanced)> CScriptEventHandler::_FuncGetEquipPercentRefinery(SERVER, "CScriptEventHandler::FuncGetEquipPercentRefinery");
bool CScriptEventHandler::FuncGetEquipPercentRefinery(int part, TokenData& ret, bool isAdvanced)
{
	return (this->*_FuncGetEquipPercentRefinery)(part, ret, isAdvanced);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(char* str, int npcID)> CScriptEventHandler::_FuncDialog(SERVER, "CScriptEventHandler::FuncDialog");
bool CScriptEventHandler::FuncDialog(char* str, int npcID)
{
	return (this->*_FuncDialog)(str, npcID);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(int npcID)> CScriptEventHandler::_FuncCloseDialog(SERVER, "CScriptEventHandler::FuncCloseDialog");
bool CScriptEventHandler::FuncCloseDialog(int npcID)
{
	return (this->*_FuncCloseDialog)(npcID);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(int npcID)> CScriptEventHandler::_FuncWaitDialog(SERVER, "CScriptEventHandler::FuncWaitDialog");
bool CScriptEventHandler::FuncWaitDialog(int npcID)
{
	return (this->*_FuncWaitDialog)(npcID);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(int npcID)> CScriptEventHandler::_FuncDlgWriteStr(SERVER, "CScriptEventHandler::FuncDlgWriteStr");
bool CScriptEventHandler::FuncDlgWriteStr(int npcID)
{
	return (this->*_FuncDlgWriteStr)(npcID);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(mystd::deque<TokenData>& parm, int npcID)> CScriptEventHandler::_FuncMenu(SERVER, "CScriptEventHandler::FuncMenu");
bool CScriptEventHandler::FuncMenu(mystd::deque<TokenData>& parm, int npcID)
{
	return (this->*_FuncMenu)(parm, npcID);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(const char* zone, int x, int y)> CScriptEventHandler::_FuncMapMove(SERVER, "CScriptEventHandler::FuncMapMove");
bool CScriptEventHandler::FuncMapMove(const char* zone, int x, int y)
{
	return (this->*_FuncMapMove)(zone, x, y);

	//TODO
}


hook_method<bool (CScriptEventHandler::*)(int effectenum)> CScriptEventHandler::_FuncSetEffectStatus(SERVER, "CScriptEventHandler::FuncSetEffectStatus");
bool CScriptEventHandler::FuncSetEffectStatus(int effectenum)
{
	return (this->*_FuncSetEffectStatus)(effectenum);

	//TODO
}


/// @patch obey defined mob spawn area
hook_method<CNPC* (CScriptEventHandler::*)(int id, const char* mapName, NpcSvrNpcInfo* npcInfo)> CScriptEventHandler::_AddNpc(SERVER, "CScriptEventHandler::AddNpc");
HOOKED CNPC* CScriptEventHandler::AddNpc(int id, const char* mapName, NpcSvrNpcInfo* npcInfo)
{
	npcInfo->dx = 0;
	npcInfo->dy = 0;
	return (this->*_AddNpc)(id, mapName, npcInfo);

	PACKET_NZ_NEWNPC packet;
	packet.NAID = id;
	packet.xPos = LOWORD(npcInfo->x) + LOWORD(npcInfo->dx);
	packet.yPos = LOWORD(npcInfo->y) + LOWORD(npcInfo->dy);
	packet.xSize = LOBYTE(npcInfo->w);
	packet.ySize = LOBYTE(npcInfo->h);
	packet.spriteType = LOWORD(npcInfo->sprite);
	packet.direction = LOBYTE(npcInfo->direction);
	packet.npcType = LOBYTE(npcInfo->type);
	packet.RegenMinTime = npcInfo->regenMin;
	packet.RegenMaxTime = npcInfo->regenMax;
	packet.RegenType = npcInfo->regenType;
	packet.force = 0;
	memcpy(packet.mapName, mapName, sizeof(packet.mapName));
	memcpy(packet.NPCName, npcInfo->name, sizeof(packet.NPCName));
	packet.NPCName[sizeof(packet.NPCName)-1] = '\0';

	CNPC* npc = g_characterMgr->CCharacterMgr::AddNPC(&packet, 0);

	this->EventLog("NPC[%d] : create type[%d] zone[%s/%d] name[%s/%d] %d %d %d %d spr %d dir %d spd %d size[%d/%d/%d] regenMin:%d regenMax:%d regenType:%d\n",
		packet.NAID, packet.npcType, packet.mapName, sizeof(packet.mapName), packet.NPCName, sizeof(packet.NPCName),
		packet.xPos, packet.yPos, packet.xSize, packet.ySize, packet.spriteType, packet.direction, packet.force,
		sizeof(PACKET_NZ_NEWNPC), sizeof(packet.mapName), sizeof(packet.NPCName), packet.RegenMinTime, packet.RegenMaxTime, packet.RegenType);

	g_npcSvr->m_npcNames.insert(npcInfo->name);

	return npc;
}


hook_method<void (CScriptEventHandler::*)(char* str, ...)> CScriptEventHandler::_EventLog(SERVER, "CScriptEventHandler::EventLog");
void CScriptEventHandler::EventLog(char* str, ...)
{
//	return (this->*_EventLog)(str, BAR);

	va_list va;
	va_start(va, str);

	char buf[1024];
	vsprintf(buf, str, va);

	if( g_EventLog == 1 )
		Trace(buf);
}
