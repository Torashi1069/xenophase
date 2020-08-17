#include "CharacterMgr.h"
#include "CZoneProcessLocalConfigMgr.h"
#include "Enum.h" // EFST_NOACTION_WAIT
#include "GVar.h"
#include "ObjectRecycleMgr.h"
#include "PC.h"
#include "AsyncDBWork/ElementalCreateADBWork.h"
#include "AsyncDBWork/ElementalDeleteADBWork.h"
#include "AsyncDBWork/LoadCartADBWork.h"
#include "AsyncDBWork/LoadStoreADBWork.h"
#include "AsyncDBWork/LoadWarpInfoADBWork.h"
#include "AsyncDBWork/LogonPermitADBWork.h"
#include "AsyncDBWork/MercenaryCreateADBWork.h"
#include "AsyncDBWork/MercenaryDeleteADBWork.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/NAsyncDBThread.h"
#include "AsyncDBWork/NASyncDBWork.h"
#include "AsyncDBWork/NIDAllocator.h"
#include "AsyncDBWork/NInterMessageSystem.h"
#include "AsyncDBWork/SaveAllADBWork.h"
#include "AsyncDBWork/SaveCartADBWork.h"
#include "AsyncDBWork/SaveSkillADBWork.h"
#include "AsyncDBWork/SaveStoreADBWork.h"
#include "Player/AmpLogonPermit.h"
#include "shared/NCriticalErrorLog.h"


/// singleton instance
NAsyncDBMgr*& NAsyncDBMgr::m_cpSelf = VTOR<NAsyncDBMgr*>(DetourFindFunction(EXEPATH(), "NAsyncDBMgr::m_cpSelf"));
CObjectRecycleMgr<CLoadCartADBWork>*& CObjectRecycleMgr<CLoadCartADBWork>::m_cpSelf = VTOR<CObjectRecycleMgr<CLoadCartADBWork>*>(DetourFindFunction(EXEPATH(), "CObjectRecycleMgr<CLoadCartADBWork>::m_cpSelf"));
CObjectRecycleMgr<CLoadStoreADBWork>*& CObjectRecycleMgr<CLoadStoreADBWork>::m_cpSelf = VTOR<CObjectRecycleMgr<CLoadStoreADBWork>*>(DetourFindFunction(EXEPATH(), "CObjectRecycleMgr<CLoadStoreADBWork>::m_cpSelf"));
CObjectRecycleMgr<CLogonPermitADBWork>*& CObjectRecycleMgr<CLogonPermitADBWork>::m_cpSelf = VTOR<CObjectRecycleMgr<CLogonPermitADBWork>*>(DetourFindFunction(EXEPATH(), "CObjectRecycleMgr<CLogonPermitADBWork>::m_cpSelf"));
CObjectRecycleMgr<CSaveAllADBWork>*& CObjectRecycleMgr<CSaveAllADBWork>::m_cpSelf = VTOR<CObjectRecycleMgr<CSaveAllADBWork>*>(DetourFindFunction(EXEPATH(), "CObjectRecycleMgr<CSaveAllADBWork>::m_cpSelf"));
CObjectRecycleMgr<CSaveCartADBWork>*& CObjectRecycleMgr<CSaveCartADBWork>::m_cpSelf = VTOR<CObjectRecycleMgr<CSaveCartADBWork>*>(DetourFindFunction(EXEPATH(), "CObjectRecycleMgr<CSaveCartADBWork>::m_cpSelf"));
CObjectRecycleMgr<CSaveStoreADBWork>*& CObjectRecycleMgr<CSaveStoreADBWork>::m_cpSelf = VTOR<CObjectRecycleMgr<CSaveStoreADBWork>*>(DetourFindFunction(EXEPATH(), "CObjectRecycleMgr<CSaveStoreADBWork>::m_cpSelf"));


NAsyncDBMgr::NAsyncDBMgr(const std::string in_ODBCConnectionStr)
: NXObject("Thread"), NXInter(),
  m_MessageQueue(), m_WorkThreadContainer(), m_WorkThreadGroupID(0), m_cpRequestCircularQueue(NULL), m_cpReponseCircularQueue(NULL), m_bOK(false)
{
	NInterMessageSystem::GetObj()->NInterMessageSystem::Insert(this->NXObject::GetMyID(), this);

	if( this->NAsyncDBMgr::Create(in_ODBCConnectionStr) )
		m_bOK = true;
}


NAsyncDBMgr::~NAsyncDBMgr()
{
	this->NAsyncDBMgr::Destory();

	NInterMessageSystem::GetObj()->NInterMessageSystem::Remove(this->NXObject::GetMyID(), this);
}


const bool NAsyncDBMgr::isOK() const
{
	return m_bOK;
}


void NAsyncDBMgr::Destory()
{
	this->NAsyncDBMgr::Stop();

	for( WORKTHREDCONTAINERITOR itor = m_WorkThreadContainer.begin(); itor != m_WorkThreadContainer.end(); ++itor )
		delete *itor;

	if( m_cpRequestCircularQueue != NULL )
	{
		delete m_cpRequestCircularQueue;
		m_cpRequestCircularQueue = NULL;
	}

	if( m_cpReponseCircularQueue != NULL )
	{
		delete m_cpReponseCircularQueue;
		m_cpReponseCircularQueue = NULL;
	}
}


