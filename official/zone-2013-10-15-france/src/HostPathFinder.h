#pragma once
#include "PathFinder.h"


struct MOVEINFO
{
	/* this+ 0 */ int xPos;
	/* this+ 4 */ int yPos;
	/* this+ 8 */ int dxPos;
	/* this+12 */ int dyPos;
	/* this+16 */ unsigned long LastTime;
	/* this+20 */ char dir;
	/* this+24 */ int state; // enumCHARACTERSTATE
};


class CHostPathInfo : public CPathInfo
{
public:
	/* this+ 0 */ //CPathInfo baseclass_0;
	/* this+28 */ MOVEINFO m_moveInfo;

public:
	void InitPosition(int xPos, int yPos, unsigned char dir);
};
