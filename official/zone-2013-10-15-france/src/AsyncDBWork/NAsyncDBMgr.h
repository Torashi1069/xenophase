#pragma once
#include "AsyncDBWork/NAsyncDBRequestCircularQueue.h"
#include "AsyncDBWork/NAsyncDBWork.h"
#include "AsyncDBWork/NInterMessageQueue.h"
#include "AsyncDBWork/NXInter.h"
#include "AsyncDBWork/NXObject.h"
class NAsyncDBResponseCircularQueue;
class NAsyncDBThread;


class NAsyncDBMgr : public NXObject, public NXInter
{
public:
	enum { TIMEOUT = 40000, TIMEOUT_LOGONPERMIT = 300000 };
	enum { MAX_ASYNCDB_WORK = 15000, MAX_TASK_NUM_PER_PROCESSLOOP = 150 };

private:
	/* static   */ static NAsyncDBMgr*& m_cpSelf; //TODO
	/* this+  0 */ //NXObject baseclass_0;
	/* this+ 36 */ //NXInter baseclass_36;
	/* this+ 40 */ bool m_bOK;
	/* this+ 44 */ NAsyncDBRequestCircularQueue* m_cpRequestCircularQueue;
	/* this+ 48 */ NAsyncDBResponseCircularQueue* m_cpReponseCircularQueue;
	/* this+ 52 */ NInterMessageQueue m_MessageQueue;
	typedef std::vector<NAsyncDBThread*> WORKTHREDCONTAINER;
	typedef std::vector<NAsyncDBThread*>::iterator WORKTHREDCONTAINERITOR;
	/* this+100 */ WORKTHREDCONTAINER m_WorkThreadContainer;
	/* this+116 */ int m_WorkThreadGroupID;

private:
	bool Create(const std::string in_ODBCConnectionStr);
	void Destory();

private:
	void ProcessMessage();
	void ProcessDBWork(NAsyncDBWork* const in_ADBWork);
	void ProcessDBWork_SAVE_ALL(class CSaveAllADBWork* const in_pSaveAllADBWork);
	void ProcessDBWork_LogonPermit(class CLogonPermitADBWork* const in_cpLogonPermitDBWork);
	void ProcessDBWork_SAVE_SKILL(class CSaveSkillADBWork* const in_cpSaveSkillADBWork);
	void ProcessDBWork_LOAD_STORE(class CLoadStoreADBWork* const in_cpLoadStoreADBWork);
	void ProcessDBWork_SAVE_STORE(class CSaveStoreADBWork* const in_cpSaveStoreADBWork);
	void ProcessDBWork_LOAD_CART(class CLoadCartADBWork* const in_cpLoadCartADBWork);
	void ProcessDBWork_SAVE_CART(class CSaveCartADBWork* const in_cpSaveCartADBWork);
	void ProcessDBWork_MERCENARY_CREATE(class CMercenaryCreateADBWork* const in_cpMercenaryCreateADBWork);
	void ProcessDBWork_MERCENARY_DELETE(class CMercenaryDeleteADBWork* const in_cpMercenaryDeleteADBWork);
	void ProcessDBWork_SAVE_EFFECTIVEINFO(class CSaveEffectiveInfoADBWork* const in_cpSaveEffectiveInfoADBWork);
	void ProcessDBWork_Skill3rdUpdate(class CSkill3rdUpdateADBWork* const in_cpSkill3rdUpdateADBWork);
	void ProcessDBWork_Skill3rdReset(class CSkill3rdResetADBWork* const in_cpSkill3rdResetADBWork);
	void ProcessDBWork_ChangeJob(class CChangeJobADBWork* const in_cpChangeJobADBWork);
	void ProcessDBWork_TranscendentJob(class CTranscendentJobADBWork* const in_cpTranscendentJobADBWork);
	void ProcessDBWork_Effect3rdUpdateAll(class CEffect3rdUpdateAllADBWork* const cpEffect3rdUpdateAllADBWork);
	void ProcessDBWork_LoadCharName(class CLoadCharNameADBWork* const in_cpLoadCharNameADBWork);
	void ProcessDBWork_Elemenal_Create(class CElementalCreateADBWork* const in_cpElementalCreateADBWork);
	void ProcessDBWork_Elemenal_Delete(class CElementalDeleteADBWork* const in_cpElementalDeleteADBWork);
	void ProcessDBWork_InsertCouple(class CInsertCoupleADBWork* const in_cpInsertCoupleADBWork);
	void ProcessDBWork_InsertFamilyADBWork(class CInsertFamilyADBWork* const in_cpInsertFamilyADBWork);
	void ProcessDBWork_DeleteFamilyADBWork(class CDeleteFamilyADBWork* const in_cpDeleteFamilyADBWork);
	void ProcessDBWork_DeleteCoupleDBWork(class CDeleteCoupleADBWork* const in_cpeleteCoupleADBWork);
	void ProcessDBWork_LoadWaprInfoDBWork(class CLoadWarpInfoADBWork* const in_cpLoadWarpInfoADBWork);

public:
	const bool isOK() const;
	bool Start();
	void Stop();
	void Process();

	bool RequestWork(NAsyncDBWork* in_cpWork);
	NAsyncDBWork* ResponseWork();
	int GetRequestWorkNum();

	virtual void PostInterMessage(const unsigned int in_FromInter, const unsigned long in_ExecTimeMS, const int in_Msg, const int in_wParam, const int in_lParam);
	virtual bool PeekInterMessage(const unsigned long in_ExecTimeMS, unsigned int& out_FromInter, int& out_Msg, int& out_wParam, int& out_lParam, const bool in_bRemove);

public:
	static bool CreateInstance(const std::string in_ODBCConnectionStr);
	static void DestoryInstance();
	static NAsyncDBMgr* GetObj(); /// @custom

private:
	NAsyncDBMgr(const std::string in_ODBCConnectionStr);
	virtual ~NAsyncDBMgr();
};
