#include "HSvrIO.h"


CHSvrIO::CHSvrIO(void) // line 9
{
}


CHSvrIO::~CHSvrIO(void) // line 14
{
}


//hook_method<CHSvrIOPacketHandler* (CHSvrIO::*)(void)> CHSvrIO::_GetPacketHandlerPtr(SERVER, "CHSvrIO::GetPacketHandlerPtr");
CHSvrIOPacketHandler* CHSvrIO::GetPacketHandlerPtr(void) // line ??
{
//	return (this->*_GetPacketHandlerPtr)();

	return (CHSvrIOPacketHandler*)m_packetHandler;
}
