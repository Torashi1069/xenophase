#pragma once


class CCSAuth
{
public:
	CCSAuth();
	~CCSAuth();

public:
	void Init();
//	DWORD IsAuth();
//	DWORD GetAuthDword();
//	DWORD CheckAuthDword(DWORD );
//	DWORD GetAuthResults(DWORD , DWORD* , DWORD );
//	DWORD EncryptPacket(void* , DWORD );
//	DWORD DecryptPacket(void* , DWORD );
//	DWORD PPGetLastError();

protected:
//	DWORD TransAuthDword(DWORD , int );
	void np_srandom(DWORD dwSeed);
//	DWORD np_random();
//	DWORD CheckLastPacket(DWORD );

public:
	/* this+  0 */ DWORD m_dwSeed;
	/* this+  4 */ DWORD m_dwAuthValue;
	/* this+  8 */ DWORD m_bAuth;
	/* this+ 12 */ DWORD m_dwCurrIndex;
	/* this+ 16 */ char m_table[8][5];
	/* this+ 56 */ DWORD m_dwClientSequenceNumber;
	/* this+ 60 */ DWORD m_dwServerSequenceNumber;
	/* this+ 64 */ DWORD m_adwLastSeqs[12];
	/* this+112 */ DWORD m_dwPPLastError;
	/* this+116 */ DWORD m_dwSeq;
};
