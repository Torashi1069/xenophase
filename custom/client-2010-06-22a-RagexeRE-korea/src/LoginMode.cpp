#include "LoginMode.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Session.h"
#include "Device/Connection.h"
#include "Device/md5.h"
#include "Window/UISys.h"
#include "Window/UIWaitWnd.h"
#include "Window/UIWindowMgr.h"
#include "Enum.h"
#include "Globals.h"
#include "Packet.h"


hook_func<CLoginMode* (CLoginMode::*)(void)> CLoginMode::_cCLoginMode("CLoginMode::CLoginMode");
CLoginMode::CLoginMode(void)
{
	(this->*_cCLoginMode)(); return;

	//TODO
}


hook_func<void (CLoginMode::*)(void)> CLoginMode::_dCLoginMode("CLoginMode::~CLoginMode");
CLoginMode::~CLoginMode(void)
{
	(this->*_dCLoginMode)(); return;

	//TODO
}


hook_func<void (CLoginMode::*)(int state)> CLoginMode::_OnChangeState("CLoginMode::OnChangeState");
void CLoginMode::OnChangeState(int state)
{
	return (this->*_OnChangeState)(state);

	//TODO
}


hook_func<void (CLoginMode::*)(void)> CLoginMode::_PollNetworkStatus("CLoginMode::PollNetworkStatus");
void CLoginMode::PollNetworkStatus(void)
{
	if( !CRagConnection::instanceR().CConnection::Poll() )
		g_modeMgr.GetCurMode()->SendMsg(MM_SOCKETERROR, 0, 0, 0);

	if( g_mustPumpOutReceiveQueue == TRUE )
	{
		int aid;
		if( CRagConnection::instanceR().CConnection::Recv((char*)&aid, sizeof(aid), true) )
			g_mustPumpOutReceiveQueue = FALSE;

		return;
	}

	char buf[2048];
	while( CRagConnection::instanceR().CRagConnection::RecvPacket(buf) )
	{
		switch( CRagConnection::instanceR().CRagConnection::GetPacketType(buf) )
		{
		case HEADER_AC_ACCEPT_LOGIN         : this->CLoginMode::Ac_Accept_Login(buf);          break;
		case HEADER_AC_REFUSE_LOGIN         :
		{
			PACKET_AC_REFUSE_LOGIN& ac_refuse_login = *reinterpret_cast<PACKET_AC_REFUSE_LOGIN*>(buf);
			ac_refuse_login.blockDate[0] = '\0';
			this->CLoginMode::Ac_Refuse_Login(ac_refuse_login.blockDate, ac_refuse_login.ErrorCode);
		}
		break;
		case HEADER_HC_ACCEPT_ENTER         : this->CLoginMode::Hc_Accept_Enter(buf);          break;
		case HEADER_HC_REFUSE_ENTER         : this->CLoginMode::Hc_Refuse_Enter(buf);          break;
		case HEADER_HC_ACCEPT_MAKECHAR      : this->CLoginMode::Hc_Accept_Makechar(buf);       break;
		case HEADER_HC_REFUSE_MAKECHAR      : this->CLoginMode::Hc_Refuse_Makechar(buf);       break;
		case HEADER_HC_ACCEPT_DELETECHAR    : this->CLoginMode::Hc_Accept_Deletechar(buf);     break;
		case HEADER_HC_REFUSE_DELETECHAR    : this->CLoginMode::Hc_Refuse_Deletechar(buf);     break;
		case HEADER_HC_NOTIFY_ZONESVR       : this->CLoginMode::Hc_Notify_Zonesvr(buf);        break;
		case HEADER_ZC_ACCEPT_ENTER         : this->CLoginMode::Zc_Accept_Enter(buf);          return; // mode switch
		case HEADER_ZC_REFUSE_ENTER         : this->CLoginMode::Zc_Refuse_Enter(buf);          break;
		case HEADER_SC_NOTIFY_BAN           : this->CLoginMode::Sc_Notify_Ban(buf);            break;
		case HEADER_PING                    :                                                  break; // ignored
		case HEADER_SC_BILLING_INFO         : this->CLoginMode::Sc_Billing_Info(buf);          break;
		case HEADER_AC_ASK_PNGAMEROOM       : this->CLoginMode::Ac_Ask_Pngameroom(buf);        break;
		case HEADER_SC_ACK_ENCRYPTION       : this->CLoginMode::Sc_Ack_Encryption(buf);        break;
		case HEADER_AC_ACK_HASH             : this->CLoginMode::Ac_Ack_Hash(buf);              break;
		case HEADER_AC_NOTIFY_ERROR         : this->CLoginMode::Ac_Notify_Error(buf);          break;
		case HEADER_HC_BLOCK_CHARACTER      : this->CLoginMode::Hc_Block_Character(buf);       break;
		case HEADER_AC_EVENT_RESULT         : this->CLoginMode::Ac_Event_Result(buf);          break;
		case HEADER_ZC_AID                  :                                                  break; // ignored
		case HEADER_HC_CHARNOTBEENSELECTED  : this->CLoginMode::Hc_CharNotBeenSelected(buf);   break;
		case HEADER_HC_ACK_IS_VALID_CHARNAME: this->CLoginMode::Hc_Ack_Is_Valid_CharName(buf); break;
		case HEADER_HC_ACK_CHANGE_CHARNAME  : this->CLoginMode::Hc_Ack_Change_CharName(buf);   break;
		case HEADER_HC_REFUSE_SELECTCHAR    : this->CLoginMode::Hc_Refuse_SelectChar(buf);     break;
		case HEADER_ZC_ACCEPT_ENTER2        : this->CLoginMode::Zc_Accept_Enter2(buf);         return; // mode switch
		case HEADER_HC_CHARACTER_LIST       : this->CLoginMode::Hc_Character_List(buf);        break;
		case HEADER_ZC_DEFINE_CHECK         : this->CLoginMode::Zc_Define_Check(buf);          break;
		case HEADER_AC_REFUSE_LOGIN_R2      :
		{
			PACKET_AC_REFUSE_LOGIN_R2& ac_refuse_login = *reinterpret_cast<PACKET_AC_REFUSE_LOGIN_R2*>(buf);
			ac_refuse_login.blockDate[0] = '\0';
			this->CLoginMode::Ac_Refuse_Login(ac_refuse_login.blockDate, ac_refuse_login.ErrorCode);
		}
		break;
		default:
			CRagConnection::instanceR().CConnection::ResetQueue();
		break;
		}
	}
}


