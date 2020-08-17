#include "Common/NOutputTextMgr.h"
#include "Common/NSyncObject.h"


/// singleton instance
NOutputTextMgr* NOutputTextMgr::m_cpSelf;


NOutputTextMgr::NOutputTextMgr()
{
	m_LineCnt = 0;
	m_bOK = false;

	InitializeCriticalSection(&m_CS);
	m_bOK = true;
}


NOutputTextMgr::~NOutputTextMgr()
{
	DeleteCriticalSection(&m_CS);
}


bool NOutputTextMgr::CreateInstance()
{
	if( m_cpSelf != NULL )
		return false;

	m_cpSelf = new(std::nothrow) NOutputTextMgr();
	if( m_cpSelf == NULL )
		return false;

	if( !m_cpSelf->m_bOK )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
		return false;
	}

	return true;
}


void NOutputTextMgr::DestroyInstance()
{
	if( m_cpSelf != NULL )
	{
		delete m_cpSelf;
		m_cpSelf = NULL;
	}
}


/// @custom
NOutputTextMgr* NOutputTextMgr::GetObj()
{
	return m_cpSelf;
}


bool NOutputTextMgr::isOK() const
{
	return m_bOK;
}


void NOutputTextMgr::Insert(const std::string in_msg)
{
	if( this == NULL )
		return; // ???

	NSyncObject sync(m_CS);

	SYSTEMTIME st;
	GetLocalTime(&st);

	char buffer[2048] = "00:00:00:0000";
	sprintf_s(buffer, sizeof(buffer), "[%02d:%02d:%02d:%04d] %s", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds, in_msg.c_str());

	++m_LineCnt;

	m_Note.insert(std::pair<unsigned int,std::vector<char>>(m_LineCnt, std::vector<char>(buffer, buffer + strlen(buffer))));

	if( m_Note.size() > 50 )
		m_Note.erase(m_Note.begin());
}


void NOutputTextMgr::InsertFmt(const char* in_pFmt, ...)
{
	if( in_pFmt == NULL )
		return;

	va_list va;
	va_start(va, in_pFmt);

	char Buffer[2048+1] = {};
	_vsnprintf_s(Buffer, sizeof(Buffer)-1, _TRUNCATE, in_pFmt, va);

	this->NOutputTextMgr::Insert(Buffer);
}


unsigned int NOutputTextMgr::GetMaxLineCnt()
{
	NSyncObject sync(m_CS);
	return m_LineCnt;
}


std::string NOutputTextMgr::GetText(const unsigned int in_LineCnt)
{
	NSyncObject sync(m_CS);

	std::map<unsigned int,std::vector<char>>::iterator it = m_Note.find(in_LineCnt);
	if( it == m_Note.end() )
		return "";
	
	return std::string(it->second.begin(), it->second.end());
}