bool NAsyncDBMgr::Create(const std::string in_ODBCConnectionStr)
{
	m_cpRequestCircularQueue = new NAsyncDBRequestCircularQueue(15000);
	if( m_cpRequestCircularQueue == NULL )
		return false;

	if( !m_cpRequestCircularQueue->NAsyncDBRequestCircularQueue::isOK() )
	{
		delete m_cpRequestCircularQueue;
		m_cpRequestCircularQueue = NULL;
		return false;
	}

	m_cpReponseCircularQueue = new NAsyncDBResponseCircularQueue("async db response circular queue", 15000);
	if( m_cpReponseCircularQueue == NULL )
		return false;

	if( !m_cpReponseCircularQueue->NAsyncDBResponseCircularQueue::isOK() )
	{
		delete m_cpReponseCircularQueue;
		m_cpReponseCircularQueue = NULL;
		return false;
	}

	if( !NIDAllocator::GetObj()->NIDAllocator::RegisterGroup("NAsyncDBThread", 1, 100) )
		return false;

	m_WorkThreadGroupID = NIDAllocator::GetObj()->NIDAllocator::GetGroupID("NAsyncDBThread");
	if( m_WorkThreadGroupID == 0 )
		return false;

	for( int WorkThreadNum = 1; WorkThreadNum <= CGVar::GetObj()->CGVar::GetAsyncDBThreadNum(); ++WorkThreadNum )
	{
		std::string ODBCConnectionStr = in_ODBCConnectionStr;

		char AppName[1024] = {};
		_snprintf_s(AppName, countof(AppName), _TRUNCATE, "APP=ZSVR(%04d)-%02d;", CZoneProcessLocalConfigMgr::GetObj()->CZoneProcessLocalConfigMgr::GetZSID(), WorkThreadNum);

		ODBCConnectionStr += AppName;

		NAsyncDBThread* cpThread = new NAsyncDBThread(this->NXObject::GetMyID(), ODBCConnectionStr, m_cpRequestCircularQueue, m_cpReponseCircularQueue);
		if( cpThread == NULL )
			return false;

		if( !cpThread->NAsyncDBThread::isOK() )
		{
			delete cpThread;
			return false;
		}

		m_WorkThreadContainer.push_back(cpThread);
	}

	return true;
}


int NAsyncDBMgr::GetRequestWorkNum()
{
	return m_cpRequestCircularQueue->NAsyncDBRequestCircularQueue::GetSize();
}


bool NAsyncDBMgr::CreateInstance(const std::string in_ODBCConnectionStr)
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new NAsyncDBMgr(in_ODBCConnectionStr);
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->NAsyncDBMgr::isOK() )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void NAsyncDBMgr::DestoryInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


NAsyncDBMgr* NAsyncDBMgr::GetObj() /// @custom
{
	return m_cpSelf;
}


void NAsyncDBMgr::PostInterMessage(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam)
{
	if( this == NULL )
		return;

	m_MessageQueue.Post(in_FromInter, in_ExecTimeMS, in_Msg, in_wParam, in_lParam);
}


bool NAsyncDBMgr::PeekInterMessage(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove)
{
	return m_MessageQueue.Peek(in_ExecTimeMS, out_FromInter, out_Msg, out_wParam, out_lParam, in_bRemove);
}


bool NAsyncDBMgr::Start()
{
	for( WORKTHREDCONTAINERITOR itor = m_WorkThreadContainer.begin(); itor != m_WorkThreadContainer.end(); ++itor )
		if( !(*itor)->NAsyncDBThread::Start() )
			return false;

	return true;
}


void NAsyncDBMgr::Stop()
{
	if( this == NULL )
		return;

	for( WORKTHREDCONTAINERITOR itor = m_WorkThreadContainer.begin(); itor != m_WorkThreadContainer.end(); ++itor )
		(*itor)->NAsyncDBThread::Stop();
}


bool NAsyncDBMgr::RequestWork(NAsyncDBWork* in_cpWork)
{
	return m_cpRequestCircularQueue->NAsyncDBRequestCircularQueue::Write3(in_cpWork);
}


NAsyncDBWork* NAsyncDBMgr::ResponseWork()
{
	NAsyncDBWork* pCompleteWork = NULL;
	if( !m_cpReponseCircularQueue->Read(pCompleteWork) )
		return NULL;

	return pCompleteWork;
}


