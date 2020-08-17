#include "AsyncDBWork/LogonPermitADBWork.h"
#include "Player/AmpLogonPermit.h"
#include "ObjectRecycleMgr.h"


CAmpLogonPermit::CAmpLogonPermit(CPC* in_cpPlayer, CLogonPermitADBWork* in_cpLogonPermitADBWork)
: CAsyncMonopolyProcess(AsyncMonopolyProcess::TYPE_LOGONPERMIT),
  m_cpPlayer(in_cpPlayer),
  m_cpLogonPermitADBWork(in_cpLogonPermitADBWork),
  m_AID(in_cpLogonPermitADBWork->CLogonPermitADBWork::GetAID()),
  m_GID(in_cpLogonPermitADBWork->CLogonPermitADBWork::GetGID()),
  m_Step(CAmpLogonPermit::STEP_PRELIMINARY_INSPECTION)
{
}


CAmpLogonPermit::~CAmpLogonPermit()
{
	CObjectRecycleMgr<CLogonPermitADBWork>::Instance()->CObjectRecycleMgr<CLogonPermitADBWork>::Put(m_cpLogonPermitADBWork);
	m_cpLogonPermitADBWork = NULL;
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__preliminary_inspection(EXEPATH(), "CAmpLogonPermit::preliminary_inspection");
bool CAmpLogonPermit::preliminary_inspection()
{
	bool result;
	void* hookptr = CAmpLogonPermit__preliminary_inspection;
	__asm mov edi, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__mercenary(EXEPATH(), "CAmpLogonPermit::mercenary");
bool CAmpLogonPermit::mercenary()
{
	bool result;
	void* hookptr = CAmpLogonPermit__mercenary;
	__asm mov ebx, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__actor_infomation_first(EXEPATH(), "CAmpLogonPermit::actor_infomation_first");
bool CAmpLogonPermit::actor_infomation_first()
{
	bool result;
	void* hookptr = CAmpLogonPermit__actor_infomation_first;
	__asm mov ecx, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__actor_infomation_second(EXEPATH(), "CAmpLogonPermit::actor_infomation_second");
bool CAmpLogonPermit::actor_infomation_second()
{
	bool result;
	void* hookptr = CAmpLogonPermit__actor_infomation_second;
	__asm mov ebx, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


bool CAmpLogonPermit::protect()
{
	m_Step = STEP_UNKNOWN_FIRST;
	return true;
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__unknown_first(EXEPATH(), "CAmpLogonPermit::unknown_first");
bool CAmpLogonPermit::unknown_first()
{
	bool result;
	void* hookptr = CAmpLogonPermit__unknown_first;
	__asm mov edi, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__skill(EXEPATH(), "CAmpLogonPermit::skill");
bool CAmpLogonPermit::skill()
{
	bool result;
	void* hookptr = CAmpLogonPermit__skill;
	__asm mov edi, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__item(EXEPATH(), "CAmpLogonPermit::item");
bool CAmpLogonPermit::item()
{
	bool result;
	void* hookptr = CAmpLogonPermit__item;
	__asm mov esi, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__quest(EXEPATH(), "CAmpLogonPermit::quest");
bool CAmpLogonPermit::quest()
{
	bool result;
	void* hookptr = CAmpLogonPermit__quest;
	__asm mov edi, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__wedding(EXEPATH(), "CAmpLogonPermit::wedding");
bool CAmpLogonPermit::wedding()
{
	bool result;
	void* hookptr = CAmpLogonPermit__wedding;
	__asm mov edi, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__unknown_second(EXEPATH(), "CAmpLogonPermit::unknown_second");
bool CAmpLogonPermit::unknown_second()
{
	bool result;
	void* hookptr = CAmpLogonPermit__unknown_second;
	__asm mov ebx, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__effect(EXEPATH(), "CAmpLogonPermit::effect");
bool CAmpLogonPermit::effect()
{
	bool result;
	void* hookptr = CAmpLogonPermit__effect;
	__asm mov esi, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


hook_func<void (__stdcall *)()> CAmpLogonPermit__expost(EXEPATH(), "CAmpLogonPermit::expost");
bool CAmpLogonPermit::expost()
{
	bool result;
	void* hookptr = CAmpLogonPermit__expost;
	__asm mov ebx, this
	__asm call hookptr
	__asm mov result, al
	return result; //TODO
}


bool CAmpLogonPermit::operator()()
{
	switch( m_Step )
	{
	case STEP_PRELIMINARY_INSPECTION:  return this->CAmpLogonPermit::preliminary_inspection();
	case STEP_MERCENARY:               return this->CAmpLogonPermit::mercenary();
	case SETP_ACTOR_INFOMATION_FIRST:  return this->CAmpLogonPermit::actor_infomation_first();
	case STEP_ACTOR_INFOMATION_SECOND: return this->CAmpLogonPermit::actor_infomation_second();
	case STEP_PROTECT:                 return this->CAmpLogonPermit::protect();
	case STEP_UNKNOWN_FIRST:           return this->CAmpLogonPermit::unknown_first();
	case STEP_SKILL:                   return this->CAmpLogonPermit::skill();
	case STEP_ITEM:                    return this->CAmpLogonPermit::item();
	case STEP_QUEST:                   return this->CAmpLogonPermit::quest();
	case STEP_WEDDING:                 return this->CAmpLogonPermit::wedding();
	case STEP_UNKNOWN_SECOND:          return this->CAmpLogonPermit::unknown_second();
	case STEP_EFFECT:                  return this->CAmpLogonPermit::effect();
	case STEP_EXPOST:                  return this->CAmpLogonPermit::expost();
	default:
		return false;
	};
}