hook_func<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Accept_Login("CLoginMode::Ac_Accept_Login");
void CLoginMode::Ac_Accept_Login(const char* buf)
{
	return (this->*_Ac_Accept_Login)(buf);

	const PACKET_AC_ACCEPT_LOGIN& ac_accept_login = *reinterpret_cast<const PACKET_AC_ACCEPT_LOGIN*>(buf);

	//TODO
}


hook_func<void (CLoginMode::*)(const char* BlockDate, int ErrorCode)> CLoginMode::_Ac_Refuse_Login("CLoginMode::Ac_Refuse_Login");
void CLoginMode::Ac_Refuse_Login(const char* BlockDate, int ErrorCode)
{
	return (this->*_Ac_Refuse_Login)(BlockDate, ErrorCode);

	//TODO
}


void CLoginMode::Hc_Accept_Enter(const char* buf)
{
	const PACKET_HC_ACCEPT_ENTER& hc_accept_enter = *reinterpret_cast<const PACKET_HC_ACCEPT_ENTER*>(buf);

	g_session.field_31B0_TotalSlotNum = hc_accept_enter.TotalSlotNum;
	g_session.field_31B4_PremiumStartSlot = hc_accept_enter.PremiumStartSlot;
	g_session.field_31B8_PremiumEndSlot = hc_accept_enter.PremiumEndSlot;

	memcpy(&m_billingInfo, &hc_accept_enter.m_extension, sizeof(m_billingInfo));
	m_billingInfo.code = ntohl(m_billingInfo.code);
	m_billingInfo.time1 = ntohl(m_billingInfo.time1);
	m_billingInfo.time2 = ntohl(m_billingInfo.time2);

	m_numChar = (hc_accept_enter.PacketLength - sizeof(hc_accept_enter)) / sizeof(CHARACTER_INFO);
	memcpy(m_charInfo, hc_accept_enter.CharInfo, m_numChar * sizeof(CHARACTER_INFO));

	if( (hc_accept_enter.PacketLength - sizeof(hc_accept_enter)) % sizeof(CHARACTER_INFO) > 0 )
	{
		char msg[256];
		sprintf(msg, "CHARACTER_INFO size error!! character num : %d  CHARACTER_INFO size : %d", m_numChar, sizeof(CHARACTER_INFO));
		g_windowMgr.UIWindowMgr::ErrorMsg(msg, 0, 1, 1, 0, "메시지");
	}

	char debugmsg[100];
	sprintf(debugmsg, "%d, %d", hc_accept_enter.PacketLength - sizeof(hc_accept_enter), sizeof(CHARACTER_INFO));

	g_session.m_numChar = m_numChar;
	m_nextSubMode = 7;
}


