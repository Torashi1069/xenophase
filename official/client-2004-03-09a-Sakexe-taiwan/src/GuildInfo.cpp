#include "GuildInfo.h"


GuildInfo::GuildInfo(void) // line 9
{
	this->GuildInfo::Init();
}


GuildInfo::~GuildInfo(void) // line 14
{
}


hook_method<void (GuildInfo::*)(void)> GuildInfo::_Init(SAKEXE, "GuildInfo::Init");
void GuildInfo::Init(void) // line 35
{
	return (this->*_Init)();

	m_gdid = 0;
	m_emblemVersion = 0;
	m_rightJoin = 0;
	m_rightPunish = 0;
	m_amIMaster = 0;
	m_guildTabBitmask = -1;
	m_isRequestInfo[0] = 0;
	m_isRequestInfo[1] = 0;
	m_isRequestInfo[2] = 0;
	m_isRequestInfo[3] = 0;
	m_isRequestInfo[4] = 0;
	m_guildName = "";
	m_masterName = "";
	m_subjectName = "";
	m_noticeName = "";
	m_guildLevel = 0;
	m_numMember = 0;
	m_numMaxMember = 0;
	m_memberAvgLevel = 0;
	m_manageLand = "";
	m_exp = 0;
	m_nextExp = 0;
	m_emblem = 0;
	m_point = 0;
	m_honor = 0;
	m_virtue = 0;
	m_zeny = 0;
	m_posInfoList.clear();
	m_memberInfoList.clear();
	m_relatedGuildInfoList.clear();
	m_banishList.clear();
	m_guildList.clear();
	m_positionIdNameMap.clear();
	m_memberPositionInfoListForChange.clear();
	m_changedPositionInfoList.clear();
}


hook_method<void (GuildInfo::*)(void)> GuildInfo::_Init2(SAKEXE, "GuildInfo::Init");
void GuildInfo::Init2(void)
{
	return (this->*_Init2)();

	// backup
	int gdid = m_gdid;
	int emblemVersion = m_emblemVersion;
	int rightJoin = m_rightJoin;
	int rightPunish = m_rightPunish;
	int amIMaster = m_amIMaster;

	// reset
	this->GuildInfo::Init();

	// restore
	m_gdid = gdid;
	m_emblemVersion = emblemVersion;
	m_rightJoin = rightJoin;
	m_rightPunish = rightPunish;
	m_amIMaster = amIMaster;
}


hook_method<void (GuildInfo::*)(unsigned long AID, int status)> GuildInfo::_SetMemberInfoState(SAKEXE, "GuildInfo::SetMemberInfoState");
void GuildInfo::SetMemberInfoState(unsigned long AID, int status)
{
	return (this->*_SetMemberInfoState)(AID, status);

	//TODO
}


hook_method<void (GuildInfo::*)(unsigned long AID, int status, unsigned long GID, short sex, short head, short headPalette)> GuildInfo::_SetMemberInfoState2(SAKEXE, "GuildInfo::SetMemberInfoState2");
void GuildInfo::SetMemberInfoState2(unsigned long AID, int status, unsigned long GID, short sex, short head, short headPalette)
{
	return (this->*_SetMemberInfoState2)(AID, status, GID, sex, head, headPalette);

	//TODO
}


hook_method<void (GuildInfo::*)(int AID, int GID, int positionID)> GuildInfo::_ChangeMemberPosition(SAKEXE, "GuildInfo::ChangeMemberPosition");
void GuildInfo::ChangeMemberPosition(int AID, int GID, int positionID)
{
	return (this->*_ChangeMemberPosition)(AID, GID, positionID);

	//TODO
}


hook_method<void (GuildInfo::*)(int gdid, int relation)> GuildInfo::_DeleteRelatedGuild(SAKEXE, "GuildInfo::DeleteRelatedGuild");
void GuildInfo::DeleteRelatedGuild(int gdid, int relation)
{
	return (this->*_DeleteRelatedGuild)(gdid, relation);

	//TODO
}


hook_method<int (GuildInfo::*)(int relation)> GuildInfo::_GetNumRelatedGuild(SAKEXE, "GuildInfo::GetNumRelatedGuild");
int GuildInfo::GetNumRelatedGuild(int relation)
{
	return (this->*_GetNumRelatedGuild)(relation);

	int result = 0;

	for( mystd::list<RELATED_GUILD_INFORMATION>::const_iterator i = m_relatedGuildInfoList.begin(); i != m_relatedGuildInfoList.end(); ++i )
	{
		if( i->relation == relation )
			++result;
	}

	return result;
}


