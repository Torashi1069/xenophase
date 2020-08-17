#include "CharacterMgr.h"
#include "NpcPet.h"
#include "PC.h"
#include "globals.hpp"


CNpcPet::CNpcPet(void) // line 23-25
{
	m_type = NPC_PET_TYPE;
}


CNpcPet::~CNpcPet(void) // line 28-29
{
}


hook_method<void (CNpcPet::*)(void)> CNpcPet::_OnProcess(SERVER, "CNpcPet::OnProcess");
void CNpcPet::OnProcess(void) // line 50-56
{
	return (this->*_OnProcess)();

    if( m_characterInfo.isValid )
    {
        m_npcUpdater.CNPCUpdater::CheckMove();
        this->CNpcPet::OnTimerPet();
        m_npcStateUpdater.CNPCStateUpdater::CheckInput();
    }
}


hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetSpeed(SERVER, "CNpcPet::GetSpeed");
int CNpcPet::GetSpeed(void) // line 526-531
{
	return (this->*_GetSpeed)();

	CPC* owner = this->CNpcPet::GetOwner();
	return ( owner != NULL ) ? owner->CPC::GetSpeed() : this->CNPC::GetSpeed();
}


//hook_method<void (CNpcPet::*)(unsigned long AID)> CNpcPet::_SetOwnerAID(SERVER, "CNpcPet::SetOwnerAID");
void CNpcPet::SetOwnerAID(unsigned long AID) // line ??-??
{
//	return (this->*_SetOwnerAID)(AID);

	m_myOwnerAID = AID;
}


//hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetPetDBKey(SERVER, "CNpcPet::GetPetDBKey");
int CNpcPet::GetPetDBKey(void) // line ??-??
{
//	return (this->*_GetPetDBKey)();

	return m_dbkey;
}


hook_method<void (CNpcPet::*)(int delta)> CNpcPet::_ModifyFullness(SERVER, "CNpcPet::ModifyFullness");
void CNpcPet::ModifyFullness(int delta) // line 105-146
{
	return (this->*_ModifyFullness)(delta);

	// compute intimacy bonus
	int intimacy = 0;
	if( delta > 0 )
	{
		switch( m_fullGrade )
		{
		case 0: intimacy = int(m_petInfo->iRIWF * 0.25 + 0.5); break;
		case 1: intimacy = m_petInfo->iRIWF; break;
		case 2: intimacy = int(m_petInfo->iRIWF * 0.5 + 0.5); break;
		case 3: intimacy = 0; break;
		case 4: intimacy = m_petInfo->iRDWF; break;
		default: break;
		}
	}

	// increase fullness
	m_fullness += delta;
	if( delta < 0 )
	{
		if( m_fullness < 1 )
			m_fullness = 1;
	}
	else
	{
		if( m_fullness > 100 )
			m_fullness = 100;
	}

	// update client
	this->CNpcPet::SendPetState(2, m_fullness);

	// recalc FullGrade
	int newfullGrade = this->CNpcPet::GetPetFG(m_fullness);
	if( m_fullGrade != 0 && newfullGrade == 0 )
		m_timerHunger.CPollTimer::Reset(timeGetTime(), 0);
	m_fullGrade = newfullGrade;

	// increase intimacy
	if( intimacy != 0 )
		this->CNpcPet::ModifyRelationship(intimacy);
}


hook_method<void (CNpcPet::*)(int delta)> CNpcPet::_ModifyRelationship(SERVER, "CNpcPet::ModifyRelationship");
void CNpcPet::ModifyRelationship(int delta)
{
	return (this->*_ModifyRelationship)(delta);

	//TODO
}


hook_method<void (CNpcPet::*)(char type, int data)> CNpcPet::_SendPetState(SERVER, "CNpcPet::SendPetState");
void CNpcPet::SendPetState(char type, int data)
{
	return (this->*_SendPetState)(type, data);

	//TODO
}


hook_method<void (CNpcPet::*)(char type, int data)> CNpcPet::_MultiCastPetState(SERVER, "CNpcPet::MultiCastPetState");
void CNpcPet::MultiCastPetState(char type, int data)
{
	return (this->*_MultiCastPetState)(type, data);

	//TODO
}