void NAsyncDBMgr::ProcessMessage()
{
	unsigned int FromInter = 0;
	int Message = 0;
	int wParam = 0;
	int lParam = 0;

	if( this->PeekInterMessage(GetTickCount(), FromInter, Message, wParam, lParam, true) != true )
		return;

	if( m_WorkThreadGroupID != NIDAllocator::GetObj()->NIDAllocator::GetGroupID(FromInter) )
		return;

	switch( Message )
	{
	case NXInter::NINTERMSG_RES_CONNECT_FAIL:
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "AsyncDBWorkThread(0x%X) database connect fail", FromInter);
		NInterMessageSystem::GetObj()->NInterMessageSystem::PostInterMessage(FromInter, this->NXObject::GetMyID(), GetTickCount() + 1000 * rand() % 10, NXInter::NINTERMSG_REQ_CONNECT, 0, 0);
	break;
	case NXInter::NINTERMSG_NOTIFY_DISCONNECT:
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "AsyncDBWorkThread(0x%X) found database disconnect", FromInter);
		NInterMessageSystem::GetObj()->NInterMessageSystem::PostInterMessage(FromInter, this->NXObject::GetMyID(), GetTickCount() + 1000 * rand() % 10, NXInter::NINTERMSG_REQ_CONNECT, 0, 0);
	break;
	case NXInter::NINTERMSG_RES_CONNECT_SUCCESS:
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "AsyncDBWorkThread(0x%X) database connect success", FromInter);
		NInterMessageSystem::GetObj()->NInterMessageSystem::PostInterMessage(FromInter, this->NXObject::GetMyID(), GetTickCount() + 1000 * rand() % 10, NXInter::NINTERMSG_REQ_CONNECT, 0, 0);
	break;
	case NXInter::NINTERMSG_NOTIFY_ERROR_RESQUEUE_WRITE:
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "AsyncDBWorkThread(0x%X) response queue error", FromInter);
		MessageBoxA(NULL, __FILE__, "NAsyncDBMgr", MB_OK);

		NAsyncDBWork* work = reinterpret_cast<NAsyncDBWork*>(wParam);
		delete work;
	}
	break;
	};
}


