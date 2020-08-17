#pragma once
#include "Mode.h"
#include "Struct.h"
class UIWaitWnd;


class CLoginMode : public CMode
{
	/* this+   0 */ public: //CMode baseclass_0;
	/* this+  64 */ int m_charParam[8];
	/* this+  96 */ char m_makingCharName[64];
	/* this+ 160 */ char m_emaiAddress[128];
	/* this+ 288 */ char m_userPassword[64];
	/* this+ 352 */ char m_userId[64];
	/* this+ 416 */ int m_numServer;
	/* this+ 420 */ int m_serverSelected;
	/* this+ 424 */ int m_numChar;
	/* this+ 428 */ unsigned long m_subModeStartTime;
	/* this+ 432 */ SERVER_ADDR m_serverInfo[100];
	/* this+3632 */ CHARACTER_INFO m_charInfo[42];
	/* this+8336 */ mystd::string m_wallPaperBmpName;
	/* this+8352 */ BILLING_INFO m_billingInfo;
	/* this+8372 */ unsigned long m_syncRequestTime;
	/* this+8376 */ UIWaitWnd* m_wndWait;
	/* this+8380 */ mystd::vector<accountInfo> m_accountInfo;
	/* this+8396 */ mystd::vector<accountInfo> m_accountInfo2;
	/* this+8412 */ bool m_multiLang;
	/* this+8416 */ int m_nSelectedAccountNo;
	/* this+8420 */ int m_nSelectedAccountNo2;
	/* this+8424 */ mystd::string m_strErrorInfo;

public:
	CLoginMode(void);
	virtual ~CLoginMode(void);
	virtual void OnChangeState(int state);

private:
	void PollNetworkStatus(void);
	void Ac_Accept_Login(const char* buf);
	void Ac_Refuse_Login(const char* BlockDate, int ErrorCode);
	void Hc_Accept_Enter(const char* buf);
	void Hc_Refuse_Enter(const char* buf);
	void Hc_Accept_Makechar(const char* buf);
	void Hc_Refuse_Makechar(const char* buf);
	void Hc_Accept_Deletechar(const char* buf);
	void Hc_Refuse_Deletechar(const char* buf);
	void Hc_Notify_Zonesvr(const char* buf);
	void Zc_Accept_Enter(const char* buf);
	void Zc_Refuse_Enter(const char* buf);
	void Sc_Notify_Ban(const char* buf);
	void Sc_Billing_Info(const char* buf);
	void Ac_Ask_Pngameroom(const char* buf);
	void Sc_Ack_Encryption(const char* buf);
	void Ac_Ack_Hash(const char* buf);
	void Ac_Notify_Error(const char* buf);
	void Hc_Block_Character(const char* buf);
	void Ac_Event_Result(const char* buf);
	void Hc_CharNotBeenSelected(const char* buf);
	void Hc_Ack_Is_Valid_CharName(const char* buf);
	void Hc_Ack_Change_CharName(const char* buf);
	void Hc_Refuse_SelectChar(const char* buf);
	void Zc_Accept_Enter2(const char* buf);
	void Hc_Character_List(const char* buf);
	void Zc_Define_Check(const char* buf);

public:
	static hook_func<CLoginMode* (CLoginMode::*)(void)> CLoginMode::_cCLoginMode;
	static hook_func<void (CLoginMode::*)(void)> CLoginMode::_dCLoginMode;
	static hook_func<void (CLoginMode::*)(int state)> CLoginMode::_OnChangeState;
	static hook_func<void (CLoginMode::*)(void)> CLoginMode::_PollNetworkStatus;
	static hook_func<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Accept_Login;
	static hook_func<void (CLoginMode::*)(const char* BlockDate, int ErrorCode)> CLoginMode::_Ac_Refuse_Login;
};
C_ASSERT( sizeof CLoginMode == 8440 );


int __cdecl GetAccountType();
