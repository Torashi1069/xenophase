#include "CharacterMgr.h"
#include "CSectionLog.h"
#include "Enum.h" // EFST_*
#include "ScriptEventHandler.h"
#include "NpcServer/NpcSvr.h"


CScriptEventHandler::CScriptEventHandler()
{
	this->CScriptEventHandler::Init(0);
	m_interpreter.CInterpreter::RegisterHandler(this);
}


void CScriptEventHandler::Init(int ownerID)
{
	m_suspendType = -1;
	m_ownerID = ownerID;
	m_isQuit = false;
	m_suspendTime = 0;
	m_nParamSize = 0;
}


void CScriptEventHandler::Free()
{
	delete this;
}


void CScriptEventHandler::EventLog(char* str, ...)
{
	if( !g_EventLog )
		return;

	va_list va;
	va_start(va, str);

	char buf[1024];
	vsprintf(buf, str, va);

	if( g_wrIteNpcEventLog == TRUE )
		CNpcEventLog::GetObj()->CNpcEventLog::Log(__FILE__, __LINE__, "%s", buf);
}


unsigned int CScriptEventHandler::Proc(bool isOnce)
{
	for( int i = 0; ; ++i )
	{
		if( m_isQuit == true )
			return FUNC_RESULT_FAIL;

		if( m_suspendType != -1 )
		{
			if( time(NULL) > m_suspendTime )
			{
				this->CScriptEventHandler::Exit();
				return FUNC_RESULT_FAIL;
			}

			return FUNC_RESULT_SUCCESS;
		}

		if( !isOnce && i == 50 )
			return FUNC_RESULT_NOT_FOUND;

		if( !m_interpreter.CInterpreter::Proc() )
			return FUNC_RESULT_FAIL;
	}
}


void CScriptEventHandler::Exit()
{
	if( m_suspendType == FUNC_MENU || m_suspendType == FUNC_WAITDIALOG || m_suspendType == FUNC_CLOSEDIALOG || m_suspendType == FUNC_MENU2 )
		this->FuncCloseDialog(0);

	m_suspendType = -1;
	m_isQuit = true;
}


void CScriptEventHandler::OnMsg(unsigned long msgID, int par1, int par2, int par3)
{
	switch( msgID )
	{
	case CM_WAIT_DIALOG:
		this->CScriptEventHandler::CheckSuspendType(FUNC_WAITDIALOG);
	break;
	case CM_CLOSE_DIALOG:
		this->CScriptEventHandler::CheckSuspendType(FUNC_CLOSEDIALOG);
	break;
	case CM_MENU_LIST:
		if( this->CScriptEventHandler::CheckSuspendType(FUNC_MENU) )
		{
			int num = (int)par1;

			if( num == 255 )
			{
				this->EventLog("choosemenu cancel button \n");
				this->CScriptEventHandler::Exit();
			}
			else
			if( num > m_nParamSize || num <= 0 )
			{
				this->EventLog("over choosemenu select number\n");
				this->CScriptEventHandler::Exit();
				this->CScriptEventHandler::BanPlayer();
			}
			else
			{
				m_varMap->data["$case"] = num;
			}
		}
	break;
	case CM_INPUT_EDITDLGSTR:
		if( this->CScriptEventHandler::CheckSuspendType(FUNC_DLGWRITESTR) )
			m_inputstr = reinterpret_cast<const char*>(par1);
	break;
	case CM_PROGRESSBAR:
		this->CScriptEventHandler::CheckSuspendType(FUNC_PROGRESS_BAR);
	break;
	case CM_CLEAR_DIALOG:
		this->CScriptEventHandler::CheckSuspendType(FUNC_CLEARDIALOG);
	break;
	};
}


bool CScriptEventHandler::CheckSuspendType(int type)
{
	if( type != m_suspendType )
	{
		this->CScriptEventHandler::Exit();
		this->CScriptEventHandler::BanPlayer();
		return false;
	}

	m_suspendType = -1;

	return true;
}


void CScriptEventHandler::Suspend(int type, int delay)
{
	m_suspendType = type;
	m_suspendTime = time(NULL) + delay;
}


