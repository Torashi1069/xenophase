#pragma once
#include "MSPacketHandler.h"
#include "shared/Client.h"
class CAsyncStream;


class CMClient : public CClient
{
public:
	void Init(CAsyncStream* in_cpAsyncStream, unsigned long in_IPaddr);
	unsigned long GetAccountID();
	void SetLastCommunicationTime(unsigned long time);
	void SetServerID(int SID);
	int GetServerID();
	int OnProcess();
	virtual int GetType();
	void SetValid(BOOL flag);
	BOOL IsValid();
	char* GetID();
	BOOL CheckPasswd(char* id, char* passwd);
	BOOL ChangePasswd(char* id, char* passwd, char* oldpasswd);

public:
	/* this+ 40 */ CMCPacketHandler m_packetHandler;

public:
	CAsyncStream* GetAsyncStream();
	unsigned long GetIPaddr();

public:
	CMClient();
	virtual ~CMClient();

private:
	/* this+ 56 */ unsigned long m_lastCommunicationTime;
	/* this+ 60 */ BOOL m_isValid;
	/* this+ 64 */ char m_ID[24];
	/* this+ 88 */ char m_passwd[24];
	/* this+112 */ int m_SID;
	/* this+116 */ unsigned long m_IPaddr;
};
