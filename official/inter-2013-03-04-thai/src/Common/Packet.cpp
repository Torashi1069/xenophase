#include "Common/Packet.h"
#include "Common/PacketLengthExMgr.h"


/// globals
CPacketLengthExMgr& g_packetLenMapEx = VTOR<CPacketLengthExMgr>(DetourFindFunction(EXEPATH(), "g_packetLenMapEx"));
