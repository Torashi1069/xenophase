#pragma once


typedef struct _GG_AUTH
{
	DWORD dwProtocolCount;
	DWORD nMaxCount;
	struct _GG_AUTH_PROTOCOL* lpCurrentAuthProtocol;
	char szGGAuthName[256];
} GG_AUTH, *PGG_AUTH;


typedef struct _GG_AUTH_DATA
{
	DWORD dwIndex;
	DWORD dwValue1;
	DWORD dwValue2;
	DWORD dwValue3;
} GG_AUTH_DATA, *PGG_AUTH_DATA;


typedef struct _GG_AUTH_PROTOCOL
{
	HINSTANCE hDllHinstance;
	DWORD dwPtrcVersion;
	DWORD dwQueryCount;
	DWORD dwFlag;
	DWORD (*PtrcGetAuthQuery)(int, PGG_AUTH, PGG_AUTH_DATA, PGG_AUTH_DATA);
	DWORD (*PtrcCheckAuthAnswer)(int, PGG_AUTH, PGG_AUTH_DATA, PGG_AUTH_DATA);
	struct _GG_AUTH_PROTOCOL* lpPrevProtocol;
} GG_AUTH_PROTOCOL, *PGG_AUTH_PROTOCOL;


#define ERROR_GGAUTH_FAIL_MEM_ALLOC               1 // CS인증 모듈 로딩시 메모리 부족
#define ERROR_GGAUTH_FAIL_LOAD_DLL                2 // CS인증 모듈(*.dll, *.so) 로딩 실패
#define ERROR_GGAUTH_FAIL_GET_PROC                3 // CS인증 모듈의 export 함수 설정 실패
#define ERROR_GGAUTH_FAIL_BEFORE_INIT             4 // 비정상 동작 <- critical error
#define ERROR_GGAUTH_FAIL_LOAD_CFG                5 // 서버인증 모듈 설정 파일 로딩 실패.
#define ERROR_GGAUTH_INVALID_PARAM               10 // 함수 호출시 잘못된 인자값을 넘겼을 경우
#define ERROR_GGAUTH_NO_REPLY                    11 // 응답없음. GetAuthQuery() 가 CheckAuthAnswer()하기전에 두번 불려지면 같은에러 발생
#define ERROR_GGAUTH_INVALID_PROTOCOL_VERSION    12 // CS인증 모듈 프로토콜 번호(ggauth##.dll) 틀림
#define ERROR_GGAUTH_INVALID_REPLY               13 // 알고리즘에 의한 응답값 틀림.
#define ERROR_GGAUTH_INVALID_GAMEGUARD_VER       14 // 게임가드 버젼검사. 라이브러리 2.5에서 추가됨(cs인증모듈 50번 이상)
#define ERROR_GGAUTH_SAME_CLIENT_DETECTED        15 // 동일 게임가드 사용자 검출
#define ERROR_GGAUTH_CLIENT_STOPPED              16 // 게임가드가 동작하지 않음
#define ERROR_GGAUTH_CLIENT_AUTH_ERROR           17 // 게임가드 동작 인증에 실패함 (동일 게임가드 or 인증 변조)
#define ERROR_GGAUTH_INVALID_PACKET              18 // 헤더가 올바르지 않음
#define ERROR_GGAUTH_INVALID_CRC1                19 // 응답 패킷이 올바르지 않거나 변조됨
#define ERROR_GGAUTH_INVALID_CRC2                20 // 응답 패킷이 올바르지 않거나 변조됨
#define ERROR_GGAUTH_CLIENT_HACK_DETECTED        21 // 게임가드에서 Hack 을 발견하여 서버인증 값이 변조됨
#define ERROR_GGAUTH_SETSTATE_ERROR              50 // SetCSAuthState() 호출 시 m_CSAuthState가 NULL이거나.. m_PrtcTemp가 NULL 인 경우 (pProtocolHead 를 찾을 수 없는 경우...)
#define ERROR_GGAUTH_INVALID_GAMEMON_VER        101
#define ERROR_GGAUTH_INVALID_GAMEMON_VER_CODE   102
#define ERROR_GGAUTH_RETRY_QUERY                200


DWORD InitGameguardAuth(LPSTR szGGAuthName, DWORD nNumberOfUser);
void  CleanupGameguardAuth();
DWORD LoadAuthProtocol(LPSTR lpszAuthDll, BOOL Flag);
DWORD UnloadAuthProtocol(_GG_AUTH_PROTOCOL* pAuthProtocol);


extern GG_AUTH& ggGlobal;
