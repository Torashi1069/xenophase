#include "Globals.h" // ErrorMsg()
#include "Base/Res.h"


CRes::CRes()
: m_lockCnt(0), m_fName("")
{
}


CRes::~CRes()
{
}


bool CRes::LoadFromBuffer(const char* fName, const unsigned char* buffer, int size)
{
	return false;
}


int CRes::Lock()
{
	return ++m_lockCnt;
}


int CRes::Unlock()
{
	m_timeStamp = timeGetTime();
	return --m_lockCnt;
}


const char* CRes::GetName()
{
	return m_fName.CHash::c_str();
}


void CRes::UpdateInfo(const char* fName, int extIndex)
{
	m_fName.CHash::SetString(fName);
	m_extIndex = extIndex;
	m_timeStamp = timeGetTime();
}


void CRes::UpdateTimeStamp()
{
	m_timeStamp = timeGetTime();
}


void CRes::Reset()
{
}


void CRes::OnLoadError(const char* fName)
{
	char msg[255];
	sprintf(msg, "ResourceError : Can't find file %s\n", fName);

	ErrorMsg(msg);
}