bool CScriptEventHandler::OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret) // 174-582
{
	switch( func )
	{
	case FUNC_ADDEXPTIME:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_SETEFFECTIVE, EFST_CASH_PLUSEXP, 60000 * parm[1].TokenData::GetNum(), parm[0].TokenData::GetNum(), 0);
		return true;
	break;
	case FUNC_SUBEXPTIME:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_SETEFFECTIVE, EFST_CASH_DEATHPENALTY, 60000 * parm[0].TokenData::GetNum(), 1, 0);
		return true;
	break;
	case FUNC_ADDRECEIVEITEM:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_SETEFFECTIVE, EFST_CASH_RECEIVEITEM, 60000 * parm[1].TokenData::GetNum(), parm[0].TokenData::GetNum(), 0);
		return true;
	break;
	case FUNC_ADVEQUIP_ISSUCCESSREFINERY:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncGetEquipIsSuccessRefinery(parm[0].TokenData::GetNum(), ret, true);
	break;
	case FUNC_GETADVEQUIPPERCENTREFINERY:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncGetEquipPercentRefinery(parm[0].TokenData::GetNum(), ret, true);
	break;
	case FUNC_PUTBOSS:
	{// 196-212
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 10) ) return false;
		const char* zone = parm[0].TokenData::GetStr();
		int x = parm[1].TokenData::GetNum();
		int y = parm[2].TokenData::GetNum();
		int w = parm[3].TokenData::GetNum();
		int h = parm[4].TokenData::GetNum();
		int num = parm[5].TokenData::GetNum();
		int mobId = parm[6].TokenData::GetNum();
		int regenMin = parm[7].TokenData::GetNum();
		int regenMax = parm[8].TokenData::GetNum();
		int regenType = parm[9].TokenData::GetNum();
		bool bUseTomb = ( parm.size() > 10 ) ? ( parm[10].TokenData::GetNum() > 0 ) : false;
		return this->CScriptEventHandler::FuncPutMob(zone, x, y, w, h, num, mobId, regenMin, regenMax, regenType, NULL, true, bUseTomb);
	}
	break;
	case FUNC_READBOOK:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncReadBook(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	break;
	case FUNC_GETWEAPONCLASS:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncGetWeaponClass(parm[0].TokenData::GetNum(), ret);
	break;
	case FUNC_GETEQUIPSLOTAMOUNT:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncGetEquipSlotAmount(parm[0].TokenData::GetNum(), ret);
	break;
	case FUNC_SETBUFF:
	{
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) return false;
		const char* EfstName = parm[0].TokenData::GetStr();
		const int Time = parm[1].TokenData::GetNum();
		const int Val1 = parm[2].TokenData::GetNum();
		const int Val2 = ( parm.size() > 3 ) ? parm[3].TokenData::GetNum() : 0;
		const int Val3 = ( parm.size() > 4 ) ? parm[4].TokenData::GetNum() : 0;
		return this->CScriptEventHandler::FuncSetBuff(EfstName, Time, Val1, Val2, Val3);
	}
	break;
	case FUNC_GETBUFFVALUE:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncGetBuffValue(parm[0].TokenData::GetStr(), ret);
	break;
	case FUNC_LOUDSPEAKER:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 6) ) return false;
		return this->CScriptEventHandler::FuncLoudSpeaker(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum(), parm[5].TokenData::GetStr());
	break;
	case FUNC_SETTARGETATTACKED_BUFF:
	case FUNC_RESETTARGETATTACKED_BUFF:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 5) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncTargetAttackedBuff(func, parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetStr(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum());
	break;
	case FUNC_GETMAPNAME:
		return this->CScriptEventHandler::FuncGetMapName(ret);
	break;
	case FUNC_GETPETRELATIONSHIP:
		return this->CScriptEventHandler::FuncGetPetRelationship(ret);
	break;
	case FUNC_ISEFFECTSTATUS:
		return this->CScriptEventHandler::FuncIsEffectStatus(parm[0].TokenData::GetNum(), ret);
	break;
	case FUNC_RAND:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncRand(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), ret);
	break;
	case FUNC_ISPCCAFE:
		return this->CScriptEventHandler::FuncIsPcCafe(ret);
	break;
	case FUNC_ISPREMIUMPCCAFE:
		return this->CScriptEventHandler::FuncIsPremiumPcCafe(ret);
	break;
	case FUNC_GETEXDEQUIPISSUCCESSREFINERY:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncGetExdEquipIsSuccessRefinery(parm[0].TokenData::GetNum(), false, ret);
	break;
	case FUNC_GETEXDADVEQUIPISSUCCESSREFINERY:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncGetExdEquipIsSuccessRefinery(parm[0].TokenData::GetNum(), true, ret);
	break;
	case FUNC_DOWNREFITEM:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncDownRefItem(parm[0].TokenData::GetNum(), 3);
	break;
	case FUNC_DOWNADVREFITEM:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncDownRefItem(parm[0].TokenData::GetNum(), 1);
	break;
	case FUNC_SUCCESSRANDREFITEM:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncSuccessRandomRefItem(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), false, ret);
	break;
	case FUNC_SUCCESSRANDADVREFITEM:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncSuccessRandomRefItem(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), true, ret);
	break;
	case FUNC_SET_ITEM_EFFECT:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncSetEffect(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	break;
	case FUNC_RESET_ITEM_EFFECT:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncReSetEffect(parm[0].TokenData::GetStr());
	break;
	case FUNC_OPEN_SEARCH_STORE_INFO:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncOpenSearchStorInfo(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum());
	break;
	case FUNC_RETURN:
		this->EventLog("return\n");
		return false;
	break;
	case FUNC_SETREADYMUTATIONHOMUN:
		return this->CScriptEventHandler::FuncSetReadyMutationHomun(ret);
	break;
	case FUNC_MUTATIONHOMUN:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncMutationHomon(parm[0].TokenData::GetNum(), ret);
	break;
	case FUNC_CHECKHOMUNLEVEL:
		return this->CScriptEventHandler::FuncCheckHomunLevel(ret);
	break;
	case FUNC_CHECKHOMUNMUTATION:
		return this->CScriptEventHandler::FuncCheckHomunMutation(ret);
	break;
	case FUNC_CHECKHOMUNCALL:
		return this->CScriptEventHandler::FuncCheckHomunCall(ret);
	break;
	case FUNC_RESETBUFF:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncResetBuff(parm[0].TokenData::GetStr());
	break;
	case FUNC_ADDSTATE_EFSTATK:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 5) ) return false;
		return this->CScriptEventHandler::FuncAddStateEfstATK(parm[0].TokenData::GetNum(), parm[1].TokenData::GetStr(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum());
	break;
	case FUNC_SUBSTATE_EFSTATK:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) return false;
		return this->CScriptEventHandler::FuncAddStateEfstATK(parm[0].TokenData::GetNum(), parm[1].TokenData::GetStr(), -parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), 0);
	break;
	case FUNC_START_COLLECTION:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncStartCollection(parm[0].TokenData::GetNum());
	break;
	case FUNC_MONTRANSFORM:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) return false;
		return this->CScriptEventHandler::FuncMontransform(parm[0].TokenData::GetNum(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetStr());
	break;
	case FUNC_DELETE_ALL_BODY_ITEM:
		return this->CScriptEventHandler::FuncDeleteAllBodyItem();
	break;
	case FUNC_INC_GLOBALVAR:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncIncGlobalVar(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	break;
	case FUNC_DEC_GLOBALVAR:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncDecGlobalVar(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	break;
	case FUNC_GET_AGITINVEST_MSG:
		return this->CScriptEventHandler::FuncGetAgitInvestMsg(ret);
	break;
	case FUNC_GET_AGIT_ECONOMY:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncGetAgitEconomy(parm[0].TokenData::GetStr(), ret);
	break;
	case FUNC_INC_AGIT_ECONOMY:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncIncAgitEconomy(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	break;
	case FUNC_DEC_AGIT_ECONOMY:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncDecAgitEconomy(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	break;
	case FUNC_EQ_MAKE:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 5) ) return false;
		return this->CScriptEventHandler::FuncEQMake(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum());
	break;
	case FUNC_EQ_CHECK_USER:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncEQCheckUser(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), ret);
	break;
	case FUNC_EQ_NOTIFY_ADMISSION:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncEQNotifyAdmission(parm[0].TokenData::GetStr());
	break;
	case FUNC_EQ_IS_READY:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncEQIsReady(parm[0].TokenData::GetStr(), ret);
	break;
	case FUNC_EQ_MOVE_TO_ROOM:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) return false;
		return this->CScriptEventHandler::FuncEQMoveToRoom(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum());
	break;
	case FUNC_EQ_RETURN_TO_PRE_SPACE:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncEQReturnToPreSpace(parm[0].TokenData::GetStr());
	break;
	case FUNC_EQ_MOVE_TO_LOBBY:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) return false;
		return this->CScriptEventHandler::FuncEQMoveToLobby(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr(), parm[2].TokenData::GetNum(), ret);
	break;
	case FUNC_LOBBY_MAKE:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncLobbyMake(parm[0].TokenData::GetStr());
	break;
	case FUNC_LOBBY_USER_COUNT:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncLobbyUserCount(parm[0].TokenData::GetStr(), ret);
	break;
	case FUNC_LOBBY_NOTIFY_ADMISSION:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncLobbyNotifyAdmission(parm[0].TokenData::GetStr());
	break;
	case FUNC_LOBBY_IS_READY:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncLobbyIsReady(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), ret);
	break;
	case FUNC_LOBBY_MOVE_TO_ROOM:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) return false;
		return this->CScriptEventHandler::FuncLobbyMoveToRoom(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum());
	break;
	case FUNC_LOBBY_RETURN_TO_PRE_SPACE:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncLobbyReturnToPreSpace(parm[0].TokenData::GetStr());
	break;
	case FUNC_LOBBY_INIT:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncLobbyInit(parm[0].TokenData::GetStr());
	break;
	case FUNC_ACTIVE_MONTRANSFORM:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncActiveMontransform(parm[0].TokenData::GetNum());
	break;
	case FUNC_DEACTIVE_MONTRANSFORM:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncDeActiveMontransform(parm[0].TokenData::GetNum());
	break;
	case FUNC_CHECK_JOB_GROUP:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncCheckJobGroup(parm[0].TokenData::GetNum(), ret);
	break;
	case FUNC_GET_BASE_JOB:
		return this->CScriptEventHandler::FuncGetBaseJob(ret);
	break;
	case FUNC_GET_CATEGORY_JOB:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false;
		return this->CScriptEventHandler::FuncGetCategoryJob(parm[0].TokenData::GetNum(), ret);
	break;
	case FUNC_EQ_JOB_CONTROL:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncEQJobControl(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	break;
	case FUNC_LOBBY_CAMPCODE:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 4) ) return false;
		return this->CScriptEventHandler::FuncLobbyCampCode(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum());
	break;
	case FUNC_INSERT_ALIVE_MEMBER:
		return this->CScriptEventHandler::FuncInsertAliveMember();
	break;
	case FUNC_EQ_USERINFO_INIT:
		return this->CScriptEventHandler::FuncEQUserInfoInit();
	break;
	case FUNC_IS_LOWLEVEL_SIEGE_JOB:
		return this->CScriptEventHandler::FuncIsLowLevelSiegeJob(ret);
	break;
	case FUNC_RESET_BUFF_LOWLEVEL_SIEGE:
		return this->CScriptEventHandler::FuncResetBuffLowLevelSiege();
	break;
	case FUNC_EQ_MOVE_TO_LOBBY_JOB_MATCHING:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) return false;
		return this->CScriptEventHandler::FuncEQMoveToLobbyJobMatching(parm[0].TokenData::GetStr(), parm[1].TokenData::GetStr(), parm[2].TokenData::GetStr(), ret);
	break;
	case FUNC_GET_YEAR:
		return this->CScriptEventHandler::FuncGetYear(ret);
	break;
	case FUNC_GET_MONTH:
		return this->CScriptEventHandler::FuncGetMonth(ret);
	break;
	case FUNC_GET_DAY:
		return this->CScriptEventHandler::FuncGetDay(ret);
	break;
	case FUNC_GET_WEEK_DAY:
		return this->CScriptEventHandler::FuncGetWeekDay(ret);
	break;
	case FUNC_MERGE_ITEM:
		return this->CScriptEventHandler::FuncMergeItem();
	break;
	case FUNC_STORE_V2:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return false;
		return this->CScriptEventHandler::FuncStoreV2(parm[0].TokenData::GetNum(), parm[1].TokenData::GetStr());
	break;
	case FUNC_IS_PREMIUM:
		return this->CScriptEventHandler::FuncIsPremium(ret);
	break;
	default:
	{
		short retcode = this->CScriptEventHandler::OnNpcFunc(func, parm, ret);
		if( retcode == FUNC_RESULT_SUCCESS )
			return true;
		else
		if( retcode == FUNC_RESULT_NOT_FOUND && this->CScriptEventHandler::OnItemFunc(func, parm, ret) == FUNC_RESULT_SUCCESS )
			return true;
		else
		{
			return false;
		}
	}
	break;
	};
}