hook_method<void (CNpcPet::*)(int item)> CNpcPet::_ModifyAccessary(SERVER, "CNpcPet::ModifyAccessary");
void CNpcPet::ModifyAccessary(int item)
{
	return (this->*_ModifyAccessary)(item);

	//TODO
}


hook_method<int (CNpcPet::*)(int i)> CNpcPet::_GetPetRG(SERVER, "CNpcPet::GetPetRG");
int CNpcPet::GetPetRG(int i) // line 395-406
{
	return (this->*_GetPetRG)(i);

	return ( i <= 100 ) ? 0
	     : ( i <= 250 ) ? 1
	     : ( i <= 750 ) ? 2
	     : ( i <= 900 ) ? 3
	     :                4;
}


hook_method<int (CNpcPet::*)(int fullness)> CNpcPet::_GetPetFG(SERVER, "CNpcPet::GetPetFG");
int CNpcPet::GetPetFG(int fullness) // line 409-420
{
	return (this->*_GetPetFG)(fullness);

	return ( fullness <= 10 ) ? 0
	     : ( fullness <= 25 ) ? 1
	     : ( fullness <= 75 ) ? 2
	     : ( fullness <= 90 ) ? 3
	     :                      4;
}


hook_method<int (CNpcPet::*)(int iRelationship)> CNpcPet::_GetPerformanceNo(SERVER, "CNpcPet::GetPerformanceNo");
int CNpcPet::GetPerformanceNo(int iRelationship)
{
	return (this->*_GetPerformanceNo)(iRelationship);

	//TODO
}


hook_method<void (CNpcPet::*)(void)> CNpcPet::_OnTimerPet(SERVER, "CNpcPet::OnTimerPet");
void CNpcPet::OnTimerPet(void)
{
	return (this->*_OnTimerPet)();

	//TODO
}


hook_method<void (CNpcPet::*)(DWORD dwTick)> CNpcPet::_InitPetTimer(SERVER, "CNpcPet::InitPetTimer");
void CNpcPet::InitPetTimer(DWORD dwTick)
{
	return (this->*_InitPetTimer)(dwTick);

	//TODO
}


hook_method<void (CNpcPet::*)(void)> CNpcPet::_SendPetProperty(SERVER, "CNpcPet::SendPetProperty");
void CNpcPet::SendPetProperty(void)
{
	return (this->*_SendPetProperty)();

	//TODO
}


hook_method<void (CNpcPet::*)(void)> CNpcPet::_UpdateDB(SERVER, "CNpcPet::UpdateDB");
void CNpcPet::UpdateDB(void)
{
	return (this->*_UpdateDB)();

	//TODO
}


hook_method<void (CNpcPet::*)(const PET_PROPERTY& property)> CNpcPet::_InitPetProperty(SERVER, "CNpcPet::InitPetProperty");
void CNpcPet::InitPetProperty(const PET_PROPERTY& property)
{
	return (this->*_InitPetProperty)(property);

	//TODO
}


hook_method<unsigned short (CNpcPet::*)(void)> CNpcPet::_GetPetFoodKind(SERVER, "CNpcPet::GetPetFoodKind");
unsigned short CNpcPet::GetPetFoodKind(void)
{
	return (this->*_GetPetFoodKind)();

	//TODO
}


//hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetPetJob(SERVER, "CNpcPet::GetPetJob");
int CNpcPet::GetPetJob(void)
{
//	return (this->*_GetPetJob)();

	return m_petInfo->iKind;
}


hook_method<void (CNpcPet::*)(int x, int y)> CNpcPet::_ModifyLocation(SERVER, "CNpcPet::ModifyLocation");
void CNpcPet::ModifyLocation(int x, int y)
{
	return (this->*_ModifyLocation)(x, y);

	//TODO
}


hook_method<void (CNpcPet::*)(char* name)> CNpcPet::_OnRenamePet(SERVER, "CNpcPet::OnRenamePet");
void CNpcPet::OnRenamePet(char* name)
{
	return (this->*_OnRenamePet)(name);

	//TODO
}


