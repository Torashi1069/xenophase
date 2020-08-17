#include "CharacterMgr.h"
#include "CStaticNPCAIDGenerator.h"
#include "Enum.h"
#include "FSMState.h"
#include "MapResMgr.h"
#include "MonParameterMgr.h"
#include "NpcMob.h"
#include "SkillTypeInfoMgr.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "Common/Packet.h"
#include "LuaMonsterAI/NLuaMonsterAIGlueFunc.h"
#include "LuaMonsterAI/NLuaMonsterAIMgr.h"
#include "NpcServer/NpcSvr.h"
#include "shared/CMapInfoMgr.h"


int LuaGlueFunc_IsTarget(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);
	const unsigned long in_TargetAID = lua_tointeger(L, 2);
	const unsigned long in_IncludeAttr = lua_tointeger(L, 3);

	CCharacter* cpMyCH = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( cpMyCH == NULL )
	{
		lua_pushboolean(L, FALSE);
		return 1;
	}

	if( cpMyCH->GetState() == CHARACTER_STATE_DEAD )
	{
		lua_pushboolean(L, FALSE);
		return 1;
	}

	CCharacter* cpTargetCH = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_TargetAID);
	if( cpTargetCH == NULL )
	{
		lua_pushboolean(L, FALSE);
		return 1;
	}

	if( cpTargetCH->GetState() == CHARACTER_STATE_DEAD && !(cpTargetCH->GetEffective(EFST_TRICKDEAD, 0) && (in_IncludeAttr & 2)) )
	{
		lua_pushboolean(L, FALSE);
		return 1;
	}

	int targetEffectState = 0;
	cpTargetCH->GetParameterValue(VAR_EFFECTSTATE, targetEffectState);

	if( targetEffectState & EFFECTSTATE_SPECIALHIDING )
	{
		lua_pushboolean(L, FALSE);
		return 1;
	}

	if( (targetEffectState & EFFECTSTATE_HIDING) && !(in_IncludeAttr & 1) )
	{
		lua_pushboolean(L, FALSE);
		return 1;
	}

	if( (targetEffectState & EFFECTSTATE_BURROW) && !(in_IncludeAttr & 4) )
	{
		lua_pushboolean(L, FALSE);
		return 1;
	}

	if( cpTargetCH->GetEffective(EFST_CAMOUFLAGE, 0) && !(in_IncludeAttr & 8) )
	{
		lua_pushboolean(L, FALSE);
		return 1;
	}

	if( !cpTargetCH->IsTarget(cpMyCH, TARGET_NORMAL) )
	{
		lua_pushboolean(L, FALSE);
		return 1;
	}

	lua_pushboolean(L, TRUE);
	return 1;
}


int LuaGlueFunc_Skill(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);
	const unsigned long in_TargetAID = lua_tointeger(L, 2);
	const char* in_skName = lua_tolstring(L, 3, NULL);

	unsigned short SKID = g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetSKID(in_skName);

	CNPC* cpNpc = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( cpNpc == NULL )
		return lua_yield(L, 0);

	if( cpNpc->GetState() == CHARACTER_STATE_DEAD )
		return lua_yield(L, 0);

	cpNpc->m_npcSkill.CNPCSkill::ForceUseSkill(in_TargetAID, SKID, 1, 1000, -1);
	return lua_yield(L, 0);
}


int LuaGlueFunc_IsRechargeTime(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);

	CNPC* cpNpc = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( cpNpc == NULL )
	{
		lua_pushboolean(L, FALSE);
		return lua_yield(L, 1);
	}

	if( cpNpc->GetState() == CHARACTER_STATE_DEAD )
	{
		lua_pushboolean(L, FALSE);
		return lua_yield(L, 1);
	}

	if( !cpNpc->IsRechargeTime() )
	{
		lua_pushboolean(L, FALSE);
		return lua_yield(L, 1);
	}

	lua_pushboolean(L, TRUE);
	return lua_yield(L, 1);
}


int LuaGlueFunc_Attack(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);
	const unsigned long in_TargetAID = lua_tointeger(L, 2);

	CNPC* cpNpc = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( cpNpc == NULL )
		return lua_yield(L, 0);

	if( cpNpc->GetState() == CHARACTER_STATE_DEAD )
		return lua_yield(L, 0);

	CCharacter* pTargetCh = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_TargetAID);
	if( pTargetCh == NULL )
		return lua_yield(L, 0);

	cpNpc->m_npcStateUpdater.CNPCStateUpdater::OnRevengeEnemy(pTargetCh);
	return lua_yield(L, 0);
}


