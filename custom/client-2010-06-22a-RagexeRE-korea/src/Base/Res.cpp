#include "Base/Res.h"
#include "Globals.h"
////////////////////////////////////////


CRes::CRes(void)
: m_lockCnt(0), m_fName("")
{
}


CRes::~CRes(void)
{
}


hook_func<bool (CRes::*)(const char* fName, const unsigned char* buffer, int size)> CRes::_LoadFromBuffer("CRes::LoadFromBuffer");
bool CRes::LoadFromBuffer(const char* fName, const unsigned char* buffer, int size)
{
	return (this->*_LoadFromBuffer)(fName, buffer, size);

	//TODO
}


const char* CRes::GetName(void)
{
	return m_fName.CHash::c_str();
}


hook_func<void (CRes::*)(void)> CRes::_Reset("CRes::Reset");
void CRes::Reset(void)
{
	return (this->*_Reset)();

	//TODO
}


void CRes::OnLoadError(const char* fName)
{
	char msg[256];
	sprintf(msg, "ResourceError : Can't find file %s\n", fName);
	ErrorMsg(msg);
}


int CRes::Lock()
{
	++m_lockCnt;
	return m_lockCnt;
}


int CRes::Unlock()
{
	m_timeStamp = timeGetTime();
	--m_lockCnt;
	return m_lockCnt;
}


////////////////////////////////////////


hook_func<void (CResMgr::*)(void)> CResMgr::_Reset("CResMgr::Reset");
void CResMgr::Reset(void)
{
	return (this->*_Reset)();
}


hook_func<CRes* (CResMgr::*)(const char* fNameInput)> CResMgr::_Get("CResMgr::Get");
CRes* CResMgr::Get(const char* fNameInput)
{
	return (this->*_Get)(fNameInput);
}


hook_func<int (CResMgr::*)(const char* fNameInput)> CResMgr::_IsExist("CResMgr::IsExist");
int CResMgr::IsExist(const char* fNameInput)
{
	return (this->*_IsExist)(fNameInput);

	//TODO
}


hook_func<void (CResMgr::*)(const char* resNameTable)> CResMgr::_ReadResNameTable("CResMgr::ReadResNameTable");
void CResMgr::ReadResNameTable(const char* resNameTable)
{
	return (this->*_ReadResNameTable)(resNameTable);

	//TODO
}


hook_func<void (CResMgr::*)(const char* resId, const char* baseDir, CRes* t)> CResMgr::_RegisterType("CResMgr::RegisterType");
void CResMgr::RegisterType(const char* resId, const char* baseDir, CRes* t)
{
	return (this->*_RegisterType)(resId, baseDir, t);

	//TODO
}


////////////////////////////////////////


hook_func<CResMgr& (__cdecl *)()> _g_resMgr("g_resMgr");
CResMgr& __cdecl g_resMgr()
{
	return _g_resMgr();

	//TODO
}


////////////////////////////////////////
