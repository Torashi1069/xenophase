#include "WUCSPacket.h"


/// globals
std::map<int,int> g_WUCSpacketLenMap;


void InitWUCSPacketLen()
{
	g_WUCSpacketLenMap[HEADER_AW_REQ_CONNECT]             =   -1;
	g_WUCSpacketLenMap[HEADER_WA_ACK_CONNECT_SUCCESS]     =    6;
	g_WUCSpacketLenMap[HEADER_WA_ACK_CONNECT_FAILED]      =    6;
	g_WUCSpacketLenMap[HEADER_AW_SEND_ACC_SVR_USERCOUNT]  =   29;
	g_WUCSpacketLenMap[HEADER_AW_SEND_CHAR_SVR_USERCOUNT] =   -1;
	g_WUCSpacketLenMap[HEADER_WA_RECV_COUNT_INFO_SUCCESS] =    6;
	g_WUCSpacketLenMap[HEADER_AW_SEND_CHECK_LINE]         = sizeof(PACKET_AW_SEND_CHECK_LINE); // 1010
	g_WUCSpacketLenMap[HEADER_WA_RECV_CHECK_LINE]         = sizeof(PACKET_WA_RECV_CHECK_LINE); // 1014
	g_WUCSpacketLenMap[HEADER_AW_COMPLETE_CHECK]          = sizeof(PACKET_AW_COMPLETE_CHECK);  // 14
}