int LuaGlueFunc_Trace(lua_State* L)
{
	lua_tolstring(L, 1, NULL);
	return lua_yield(L, 0);
}


int LuaGlueFunc_SummaryUpdate(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);

	CNPC* cpNpc = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( cpNpc == NULL )
	{
		lua_pushinteger(L, timeGetTime());
		lua_pushinteger(L, 0);
		lua_pushinteger(L, 0);
		lua_pushinteger(L, 0);
		lua_pushinteger(L, 0);
		return lua_yield(L, 5);
	}

	lua_pushinteger(L, timeGetTime());
	lua_pushinteger(L, cpNpc->m_pathInfo.m_moveInfo.xPos);
	lua_pushinteger(L, cpNpc->m_pathInfo.m_moveInfo.yPos);
	lua_pushinteger(L, cpNpc->m_currentState);
	lua_pushinteger(L, cpNpc->m_pathInfo.m_moveInfo.state);
	return lua_yield(L, 5);
}


int LuaGlueFunc_GetAttackRange(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);

	CNPC* cpNpc = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	int attackRange = ( cpNpc != NULL ) ? cpNpc->GetCharacterInfo()->attackRange : -1;

	lua_pushinteger(L, attackRange);
	return lua_yield(L, 1);
}


int LuaGlueFunc_Move(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);
	const int in_dx = lua_tointeger(L, 2);
	const int in_dy = lua_tointeger(L, 3);

	CNPC* cpNpc = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( cpNpc == NULL )
	{
		lua_pushboolean(L, FALSE);
		return lua_yield(L, 1);
	}

	if( cpNpc->GetState() == CHARACTER_STATE_DEAD )
	{
		lua_pushboolean(L, FALSE);
		return lua_yield(L, 1);
	}

	PACKET_CZ_REQUEST_MOVE move;
	move.PacketType = 0;
	EncodePosDir(in_dx, in_dy, 0, move.dest);

	if( !cpNpc->CNPC::OnMove(&move) )
	{
		lua_pushboolean(L, FALSE);
		return lua_yield(L, 1);
	}

	lua_pushboolean(L, TRUE);
	return lua_yield(L, 1);
}


int LuaGlueFunc_GetCurPos(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);
	const unsigned long in_OtherAID = lua_tointeger(L, 2);

	CCharacter* pMyCharacter = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( pMyCharacter == NULL )
	{
		lua_pushinteger(L, 0);
		lua_pushinteger(L, 0);
		return lua_yield(L, 2);
	}
	
	CCharacter* pOtherCharacter = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_OtherAID);
	if( pOtherCharacter == NULL )
	{
		lua_pushinteger(L, 0);
		lua_pushinteger(L, 0);
		return lua_yield(L, 2);
	}
	
	if( pMyCharacter->CCharacter::GetMapRes() != pOtherCharacter->CCharacter::GetMapRes() )
	{
		lua_pushinteger(L, 0);
		lua_pushinteger(L, 0);
		return lua_yield(L, 2);
	}

	int targetXpos = 0;
	int targetYpos = 0;
	pOtherCharacter->GetParameterValue(VAR_CURXPOS, targetXpos);
	pOtherCharacter->GetParameterValue(VAR_CURYPOS, targetYpos);

	lua_pushinteger(L, targetXpos);
	lua_pushinteger(L, targetYpos);
	return lua_yield(L, 2);
}


int LuaGlueFunc_Revival(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);

	CNPC* cpNpc = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( cpNpc == NULL )
		return lua_yield(L, 0);

	if( cpNpc->GetState() != CHARACTER_STATE_DEAD && cpNpc->CNPC::GetCurrentFSMState() != DEAD_ST )
		return lua_yield(L, 0);

	cpNpc->m_npcStateUpdater.CNPCStateUpdater::OnRevival(IDLE_ST);
	return lua_yield(L, 0);
}


