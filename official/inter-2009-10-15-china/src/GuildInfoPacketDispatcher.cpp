#include "GuildInfoPacketDispatcher.h"


CIGuildInfoPacketDispatcher::CIGuildInfoPacketDispatcher(void) // line 23
{
}


CIGuildInfoPacketDispatcher::~CIGuildInfoPacketDispatcher(void) // line 28
{
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnAllyGuild(SERVER, "CIGuildInfoPacketDispatcher::OnAllyGuild");
void CIGuildInfoPacketDispatcher::OnAllyGuild(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnAllyGuild)(GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnChangeMaxUser(SERVER, "CIGuildInfoPacketDispatcher::OnChangeMaxUser");
void CIGuildInfoPacketDispatcher::OnChangeMaxUser(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnChangeMaxUser)(GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnGuildNotice(SERVER, "CIGuildInfoPacketDispatcher::OnGuildNotice");
void CIGuildInfoPacketDispatcher::OnGuildNotice(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnGuildNotice)(GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnRegisterGuildEmblem(SERVER, "CIGuildInfoPacketDispatcher::OnRegisterGuildEmblem");
void CIGuildInfoPacketDispatcher::OnRegisterGuildEmblem(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnRegisterGuildEmblem)(GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnReqGuildPositionInfo(SERVER, "CIGuildInfoPacketDispatcher::OnReqGuildPositionInfo");
void CIGuildInfoPacketDispatcher::OnReqGuildPositionInfo(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnReqGuildPositionInfo)(GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnReqChangePosition(SERVER, "CIGuildInfoPacketDispatcher::OnReqChangePosition");
void CIGuildInfoPacketDispatcher::OnReqChangePosition(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnReqChangePosition)(GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnGuildSkillUpdate(SERVER, "CIGuildInfoPacketDispatcher::OnGuildSkillUpdate");
void CIGuildInfoPacketDispatcher::OnGuildSkillUpdate(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnGuildSkillUpdate)(GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnAddExp(SERVER, "CIGuildInfoPacketDispatcher::OnAddExp");
void CIGuildInfoPacketDispatcher::OnAddExp(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnAddExp)(GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnGuildChat(SERVER, "CIGuildInfoPacketDispatcher::OnGuildChat");
void CIGuildInfoPacketDispatcher::OnGuildChat(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnGuildChat)(ZSID, GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnReqLeaveGuild(SERVER, "CIGuildInfoPacketDispatcher::OnReqLeaveGuild");
void CIGuildInfoPacketDispatcher::OnReqLeaveGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnReqLeaveGuild)(ZSID, GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnReqBanGuild(SERVER, "CIGuildInfoPacketDispatcher::OnReqBanGuild");
void CIGuildInfoPacketDispatcher::OnReqBanGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnReqBanGuild)(ZSID, GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnJoinGuild(SERVER, "CIGuildInfoPacketDispatcher::OnJoinGuild");
void CIGuildInfoPacketDispatcher::OnJoinGuild(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnJoinGuild)(ZSID, GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_OnUpdateGuildZeny(SERVER, "CIGuildInfoPacketDispatcher::OnUpdateGuildZeny");
void CIGuildInfoPacketDispatcher::OnUpdateGuildZeny(unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_OnUpdateGuildZeny)(GDID, PacketType, Len, buf);

	//TODO
}


hook_method<void (CIGuildInfoPacketDispatcher::*)(CIGuildInfo* Info)> CIGuildInfoPacketDispatcher::_SetGuildInfo(SERVER, "CIGuildInfoPacketDispatcher::SetGuildInfo");
void CIGuildInfoPacketDispatcher::SetGuildInfo(CIGuildInfo* Info)
{
	return (this->*_SetGuildInfo)(Info);

	//TODO
}


hook_method<int (CIGuildInfoPacketDispatcher::*)(void)> CIGuildInfoPacketDispatcher::_OnProcess(SERVER, "CIGuildInfoPacketDispatcher::OnProcess");
int CIGuildInfoPacketDispatcher::OnProcess(void)
{
	return (this->*_OnProcess)();

	//TODO
}


hook_method<int (CIGuildInfoPacketDispatcher::*)(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)> CIGuildInfoPacketDispatcher::_DispatchPacket(SERVER, "CIGuildInfoPacketDispatcher::DispatchPacket");
int CIGuildInfoPacketDispatcher::DispatchPacket(unsigned long ZSID, unsigned long GDID, short PacketType, unsigned short Len, char* buf)
{
	return (this->*_DispatchPacket)(ZSID, GDID, PacketType, Len, buf);

	switch( PacketType )
	{
	case 10579: this->CIGuildInfoPacketDispatcher::OnJoinGuild(ZSID, GDID, PacketType, Len, buf); break;
	case 10568: this->CIGuildInfoPacketDispatcher::OnReqBanGuild(ZSID, GDID, PacketType, Len, buf); break;
	case 10591: this->CIGuildInfoPacketDispatcher::OnGuildNotice(GDID, PacketType, Len, buf); break;
	case 10603: this->CIGuildInfoPacketDispatcher::OnGuildChat(ZSID, GDID, PacketType, Len, buf); break;
	case 10605: this->CIGuildInfoPacketDispatcher::OnAddExp(GDID, PacketType, Len, buf); break;
	case 10614: this->CIGuildInfoPacketDispatcher::OnUpdateGuildZeny(GDID, PacketType, Len, buf); break;
	case 10566: this->CIGuildInfoPacketDispatcher::OnReqLeaveGuild(ZSID, GDID, PacketType, Len, buf); break;
	case 10634: this->CIGuildInfoPacketDispatcher::OnChangeMaxUser(GDID, PacketType, Len, buf); break;
	case 10558: this->CIGuildInfoPacketDispatcher::OnRegisterGuildEmblem(GDID, PacketType, Len, buf); break;
	case 10572: this->CIGuildInfoPacketDispatcher::OnReqGuildPositionInfo(GDID, PacketType, Len, buf); break;
	case 10562: this->CIGuildInfoPacketDispatcher::OnReqChangePosition(GDID, PacketType, Len, buf); break;
	case 10629: this->CIGuildInfoPacketDispatcher::OnGuildSkillUpdate(GDID, PacketType, Len, buf); break;
	default:
		break;
	}

	return -1;
}
