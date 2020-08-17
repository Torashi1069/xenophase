#include "RoomMgr.h"


CRoomMgr::CRoomMgr(void) // line 6
{
}


CRoomMgr::~CRoomMgr(void) // line 10
{
}


hook_method<void (CRoomMgr::*)(int maxcount)> CRoomMgr::_Init(SERVER, "CRoomMgr::Init");
void CRoomMgr::Init(int maxcount) // line 15
{
	return (this->*_Init)(maxcount);

	//TODO
}


hook_method<CRoom* (CRoomMgr::*)(unsigned long roomID)> CRoomMgr::_SearchRoom(SERVER, "CRoomMgr::SearchRoom");
CRoom* CRoomMgr::SearchRoom(unsigned long roomID) // line 25
{
	return (this->*_SearchRoom)(roomID);

	//TODO
}


hook_method<int (CRoomMgr::*)(unsigned long roomID, const char* name)> CRoomMgr::_ExitRoom(SERVER, "CRoomMgr::ExitRoom");
int CRoomMgr::ExitRoom(unsigned long roomID, const char* name) // line 197
{
	return (this->*_ExitRoom)(roomID, name);

	//TODO
}


hook_method<unsigned long (CRoomMgr::*)(unsigned long roomID)> CRoomMgr::_GetOwner(SERVER, "CRoomMgr::GetOwner");
unsigned long CRoomMgr::GetOwner(unsigned long roomID) // line 212
{
	return (this->*_GetOwner)(roomID);

	CRoom* room = this->CRoomMgr::SearchRoom(roomID);
	return ( room != NULL ) ? room->CRoom::GetOwner() : 0;
}
