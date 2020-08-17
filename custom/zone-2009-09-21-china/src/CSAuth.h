#pragma once


class CCSAuth
{
public:
	/* this+  0 */ public: DWORD m_dwSeed;
	/* this+  4 */ public: DWORD m_dwAuthValue;
	/* this+  8 */ public: DWORD m_bAuth;
	/* this+ 12 */ public: DWORD m_dwCurrIndex;
	/* this+ 16 */ public: char m_table[8][5];
	/* this+ 56 */ public: DWORD m_dwClientSequenceNumber;
	/* this+ 60 */ public: DWORD m_dwServerSequenceNumber;
	/* this+ 64 */ public: DWORD m_adwLastSeqs[12];
	/* this+112 */ public: DWORD m_dwPPLastError;
	/* this+116 */ public: DWORD m_dwSeq;

	public: CCSAuth::CCSAuth(void);
	public: CCSAuth::~CCSAuth(void);
	public: void CCSAuth::Init(void);
	//public: unsigned long CCSAuth::IsAuth();
	//public: unsigned long CCSAuth::GetAuthDword();
	//public: unsigned long CCSAuth::CheckAuthDword(unsigned long);
	//public: unsigned long CCSAuth::GetAuthResults(unsigned long, unsigned long *, unsigned long);
	//public: unsigned long CCSAuth::EncryptPacket(void *, unsigned long);
	//public: unsigned long CCSAuth::DecryptPacket(void *, unsigned long);
	//public: unsigned long CCSAuth::PPGetLastError();
	//protected: unsigned long CCSAuth::TransAuthDword(unsigned long, int);
	protected: void CCSAuth::np_srandom(DWORD dwSeed);
	//protected: unsigned long CCSAuth::np_random();
	//protected: unsigned long CCSAuth::CheckLastPacket(unsigned long);

private:
	static hook_method<void (CCSAuth::*)(void)> CCSAuth::_Init;
	static hook_method<void (CCSAuth::*)(DWORD dwSeed)> CCSAuth::_np_srandom;
};


struct _GG_AUTH_PROTOCOL
{
};


struct _GG_AUTH_DATA
{
	/* this+ 0 */ DWORD dwIndex;
	/* this+ 4 */ DWORD dwValue1;
	/* this+ 8 */ DWORD dwValue2;
	/* this+12 */ DWORD dwValue3;
};


class CCSAuth2
{
	/* this+ 0 */ protected: _GG_AUTH_PROTOCOL* m_pProtocol;
	/* this+ 4 */ protected: DWORD m_bPrtcRef;
	/* this+ 8 */ protected: DWORD m_dwUserFlag;
	/* this+12 */ public: _GG_AUTH_DATA m_AuthQuery;
	/* this+28 */ public: _GG_AUTH_DATA m_AuthAnswer;

	public: CCSAuth2::CCSAuth2(void);
	public: CCSAuth2::~CCSAuth2(void);
	public: void CCSAuth2::Init(void);
	//public: unsigned long CCSAuth2::GetAuthQuery();
	//public: unsigned long CCSAuth2::CheckAuthAnswer();

private:
	static hook_method<void (CCSAuth2::*)(void)> CCSAuth2::_Init;
};
