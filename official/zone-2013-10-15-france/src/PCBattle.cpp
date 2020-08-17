#include "PC.h"
#include "PCBattle.h"
#include "ScriptEventHandler.h"
#include "SkillTypeInfo.h"
#include "SkillTypeInfoMgr.h"
#include "ZoneProcessStuff.h"


CPCBattle::CPCBattle() // 67-68
{
}


CPCBattle::~CPCBattle() // 168.h (163.h)
{
}


void CPCBattle::Init() // 71-74
{
	m_pc = NULL;
	this->CPCBattle::Reset();
}


void CPCBattle::SetMyOwner(CPC* pc) // ??? (167.h)
{
	m_pc = pc;
}


hook_func<void (__stdcall *)()> CPCBattle__Reset(EXEPATH(), "CPCBattle::Reset");
void CPCBattle::Reset() // 77-209
{
	void* hookptr = CPCBattle__Reset;
	__asm mov ebx, this
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CPCBattle__ApplyEffect_ATKED(EXEPATH(), "CPCBattle::ApplyEffect_ATKED");
void CPCBattle::ApplyEffect_ATKED(CCharacter* other, BOOL isMLEATK, BOOL isMATK, unsigned short SKID, int in_Damage) // 4526-4636
{
	void* hookptr = CPCBattle__ApplyEffect_ATKED;
	__asm push in_Damage
	__asm push SKID
	__asm push isMATK
	__asm push isMLEATK
	__asm mov ecx, other
	__asm mov edx, this
	__asm call hookptr
	return; //TODO
}


hook_func<void (CPCBattle::*)(unsigned short SKID, CCharacter* ch, short skillLv, MSGpar::CVar in_par)> CPCBattle__UseAutoSpell(EXEPATH(), "CPCBattle::UseAutoSpell");
void CPCBattle::UseAutoSpell(unsigned short SKID, CCharacter* ch, short skillLv, MSGpar::CVar in_par) // 4835-4873
{
	return (this->*CPCBattle__UseAutoSpell)(SKID, ch, skillLv, in_par); //TODO
}


void CPCBattle::ResetATKPercentInfo(int SKID) // 4950-4966
{
	CharacterInfo* charInfo = m_pc->CPC::GetCharacterInfo();

	std::map<int,AMOUNT_INFO>::iterator iter = m_ATKPercentList.find(SKID);
	if( iter == m_ATKPercentList.end() )
		return;

	charInfo->ATKPercent -= iter->second.amount;
	iter->second.time = 0;
	iter->second.amount = 0;

	m_pc->UpdateParameterValue(VAR_ITEMPOWER, 0);
}


void CPCBattle::ResetDEFPercentInfo(const int in_SKID) // 4999-5013
{
	CharacterInfo* charInfo = m_pc->CPC::GetCharacterInfo();

	std::map<int,AMOUNT_INFO>::iterator iter = m_DEFPercentList.find(in_SKID);
	if( iter == m_DEFPercentList.end() )
		return;

	charInfo->DEFPercent -= iter->second.amount;
	iter->second.time = 0;
	iter->second.amount = 0;
}


hook_func<void (__stdcall *)()> CPCBattle__GetSKCastingTM(EXEPATH(), "CPCBattle::GetSKCastingTM");
int CPCBattle::GetSKCastingTM(CSkillTypeInfo* SKTypeInfo, short skLevel, CCharacter* ch, int x, int y, int spCost) // 5602-5808
{
	int result;
	void* hookptr = CPCBattle__GetSKCastingTM;
	CCharacter* ch_ = ch;
	__asm push spCost
	__asm push y
	__asm push x
	__asm mov ecx, ch_
	__asm push skLevel
	__asm push SKTypeInfo
	__asm mov edx, this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


void CPCBattle::OnDoubleCasting(int SKID, int target, int level, int spCost) // 5826-5866
{
	if( !g_skillTypeInfoMgr.CSkillTypeInfoMgr::IsSkillCategory(SKID, SKILLTYPE_TOCHARACTER) )
		return;

	int percent = m_pc->GetEffective(EFST_DOUBLECASTING, 0);
	if( percent == 0 )
	{
		m_DoubleCastingSKID = 0;
		return;
	}

	if( m_DoubleCastingSKID != 0 )
	{
		if( m_DoubleCastingSKID == SKID )
			m_DoubleCastingSKID = 0;

		return;
	}

	if( GetServerRandom(0, 20000) % 100 < percent )
	{
		COMMAND_QUEUE command;
		command.commandID = USE_SKILL_IN;
		command.executionTime = timeGetTime() + 500;
		command.sender = m_pc->GetAccountID();
		command.par1 = SKID;
		command.par2 = target;
		command.par3 = level;
		command.par4 = 0; //spCost
		m_pc->InsertCommand(&command);

		m_DoubleCastingSKID = SKID;
	}
}


hook_func<void (__stdcall *)()> CPCBattle__MercenaryCall_Create_After(EXEPATH(), "CPCBattle::MercenaryCall_Create_After");
void CPCBattle::MercenaryCall_Create_After(const int in_Job) // 7911-7991
{
	void* hookptr = CPCBattle__MercenaryCall_Create_After;
	__asm push in_Job
	__asm mov ebx, this
	__asm call hookptr
	return; //TODO
}


hook_func<void (__stdcall *)()> CPCBattle__MercenaryCall_Delete_After(EXEPATH(), "CPCBattle::MercenaryCall_Delete_After");
void CPCBattle::MercenaryCall_Delete_After(const int in_reason) // 8131-8207
{
	void* hookptr = CPCBattle__MercenaryCall_Delete_After;
	__asm push in_reason
	__asm mov edi, this
	__asm call hookptr
	return; //TODO
}


void CPCBattle::UseAutoSpellToGround(unsigned short SKID, short xPos, short yPos, short skillLv) // 8992-9018
{
	int val = m_pc->GetEffective(EFST_MAGICPOWER, 0);
	if( val != 0 )
	{
		CSkillTypeInfo* skilltypeInfo = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
		if( skilltypeInfo == NULL )
			return;

		if( val & 0xFFFFFF00 )
			m_pc->ResetEffective(EFST_MAGICPOWER, 0);
		else
		if( skilltypeInfo->CSkillTypeInfo::GetPattern() == SKILLPATT_ATTACKSPELL )
			m_pc->UpdateEffective(EFST_MAGICPOWER, 0x100, 0);
	}

	if( !m_pc->CPC::IsSkillEnableMapProperty(SKID) )
		return;

	if( g_skillTypeInfoMgr.CSkillTypeInfoMgr::GetType(SKID) != SKILLTYPE_TOGROUND )
		return;

	MSG_TYPE1_TWODWORD posInfo;
	posInfo.data1 = xPos;
	posInfo.data2 = yPos;
	g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(m_pc, SKID, SM_USE_SKILL, skillLv, 0, (int)&posInfo, 0);
}


const CPCBattle::unionSkillStdOption* CPCBattle::GetSkillStdOption(const unsigned short in_SKID, const unsigned long in_FuncType) // 9671-9682
{
	std::map<unsigned short,LIST_FUNC_SKILLSTD>::iterator iter = m_SkillSTD.find(in_SKID);
	if( iter == m_SkillSTD.end() )
		return 0;
	
	LIST_FUNC_SKILLSTD::iterator funciter = iter->second.find(static_cast<unsigned short>(in_FuncType));
	if( funciter == iter->second.end() )
		return 0;

	return &funciter->second;
}


int CPCBattle::GetAdditionalSkillSPCost(const unsigned short in_SKID) // 9693-9698
{
	const unionSkillStdOption* option = this->CPCBattle::GetSkillStdOption(in_SKID, FUNC_ADDSKILLSP);
	if( option == NULL )
		return 0;

	return option->m_tagSkillSP.SpValue;
}


int CPCBattle::GetAdditionalSkillDelayTime(const unsigned short in_SKID) // 9709-9714
{
	const unionSkillStdOption* option = this->CPCBattle::GetSkillStdOption(in_SKID, FUNC_ADDSKILLDELAY);
	if( option == NULL )
		return 0;

	return option->m_tagSkillDelay.DelayTime;
}


int CPCBattle::GetAdditionalSkillStateCastTime(const unsigned short in_SKID) // 9725-9730
{
	const unionSkillStdOption* option = this->CPCBattle::GetSkillStdOption(in_SKID, FUNC_ADDSTATECASTTIME);
	if( option == NULL )
		return 0;

	return option->m_tagSkillStateCastTime.CastTime;
}
