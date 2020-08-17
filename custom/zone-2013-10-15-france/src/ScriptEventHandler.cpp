#include "CharacterMgr.h"
#include "Enum.h" // EFST_*
#include "ScriptEventHandler.h"


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
	//TODO
	/*
	if( !g_EventLog )
		return;

	va_list va;
	va_start(va, str);

	char buf[1024];
	vsprintf(buf, str, va);

	if( g_wrIteNpcEventLog == true )
		CNpcEventLog::m_isSelf->Log(__FILE__, __LINE__, "%s", buf);
	*/
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
	return FUNC_RESULT_FAIL;
	//TODO
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