int LuaGlueFunc_GetAsyncMsg(lua_State* L)
{
	const int in_SvrScriptAppID = lua_tointeger(L, 1);

	NLuaMonsterAI* cpApp = NLuaMonsterAIMgr::GetObj()->NLuaMonsterAIMgr::GetAppPtr(in_SvrScriptAppID);
	if( cpApp == NULL )
		return lua_yield(L, 0);

	std::pair<bool,NLuaMonsterAI::MSG_SHARDPTR> msgRet = cpApp->NLuaMonsterAI::GetAsyncMsg();
	if( !msgRet.first )
		return lua_yield(L, 0);

	LuaMonsterAIStuff::NMSG* msgBase = msgRet.second.get();
	switch( msgBase->LuaMonsterAIStuff::NMSG::GetMSGID() )
	{
	case LuaMonsterAIStuff::MSGID_ATTACKED:
	{
		LuaMonsterAIStuff::NMSG_ATTACKED* msg = static_cast<LuaMonsterAIStuff::NMSG_ATTACKED*>(msgBase);
		lua_pushinteger(L, LuaMonsterAIStuff::MSGID_ATTACKED);
		lua_pushinteger(L, msg->m_AID);
		lua_pushinteger(L, msg->m_Damage);
		return lua_yield(L, 3);
	}
	break;
	case LuaMonsterAIStuff::MSGID_DEAD:
	{
		LuaMonsterAIStuff::NMSG_DEAD* msg = static_cast<LuaMonsterAIStuff::NMSG_DEAD*>(msgBase);
		lua_pushinteger(L, LuaMonsterAIStuff::MSGID_DEAD);
		lua_pushinteger(L, msg->m_AID);
		return lua_yield(L, 2);
	}
	break;
	case LuaMonsterAIStuff::MSGID_LOG:
	{
		LuaMonsterAIStuff::NMSG_LOG* msg = static_cast<LuaMonsterAIStuff::NMSG_LOG*>(msgBase);
		lua_pushinteger(L, LuaMonsterAIStuff::MSGID_LOG);
		return lua_yield(L, 1);
	}
	break;
	case LuaMonsterAIStuff::MSGID_TELEPORT:
	{
		LuaMonsterAIStuff::NMSG_TELEPORT* msg = static_cast<LuaMonsterAIStuff::NMSG_TELEPORT*>(msgBase);
		lua_pushinteger(L, LuaMonsterAIStuff::MSGID_TELEPORT);
		lua_pushinteger(L, msg->m_xPos);
		lua_pushinteger(L, msg->m_yPos);
		lua_pushstring(L, msg->m_MapName);
		return lua_yield(L, 4);
	}
	break;
	default:
	{
		return lua_yield(L, 0);
	}
	break;
	};
}


int LuaGlueFunc_GetNeighborNum(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);

	CCharacter* pCharacter = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	int neighborNum = ( pCharacter != NULL ) ? pCharacter->CCharacter::GetNeighborPlayerNum() : 0;

	lua_pushinteger(L, neighborNum);
	return lua_yield(L, 1);
}


int LuaGlueFunc_timeGetTime(lua_State* L)
{
	lua_pushinteger(L, timeGetTime());
	return 1;
}


int LuaGlueFunc_DebugMsg(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);
	const char* in_pMsg = lua_tolstring(L, 2, 0);

	CCharacter* pCharacter = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( pCharacter->GetType() != NPC_MOB_TYPE )
		return lua_yield(L, 0);

	CMapRes* mapRes = pCharacter->CCharacter::GetMapRes();
	if( mapRes == NULL )
		return lua_yield(L, 0);

	std::string msg = in_pMsg;

	BROADCAST_INFO info;
	info.packetType = HEADER_ZC_BROADCAST;
	info.broadcastType = 0;
	info.str = const_cast<char*>(msg.c_str());
	mapRes->CMapRes::Broadcast(&info);

	return lua_yield(L, 0);
}