void NAsyncDBMgr::ProcessDBWork(NAsyncDBWork* const in_ADBWork)
{
	switch( in_ADBWork->NAsyncDBWork::GetType() )
	{
	case NAsyncDBWork::TYPE_MERCENARY_DELETE:
		this->NAsyncDBMgr::ProcessDBWork_MERCENARY_DELETE(static_cast<CMercenaryDeleteADBWork* const>(in_ADBWork));
	break;
	case NAsyncDBWork::TYPE_MERCENARY_CREATE:
		this->NAsyncDBMgr::ProcessDBWork_MERCENARY_CREATE(static_cast<CMercenaryCreateADBWork* const>(in_ADBWork));
	break;
	case NAsyncDBWork::TYPE_SAVE_CART:
		this->NAsyncDBMgr::ProcessDBWork_SAVE_CART(static_cast<CSaveCartADBWork* const>(in_ADBWork));
	break;
	case NAsyncDBWork::TYPE_LOAD_CART:
		this->NAsyncDBMgr::ProcessDBWork_LOAD_CART(static_cast<CLoadCartADBWork* const>(in_ADBWork));
	break;
	case NAsyncDBWork::TYPE_SAVE_STORE:
		this->NAsyncDBMgr::ProcessDBWork_SAVE_STORE(static_cast<CSaveStoreADBWork* const>(in_ADBWork));
	break;
	case NAsyncDBWork::TYPE_LOAD_STORE:
		this->NAsyncDBMgr::ProcessDBWork_LOAD_STORE(static_cast<CLoadStoreADBWork* const>(in_ADBWork));
	break;
	case NAsyncDBWork::TYPE_SAVE_SKILL:
		this->NAsyncDBMgr::ProcessDBWork_SAVE_SKILL(static_cast<CSaveSkillADBWork* const>(in_ADBWork));
	break;
	case 6: //TYPE_SAVE_CHARACTERINFO
	break;
	case 5: //TYPE_SAVE_BODYITEM
	break;
	case NAsyncDBWork::TYPE_SAVE_ALL:
		this->NAsyncDBMgr::ProcessDBWork_SAVE_ALL(static_cast<CSaveAllADBWork* const>(in_ADBWork));
	break;
	case NAsyncDBWork::TYPE_LOGON_PERMIT:
		this->NAsyncDBMgr::ProcessDBWork_LogonPermit(static_cast<CLogonPermitADBWork* const>(in_ADBWork));
	break;
	case 2: //TYPE_ZIP
	break;
	case 1: //TYPE_UNZIP
	break;
	case 0: //TYPE_NONE
	break;
	case 14: //TYPE_SAVE_EFFECTIVEINFO
//		this->NAsyncDBMgr::ProcessDBWork_SAVE_EFFECTIVEINFO(static_cast<CSaveEffectiveInfoADBWork* const>(in_ADBWork)); //TODO
	break;
	case 15: //TYPE_SAVE_QUESTEVENT
	break;
	case 16: //TYPE_SAVE_BATTLEFIELD
	break;
	case 17: //TYPE_SKILL3RD_UPDATE
//		this->NAsyncDBMgr::ProcessDBWork_Skill3rdUpdate(static_cast<CSkill3rdUpdateADBWork* const>(in_ADBWork)); //TODO
	break;
	case 19: //TYPE_SKILL3RD_RESET
//		this->NAsyncDBMgr::ProcessDBWork_Skill3rdReset(static_cast<CSkill3rdResetADBWork* const>(in_ADBWork)); //TODO
	break;
	case 18: //TYPE_SKILL3RD_DELETE
	break;
	case 20: //TYPE_JOB_CHANGE
//		this->NAsyncDBMgr::ProcessDBWork_ChangeJob(static_cast<CChangeJobADBWork* const>(in_ADBWork)); //TODO
	break;
	case 21: //TYPE_JOB_TRANSCENDENT
//		this->NAsyncDBMgr::ProcessDBWork_TranscendentJob(static_cast<CTranscendentJobADBWork* const>(in_ADBWork)); //TODO
	break;
	case 22: //TYPE_EFFECT3RD_DELETE
	break;
	case 23: //TYPE_EFFECT3RD_UPDATEALL
//		this->NAsyncDBMgr::ProcessDBWork_Effect3rdUpdateAll(static_cast<CEffect3rdUpdateAllADBWork* const>(in_ADBWork)); //TODO
	break;
	case 24: //TYPE_LOAD_CHARNAME
//		this->NAsyncDBMgr::ProcessDBWork_LoadCharName(static_cast<CLoadCharNameADBWork* const>(in_ADBWork)); //TODO
	break;
	case 25: //TYPE_PARTY_BOOKING_INSERT
	break;
	case 26: //TYPE_PARTY_BOOKING_DELETE
	break;
	case 27: //TYPE_PARTY_BOOKING_UPDATE
	break;
	case NAsyncDBWork::TYPE_ELEMENTAL_CREATE:
		this->NAsyncDBMgr::ProcessDBWork_Elemenal_Create(static_cast<CElementalCreateADBWork* const>(in_ADBWork));
	break;
	case NAsyncDBWork::TYPE_ELEMENTAL_DELETE:
		this->NAsyncDBMgr::ProcessDBWork_Elemenal_Delete(static_cast<CElementalDeleteADBWork* const>(in_ADBWork));
	break;
	case 30: //TYPE_INSERT_QUEST
	break;
	case 31: //TYPE_ERASE_QUEST
	break;
	case 32: //TYPE_UPDATE_QUEST
	break;
	case 33: //TYPE_HOMUNSKILL_UPDATE
	break;
	case 34: //TYPE_HOMUNDATA_SAVE
	break;
	case 35: //TYPE_INSERT_IRINVENTORY
	break;
	case 36: //TYPE_DELETE_IRINVENTORY
	break;
	case 37: //TYPE_IRMAIL_SEND
	break;
	case 38: //TYPE_INSERT_COUPLE
//		this->NAsyncDBMgr::ProcessDBWork_InsertCouple(static_cast<CInsertCoupleADBWork* const>(in_ADBWork)); //TODO
	break;
	case 40: //TYPE_INSERT_FAMILY
//		this->NAsyncDBMgr::ProcessDBWork_InsertFamilyADBWork(static_cast<CInsertFamilyADBWork* const>(in_ADBWork)); //TODO
	break;
	case 41: //TYPE_DELETE_FAMILY
//		this->NAsyncDBMgr::ProcessDBWork_DeleteFamilyADBWork(static_cast<CDeleteFamilyADBWork* const>(in_ADBWork)); //TODO
	break;
	case 39: //TYPE_DELETE_COUPLE
//		this->NAsyncDBMgr::ProcessDBWork_DeleteCoupleDBWork(static_cast<CDeleteCoupleADBWork* const>(in_ADBWork)); //TODO
	break;
	case 47: //TYPE_LOAD_WARPINFO
		this->NAsyncDBMgr::ProcessDBWork_LoadWaprInfoDBWork(static_cast<CLoadWarpInfoADBWork* const>(in_ADBWork));
	break;
	case 42: //TYPE_PARTY_RECRUIT_INSERT
	break;
	case 43: //TYPE_PARTY_RECRUIT_DELETE
	break;
	case 44: //TYPE_PARTY_RECRUIT_UPDATE
	break;
	case 45: //TYPE_PARTY_RECRUIT_ADDBLOCKLIST
	break;
	case 46: //TYPE_PARTY_RECRUIT_DELETEBLOCKLIST
	break;
	case 48: //TYPE_GET_BEFOR_WORLD_INFO
	break;
	case 49: //TYPE_GET_GUILD_EMBLEM
	break;
	case 50: //TYPE_BANKING_DEPOSIT
	break;
	case 51: //TYPE_BANKING_WITHDRAW
	break;
	case 52: //TYPE_BANKING_VIEW
	break;
	case 53: //TYPE_BANKING_CHECK
	break;
	case 54: //TYPE_INSERT_BARGAIN_SALE
	break;
	case 55: //TYPE_UPDATE_BARGAIN_SALE
	break;
	case 56: //TYPE_DELETE_BARGAIN_SALE
	break;
	case 57: //TYPE_INIT_BARGAIN_SALE
	break;
	case 58: //TYPE_SELECT_BARGAIN_SALE
	break;
	case 59: //TYPE_LOAD_GUILD_STORE
	break;
	case 60: //TYPE_INSERT_GUILD_STORE
	break;
	case 61: //TYPE_UPDATE_AID_GUILD_STORE
	break;
	case 62: //TYPE_UPDATE_ITEM_GUILD_STORE
	break;
	case 63: //TYPE_CHECKZENYWHENLOGOUT
	break;
	case 64: //TYPE_INSERTGUILDSTORAGELOG
	break;
	case 65: //TYPE_SELECTGUILDSTORAGELOG
	break;
	};
}


