#pragma once
class CCharacter;


void SendPacket_ZC_NOTIFY_ACT(CCharacter* in_toCharacter, const unsigned long in_GID, const unsigned long in_targetGID, const unsigned long in_startTime, const int in_attackMT, const int in_attackedMT, int in_damage, const short in_count, const unsigned char in_action, const int in_leftDamage);