void CLoginMode::Hc_Refuse_Enter(const char* buf)
{
	const PACKET_HC_REFUSE_ENTER& hc_refuse_enter = *reinterpret_cast<const PACKET_HC_REFUSE_ENTER*>(buf);

	CRagConnection::instanceR().CConnection::Disconnect();

	if( hc_refuse_enter.ErrorCode == 0 || hc_refuse_enter.ErrorCode != 1 )
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ACCESS_DENIED), 0, 1, 0, 0, "메시지");
	else
		g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ID_MISMATCH), 0, 1, 1, 0, "메시지");

	g_mustPumpOutReceiveQueue = FALSE;
	m_nextSubMode = 3;
}


void CLoginMode::Hc_Accept_Makechar(const char* buf)
{
	const PACKET_HC_ACCEPT_MAKECHAR& hc_accept_makechar = *reinterpret_cast<const PACKET_HC_ACCEPT_MAKECHAR*>(buf);

	memcpy(&g_charInfo, &hc_accept_makechar.charinfo, sizeof(g_charInfo));
	memcpy(&m_charInfo[m_numChar], &hc_accept_makechar.charinfo, sizeof(m_charInfo[m_numChar]));
	++m_numChar;
	++g_session.m_numChar;

	m_nextSubMode = 7;
}


void CLoginMode::Hc_Refuse_Makechar(const char* buf)
{
	const PACKET_HC_REFUSE_MAKECHAR& hc_refuse_makechar = *reinterpret_cast<const PACKET_HC_REFUSE_MAKECHAR*>(buf);

	MSGSTRINGID id;
	switch( hc_refuse_makechar.ErrorCode )
	{
	case  0: id = MSI_CHARACTER_NAME_ALREADY_EXISTS; break;
	case  1: id = MSI_LIMIT_AGE; break;
	case  2: id = MSI_LIMIT_CHAR_DELETE; break;
	case 11: id = MSI_NEED_PREMIUM_SERVICE; break;
	case  3: id = MSI_FR_ERR_MKCHAR_INVALID_SLOT; break;
	default: id = MSI_CHARACTER_CREATION_DENIED; break;
	}

	g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(id), 0, 1, 0, 0, "메시지");
	m_nextSubMode = 7;
}


void CLoginMode::Hc_Accept_Deletechar(const char* buf)
{
	const PACKET_HC_ACCEPT_DELETECHAR& hc_accept_deletechar = *reinterpret_cast<const PACKET_HC_ACCEPT_DELETECHAR*>(buf);

	//FIXME: memleak, pointless and inefficient code
	CHARACTER_INFO* tmpInfo = new CHARACTER_INFO[m_numChar];
	int j = 0;

	for( int i = 0; i < m_numChar; ++i )
	{
		if( m_charInfo[i].CharNum != g_charInfo.CharNum )
		{
			memcpy(&tmpInfo[j], &m_charInfo[i], sizeof(CHARACTER_INFO));
			++j;
		}
	}

	--m_numChar;
	--g_session.m_numChar;
	memcpy(m_charInfo, tmpInfo, m_numChar * sizeof(CHARACTER_INFO));

	m_nextSubMode = 7;
}


