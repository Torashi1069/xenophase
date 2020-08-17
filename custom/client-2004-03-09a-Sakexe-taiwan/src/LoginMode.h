#pragma once
#include "Mode.h"
#include "Struct.h"


class CLoginMode : public CMode
{
	struct vtable_t // const CLoginMode::`vftable'
	{
		void* (CLoginMode::* scalar_deleting_destructor)(unsigned int __flags);
		void (CLoginMode::* OnInit)(const char* modeName);
		int (CLoginMode::* OnRun)(void);
		void (CLoginMode::* OnExit)(void);
		void (CLoginMode::* OnUpdate)(void);
		int (CLoginMode::* SendMsg)(int messageId, int val1, int val2, int val3);
		void (CLoginMode::* OnChangeState)(int state);
	};

	/* this+   0 */ public: //CMode baseclass_0;
	/* this+  64 */ private: int m_charParam[8];
	/* this+  96 */ private: char m_makingCharName[64];
	/* this+ 160 */ private: char m_emaiAddress[128];
	/* this+ 288 */ private: char m_userPassword[64];
	/* this+ 352 */ private: char m_userId[64];
	/* this+ 416 */ private: int m_numServer;
	/* this+ 420 */ private: int m_serverSelected;
	/* this+ 424 */ private: int m_numChar;
	/* this+ 428 */ private: unsigned long m_subModeStartTime;
	/* this+ 432 */ private: struct SERVER_ADDR m_serverInfo[100];
	/* this+3632 */ private: struct CHARACTER_INFO m_charInfo[12];
	/* this+4904 */ private: mystd::string m_wallPaperBmpName;
	/* this+4920 */ private: struct BILLING_INFO m_billingInfo;
	/* this+4940 */ private: unsigned long m_syncRequestTime;
	/* this+4944 */ private: unsigned long m_logoShowTime;
	/* this+4948 */ private: mystd::vector<accountInfo> m_accountInfo;
	/* this+4964 */ private: bool m_multiLang;

	public: CLoginMode::CLoginMode(void);
	public: virtual CLoginMode::~CLoginMode(void);
	public: virtual void CLoginMode::OnInit(const char* modeName);
	public: virtual int CLoginMode::OnRun(void);
	public: virtual void CLoginMode::OnExit(void);
	public: virtual void CLoginMode::OnUpdate(void);
	public: virtual int CLoginMode::SendMsg(int messageId, int val1, int val2, int val3);
	public: void CLoginMode::PreLoadAlwaysNeededRes(void);
	private: void CLoginMode::OnChangeState(int state);
	private: void CLoginMode::PollNetworkStatus(void);
	private: void CLoginMode::OnProcessState(int state);
	private: void CLoginMode::OnRenderState(int state);
	private: void CLoginMode::OpenSettlePage(void);
	private: void CLoginMode::CheckPingTime(void);
	private: void CLoginMode::Ac_Accept_Login(const char* buf);
	private: void CLoginMode::Ac_Refuse_Login(const char* buf);
	private: void CLoginMode::Hc_Accept_Enter(const char* buf);
	private: void CLoginMode::Hc_Refuse_Enter(const char* buf);
	private: void CLoginMode::Hc_Accept_Makechar(const char* buf);
	private: void CLoginMode::Hc_Refuse_Makechar(const char* buf);
	private: void CLoginMode::Hc_Accept_Deletechar(const char* buf);
	private: void CLoginMode::Hc_Refuse_Deletechar(const char* buf);
	private: void CLoginMode::Hc_Notify_Zonesvr(const char* buf);
	private: void CLoginMode::Zc_Accept_Enter(const char* buf);
	private: void CLoginMode::Zc_Refuse_Enter(const char* buf);
	private: void CLoginMode::Sc_Notify_Ban(const char* buf);
	private: void CLoginMode::Sc_Billing_Info(const char* buf);
	private: void CLoginMode::Ac_Ask_Pngameroom(const char* buf);
	private: void CLoginMode::Sc_Ack_Encryption(const char* buf);
	private: void CLoginMode::Ac_Ack_Hash(const char* buf);
	private: void CLoginMode::Ac_Notify_Error(const char* buf);
	private: bool CLoginMode::InitAccountInfo(void);

private:
	static hook_method<void (CLoginMode::*)(const char* modeName)> CLoginMode::_OnInit;
	static hook_method<int (CLoginMode::*)(void)> CLoginMode::_OnRun;
	static hook_method<void (CLoginMode::*)(void)> CLoginMode::_OnExit;
	static hook_method<void (CLoginMode::*)(void)> CLoginMode::_OnUpdate;
	static hook_method<int (CLoginMode::*)(int messageId, int val1, int val2, int val3)> CLoginMode::_SendMsg;
	static hook_method<void (CLoginMode::*)(void)> CLoginMode::_PreLoadAlwaysNeededRes;
	static hook_method<void (CLoginMode::*)(int state)> CLoginMode::_OnChangeState;
	static hook_method<void (CLoginMode::*)(void)> CLoginMode::_PollNetworkStatus;
	static hook_method<void (CLoginMode::*)(int state)> CLoginMode::_OnProcessState;
	static hook_method<void (CLoginMode::*)(int state)> CLoginMode::_OnRenderState;
	static hook_method<void (CLoginMode::*)(void)> CLoginMode::_OpenSettlePage;
	static hook_method<void (CLoginMode::*)(void)> CLoginMode::_CheckPingTime;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Accept_Login;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Refuse_Login;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Accept_Enter;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Refuse_Enter;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Accept_Makechar;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Refuse_Makechar;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Accept_Deletechar;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Refuse_Deletechar;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Hc_Notify_Zonesvr;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Zc_Accept_Enter;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Zc_Refuse_Enter;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Sc_Notify_Ban;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Sc_Billing_Info;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Ask_Pngameroom;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Sc_Ack_Encryption;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Ack_Hash;
	static hook_method<void (CLoginMode::*)(const char* buf)> CLoginMode::_Ac_Notify_Error;
	static hook_method<bool (CLoginMode::*)(void)> CLoginMode::_InitAccountInfo;
};


int __cdecl GetAccountType(void);
