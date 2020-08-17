#include "Account.h"
#include "Certificate.h"
#include "CharSvrProcess.h"
#include "UserList.h"
#include "UserVerify.h"
#include "Common/Packet.h"
#include "Network3/StreamManager.h"


CCertificate::CCertificate()
{
	m_mapCertificate.clear();
}


CCertificate::~CCertificate()
{
}


int CCertificate::GetCertificate(DWORD dwAID, SCERTIFICATE& rCertificate)
{
	m_csCertificate.Enter();

	std::map<DWORD,SCERTIFICATE>::iterator iCertificate = m_mapCertificate.find(dwAID);
	if( iCertificate == m_mapCertificate.end() )
	{
		m_csCertificate.Leave();
		return -1;
	}

	rCertificate = iCertificate->second;

	m_csCertificate.Leave();
	return 0;
}


void CCertificate::TryCertificate(SCERTIFICATE& rCertificate)
{
	m_csCertificate.Enter();
	m_mapCertificate[rCertificate.m_dwAID] = rCertificate;
	m_csCertificate.Leave();
}


void CCertificate::AnswerCertificate(DWORD dwAID, DWORD dwCerticate, DWORD dwMessageID)
{
	m_csCertificate.Enter();

	std::map<DWORD,SCERTIFICATE>::iterator iCertificate = m_mapCertificate.find(dwAID);
	if( iCertificate == m_mapCertificate.end() )
	{
		m_csCertificate.Leave();
		return;
	}

	SCERTIFICATE certificate = iCertificate->second;
	m_mapCertificate.erase(iCertificate);

	m_csCertificate.Leave();

	if( dwCerticate != 0 )
	{
		if( dwCerticate == 1 )
		{
			if( g_userList.CUserList::IsPCBangUser(dwAID) )
			{
				CCharSvrProcess* p = g_userList.CUserList::GetCharProcess(dwAID);
				if( p != NULL )
				{
					p->CCharSvrProcess::SendLoginAck(dwAID);
				}
			}
		}

		return;
	}

	unsigned char reason;
	switch( dwMessageID )
	{
	case 13:
		reason = BAN_PAY_SUSPEND;
	break;
	case 14:
	case 18:
	case 19:
		reason = BAN_NOT_SETTLED;
	break;
	case 16:
		reason = BAN_IP_OVERFLOW;
	break;
	default:
		reason = BAN_UNFAIR;
	break;
	}

	SUSER_ user = {};
	g_userList.CUserList::Get(dwAID, &user); //NOTE: unused

	g_userList.CUserList::Delete(dwAID);
	CSingleton<CUserVerify>::getSingletonPtr()->CUserVerify::DeleteUserVerify(dwAID);

	if( certificate.m_dwCharIP != -1 )
		return;

	PACKET_AH_DISCONNECT ah_disconnect;
	ah_disconnect.PacketType = HEADER_AH_DISCONNECT;
	ah_disconnect.AID = dwAID;
	ah_disconnect.reason = reason;
	g_CharSvrStreamMgr.CStreamManager::Broadcast((char*)&ah_disconnect, sizeof(ah_disconnect));
}