int LuaGlueFunc_GetObjects(lua_State* L)
{
	const unsigned long in_AID = lua_tointeger(L, 1);
	const int in_myXpos = lua_tointeger(L, 2);
	const int in_myYpos = lua_tointeger(L, 3);
	const int in_range = lua_tointeger(L, 4);

	lua_createtable(L, 0, 0);

	CCharacter* cpMyCharacter = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(in_AID);
	if( cpMyCharacter->GetType() != NPC_MOB_TYPE )
		return lua_yield(L, 1);

	CMapRes* mapRes = cpMyCharacter->CCharacter::GetMapRes();
	if( mapRes == NULL )
		return lua_yield(L, 1);

	NEIGHBORHOOD_SECTION result = {};
	mapRes->CMapRes::GetNeighborhoodSections(in_myXpos, in_myYpos, in_range, &result);

	for( int k = 0; k < 4; ++k )
	{
		std::vector<CCharacter*>* sectionList = result.section[k];
		if( sectionList == NULL )
			continue;

		std::vector<CCharacter*>::iterator iter;
		for( iter = sectionList->begin(); iter != sectionList->end(); ++iter )
		{
			CCharacter* ch = *iter;
			if( ch == NULL )
				continue;

			if( cpMyCharacter == ch )
				continue;

			int targetXpos = 0;
			int targetYpos = 0;
			ch->GetParameterValue(VAR_CURXPOS, targetXpos);
			ch->GetParameterValue(VAR_CURYPOS, targetYpos);
			if( abs(in_myXpos - targetXpos) > in_range || abs(in_myYpos - targetYpos) > in_range )
				continue;

			int targetEffectState = 0;
			ch->GetParameterValue(VAR_EFFECTSTATE, targetEffectState);

			int Attr = 0;
			if( targetEffectState & EFFECTSTATE_SPECIALHIDING )
				Attr |= 2;
			if( targetEffectState & EFFECTSTATE_HIDING )
				Attr |= 1;
			if( targetEffectState & EFFECTSTATE_BURROW )
				Attr |= 16;
			if( ch->GetState() == CHARACTER_STATE_DEAD )
			{
				Attr |= 4;
				if( ch->GetEffective(EFST_TRICKDEAD, 0) )
					Attr |= 8;
			}
			if( ch->GetEffective(EFST_CAMOUFLAGE, 0) )
				Attr |= 32;

			lua_pushnumber(L, ch->GetAccountID());
			lua_createtable(L, 0, 0);
			lua_pushstring(L, "type");
			lua_pushnumber(L, ch->GetType());
			lua_settable(L, -3);
			lua_pushstring(L, "attr");
			lua_pushnumber(L, Attr);
			lua_settable(L, -3);
			lua_settable(L, -3);
		}
	}

	return lua_yield(L, 1);
}


int LuaGlueFunc_GetV(lua_State* L)
{
	unsigned long AID = lua_tointeger(L, 1);

	CCharacter* pCharacter = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(AID);
	if( pCharacter == NULL )
	{
		lua_pushnil(L);
		return lua_yield(L, 1);
	}

	std::vector<int> VARs;
	for( int idx = 2; lua_isnumber(L, idx); ++idx )
	{
		int data = lua_tointeger(L, idx);
		VARs.push_back(data);
	}

	for( std::vector<int>::iterator iter = VARs.begin(); iter != VARs.end(); ++iter )
	{
		int var = *iter;

		if( var == VAR_NAME )
		{
			switch( pCharacter->GetType() )
			{
			case PC_TYPE     : lua_pushstring(L, static_cast<CPC*>(pCharacter)->CPC::GetCharacterName()); break;
			case NPC_TYPE    : lua_pushstring(L, static_cast<CNPC*>(pCharacter)->CNPC::GetAccountName()); break;
			case ITEM_TYPE   : lua_pushstring(L, static_cast<CItem*>(pCharacter)->CItem::GetName()); break;
			case NPC_MOB_TYPE: lua_pushstring(L, static_cast<CNpcMob*>(pCharacter)->CNPC::GetAccountName()); break;
			default          : lua_pushstring(L, "unknown"); break;
			};
		}
		else
		if( var == VAR_FSMSTATE )
		{
			if( pCharacter->GetType() == NPC_TYPE || pCharacter->GetType() == NPC_MOB_TYPE )
			{
				lua_pushnumber(L, static_cast<CNPC*>(pCharacter)->CNPC::GetCurrentFSMState());
			}
			else
			{
				lua_pushnil(L);
			}
		}
		else
		{
			int data = 0;
			pCharacter->GetParameterValue(var, data);
			lua_pushnumber(L, data);
		}
	}

	return lua_yield(L, VARs.size());
}