void NAsyncDBMgr::Process()
{
	this->NAsyncDBMgr::ProcessMessage();

	for( int i = 1; i <= 150; ++i )
	{
		NAsyncDBWork* pCompleteWork = NULL;
		if( !m_cpReponseCircularQueue->Read(pCompleteWork) )
			break;

		if( pCompleteWork == NULL )
		{
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "notify program team!!!! (NULL == pCompleteWork)");
			return;
		}

		NAsyncDBWork::enumType Type = pCompleteWork->NAsyncDBWork::GetType();
		this->NAsyncDBMgr::ProcessDBWork(pCompleteWork);

		switch( Type )
		{
		case NAsyncDBWork::TYPE_LOGON_PERMIT:
		break;
		case NAsyncDBWork::TYPE_SAVE_BODYITEM:
//			CObjectRecycleMgr<CSaveBodyItemADBWork>::Instance()->CObjectRecycleMgr<CSaveBodyItemADBWork>::Put(static_cast<CSaveBodyItemADBWork*>(pCompleteWork)); //TODO
		break;
		case NAsyncDBWork::TYPE_SAVE_CART:
			CObjectRecycleMgr<CSaveCartADBWork>::Instance()->CObjectRecycleMgr<CSaveCartADBWork>::Put(static_cast<CSaveCartADBWork*>(pCompleteWork));
		break;
		case NAsyncDBWork::TYPE_LOAD_CART:
			CObjectRecycleMgr<CLoadCartADBWork>::Instance()->CObjectRecycleMgr<CLoadCartADBWork>::Put(static_cast<CLoadCartADBWork*>(pCompleteWork));
		break;
		case NAsyncDBWork::TYPE_SAVE_STORE:
			CObjectRecycleMgr<CSaveStoreADBWork>::Instance()->CObjectRecycleMgr<CSaveStoreADBWork>::Put(static_cast<CSaveStoreADBWork*>(pCompleteWork));
		break;
		case NAsyncDBWork::TYPE_LOAD_STORE:
			CObjectRecycleMgr<CLoadStoreADBWork>::Instance()->CObjectRecycleMgr<CLoadStoreADBWork>::Put(static_cast<CLoadStoreADBWork*>(pCompleteWork));
		break;
		case NAsyncDBWork::TYPE_SAVE_QUESTEVENT:
//			CObjectRecycleMgr<CSaveQuestEventDBWork>::Instance()->CObjectRecycleMgr<CSaveQuestEventDBWork>::Put(static_cast<CSaveQuestEventDBWork*>(pCompleteWork)); //TODO
		break;
		case NAsyncDBWork::TYPE_SAVE_ALL:
			CObjectRecycleMgr<CSaveAllADBWork>::Instance()->CObjectRecycleMgr<CSaveAllADBWork>::Put(static_cast<CSaveAllADBWork*>(pCompleteWork));
		break;
		default:
			delete pCompleteWork;
		break;
		};
	}
}


void NAsyncDBMgr::ProcessDBWork_Effect3rdUpdateAll(class CEffect3rdUpdateAllADBWork* const in_cpEffect3rdUpdateAllADBWork) // 809-827
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_TranscendentJob(class CTranscendentJobADBWork* const in_cpTranscendentJobADBWork) // 833-863
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_ChangeJob(class CChangeJobADBWork* const in_cpChangeJobADBWork) // 868-901
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_Skill3rdReset(class CSkill3rdResetADBWork* const in_cpSkill3rdResetADBWork) // 908-936
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_Skill3rdUpdate(class CSkill3rdUpdateADBWork* const in_cpSkill3rdUpdateADBWork) // 941-969
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_SAVE_ALL(CSaveAllADBWork* const in_pSaveAllADBWork) // 976-1033
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_pSaveAllADBWork->CSaveAllADBWork::GetAID(), PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_pSaveAllADBWork->CSaveAllADBWork::GetGID() )
		return;

	int id = pc->GetEffective(EFST_NOACTION_WAIT, 0);
	if( id == in_pSaveAllADBWork->NAsyncDBWork::GetIdentity() )
		pc->ResetEffective(EFST_NOACTION_WAIT, id);

	switch( in_pSaveAllADBWork->CSaveAllADBWork::GetAfterAction() )
	{
	case CSaveAllADBWork::AFTER_ACTION_DISCONNECT:
		pc->CPC::SetDisconnectStep(CPC::DISCONNECTSTEP_ASYNCDB_SAVE_COMPLETE);
	break;
	case CSaveAllADBWork::AFTER_ACTION_QUIT_EXIT:
	{
		CPacketHandler* handler = pc->CPC::GetPacketHandler();
		if( handler == NULL )
			break;

		static_cast<CPCPacketHandler*>(handler)->CPCPacketHandler::OnRestart_QUIT_EXIT_Part2();
	}
	break;
	case CSaveAllADBWork::AFTER_ACTION_MAPMOVE_OTHERSERVER:
		pc->m_pcClientUpdater.CPCClientUpdater::MapMove_OtherServer_Part2(in_pSaveAllADBWork->m_MapMoveOtherSvr.m_NID, in_pSaveAllADBWork->m_MapMoveOtherSvr.m_TargetSvrID);
	break;
	case CSaveAllADBWork::AFTER_ACTION_NONE:
		pc->CPC::AsyncSaveALL_AFTER_ACTION_NONE();
	break;
	case CSaveAllADBWork::AFTER_ACTION_ANYTIME:
		pc->CPC::AsyncSaveALL_AFTER_ACTION_ANYTIME();
	break;
	case CSaveAllADBWork::AFTER_ACTION_XXX:
		pc->CPC::AsyncSaveALL_AFTER_ACTION_ANYTIME();
	break;
	};
}


