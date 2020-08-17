#pragma once


struct HO_SKINFO
{
	HO_SKINFO();

	/* this+ 0 */ int level;
	/* this+ 4 */ int type;
	/* this+ 8 */ int count;
	/* this+12 */ DWORD BlockUseTM;
	/* this+16 */ bool bDBupdateWhenLogout;
};