static int mylua_tocolor(lua_State* L, int in_TblIdx)
{
	lua_pushstring(L, "R");
	lua_gettable(L, 2);
	int R = (int)lua_tonumber(L, -1);
	lua_settop(L, -2);

	lua_pushstring(L, "G");
	lua_gettable(L, 2);
	int G = (int)lua_tonumber(L, -1);
	lua_settop(L, -2);

	lua_pushstring(L, "B");
	lua_gettable(L, 2);
	int B = (int)lua_tonumber(L, -1);
	lua_settop(L, -2);

	return (B << 16) + (G << 8) + (R << 0);
}


int LuaGlueFunc_Chat(lua_State* L)
{
	const unsigned long AID = lua_tointeger(L, 1);
	const unsigned long color = mylua_tocolor(L, 2);
	const char* szpChat = lua_tolstring(L, 3, NULL);

	CCharacter* pCharacter = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(AID);
	if( pCharacter == NULL )
		return lua_yield(L, 0);

	int charType = pCharacter->GetType();
	if( charType == NPC_MOB_TYPE || charType == NPC_ELEMENTAL_TYPE )
	{
		CNPC* cpNpc = static_cast<CNPC*>(pCharacter);
		cpNpc->CNPC::Chat(szpChat, color);
	}

	return lua_yield(L, 0);
}


int LuaGlueFunc_Emotion(lua_State* L)
{
	const unsigned long AID = lua_tointeger(L, 1);
	const int type = lua_tointeger(L, 2);

	CCharacter* pCharacter = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(AID);
	if( pCharacter == NULL )
		return lua_yield(L, 0);

	int charType = pCharacter->GetType();
	if( charType == NPC_MOB_TYPE )
	{
		CNPC* cpNpc = static_cast<CNPC*>(pCharacter);
		cpNpc->CNPC::OnEmotion(type);
	}

	return lua_yield(L, 0);
}


int LuaGlueFunc_Teleport(lua_State* L)
{
	const unsigned long AID = lua_tointeger(L, 1);
	int xPos = lua_tointeger(L, 2);
	int yPos = lua_tointeger(L, 3);
	const char* mapName = lua_tolstring(L, 4, NULL);

	CCharacter* pCharacter = CCharacterMgr::GetObj()->CCharacterMgr::FastFindCharacter(AID);
	if( pCharacter == NULL )
		return lua_yield(L, 0);

	if( pCharacter->GetState() == CHARACTER_STATE_DEAD )
		return lua_yield(L, 0);

	CMapRes* mapRes = ( mapName != NULL ) ? g_mapResMgr.CMapResMgr::GetMapRes(mapName) : pCharacter->CCharacter::GetMapRes();
	if( mapRes == NULL || !mapRes->CMapRes::GetValidPos(xPos, yPos) )
		return lua_yield(L, 0);

	COMMAND_QUEUE command;
	command.commandID = TELEPORT_IN;
	command.executionTime = timeGetTime() + 500;
	command.sender = AID;
	command.par1 = (int)mapRes->CMapRes::GetName();
	command.par2 = xPos;
	command.par3 = yPos;
	command.par4 = 0;
	pCharacter->InsertCommand(&command);

	return lua_yield(L, 0);
}