namespace {
class lcLogonPermitADBWorkPtr
{
public:
	void Reset()
	{
		m_cpLogonPermitDBWork = NULL;
	}

public:
	lcLogonPermitADBWorkPtr(CLogonPermitADBWork* in_cpLogonPermitDBWork)
	{
		m_cpLogonPermitDBWork = in_cpLogonPermitDBWork;
	}

	~lcLogonPermitADBWorkPtr()
	{
		if( m_cpLogonPermitDBWork != NULL )
			CObjectRecycleMgr<CLogonPermitADBWork>::Instance()->CObjectRecycleMgr<CLogonPermitADBWork>::Put(m_cpLogonPermitDBWork);
	}

private:
	/* this+0 */ CLogonPermitADBWork* m_cpLogonPermitDBWork;
};
}; // namespace


void NAsyncDBMgr::ProcessDBWork_LogonPermit(CLogonPermitADBWork* const in_cpLogonPermitDBWork) // 1051-1135
{
	lcLogonPermitADBWorkPtr myPtr(in_cpLogonPermitDBWork);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpLogonPermitDBWork->CLogonPermitADBWork::GetAID(), PC_TYPE);
	if( pc == NULL )
		return;
	
	if( pc->CPC::GetCharacterID() != in_cpLogonPermitDBWork->CLogonPermitADBWork::GetGID() )
		return;

	int id = pc->GetEffective(EFST_NOACTION_WAIT, 0);
	if( id == 0 )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[EFST_NOACTION_WAIT] %d,%d,%d", pc->GetEffective(EFST_NOACTION_WAIT, 0), pc->GetEffective(EFST_NOACTION_WAIT, 1), pc->GetEffective(EFST_NOACTION_WAIT, 2));
		return;
	}

	if( id == in_cpLogonPermitDBWork->NAsyncDBWork::GetIdentity() )
		pc->ResetEffective(EFST_NOACTION_WAIT, id);

	if( pc->CClient::GetErrorCount() >= 4 )
		return;

	if( pc->CPC::GetAsyncMonopolyProcessType() != AsyncMonopolyProcess::TYPE_NONE )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "0000 ************* AID(%d) GID(%d) IsValid(%d) ErrorCnt(%d) DisconnectStep(%d) AsyncMonopolyProcessType(%d)", pc->GetAccountID(), pc->CPC::GetCharacterID(), pc->CPC::IsValid(), pc->CClient::GetErrorCount(), pc->CPC::GetDisconnectStep(), pc->CPC::GetAsyncMonopolyProcessType());
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( in_cpLogonPermitDBWork->CLogonPermitADBWork::GetResult() != CLogonPermitADBWork::RESULT_SUCCESS )
	{
		pc->CPC::SetValid(FALSE);
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "NAsyncDBMgr::ProcessDBWork_LogonPermit(): AID=%d GID=%d Result(%d)", in_cpLogonPermitDBWork->CLogonPermitADBWork::GetAID(), in_cpLogonPermitDBWork->CLogonPermitADBWork::GetGID(), in_cpLogonPermitDBWork->CLogonPermitADBWork::GetResult());
		return;
	}

	CAmpLogonPermit* amp = new(std::nothrow) CAmpLogonPermit(pc, in_cpLogonPermitDBWork);
	pc->CPC::SetAsyncMonopolyProcess(std::tr1::shared_ptr<CAsyncMonopolyProcess>(amp));

	myPtr.lcLogonPermitADBWorkPtr::Reset();
}


void NAsyncDBMgr::ProcessDBWork_SAVE_SKILL(class CSaveSkillADBWork* const in_cpSaveSkillADBWork) // ???-1144-???
{
	if( in_cpSaveSkillADBWork->CSaveSkillADBWork::GetResult() != CSaveSkillADBWork::RESULT_SUCCESS )
	{
		CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpSaveSkillADBWork->CSaveSkillADBWork::GetAID(), PC_TYPE);
		if( pc == NULL )
			return;

		if( pc->CPC::GetCharacterID() == in_cpSaveSkillADBWork->CSaveSkillADBWork::GetGID() )
			pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
	}
}


