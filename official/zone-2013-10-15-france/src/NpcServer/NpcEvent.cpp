#include "CharacterMgr.h"
#include "CSectionLog.h"
#include "CStaticNPCAIDGenerator.h"
#include "PC.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "Common/Packet.h"
#include "NpcServer/NpcEvent.h"
#include "NpcServer/NpcSvr.h"
#include "shared/NCriticalErrorLog.h"
#include "shared/shared.h"
#include <mbstring.h>


/// static members
int& CNpcEvent::m_serverID = VTOR<int>(DetourFindFunction(EXEPATH(), "CNpcEvent::m_serverID"));


void CNpcEvent::EventLog(char* str, ...)
{
	if( !g_EventLog )
		return;

	va_list va;
	va_start(va, str);

	char buf[1024];
	vsprintf(buf, str, va);

	if( g_wrIteNpcEventLog == TRUE )
		CNpcEventLog::GetObj()->CNpcEventLog::Log(__FILE__, __LINE__, "%s", buf);
	else
		Trace(buf);
}


void TrimLeft(char* szString)
{
	char* szCursor = szString;

	while( _ismbcspace(*szCursor) )
		szCursor = (char*)_mbsinc((unsigned char*)szCursor);

	if( szCursor != szString )
		memmove(szString, szCursor, szString - szCursor + strlen(szString) + 1);
}


void TrimRight(char* szString)
{
	char* szCursor = szString;
	char* szTrimPos = NULL;

	while( *szCursor != '\0' )
	{
		if( _ismbcspace(*szCursor) )
		{
			if( szTrimPos == NULL )
				szTrimPos = szCursor;
		}
		else
		{
			szTrimPos = NULL;
		}

		szCursor = (char*)_mbsinc((unsigned char*)szCursor);
	}

	if( szTrimPos != NULL )
		*szTrimPos = '\0';
}


void SetMapName(char* dest, const char* src)
{
	wsprintfA(dest, "%s.gat", src); //FIXME: deprecated API
	_mbslwr((unsigned char*)dest);
}


CNpcEvent::CNpcEvent()
{
	this->CNpcEvent::Clear();
	m_interpreter.CInterpreter::RegisterHandler(this);
	m_nParamSize = 0;
	m_curInitNpc = 0;
	m_instantID = 0;
	m_DeleteCount = 0;
}


CNpcEvent::~CNpcEvent()
{
}


void CNpcEvent::Clear()
{
	m_input = 0;
	m_error = 0;
	m_waitType = REQ_NONE;
	m_waitTime = 0;
	m_pcId = 0;
	m_npcId = 0;
	m_npc = NULL;
	m_npcMgr = NULL;
	m_binBuf = NULL;
	m_isDisableItemMove = false;
	m_dialogFlag = false;
	m_reserveTime = 0;
	m_initList.clear();
	m_numArray.clear();
	m_DeleteCount = 0;
}


bool CNpcEvent::Run_Dungeon(CNpcMgr* npcMgr, CBinBuf* binBuf, const char* dg_ident, unsigned int instantID, int pcId, int npcId, int act)
{
	if( dg_ident == NULL )
		return false;

	memset(m_dgIdent, 0, sizeof(m_dgIdent));
	memcpy_s(m_dgIdent, sizeof(m_dgIdent), dg_ident, 3);

	if( pcId == 0 && npcId == 0 )
		m_instantID = instantID;

	return this->CNpcEvent::Run(npcMgr, binBuf, pcId, npcId, act);
}


char* CNpcEvent::GetDungeonIdent()
{
	return m_dgIdent;
}


bool CNpcEvent::Run(CNpcMgr* npcMgr, CBinBuf* binBuf, int pcId, int npcId, int actIndex)
{
	this->CNpcEvent::Clear();
	m_npcMgr = npcMgr;
	m_npcId = npcId;
	m_binBuf = binBuf;
	m_pcId = pcId;

	this->CScriptEventHandler::Init(pcId);

	if( m_pcId == 0 && m_npcId == 0 && actIndex == 0 )
	{
		if( !m_interpreter.CInterpreter::Run(binBuf, 0, true) )
		{
			this->EventLog("CNpcEvnet.Run : Main Script Failure\n");
			return false;
		}

		this->EventLog("restart...\n");
		return true;
	}

	m_npc = m_npcMgr->CNpcMgr::Get(m_npcId);
	if( m_npc == NULL )
	{
		this->EventLog("CNpcEvnet.Run : not exist NPC\n");
		return false;
	}

	int pos = m_npc->CNpc::GetActionScriptPos(actIndex);
	if( pos == 0 )
	{
		if( actIndex != 0 || m_pcId != 0 )
			this->EventLog("CNpcEvent.Run : npc=%d act=%d no script\n", m_npcId, actIndex);
		return false;
	}

	if( !m_interpreter.CInterpreter::Run(binBuf, pos, false) )
	{
		this->EventLog("CNpcEvnet.Run : actIndex=%d script pos error\n", actIndex);
		return false;
	}

	this->EventLog("script begin pos - hex: %x dec:%d\n", pos, pos);
	return true;
}


