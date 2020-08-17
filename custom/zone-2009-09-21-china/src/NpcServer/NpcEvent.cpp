#include "globals.hpp"
#include "struct.hpp"
#include "CharacterMgr.h"
#include "ErrorLog.h"
#include "MapInfo.h"
#include "MonParameterMgr.h"
#include "CMsg.hpp"
#include "NPC.h"
#include "Common/Packet.h"
#include "NpcServer/NpcObj.h"
#include "NpcServer/NpcEvent.h"
#include "NpcServer/NpcSvr.h"
#include "shared.h" // Trace


hook_val<int> CNpcEvent::m_serverID(SERVER, "CNpcEvent::m_serverID"); // = ?


hook_method<bool (CNpcEvent::*)(CNpcMgr* npcMgr, CBinBuf* binBuf, int pcId, int npcId, int actIndex)> CNpcEvent::_Run(SERVER, "CNpcEvent::Run");
bool CNpcEvent::Run(CNpcMgr* npcMgr, CBinBuf* binBuf, int pcId, int npcId, int actIndex) // line 200
{
	return (this->*_Run)(npcMgr, binBuf, pcId, npcId, actIndex);

	//TODO
}


hook_method<void (CNpcEvent::*)(CNpcMgr* mobMgr)> CNpcEvent::_RegisterMobMgr(SERVER, "CNpcEvent::RegisterMobMgr");
void CNpcEvent::RegisterMobMgr(CNpcMgr* mobMgr) // line 175
{
	return (this->*_RegisterMobMgr)(mobMgr);

	m_mobMgr = mobMgr;
}


hook_method<unsigned int (CNpcEvent::*)(bool isOnce)> CNpcEvent::_Proc(SERVER, "CNpcEvent::Proc");
unsigned int CNpcEvent::Proc(bool isOnce) // line 250
{
	return (this->*_Proc)(isOnce);

	if( m_binBuf == NULL )
		return 0;

	if( m_waitType != 0 )
	{
		if( m_waitTime > _time32(NULL) )
			return 2;

		this->CNpcEvent::Stop();
		return 0;
	}

	if( m_interpreter.CInterpreter::Proc() )
		return 1;

	if( m_reserveTime != 0 )
		m_npc->CNpc::OnTimer();

	return 0;
}


hook_method<bool (CNpcEvent::*)(int func, mystd::deque<TokenData>& parm, TokenData& ret)> CNpcEvent::_OnFunc(SERVER, "CNpcEvent::OnFunc");
bool CNpcEvent::OnFunc(int func, mystd::deque<TokenData>& parm, TokenData& ret)
{
	return (this->*_OnFunc)(func, parm, ret);

	ret = 0;

	switch( func )
	{
	case 147:
		if( this->CScriptEventHandler::CheckFixedVarNum(parm, 1) )
			return this->CNpcEvent::FuncTrace(parm[0].TokenData::GetStr());
	break;
	case 211:
		if( this->CScriptEventHandler::CheckFixedVarNum(parm, 0) )
			return this->CNpcEvent::FuncError(ret);
	break;
	case 172:
		return this->CScriptEventHandler::OnFunc(func, parm, ret);
	break;
	case 173:
		if( this->CScriptEventHandler::CheckFixedVarNum(parm, 2) )
			return this->CNpcEvent::FuncLot(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), ret);
	break;
	default:
	break;
	}

	if( m_npcId )
		return this->CNpcEvent::DefaultNpcFunc(func, parm, ret);
	else
		return this->CNpcEvent::GlobalFunc(func, parm, ret);
}


hook_method<void (CNpcEvent::*)(void)> CNpcEvent::_Stop(SERVER, "CNpcEvent::Stop");
void CNpcEvent::Stop(void) // line 294
{
	return (this->*_Stop)();

	//TODO
}


//hook_method<void (CNpcEvent::*)(DWORD reserveTime)> CNpcEvent::_SetReserveTime(SERVER, "CNpcEvent::SetReserveTime");
void CNpcEvent::SetReserveTime(DWORD reserveTime)
{
//	return (this->*_SetReserveTime)(reserveTime);

	m_reserveTime = reserveTime;
}


//hook_method<DWORD (CNpcEvent::*)(void)> CNpcEvent::_GetReserveTime(SERVER, "CNpcEvent::GetReserveTime");
DWORD CNpcEvent::GetReserveTime(void)
{
//	return (this->*_GetReserveTime)();

	return m_reserveTime;
}


//hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_GetOnInit(SERVER, "CNpcEvent::GetOnInit");
bool CNpcEvent::GetOnInit(void) // line ???
{
//	return (this->*_GetOnInit)();

	return m_OnInit;
}


//hook_method<void (CNpcEvent::*)(bool oninit)> CNpcEvent::_SetOnInit(SERVER, "CNpcEvent::SetOnInit");
void CNpcEvent::SetOnInit(bool oninit) // line ???
{
//	return (this->*_SetOnInit)(oninit);

	m_OnInit = oninit;
}


