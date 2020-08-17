void Hook()
{
	#define HOOK(S) HookDB::DB().Hook(S, SymDB::Find(S), DetourFindFunction(DLLPATH(), S))
	#define HOOK_(S,S2) HookDB::DB().Hook(S, SymDB::Find(S), DetourFindFunction(DLLPATH(), S2))

	// replace exe's allocator with ours
	HookDB::DB().Hook("operator new", SymDB::Find("operator new"), (void*(*)(size_t))&::operator new);
	HookDB::DB().Hook("operator new(nothrow)", SymDB::Find("operator new(nothrow)"), (void*(*)(size_t,std::nothrow_t const &))&::operator new);
	HookDB::DB().Hook("operator delete", SymDB::Find("operator delete"), (void(*)(void*))&::operator delete);

	HOOK_("ErrorMsg(msg)", "?ErrorMsg@@YAXPBD@Z");
	HOOK_("ErrorMsg(num)", "?ErrorMsg@@YAXH@Z");
//	HOOK("GDIFlip");
	HOOK("Trace");
	HOOK("CConnection::Connect");
	HOOK("CConnection::Poll");
	HOOK("CConnection::Poll2");
	HOOK("CConnection::Disconnect");
	HOOK("CConnection::Send");
	HOOK("CConnection::Recv");
	HOOK("CConnection::ResetQueue");
	HOOK("CConnection::SetBlock");
	HOOK("CConnection::Startup");
	HOOK("CConnection::Cleanup");
	HOOK("CConnection::CheckModulePt");
	HOOK("CFile::CFile");
	HOOK("CFile::~CFile");
	HOOK("CFile::Close");
	HOOK("CFile::IsFileExist");
	HOOK("CFile::Open");
	HOOK("CFile::Read");
	HOOK("CFile::Seek");
	HOOK("CFile::Write");
	HOOK("CFileMgr::AddPak");
	HOOK("CLua::CLua");
	HOOK("CLua::~CLua");
	HOOK("CLua::Init");
	HOOK("CLua::Destroy");
//	HOOK("CLua::RegisterFuncs");
	HOOK("CLua::ErrorMsg");
	HOOK("CLua::Load");
	HOOK("CLua::Execute");
	HOOK("CPacketLengthExMgr::CPacketLengthExMgr");
	HOOK("CPacketLengthExMgr::~CPacketLengthExMgr");
	HOOK("CPacketLengthExMgr::GetReplayFactor");
	HOOK("CPacketLengthExMgr::IsFixedPacket");
	HOOK("CRagConnection::instanceR");
	HOOK("CRagConnection::GetPacketType");
	HOOK("CRagConnection::SendPacket");
	HOOK("CRagConnection::RecvPacket");
	HOOK("CReassemblyPacket::CreateInstance");
	HOOK("CReassemblyPacket::DestroyInstance");
	HOOK("CReassemblyPacket::GetObj");
	HOOK("CReassemblyPacket::Seed");
	HOOK("CReassemblyPacket::GetVal");
	HOOK("CReassemblyPacketMgr::CreateInstance");
	HOOK("CReassemblyPacketMgr::DestroyInstance");
	HOOK("XMLDocument::XMLDocument");
	HOOK("XMLDocument::~XMLDocument");
	HOOK("XMLDocument::Clear");
	HOOK("XMLDocument::ReadDocument");
	HOOK("XMLElement::XMLElement");
	HOOK("XMLElement::~XMLElement");
	HOOK("XMLElement::FindChild");
	HOOK("XMLElement::FindNext");
	HOOK("XMLElement::GetContents");
}


void UnHook()
{
}