short CScriptEventHandler::OnItemFunc(int func, std::deque<TokenData>& parm, TokenData& ret) // 585-988
{
	CMsg reqMsg;
	CMsg ansMsg;
	CITZMsg itemMsg;

	switch( func )
	{
	case FUNC_GETMERCENARYTOTALSUMMONNUM:
		reqMsg.CMsg::SetMsgID(FUNC_GETMERCENARYTOTALSUMMONNUM); //NOTE: type mismatch
		reqMsg.par1 = parm[0].TokenData::GetNum();

		CCharacterMgr::GetObj()->CCharacterMgr::GetVarFromPC(m_ownerID, &reqMsg, &ansMsg);
		ret = ansMsg.par1;

		this->EventLog("return value: %d\n", ret.num);
		return FUNC_RESULT_SUCCESS;
	break;
	case FUNC_GETMERCENARYFAITH:
		reqMsg.CMsg::SetMsgID(FUNC_GETMERCENARYFAITH); //NOTE: type mismatch
		reqMsg.par1 = parm[0].TokenData::GetNum();

		CCharacterMgr::GetObj()->CCharacterMgr::GetVarFromPC(m_ownerID, &reqMsg, &ansMsg);
		ret = ansMsg.par1;

		this->EventLog("return value: %d\n", ret.num);
		return FUNC_RESULT_SUCCESS;
	break;
	case FUNC_GET:
		reqMsg.CMsg::SetMsgID(MSG_REQVAR);
		reqMsg.par1 = parm[0].TokenData::GetNum();
		CCharacterMgr::GetObj()->CCharacterMgr::GetVar(m_ownerID, &reqMsg, &ansMsg);
		ret = ansMsg.par1;

		if( reqMsg.par1 == VAR_JOB )
		{
			if( g_mapBabyJob2Normal.find(ret.TokenData::GetNum()) != g_mapBabyJob2Normal.end() )
				ret = g_mapBabyJob2Normal[ret.TokenData::GetNum()];
		}

		this->EventLog("return value: %d\n", ret.num);
		return FUNC_RESULT_SUCCESS;
	break;
	case FUNC_GETPUREJOB:
		reqMsg.CMsg::SetMsgID(FUNC_GETPUREJOB); //NOTE: type mismatch

		CCharacterMgr::GetObj()->CCharacterMgr::GetVarFromPC(m_ownerID, &reqMsg, &ansMsg);
		ret = ansMsg.par1;

		this->EventLog("return value: %d\n", ret.num);
		return FUNC_RESULT_SUCCESS;
	break;
	case FUNC_GETSKILLLEVEL:
		reqMsg.CMsg::SetMsgID(FUNC_GETSKILLLEVEL); //NOTE: type mismatch
		reqMsg.par1 = parm[0].TokenData::GetNum();

		CCharacterMgr::GetObj()->CCharacterMgr::GetVarFromPC(m_ownerID, &reqMsg, &ansMsg);
		ret = ansMsg.par1;

		this->EventLog("return value: %d\n", ret.num);
		return FUNC_RESULT_SUCCESS;
	break;
	case FUNC_GETACTIVATED_SKILL:
	{
		if( !this->CScriptEventHandler::FuncGetActivatedSkill(ret) )
			return FUNC_RESULT_FAIL;

		return FUNC_RESULT_SUCCESS;
	}
	break;
	case FUNC_GETDEACTIVATED_SKILL:
	{
		if( !this->CScriptEventHandler::FuncGetDeactivatedSkill(ret) )
			return FUNC_RESULT_FAIL;

		return FUNC_RESULT_SUCCESS;
	}
	break;
	case FUNC_ISSUCCESSRUNEUSE:
	{
		int runeID = parm[0].TokenData::GetNum();
		TokenData ret;

		if( !this->CScriptEventHandler::FuncIsSuccessRuneUse(runeID, ret) )
			return FUNC_RESULT_FAIL;

		return FUNC_RESULT_SUCCESS;
	}
	break;
	case FUNC_INC:
	case FUNC_DEC:
	case FUNC_ENABLESKILL:
	case FUNC_DISABLESKILL:
	case FUNC_SKILL:
	case FUNC_HEALHP:
	case FUNC_HEALSP:
	case FUNC_HEALALL:
	case FUNC_CONDITION:
	case FUNC_CURE:
	case FUNC_ADDEXTPARAM:
	case FUNC_SUBEXTPARAM:
	case FUNC_SETMAKABLE_WPNLIST:
	case FUNC_SETMAKABLE_MTLLIST:
	case FUNC_RACE_ADD_DAMAGE:
	case FUNC_RACE_SUB_DAMAGE:
	case FUNC_ATTR_ADD_TOLERACE:
	case FUNC_ATTR_SUB_TOLERACE:
	case FUNC_RACE_ADD_TOLERACE:
	case FUNC_RACE_SUB_TOLERACE:
	case FUNC_ADDDAMAGE_PROPERTY:
	case FUNC_SUBDAMAGE_PROPERTY:
	case FUNC_ADDDAMAGE_SIZE:
	case FUNC_SUBDAMAGE_SIZE:
	case FUNC_ADDDAMAGE_NAME:
	case FUNC_SUBDAMAGE_NAME:
	case FUNC_ADDDAMAGE_SKID:
	case FUNC_SUBDAMAGE_SKID:
	case FUNC_ADDDAMAGE_CRI:
	case FUNC_SUBDAMAGE_CRI:
	case FUNC_ADDSTATE_MLEATK:
	case FUNC_SUBSTATE_MLEATK:
	case FUNC_ADDSTATE_MLEATTACKED:
	case FUNC_SUBSTATE_MLEATTACKED:
	case FUNC_ADDHEALPERCENT_ITEM:
	case FUNC_SUBHEALPERCENT_ITEM:
	case FUNC_ADDHEALAMOUNT_KILL:
	case FUNC_SUBHEALAMOUNT_KILL:
	case FUNC_INDESTRUCTIBLE_ARMOR:
	case FUNC_INDESTRUCTIBLE_WEAPON:
	case FUNC_ADD_STATE_TOLERACE:
	case FUNC_SUB_STATE_TOLERACE:
	case FUNC_BODY_ATTRIBUTE:
	case FUNC_SUB_RANGE_ATTACKDAMAGE:
	case FUNC_ADD_RANGE_ATTACKDAMAGE:
	case FUNC_NODISPELL:
	case FUNC_ADD_HPDRAIN:
	case FUNC_SUB_HPDRAIN:
	case FUNC_MAGICIMMUNE:
	case FUNC_NOJAMSTONE:
	case FUNC_ADD_SPDRAIN:
	case FUNC_SUB_SPDRAIN:
	case FUNC_ADD_MELEEATTACK_REFLECT:
	case FUNC_SUB_MELEEATTACK_REFLECT:
	case FUNC_PERFECT_DAMAGE:
	case FUNC_REINCARNATION:
	case FUNC_SUB_SPELLCASTTIME:
	case FUNC_ADD_SPELLCASTTIME:
	case FUNC_SPLASH_ATTACK:
	case FUNC_SUB_SPCONSUMPTION:
	case FUNC_ADD_SPCONSUMPTION:
	case FUNC_START_CAPTURE:
	case FUNC_INCUBATION:
	case FUNC_ADDATK_DAMAGEWEAPON:
	case FUNC_SUBATK_DAMAGEWEAPON:
	case FUNC_ADDATK_DAMAGEARMOR:
	case FUNC_SUBATK_DAMAGEARMOR:
	case FUNC_ADDRECEIVEITEM_RACE:
	case FUNC_SUBRECEIVEITEM_RACE:
	case FUNC_SETIGNOREDEFRACE:
	case FUNC_RESETIGNOREDEFRACE:
	case FUNC_SETIGNOREDEFCLASS:
	case FUNC_RESETIGNOREDEFCLASS:
	case FUNC_SET_DISAPPEARHPAMOUNT:
	case FUNC_RESET_DISAPPEARHPAMOUNT:
	case FUNC_SET_DISAPPEARSPAMOUNT:
	case FUNC_RESET_DISAPPEARSPAMOUNT:
	case FUNC_SETAUTOSPELL:
	case FUNC_ADDATK_COMARACE:
	case FUNC_SUBATK_COMARACE:
	case FUNC_ADDATK_COMA:
	case FUNC_SUBATK_COMA:
	case FUNC_SUBSPAMOUNT_ACTION:
	case FUNC_ADDSPAMOUNT_ACTION:
	case FUNC_SUBSPAMOUNT_ATTACK:
	case FUNC_ADDSPAMOUNT_ATTACK:
	case FUNC_ADDSPAMOUNT_ATKRACE:
	case FUNC_SUBSPAMOUNT_ATKRACE:
	case FUNC_ADDDESTROYSP_ATTACK:
	case FUNC_SUBDESTROYSP_ATTACK:
	case FUNC_ADDSPAMOUNT_KILLRACE:
	case FUNC_SUBSPAMOUNT_KILLRACE:
	case FUNC_ADDEXPPERCENT_KILLRACE:
	case FUNC_SUBEXPPERCENT_KILLRACE:
	case FUNC_CLASSADDDAMAGE:
	case FUNC_CLASSSUBDAMAGE:
	case FUNC_RACEADDDAMAGESELF:
	case FUNC_RACESUBDAMAGESELF:
	case FUNC_SETINVESTIGATE:
	case FUNC_RESETINVESTIGATE:
	case FUNC_MODIFYDEF_FRACTION:
	case FUNC_ADDGUIDEATTACK:
	case FUNC_SUBGUIDEATTACK:
	case FUNC_ADDCHANGEMONSTER:
	case FUNC_SUBCHANGEMONSTER:
	case FUNC_ADDCRIPERCENT_RACE:
	case FUNC_SUBCRIPERCENT_RACE:
	case FUNC_SETPUSHINGSKILL:
	case FUNC_RESETPUSHINGSKILL:
	case FUNC_GETZENY_RANGE:
	case FUNC_MULTICASTEFFECT:
	case FUNC_SETEXTPARAMTIME:
	case FUNC_SETRECEIVEZENY_KILL:
	case FUNC_ADDCRI_RANGEATK:
	case FUNC_SUBCRI_RANGEATK:
	case FUNC_ADDSTATE_RANGEATK:
	case FUNC_SUBSTATE_RANGEATK:
	case FUNC_ADDGUILDEXP:
	case FUNC_SETRECEIVEITEM_GROUP:
	case FUNC_ADDREFLECT_MAGIC:
	case FUNC_SUBREFLECT_MAGIC:
	case FUNC_ITEMCREATE:
	case FUNC_ADDGETITEM_KILL:
	case FUNC_SUBGETITEM_KILL:
	case FUNC_ADDPARAMETERVALUE:
	case FUNC_EVOLUTION_HOMUN:
	case FUNC_ADDPARAMTIME:
	case FUNC_COOKING:
	case FUNC_SUMMONNPC:
	case FUNC_PARTYCALL:
	case FUNC_USEBOSSPERCEPTION:
	case FUNC_SKILLTOME:
	case FUNC_WEAPONPROPERTY:
	case FUNC_MERCENARY_SUMMON:
	case FUNC_MERCENARY_HEALHP:
	case FUNC_MERCENARY_HEALSP:
	case FUNC_SUBMERCENARYFAITH:
	case FUNC_ADDMERCENARYFAITH:
	case FUNC_MERCENARY_CONDITION:
	case FUNC_ADDNEVERKNOCKBACK:
	case FUNC_SUBNEVERKNOCKBACK:
	case FUNC_ADDHEALVALUE:
	case FUNC_SUBHEALVALUE:
	case FUNC_ADDHPAMOUNT_MAGKILL:
	case FUNC_SUBHPAMOUNT_MAGKILL:
	case FUNC_ADDSPAMOUNT_MAGKILL:
	case FUNC_SUBSPAMOUNT_MAGKILL:
	case FUNC_ADDSPELLDELAY:
	case FUNC_SUBSPELLDELAY:
	case FUNC_ADDSPECIFICSPELLCASTTIME:
	case FUNC_SUBSPECIFICSPELLCASTTIME:
	case FUNC_ADDMDAMAGE_RACE:
	case FUNC_SUBMDAMAGE_RACE:
	case FUNC_ADDMDAMAGE_CLASS:
	case FUNC_SUBMDAMAGE_CLASS:
	case FUNC_SETIGNOREMDEFRACE:
	case FUNC_RESETIGNOREMDEFRACE:
	case FUNC_SETIGNOREMDEFCLASS:
	case FUNC_RESETIGNOREMDEFCLASS:
	case FUNC_SETHPAMOUNTTIME:
	case FUNC_RESETHPAMOUNTTIME:
	case FUNC_SETSPAMOUNTTIME:
	case FUNC_RESETSPAMOUNTTIME:
	case FUNC_SETIGNOREDEFRACE_PERCENT:
	case FUNC_RESETIGNOREDEFRACE_PERCENT:
	case FUNC_SETIGNOREDEFCLASS_PERCENT:
	case FUNC_RESETIGNOREDEFCLASS_PERCENT:
	case FUNC_SETAUTOWEAPON:
	case FUNC_RESETAUTOWEAPON:
	case FUNC_SETAUTOMWEAPON:
	case FUNC_RESETAUTOMWEAPON:
	case FUNC_SETAUTOATTACKED:
	case FUNC_RESETAUTOATTACKED:
	case FUNC_SETAUTOMATTACKED:
	case FUNC_RESETAUTOMATTACKED:
	case FUNC_RESETRECEIVEITEM_GROUP:
	case FUNC_ADDHEALMODIFYPERCENT:
	case FUNC_SUBHEALMODIFYPERCENT:
	case FUNC_SETHPPERCENTTIME:
	case FUNC_RESETHPPERCENTTIME:
	case FUNC_SETSPPERCENTTIME:
	case FUNC_RESETSPPERCENTTIME:
	case FUNC_ADDSTATE_MATK:
	case FUNC_SUBSTATE_MATK:
	case FUNC_ADDSTATE_MATTACKED:
	case FUNC_SUBSTATE_MATTACKED:
	case FUNC_ADDHPDRAIN_100:
	case FUNC_SUBHPDRAIN_100:
	case FUNC_ADDRECEIVEITEM_EQUIP:
	case FUNC_SUBRECEIVEITEM_EQUIP:
	case FUNC_ADDONLYJOBEXPTIME:
	case FUNC_SETSKILLAUTOSPELL:
	case FUNC_RESETSKILLAUTOSPELL:
	case FUNC_SETSKILLACTIVATE:
	case FUNC_RESETSKILLACTIVATE:
	case FUNC_ADDSTATE_SKID:
	case FUNC_SUBSTATE_SKID:
	case FUNC_SETAUTOSPELLMAGIC:
	case FUNC_RESETAUTOSPELLMAGIC:
	case FUNC_SETMAKABLERUNEITEMLIST:
	case FUNC_SETMAKABLENEWPOISONLIST:
	case FUNC_ADDMDAMAGE_NAME:
	case FUNC_SUBMDAMAGE_NAME:
	case FUNC_ADDRECEIVEITEM_NAME:
	case FUNC_SUBRECEIVEITEM_NAME:
	case FUNC_ADD_SFCT_CONSUME_AMOUNT:
	case FUNC_SUB_SFCT_CONSUME_AMOUNT:
	case FUNC_ADD_SFCT_CONSUME_PERMILL:
	case FUNC_SUB_SFCT_CONSUME_PERMILL:
	case FUNC_ADD_SFCT_EQUIP_AMOUNT:
	case FUNC_SUB_SFCT_EQUIP_AMOUNT:
	case FUNC_ADD_SFCT_EQUIP_PERMILL:
	case FUNC_SUB_SFCT_EQUIP_PERMILL:
	case FUNC_ADDATTRTOLERACE_DISREGARD:
	case FUNC_SUBATTRTOLERACE_DISREGARD:
	case FUNC_ADDSKILLSP:
	case FUNC_SUBSKILLSP:
	case FUNC_ADDSKILLDELAY:
	case FUNC_SUBSKILLDELAY:
	case FUNC_ADDSTATECASTTIME:
	case FUNC_SUBSTATECASTTIME:
	case FUNC_ADDSKILLMDAMAGE:
	case FUNC_SUBSKILLMDAMAGE:
	case FUNC_MODIFYMDEF_FRACTION:
	case FUNC_ADDALLDEF_FLUCTUATION:
	case FUNC_SUBALLDEF_FLUCTUATION:
	case FUNC_ADDALLMDEF_FLUCTUATION:
	case FUNC_SUBALLMDEF_FLUCTUATION:
	case FUNC_SETAUTOSPELL2:
	case FUNC_SETAUTOSPELL2_MLEATKED:
	case FUNC_SETAUTOSPELL2_MLEATKED_SHORT:
	case FUNC_SETAUTOSPELL2_MLEATKED_LONG:
	case FUNC_SETAUTOSPELL2_MAGATKED:
	case FUNC_SETAUTOSPELL2_MLEATK:
	case FUNC_SETAUTOSPELL2_RANGEATK:
	case FUNC_RESETAUTOSPELL2:
	case FUNC_RESETAUTOSPELL2_MLEATKED:
	case FUNC_RESETAUTOSPELL2_MLEATKED_SHORT:
	case FUNC_RESETAUTOSPELL2_MLEATKED_LONG:
	case FUNC_RESETAUTOSPELL2_MAGATKED:
	case FUNC_RESETAUTOSPELL2_MLEATK:
	case FUNC_RESETAUTOSPELL2_RANGEATK:
	case FUNC_PAUSEAUTOSPELL2:
	case FUNC_PAUSEAUTOSPELL2_MLEATKED:
	case FUNC_PAUSEAUTOSPELL2_MLEATKED_SHORT:
	case FUNC_PAUSEAUTOSPELL2_MLEATKED_LONG:
	case FUNC_PAUSEAUTOSPELL2_MAGATKED:
	case FUNC_PAUSEAUTOSPELL2_MLEATK:
	case FUNC_PAUSEAUTOSPELL2_RANGEATK:
	case FUNC_RESUMEAUTOSPELL2:
	case FUNC_RESUMEAUTOSPELL2_MLEATKED:
	case FUNC_RESUMEAUTOSPELL2_MLEATKED_SHORT:
	case FUNC_RESUMEAUTOSPELL2_MLEATKED_LONG:
	case FUNC_RESUMEAUTOSPELL2_MAGATKED:
	case FUNC_RESUMEAUTOSPELL2_MLEATK:
	case FUNC_RESUMEAUTOSPELL2_RANGEATK:
		;
	break;
	default:
		return FUNC_RESULT_NOT_FOUND;
	break;
	};

	int nParm = parm.size();

	itemMsg.CMsg::SetMsgID(func);
	if( nParm > 0 ) itemMsg.par1 = parm[0].TokenData::GetNum();
	if( nParm > 1 ) itemMsg.par2 = parm[1].TokenData::GetNum();
	if( nParm > 2 ) itemMsg.par3 = parm[2].TokenData::GetNum();
	if( nParm > 3 ) itemMsg.par4 = parm[3].TokenData::GetNum();
	if( nParm > 4 ) itemMsg.par5 = parm[4].TokenData::GetNum();
	CCharacterMgr::GetObj()->CCharacterMgr::SendCommand(m_ownerID, &itemMsg);

	return FUNC_RESULT_SUCCESS;
}