class hook_ptr<struct mystd::_Tree<int,struct mystd::pair<int const ,struct MEMBER_POSITION_INFORMATION>,struct mystd::map<int,struct MEMBER_POSITION_INFORMATION,struct mystd::less<int>,class mystd::allocator<struct MEMBER_POSITION_INFORMATION> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct MEMBER_POSITION_INFORMATION> >::_Node *> mystd::_Tree<int,struct mystd::pair<int const ,struct MEMBER_POSITION_INFORMATION>,struct mystd::map<int,struct MEMBER_POSITION_INFORMATION,struct mystd::less<int>,class mystd::allocator<struct MEMBER_POSITION_INFORMATION> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct MEMBER_POSITION_INFORMATION> >::_Nil(SAKEXE, "?_Nil@?$_Tree@HU?$pair@$$CBHUMEMBER_POSITION_INFORMATION@@@std@@U_Kfn@?$map@HUMEMBER_POSITION_INFORMATION@@U?$less@H@std@@V?$allocator@UMEMBER_POSITION_INFORMATION@@@3@@2@U?$less@H@2@V?$allocator@UMEMBER_POSITION_INFORMATION@@@2@@std@@1PAU_Node@12@A");
class hook_val<unsigned int> mystd::_Tree<int,struct mystd::pair<int const ,struct MEMBER_POSITION_INFORMATION>,struct mystd::map<int,struct MEMBER_POSITION_INFORMATION,struct mystd::less<int>,class mystd::allocator<struct MEMBER_POSITION_INFORMATION> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct MEMBER_POSITION_INFORMATION> >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@HU?$pair@$$CBHUMEMBER_POSITION_INFORMATION@@@std@@U_Kfn@?$map@HUMEMBER_POSITION_INFORMATION@@U?$less@H@std@@V?$allocator@UMEMBER_POSITION_INFORMATION@@@3@@2@U?$less@H@2@V?$allocator@UMEMBER_POSITION_INFORMATION@@@2@@std@@1IA");
class hook_ptr<struct mystd::_Tree<int,struct mystd::pair<int const ,struct GUILD_POSITION_INFORMATION>,struct mystd::map<int,struct GUILD_POSITION_INFORMATION,struct mystd::less<int>,class mystd::allocator<struct GUILD_POSITION_INFORMATION> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct GUILD_POSITION_INFORMATION> >::_Node *> mystd::_Tree<int,struct mystd::pair<int const ,struct GUILD_POSITION_INFORMATION>,struct mystd::map<int,struct GUILD_POSITION_INFORMATION,struct mystd::less<int>,class mystd::allocator<struct GUILD_POSITION_INFORMATION> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct GUILD_POSITION_INFORMATION> >::_Nil(SAKEXE, "?_Nil@?$_Tree@HU?$pair@$$CBHUGUILD_POSITION_INFORMATION@@@std@@U_Kfn@?$map@HUGUILD_POSITION_INFORMATION@@U?$less@H@std@@V?$allocator@UGUILD_POSITION_INFORMATION@@@3@@2@U?$less@H@2@V?$allocator@UGUILD_POSITION_INFORMATION@@@2@@std@@1PAU_Node@12@A");
class hook_val<unsigned int> mystd::_Tree<int,struct mystd::pair<int const ,struct GUILD_POSITION_INFORMATION>,struct mystd::map<int,struct GUILD_POSITION_INFORMATION,struct mystd::less<int>,class mystd::allocator<struct GUILD_POSITION_INFORMATION> >::_Kfn,struct mystd::less<int>,class mystd::allocator<struct GUILD_POSITION_INFORMATION> >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@HU?$pair@$$CBHUGUILD_POSITION_INFORMATION@@@std@@U_Kfn@?$map@HUGUILD_POSITION_INFORMATION@@U?$less@H@std@@V?$allocator@UGUILD_POSITION_INFORMATION@@@3@@2@U?$less@H@2@V?$allocator@UGUILD_POSITION_INFORMATION@@@2@@std@@1IA");
class hook_ptr<struct mystd::_Tree<int,struct mystd::pair<int const ,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,struct mystd::map<int,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::less<int>,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Kfn,struct mystd::less<int>,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Node *> mystd::_Tree<int,struct mystd::pair<int const ,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,struct mystd::map<int,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::less<int>,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Kfn,struct mystd::less<int>,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Nil(SAKEXE, "?_Nil@?$_Tree@HU?$pair@$$CBHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@U_Kfn@?$map@HV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$less@H@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocatorf457d560");
class hook_val<unsigned int> mystd::_Tree<int,struct mystd::pair<int const ,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > >,struct mystd::map<int,class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> >,struct mystd::less<int>,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Kfn,struct mystd::less<int>,class mystd::allocator<class mystd::basic_string<char,struct mystd::char_traits<char>,class mystd::allocator<char> > > >::_Nilrefs(SAKEXE, "?_Nilrefs@?$_Tree@HU?$pair@$$CBHV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@std@@U_Kfn@?$map@HV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@U?$less@H@2@V?$allocator@V?$basic_string@DU?$char_traits@D@std@@V?$allocd7356836");
