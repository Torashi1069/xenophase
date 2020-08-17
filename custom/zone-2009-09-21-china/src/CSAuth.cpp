#include "CSAuth.h"
#include "globals.hpp"


CCSAuth::CCSAuth(void)
{
	this->CCSAuth::Init();
}


CCSAuth::~CCSAuth(void)
{
}


hook_method<void (CCSAuth::*)(void)> CCSAuth::_Init(SERVER, "?Init@CCSAuth@@QAEXXZ");
void CCSAuth::Init(void)
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CCSAuth::*)(DWORD dwSeed)> CCSAuth::_np_srandom(SERVER, "?np_srandom@CCSAuth@@IAEXK@Z");
void CCSAuth::np_srandom(DWORD dwSeed)
{
	return (this->*_np_srandom)(dwSeed);

	m_dwSeed = dwSeed;
}


////////////////////////////////////////


/// total guesswork
struct GG
{
	DWORD a1;
	DWORD dword_70B28C;
	_GG_AUTH_PROTOCOL* pBlock;
	char byte_70B294[260];
};


CCSAuth2::CCSAuth2(void)
{
	m_pProtocol = ((GG*)&ggGlobal)->pBlock;
	m_bPrtcRef = 0;
	m_dwUserFlag = 0;
	memset(&m_AuthQuery, 0, sizeof(m_AuthQuery));
	memset(&m_AuthAnswer, 0, sizeof(m_AuthAnswer));
	srand(_time32(NULL));
}


CCSAuth2::~CCSAuth2(void)
{
  if( m_bPrtcRef == 1 )
  {
    --m_dwUserFlag;
    if( m_dwUserFlag == 0 )
    {
		void* v1 = *(void **)m_pProtocol;
		if ( v1 != ((GG*)&ggGlobal)->pBlock )
			UnloadAuthProtocol((_GG_AUTH_PROTOCOL*)v1);
    }
  }
}


hook_method<void (CCSAuth2::*)(void)> CCSAuth2::_Init(SERVER, "?Init@CCSAuth2@@QAEXXZ");
void CCSAuth2::Init(void)
{
	return (this->*_Init)();

	//TODO
}