short CScriptEventHandler::OnNpcFunc(int func, std::deque<TokenData>& parm, TokenData& ret) // 991-1092
{
	switch( func )
	{
	case FUNC_STORE:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_NOTIFY_STOREDITEM, 0, 0, 0, 0);
		return FUNC_RESULT_SUCCESS;
	break;
	case FUNC_RESETSKILL:
		return this->CScriptEventHandler::FuncResetSkill();
	break;
	case FUNC_DIALOG:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return FUNC_RESULT_FAIL;
		return this->FuncDialog(parm[0].TokenData::GetStr(), 0);
	break;
	case FUNC_NAVIGATION_ACTIVE:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 6) ) return FUNC_RESULT_FAIL;
		return this->FuncNavigationActive(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum(), parm[5].TokenData::GetNum(), parm[6].TokenData::GetStr());
	break;
	case FUNC_GETPREMIUMCAMPAIGN_GRADE:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return FUNC_RESULT_FAIL;
		return this->FuncGetPremiumCampaignGrade(parm[0].TokenData::GetNum(), ret, 0);
	break;
	case FUNC_CLOSEDIALOG:
		return this->FuncCloseDialog(0);
	break;
	case FUNC_CLEARDIALOG:
		return this->FuncClearDialog(0);
	break;
	case FUNC_WAITDIALOG:
		return this->FuncWaitDialog(0);
	break;
	case FUNC_SHOW_IMAGE:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return FUNC_RESULT_FAIL;
		return this->CScriptEventHandler::FuncShowImage(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum());
	break;
	case FUNC_PCNAME:
		return this->CScriptEventHandler::FuncPcName(ret);
	break;
	case FUNC_DLGWRITESTR:
		return this->FuncDlgWriteStr(0);
	break;
	case FUNC_INPUTSTR:
		return this->CScriptEventHandler::FuncInputStr(ret);
	break;
	case FUNC_BROADCASTSERVER:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 6) ) return FUNC_RESULT_FAIL;
		return this->CScriptEventHandler::FuncBroadcastServer(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum(), parm[3].TokenData::GetNum(), parm[4].TokenData::GetNum(), parm[5].TokenData::GetStr());
	break;
	case FUNC_MENU:
	case FUNC_MENU2:
		return this->FuncMenu(parm, 0);
	break;
	case FUNC_MOVETO:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 3) ) return FUNC_RESULT_FAIL;
		return this->FuncMapMove(parm[0].TokenData::GetStr(), parm[1].TokenData::GetNum(), parm[2].TokenData::GetNum());
	break;
	case FUNC_GETEQUIP_WEAPONLV:
