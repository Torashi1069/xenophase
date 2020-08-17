#pragma once
#include "NPCElemental.h"
namespace CSaveAllADBWorkStuff { class CElementalData; } // #include "AsyncDBWork/SaveAllADBWork.h"
namespace CLogonPermitADBWorkStuff { class CElementalData; } // #include "AsyncDBWork/LogonPermitADBWork.h"
class CElementalCreateADBWork;


class CPCElemental
{
public:
	enum enumState
	{
		STATE_NONEXISTENT = 0,
		STATE_CREATE      = 1,
		STATE_ACTIVE      = 2,
	};

public:
	void Init();
	enumState GetState();
	void SetState(enumState in_State);
	bool Create_Before(CPC* in_cpOwnerPlayer, const ElementalStuff::enumKind in_Kind, const ElementalStuff::enumScale in_Scale, const int in_LifeTM, const int in_ReduceSPAmount);
	void Create_After(CPC* in_cpOwnerPlayer, const CElementalCreateADBWork* in_cpADBWork);
	void Delete(CPC* in_cpOwnerPlayer);
	void Load(CPC* in_cpOwnerPlayer, const CLogonPermitADBWorkStuff::CElementalData& in_ElementData);
	void GetSaveData(CPC* in_cpOwnerPlayer, CSaveAllADBWorkStuff::CElementalData& io_ElementalData);
	void Release();
	unsigned long GetAID() const;

private:
	/* this+0 */ enumState m_State;
	/* this+4 */ unsigned long m_AID;

public:
	CPCElemental();
	~CPCElemental();
};
