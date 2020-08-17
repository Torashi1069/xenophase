#pragma once
#include "Common/Packet.h"
class CPC;


class CPCFriendClass
{
public:
	static void HPRecoveryProhibitionSet(CPC* in_cpPlayer);
	static void HPRecoveryProhibitionReset(CPC* in_cpPlayer);
	static void SPRecoveryProhibitionSet(CPC* in_cpPlayer);
	static void SPRecoveryProhibitionReset(CPC* in_cpPlayer);
	static void SetPERSONAL_INFOMATION_3ND(CPC* , const PACKET_HZ_PERSONAL_INFORMATION_2ND& , const PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO& , const PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO& , const PACKET_ZC_PERSONAL_INFOMATION::DETAIL_EXP_INFO& ); // not implemented
	static bool CheckNPCAround(CPC* in_cpPlayer);

private:
	CPCFriendClass(); // = delete;
	virtual ~CPCFriendClass(); // = delete;
};