hook_method<bool (CNpcEvent::*)(int func, mystd::deque<TokenData>& parm, TokenData& ret)> CNpcEvent::_GlobalFunc(SERVER, "CNpcEvent::GlobalFunc");
bool CNpcEvent::GlobalFunc(int func, mystd::deque<TokenData>& parm, TokenData& ret)
{
	return (this->*_GlobalFunc)(func, parm, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int func, mystd::deque<TokenData>& parm, TokenData& ret)> CNpcEvent::_DefaultNpcFunc(SERVER, "CNpcEvent::DefaultNpcFunc");
bool CNpcEvent::DefaultNpcFunc(int func, mystd::deque<TokenData>& parm, TokenData& ret) // line 598
{
	return (this->*_DefaultNpcFunc)(func, parm, ret);

	switch( func )
	{
	case 163:
	case 165:
	case 166:
	case 167:
	case 169:
	case 170:
	case 175:
	case 176:
	case 177:
	case 178:
	case 179:
	case 180:
	case 181:
	case 182:
	case 183:
	case 186:
	case 267:
	case 504:
	case 505:
	case 506:
		return false;
	case 185: // fall through
	case 188: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->FuncDialog(parm[0].TokenData::GetStr(), 0);
	case 195: return this->FuncWaitDialog(0);
	case 196: return this->FuncCloseDialog(0);
	case 187: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) ? false : this->FuncMapMove(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	case 189:
	case 252:
	{
		if( parm.size() < 1 )
			break;

		mystd::string data = "";
		for( mystd::deque<TokenData>::iterator qi = parm.begin(); qi != parm.end(); ++qi )
		{
			if( qi->TokenData::IsStr() )
			{
				data += qi->TokenData::GetStr();
				data += ':';
			}
		}

		m_nParamSize = parm.size() - 1;
		return this->CNpcEvent::FuncMenu(data.c_str(), func == 252);
	}
	case 148: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncVar(parm[0].TokenData::GetNum(), ret);
	case 149: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncLV(parm[0].TokenData::GetStr(), ret);
	case 150: return this->CNpcEvent::FuncNpcV(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), ret);
	case 151: return this->CNpcEvent::FuncIncLocalVar(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 152: return this->CNpcEvent::FuncDecLocalVar(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 153: return this->CNpcEvent::FuncSetLocalVar(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 154: return this->CNpcEvent::FuncGetEquipIsIdentify(parm[0].TokenData::GetNum(), ret);
	case 155: return this->CNpcEvent::FuncGetEquipRefineryCnt(parm[0].TokenData::GetNum(), ret);
	case 156: return this->CScriptEventHandler::FuncGetEquipPercentRefinery(parm[0].TokenData::GetNum(), ret, 0);
	case 157: return this->CNpcEvent::FuncGetEquipRefineryCost(parm[0].TokenData::GetNum(), ret);
	case 158: return this->CScriptEventHandler::FuncGetEquipIsSuccessRefinery(parm[0].TokenData::GetNum(), ret, 0);
	case 159: return this->CNpcEvent::FuncGetEquipName(parm[0].TokenData::GetNum(), ret);
	case 160: return this->CNpcEvent::FuncGetEquipItemIdx(parm[0].TokenData::GetNum(), ret);
	case 161: return this->CNpcEvent::FuncGetEquipWeaponLv(parm[0].TokenData::GetNum(), ret);
	case 162: return this->CNpcEvent::FuncGetEquipIsEnableRef(parm[0].TokenData::GetNum(), ret);
	case 226: return this->CNpcEvent::FuncInitTimer();
	case 190: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetMoney(parm[0].TokenData::GetNum());
	case 191: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncDropMoney(parm[0].TokenData::GetNum(), ret);
	case 194: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetItem(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 192: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncGetItem(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 193: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncDropItem(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case   4: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncInc(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case   5: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncDec(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 197: return this->CNpcEvent::FuncHeal(5, 100);
	case 198: return this->CNpcEvent::FuncHeal(7, 100);
	case 199: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncHeal(5, parm[0].TokenData::GetNum());
	case 200: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncHeal(7, parm[0].TokenData::GetNum());
	case 201: return this->CNpcEvent::FuncHeal(26, 100);
	case 202: return this->CNpcEvent::FuncHeal(27, 100);
	case 203: return this->CNpcEvent::FuncHeal(28, 100);
	case 204: return this->CNpcEvent::FuncHeal(29, 100);
	case 205: return this->CNpcEvent::FuncHeal(30, 100);
	case 206: return this->CNpcEvent::FuncHeal(31, 100);
	case 210: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) ? false : this->CNpcEvent::FuncExchangeItem(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum());
	case 209: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncJobChange(parm[0].TokenData::GetNum());
	case 212: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) ? false : this->CNpcEvent::FuncCheckPoint(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	case 214: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncCart(parm[0].TokenData::GetNum());
	case 215: return this->CNpcEvent::FuncDlgWrite(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 213: return this->CNpcEvent::FuncStore();
	case 219: return this->CNpcEvent::FuncNude();
	case 207: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncRegSellItem(parm[0].TokenData::GetNum());
	case 218: return this->CNpcEvent::FuncCompass(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetStr());
	case 216: return this->CNpcEvent::FuncInput(ret);
	case 221: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncChangePallete(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 222:
	{
		int xsize = 0;
		int ysize = 0;
		int num = 1;

		if( parm.size() > 5 )
			xsize = parm[5].TokenData::GetNum();

		if( parm.size() > 6 )
			ysize = parm[6].TokenData::GetNum();

		if( parm.size() > 7 )
			num = parm[7].TokenData::GetNum();

		return this->CNpcEvent::FuncCallMonster(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetStr(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum(), xsize, ysize, num);
	}
	case 223: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) ? false : this->CNpcEvent::FuncAddSkill(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum());
	case 224: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncOtherNpcCmd(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr());
	case 225: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncStrLocalVar(parm[0].TokenData::GetNum(), parm[1].TokenData::GetStr());
	case 227: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncSetArenaEventSize(parm[0].TokenData::GetNum());
	case 537: return this->CNpcEvent::FuncGetArenaEventSize(ret);
	case 228: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncMakeWaitingRoom(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 229: return this->CNpcEvent::FuncEnableArena();
	case 230: return this->CNpcEvent::FuncDisableArena();
	case 231: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) ? false : this->CNpcEvent::FuncWarpWaitingPcToArena(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	case 232: return this->CNpcEvent::FuncResetMyMob();
	case 233: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) ? false : this->CNpcEvent::FuncWarpAllPcInTheMap(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	case 234: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncBroadcastInTheMap(parm[0].TokenData::GetStr());
	case 235:
	{
		CNpc* npc = m_npcMgr->CNpcMgr::Get(m_npcId);
		if( npc == NULL )
		{
			Trace("PauseTimer failed %s\n", m_npc->CNpc::GetName());
			return false;
		}

		npc->CNpc::PauseTimer();
		Trace("PauseTimer\n");
		return true;
	}
	case 236: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncAddNpcTimer(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 237: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSubNpcTimer(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 238: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncEnableNpc(parm[0].TokenData::GetStr());
	case 239: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncDisableNpc(parm[0].TokenData::GetStr());
	case 240: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 6) ) ? false : this->CNpcEvent::FuncCallNpc(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetStr(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum(), parm[5].TokenData::GetNum());
	case 241: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncSetFeeZeny(parm[0].TokenData::GetNum());
	case 242: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncSetFeeItem(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 243: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetReqLevel(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 244: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncSetTexJob(parm[0].TokenData::GetNum());
	case 245: return this->CNpcEvent::FuncDisableItemMove();
	case 246: return this->CNpcEvent::FuncEnableItemMove();
	case 247: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncSuccessRefItem(parm[0].TokenData::GetNum());
	case 248: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncFailedRefItem(parm[0].TokenData::GetNum());
	case 249: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->FuncSetEffectStatus(parm[0].TokenData::GetNum());
	case 250: return this->CNpcEvent::FuncResetStat();
	case 174: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetPcCount(parm[0].TokenData::GetStr(), ret);
	case 253: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncShowDigit(parm[0].TokenData::GetNum());
	case 254: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncEnableSkill(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 255: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncDisableSkill(parm[0].TokenData::GetNum());
	case 256: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetParameter(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 257: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncEmotion(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 258: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncChangeSpr(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 259: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetEquipCount(parm[0].TokenData::GetNum(), ret);
	case 260: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncAgitGet(0, parm[0].TokenData::GetNum(), ret);
	case 261: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncAgitGet(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), ret);
	case 262: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncAgitSet(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 263: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) ? false : this->CNpcEvent::FuncAgitFunc(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	case 264: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncAgitNpcGet(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), ret);
	case 265: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) ? false : this->CNpcEvent::FuncAgitNpcSet(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	case 266: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncIsGuildMaster(parm[0].TokenData::GetNum(), ret);
	case 268: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncAgitRegister(parm[0].TokenData::GetStr());
	case 269: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 6) ) ? false : this->CNpcEvent::FuncBroadcast(0, parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum(), parm[5].TokenData::GetStr());
	case 271: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) ? false : this->CNpcEvent::FuncSound(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum());
	case 272: return this->FuncDlgWriteStr(0);
	case 273: return this->CNpcEvent::FuncGetDamagedItemNum(ret);
	case 274: return this->CNpcEvent::FuncRepairDamagedItem();
	case 275:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) )
		{
			g_errorLogs->CErrorLog::CriticalErrorLog("SavePPL Parameter Error!!!\n", 949, ".\\NpcServer\\NpcEvent.Cpp");
			return false;
		}
		return this->CNpcEvent::FuncSavePPL(parm[0].TokenData::GetNum());
	case 276: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncAgitEmblemFlag(parm[0].TokenData::GetStr());
	case 277: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncHeal(5, -parm[0].TokenData::GetNum());
	case 278: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncHeal(7, -parm[0].TokenData::GetNum());
	case 279: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncChangeEXP(parm[0].TokenData::GetNum());
	case 280: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncChangeEXP(-parm[0].TokenData::GetNum());
	case 281: return this->CNpcEvent::FuncServerTime(ret);
	case 282: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetLocalVarName(parm[0].TokenData::GetNum(), ret);
	case 283: return this->CNpcEvent::FuncGetMarried(ret);
	case 285: return this->CNpcEvent::FuncGetGuildName(ret);
	case 284: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncCountDown(parm[0].TokenData::GetNum());
	case 286: return this->CNpcEvent::FuncGetNeighborPcNumber(parm[0].TokenData::GetNum(), ret);
	case 287: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncGetNamedItem(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 288: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncDropNamedItem(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 289: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetCountOfMyNameItem(parm[0].TokenData::GetNum(), ret);
	case 290: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncChangeHairStyle(parm[0].TokenData::GetNum());
	case 291: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncShowEffect(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 292: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncFalcon(parm[0].TokenData::GetNum());
	case 293: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncPeco(parm[0].TokenData::GetNum());
	case 294: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncCheckMaxWeight(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), ret);
	case 295: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncCheckMaxCount(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), ret);
	case 296: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncCheckMaxZeny(parm[0].TokenData::GetNum(), ret);
	case 297: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncMGetEventZenyName(parm[0].TokenData::GetNum(), ret);
	case 298: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncMGetEventItemName(parm[0].TokenData::GetNum(), ret);
	case 299: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncMGetEventZeny(parm[0].TokenData::GetNum(), ret);
	case 300: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncMGetEventItem(parm[0].TokenData::GetNum(), ret);
	case 301: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncCreateGuild(parm[0].TokenData::GetStr());
	case 302: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncCreateGlobalVar(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 303: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetGlobalVar(parm[0].TokenData::GetStr(), ret);
	case 304: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetGlobalVar(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 305: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncStrCmp(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr(), ret);
	case 306: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncStrStr(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr(), ret);
	case 307: return this->CNpcEvent::FuncUpgradeGuildLevel();
	case 308: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncCreateGlobalStr(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr());
	case 309: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetGlobalStr(parm[0].TokenData::GetStr(), ret);
	case 310: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetGlobalStr(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr());
	case 311: return this->CNpcEvent::FuncDivorce();
	case 312: return this->CNpcEvent::FuncPEventGet(ret);
	case 313: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncPEventAdd(parm[0].TokenData::GetNum(), ret);
	case 314: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncPEventDel(parm[0].TokenData::GetNum(), ret);
	case 315: return this->CNpcEvent::FuncPCDataMoveToPVP();
	case 318: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncMGetEventItemID(parm[0].TokenData::GetNum(), ret);
	case 319: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetJobExp(parm[0].TokenData::GetNum());
	case 320: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncDropJobExp(parm[0].TokenData::GetNum());
	case 321: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncChkSkill(parm[0].TokenData::GetNum(), ret);
	case 322: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncGetBodyState(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 323: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncGetHealthState(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 324: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) ? false : this->CNpcEvent::FuncUseSkillToPC(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum());
	case 325: return this->CNpcEvent::FuncIsBaby(ret);
	case 326: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetLotto(parm[0].TokenData::GetNum(), ret);
	case 327: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 6) ) ? false : this->CNpcEvent::FuncSetLotto(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum(), parm[5].TokenData::GetNum());
	case 328: return this->CNpcEvent::FuncInitLotto();
	case 329: return this->CNpcEvent::FuncOpenAuction();
	case 330: return this->CNpcEvent::FuncOpenMailing();
	case 331: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncStripPC(parm[0].TokenData::GetNum());
	case 332: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncPushPC(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 333: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) ? false : this->CNpcEvent::FuncItemDown(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum());
	case 334: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetNumArray(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 335: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetNumArray(parm[0].TokenData::GetNum(), ret);
	case 336: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncShuffleNumbers(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 337: return this->CNpcEvent::FuncPartyName(ret);
	case 338: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncChangeSpeed(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 339: return this->CNpcEvent::FuncIsSiegeTime(ret);
	case 340: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncConsumeSpecialItem(parm[0].TokenData::GetNum());
	case 341: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetItemPartyInMap(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 342: return this->CNpcEvent::FuncIsHuntingListFull(ret);
	case 343: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncFindHuntingList(parm[0].TokenData::GetNum(), ret);
	case 344: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncAddHuntingList(parm[0].TokenData::GetNum());
	case 345: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncDeleteHuntingList(parm[0].TokenData::GetNum());
	case 346: return this->CNpcEvent::FuncDisplayHuntingList(ret);
	case 347: return this->CNpcEvent::FuncDisplayHuntingList2(ret);
	case 348: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetHuntingList(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 349: return this->CNpcEvent::FuncClearHuntingList();
	case 374: return this->CNpcEvent::FUNCUseHuntingList(ret);
	case 375: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FUNCCheckHuntingList(parm[0].TokenData::GetNum(), ret);
	case 350: return this->CNpcEvent::FuncIsTimeListFull(ret);
	case 351: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncFindTimeList(parm[0].TokenData::GetNum(), ret);
	case 352: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncAddTimeList(parm[0].TokenData::GetNum());
	case 353: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncDeleteTimeList(parm[0].TokenData::GetNum());
	case 354: return this->CNpcEvent::FuncDisplayTimeList(ret);
	case 355: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetTimeList(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 356: return this->CNpcEvent::FuncClearTimeList();
	case 357: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) ? false : this->CNpcEvent::FuncChangeCellType(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	case 358: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncGetCellType(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), ret);
	case 365: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncCashItem(parm[0].TokenData::GetStr());
	case 360: return this->CNpcEvent::FuncGetPayType(ret);
	case 361: this->CNpcEvent::FuncGetConnectionArea(ret); // fall through
	case 362: this->CNpcEvent::FuncGetConnectionState(ret); // fall through
	case 363:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) )
			return false;
		this->CNpcEvent::FuncGetPetEgg(parm[0].TokenData::GetNum());
		break; //FIXME: unintended?
	case 390: return this->CNpcEvent::FuncRefinery(parm[0].TokenData::GetNum(), ret);
	case 394: return this->CNpcEvent::FuncRelaodMobileEvent();
	case 395: return this->CNpcEvent::FuncSetTempTime(parm[0].TokenData::GetNum());
	case 396: return this->CNpcEvent::FuncElapseTempTime(parm[0].TokenData::GetNum(), ret);
	case 427: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncGetInventoryRemainCount(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), ret);
	case 450: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncSetQuest(parm[0].TokenData::GetNum());
	case 453: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncComplateQuest(parm[0].TokenData::GetNum());
	case 452: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncEraseQuest(parm[0].TokenData::GetNum());
	case 457: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncCheckQuest_Hunting(parm[0].TokenData::GetNum(), ret);
	case 458: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncCheckQuest_PlayTime(parm[0].TokenData::GetNum(), ret);
	case 456: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncIsBeginQuest(parm[0].TokenData::GetNum(), ret);
	case 451: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncChangQuest(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 454: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncCompleteQuest_Between(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 455: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncRecall_CompleteQuest(parm[0].TokenData::GetNum());
	case 460: return this->CNpcEvent::FuncPCDataMoveToPVP();
	case 461: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 5) ) ? false : this->CNpcEvent::FuncCallGuardian(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetStr(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum());
	case 465: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) ? false : this->CNpcEvent::FuncCampCode(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	case 466: return this->CNpcEvent::FuncGetCampCode(ret);
	case 467: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 5) ) ? false : this->CNpcEvent::FuncCallCampMob(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetStr(), parm[4].TokenData::GetStr());
	case 468: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncSetRP2(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	case 469: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) ? false : this->CNpcEvent::FuncMassSetRP2(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	case 470: return this->CNpcEvent::FuncPlayerToRP(parm[0].TokenData::GetNum());
	case 479: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncUpdateCampPoint(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 480: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncUpdateCampPoint(parm[0].TokenData::GetStr(), -parm[1].TokenData::GetNum());
	case 481: return this->CNpcEvent::FuncGetCampPoint(parm[0].TokenData::GetStr(), ret);
	case 482: return this->CNpcEvent::FuncResetCampPoint();
	case 459: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncGetLastSiegeMsg(parm[0].TokenData::GetStr(), ret);
	case 463: return this->CNpcEvent::FuncMdungeon_Subscription(parm[0].TokenData::GetStr(), ret);
	case 464: return this->CNpcEvent::FuncMdungeon_Enter(parm[0].TokenData::GetStr(), ret);
	case 477: return this->CNpcEvent::FuncMdungeon_List(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr(), parm[2].TokenData::GetStr());
	case 478: return this->CNpcEvent::FuncMdungeon_Destroy(parm[0].TokenData::GetStr());
	case 499: return this->CNpcEvent::FuncMdungeon_OpenState(parm[0].TokenData::GetNum(), ret);
	case 483: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncCheckSiegeTime(parm[0].TokenData::GetNum(), ret);
	case 489: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncMDungeon_NpcName(parm[0].TokenData::GetStr(), ret);
	case 488: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncMDungeon_MapName(parm[0].TokenData::GetStr(), ret);
	case 494: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 5) ) ? false : this->CNpcEvent::FuncMyMobSkillUse(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum());
	case 495: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncWhereMyMob_X(parm[0].TokenData::GetStr(), ret);
	case 496: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncWhereMyMob_Y(parm[0].TokenData::GetStr(), ret);
	case 497: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 7) ) ? false : this->CNpcEvent::FuncWideMobSkillUse(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum(), parm[5].TokenData::GetNum(), parm[6].TokenData::GetNum());
	case 498:
	{
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 8) )
			return false;

		MSG_TYPE7_EIGHTWORD data;
		data.data1 = parm[0].TokenData::GetNum();
		data.data2 = parm[1].TokenData::GetNum();
		data.data3 = parm[2].TokenData::GetNum();
		data.data4 = (int)parm[3].TokenData::GetStr();
		data.data5 = parm[4].TokenData::GetNum();
		data.data6 = parm[5].TokenData::GetNum();
		data.data7 = parm[6].TokenData::GetNum();
		data.data8 = parm[7].TokenData::GetNum();
		return this->CNpcEvent::FuncWideMobSkillUse2(&data);
	}
	case 503: return this->CNpcEvent::FuncIsBender(ret);
	case 507: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncGetNpcPosition(parm[0].TokenData::GetStr(), ret);
	case 511: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) ? false : this->CNpcEvent::FuncProgressBar(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	case 512: return this->CNpcEvent::FuncMercenaryCheck(ret);
	case 513: return this->CNpcEvent::FuncMercenaryType(ret);
	case 514: return this->CNpcEvent::FuncIsFreeServer(ret);
	case 528: return this->CNpcEvent::FuncCheckPartyJob(ret);
	case 529: return this->CNpcEvent::FuncClearBuff();
	case 530: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncCheckAlive(parm[0].TokenData::GetStr(), ret);
	case 532: return this->CNpcEvent::FuncKVMStartAliveCheck();
	case 533: return this->CNpcEvent::FuncPVPRankCheck(ret);
	case 536: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncKvm_Npc_Noti(parm[0].TokenData::GetStr());
	case 541: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 5) ) ? false : this->CNpcEvent::FuncGetItemSocket(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum());
	case 545: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 5) ) ? false : this->CNpcEvent::FuncGetNonSlotItemSocket(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum());
	case 547: return this->CNpcEvent::FuncGetMyMercenary(ret);
	case 548: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncErrorLog(parm[0].TokenData::GetStr());
	case 551: return this->CNpcEvent::FuncIsMadogear(ret);
	case 552: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncSetMadogear(parm[0].TokenData::GetStr());
	case 569: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) ? false : this->CNpcEvent::FuncBattlePlayModeNoti(parm[0].TokenData::GetNum());
	case 571: return ( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) ? false : this->CNpcEvent::FuncInterOther(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum());
	default:
		return this->CScriptEventHandler::OnFunc(func, parm, ret);
	}

	Trace("===========================================================================\n");
	this->CNpcEvent::TraceCurPos();
	Trace("CNpcEvent::DefaultFunc - unknown function type:%d\n", func);

	return false;
}


hook_method<bool (CNpcEvent::*)(int where, int type)> CNpcEvent::_FuncChangePallete(SERVER, "CNpcEvent::FuncChangePallete");
bool CNpcEvent::FuncChangePallete(int where, int type)
{
	return (this->*_FuncChangePallete)(where, type);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* zone, int mobId, char* mobName, int posX, int posY, int weight, int height, int num)> CNpcEvent::_FuncCallMonster(SERVER, "CNpcEvent::FuncCallMonster");
bool CNpcEvent::FuncCallMonster(char* zone, int mobId, char* mobName, int posX, int posY, int weight, int height, int num)
{
	return (this->*_FuncCallMonster)(zone, mobId, mobName, posX, posY, weight, height, num);

	int aitype = g_monParameter->CMonParameterMgr::GetMonsterType(mobId);
	if( aitype == -1 )
	{
		Trace("callmonster invalid mobID[%d] %s %s\n", mobId, zone, mobName);
		return false;
	}

	PACKET_NZ_NEWNPC packet;
	packet.npcType = aitype;
	packet.RegenMinTime = 1;
	packet.RegenMaxTime = 1;
	packet.xPos = posX;
	packet.yPos = posY;
	packet.NAID = 0;
	packet.xSize = weight;
	packet.ySize = height;
	packet.force = 1;
	packet.spriteType = mobId;
	packet.direction = 0;
	packet.RegenType = 0;
	SetMapName(packet.mapName, zone);
	memcpy(packet.NPCName, mobName, sizeof(packet.NPCName));
	packet.NPCName[sizeof(packet.NPCName)-1] = '\0';

	for( int i = 0; i < num; ++i )
		g_characterMgr->CCharacterMgr::AddNPC(&packet, m_npcId);

	Trace("callmonster %s %d %s %d %d parent:%d\n", zone, mobId, mobName, posX, posY, m_npcId);
	return true;
}


hook_method<bool (CNpcEvent::*)(int skillId, int level, int state, int percent)> CNpcEvent::_FuncAddSkill(SERVER, "CNpcEvent::FuncAddSkill");
bool CNpcEvent::FuncAddSkill(int skillId, int level, int state, int percent)
{
	return (this->*_FuncAddSkill)(skillId, level, state, percent);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* str, char* eventStr)> CNpcEvent::_FuncOtherNpcCmd(SERVER, "CNpcEvent::FuncOtherNpcCmd");
bool CNpcEvent::FuncOtherNpcCmd(const char* str, char* eventStr)
{
	return (this->*_FuncOtherNpcCmd)(str, eventStr);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int varSlot, char* str)> CNpcEvent::_FuncStrLocalVar(SERVER, "CNpcEvent::FuncStrLocalVar");
bool CNpcEvent::FuncStrLocalVar(int varSlot, char* str)
{
	return (this->*_FuncStrLocalVar)(varSlot, str);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int no)> CNpcEvent::_FuncSetArenaEventSize(SERVER, "?FuncSetArenaEventSize@CNpcEvent@@AAE_NH@Z");
bool CNpcEvent::FuncSetArenaEventSize(int no)
{
	return (this->*_FuncSetArenaEventSize)(no);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncGetArenaEventSize2(SERVER, "?FuncGetArenaEventSize@CNpcEvent@@AAE_NAAUTokenData@@@Z");
bool CNpcEvent::FuncGetArenaEventSize(TokenData& ret)
{
	return (this->*_FuncGetArenaEventSize2)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* title, int num)> CNpcEvent::_FuncMakeWaitingRoom(SERVER, "CNpcEvent::FuncMakeWaitingRoom");
bool CNpcEvent::FuncMakeWaitingRoom(char* title, int num)
{
	return (this->*_FuncMakeWaitingRoom)(title, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncEnableArena(SERVER, "CNpcEvent::FuncEnableArena");
bool CNpcEvent::FuncEnableArena(void)
{
	return (this->*_FuncEnableArena)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncDisableArena(SERVER, "CNpcEvent::FuncDisableArena");
bool CNpcEvent::FuncDisableArena(void)
{
	return (this->*_FuncDisableArena)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* str, int posx, int posy)> CNpcEvent::_FuncWarpWaitingPcToArena(SERVER, "CNpcEvent::FuncWarpWaitingPcToArena");
bool CNpcEvent::FuncWarpWaitingPcToArena(char* str, int posx, int posy)
{
	return (this->*_FuncWarpWaitingPcToArena)(str, posx, posy);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncResetMyMob(SERVER, "CNpcEvent::FuncResetMyMob");
bool CNpcEvent::FuncResetMyMob(void)
{
	return (this->*_FuncResetMyMob)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* str, int posx, int posy)> CNpcEvent::_FuncWarpAllPcInTheMap(SERVER, "CNpcEvent::FuncWarpAllPcInTheMap");
bool CNpcEvent::FuncWarpAllPcInTheMap(char* str, int posx, int posy)
{
	return (this->*_FuncWarpAllPcInTheMap)(str, posx, posy);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* str)> CNpcEvent::_FuncBroadcastInTheMap(SERVER, "CNpcEvent::FuncBroadcastInTheMap");
bool CNpcEvent::FuncBroadcastInTheMap(char* str)
{
	return (this->*_FuncBroadcastInTheMap)(str);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* str, int num)> CNpcEvent::_FuncAddNpcTimer(SERVER, "CNpcEvent::FuncAddNpcTimer");
bool CNpcEvent::FuncAddNpcTimer(char* str, int num)
{
	return (this->*_FuncAddNpcTimer)(str, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* str, int num)> CNpcEvent::_FuncSubNpcTimer(SERVER, "CNpcEvent::FuncSubNpcTimer");
bool CNpcEvent::FuncSubNpcTimer(char* str, int num)
{
	return (this->*_FuncSubNpcTimer)(str, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* str)> CNpcEvent::_FuncEnableNpc(SERVER, "CNpcEvent::FuncEnableNpc");
bool CNpcEvent::FuncEnableNpc(char* str)
{
	return (this->*_FuncEnableNpc)(str);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* str)> CNpcEvent::_FuncDisableNpc(SERVER, "CNpcEvent::FuncDisableNpc");
bool CNpcEvent::FuncDisableNpc(char* str)
{
	return (this->*_FuncDisableNpc)(str);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* zone, int npcType, char* npcName, int spriteType, int posX, int posY)> CNpcEvent::_FuncCallNpc(SERVER, "CNpcEvent::FuncCallNpc");
bool CNpcEvent::FuncCallNpc(char* zone, int npcType, char* npcName, int spriteType, int posX, int posY)
{
	return (this->*_FuncCallNpc)(zone, npcType, npcName, spriteType, posX, posY);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int money)> CNpcEvent::_FuncSetFeeZeny(SERVER, "CNpcEvent::FuncSetFeeZeny");
bool CNpcEvent::FuncSetFeeZeny(int money)
{
	return (this->*_FuncSetFeeZeny)(money);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, int num)> CNpcEvent::_FuncSetFeeItem(SERVER, "CNpcEvent::FuncSetFeeItem");
bool CNpcEvent::FuncSetFeeItem(int item, int num)
{
	return (this->*_FuncSetFeeItem)(item, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int lowlevel, int highlevel)> CNpcEvent::_FuncSetReqLevel(SERVER, "CNpcEvent::FuncSetReqLevel");
bool CNpcEvent::FuncSetReqLevel(int lowlevel, int highlevel)
{
	return (this->*_FuncSetReqLevel)(lowlevel, highlevel);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int job)> CNpcEvent::_FuncSetTexJob(SERVER, "CNpcEvent::FuncSetTexJob");
bool CNpcEvent::FuncSetTexJob(int job)
{
	return (this->*_FuncSetTexJob)(job);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncDisableItemMove(SERVER, "CNpcEvent::FuncDisableItemMove");
bool CNpcEvent::FuncDisableItemMove(void)
{
	return (this->*_FuncDisableItemMove)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncEnableItemMove(SERVER, "CNpcEvent::FuncEnableItemMove");
bool CNpcEvent::FuncEnableItemMove(void)
{
	return (this->*_FuncEnableItemMove)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part)> CNpcEvent::_FuncSuccessRefItem(SERVER, "CNpcEvent::FuncSuccessRefItem");
bool CNpcEvent::FuncSuccessRefItem(int part)
{
	return (this->*_FuncSuccessRefItem)(part);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part)> CNpcEvent::_FuncFailedRefItem(SERVER, "CNpcEvent::FuncFailedRefItem");
bool CNpcEvent::FuncFailedRefItem(int part)
{
	return (this->*_FuncFailedRefItem)(part);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int effectenum)> CNpcEvent::_FuncSetEffectStatus(SERVER, "CNpcEvent::FuncSetEffectStatus");
bool CNpcEvent::FuncSetEffectStatus(int effectenum)
{
	return (this->*_FuncSetEffectStatus)(effectenum);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncResetStat(SERVER, "CNpcEvent::FuncResetStat");
bool CNpcEvent::FuncResetStat(void)
{
	return (this->*_FuncResetStat)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* str)> CNpcEvent::_FuncTrace(SERVER, "CNpcEvent::FuncTrace");
bool CNpcEvent::FuncTrace(char* str)
{
	return (this->*_FuncTrace)(str);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int p, TokenData& ret)> CNpcEvent::_FuncVar(SERVER, "CNpcEvent::FuncVar");
bool CNpcEvent::FuncVar(int p, TokenData& ret)
{
	return (this->*_FuncVar)(p, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* varName, TokenData& ret)> CNpcEvent::_FuncLV(SERVER, "CNpcEvent::FuncLV");
bool CNpcEvent::FuncLV(char* varName, TokenData& ret)
{
	return (this->*_FuncLV)(varName, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* name, int p, TokenData& ret)> CNpcEvent::_FuncNpcV(SERVER, "CNpcEvent::FuncNpcV");
bool CNpcEvent::FuncNpcV(char* name, int p, TokenData& ret)
{
	return (this->*_FuncNpcV)(name, p, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* varName, int val)> CNpcEvent::_FuncIncLocalVar(SERVER, "CNpcEvent::FuncIncLocalVar");
bool CNpcEvent::FuncIncLocalVar(char* varName, int val)
{
	return (this->*_FuncIncLocalVar)(varName, val);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* varName, int val)> CNpcEvent::_FuncDecLocalVar(SERVER, "CNpcEvent::FuncDecLocalVar");
bool CNpcEvent::FuncDecLocalVar(char* varName, int val)
{
	return (this->*_FuncDecLocalVar)(varName, val);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* varName, int val)> CNpcEvent::_FuncSetLocalVar(SERVER, "CNpcEvent::FuncSetLocalVar");
bool CNpcEvent::FuncSetLocalVar(char* varName, int val)
{
	return (this->*_FuncSetLocalVar)(varName, val);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part, TokenData& ret)> CNpcEvent::_FuncGetEquipIsIdentify(SERVER, "CNpcEvent::FuncGetEquipIsIdentify");
bool CNpcEvent::FuncGetEquipIsIdentify(int part, TokenData& ret)
{
	return (this->*_FuncGetEquipIsIdentify)(part, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part, TokenData& ret)> CNpcEvent::_FuncGetEquipRefineryCnt(SERVER, "CNpcEvent::FuncGetEquipRefineryCnt");
bool CNpcEvent::FuncGetEquipRefineryCnt(int part, TokenData& ret)
{
	return (this->*_FuncGetEquipRefineryCnt)(part, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part, TokenData& ret)> CNpcEvent::_FuncGetEquipRefineryCost(SERVER, "CNpcEvent::FuncGetEquipRefineryCost");
bool CNpcEvent::FuncGetEquipRefineryCost(int part, TokenData& ret)
{
	return (this->*_FuncGetEquipRefineryCost)(part, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part, TokenData& ret)> CNpcEvent::_FuncGetEquipName(SERVER, "CNpcEvent::FuncGetEquipName");
bool CNpcEvent::FuncGetEquipName(int part, TokenData& ret)
{
	return (this->*_FuncGetEquipName)(part, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part, TokenData& ret)> CNpcEvent::_FuncGetEquipItemIdx(SERVER, "CNpcEvent::FuncGetEquipItemIdx");
bool CNpcEvent::FuncGetEquipItemIdx(int part, TokenData& ret)
{
	return (this->*_FuncGetEquipItemIdx)(part, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part, TokenData& ret)> CNpcEvent::_FuncGetEquipWeaponLv(SERVER, "CNpcEvent::FuncGetEquipWeaponLv");
bool CNpcEvent::FuncGetEquipWeaponLv(int part, TokenData& ret)
{
	return (this->*_FuncGetEquipWeaponLv)(part, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part, TokenData& ret)> CNpcEvent::_FuncGetEquipIsEnableRef(SERVER, "CNpcEvent::FuncGetEquipIsEnableRef");
bool CNpcEvent::FuncGetEquipIsEnableRef(int part, TokenData& ret)
{
	return (this->*_FuncGetEquipIsEnableRef)(part, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncInitTimer(SERVER, "CNpcEvent::FuncInitTimer");
bool CNpcEvent::FuncInitTimer(void)
{
	return (this->*_FuncInitTimer)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(int act, mystd::deque<TokenData>& parm)> CNpcEvent::_FuncLabel(SERVER, "CNpcEvent::FuncLabel");
bool CNpcEvent::FuncLabel(int act, mystd::deque<TokenData>& parm)
{
	return (this->*_FuncLabel)(act, parm);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item)> CNpcEvent::_FuncRegSellItem(SERVER, "CNpcEvent::FuncRegSellItem");
bool CNpcEvent::FuncRegSellItem(int item)
{
	return (this->*_FuncRegSellItem)(item);

	CNPC2ZMsg msg;
	msg.CMsg::SetMsgID(54);
	msg.par1 = 0;
	msg.par2 = item;
	g_characterMgr->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);
	Trace("register sell item %d\n", item);
	return true;
}


hook_method<bool (CNpcEvent::*)(int id, NpcSvrNpcInfo* npcInfo)> CNpcEvent::_FuncMob(SERVER, "CNpcEvent::FuncMob");
bool CNpcEvent::FuncMob(int id, NpcSvrNpcInfo* npcInfo)
{
	return (this->*_FuncMob)(id, npcInfo);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int id, int x, int y, int type, const char* color)> CNpcEvent::_FuncCompass(SERVER, "CNpcEvent::FuncCompass");
bool CNpcEvent::FuncCompass(int id, int x, int y, int type, const char* color)
{
	return (this->*_FuncCompass)(id, x, y, type, color);

	//TODO
}


hook_method<bool (CNpcEvent::*)(NpcSvrNpcInfo* npcInfo, bool isNpc)> CNpcEvent::_FuncNpc(SERVER, "CNpcEvent::FuncNpc");
bool CNpcEvent::FuncNpc(NpcSvrNpcInfo* npcInfo, bool isNpc) // line 3194
{
	return (this->*_FuncNpc)(npcInfo, isNpc);

	return( this->CNpcEvent::FuncNpc2(npcInfo, isNpc) > 0 );
}


hook_method<unsigned long (CNpcEvent::*)(NpcSvrNpcInfo* npcInfo, bool isNpc)> CNpcEvent::_FuncNpc2(SERVER, "CNpcEvent::FuncNpc2");
unsigned long CNpcEvent::FuncNpc2(NpcSvrNpcInfo* npcInfo, bool isNpc) // line 3143
{
	return (this->*_FuncNpc2)(npcInfo, isNpc);

	char mapName[256];
	SetMapName(mapName, npcInfo->zone);

	int AID = g_npcSvr->GetNpcMgr()->CNpcMgr::GetNewID();
	if( AID == 0 )
	{
		Trace("FuncNpc: npc over aid\n");
		return 0;
	}

	TrimLeft(mapName);
	TrimRight(mapName);

	if( g_mapInfo->CMapInfo::GetServerID(mapName) != GetLocalServerID() )
	{
		m_curInitNpc = 0;
		return 1;
	}

	CNpc* npc = g_npcSvr->GetNpcMgr()->CNpcMgr::Add(AID);
	if( npc == NULL )
	{
		Trace("FuncNpc: NpcMgr's add() failed. addr: hex[%x] dec[%d]\n", m_interpreter.CInterpreter::GetCurPos(), m_interpreter.CInterpreter::GetCurPos());
		return 0;
	}

	npc->CNpc::SetInfo(AID, npcInfo);
	npc->SetOnInit(true);
	m_curInitNpc = AID;

	if( !this->CScriptEventHandler::AddNpc(AID, mapName, npcInfo) )
	{
		char buf[1024];
		memset(buf, 0, sizeof(buf));
		sprintf(buf, "CNpcEvent::FuncNpc, Can't Not AddNpc, MapName[%s], NpcName[%s], Pos[%d, %d]", mapName, npcInfo->name, npcInfo->x, npcInfo->y);
		g_errorLogs->CErrorLog::CriticalErrorLog(buf, 3182, ".\\NpcServer\\NpcEvent.Cpp");
	}

	return AID;
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncInput(SERVER, "CNpcEvent::FuncInput");
bool CNpcEvent::FuncInput(TokenData& ret)
{
	return (this->*_FuncInput)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int min, int max)> CNpcEvent::_FuncDlgWrite(SERVER, "CNpcEvent::FuncDlgWrite");
bool CNpcEvent::FuncDlgWrite(int min, int max)
{
	return (this->*_FuncDlgWrite)(min, max);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncNude(SERVER, "CNpcEvent::FuncNude");
bool CNpcEvent::FuncNude(void)
{
	return (this->*_FuncNude)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(int flag)> CNpcEvent::_FuncCart(SERVER, "CNpcEvent::FuncCart");
bool CNpcEvent::FuncCart(int flag)
{
	return (this->*_FuncCart)(flag);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncStore(SERVER, "CNpcEvent::FuncStore");
bool CNpcEvent::FuncStore(void)
{
	return (this->*_FuncStore)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* str, bool bExtra)> CNpcEvent::_FuncMenu(SERVER, "CNpcEvent::FuncMenu");
bool CNpcEvent::FuncMenu(const char* str, bool bExtra)
{
	return (this->*_FuncMenu)(str, bExtra);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int job)> CNpcEvent::_FuncJobChange(SERVER, "CNpcEvent::FuncJobChange");
bool CNpcEvent::FuncJobChange(int job)
{
	return (this->*_FuncJobChange)(job);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int amount)> CNpcEvent::_FuncGetMoney(SERVER, "CNpcEvent::FuncGetMoney");
bool CNpcEvent::FuncGetMoney(int amount)
{
	return (this->*_FuncGetMoney)(amount);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int amount, TokenData& ret)> CNpcEvent::_FuncDropMoney(SERVER, "CNpcEvent::FuncDropMoney");
bool CNpcEvent::FuncDropMoney(int amount, TokenData& ret)
{
	return (this->*_FuncDropMoney)(amount, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, int num)> CNpcEvent::_FuncSetItem(SERVER, "CNpcEvent::FuncSetItem");
bool CNpcEvent::FuncSetItem(int item, int num)
{
	return (this->*_FuncSetItem)(item, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, int num)> CNpcEvent::_FuncGetItem(SERVER, "CNpcEvent::FuncGetItem");
bool CNpcEvent::FuncGetItem(int item, int num)
{
	return (this->*_FuncGetItem)(item, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, int num)> CNpcEvent::_FuncDropItem(SERVER, "CNpcEvent::FuncDropItem");
bool CNpcEvent::FuncDropItem(int item, int num)
{
	return (this->*_FuncDropItem)(item, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int srcItem, int srcNum, int destItem, int destNum)> CNpcEvent::_FuncExchangeItem(SERVER, "CNpcEvent::FuncExchangeItem");
bool CNpcEvent::FuncExchangeItem(int srcItem, int srcNum, int destItem, int destNum)
{
	return (this->*_FuncExchangeItem)(srcItem, srcNum, destItem, destNum);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int var, int num)> CNpcEvent::_FuncInc(SERVER, "CNpcEvent::FuncInc");
bool CNpcEvent::FuncInc(int var, int num)
{
	return (this->*_FuncInc)(var, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int var, int num)> CNpcEvent::_FuncDec(SERVER, "CNpcEvent::FuncDec");
bool CNpcEvent::FuncDec(int var, int num)
{
	return (this->*_FuncDec)(var, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int var, int percent)> CNpcEvent::_FuncHeal(SERVER, "CNpcEvent::FuncHeal");
bool CNpcEvent::FuncHeal(int var, int percent) // line 2571
{
	return (this->*_FuncHeal)(var, percent);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int numerator, int denominator, TokenData& ret)> CNpcEvent::_FuncLot(SERVER, "CNpcEvent::FuncLot");
bool CNpcEvent::FuncLot(int numerator, int denominator, TokenData& ret)
{
	return (this->*_FuncLot)(numerator, denominator, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* pszMapName, TokenData& ret)> CNpcEvent::_FuncGetPcCount(SERVER, "CNpcEvent::FuncGetPcCount");
bool CNpcEvent::FuncGetPcCount(const char* pszMapName, TokenData& ret)
{
	return (this->*_FuncGetPcCount)(pszMapName, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncError(SERVER, "CNpcEvent::FuncError");
bool CNpcEvent::FuncError(TokenData& ret)
{
	return (this->*_FuncError)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* zone, int x, int y)> CNpcEvent::_FuncCheckPoint(SERVER, "CNpcEvent::FuncCheckPoint");
bool CNpcEvent::FuncCheckPoint(const char* zone, int x, int y)
{
	return (this->*_FuncCheckPoint)(zone, x, y);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int digit)> CNpcEvent::_FuncShowDigit(SERVER, "CNpcEvent::FuncShowDigit");
bool CNpcEvent::FuncShowDigit(int digit)
{
	return (this->*_FuncShowDigit)(digit);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int skill, int level)> CNpcEvent::_FuncEnableSkill(SERVER, "CNpcEvent::FuncEnableSkill");
bool CNpcEvent::FuncEnableSkill(int skill, int level)
{
	return (this->*_FuncEnableSkill)(skill, level);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int skill)> CNpcEvent::_FuncDisableSkill(SERVER, "CNpcEvent::FuncDisableSkill");
bool CNpcEvent::FuncDisableSkill(int skill)
{
	return (this->*_FuncDisableSkill)(skill);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int type, int value)> CNpcEvent::_FuncSetParameter(SERVER, "CNpcEvent::FuncSetParameter");
bool CNpcEvent::FuncSetParameter(int type, int value)
{
	return (this->*_FuncSetParameter)(type, value);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* name, int emotion)> CNpcEvent::_FuncEmotion(SERVER, "CNpcEvent::FuncEmotion");
bool CNpcEvent::FuncEmotion(char* name, int emotion)
{
	return (this->*_FuncEmotion)(name, emotion);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* name, int sprite)> CNpcEvent::_FuncChangeSpr(SERVER, "CNpcEvent::FuncChangeSpr");
bool CNpcEvent::FuncChangeSpr(char* name, int sprite)
{
	return (this->*_FuncChangeSpr)(name, sprite);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, TokenData& ret)> CNpcEvent::_FuncGetEquipCount(SERVER, "CNpcEvent::FuncGetEquipCount");
bool CNpcEvent::FuncGetEquipCount(int item, TokenData& ret)
{
	return (this->*_FuncGetEquipCount)(item, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* mapName, int n, TokenData& ret)> CNpcEvent::_FuncAgitGet(SERVER, "CNpcEvent::FuncAgitGet");
bool CNpcEvent::FuncAgitGet(char* mapName, int n, TokenData& ret)
{
	return (this->*_FuncAgitGet)(mapName, n, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int n, int data)> CNpcEvent::_FuncAgitSet(SERVER, "CNpcEvent::FuncAgitSet");
bool CNpcEvent::FuncAgitSet(int n, int data)
{
	return (this->*_FuncAgitSet)(n, data);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int func, int parm1, int parm2)> CNpcEvent::_FuncAgitFunc(SERVER, "CNpcEvent::FuncAgitFunc");
bool CNpcEvent::FuncAgitFunc(int func, int parm1, int parm2)
{
	return (this->*_FuncAgitFunc)(func, parm1, parm2);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int guardian, int n, TokenData& ret)> CNpcEvent::_FuncAgitNpcGet(SERVER, "CNpcEvent::FuncAgitNpcGet");
bool CNpcEvent::FuncAgitNpcGet(int guardian, int n, TokenData& ret)
{
	return (this->*_FuncAgitNpcGet)(guardian, n, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int guardian, int n, int data)> CNpcEvent::_FuncAgitNpcSet(SERVER, "CNpcEvent::FuncAgitNpcSet");
bool CNpcEvent::FuncAgitNpcSet(int guardian, int n, int data)
{
	return (this->*_FuncAgitNpcSet)(guardian, n, data);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int guildID, TokenData& ret)> CNpcEvent::_FuncIsGuildMaster(SERVER, "CNpcEvent::FuncIsGuildMaster");
bool CNpcEvent::FuncIsGuildMaster(int guildID, TokenData& ret)
{
	return (this->*_FuncIsGuildMaster)(guildID, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* name)> CNpcEvent::_FuncAgitRegister(SERVER, "CNpcEvent::FuncAgitRegister");
bool CNpcEvent::FuncAgitRegister(char* name)
{
	return (this->*_FuncAgitRegister)(name);

	//TODO
}


hook_method<bool (CNpcEvent::*)(bool isServerSide, char* color, int fontType, int fontSize, int fontAlign, int fontY, char* str)> CNpcEvent::_FuncBroadcast(SERVER, "CNpcEvent::FuncBroadcast");
bool CNpcEvent::FuncBroadcast(bool isServerSide, char* color, int fontType, int fontSize, int fontAlign, int fontY, char* str)
{
	return (this->*_FuncBroadcast)(isServerSide, color, fontType, fontSize, fontAlign, fontY, str);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* filename, int range, int act, int term)> CNpcEvent::_FuncSound(SERVER, "CNpcEvent::FuncSound");
bool CNpcEvent::FuncSound(char* filename, int range, int act, int term)
{
	return (this->*_FuncSound)(filename, range, act, term);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncGetDamagedItemNum(SERVER, "CNpcEvent::FuncGetDamagedItemNum");
bool CNpcEvent::FuncGetDamagedItemNum(TokenData& ret)
{
	return (this->*_FuncGetDamagedItemNum)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncRepairDamagedItem(SERVER, "CNpcEvent::FuncRepairDamagedItem");
bool CNpcEvent::FuncRepairDamagedItem(void)
{
	return (this->*_FuncRepairDamagedItem)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item)> CNpcEvent::_FuncSavePPL(SERVER, "CNpcEvent::FuncSavePPL");
bool CNpcEvent::FuncSavePPL(int item)
{
	return (this->*_FuncSavePPL)(item);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* name)> CNpcEvent::_FuncAgitEmblemFlag(SERVER, "CNpcEvent::FuncAgitEmblemFlag");
bool CNpcEvent::FuncAgitEmblemFlag(char* name)
{
	return (this->*_FuncAgitEmblemFlag)(name);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int amount)> CNpcEvent::_FuncChangeEXP(SERVER, "CNpcEvent::FuncChangeEXP");
bool CNpcEvent::FuncChangeEXP(int amount)
{
	return (this->*_FuncChangeEXP)(amount);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncServerTime(SERVER, "CNpcEvent::FuncServerTime");
bool CNpcEvent::FuncServerTime(TokenData& ret)
{
	return (this->*_FuncServerTime)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int index, TokenData& ret)> CNpcEvent::_FuncGetLocalVarName(SERVER, "CNpcEvent::FuncGetLocalVarName");
bool CNpcEvent::FuncGetLocalVarName(int index, TokenData& ret)
{
	return (this->*_FuncGetLocalVarName)(index, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncGetMarried(SERVER, "CNpcEvent::FuncGetMarried");
bool CNpcEvent::FuncGetMarried(TokenData& ret)
{
	return (this->*_FuncGetMarried)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncGetGuildName(SERVER, "CNpcEvent::FuncGetGuildName");
bool CNpcEvent::FuncGetGuildName(TokenData& ret)
{
	return (this->*_FuncGetGuildName)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int time)> CNpcEvent::_FuncCountDown(SERVER, "CNpcEvent::FuncCountDown");
bool CNpcEvent::FuncCountDown(int time)
{
	return (this->*_FuncCountDown)(time);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int Range, TokenData& ret)> CNpcEvent::_FuncGetNeighborPcNumber(SERVER, "CNpcEvent::FuncGetNeighborPcNumber");
bool CNpcEvent::FuncGetNeighborPcNumber(int Range, TokenData& ret)
{
	return (this->*_FuncGetNeighborPcNumber)(Range, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, int num)> CNpcEvent::_FuncGetNamedItem(SERVER, "CNpcEvent::FuncGetNamedItem");
bool CNpcEvent::FuncGetNamedItem(int item, int num)
{
	return (this->*_FuncGetNamedItem)(item, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, int num)> CNpcEvent::_FuncDropNamedItem(SERVER, "CNpcEvent::FuncDropNamedItem");
bool CNpcEvent::FuncDropNamedItem(int item, int num)
{
	return (this->*_FuncDropNamedItem)(item, num);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, TokenData& ret)> CNpcEvent::_FuncGetCountOfMyNameItem(SERVER, "CNpcEvent::FuncGetCountOfMyNameItem");
bool CNpcEvent::FuncGetCountOfMyNameItem(int item, TokenData& ret)
{
	return (this->*_FuncGetCountOfMyNameItem)(item, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int hair)> CNpcEvent::_FuncChangeHairStyle(SERVER, "CNpcEvent::FuncChangeHairStyle");
bool CNpcEvent::FuncChangeHairStyle(int hair)
{
	return (this->*_FuncChangeHairStyle)(hair);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* name, int effect)> CNpcEvent::_FuncShowEffect(SERVER, "CNpcEvent::FuncShowEffect");
bool CNpcEvent::FuncShowEffect(const char* name, int effect)
{
	return (this->*_FuncShowEffect)(name, effect);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int flag)> CNpcEvent::_FuncFalcon(SERVER, "CNpcEvent::FuncFalcon");
bool CNpcEvent::FuncFalcon(int flag)
{
	return (this->*_FuncFalcon)(flag);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int flag)> CNpcEvent::_FuncPeco(SERVER, "CNpcEvent::FuncPeco");
bool CNpcEvent::FuncPeco(int flag)
{
	return (this->*_FuncPeco)(flag);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int zeny, TokenData& ret)> CNpcEvent::_FuncCheckMaxZeny(SERVER, "CNpcEvent::FuncCheckMaxZeny");
bool CNpcEvent::FuncCheckMaxZeny(int zeny, TokenData& ret)
{
	return (this->*_FuncCheckMaxZeny)(zeny, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, int count, TokenData& ret)> CNpcEvent::_FuncCheckMaxCount(SERVER, "CNpcEvent::FuncCheckMaxCount");
bool CNpcEvent::FuncCheckMaxCount(int item, int count, TokenData& ret)
{
	return (this->*_FuncCheckMaxCount)(item, count, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, int count, TokenData& ret)> CNpcEvent::_FuncCheckMaxWeight(SERVER, "CNpcEvent::FuncCheckMaxWeight");
bool CNpcEvent::FuncCheckMaxWeight(int item, int count, TokenData& ret)
{
	return (this->*_FuncCheckMaxWeight)(item, count, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int index, TokenData& ret)> CNpcEvent::_FuncMGetEventItem(SERVER, "CNpcEvent::FuncMGetEventItem");
bool CNpcEvent::FuncMGetEventItem(int index, TokenData& ret)
{
	return (this->*_FuncMGetEventItem)(index, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int index, TokenData& ret)> CNpcEvent::_FuncMGetEventZeny(SERVER, "CNpcEvent::FuncMGetEventZeny");
bool CNpcEvent::FuncMGetEventZeny(int index, TokenData& ret)
{
	return (this->*_FuncMGetEventZeny)(index, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int index, TokenData& ret)> CNpcEvent::_FuncMGetEventItemName(SERVER, "CNpcEvent::FuncMGetEventItemName");
bool CNpcEvent::FuncMGetEventItemName(int index, TokenData& ret)
{
	return (this->*_FuncMGetEventItemName)(index, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int index, TokenData& ret)> CNpcEvent::_FuncMGetEventZenyName(SERVER, "CNpcEvent::FuncMGetEventZenyName");
bool CNpcEvent::FuncMGetEventZenyName(int index, TokenData& ret)
{
	return (this->*_FuncMGetEventZenyName)(index, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* guildname)> CNpcEvent::_FuncCreateGuild(SERVER, "CNpcEvent::FuncCreateGuild");
bool CNpcEvent::FuncCreateGuild(char* guildname)
{
	return (this->*_FuncCreateGuild)(guildname);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* name, int value)> CNpcEvent::_FuncCreateGlobalVar(SERVER, "CNpcEvent::FuncCreateGlobalVar");
bool CNpcEvent::FuncCreateGlobalVar(const char* name, int value)
{
	return (this->*_FuncCreateGlobalVar)(name, value);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* name, TokenData& ret)> CNpcEvent::_FuncGetGlobalVar(SERVER, "CNpcEvent::FuncGetGlobalVar");
bool CNpcEvent::FuncGetGlobalVar(const char* name, TokenData& ret)
{
	return (this->*_FuncGetGlobalVar)(name, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* name, int value)> CNpcEvent::_FuncSetGlobalVar(SERVER, "CNpcEvent::FuncSetGlobalVar");
bool CNpcEvent::FuncSetGlobalVar(const char* name, int value)
{
	return (this->*_FuncSetGlobalVar)(name, value);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* str1, const char* str2, TokenData& ret)> CNpcEvent::_FuncStrCmp(SERVER, "CNpcEvent::FuncStrCmp");
bool CNpcEvent::FuncStrCmp(const char* str1, const char* str2, TokenData& ret)
{
	return (this->*_FuncStrCmp)(str1, str2, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* str1, const char* str2, TokenData& ret)> CNpcEvent::_FuncStrStr(SERVER, "CNpcEvent::FuncStrStr");
bool CNpcEvent::FuncStrStr(const char* str1, const char* str2, TokenData& ret)
{
	return (this->*_FuncStrStr)(str1, str2, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncUpgradeGuildLevel(SERVER, "CNpcEvent::FuncUpgradeGuildLevel");
bool CNpcEvent::FuncUpgradeGuildLevel(void)
{
	return (this->*_FuncUpgradeGuildLevel)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* name, char* value)> CNpcEvent::_FuncCreateGlobalStr(SERVER, "CNpcEvent::FuncCreateGlobalStr");
bool CNpcEvent::FuncCreateGlobalStr(const char* name, char* value)
{
	return (this->*_FuncCreateGlobalStr)(name, value);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* name, TokenData& ret)> CNpcEvent::_FuncGetGlobalStr(SERVER, "CNpcEvent::FuncGetGlobalStr");
bool CNpcEvent::FuncGetGlobalStr(const char* name, TokenData& ret)
{
	return (this->*_FuncGetGlobalStr)(name, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* name, char* value)> CNpcEvent::_FuncSetGlobalStr(SERVER, "CNpcEvent::FuncSetGlobalStr");
bool CNpcEvent::FuncSetGlobalStr(const char* name, char* value)
{
	return (this->*_FuncSetGlobalStr)(name, value);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncDivorce(SERVER, "CNpcEvent::FuncDivorce");
bool CNpcEvent::FuncDivorce(void)
{
	return (this->*_FuncDivorce)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncPEventGet(SERVER, "CNpcEvent::FuncPEventGet");
bool CNpcEvent::FuncPEventGet(TokenData& ret)
{
	return (this->*_FuncPEventGet)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int addPoint, TokenData& ret)> CNpcEvent::_FuncPEventAdd(SERVER, "CNpcEvent::FuncPEventAdd");
bool CNpcEvent::FuncPEventAdd(int addPoint, TokenData& ret)
{
	return (this->*_FuncPEventAdd)(addPoint, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int delPoint, TokenData& ret)> CNpcEvent::_FuncPEventDel(SERVER, "CNpcEvent::FuncPEventDel");
bool CNpcEvent::FuncPEventDel(int delPoint, TokenData& ret)
{
	return (this->*_FuncPEventDel)(delPoint, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncPCDataMoveToPVP(SERVER, "CNpcEvent::FuncPCDataMoveToPVP");
bool CNpcEvent::FuncPCDataMoveToPVP(void)
{
	return (this->*_FuncPCDataMoveToPVP)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(int index, TokenData& ret)> CNpcEvent::_FuncMGetEventItemID(SERVER, "CNpcEvent::FuncMGetEventItemID");
bool CNpcEvent::FuncMGetEventItemID(int index, TokenData& ret)
{
	return (this->*_FuncMGetEventItemID)(index, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int jobexp)> CNpcEvent::_FuncGetJobExp(SERVER, "CNpcEvent::FuncGetJobExp");
bool CNpcEvent::FuncGetJobExp(int jobexp)
{
	return (this->*_FuncGetJobExp)(jobexp);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int jobexp)> CNpcEvent::_FuncDropJobExp(SERVER, "CNpcEvent::FuncDropJobExp");
bool CNpcEvent::FuncDropJobExp(int jobexp)
{
	return (this->*_FuncDropJobExp)(jobexp);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int SKID, TokenData& ret)> CNpcEvent::_FuncChkSkill(SERVER, "CNpcEvent::FuncChkSkill");
bool CNpcEvent::FuncChkSkill(int SKID, TokenData& ret)
{
	return (this->*_FuncChkSkill)(SKID, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int bodystate, int time)> CNpcEvent::_FuncGetBodyState(SERVER, "CNpcEvent::FuncGetBodyState");
bool CNpcEvent::FuncGetBodyState(int bodystate, int time)
{
	return (this->*_FuncGetBodyState)(bodystate, time);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int healthstate, int time)> CNpcEvent::_FuncGetHealthState(SERVER, "CNpcEvent::FuncGetHealthState");
bool CNpcEvent::FuncGetHealthState(int healthstate, int time)
{
	return (this->*_FuncGetHealthState)(healthstate, time);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int SKID, int skLevel, int sppoint, int clevel)> CNpcEvent::_FuncUseSkillToPC(SERVER, "CNpcEvent::FuncUseSkillToPC");
bool CNpcEvent::FuncUseSkillToPC(int SKID, int skLevel, int sppoint, int clevel)
{
	return (this->*_FuncUseSkillToPC)(SKID, skLevel, sppoint, clevel);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncIsBaby(SERVER, "CNpcEvent::FuncIsBaby");
bool CNpcEvent::FuncIsBaby(TokenData& ret)
{
	return (this->*_FuncIsBaby)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int index, TokenData& ret)> CNpcEvent::_FuncGetLotto(SERVER, "CNpcEvent::FuncGetLotto");
bool CNpcEvent::FuncGetLotto(int index, TokenData& ret)
{
	return (this->*_FuncGetLotto)(index, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int n1, int n2, int n3, int n4, int n5, int n6)> CNpcEvent::_FuncSetLotto(SERVER, "CNpcEvent::FuncSetLotto");
bool CNpcEvent::FuncSetLotto(int n1, int n2, int n3, int n4, int n5, int n6)
{
	return (this->*_FuncSetLotto)(n1, n2, n3, n4, n5, n6);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncInitLotto(SERVER, "CNpcEvent::FuncInitLotto");
bool CNpcEvent::FuncInitLotto(void)
{
	return (this->*_FuncInitLotto)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncOpenAuction(SERVER, "CNpcEvent::FuncOpenAuction");
bool CNpcEvent::FuncOpenAuction(void)
{
	return (this->*_FuncOpenAuction)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncOpenMailing(SERVER, "CNpcEvent::FuncOpenMailing");
bool CNpcEvent::FuncOpenMailing(void)
{
	return (this->*_FuncOpenMailing)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(int time)> CNpcEvent::_FuncStripPC(SERVER, "CNpcEvent::FuncStripPC");
bool CNpcEvent::FuncStripPC(int time)
{
	return (this->*_FuncStripPC)(time);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int dir, int cell)> CNpcEvent::_FuncPushPC(SERVER, "CNpcEvent::FuncPushPC");
bool CNpcEvent::FuncPushPC(int dir, int cell)
{
	return (this->*_FuncPushPC)(dir, cell);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int itemID, int count, int x, int y)> CNpcEvent::_FuncItemDown(SERVER, "CNpcEvent::FuncItemDown");
bool CNpcEvent::FuncItemDown(int itemID, int count, int x, int y)
{
	return (this->*_FuncItemDown)(itemID, count, x, y);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int index, int value)> CNpcEvent::_FuncSetNumArray(SERVER, "CNpcEvent::FuncSetNumArray");
bool CNpcEvent::FuncSetNumArray(int index, int value)
{
	return (this->*_FuncSetNumArray)(index, value);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int index, TokenData& ret)> CNpcEvent::_FuncGetNumArray(SERVER, "CNpcEvent::FuncGetNumArray");
bool CNpcEvent::FuncGetNumArray(int index, TokenData& ret)
{
	return (this->*_FuncGetNumArray)(index, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int small, int big)> CNpcEvent::_FuncShuffleNumbers(SERVER, "CNpcEvent::FuncShuffleNumbers");
bool CNpcEvent::FuncShuffleNumbers(int small, int big)
{
	return (this->*_FuncShuffleNumbers)(small, big);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncPartyName(SERVER, "CNpcEvent::FuncPartyName");
bool CNpcEvent::FuncPartyName(TokenData& ret)
{
	return (this->*_FuncPartyName)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int percent, int time)> CNpcEvent::_FuncChangeSpeed(SERVER, "CNpcEvent::FuncChangeSpeed");
bool CNpcEvent::FuncChangeSpeed(int percent, int time)
{
	return (this->*_FuncChangeSpeed)(percent, time);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncIsSiegeTime(SERVER, "CNpcEvent::FuncIsSiegeTime");
bool CNpcEvent::FuncIsSiegeTime(TokenData& ret)
{
	return (this->*_FuncIsSiegeTime)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int ITID)> CNpcEvent::_FuncConsumeSpecialItem(SERVER, "CNpcEvent::FuncConsumeSpecialItem");
bool CNpcEvent::FuncConsumeSpecialItem(int ITID)
{
	return (this->*_FuncConsumeSpecialItem)(ITID);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int item, int count)> CNpcEvent::_FuncSetItemPartyInMap(SERVER, "CNpcEvent::FuncSetItemPartyInMap");
bool CNpcEvent::FuncSetItemPartyInMap(int item, int count)
{
	return (this->*_FuncSetItemPartyInMap)(item, count);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncIsHuntingListFull(SERVER, "CNpcEvent::FuncIsHuntingListFull");
bool CNpcEvent::FuncIsHuntingListFull(TokenData& ret)
{
	return (this->*_FuncIsHuntingListFull)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int mob, TokenData& ret)> CNpcEvent::_FuncFindHuntingList(SERVER, "CNpcEvent::FuncFindHuntingList");
bool CNpcEvent::FuncFindHuntingList(int mob, TokenData& ret)
{
	return (this->*_FuncFindHuntingList)(mob, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int mob)> CNpcEvent::_FuncAddHuntingList(SERVER, "CNpcEvent::FuncAddHuntingList");
bool CNpcEvent::FuncAddHuntingList(int mob)
{
	return (this->*_FuncAddHuntingList)(mob);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int mob)> CNpcEvent::_FuncDeleteHuntingList(SERVER, "CNpcEvent::FuncDeleteHuntingList");
bool CNpcEvent::FuncDeleteHuntingList(int mob)
{
	return (this->*_FuncDeleteHuntingList)(mob);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncDisplayHuntingList(SERVER, "CNpcEvent::FuncDisplayHuntingList");
bool CNpcEvent::FuncDisplayHuntingList(TokenData& ret)
{
	return (this->*_FuncDisplayHuntingList)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncDisplayHuntingList2(SERVER, "CNpcEvent::FuncDisplayHuntingList2");
bool CNpcEvent::FuncDisplayHuntingList2(TokenData& ret)
{
	return (this->*_FuncDisplayHuntingList2)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int mob, int count)> CNpcEvent::_FuncSetHuntingList(SERVER, "CNpcEvent::FuncSetHuntingList");
bool CNpcEvent::FuncSetHuntingList(int mob, int count)
{
	return (this->*_FuncSetHuntingList)(mob, count);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncClearHuntingList(SERVER, "CNpcEvent::FuncClearHuntingList");
bool CNpcEvent::FuncClearHuntingList(void)
{
	return (this->*_FuncClearHuntingList)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FUNCUseHuntingList(SERVER, "CNpcEvent::FUNCUseHuntingList");
bool CNpcEvent::FUNCUseHuntingList(TokenData& ret)
{
	return (this->*_FUNCUseHuntingList)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int mob, TokenData& ret)> CNpcEvent::_FUNCCheckHuntingList(SERVER, "CNpcEvent::FUNCCheckHuntingList");
bool CNpcEvent::FUNCCheckHuntingList(int mob, TokenData& ret)
{
	return (this->*_FUNCCheckHuntingList)(mob, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncIsTimeListFull(SERVER, "CNpcEvent::FuncIsTimeListFull");
bool CNpcEvent::FuncIsTimeListFull(TokenData& ret)
{
	return (this->*_FuncIsTimeListFull)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int ti, TokenData& ret)> CNpcEvent::_FuncFindTimeList(SERVER, "CNpcEvent::FuncFindTimeList");
bool CNpcEvent::FuncFindTimeList(int ti, TokenData& ret)
{
	return (this->*_FuncFindTimeList)(ti, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int ti)> CNpcEvent::_FuncAddTimeList(SERVER, "CNpcEvent::FuncAddTimeList");
bool CNpcEvent::FuncAddTimeList(int ti)
{
	return (this->*_FuncAddTimeList)(ti);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int ti)> CNpcEvent::_FuncDeleteTimeList(SERVER, "CNpcEvent::FuncDeleteTimeList");
bool CNpcEvent::FuncDeleteTimeList(int ti)
{
	return (this->*_FuncDeleteTimeList)(ti);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncDisplayTimeList(SERVER, "CNpcEvent::FuncDisplayTimeList");
bool CNpcEvent::FuncDisplayTimeList(TokenData& ret)
{
	return (this->*_FuncDisplayTimeList)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int ti, int dt)> CNpcEvent::_FuncSetTimeList(SERVER, "CNpcEvent::FuncSetTimeList");
bool CNpcEvent::FuncSetTimeList(int ti, int dt)
{
	return (this->*_FuncSetTimeList)(ti, dt);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncClearTimeList(SERVER, "CNpcEvent::FuncClearTimeList");
bool CNpcEvent::FuncClearTimeList(void)
{
	return (this->*_FuncClearTimeList)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(int x, int y, int type)> CNpcEvent::_FuncChangeCellType(SERVER, "CNpcEvent::FuncChangeCellType");
bool CNpcEvent::FuncChangeCellType(int x, int y, int type)
{
	return (this->*_FuncChangeCellType)(x, y, type);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int x, int y, TokenData& ret)> CNpcEvent::_FuncGetCellType(SERVER, "CNpcEvent::FuncGetCellType");
bool CNpcEvent::FuncGetCellType(int x, int y, TokenData& ret)
{
	return (this->*_FuncGetCellType)(x, y, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncGetPayType(SERVER, "CNpcEvent::FuncGetPayType");
bool CNpcEvent::FuncGetPayType(TokenData& ret)
{
	return (this->*_FuncGetPayType)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncGetConnectionArea(SERVER, "CNpcEvent::FuncGetConnectionArea");
bool CNpcEvent::FuncGetConnectionArea(TokenData& ret)
{
	return (this->*_FuncGetConnectionArea)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncGetConnectionState(SERVER, "CNpcEvent::FuncGetConnectionState");
bool CNpcEvent::FuncGetConnectionState(TokenData& ret)
{
	return (this->*_FuncGetConnectionState)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int mobType)> CNpcEvent::_FuncGetPetEgg(SERVER, "CNpcEvent::FuncGetPetEgg");
bool CNpcEvent::FuncGetPetEgg(int mobType)
{
	return (this->*_FuncGetPetEgg)(mobType);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* cashShop)> CNpcEvent::_FuncCashItem(SERVER, "CNpcEvent::FuncCashItem");
bool CNpcEvent::FuncCashItem(char* cashShop)
{
	return (this->*_FuncCashItem)(cashShop);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part, TokenData& ret)> CNpcEvent::_FuncRefinery(SERVER, "CNpcEvent::FuncRefinery");
bool CNpcEvent::FuncRefinery(int part, TokenData& ret)
{
	return (this->*_FuncRefinery)(part, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncRelaodMobileEvent(SERVER, "CNpcEvent::FuncRelaodMobileEvent");
bool CNpcEvent::FuncRelaodMobileEvent(void)
{
	return (this->*_FuncRelaodMobileEvent)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part)> CNpcEvent::_FuncSetTempTime(SERVER, "CNpcEvent::FuncSetTempTime");
bool CNpcEvent::FuncSetTempTime(int part)
{
	return (this->*_FuncSetTempTime)(part);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int part, TokenData& ret)> CNpcEvent::_FuncElapseTempTime(SERVER, "CNpcEvent::FuncElapseTempTime");
bool CNpcEvent::FuncElapseTempTime(int part, TokenData& ret)
{
	return (this->*_FuncElapseTempTime)(part, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int itemID, int count, TokenData& ret)> CNpcEvent::_FuncGetInventoryRemainCount(SERVER, "CNpcEvent::FuncGetInventoryRemainCount");
bool CNpcEvent::FuncGetInventoryRemainCount(int itemID, int count, TokenData& ret)
{
	return (this->*_FuncGetInventoryRemainCount)(itemID, count, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int qid, TokenData& ret)> CNpcEvent::_FuncIsBeginQuest(SERVER, "CNpcEvent::FuncIsBeginQuest");
bool CNpcEvent::FuncIsBeginQuest(int qid, TokenData& ret)
{
	return (this->*_FuncIsBeginQuest)(qid, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int qid)> CNpcEvent::_FuncSetQuest(SERVER, "CNpcEvent::FuncSetQuest");
bool CNpcEvent::FuncSetQuest(int qid)
{
	return (this->*_FuncSetQuest)(qid);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int oldQID, int newQID)> CNpcEvent::_FuncChangQuest(SERVER, "CNpcEvent::FuncChangQuest");
bool CNpcEvent::FuncChangQuest(int oldQID, int newQID)
{
	return (this->*_FuncChangQuest)(oldQID, newQID);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int qid)> CNpcEvent::_FuncEraseQuest(SERVER, "CNpcEvent::FuncEraseQuest");
bool CNpcEvent::FuncEraseQuest(int qid)
{
	return (this->*_FuncEraseQuest)(qid);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int qid)> CNpcEvent::_FuncComplateQuest(SERVER, "CNpcEvent::FuncComplateQuest");
bool CNpcEvent::FuncComplateQuest(int qid)
{
	return (this->*_FuncComplateQuest)(qid);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int startQID, int endQID)> CNpcEvent::_FuncCompleteQuest_Between(SERVER, "CNpcEvent::FuncCompleteQuest_Between");
bool CNpcEvent::FuncCompleteQuest_Between(int startQID, int endQID)
{
	return (this->*_FuncCompleteQuest_Between)(startQID, endQID);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int questID)> CNpcEvent::_FuncRecall_CompleteQuest(SERVER, "CNpcEvent::FuncRecall_CompleteQuest");
bool CNpcEvent::FuncRecall_CompleteQuest(int questID)
{
	return (this->*_FuncRecall_CompleteQuest)(questID);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int qid, TokenData& ret)> CNpcEvent::_FuncCheckQuest_Hunting(SERVER, "CNpcEvent::FuncCheckQuest_Hunting");
bool CNpcEvent::FuncCheckQuest_Hunting(int qid, TokenData& ret)
{
	return (this->*_FuncCheckQuest_Hunting)(qid, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int qid, TokenData& ret)> CNpcEvent::_FuncCheckQuest_PlayTime(SERVER, "CNpcEvent::FuncCheckQuest_PlayTime");
bool CNpcEvent::FuncCheckQuest_PlayTime(int qid, TokenData& ret)
{
	return (this->*_FuncCheckQuest_PlayTime)(qid, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* zone, int mobId, char* mobName, int posX, int posY)> CNpcEvent::_FuncCallGuardian(SERVER, "CNpcEvent::FuncCallGuardian");
bool CNpcEvent::FuncCallGuardian(char* zone, int mobId, char* mobName, int posX, int posY)
{
	return (this->*_FuncCallGuardian)(zone, mobId, mobName, posX, posY);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* mapName, TokenData& ret)> CNpcEvent::_FuncGetLastSiegeMsg(SERVER, "CNpcEvent::FuncGetLastSiegeMsg");
bool CNpcEvent::FuncGetLastSiegeMsg(char* mapName, TokenData& ret)
{
	return (this->*_FuncGetLastSiegeMsg)(mapName, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* str, int npcID)> CNpcEvent::_FuncDialog(SERVER, "CNpcEvent::FuncDialog");
bool CNpcEvent::FuncDialog(char* str, int npcID)
{
	return (this->*_FuncDialog)(str, npcID);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int npcID)> CNpcEvent::_FuncWaitDialog(SERVER, "CNpcEvent::FuncWaitDialog");
bool CNpcEvent::FuncWaitDialog(int npcID)
{
	return (this->*_FuncWaitDialog)(npcID);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int npcID)> CNpcEvent::_FuncCloseDialog(SERVER, "CNpcEvent::FuncCloseDialog");
bool CNpcEvent::FuncCloseDialog(int npcID)
{
	return (this->*_FuncCloseDialog)(npcID);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int npcID)> CNpcEvent::_FuncDlgWriteStr(SERVER, "CNpcEvent::FuncDlgWriteStr");
bool CNpcEvent::FuncDlgWriteStr(int npcID)
{
	return (this->*_FuncDlgWriteStr)(npcID);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* zone, int x, int y)> CNpcEvent::_FuncMapMove(SERVER, "CNpcEvent::FuncMapMove");
bool CNpcEvent::FuncMapMove(const char* zone, int x, int y)
{
	return (this->*_FuncMapMove)(zone, x, y);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* in_pMemorialDungeonName, TokenData& out_ret)> CNpcEvent::_FuncMdungeon_Subscription(SERVER, "CNpcEvent::FuncMdungeon_Subscription");
bool CNpcEvent::FuncMdungeon_Subscription(const char* in_pMemorialDungeonName, TokenData& out_ret)
{
	return (this->*_FuncMdungeon_Subscription)(in_pMemorialDungeonName, out_ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* in_pMemorialDungeonName, TokenData& out_ret)> CNpcEvent::_FuncMdungeon_Enter(SERVER, "CNpcEvent::FuncMdungeon_Enter");
bool CNpcEvent::FuncMdungeon_Enter(const char* in_pMemorialDungeonName, TokenData& out_ret)
{
	return (this->*_FuncMdungeon_Enter)(in_pMemorialDungeonName, out_ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* in_pTitle, const char* in_pMdunTitle, const char* in_pPartyTitle)> CNpcEvent::_FuncMdungeon_List(SERVER, "CNpcEvent::FuncMdungeon_List");
bool CNpcEvent::FuncMdungeon_List(const char* in_pTitle, const char* in_pMdunTitle, const char* in_pPartyTitle)
{
	return (this->*_FuncMdungeon_List)(in_pTitle, in_pMdunTitle, in_pPartyTitle);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* in_pPartyName)> CNpcEvent::_FuncMdungeon_Destroy(SERVER, "CNpcEvent::FuncMdungeon_Destroy");
bool CNpcEvent::FuncMdungeon_Destroy(const char* in_pPartyName)
{
	return (this->*_FuncMdungeon_Destroy)(in_pPartyName);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const int in_Request, TokenData& out_ret)> CNpcEvent::_FuncMdungeon_OpenState(SERVER, "CNpcEvent::FuncMdungeon_OpenState");
bool CNpcEvent::FuncMdungeon_OpenState(const int in_Request, TokenData& out_ret)
{
	return (this->*_FuncMdungeon_OpenState)(in_Request, out_ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* name, TokenData& out_ret)> CNpcEvent::_FuncMDungeon_NpcName(SERVER, "CNpcEvent::FuncMDungeon_NpcName");
bool CNpcEvent::FuncMDungeon_NpcName(const char* name, TokenData& out_ret)
{
	return (this->*_FuncMDungeon_NpcName)(name, out_ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* map_name, TokenData& out_ret)> CNpcEvent::_FuncMDungeon_MapName(SERVER, "CNpcEvent::FuncMDungeon_MapName");
bool CNpcEvent::FuncMDungeon_MapName(const char* map_name, TokenData& out_ret)
{
	return (this->*_FuncMDungeon_MapName)(map_name, out_ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(NpcSvrNpcInfo* npcInfo, bool isNpc)> CNpcEvent::_FuncMDungeon_Npc(SERVER, "CNpcEvent::FuncMDungeon_Npc");
bool CNpcEvent::FuncMDungeon_Npc(NpcSvrNpcInfo* npcInfo, bool isNpc)
{
	return (this->*_FuncMDungeon_Npc)(npcInfo, isNpc);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* zone, int x, int y, int w, int h, int num, int mobId, int regenMin, int regenMax, int regenType, char* name)> CNpcEvent::_FuncMDungeon_PutMob(SERVER, "CNpcEvent::FuncMDungeon_PutMob");
bool CNpcEvent::FuncMDungeon_PutMob(const char* zone, int x, int y, int w, int h, int num, int mobId, int regenMin, int regenMax, int regenType, char* name)
{
	return (this->*_FuncMDungeon_PutMob)(zone, x, y, w, h, num, mobId, regenMin, regenMax, regenType, name);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* campCode, int x, int y)> CNpcEvent::_FuncCampCode(SERVER, "CNpcEvent::FuncCampCode");
bool CNpcEvent::FuncCampCode(char* campCode, int x, int y)
{
	return (this->*_FuncCampCode)(campCode, x, y);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncGetCampCode(SERVER, "CNpcEvent::FuncGetCampCode");
bool CNpcEvent::FuncGetCampCode(TokenData& ret)
{
	return (this->*_FuncGetCampCode)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int mobID, int x, int y, char* campCode, char* name)> CNpcEvent::_FuncCallCampMob(SERVER, "CNpcEvent::FuncCallCampMob");
bool CNpcEvent::FuncCallCampMob(int mobID, int x, int y, char* campCode, char* name)
{
	return (this->*_FuncCallCampMob)(mobID, x, y, campCode, name);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int x, int y)> CNpcEvent::_FuncSetRP2(SERVER, "CNpcEvent::FuncSetRP2");
bool CNpcEvent::FuncSetRP2(int x, int y)
{
	return (this->*_FuncSetRP2)(x, y);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* campCode, int x, int y)> CNpcEvent::_FuncMassSetRP2(SERVER, "CNpcEvent::FuncMassSetRP2");
bool CNpcEvent::FuncMassSetRP2(char* campCode, int x, int y)
{
	return (this->*_FuncMassSetRP2)(campCode, x, y);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int RPNo)> CNpcEvent::_FuncPlayerToRP(SERVER, "CNpcEvent::FuncPlayerToRP");
bool CNpcEvent::FuncPlayerToRP(int RPNo)
{
	return (this->*_FuncPlayerToRP)(RPNo);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* campCode, int point)> CNpcEvent::_FuncUpdateCampPoint(SERVER, "CNpcEvent::FuncUpdateCampPoint");
bool CNpcEvent::FuncUpdateCampPoint(char* campCode, int point)
{
	return (this->*_FuncUpdateCampPoint)(campCode, point);

	//TODO
}


hook_method<bool (CNpcEvent::*)(char* campCode, TokenData& ret)> CNpcEvent::_FuncGetCampPoint(SERVER, "CNpcEvent::FuncGetCampPoint");
bool CNpcEvent::FuncGetCampPoint(char* campCode, TokenData& ret)
{
	return (this->*_FuncGetCampPoint)(campCode, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncResetCampPoint(SERVER, "CNpcEvent::FuncResetCampPoint");
bool CNpcEvent::FuncResetCampPoint(void)
{
	return (this->*_FuncResetCampPoint)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* mobName, int skill, int level, int time, int chatNo)> CNpcEvent::_FuncMyMobSkillUse(SERVER, "CNpcEvent::FuncMyMobSkillUse");
bool CNpcEvent::FuncMyMobSkillUse(const char* mobName, int skill, int level, int time, int chatNo)
{
	return (this->*_FuncMyMobSkillUse)(mobName, skill, level, time, chatNo);

	CMsg msg;
	msg.CMsg::SetMsgID(79);
	msg.par1 = (int)mobName;
	msg.par2 = skill;
	msg.par3 = level;
	msg.par4 = time;
	msg.par5 = chatNo;
	g_characterMgr->CCharacterMgr::SendMsgFromNPCServer(0, m_npcId, &msg, 0, 0);
	Trace("FuncMyMobSkillUse mobName = %s, skill = %d, level = %d, time = %d, chatNo = %d \n", mobName, skill, level, time, chatNo);
	return true;
}


hook_method<bool (CNpcEvent::*)(const char* mobName, TokenData& ret)> CNpcEvent::_FuncWhereMyMob_X(SERVER, "CNpcEvent::FuncWhereMyMob_X");
bool CNpcEvent::FuncWhereMyMob_X(const char* mobName, TokenData& ret)
{
	return (this->*_FuncWhereMyMob_X)(mobName, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* mobName, TokenData& ret)> CNpcEvent::_FuncWhereMyMob_Y(SERVER, "CNpcEvent::FuncWhereMyMob_Y");
bool CNpcEvent::FuncWhereMyMob_Y(const char* mobName, TokenData& ret)
{
	return (this->*_FuncWhereMyMob_Y)(mobName, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int x, int y, int range, int skill_id, int level, int time, int msgId)> CNpcEvent::_FuncWideMobSkillUse(SERVER, "CNpcEvent::FuncWideMobSkillUse");
bool CNpcEvent::FuncWideMobSkillUse(int x, int y, int range, int skill_id, int level, int time, int msgId)
{
	return (this->*_FuncWideMobSkillUse)(x, y, range, skill_id, level, time, msgId);

	//TODO
}


hook_method<bool (CNpcEvent::*)(MSG_TYPE7_EIGHTWORD* data)> CNpcEvent::_FuncWideMobSkillUse2(SERVER, "CNpcEvent::FuncWideMobSkillUse2");
bool CNpcEvent::FuncWideMobSkillUse2(MSG_TYPE7_EIGHTWORD* data)
{
	return (this->*_FuncWideMobSkillUse2)(data);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int type, TokenData& ret)> CNpcEvent::_FuncCheckSiegeTime(SERVER, "CNpcEvent::FuncCheckSiegeTime");
bool CNpcEvent::FuncCheckSiegeTime(int type, TokenData& ret)
{
	return (this->*_FuncCheckSiegeTime)(type, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncIsBender(SERVER, "CNpcEvent::FuncIsBender");
bool CNpcEvent::FuncIsBender(TokenData& ret)
{
	return (this->*_FuncIsBender)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* ask, TokenData& ret)> CNpcEvent::_FuncGetNpcPosition(SERVER, "CNpcEvent::FuncGetNpcPosition");
bool CNpcEvent::FuncGetNpcPosition(const char* ask, TokenData& ret)
{
	return (this->*_FuncGetNpcPosition)(ask, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* color, int time)> CNpcEvent::_FuncProgressBar(SERVER, "CNpcEvent::FuncProgressBar");
bool CNpcEvent::FuncProgressBar(const char* color, int time)
{
	return (this->*_FuncProgressBar)(color, time);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncMercenaryCheck(SERVER, "CNpcEvent::FuncMercenaryCheck");
bool CNpcEvent::FuncMercenaryCheck(TokenData& ret)
{
	return (this->*_FuncMercenaryCheck)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncMercenaryType(SERVER, "CNpcEvent::FuncMercenaryType");
bool CNpcEvent::FuncMercenaryType(TokenData& ret)
{
	return (this->*_FuncMercenaryType)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncIsFreeServer(SERVER, "CNpcEvent::FuncIsFreeServer");
bool CNpcEvent::FuncIsFreeServer(TokenData& ret)
{
	return (this->*_FuncIsFreeServer)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncCheckPartyJob(SERVER, "CNpcEvent::FuncCheckPartyJob");
bool CNpcEvent::FuncCheckPartyJob(TokenData& ret)
{
	return (this->*_FuncCheckPartyJob)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncClearBuff(SERVER, "CNpcEvent::FuncClearBuff");
bool CNpcEvent::FuncClearBuff(void)
{
	return (this->*_FuncClearBuff)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* camp_code, TokenData& ret)> CNpcEvent::_FuncCheckAlive(SERVER, "CNpcEvent::FuncCheckAlive");
bool CNpcEvent::FuncCheckAlive(const char* camp_code, TokenData& ret)
{
	return (this->*_FuncCheckAlive)(camp_code, ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(NpcSvrNpcInfo* npcInfo)> CNpcEvent::_FuncKVMNpc(SERVER, "CNpcEvent::FuncKVMNpc");
HOOKED bool CNpcEvent::FuncKVMNpc(NpcSvrNpcInfo* npcInfo) // line 6809
{
	char mapName[256];
	SetMapName(mapName, npcInfo->zone);
	TrimLeft(mapName);
	TrimRight(mapName);
	if( g_mapInfo->CMapInfo::GetServerID(mapName) != GetLocalServerID() )
	{
		m_curInitNpc = 0;
		return true;
	}

	return (this->*_FuncKVMNpc)(npcInfo);

	unsigned long AID = this->CNpcEvent::FuncNpc2(npcInfo, true);
	if( AID <= 0 )
		return false;

	CNPC* npc = (CNPC*)g_characterMgr->CCharacterMgr::FindCharacter(AID, NPC_TYPE);
	if( npc == NULL || !npc->CNPC::RegistBattleFiledNpc(npcInfo->zone) )
	{
		Trace("FuncBattleNpc Regist Fail npcid = %d, mpa_name = %s\n", AID, npcInfo->zone);
		return false;
	}

	Trace("FuncBattleNpc npcid = %d, mpa_name = %s\n", AID, npcInfo->zone);
	return true;
}


hook_method<bool (CNpcEvent::*)(void)> CNpcEvent::_FuncKVMStartAliveCheck(SERVER, "CNpcEvent::FuncKVMStartAliveCheck");
bool CNpcEvent::FuncKVMStartAliveCheck(void)
{
	return (this->*_FuncKVMStartAliveCheck)();

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncPVPRankCheck(SERVER, "CNpcEvent::FuncPVPRankCheck");
bool CNpcEvent::FuncPVPRankCheck(TokenData& ret)
{
	return (this->*_FuncPVPRankCheck)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* sw)> CNpcEvent::_FuncKvm_Npc_Noti(SERVER, "CNpcEvent::FuncKvm_Npc_Noti");
bool CNpcEvent::FuncKvm_Npc_Noti(const char* sw)
{
	return (this->*_FuncKvm_Npc_Noti)(sw);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const int itemId, const int card1, const int card2, const int card3, const int card4)> CNpcEvent::_FuncGetItemSocket(SERVER, "CNpcEvent::FuncGetItemSocket");
bool CNpcEvent::FuncGetItemSocket(const int itemId, const int card1, const int card2, const int card3, const int card4)
{
	return (this->*_FuncGetItemSocket)(itemId, card1, card2, card3, card4);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const int itemId, const int card1, const int card2, const int card3, const int card4)> CNpcEvent::_FuncGetNonSlotItemSocket(SERVER, "CNpcEvent::FuncGetNonSlotItemSocket");
bool CNpcEvent::FuncGetNonSlotItemSocket(const int itemId, const int card1, const int card2, const int card3, const int card4)
{
	return (this->*_FuncGetNonSlotItemSocket)(itemId, card1, card2, card3, card4);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncGetMyMercenary(SERVER, "CNpcEvent::FuncGetMyMercenary");
bool CNpcEvent::FuncGetMyMercenary(TokenData& ret)
{
	return (this->*_FuncGetMyMercenary)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* log)> CNpcEvent::_FuncErrorLog(SERVER, "CNpcEvent::FuncErrorLog");
bool CNpcEvent::FuncErrorLog(const char* log)
{
	return (this->*_FuncErrorLog)(log);

	//TODO
}


hook_method<bool (CNpcEvent::*)(TokenData& ret)> CNpcEvent::_FuncIsMadogear(SERVER, "CNpcEvent::FuncIsMadogear");
bool CNpcEvent::FuncIsMadogear(TokenData& ret)
{
	return (this->*_FuncIsMadogear)(ret);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const char* opt)> CNpcEvent::_FuncSetMadogear(SERVER, "CNpcEvent::FuncSetMadogear");
bool CNpcEvent::FuncSetMadogear(const char* opt)
{
	return (this->*_FuncSetMadogear)(opt);

	//TODO
}


hook_method<bool (CNpcEvent::*)(int type)> CNpcEvent::_FuncBattlePlayModeNoti(SERVER, "CNpcEvent::FuncBattlePlayModeNoti");
bool CNpcEvent::FuncBattlePlayModeNoti(int type)
{
	return (this->*_FuncBattlePlayModeNoti)(type);

	//TODO
}


hook_method<bool (CNpcEvent::*)(const int other, const int par1, const int par2, const int par3)> CNpcEvent::_FuncInterOther(SERVER, "CNpcEvent::FuncInterOther");
bool CNpcEvent::FuncInterOther(const int other, const int par1, const int par2, const int par3)
{
	return (this->*_FuncInterOther)(other, par1, par2, par3);

	//TODO
}


hook_method<void (CNpcEvent::*)(void)> CNpcEvent::_TraceCurPos(SERVER, "CNpcEvent::TraceCurPos");
void CNpcEvent::TraceCurPos(void)
{
	return (this->*_TraceCurPos)();

	//TODO
}
