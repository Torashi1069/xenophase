#include "Enum.h"
#include "MServer.h"


CMClient::CMClient()
{
	m_IPaddr = INADDR_ANY;
}


CMClient::~CMClient()
{
}


void CMClient::Init(CAsyncStream* in_cpAsyncStream, unsigned long in_IPaddr)
{
	this->CMClient::SetValid(0);
	m_packetHandler.CMCPacketHandler::SetMyOwner(this);
	m_dwErrorCount = 0;
	m_nBanTime = 0;
	m_asyncStream = in_cpAsyncStream;
	m_IPaddr = in_IPaddr;
	m_lastCommunicationTime = timeGetTime();
}


void CMClient::SetServerID(int SID)
{
	m_SID = SID;
}


int CMClient::GetServerID()
{
	return m_SID;
}


int CMClient::OnProcess()
{
	if( timeGetTime() - m_lastCommunicationTime >= 60000 )
		return 0;

	if( m_packetHandler.OnProcess() != -1 )
		return 0;

	return -1;
}


unsigned long CMClient::GetAccountID()
{
	return -1;
}


int CMClient::GetType()
{
	return MCLIENT_TYPE;
}


void CMClient::SetValid(BOOL flag)
{
	m_isValid = flag;
}


BOOL CMClient::IsValid()
{
	return m_isValid;
}


char* CMClient::GetID()
{
	return m_ID;
}


BOOL CMClient::CheckPasswd(char* id, char* passwd)
{
	FILE* fp = fopen("passwd.txt", "r");
	if( fp == NULL )
		return FALSE;

	char buf[512];
	fgets(buf, countof(buf), fp);

	char tempid[24];
	char temppasswd[24];
	sscanf(buf, "%s%s", tempid, temppasswd);

	if( strncmp(tempid, id, countof(tempid)) != 0
	 || strncmp(temppasswd, passwd, countof(temppasswd)) != 0 )
	{
		fclose(fp);
		return FALSE;
	}

	strncpy(m_ID, id, countof(m_ID));
	strncpy(m_passwd, passwd, countof(m_passwd));

	fclose(fp);
	return TRUE;
}


BOOL CMClient::ChangePasswd(char* id, char* passwd, char* oldpasswd)
{
	FILE* fp = fopen("passwd.txt", "r");
	if( fp == NULL )
		return FALSE;

	char buf[512];
	fgets(buf, 512, fp);

	char tempid[24];
	char temppasswd[24];
	sscanf(buf, "%s%s", tempid, temppasswd);

	if( strncmp(tempid, id, countof(tempid)) != 0
	 || strncmp(temppasswd, passwd, countof(temppasswd)) != 0 )
	{
		fclose(fp);
		return FALSE;
	}

	strncpy(m_ID, id, countof(m_ID));
	strncpy(m_passwd, passwd, countof(m_passwd));

	fclose(fp);
	return TRUE;
}


void CMClient::SetLastCommunicationTime(unsigned long time)
{
	m_lastCommunicationTime = time;
}


CAsyncStream* CMClient::GetAsyncStream()
{
	return m_asyncStream;
}


unsigned long CMClient::GetIPaddr()
{
	return m_IPaddr;
}
