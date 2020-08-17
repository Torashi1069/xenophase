#include "GameGuard/ggsrv.h"


/// globals
GG_AUTH& ggGlobal = VTOR<GG_AUTH>(DetourFindFunction(EXEPATH(), "?ggGlobal@@3U__unnamed@@A"));


DWORD InitGameguardAuth(LPSTR szGGAuthName, DWORD nNumberOfUser)
{
	ggGlobal.dwProtocolCount = 0;
	ggGlobal.nMaxCount = nNumberOfUser;
	ggGlobal.lpCurrentAuthProtocol = NULL;
	ggGlobal.szGGAuthName[0] = '\0';

	if( szGGAuthName != NULL && szGGAuthName[0] != '\0' )
	{
		if( szGGAuthName[strlen(szGGAuthName) - 1] == '\\' )
			strcpy(ggGlobal.szGGAuthName, szGGAuthName);
		else
			sprintf(ggGlobal.szGGAuthName, "%s%c", szGGAuthName, '\\');
	}

	DWORD dwResult = LoadAuthProtocol("ggauth.dll", TRUE);
	if( dwResult != ERROR_SUCCESS )
	{
		CleanupGameguardAuth();
		return dwResult;
	}

	return ERROR_SUCCESS;
}


void CleanupGameguardAuth()
{
	while( ggGlobal.lpCurrentAuthProtocol != NULL )
	{
		_GG_AUTH_PROTOCOL* pAuthProtocol = ggGlobal.lpCurrentAuthProtocol;
		ggGlobal.lpCurrentAuthProtocol = pAuthProtocol->lpPrevProtocol;

		if( pAuthProtocol->hDllHinstance != NULL )
			FreeLibrary(pAuthProtocol->hDllHinstance);

		free(pAuthProtocol);
	}
}


DWORD LoadAuthProtocol(LPSTR lpszAuthDll, BOOL Flag)
{
	_GG_AUTH_PROTOCOL* pProtocol = (_GG_AUTH_PROTOCOL*)malloc(sizeof(_GG_AUTH_PROTOCOL));
	if( pProtocol == NULL )
		return ERROR_GGAUTH_FAIL_MEM_ALLOC;

	char szTemp[MAX_PATH];
	sprintf(szTemp, "%s%s", ggGlobal.szGGAuthName, lpszAuthDll);

	pProtocol->hDllHinstance = LoadLibraryA(szTemp);
	if( pProtocol->hDllHinstance == NULL )
	{
		free(pProtocol);
		return ERROR_GGAUTH_FAIL_LOAD_DLL;
	}

	DWORD (*PtrcGetVersion)() = (DWORD(*)())GetProcAddress(pProtocol->hDllHinstance, "PrtcGetVersion"); 
	pProtocol->PtrcGetAuthQuery = (DWORD (*)(int, _GG_AUTH*, _GG_AUTH_DATA*, _GG_AUTH_DATA*))GetProcAddress(pProtocol->hDllHinstance, "PrtcGetAuthQuery");
	pProtocol->PtrcCheckAuthAnswer = (DWORD (*)(int, _GG_AUTH*, _GG_AUTH_DATA*, _GG_AUTH_DATA*))GetProcAddress(pProtocol->hDllHinstance, "PrtcCheckAuthAnswer");

	if( PtrcGetVersion == NULL || pProtocol->PtrcGetAuthQuery == NULL || pProtocol->PtrcCheckAuthAnswer == NULL )
	{
		FreeLibrary(pProtocol->hDllHinstance);
		free(pProtocol);
		return ERROR_GGAUTH_FAIL_GET_PROC;
	}

	pProtocol->dwPtrcVersion = PtrcGetVersion();
	pProtocol->dwQueryCount = 0;
	pProtocol->dwFlag = 0;

	if( Flag )
	{
		pProtocol->dwFlag = 3;
		pProtocol->lpPrevProtocol = NULL;
	}
	else
	{
		pProtocol->dwFlag = 1;
		ggGlobal.lpCurrentAuthProtocol->dwFlag &= ~1;
		pProtocol->lpPrevProtocol = ggGlobal.lpCurrentAuthProtocol;
	}

	ggGlobal.lpCurrentAuthProtocol = pProtocol;
	++ggGlobal.dwProtocolCount;

	return ERROR_SUCCESS;
}


DWORD UnloadAuthProtocol(_GG_AUTH_PROTOCOL* pAuthProtocol)
{
	if( ggGlobal.dwProtocolCount <= 1 || ggGlobal.lpCurrentAuthProtocol->lpPrevProtocol == NULL )
		return ERROR_GGAUTH_INVALID_PARAM;

	_GG_AUTH_PROTOCOL* pProtocol;
	for( pProtocol = ggGlobal.lpCurrentAuthProtocol; pProtocol != NULL; pProtocol = pProtocol->lpPrevProtocol )
		if( pProtocol->lpPrevProtocol == pAuthProtocol )
			break;

	if( pProtocol == NULL )
		return ERROR_GGAUTH_INVALID_PARAM;

	pProtocol->lpPrevProtocol = pAuthProtocol->lpPrevProtocol;

	if( pAuthProtocol->hDllHinstance != NULL )
		FreeLibrary(pAuthProtocol->hDllHinstance);

	free(pAuthProtocol);
	--ggGlobal.dwProtocolCount;

	return ERROR_SUCCESS;
}
