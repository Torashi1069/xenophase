#include "CharacterMgr.h"
#include "PC.h"
#include "NpcServer/NpcEvent.h"


/// static members
int& CNpcEvent::m_serverID = VTOR<int>(DetourFindFunction(EXEPATH(), "CNpcEvent::m_serverID"));


bool CNpcEvent::FuncCart(BOOL flag) // 3037-3053
{
	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_pcId, PC_TYPE);
	if( pc == NULL )
		return false;

	if( flag )
	{
		CNPC2ZMsg msg;
		msg.CMsg::SetMsgID(NPC2ZMSG_CARTON);
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsgFromNPCServer(m_pcId, m_npcId, &msg, 0, 0);
	}
	else
	{
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, pc, CM_CARTOFF, 0, 0, 0, 0);
	}

	this->EventLog("cart [on/off] %d\n", flag);
	return true;
}