unsigned int CNpcEvent::Proc(bool isOnce)
{
	if( m_binBuf == NULL )
		return 0;

	if( m_waitType != REQ_NONE )
	{
		if( time(NULL) < m_waitTime )
			return 2;

		this->CNpcEvent::Stop();
		return 0;
	}

	if( !m_interpreter.CInterpreter::Proc() )
	{
		if( m_reserveTime != 0 )
			m_npc->CNpc::OnTimer();
		return 0;
	}

	return 1;
}


void CNpcEvent::TraceCurPos()
{
	this->EventLog("addr hex[%x] dec[%d]\n", m_interpreter.CInterpreter::GetCurPos(), m_interpreter.CInterpreter::GetCurPos());
}


void CNpcEvent::OnError(const char* str)
{
	this->CNpcEvent::TraceCurPos();
	this->EventLog("Interpreter Error: %s\n", str);
}


void CNpcEvent::Stop()
{
	if( m_dialogFlag )
	{
		this->FuncDlgWriteStr(0);
		m_dialogFlag = false;
	}

	if( m_isDisableItemMove )
	{
		this->CNpcEvent::FuncEnableItemMove();
		m_isDisableItemMove = false;
	}

	m_binBuf = NULL;

	if( m_pcId != 0 )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pcId, CM_CLEAR_EVENT, 0, 0, 0, 0);

	if( this->CNpcEvent::IsGlobalEvent() )
	{
		CZNPC2Msg msg1;
		msg1.CMsg::SetMsgID(ZNPC2MSG_CLEARFIRSTEVENT);
		if( m_instantID <= 0 )
		{
			msg1.par1 = 0;
		}
		else
		{
			msg1.par1 = 1;
			msg1.par2 = m_instantID;
		}
		g_npcSvr.CNpcSvr::SendMsg(0, 0, &msg1);

		for( std::vector<int>::const_iterator iter = m_initList.begin(); iter != m_initList.end(); ++iter )
		{
			unsigned long AID = *iter;

			CZNPC2Msg msg;
			msg.CMsg::SetMsgID(ZNPC2MSG_CALLEVENT);
			msg.par1 = NPCEVENT_ONINIT;
			g_npcSvr.CNpcSvr::SendMsg(0, AID, &msg);
		}

		m_initList.clear();

		std::set<std::string>::const_iterator b = g_npcSvr.m_cmdothernpcNames.begin();
		std::set<std::string>::const_iterator e = g_npcSvr.m_cmdothernpcNames.end();
		for( std::set<std::string>::const_iterator iter = b; iter != e; ++iter )
		{
			const std::string& npcName = *iter;

			if( g_npcSvr.m_npcNames.count(npcName) > 1 )
			{
				char strTemp[256];
				sprintf_s(strTemp, countof(strTemp), "find a npc whose name is \"%s\" and is not the target of cmdothernpc. rename!\n", npcName.c_str());
				Trace(strTemp);
			}
		}

		g_npcSvr.m_npcNames.clear();
		g_npcSvr.m_cmdothernpcNames.clear();
	}
	else
	{
		if( m_OnInit )
			m_npc->CNpc::SetOnInit(true);
	}
}