void SymDBInitCallback()
{
	// functions
	SymDB::Add("ErrorMsg(msg)", 0x56E040);
	SymDB::Add("ErrorMsg(num)", 0x56E060);
	SymDB::Add("GDIFlip", 0x405F60);
	SymDB::Add("Trace", 0x405E50);
	SymDB::Add("CConnection::Connect", 0x6A0510);
	SymDB::Add("CConnection::Poll", 0x6A0610);
	SymDB::Add("CConnection::Poll2", 0x6A0640);
	SymDB::Add("CConnection::Disconnect", 0x69FF20);
	SymDB::Add("CConnection::Send", 0x6A0670);
	SymDB::Add("CConnection::Recv", 0x69FF60);
	SymDB::Add("CConnection::ResetQueue", 0x69FFC0);
	SymDB::Add("CConnection::SetBlock", 0x6A04B0);
	SymDB::Add("CConnection::Startup", 0x6A08F0);
	SymDB::Add("CConnection::Cleanup", 0x6A0220);
	SymDB::Add("CConnection::CheckModulePt", 0x6A0240);
	SymDB::Add("CConnection::s_wsaData", 0x932EE0);
	SymDB::Add("CConnection::s_wsmodule", 0x933074);
	SymDB::Add("CConnection::s_wsSend", 0x933078);
	SymDB::Add("CConnection::s_wsRecv", 0x933070);
	SymDB::Add("CFile::CFile", 0x584BA0);
	SymDB::Add("CFile::~CFile", 0x585140);
	SymDB::Add("CFile::Close", 0x584BB0);
	SymDB::Add("CFile::IsFileExist", 0x585860);
	SymDB::Add("CFile::Open", 0x585C00);
	SymDB::Add("CFile::Read", 0x584BF0);
	SymDB::Add("CFile::Seek", 0x584C90);
	SymDB::Add("CFile::Write", 0x584C60);
	SymDB::Add("CFileMgr::AddPak", 0x585E50);
	SymDB::Add("CLua::CLua", 0x593950);
	SymDB::Add("CLua::~CLua", 0x594380);
	SymDB::Add("CLua::Init", 0x595A80);
	SymDB::Add("CLua::Destroy", 0x593960);
	SymDB::Add("CLua::RegisterFuncs", 0x595870);
	SymDB::Add("CLua::ErrorMsg", 0x593CC0);
	SymDB::Add("CLua::Load", 0x5943A0);
	SymDB::Add("CLua::Execute", 0x594820);
	SymDB::Add("CPacketLengthExMgr::CPacketLengthExMgr", 0x59CD80);
	SymDB::Add("CPacketLengthExMgr::~CPacketLengthExMgr", 0x59CCC0);
	SymDB::Add("CPacketLengthExMgr::GetReplayFactor", 0x5973B0);
	SymDB::Add("CPacketLengthExMgr::IsFixedPacket", 0x5973E0);
	SymDB::Add("CRagConnection::instanceR", 0x6A0880);
	SymDB::Add("CRagConnection::GetPacketType", 0x6A0390);
	SymDB::Add("CRagConnection::SendPacket", 0x6A0780);
	SymDB::Add("CRagConnection::RecvPacket", 0x6A07E0);
	SymDB::Add("CReassemblyPacket::CreateInstance", 0x5A7B20);
	SymDB::Add("CReassemblyPacket::DestroyInstance", 0x5A7B00);
	SymDB::Add("CReassemblyPacket::GetObj", 0x69FE90);
	SymDB::Add("CReassemblyPacket::Seed", 0x5A7AA0);
	SymDB::Add("CReassemblyPacket::GetVal", 0x5A7AC0);
	SymDB::Add("CReassemblyPacket::m_cpSelf", 0x92C264);
	SymDB::Add("CReassemblyPacketMgr::CreateInstance", 0x5A7C80);
	SymDB::Add("CReassemblyPacketMgr::DestroyInstance", 0x5A7C50);
	SymDB::Add("CReassemblyPacketMgr::m_cpSelf", 0x92C268);
	SymDB::Add("XMLDocument::XMLDocument", 0x56B2D0);
	SymDB::Add("XMLDocument::~XMLDocument", 0x56B330);
	SymDB::Add("XMLDocument::Clear", 0x591930);
	SymDB::Add("XMLDocument::ReadDocument", 0x591BC0);
	SymDB::Add("XMLElement::XMLElement", 0x591490);
	SymDB::Add("XMLElement::~XMLElement", 0x591500);
	SymDB::Add("XMLElement::FindChild", 0x5918E0);
	SymDB::Add("XMLElement::FindNext", 0x5915B0);
	SymDB::Add("XMLElement::GetContents", 0x591760);

	// variables
	SymDB::Add("g_baseDir", 0x8B3180);
	SymDB::Add("g_baseDir3", 0x9629A8);
	SymDB::Add("g_fileMgr", 0x909F80);
	SymDB::Add("g_hMainWnd", 0x962EBC);
	SymDB::Add("g_packetLenMapEx", 0x90A9AC);
	SymDB::Add("g_readFolderFirst", 0x909F7C);

	// library functions
	SymDB::Add("operator new", 0x7C1832);
	SymDB::Add("operator new(nothrow)", 0x7C1B10);
	SymDB::Add("operator delete", 0x7C181A);
	SymDB::Add("lua_close", 0x5F0EF0);
	SymDB::Add("lua_getfield", 0x5DF110);
	SymDB::Add("lua_gettop", 0x5DE800);
	SymDB::Add("lua_settop", 0x5DE810);
	SymDB::Add("lua_gettable", 0x5DF0E0);
	SymDB::Add("lua_pcall", 0x5DF610);
	SymDB::Add("lua_pushnumber", 0x5DEE80);
	SymDB::Add("lua_pushstring", 0x5DEF00);
	SymDB::Add("lua_pushboolean", 0x5DF070);
	SymDB::Add("lua_tonumber", 0x5DEBE0);
	SymDB::Add("lua_toboolean", 0x5DEC60);
	SymDB::Add("lua_tolstring", 0x5DEC90);
	SymDB::Add("luaL_newstate", 0x5E05D0);
	SymDB::Add("luaL_checkstack", 0x5DFCF0);
	SymDB::Add("luaL_loadbuffer", 0x5E0500);
	SymDB::Add("luaL_openlibs", 0x5E8350);
}
