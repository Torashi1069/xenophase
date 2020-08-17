#pragma once
#include "Common/CriticalSection.h"


struct SCERTIFICATE
{
	/* this+ 0 */ DWORD m_dwAID;
	/* this+ 4 */ DWORD m_dwCertificate;
	/* this+ 8 */ DWORD m_dwMessageID;
	/* this+12 */ DWORD m_dwIP;
	/* this+16 */ DWORD m_dwCharIP;
	/* this+20 */ DWORD m_CharIndex;
};


class CCertificate
{
public:
	CCertificate();
	~CCertificate();
	void TryCertificate(SCERTIFICATE& rCertificate);
	void AnswerCertificate(DWORD dwAID, DWORD dwCerticate, DWORD dwMessageID);
//	int BringCertificate(DWORD dwAID, SCERTIFICATE& rCertificate);
	int GetCertificate(DWORD dwAID, SCERTIFICATE& rCertificate);

private:
	/* this+ 0 */ std::map<DWORD,SCERTIFICATE> m_mapCertificate;
	/* this+16 */ CCriticalSection m_csCertificate;
};