void CNpcEvent::StopDungern()
{
	if( m_dialogFlag )
	{
		this->FuncCloseDialog(0);
		m_dialogFlag = false;
	}

	if( m_isDisableItemMove )
	{
		this->CNpcEvent::FuncEnableItemMove();
		m_isDisableItemMove = false;
	}

	m_binBuf = NULL;

	if( m_pcId != 0 )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pcId, CM_CLEAR_EVENT, 0, 0, 0, 0);

	if( this->CNpcEvent::IsGlobalEvent() )
	{
		CZNPC2Msg msg1;
		msg1.CMsg::SetMsgID(ZNPC2MSG_CLEARFIRSTEVENT);
		if( m_instantID <= 0 )
		{
			msg1.par1 = 0;
		}
		else
		{
			msg1.par1 = 1;
			msg1.par2 = m_instantID;
		}
		g_npcSvr.CNpcSvr::SendMsg(0, 0, &msg1);

		m_initList.clear();

		std::set<std::string>::const_iterator b = g_npcSvr.m_cmdothernpcNames.begin();
		std::set<std::string>::const_iterator e = g_npcSvr.m_cmdothernpcNames.end();
		for( std::set<std::string>::const_iterator iter = b; iter != e; ++iter )
		{
			const std::string& npcName = *iter;

			if( g_npcSvr.m_npcNames.count(npcName) > 1 )
			{
				char strTemp[256];
				sprintf_s(strTemp, countof(strTemp), "find a npc whose name is \"%s\" and is not the target of cmdothernpc. rename!\n", npcName.c_str());
				Trace(strTemp);
			}
		}

		g_npcSvr.m_npcNames.clear();
		g_npcSvr.m_cmdothernpcNames.clear();
	}
	else
	{
		if( m_OnInit )
			m_npc->CNpc::SetOnInit(true);
	}
}


void CNpcEvent::Answer(int type, int answer)
{
	this->EventLog("Answer %d %d\n", type, answer);

	if( m_waitType != type )
	{
		if( m_waitType == PROGRESS )
		{
			this->CNpcEvent::Stop();
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_pcId, CM_PROGRESSBAR_CANCEL, 0, 0, 0, 0);
			this->EventLog("progress cancel \n");
			return;
		}

		this->CNpcEvent::Stop();
		this->EventLog("Mismatch Answer. m_waitType[%d] Answer(%d, %d)\n", m_waitType, type, answer);
		m_error = 1;
		this->CScriptEventHandler::BanPlayer();
		return;
	}

	switch( m_waitType )
	{
	case DLG_WRITE:
	{
		m_input = answer;

		if( answer < m_min )
		{
			this->EventLog("dlgwrite :%d < %d\n", answer, m_min);
			m_error = 1;
			break;
		}

		if( answer > m_max )
		{
			this->EventLog("dlgwrite :%d > %d\n", answer, m_max);
			m_error = 1;
			break;
		}

		this->EventLog("dlgwrite :%d\n", answer);
	}
	break;
	case DLG_WRITESTR:
	{
		if( answer == -1 )
			break;

		const char* answerstr = reinterpret_cast<const char*>(answer);

		m_inputstr = answerstr;
		this->EventLog("dlgwritestr :%s\n", answerstr);
	}
	break;
	case ITEM_GET:
	{
		if( answer != 3 ) //TODO
		{
			this->EventLog("get:cancel\n");
			this->CNpcEvent::Stop();
			m_error = 1;
			break;
		}

		this->EventLog("get:ok\n");
	}
	break;
	case REQ_NEXT_ANS:
	{
		this->EventLog("answer:next\n");
	}
	break;
	case REQ_CLOSE_ANS:
	{
		m_dialogFlag = false;
		this->EventLog("answer:close\n");
	}
	break;
	case CHOOSE_ANS:
	{
		if( answer == 255 )
		{
			this->CNpcEvent::Stop();
			this->EventLog("choosemenu cancel button \n");
			return;
		}

		if( answer <= 0 || answer > m_nParamSize )
		{
			this->EventLog("over choosemenu select number\n");
			this->CNpcEvent::Stop();
			m_error = 1;
			this->CScriptEventHandler::BanPlayer();
			return;
		}

		this->EventLog("menu answer:%d\n", answer);
		m_varMap->data["$case"] = answer;
	}
	break;
	case PROGRESS:
	{
		if( time(NULL) < m_waitTime - 5 )
		{
			this->EventLog("progress anser early arrival\n");
			this->CNpcEvent::Stop();
			m_error = 1;
			this->CScriptEventHandler::BanPlayer();
			break;
		}

		this->EventLog("progress\n");
	}
	break;
	};

	m_waitType = REQ_NONE;
	m_waitTime = 0;
}