void CLoginMode::Hc_Refuse_Deletechar(const char* buf)
{
	const PACKET_HC_REFUSE_DELETECHAR& hc_refuse_deletechar = *reinterpret_cast<const PACKET_HC_REFUSE_DELETECHAR*>(buf);

	MSGSTRINGID id;
	switch( hc_refuse_deletechar.ErrorCode )
	{
	case  0: id = ( g_serviceType != ServiceKorea ) ? MSI_CANNOT_DELETE_CHARACTER_EMAIL : MSI_CANNOT_DELETE_CHARACTER_PEOPLE_REG_NUMBER; break;
	case  1: id = MSI_FR_ERR_DELCHAR_INVALID_SLOT; break;
	default: id = MSI_CANNOT_DELETE_CHARACTER; break;
	}

	g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(id), 0, 1, 0, 0, "메시지");
	m_nextSubMode = 7;
}


void CLoginMode::Hc_Notify_Zonesvr(const char* buf)
{
	const PACKET_HC_NOTIFY_ZONESVR& hc_notify_zonesvr = *reinterpret_cast<const PACKET_HC_NOTIFY_ZONESVR*>(buf);

	g_session.CSession::SetGid(hc_notify_zonesvr.GID);

	char mapName[16+1];
	memcpy(mapName, hc_notify_zonesvr.mapName, 16);
	mapName[countof(mapName)-1] = '\0';

	mystd::string curMap = mapName;
	curMap.resize(curMap.size());
	strcpy(g_session.m_curMap, curMap.c_str());

	strcpy(g_zoneServerAddr.ip, inet_ntoa(*(in_addr*)&hc_notify_zonesvr.addr.ip));
	g_zoneServerAddr.port = hc_notify_zonesvr.addr.port;

	CRagConnection::instanceR().CConnection::Disconnect();

	m_nextSubMode = 12;
}


void CLoginMode::Zc_Accept_Enter(const char* buf)
{
	//TODO
}


void CLoginMode::Zc_Refuse_Enter(const char* buf)
{
/*
	g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ACCESS_DENIED), 0, 1, 0, 0, aMessage);
	CRagConnection::instanceR().CConnection::Disconnect();
	g_mustPumpOutReceiveQueue = FALSE;
	m_nextSubMode = 3;
*/
}


void CLoginMode::Sc_Notify_Ban(const char* buf)
{
	//TODO
}


void CLoginMode::Sc_Billing_Info(const char* buf)
{
	//TODO
}


void CLoginMode::Ac_Ask_Pngameroom(const char* buf)
{
	if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_ASK_PNGAMEROOM), 2, 1, 0, 0, "메시지") == 125 )
	{
		PACKET_CA_REPLY_PNGAMEROOM ca_reply_pngameroom;
		ca_reply_pngameroom.PacketType = HEADER_CA_REPLY_PNGAMEROOM;
		ca_reply_pngameroom.Permission = 1;
		CRagConnection::instanceR().CRagConnection::SendPacket(CRagConnection::instanceR().CRagConnection::GetPacketSize(ca_reply_pngameroom.PacketType), (char*)&ca_reply_pngameroom);
	}
	else
	{
		CRagConnection::instanceR().CConnection::Disconnect();
		g_mustPumpOutReceiveQueue = FALSE;
		m_nextSubMode = 3;
	}
}


void CLoginMode::Sc_Ack_Encryption(const char* buf)
{
	ErrorMsg("No Packet Encryption !!!");
}


