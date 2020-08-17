#include "Character.h"
#include "CharacterMgr.h"
#include "CharSkill.h"
#include "Common/Packet.h"


void SendPacket_ZC_NOTIFY_ACT(CCharacter* in_toCharacter, const unsigned long in_GID, const unsigned long in_targetGID, const unsigned long in_startTime, const int in_attackMT, const int in_attackedMT, int in_damage, const short in_count, const unsigned char in_action, const int in_leftDamage) // 2081-2102 (3877-3926)
{
	PACKET_ZC_NOTIFY_ACT2 outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_ACT2;
	outpacket.GID = in_GID;
	outpacket.targetGID = in_targetGID;
	outpacket.action = in_action;
	outpacket.damage = in_damage;
	outpacket.leftDamage = in_leftDamage;
	outpacket.count = in_count;
	outpacket.attackMT = in_attackMT;
	outpacket.attackedMT = in_attackedMT;
	outpacket.startTime = in_startTime;
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(in_toCharacter, (CCharacter*)NULL, CM_SEND_DAMAGEPACKET, sizeof(outpacket), (int)&outpacket, 0, 0);
}