bool CNpcEvent::OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret)
{
	ret = 0;

	switch( func )
	{
	case FUNC_TRACE:
	{
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) break;
		char* str = parm[0].TokenData::GetStr();
		return this->CNpcEvent::FuncTrace(str);
	}
	break;
	case FUNC_ERROR:
	{
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 0) ) break;
		return this->CNpcEvent::FuncError(ret);
	}
	break;
	case FUNC_RAND:
	{
		return this->CScriptEventHandler::OnFunc(FUNC_RAND, parm, ret);
	}
	break;
	case FUNC_LOT:
	{
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) break;
		int numerator = parm[0].TokenData::GetNum();
		int denominator = parm[1].TokenData::GetNum();
		return this->CNpcEvent::FuncLot(numerator, denominator, ret);
	}
	break;
	};

	if( this->CNpcEvent::IsGlobalEvent() )
		return this->CNpcEvent::GlobalFunc(func, parm, ret);
	else
		return this->CNpcEvent::DefaultNpcFunc(func, parm, ret);
}


hook_func<void (__stdcall *)()> CNpcEvent__DefaultNpcFunc(EXEPATH(), "CNpcEvent::DefaultNpcFunc");
bool CNpcEvent::DefaultNpcFunc(int func, std::deque<TokenData>& parm, TokenData& ret) // 661-1683
{
	bool result;
	void* hookptr = CNpcEvent__DefaultNpcFunc;
#pragma warning(push)
#pragma warning(disable:4405)
	__asm lea eax, ret
#pragma warning(pop)
	__asm push eax
	__asm lea edx, parm
	__asm push func
	__asm mov ecx, this
	__asm call hookptr
	__asm mov result, al
	return result;
	//TODO
}


hook_func<void (__stdcall *)()> CNpcEvent__GlobalFunc(EXEPATH(), "CNpcEvent::GlobalFunc");
bool CNpcEvent::GlobalFunc(int func, std::deque<TokenData>& parm, TokenData& ret) // 1688-2058
{
	bool result;
	void* hookptr = CNpcEvent__GlobalFunc;
#pragma warning(push)
#pragma warning(disable:4405)
	__asm lea eax, ret
#pragma warning(pop)
	__asm push eax
	__asm lea eax, parm
	__asm mov ecx, func
	__asm push this
	__asm call hookptr
	__asm mov result, al
	return result;
	//TODO
}


bool CNpcEvent::FuncTrace(char* str) // 2061-2065
{
	this->CNpcEvent::TraceCurPos();
	this->EventLog("Trace: %s\n", str);
	return true;
}


bool CNpcEvent::FuncError(TokenData& ret) // 2368-2371
{
	ret = m_error;
	return true;
}


bool CNpcEvent::FuncLot(int numerator, int denominator, TokenData& ret) // 2389-2404
{
	if( numerator > denominator )
	{
		this->EventLog("lot:\tnumerator > denominator.\n");
		return false;
	}

	if( denominator == 0 )
	{
		this->EventLog("lot: denominator is zero.\n");
		return false;
	}

	int result = ( rand() % denominator < numerator ) ? 1 : 0;
	ret = result;
	return true;
}


void CNpcEvent::Wait(int type, int delay) // 2408-2420
{
	m_waitType = type;
	m_waitTime = delay + time(NULL);

	if( type == ITEM_GET || type == DLG_WRITE || type >= DLG_WRITESTR )
		m_error = 0;
}


bool CNpcEvent::FuncDialog(char* str, int npcID) // 2704-2726
{
	size_t len = strlen(str);

	PACKET_NZ_DIALOG_ACK dialogPacket;
	dialogPacket.PacketType = HEADER_NZ_DIALOG_ACK;
	dialogPacket.length = sizeof(PACKET_NZ_DIALOG_ACK) + len + 1;
	dialogPacket.NAID = m_npcId;
	dialogPacket.CAID = m_pcId;

	CNPC2ZMsg msg;
	msg.CMsg::SetMsgID(NPC2ZMSG_OPENDIALOG);
	msg.par1 = sizeof(PACKET_NZ_DIALOG_ACK);
	msg.par2 = reinterpret_cast<int>(&dialogPacket);
	msg.par3 = len + 1;
	msg.par4 = reinterpret_cast<int>(str);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(0, dialogPacket.NAID, &msg, 0, 0);

	m_dialogFlag = true;
	this->EventLog("dialog : %s\n", str);
	return true;
}


bool CNpcEvent::FuncWaitDialog(int npcID) // 2748-2758
{
	CNPC2ZMsg msg;
	msg.CMsg::SetMsgID(NPC2ZMSG_WAITDIALOG);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);

	this->CNpcEvent::Wait(REQ_NEXT_ANS, 60);
	this->EventLog("Wait - wait REQ_NEXT_ANS\n");
	return true;
}