void NAsyncDBMgr::ProcessDBWork_LOAD_STORE(CLoadStoreADBWork* const in_cpLoadStoreADBWork) // 1150-1180
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpLoadStoreADBWork->CLoadStoreADBWork::GetAID(), PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_cpLoadStoreADBWork->CLoadStoreADBWork::GetGID() )
		return;

	int id = pc->GetEffective(EFST_NOACTION_WAIT, 0);
	if( id == 0 )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[EFST_NOACTION_WAIT] %d,%d,%d", pc->GetEffective(EFST_NOACTION_WAIT, 0), pc->GetEffective(EFST_NOACTION_WAIT, 1), pc->GetEffective(EFST_NOACTION_WAIT, 2));
		return;
	}

	if( id == in_cpLoadStoreADBWork->NAsyncDBWork::GetIdentity() )
		pc->ResetEffective(EFST_NOACTION_WAIT, id);

	if( in_cpLoadStoreADBWork->CLoadStoreADBWork::GetResult() != CLoadStoreADBWork::RESULT_SUCCESS )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	pc->CPC::ParseDBFmtStoreItemData(in_cpLoadStoreADBWork->m_Length, in_cpLoadStoreADBWork->m_Data);
}


void NAsyncDBMgr::ProcessDBWork_SAVE_STORE(CSaveStoreADBWork* const in_cpSaveStoreADBWork) // 1183-1207
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpSaveStoreADBWork->CSaveStoreADBWork::GetAID(), PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_cpSaveStoreADBWork->CSaveStoreADBWork::GetGID() )
		return;

	int id = pc->GetEffective(EFST_NOACTION_WAIT, 0);
	if( id == 0 )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[EFST_NOACTION_WAIT] %d,%d,%d", pc->GetEffective(EFST_NOACTION_WAIT, 0), pc->GetEffective(EFST_NOACTION_WAIT, 1), pc->GetEffective(EFST_NOACTION_WAIT, 2));
		return;
	}

	if( id == in_cpSaveStoreADBWork->NAsyncDBWork::GetIdentity() )
		pc->ResetEffective(EFST_NOACTION_WAIT, id);

	if( in_cpSaveStoreADBWork->CSaveStoreADBWork::GetResult() )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( in_cpSaveStoreADBWork->CSaveStoreADBWork::IsCloseStore() )
		pc->CPC::StoreItemReset();
}


void NAsyncDBMgr::ProcessDBWork_LOAD_CART(class CLoadCartADBWork* const in_cpLoadCartADBWork) // 1211-1240
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpLoadCartADBWork->CLoadCartADBWork::GetAID(), PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_cpLoadCartADBWork->CLoadCartADBWork::GetGID() )
		return;

	int id = pc->GetEffective(EFST_NOACTION_WAIT, 0);
	if( id == 0 )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[EFST_NOACTION_WAIT] %d,%d,%d", pc->GetEffective(EFST_NOACTION_WAIT, 0), pc->GetEffective(EFST_NOACTION_WAIT, 1), pc->GetEffective(EFST_NOACTION_WAIT, 2));
		return;
	}

	if( id == in_cpLoadCartADBWork->NAsyncDBWork::GetIdentity() )
		pc->ResetEffective(EFST_NOACTION_WAIT, id);

	if( in_cpLoadCartADBWork->CLoadCartADBWork::GetResult() != CLoadCartADBWork::RESULT_SUCCESS )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	pc->CPC::AsyncDBComplete_LoadCart(in_cpLoadCartADBWork->m_SKLevel, in_cpLoadCartADBWork->m_Data, in_cpLoadCartADBWork->m_Length);
}


void NAsyncDBMgr::ProcessDBWork_SAVE_CART(class CSaveCartADBWork* const in_cpSaveCartADBWork) // ???-1250-???
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpSaveCartADBWork->CSaveCartADBWork::GetAID(), PC_TYPE);
	if( pc == NULL )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( pc->CPC::GetCharacterID() != in_cpSaveCartADBWork->CSaveCartADBWork::GetGID() )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}
	
	if( in_cpSaveCartADBWork->CSaveCartADBWork::GetResult() != CSaveCartADBWork::RESULT_SUCCESS )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}
}


void NAsyncDBMgr::ProcessDBWork_MERCENARY_CREATE(class CMercenaryCreateADBWork* const in_cpMercenaryCreateADBWork) // 1256-1283
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpMercenaryCreateADBWork->CMercenaryCreateADBWork::GetAID(), PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_cpMercenaryCreateADBWork->CMercenaryCreateADBWork::GetGID() )
		return;

	int id = pc->GetEffective(EFST_NOACTION_WAIT, 0);
	if( id == 0 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[EFST_NOACTION_WAIT] %d,%d,%d", pc->GetEffective(EFST_NOACTION_WAIT, 0), pc->GetEffective(EFST_NOACTION_WAIT, 1), pc->GetEffective(EFST_NOACTION_WAIT, 2));
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( id == in_cpMercenaryCreateADBWork->NAsyncDBWork::GetIdentity() )
		pc->ResetEffective(EFST_NOACTION_WAIT, id);

	if( in_cpMercenaryCreateADBWork->CMercenaryCreateADBWork::GetResult() != CMercenaryCreateADBWork::RESULT_SUCCESS )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	pc->m_pcBattle.CPCBattle::MercenaryCall_Create_After(in_cpMercenaryCreateADBWork->CMercenaryCreateADBWork::GetJob());
}