hook_method<void (CNpcPet::*)(CPC* sender, int par1, int par2)> CNpcPet::_OnPetMsg(SERVER, "CNpcPet::OnPetMsg");
void CNpcPet::OnPetMsg(CPC* sender, int par1, int par2)
{
	return (this->*_OnPetMsg)(sender, par1, par2);

	int msgType = (int)par1;

	switch( msgType )
	{
	case 0:
		this->CNpcPet::SendPetProperty();
	break;
	case 1:
		this->CNpcPet::ModifyFullness(m_petInfo->iSIWF);
	break;
	case 2:
	{
		int perfNo = this->CNpcPet::GetPerformanceNo(m_relationship);
		if( perfNo != 0 )
			this->CNpcPet::MultiCastPetState(4, perfNo);
	}
	break;
	case 3:
		this->CNpcPet::ModifyRelationship(m_petInfo->iRDWD);
	break;
	case 4:
	{
		int actType = (int)par2;

		PACKET_ZC_PET_ACT outpacket;
		outpacket.PacketType = HEADER_ZC_PET_ACT;
		outpacket.GID = this->GetAccountID();
		outpacket.data = actType;
		this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
	}
	break;
	default:
	break;
	}
}


hook_method<int (CNpcPet::*)(unsigned short item)> CNpcPet::_IsWearable(SERVER, "CNpcPet::IsWearable");
int CNpcPet::IsWearable(unsigned short item)
{
	return (this->*_IsWearable)(item);

	//TODO
}


//hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetRelationship(SERVER, "CNpcPet::GetRelationship");
int CNpcPet::GetRelationship(void)
{
//	return (this->*_GetRelationship)();

	return m_relationship;
}


hook_method<void (CNpcPet::*)(PET_PROPERTY& property)> CNpcPet::_ConvertInto_PET_PROPERTY(SERVER, "CNpcPet::ConvertInto_PET_PROPERTY");
void CNpcPet::ConvertInto_PET_PROPERTY(PET_PROPERTY& property)
{
	return (this->*_ConvertInto_PET_PROPERTY)(property);

	//TODO
}


hook_method<bool (CNpcPet::*)(void)> CNpcPet::_UpdateDB_WithGID(SERVER, "CNpcPet::UpdateDB_WithGID");
bool CNpcPet::UpdateDB_WithGID(void)
{
	return (this->*_UpdateDB_WithGID)();

	//TODO
}


hook_method<void (CNpcPet::*)(int logtype)> CNpcPet::_AddLog(SERVER, "CNpcPet::AddLog");
void CNpcPet::AddLog(int logtype)
{
	return (this->*_AddLog)(logtype);

	//TODO
}


//hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetNameModified(SERVER, "CNpcPet::GetNameModified");
int CNpcPet::GetNameModified(void)
{
//	return (this->*_GetNameModified)();

	return m_modified;
}


hook_method<void (CNpcPet::*)(void)> CNpcPet::_InitCore(SERVER, "CNpcPet::InitCore");
void CNpcPet::InitCore(void) // line 36-47
{
	return (this->*_InitCore)();

	this->CNPC::InitCore();
	m_petInfo = NULL;
	m_modified = 0;
	m_fullness = 0;
	m_relationship = 0;
	m_characterInfo.accessory = 0;
	m_dbkey = 0;
	m_fullGrade = 2;
	m_myOwnerAID = 0;
}


hook_method<CPC* (CNpcPet::*)(void)> CNpcPet::_GetOwner(SERVER, "CNpcPet::GetOwner");
CPC* CNpcPet::GetOwner(void) // line 59-65
{
	return (this->*_GetOwner)();

	if( m_myOwnerAID == 0 )
		return NULL;
	return (CPC*)g_characterMgr->CCharacterMgr::FindCharacter(m_myOwnerAID, PC_TYPE);
}


//hook_method<unsigned long (CNpcPet::*)(void)> CNpcPet::_GetOwnerAID(SERVER, "CNpcPet::GetOwnerAID");
unsigned long CNpcPet::GetOwnerAID(void) // line ??-??
{
//	return (this->*_GetOwnerAID)();

	return m_myOwnerAID;
}