bool CNpcEvent::FuncCloseDialog(int npcID) // 2774-2787
{
	if( !m_dialogFlag )
		return true;

	CNPC2ZMsg msg;
	msg.CMsg::SetMsgID(NPC2ZMSG_CLOSEDIALOG);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);

	this->CNpcEvent::Wait(REQ_CLOSE_ANS, 60);
	this->EventLog("close - wait REQ_CLOSE_ANS\n");
	return true;
}


bool CNpcEvent::FuncCart(BOOL flag) // 3037-3053
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_pcId, PC_TYPE);
	if( pc == NULL )
		return false;

	if( flag )
	{
		CNPC2ZMsg msg;
		msg.CMsg::SetMsgID(NPC2ZMSG_CARTON);
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);
	}
	else
	{
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pc, CM_CARTOFF, 0, 0, 0, 0);
	}

	this->EventLog("cart [on/off] %d\n", flag);
	return true;
}


bool CNpcEvent::FuncMenu(const char* str, bool bExtra) // 3068-3083
{
	CNPC2ZMsg msg;
	msg.CMsg::SetMsgID(NPC2ZMSG_MENU);
	msg.par1 = strlen(str) + 1;
	msg.par2 = reinterpret_cast<int>(str);
	if( bExtra )
		msg.par3 = 1;

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);
	m_dialogFlag = true;
	this->CNpcEvent::Wait(CHOOSE_ANS, 60);
	this->EventLog("menu %s\n", str);
	return true;
}


bool CNpcEvent::FuncMapMove(const char* zone, int x, int y) // 3137-3153
{
	char zoneGAT[256];
	SetMapName(zoneGAT, zone);

	CNPC2ZMsg msg;
	msg.CMsg::SetMsgID(NPC2ZMSG_MAPMOVE);
	msg.par1 = strlen(zoneGAT);
	msg.par2 = reinterpret_cast<int>(zoneGAT);
	msg.par3 = x;
	msg.par4 = y;
	msg.par5 = m_pcId;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);

	this->EventLog("mapmove %s %d %d\n", zoneGAT, x, y);
	return true;
}


bool CNpcEvent::FuncEnableItemMove() // 3399-3407
{
	CNPC2ZMsg msg;
	msg.CMsg::SetMsgID(NPC2ZMSG_ENABLEITEMMOVE);
	msg.par1 = m_pcId;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);

	this->EventLog("EnableItemMove\n");
	return true;
}


bool CNpcEvent::FuncSetEffectStatus(int effect) // 3490-3499
{
	CNPC2ZMsg msg;
	msg.CMsg::SetMsgID(NPC2ZMSG_SETEFFECTSTATE);
	msg.par1 = m_pcId;
	msg.par2 = effect;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);

	this->EventLog("FuncSetEffectStatus : %d\n", effect);
	return true;
}


unsigned long CNpcEvent::FuncNpc2(NpcSvrNpcInfo* npcInfo, bool isNpc) // 3541-3595
{
	char mapName[16] = {};
	SetMapName(mapName, (const char *)npcInfo->zone);
	TrimLeft(mapName);
	TrimRight(mapName);

	if( GetLocalServerID() != CMapInfoMgr::GetObj()->CMapInfoMgr::GetServerID(mapName) )
	{
		m_curInitNpc = 0;
		return true;
	}

	CStaticNPCAID StaticNPCAID = CStaticNPCAIDGenerator::GetObj()->CStaticNPCAIDGenerator::Alloc();
	int npcId = StaticNPCAID;
	if( npcId == 0 )
	{
		this->EventLog("FuncNpc: npc over aid\n");
		return false;
	}

	CNpc* npc = g_npcSvr.CNpcSvr::GetStaticNpcMgr()->CNpcMgr::Add(npcId);
	if( npc == NULL )
	{
		this->EventLog("FuncNpc: NpcMgr's add() failed. addr: hex[%x] dec[%d]\n", m_interpreter.CInterpreter::GetCurPos(), m_interpreter.CInterpreter::GetCurPos());
		return false;
	}

	npc->CNpc::SetInfo(npcId, npcInfo);
	npc->CNpc::SetOnInit(true);
	m_curInitNpc = npcId;

	if( !this->CScriptEventHandler::AddNpc(npcId, mapName, npcInfo) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CNpcEvent::FuncNpc, Can't Not AddNpc, MapName[%s], NpcName[%s], Pos[%d, %d]", mapName, npcInfo->name, npcInfo->x, npcInfo->y);
		g_npcSvr.GetStaticNpcMgr()->CNpcMgr::Delete(npcId);
		return true;
	}

	StaticNPCAID.CStaticNPCAID::Release();
	return npcId;
}