void CLoginMode::Ac_Ack_Hash(const char* buf)
{
	const PACKET_AC_ACK_HASH& packet = *reinterpret_cast<const PACKET_AC_ACK_HASH*>(buf);

	MD5 hash;
	hash.MD5::init();

	if( g_passwordEncrypt2 )
	{
		hash.MD5::append((const unsigned char*)m_userPassword, strlen(m_userPassword));
		hash.MD5::append((const unsigned char*)packet.RandStr, packet.PacketLength - sizeof(packet));
	}
	else
	{
		hash.MD5::append((const unsigned char*)packet.RandStr, packet.PacketLength - sizeof(packet));
		hash.MD5::append((const unsigned char*)m_userPassword, strlen(m_userPassword));
	}

	if( g_serviceType == ServiceThai )
	{
		PACKET_CA_LOGIN3 p;
		p.PacketType = HEADER_CA_LOGIN3;
		p.Version = g_version;
		memcpy(p.ID, m_userId, 24);
		hash.MD5::finish(p.PasswdMD5);
		p.clienttype = GetAccountType();
		p.ClientInfo = ( g_session.m_isCheckToPcbang ) ? LOBYTE(g_session.m_SelectAccountNumber) + 10 : LOBYTE(g_session.m_SelectAccountNumber);

		CRagConnection::instanceR().CRagConnection::SendPacket(CRagConnection::instanceR().CRagConnection::GetPacketSize(p.PacketType), (const char*)&p);
	}
	else
	if( g_serviceType == ServiceJapan )
	{
		PACKET_CA_LOGIN4 p;
		p.PacketType = HEADER_CA_LOGIN4;
		p.Version = g_version;
		memcpy(p.ID, m_userId, 24);
		hash.MD5::finish(p.PasswdMD5);
		p.clienttype = GetAccountType();
		//FIXME: p.macData left uninitialized

		CRagConnection::instanceR().CRagConnection::SendPacket(CRagConnection::instanceR().CRagConnection::GetPacketSize(p.PacketType), (const char*)&p);
	}
	else
	{
		PACKET_CA_LOGIN2 p;
		p.PacketType = HEADER_CA_LOGIN2;
		p.Version = g_version;
		memcpy(p.ID, m_userId, 24);
		hash.MD5::finish(p.PasswdMD5);
		p.clienttype = GetAccountType();

		CRagConnection::instanceR().CRagConnection::SendPacket(CRagConnection::instanceR().CRagConnection::GetPacketSize(p.PacketType), (const char*)&p);
	}

	UIWaitWnd* wnd = (UIWaitWnd*)g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
	wnd->UIWaitWnd::SetMsg(MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER), 16, 1);
}


void CLoginMode::Ac_Notify_Error(const char* buf)
{
	//TODO
}


void CLoginMode::Hc_Block_Character(const char* buf)
{
	PACKET_HC_BLOCK_CHARACTER& hc_block_character = *(PACKET_HC_BLOCK_CHARACTER*)buf;

	g_session.m_nCharBlockInfoCount = (hc_block_character.PacketLength - sizeof(hc_block_character)) / sizeof(TAG_CHARACTER_BLOCK_INFO);
	memset(g_session.m_charBlockInfo2, 0, g_session.m_nCharBlockInfoCount * sizeof(TAG_CHARACTER_BLOCK_INFO));
	memcpy(g_session.m_charBlockInfo2, hc_block_character.CharBlockInfo, g_session.m_nCharBlockInfoCount * sizeof(TAG_CHARACTER_BLOCK_INFO));
}


void CLoginMode::Ac_Event_Result(const char* buf)
{
/*
	g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_1020), 0, 1, 0, 0, aMessage);
*/
}


void CLoginMode::Hc_CharNotBeenSelected(const char* buf)
{
	//TODO
}


void CLoginMode::Hc_Ack_Is_Valid_CharName(const char* buf)
{
	//TODO
}


void CLoginMode::Hc_Ack_Change_CharName(const char* buf)
{
	//TODO
}


void CLoginMode::Hc_Refuse_SelectChar(const char* buf)
{
	//TODO
}


void CLoginMode::Zc_Accept_Enter2(const char* buf)
{
	//TODO
}


void CLoginMode::Hc_Character_List(const char* buf)
{
	PACKET_HC_CHARACTER_LIST& hc_character_list = *(PACKET_HC_CHARACTER_LIST*)buf;

	m_numChar = (hc_character_list.PacketLength - sizeof(hc_character_list)) / sizeof(CHARACTER_INFO);
	g_session.m_numChar = m_numChar;
	memcpy(m_charInfo, hc_character_list.CharInfo, m_numChar * sizeof(CHARACTER_INFO));
	m_nextSubMode = 7;
}


