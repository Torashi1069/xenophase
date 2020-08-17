#include "MSPacketHandler.h"


CMCPacketHandler::CMCPacketHandler(void)
{
}


CMCPacketHandler::~CMCPacketHandler(void)
{
}


hook_method<void (CMCPacketHandler::*)(void)> CMCPacketHandler::_OnClose(SERVER, "CMCPacketHandler::OnClose");
void CMCPacketHandler::OnClose(void)
{
	return (this->*_OnClose)();

	//TODO
}


hook_method<int (CMCPacketHandler::*)(void)> CMCPacketHandler::_OnProcess(SERVER, "CMCPacketHandler::OnProcess");
int CMCPacketHandler::OnProcess(void)
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<void (CMCPacketHandler::*)(CMClient* mServer)> CMCPacketHandler::_SetMyOwner(SERVER, "CMCPacketHandler::SetMyOwner");
void CMCPacketHandler::SetMyOwner(CMClient* mServer)
{
	return (this->*_SetMyOwner)(mServer);

	//TODO
}


hook_method<int (CMCPacketHandler::*)(short Header, int packetSize)> CMCPacketHandler::_DispatchPacket(SERVER, "CMCPacketHandler::DispatchPacket");
int CMCPacketHandler::DispatchPacket(short Header, int packetSize)
{
	return (this->*_DispatchPacket)(Header, packetSize);

	//TODO
}


hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIEnter(SERVER, "CMCPacketHandler::OnMIEnter");
void CMCPacketHandler::OnMIEnter(int len)
{
	return (this->*_OnMIEnter)(len);

	//TODO
}


hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIReqServerState(SERVER, "CMCPacketHandler::OnMIReqServerState");
void CMCPacketHandler::OnMIReqServerState(int len)
{
	return (this->*_OnMIReqServerState)(len);

	//TODO
}


hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIMsg(SERVER, "CMCPacketHandler::OnMIMsg");
void CMCPacketHandler::OnMIMsg(int len)
{
	return (this->*_OnMIMsg)(len);

	//TODO
}


hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIShotDown(SERVER, "CMCPacketHandler::OnMIShotDown");
void CMCPacketHandler::OnMIShotDown(int len)
{
	return (this->*_OnMIShotDown)(len);

	//TODO
}


hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIGetGuildInfo(SERVER, "CMCPacketHandler::OnMIGetGuildInfo");
void CMCPacketHandler::OnMIGetGuildInfo(int len)
{
	return (this->*_OnMIGetGuildInfo)(len);

	//TODO
}


hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIGuildInfoInit(SERVER, "CMCPacketHandler::OnMIGuildInfoInit");
void CMCPacketHandler::OnMIGuildInfoInit(int len)
{
	return (this->*_OnMIGuildInfoInit)(len);

	//TODO
}


hook_method<void (CMCPacketHandler::*)(int len)> CMCPacketHandler::_OnMIAllyGuildInfoInit(SERVER, "CMCPacketHandler::OnMIAllyGuildInfoInit");
void CMCPacketHandler::OnMIAllyGuildInfoInit(int len)
{
	return (this->*_OnMIAllyGuildInfoInit)(len);

	//TODO
}
