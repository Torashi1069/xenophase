#include "AsyncDBWork/Effect3rd.h"
#include "AsyncDBWork/Effect3rdDeleteADBWork.h"
#include "AsyncDBWork/Effect3rdUpdateAllADBWork.h"
#include "AsyncDBWork/NAsyncDBMgr.h"
namespace Effect3rd {


void Delete(const int in_AID, const int in_GID, const int in_EffectID)
{
	CEffect3rdDeleteADBWork* work = new(std::nothrow) CEffect3rdDeleteADBWork(in_AID, in_GID, in_EffectID);
	if( work == NULL )
		return;

	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) )
		delete work;
}


void UpdateAll(CPC* in_cpPlayer)
{
	//TODO
/*
	CEffect3rdUpdateAllADBWork* work = new(std::nothrow) CEffect3rdUpdateAllADBWork(in_cpPlayer->GetAccountID(), in_cpPlayer->CPC::GetCharacterID());

	if( work == NULL )
		return;

	in_cpPlayer->CPC::GetEfstListDBFmt_And_UpdateResetFlag(work->m_List, false);
	if( !NAsyncDBMgr::GetObj()->NAsyncDBMgr::RequestWork(work) )
	{
		delete work;
		return;
	}

	in_cpPlayer->CPC::SetEffective(EFST_NOACTION_WAIT, 40000, work->NAsyncDBWork::GetIdentity(), work->NAsyncDBWork::GetType(), timeGetTime(), 0);
*/
}


}; //namespace