void CLoginMode::Zc_Define_Check(const char* buf)
{
	PACKET_ZC_DEFINE_CHECK& zc_define_check = *(PACKET_ZC_DEFINE_CHECK*)buf;

	mystd::pair<int,mystd::string> result = PACKET_ZC_DEFINE_CHECK::CHECK_FIRST(zc_define_check.Data);
	if( result.first != 0 )
	{
		char msg[260] = {};
		_snprintf(msg, sizeof(msg), "*** define mismatch found ... (%s)(0x%08X)", result.second.c_str(), result.first);
		MessageBoxA(NULL, msg, "DEFINE MISMATCH FOUND", MB_OK);
	}
}


int __cdecl GetAccountType()
{
	if( g_serverType == ServerSakray )
	{
		switch( g_serviceType )
		{
		default               : return CLIENTTYPE_SAKRAY;
		case ServiceChina     : return CLIENTTYPE_CHINA;
		case ServiceTaiwan    : return CLIENTTYPE_TAIWAN;
		case ServiceMalaysia  : return CLIENTTYPE_MALAYSIA;
		case ServiceSingapore : return CLIENTTYPE_SINGAPORE;
		case ServiceGermany   : return CLIENTTYPE_GERMANY;
		case ServiceIndia     : return CLIENTTYPE_INDIA;
		case ServiceBrazil    : return CLIENTTYPE_BRAZIL;
		case ServiceAustralia : return CLIENTTYPE_AUSTRALIA;
		case ServiceRussia    : return CLIENTTYPE_RUSSIA;
		case ServiceArabic    : return CLIENTTYPE_UAE;
		case ServiceAmerica   : return CLIENTTYPE_ENGLISH_SAKRAY;
		case ServiceJapan     : return CLIENTTYPE_JAPAN_SAKRAY;
		case ServiceThai      : return CLIENTTYPE_THAI_SAKRAY;
		case ServiceIndonesia : return CLIENTTYPE_INDONESIA_SAKRAY;
		case ServicePhilippine: return CLIENTTYPE_PHILIPPINE_SAKRAY;
		case ServiceVietnam   : return CLIENTTYPE_VIETNAM_SAKRAY;
		}
	}
	else
	if( g_serverType == ServerPK )
	{
		switch( g_serviceType )
		{
		default               : return CLIENTTYPE_KOREAN;
		case ServicePhilippine: return CLIENTTYPE_PHILIPPINE_PK;
		case ServiceJapan     : return CLIENTTYPE_JAPAN_PK;
		case ServiceThai      : return CLIENTTYPE_THAI_PK;
		case ServiceVietnam   : return CLIENTTYPE_VIETNAM_PK;
		case ServiceIndonesia : return CLIENTTYPE_INDONESIA_PK;
		}
	}
	else
	{
		switch( g_serviceType )
		{
		default               : return CLIENTTYPE_KOREAN;
		case ServiceAmerica   : return CLIENTTYPE_ENGLISH;
		case ServiceJapan     : return CLIENTTYPE_JAPAN;
		case ServiceChina     : return CLIENTTYPE_CHINA;
		case ServiceTaiwan    : return CLIENTTYPE_TAIWAN;
		case ServiceThai      : return CLIENTTYPE_THAI;
		case ServiceIndonesia : return CLIENTTYPE_INDONESIA;
		case ServicePhilippine: return CLIENTTYPE_PHILIPPINE;
		case ServiceMalaysia  : return CLIENTTYPE_MALAYSIA;
		case ServiceSingapore : return CLIENTTYPE_SINGAPORE;
		case ServiceGermany   : return CLIENTTYPE_GERMANY;
		case ServiceIndia     : return CLIENTTYPE_INDIA;
		case ServiceBrazil    : return CLIENTTYPE_BRAZIL;
		case ServiceAustralia : return CLIENTTYPE_AUSTRALIA;
		case ServiceVietnam   : return CLIENTTYPE_VIETNAM;
		case ServiceRussia    : return CLIENTTYPE_RUSSIA;
		case ServiceChile     : return CLIENTTYPE_CHILE;
		case ServiceFrance    : return CLIENTTYPE_FRANCE;
		case ServiceArabic    : return CLIENTTYPE_UAE;
		}
	}
}
