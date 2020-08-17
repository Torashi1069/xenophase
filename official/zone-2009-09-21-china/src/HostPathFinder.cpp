#include "HostPathFinder.h"


hook_method<void (CHostPathInfo::*)(int xPos, int yPos, unsigned char dir)> CHostPathInfo::_InitPosition(SERVER, "CHostPathInfo::InitPosition");
void CHostPathInfo::InitPosition(int xPos, int yPos, unsigned char dir) // line 10
{
	return (this->*_InitPosition)(xPos, yPos, dir);

	m_startPointX = float(xPos);
	m_moveInfo.xPos = xPos;
	m_moveInfo.dxPos = xPos;
	m_startPointY = float(yPos);
	m_moveInfo.yPos = yPos;
	m_moveInfo.dyPos = yPos;
	m_moveInfo.dir = dir;
	m_moveInfo.state = CHARACTER_STATE_ENTER;
	m_moveInfo.LastTime = timeGetTime();
}