//		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return false; //FIXME: verify parameter count
		return this->CScriptEventHandler::FuncGetEquipWeaponLv(parm[0].TokenData::GetNum(), ret);
	break;
	case FUNC_SHOWEFFECT:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return FUNC_RESULT_FAIL;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_SHOWEFFECT, (int)parm[1].TokenData::GetNum(), 0, 0, 0);
		return FUNC_RESULT_SUCCESS;
	break;
	case FUNC_SHOWSCRIPT:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return FUNC_RESULT_FAIL;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_SHOWSCRIPT, (int)parm[1].TokenData::GetStr(), 0, 0, 0);
		return FUNC_RESULT_SUCCESS;
	break;
	case FUNC_SHOWEMOTION:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 2) ) return FUNC_RESULT_FAIL;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_EMOTION, (int)parm[1].TokenData::GetNum(), 0, 0, 0);
		return FUNC_RESULT_SUCCESS;
	break;
	case FUNC_SETEFFECTSTATUS:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return FUNC_RESULT_FAIL;
		return this->FuncSetEffectStatus(parm[0].TokenData::GetNum());
	break;
	case FUNC_PLAYBGM:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return FUNC_RESULT_FAIL;
		return this->CScriptEventHandler::FuncPlayBGM(parm[0].TokenData::GetStr());
	break;
	case FUNC_STRIPTPC2:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return FUNC_RESULT_FAIL;
		return this->CScriptEventHandler::FuncStriptPC2(parm[0].TokenData::GetNum());
	break;
	case FUNC_GETEQUIP_NAME:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return FUNC_RESULT_FAIL;
		return this->CScriptEventHandler::FuncGetEquipName(parm[0].TokenData::GetNum(), ret);
	break;
	case FUNC_GETEQUIP_ITEMIDX:
		if( !this->CScriptEventHandler::CheckFixedVarNum(parm, 1) ) return FUNC_RESULT_FAIL;
		return this->CScriptEventHandler::FuncGetEquipItemIdx(parm[0].TokenData::GetNum(), ret);
	break;
	default:
		return FUNC_RESULT_NOT_FOUND;
	break;
	};
}


bool CScriptEventHandler::CheckFixedVarNum(std::deque<TokenData>& parm, int n)
{
	int size = parm.size();
	if( n > size )
	{
		this->EventLog("CNpcEvent::CheckFixedVarNum %d < %d\n", size, n);
		return false;
	}

	return true;
}


void CScriptEventHandler::BanPlayer()
{
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_ownerID, CM_BAN, 0, 0, 0, 0);
	this->EventLog("BanPlayer %d \n", m_ownerID);
}


////////////////////////////////////////


void CScriptEventHandler::OnError(const char* str)
{
}


int CScriptEventHandler::GetOwnerID()
{
	return m_ownerID;
}


bool CScriptEventHandler::RunInterpreter(CBinBuf* binBuf, int beginPos)
{
	return m_interpreter.CInterpreter::Run(binBuf, beginPos, false);
}
