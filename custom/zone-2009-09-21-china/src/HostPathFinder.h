#pragma once
#include "PathFinder.h"
#include "struct.hpp" // struct MOVEINFO


class CHostPathInfo : public CPathInfo
{
	/* this+ 0 */ public: //CPathInfo baseclass_0;
	/* this+28 */ public: MOVEINFO m_moveInfo;

	public: void CHostPathInfo::InitPosition(int xPos, int yPos, unsigned char dir);

private:
	static hook_method<void (CHostPathInfo::*)(int xPos, int yPos, unsigned char dir)> CHostPathInfo::_InitPosition;
};
