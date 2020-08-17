#include "MonitorPacket.h"


/// globals
stdext::hash_map<int,int> g_monitor_pkt_len_map;


void InitMonitorPktLenMap()
{
	g_monitor_pkt_len_map[0] =  2; // HEADER_MA_REQ_HASH
	g_monitor_pkt_len_map[1] = -1; // HEADER_AM_RES_HASH
	g_monitor_pkt_len_map[2] = 28; // HEADER_MA_ENTER
	g_monitor_pkt_len_map[3] =  2; // HEADER_AM_ACCEPT_ENTER
	g_monitor_pkt_len_map[4] =  6; // HEADER_AM_REFUSE_ENTER
	g_monitor_pkt_len_map[5] = -1; // HEADER_AM_SERVER_STATE
	g_monitor_pkt_len_map[6] =  3; // HEADER_MA_CTRL_USER_CONNECTION
};
