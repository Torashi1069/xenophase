#include "CharacterMgr.h"
#include "ITPMgr.h"
#include "ItemServer/CItemScriptEventHandler.h"
#include "ItemServer/specialitemmgr.h"


CItemScriptEventHandler::CItemScriptEventHandler()
: m_Identity(0)
{
}


CItemScriptEventHandler::~CItemScriptEventHandler()
{
}


void CItemScriptEventHandler::Set(CSpecialItemMgr* ptrItemMgr, int* pParam, int CharId, int scanItem, const unsigned int in_Identity)
{
	m_pParam = pParam;
	m_nScanItem = scanItem;
	m_ptrItemMgr = ptrItemMgr;
	m_CharId = CharId;
	m_Identity = in_Identity;
	this->CScriptEventHandler::Init(CharId);
}


void CItemScriptEventHandler::Free()
{
	g_itemHandlerPool.CMemoryMgr<CItemScriptEventHandler>::Free(this);
}


bool CItemScriptEventHandler::OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret)
{
	switch( func )
	{
	case FUNC_SUMMON:
	case FUNC_CREATEITEM:
	case FUNC_LOSTITEM:
	case FUNC_CREATEPACKAGE:
	{
		CITZMsg itemMsg;
		itemMsg.CMsg::SetMsgID(func);
		itemMsg.par1 = m_nScanItem;
		CCharacterMgr::GetObj()->CCharacterMgr::SendCommand(m_ownerID, &itemMsg);
		return true;
	}
	break;
	case FUNC_GETREFINELEVEL:
	{
		CMsg reqMsg;
		reqMsg.CMsg::SetMsgID(MSG_REQREFINELEVEL);
		reqMsg.par1 = parm[0].TokenData::GetNum();

		if( w_cardItem != 0 )
		{
			CITP* cardItp = g_itpMgr.CITPMgr::GetITP(w_cardItem);
			if( cardItp != NULL )
			{
				unsigned short loc = cardItp->GetLocation(JT_NOVICE);
				if( loc == LOCATION_HEAD3 )
					reqMsg.par1 = 10;
				else
				if( loc == LOCATION_HEAD2 )
					reqMsg.par1 = 9;
				else
				if( loc == LOCATION_HEAD )
					reqMsg.par1 = 1;
			}
		}

		CMsg ansMsg;
		CCharacterMgr::GetObj()->CCharacterMgr::GetVar(m_ownerID, &reqMsg, &ansMsg);
		ret = ansMsg.par1;
		return true;
	}
	break;
	case FUNC_ADDDAMAGETM_PROP:
	case FUNC_SUBSAMAGETM_PROP:
	{
		int nparm = parm.size();

		CITZMsg msg;
		msg.CMsg::SetMsgID(func);
		msg.m_ITID = m_nScanItem;
		if( nparm > 0 ) msg.par1 = parm[0].TokenData::GetNum();
		if( nparm > 1 ) msg.par2 = parm[1].TokenData::GetNum();
		if( nparm > 2 ) msg.par3 = parm[2].TokenData::GetNum();
		if( nparm > 3 ) msg.par4 = parm[3].TokenData::GetNum();
		if( nparm > 4 ) msg.par5 = parm[4].TokenData::GetNum();
		CCharacterMgr::GetObj()->CCharacterMgr::SendCommand(m_ownerID, &msg);
		return true;
	}
	break;
	case FUNC_GETLOCATION:
	{
		CITZMsg msg;
		msg.CMsg::SetMsgID(FUNC_GETLOCATION);
		msg.par1 = w_index;
		CCharacterMgr::GetObj()->CCharacterMgr::SendCommand(m_ownerID, &msg);
		ret = msg.par2;
		return true;
	}
	break;
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
	{
		{
		TokenData a;
		a = (int)m_Identity;
		parm.push_back(a);
		}
		return this->CScriptEventHandler::OnFunc(func, parm, ret);
	}
	break;
	default:
	{
		return this->CScriptEventHandler::OnFunc(func, parm, ret);
	}
	break;
	};
}


void CItemScriptEventHandler::OnError(const char* str)
{
}


bool CItemScriptEventHandler::Run(CBinBuf* binBuf, int beginPos)
{
	return m_interpreter.CInterpreter::Run(binBuf, beginPos, false);
}
