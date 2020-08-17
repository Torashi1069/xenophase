#include "CharacterMgr.h"
#include "PCElemental.h"


CPCElemental::CPCElemental()
{
	m_State = STATE_NONEXISTENT;
//	m_AID = 0;
}


CPCElemental::~CPCElemental()
{
}


void CPCElemental::Init()
{
	m_State = STATE_NONEXISTENT;
	m_AID = 0;
}


CPCElemental::enumState CPCElemental::GetState()
{
	return m_State;
}


void CPCElemental::SetState(enumState in_State)
{
	m_State = in_State;
}


unsigned long CPCElemental::GetAID() const
{
	return m_AID;
}


hook_func<void (__stdcall *)()> CPCElemental__Create_Before(EXEPATH(), "CPCElemental::Create_Before");
bool CPCElemental::Create_Before(CPC* in_cpOwnerPlayer, const ElementalStuff::enumKind in_Kind, const ElementalStuff::enumScale in_Scale, const int in_LifeTM, const int in_ReduceSPAmount)
{
	bool result;
	void* hookptr = CPCElemental__Create_Before;
	__asm push in_ReduceSPAmount
	__asm push in_LifeTM
	__asm push in_Scale
	__asm push in_Kind
	__asm mov ebx, in_cpOwnerPlayer
	__asm push this
	__asm call hookptr
	__asm mov result, al
	return result;
}


hook_func<void (__stdcall *)()> CPCElemental__Create_After(EXEPATH(), "CPCElemental::Create_After");
void CPCElemental::Create_After(CPC* in_cpOwnerPlayer, const CElementalCreateADBWork* in_cpADBWork)
{
	void* hookptr = CPCElemental__Create_After;
	__asm push in_cpADBWork
	__asm mov ebx, in_cpOwnerPlayer
	__asm push this
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CPCElemental__Load(EXEPATH(), "CPCElemental::Load");
void CPCElemental::Load(CPC* in_cpOwnerPlayer, const CLogonPermitADBWorkStuff::CElementalData& in_ElementData)
{
	void* hookptr = CPCElemental__Load;
	__asm lea eax, in_ElementData
	__asm push in_cpOwnerPlayer
	__asm push this
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CPCElemental__Delete(EXEPATH(), "CPCElemental::Delete");
void CPCElemental::Delete(CPC* in_cpOwnerPlayer)
{
	void* hookptr = CPCElemental__Delete;
	__asm push in_cpOwnerPlayer
	__asm push this
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CPCElemental__GetSaveData(EXEPATH(), "CPCElemental::GetSaveData");
void CPCElemental::GetSaveData(CPC* in_cpOwnerPlayer, CSaveAllADBWorkStuff::CElementalData& io_ElementalData)
{
	void* hookptr = CPCElemental__GetSaveData;
	__asm lea ebx, io_ElementalData
	__asm mov ecx, this
	__asm call hookptr
	return; //TODO
}


void CPCElemental::Release()
{
	if( m_State == STATE_NONEXISTENT )
		return;

	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, m_AID, CM_DISAPPEAR, 0, 0, 0, 0);
	m_State = STATE_NONEXISTENT;
	m_AID = 0;
}