void NAsyncDBMgr::ProcessDBWork_MERCENARY_DELETE(class CMercenaryDeleteADBWork* const in_cpMercenaryDeleteADBWork) // 1304-1329
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpMercenaryDeleteADBWork->CMercenaryDeleteADBWork::GetAID(), PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_cpMercenaryDeleteADBWork->CMercenaryDeleteADBWork::GetGID() )
		return;

	int id = pc->GetEffective(EFST_NOACTION_WAIT, 0);
	if( id == 0 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[EFST_NOACTION_WAIT] %d,%d,%d", pc->GetEffective(EFST_NOACTION_WAIT, 0), pc->GetEffective(EFST_NOACTION_WAIT, 1), pc->GetEffective(EFST_NOACTION_WAIT, 2));
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( id == in_cpMercenaryDeleteADBWork->NAsyncDBWork::GetIdentity() )
		pc->ResetEffective(EFST_NOACTION_WAIT, id);

	if( in_cpMercenaryDeleteADBWork->CMercenaryDeleteADBWork::GetResult() != CMercenaryDeleteADBWork::RESULT_SUCCESS )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	pc->m_pcBattle.CPCBattle::MercenaryCall_Delete_After(in_cpMercenaryDeleteADBWork->CMercenaryDeleteADBWork::GetReason());
}


void NAsyncDBMgr::ProcessDBWork_SAVE_EFFECTIVEINFO(class CSaveEffectiveInfoADBWork* const in_cpSaveEffectiveInfoADBWork) // 1332-1336
{
}


void NAsyncDBMgr::ProcessDBWork_InsertCouple(class CInsertCoupleADBWork* const in_cpInsertCoupleADBWork) // 1340-1375
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_InsertFamilyADBWork(class CInsertFamilyADBWork* const in_cpInsertFamilyADBWork) // 1378-1409
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_DeleteFamilyADBWork(class CDeleteFamilyADBWork* const in_cpDeleteFamilyADBWork) // 1413-1444
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_DeleteCoupleDBWork(class CDeleteCoupleADBWork* const in_cpeleteCoupleADBWork) // 1447-1478
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_LoadCharName(class CLoadCharNameADBWork* const in_cpLoadCharNameADBWork) // ???
{
	//TODO
/*
	CCharacterNameDictionary::GetObj()->CCharacterNameDictionary::LoadingComplete(in_cpLoadCharNameADBWork->m_GID, in_cpLoadCharNameADBWork->m_CharacterName, in_cpLoadCharNameADBWork->m_Result);
*/
}


void NAsyncDBMgr::ProcessDBWork_Elemenal_Create(class CElementalCreateADBWork* const in_cpElementalCreateADBWork) // ???
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpElementalCreateADBWork->NAsyncDBWork::GetID(), PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_cpElementalCreateADBWork->NAsyncDBWork::GetID() )
		return;

	pc->m_Elemental.CPCElemental::Create_After(pc, in_cpElementalCreateADBWork);
}


void NAsyncDBMgr::ProcessDBWork_Elemenal_Delete(class CElementalDeleteADBWork* const in_cpElementalDeleteADBWork) // 1537-1557
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpElementalDeleteADBWork->NAsyncDBWork::GetID(), PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_cpElementalDeleteADBWork->CElementalDeleteADBWork::GetGID() )
		return;

	int id = pc->GetEffective(EFST_NOACTION_WAIT, 0);
	if( id == 0 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[EFST_NOACTION_WAIT] %d,%d,%d", pc->GetEffective(EFST_NOACTION_WAIT, 0), pc->GetEffective(EFST_NOACTION_WAIT, 1), pc->GetEffective(EFST_NOACTION_WAIT, 2));
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	if( id == in_cpElementalDeleteADBWork->NAsyncDBWork::GetIdentity() )
		pc->ResetEffective(EFST_NOACTION_WAIT, id);
}


void NAsyncDBMgr::ProcessDBWork_LoadWaprInfoDBWork(class CLoadWarpInfoADBWork* const in_cpLoadWarpInfoADBWork) // 1572-1593
{
	CPC* pPC = CCharacterMgr::GetObj()->CCharacterMgr::FindPCByGID(in_cpLoadWarpInfoADBWork->CLoadWarpInfoADBWork::GetGID());
	if( pPC == NULL )
		return;

	if( in_cpLoadWarpInfoADBWork->CLoadWarpInfoADBWork::GetResult() != CLoadWarpInfoADBWork::RESULT_SUCCESS )
	{
		pPC->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	switch( in_cpLoadWarpInfoADBWork->CLoadWarpInfoADBWork::GetLoadType() )
	{
	case CLoadWarpInfoADBWork::LOAD_TYPE_PORTAL:
	{
		pPC->m_pcSkill.CPCSkill::SetWarpInfo(in_cpLoadWarpInfoADBWork->CLoadWarpInfoADBWork::GetWarpInfo());
	}
	break;
	case CLoadWarpInfoADBWork::LOAD_TYPE_STAR_PLACE:
	{
		pPC->m_pcSkill.CPCSkill::SetStarPlaceInfo(in_cpLoadWarpInfoADBWork->CLoadWarpInfoADBWork::GetWarpInfo());

		short skillLv = pPC->m_pcSkill.CPCSkill::GetSkillLevel(SKID_SG_KNOWLEDGE, TRUE);
		if( skillLv > 0 )
			CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pPC, CM_SKILL_SG_KNOWLEDGE, SKID_SG_KNOWLEDGE, 0, skillLv, 0);
	}
	break;
	};
}
