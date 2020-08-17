#include "GameGuard/CSAuth.h"


static char g_Table[5][8] = {};
static DWORD g_CurrIndex = -1;


CCSAuth::CCSAuth()
{
	this->CCSAuth::Init();
}


CCSAuth::~CCSAuth()
{
}


void CCSAuth::Init()
{
	this->CCSAuth::np_srandom((DWORD)this + time(NULL));
	m_dwAuthValue = 0;
	m_bAuth = TRUE;
	memcpy(m_table, g_Table, sizeof(m_table));
	m_dwCurrIndex = g_CurrIndex;
	m_dwServerSequenceNumber = 0;
	m_dwClientSequenceNumber = 0;
	memset(m_adwLastSeqs, 0, sizeof(m_adwLastSeqs));
	m_dwPPLastError = 0;
	m_dwSeq = 0;
}


void CCSAuth::np_srandom(DWORD dwSeed)
{
	m_dwSeed = dwSeed;
}
