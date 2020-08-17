#include "Enum.h"
#include "PC.h"
#include "PCClientUpdater.h"


CPCClientUpdater::CPCClientUpdater() // 90-91
{
}


CPCClientUpdater::~CPCClientUpdater() // 94-95
{
}


void CPCClientUpdater::SetMyOwner(CPC* pc) // 98-100
{
	m_pc = pc;
}


void CPCClientUpdater::Init() // 103-106
{
	m_pc->m_dwErrorCount = 0;
	m_disconnectType = NORMAL_DISCONNECT;
}


void CPCClientUpdater::SetAccountID(int AccountID) // 109-111
{
	m_pc->m_characterInfo.accountID = AccountID;
}


void CPCClientUpdater::SetCharacterID(int CharacterID) // 114-117
{
	m_pc->m_characterInfo.characterID = CharacterID;
}


unsigned long CPCClientUpdater::GetAccountID() // 120-122
{
	return m_pc->m_characterInfo.accountID;
}


unsigned long CPCClientUpdater::GetCharacterID() // 125-127
{
	return m_pc->m_characterInfo.characterID;
}


void CPCClientUpdater::SetAuthCode(int AuthCode) // 245-247
{
	m_pc->m_characterInfo.AuthCode = AuthCode;
}


int CPCClientUpdater::GetAuthCode()
{
	return m_pc->m_characterInfo.AuthCode;
}


BOOL CPCClientUpdater::IsSendable() // 255-257
{
	return m_pc->m_characterInfo.isSendable;
}


void CPCClientUpdater::SetSendable(BOOL isActive) // 260-262
{
	m_pc->m_characterInfo.isSendable = isActive;
}


BOOL CPCClientUpdater::IsMyArea(CCharacter* other, int Range) // 265-278
{
	int x, y, mapID;
	other->GetParameterValue(VAR_MAPID, mapID);
	if( !other->GetParameterValue(VAR_CURXPOS, x) )
		return FALSE;
	if( !other->GetParameterValue(VAR_CURYPOS, y) )
		return FALSE;

	return ( abs(m_pc->m_pathInfo.m_moveInfo.xPos - x) <= Range && abs(m_pc->m_pathInfo.m_moveInfo.yPos - y) <= Range && m_pc->m_characterInfo.mapID == mapID );
}


BOOL CPCClientUpdater::IsMyArea(CCharacter* other, int xRange, int yRange) // 281-295
{
	int x, y, mapID;
	other->GetParameterValue(VAR_CURXPOS, x);
	other->GetParameterValue(VAR_CURYPOS, y);
	other->GetParameterValue(VAR_MAPID, mapID);

	return ( abs(m_pc->m_pathInfo.m_moveInfo.xPos - x) <= xRange && abs(m_pc->m_pathInfo.m_moveInfo.yPos - y) <= yRange && m_pc->m_characterInfo.mapID == mapID );
}


void CPCClientUpdater::StopMove() // 298-310
{
	if( m_pc->GetEffective(EFST_RUN, 0) )
		return;

	if( m_pc->GetEffective(EFST_WUGDASH, 0) )
		return;

	if( m_pc->m_pathInfo.m_moveInfo.state == CHARACTER_STATE_MOVE )
	{
		m_pc->m_pathInfo.m_moveInfo.state = CHARACTER_STATE_STAND;
		m_pc->m_pathInfo.CPathInfo::Reset();
	}
}


void CPCClientUpdater::SetIndex(int index) // 337-339
{
	m_pc->m_index = index;
}


hook_func<void (CPCClientUpdater::*)(unsigned short type, int count)> CPCClientUpdater__NotifyParameter(EXEPATH(), "CPCClientUpdater::NotifyParameter");
void CPCClientUpdater::NotifyParameter(unsigned short type, int count) // 633-738
{
	return (this->*CPCClientUpdater__NotifyParameter)(type, count); //TODO
}


hook_func<void (CPCClientUpdater::*)(unsigned short varID, int amount)> CPCClientUpdater__NotifyLongParameter(EXEPATH(), "CPCClientUpdater::NotifyLongParameter");
void CPCClientUpdater::NotifyLongParameter(unsigned short varID, int amount) // 743-1074
{
	return (this->*CPCClientUpdater__NotifyLongParameter)(varID, amount); //TODO
}


hook_func<void (__stdcall *)()> CPCClientUpdater__OnDead(EXEPATH(), "CPCClientUpdater::OnDead");
void CPCClientUpdater::OnDead(unsigned long enemyAID) // 1089-1255
{
	void* hookptr = CPCClientUpdater__OnDead;
	__asm push enemyAID
	__asm mov ebx, this
	__asm call hookptr
	return; //TODO
}


void CPCClientUpdater::ReStart(unsigned long NAID) // 1258-1267
{
	m_pc->m_characterInfo.deadCount = 0;
	m_pc->CPC::DisableAllCommand();

	if( m_pc->m_characterInfo.reinCarnation )
	{
		m_pc->UpdateParameterValue(VAR_HP, m_pc->CPC::GetMaxHP());
		m_pc->UpdateParameterValue(VAR_SP, m_pc->CPC::GetMaxSP());
	}

	this->CPCClientUpdater::MapMove(m_pc->CPC::GetRestartMapName(), m_pc->m_characterInfo.sxPos, m_pc->m_characterInfo.syPos, 0, NORMAL_DISCONNECT);
}


hook_func<void (CPCClientUpdater::*)(const unsigned long in_NAID, const int in_TargetSvrID)> CPCClientUpdater__MapMove_OtherServer_Part2(EXEPATH(), "CPCClientUpdater::MapMove_OtherServer_Part2");
void CPCClientUpdater::MapMove_OtherServer_Part2(const unsigned long in_NAID, const int in_TargetSvrID) // 1636-1697
{
	return (this->*CPCClientUpdater__MapMove_OtherServer_Part2)(in_NAID, in_TargetSvrID); //TODO
}


hook_func<void (__stdcall *)()> CPCClientUpdater__MapMove(EXEPATH(), "CPCClientUpdater::MapMove");
int CPCClientUpdater::MapMove(const char* mapName, short xPos, short yPos, unsigned long NAID, int type) // 1739-2147
{
	int result;
	void* hookptr = CPCClientUpdater__MapMove;
	int type_ = type;
	__asm push type_
	__asm push NAID
	__asm push yPos
	__asm push xPos
	__asm push mapName
	__asm push this
	__asm call hookptr
	__asm mov result, eax
	return result; //TODO
}


void CPCClientUpdater::NotifySpriteChange(CPC* other, int type, int value) // 2838-2854
{
	if( other == NULL )
		return;

	PACKET_ZC_SPRITE_CHANGE2 outpacket;
	outpacket.PacketType = HEADER_ZC_SPRITE_CHANGE2;
	outpacket.GID = this->CPCClientUpdater::GetAccountID();
	outpacket.value = value;
	outpacket.type = type;
	other->Send(sizeof(outpacket), (const char*)&outpacket);
	if( type == SPRITETYPE_JOB )
		other->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}