int LuaGlueFunc_PutMob(lua_State* L)
{
	const char* in_szpZoneName = lua_tolstring(L, 1, NULL);
	const int in_x = lua_tointeger(L, 2);
	const int in_y = lua_tointeger(L, 3);
	const int in_width = lua_tointeger(L, 4);
	const int in_height = lua_tointeger(L, 5);
	const char* in_szpKeyword = lua_tolstring(L, 6, NULL);
	const int in_RegenMinTM = lua_tointeger(L, 7);
	const int in_RegenMaxTM = lua_tointeger(L, 8);
	const int in_RegenType = lua_tointeger(L, 9);
	const char* in_szpNickName = lua_tolstring(L, 10, NULL);
	const BOOL in_IsBoss = lua_toboolean(L, 11);
	const char* in_szpAIName = lua_tolstring(L, 12, NULL);

	const int MobID = g_monParameter.CMonParameterMgr::SearchKeyword(in_szpKeyword);
	if( MobID <= 0 )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, "unknown mob name");
		return lua_yield(L, 2);
	}

	std::string mapName = std::string() + in_szpZoneName + ".gat";
	if( GetLocalServerID() != CMapInfoMgr::GetObj()->CMapInfoMgr::GetServerID(mapName.c_str()) )
	{
		lua_pushboolean(L, TRUE);
		return lua_yield(L, 1);
	}

	if( in_width < 0 )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, "width is minus value");
		return lua_yield(L, 2);
	}

	if( in_height < 0 )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, "height is minus value");
		return lua_yield(L, 2);
	}

	std::string Name = "";
	const char* szpMonsterName = g_monParameter.CMonParameterMgr::GetMonsterName(MobID);
	if( szpMonsterName != NULL )
		Name = szpMonsterName;
	if( in_szpNickName != NULL )
		Name = in_szpNickName;

	if( Name.size() == 0 )
	{
		lua_pushboolean(L, FALSE);
		lua_pushstring(L, "name is empty");
		return lua_yield(L, 2);
	}

	PACKET_NZ_NEWNPC packet = {};
	packet.NAID = 0;
	packet.xPos = 0;
	packet.yPos = 0;
	packet.xSize = in_width;
	packet.ySize = in_height;
	packet.spriteType = MobID;
	packet.RegenMinTime = in_RegenMinTM;
	packet.RegenMaxTime = in_RegenMaxTM;
	packet.RegenType = in_RegenType;
	packet.force = false;
	packet.npcType = LUA_AI_TYPE;
	packet.direction = 0;
	memcpy_s(packet.mapName, sizeof(packet.mapName), mapName.c_str(), 16);
	size_t NameLen = min(Name.size(), 24-1);
	memcpy_s(packet.NPCName, sizeof(packet.NPCName), Name.c_str(), NameLen);
	packet.NPCName[NameLen] = '\0';

	CStaticNPCAID StaticNPCAID = CStaticNPCAIDGenerator::GetObj()->CStaticNPCAIDGenerator::Alloc();
	if( StaticNPCAID == 0 )
	{
		lua_pushboolean(L, TRUE);
		return lua_yield(L, 1);
	}

	packet.NAID = StaticNPCAID;
	packet.xPos = in_x;
	packet.yPos = in_y;

	CNpcMob* cpNpcMob = static_cast<CNpcMob*>(CCharacterMgr::GetObj()->CCharacterMgr::AddNPC(&packet, 0, 0));
	if( cpNpcMob == NULL )
	{
		lua_pushboolean(L, TRUE);
		return lua_yield(L, 1);
	}

	StaticNPCAID.CStaticNPCAID::Release();

	if( cpNpcMob->GetType() == NPC_MOB_TYPE )
	{
		int AppID = NLuaMonsterAIMgr::GetObj()->NLuaMonsterAIMgr::CreateApp(cpNpcMob->GetAccountID(), in_szpAIName, false);
		if( AppID == 0 )
		{
			CCharacterMgr::GetObj()->CCharacterMgr::Free(cpNpcMob);
			lua_pushboolean(L, FALSE);
			lua_pushstring(L, "server script create error");
			return lua_yield(L, 2);
		}

		cpNpcMob->CNpcMob::SetSvrScriptAppID(AppID);
	}

	g_npcSvr.m_npcNames.insert(packet.NPCName);

	if( in_IsBoss )
		CCharacterMgr::GetObj()->CCharacterMgr::RegisterBossInMap(cpNpcMob);

	lua_pushboolean(L, TRUE);
	return lua_yield(L, 1);
}


int LuaGlueFunc_GetOwnerAID(lua_State* L)
{
	const int npcAID = lua_tointeger(L, 1);

	CNPC* cpNpc = (CNPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(npcAID, NPC_TYPE);
	unsigned long ownerAID = ( cpNpc != NULL ) ? cpNpc->CNPC::GetParentAID() : 0;

	lua_pushinteger(L, ownerAID);
	return lua_yield(L, 1);
}


int LuaGlueFunc_IsServiceMap(lua_State* L)
{
	const char* in_szpZoneName = lua_tolstring(L, 1, NULL);

	std::string mapName = std::string() + in_szpZoneName + ".gat";
	BOOL b = ( GetLocalServerID() == CMapInfoMgr::GetObj()->CMapInfoMgr::GetServerID(mapName.c_str()) );

	lua_pushboolean(L, b);
	return lua_yield(L, 1);
}