bool CNpcEvent::FuncDlgWriteStr(int npcID) // 4053-4062
{
	CNPC2ZMsg msg;
	msg.CMsg::SetMsgID(NPC2ZMSG_DLGWRITESTR);
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);

	this->EventLog("DlgWriteStr\n");
	this->CNpcEvent::Wait(DLG_WRITESTR, 180);
	return true;
}


bool CNpcEvent::FuncMDungeon_NpcName(const char* name, TokenData& out_ret) // 6692-6697
{
	char npcName[56] = {};
	wsprintfA(npcName, "%s_%s", name, m_dgIdent); //FIXME: deprecated API
	out_ret = npcName;
	return true;
}


bool CNpcEvent::FuncMDungeon_MapName(const char* map_name, TokenData& out_ret) // 6700-6710
{
	char mapName[16] = {};
	wsprintfA(mapName, "%s%s", m_dgIdent, map_name); //FIXME: deprecated API
	out_ret = mapName;
	return true;
}


bool CNpcEvent::FuncMDungeon_Npc(NpcSvrNpcInfo* npcInfo, bool isNpc) // 6715-6780
{
	char mapName[256] = {};
	char dg_mapName[256] = {};
	TokenData out_name;
	TokenData out_mapName;

	npcInfo->npcType = 1;
	this->CNpcEvent::FuncMDungeon_NpcName(npcInfo->name, out_name);
	npcInfo->name = out_name.TokenData::GetStr();
	this->CNpcEvent::FuncMDungeon_MapName(npcInfo->zone, out_mapName);
	SetMapName(dg_mapName, out_mapName.TokenData::GetStr());
	npcInfo->zone = dg_mapName;

	CStaticNPCAID StaticNPCAID = CStaticNPCAIDGenerator::GetObj()->CStaticNPCAIDGenerator::Alloc();
	int npcId = StaticNPCAID;
	if( npcId == 0 )
	{
		this->EventLog("FuncNpc: npc over aid\n");
		return false;
	}

	TrimLeft(mapName);
	TrimRight(mapName);
	TrimLeft(dg_mapName);
	TrimRight(dg_mapName);

	if( GetLocalServerID() != CMapInfoMgr::GetObj()->CMapInfoMgr::GetServerID(dg_mapName) )
	{
		m_curInitNpc = 0;
		return true;
	}

	CNpc* npc = g_npcSvr.CNpcSvr::GetStaticNpcMgr()->CNpcMgr::Add(npcId);
	if( npc == NULL )
	{
		this->EventLog("FuncNpc: NpcMgr's add() failed. addr: hex[%x] dec[%d]\n", m_interpreter.CInterpreter::GetCurPos(), m_interpreter.CInterpreter::GetCurPos());
		return false;
	}

	npc->CNpc::SetInfo(npcId, npcInfo);
	npc->CNpc::SetOnInit(true);
	m_curInitNpc = npcId;

	if( this->CScriptEventHandler::AddNpc(npcId, dg_mapName, npcInfo) == NULL )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "CNpcEvent::FuncNpc, Can't Not AddNpc, MapName[%s], NpcName[%s], Pos[%d, %d]", mapName, npcInfo->name, npcInfo->x, npcInfo->y);
		g_npcSvr.CNpcSvr::GetStaticNpcMgr()->CNpcMgr::Delete(npcId);
		return true;
	}

	StaticNPCAID.CStaticNPCAID::Release();
	return true;
}


CNpc* CNpcEvent::GetNpc()
{
	return m_npc;
}


void CNpcEvent::SetReserveTime(unsigned long t)
{
	m_reserveTime = t;
}


unsigned long CNpcEvent::GetReserveTime()
{
	return m_reserveTime;
}


bool CNpcEvent::IsGlobalEvent() const
{
	return ( m_npcId == 0 );
}


bool CNpcEvent::GetOnInit() const
{
	return m_OnInit;
}


void CNpcEvent::SetOnInit(bool oninit)
{
	m_OnInit = oninit;
}


int CNpcEvent::GetDeleteCount()
{
	return m_DeleteCount;
}


void CNpcEvent::AddDeleteCount()
{
	++m_DeleteCount;
}
