#include "CharacterMgr.h"
#include "CZoneProcessLocalConfigMgr.h"
#include "Enum.h" // EFST_NOACTION_WAIT
#include "GVar.h"
#include "ObjectRecycleMgr.h"
#include "PC.h"
#include "AsyncDBWork/LoadCartADBWork.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
#include "AsyncDBWork/NAsyncDBThread.h"
#include "AsyncDBWork/NASyncDBWork.h"
#include "AsyncDBWork/NIDAllocator.h"
#include "AsyncDBWork/NInterMessageSystem.h"
#include "shared/NCriticalErrorLog.h"


/// singleton instance
NAsyncDBMgr*& NAsyncDBMgr::m_cpSelf = VTOR<NAsyncDBMgr*>(DetourFindFunction(EXEPATH(), "NAsyncDBMgr::m_cpSelf"));


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
	case 13: //TYPE_MERCENARY_DELETE
//		this->NAsyncDBMgr::ProcessDBWork_MERCENARY_DELETE(static_cast<CMercenaryDeleteADBWork* const>(in_ADBWork)); //TODO
	break;
	case 12: //TYPE_MERCENARY_CREATE
//		this->NAsyncDBMgr::ProcessDBWork_MERCENARY_CREATE(static_cast<CMercenaryCreateADBWork* const>(in_ADBWork)); //TODO
	break;
	case 11: //TYPE_SAVE_CART
//		this->NAsyncDBMgr::ProcessDBWork_SAVE_CART(static_cast<CSaveCartADBWork* const>(in_ADBWork)); //TODO
	break;
	case 10: //TYPE_LOAD_CART
//		this->NAsyncDBMgr::ProcessDBWork_LOAD_CART(static_cast<CLoadCartADBWork* const>(in_ADBWork)); //TODO
	break;
	case 9: //TYPE_SAVE_STORE
//		this->NAsyncDBMgr::ProcessDBWork_SAVE_STORE(static_cast<CSaveStoreADBWork* const>(in_ADBWork)); //TODO
	break;
	case 8: //TYPE_LOAD_STORE
//		this->NAsyncDBMgr::ProcessDBWork_LOAD_STORE(static_cast<CLoadStoreADBWork* const>(in_ADBWork)); //TODO
	break;
	case 7: //TYPE_SAVE_SKILL
//		this->NAsyncDBMgr::ProcessDBWork_SAVE_SKILL(static_cast<CSaveSkillADBWork* const>(in_ADBWork)); //TODO
	break;
	case 6: //TYPE_SAVE_CHARACTERINFO
	break;
	case 5: //TYPE_SAVE_BODYITEM
	break;
	case 4: //TYPE_SAVE_ALL
//		this->NAsyncDBMgr::ProcessDBWork_SAVE_ALL(static_cast<CSaveAllADBWork* const>(in_ADBWork)); //TODO
	break;
	case 3: //TYPE_LOGON_PERMIT
//		this->NAsyncDBMgr::ProcessDBWork_LogonPermit(static_cast<CLogonPermitADBWork* const>(in_ADBWork)); //TODO
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
	case 28: //TYPE_ELEMENTAL_CREATE
//		this->NAsyncDBMgr::ProcessDBWork_Elemenal_Create(static_cast<CElementalCreateADBWork* const>(in_ADBWork)); //TODO
	break;
	case 29: //TYPE_ELEMENTAL_DELETE
//		this->NAsyncDBMgr::ProcessDBWork_Elemenal_Delete(static_cast<CElementalDeleteADBWork* const>(in_ADBWork)); //TODO
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
//		this->NAsyncDBMgr::ProcessDBWork_LoadWaprInfoDBWork(static_cast<CLoadWarpInfoADBWork* const>(in_ADBWork)); //TODO
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
//			CObjectRecycleMgr<CSaveCartADBWork>::Instance()->CObjectRecycleMgr<CSaveCartADBWork>::Put(static_cast<CSaveCartADBWork*>(pCompleteWork)); //TODO
		break;
		case NAsyncDBWork::TYPE_LOAD_CART:
//			CObjectRecycleMgr<CLoadCartADBWork>::Instance()->CObjectRecycleMgr<CLoadCartADBWork>::Put(static_cast<CLoadCartADBWork*>(pCompleteWork)); //TODO
		break;
		case NAsyncDBWork::TYPE_SAVE_STORE:
//			CObjectRecycleMgr<CSaveStoreADBWork>::Instance()->CObjectRecycleMgr<CSaveStoreADBWork>::Put(static_cast<CSaveStoreADBWork*>(pCompleteWork)); //TODO
		break;
		case NAsyncDBWork::TYPE_LOAD_STORE:
//			CObjectRecycleMgr<CLoadStoreADBWork>::Instance()->CObjectRecycleMgr<CLoadStoreADBWork>::Put(static_cast<CLoadStoreADBWork*>(pCompleteWork)); //TODO
		break;
		case NAsyncDBWork::TYPE_SAVE_QUESTEVENT:
//			CObjectRecycleMgr<CSaveQuestEventDBWork>::Instance()->CObjectRecycleMgr<CSaveQuestEventDBWork>::Put(static_cast<CSaveQuestEventDBWork*>(pCompleteWork)); //TODO
		break;
		case NAsyncDBWork::TYPE_SAVE_ALL:
//			CObjectRecycleMgr<CSaveAllADBWork>::Instance()->CObjectRecycleMgr<CSaveAllADBWork>::Put(static_cast<CSaveAllADBWork*>(pCompleteWork)); //TODO
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
	//TODO
}


namespace {
class lcLogonPermitADBWorkPtr
{
public:
	void Reset()
	{
		//TODO
	}

public:
	lcLogonPermitADBWorkPtr(CLogonPermitADBWork* in_cpLogonPermitDBWork)
	{
		//TODO
	}

	~lcLogonPermitADBWorkPtr()
	{
		//TODO
		/*
		if( m_cpLogonPermitDBWork != NULL )
			CObjectRecycleMgr<CLogonPermitADBWork>::Instance()->CObjectRecycleMgr<CLogonPermitADBWork>::Put(m_cpLogonPermitDBWork);
		*/
	}

private:
	/* this+0 */ CLogonPermitADBWork* m_cpLogonPermitDBWork;
};
}; // namespace


void NAsyncDBMgr::ProcessDBWork_LogonPermit(CLogonPermitADBWork* const in_cpLogonPermitDBWork) // 1051-1135
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_SAVE_SKILL(class CSaveSkillADBWork* const in_cpSaveSkillADBWork) // ???-1144-???
{
	//TODO
/*
	if( in_ADBWork->m_Result != 0 )
	{
		CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpSaveSkillADBWork->m_AID, PC_TYPE);
		if( pc == NULL )
			return;

		if( pc->CPC::GetCharacterID() == in_cpSaveSkillADBWork->m_GID )
			pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
	}
*/
}


void NAsyncDBMgr::ProcessDBWork_LOAD_STORE(CLoadStoreADBWork* const in_cpLoadStoreADBWork) // 1150-1180
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_SAVE_STORE(CSaveStoreADBWork* const in_cpSaveStoreADBWork) // 1183-1207
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_LOAD_CART(class CLoadCartADBWork* const in_cpLoadCartADBWork) // 1211-1240
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpLoadCartADBWork->CLoadCartADBWork::GetAID(), PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_cpLoadCartADBWork->CLoadCartADBWork::GetGID() )
		return;

	int identity = pc->GetEffective(EFST_NOACTION_WAIT, 0);
	if( identity == 0 )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "[EFST_NOACTION_WAIT] %d,%d,%d", pc->GetEffective(EFST_NOACTION_WAIT, 0), pc->GetEffective(EFST_NOACTION_WAIT, 1), pc->GetEffective(EFST_NOACTION_WAIT, 2));
		return;
	}

	if( identity == in_cpLoadCartADBWork->NAsyncDBWork::GetIdentity() )
		pc->ResetEffective(EFST_NOACTION_WAIT, identity);

	if( in_cpLoadCartADBWork->CLoadCartADBWork::GetResult() != CLoadCartADBWork::RESULT_SUCCESS )
	{
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
		return;
	}

	pc->CPC::AsyncDBComplete_LoadCart(in_cpLoadCartADBWork->m_SKLevel, in_cpLoadCartADBWork->m_Data, in_cpLoadCartADBWork->m_Length);
}


void NAsyncDBMgr::ProcessDBWork_SAVE_CART(class CSaveCartADBWork* const in_cpSaveCartADBWork) // ???-1250-???
{
	//TODO
/*
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpSaveCartADBWork->m_AID, PC_TYPE);
	if( pc != NULL && pc->CPC::GetCharacterID() == in_cpSaveCartADBWork->m_GID && in_cpSaveCartADBWork->m_Result )
		pc->AddErrorCnt(__FILE__, __LINE__, 4, timeGetTime());
*/
}


void NAsyncDBMgr::ProcessDBWork_MERCENARY_CREATE(class CMercenaryCreateADBWork* const in_cpMercenaryCreateADBWork) // 1256-1283
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_MERCENARY_DELETE(class CMercenaryDeleteADBWork* const in_cpMercenaryDeleteADBWork) // 1304-1329
{
	//TODO
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
	//TODO
/*
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(in_cpElementalCreateADBWork->m_ID, PC_TYPE);
	if( pc == NULL )
		return;

	if( pc->CPC::GetCharacterID() != in_cpElementalCreateADBWork->m_GID )
		return;

	pc->m_Elemental->CPCElemental::Create_After(pc, in_cpElementalCreateADBWork);
*/
}


void NAsyncDBMgr::ProcessDBWork_Elemenal_Delete(class CElementalDeleteADBWork* const in_cpElementalDeleteADBWork) // 1537-1557
{
	//TODO
}


void NAsyncDBMgr::ProcessDBWork_LoadWaprInfoDBWork(class CLoadWarpInfoADBWork* const in_cpLoadWarpInfoADBWork) // 1572-1593
{
	//TODO
}
