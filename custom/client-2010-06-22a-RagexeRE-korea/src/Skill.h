#pragma once
#include "GameActor.h"


class CGroundScope : public CAbleToMakeEffect
{
public:
	CGroundScope();
	virtual void Render(matrix& vtm);
	virtual bool OnProcess();
	virtual void SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3);

private:
	int GetScopeSize(int skill_id);

private:
	/* this+  0 */ //CAbleToMakeEffect baseclass_0;
	/* this+280 */ int m_master_gid;
	/* this+284 */ int m_ground_pos_x;
	/* this+288 */ int m_ground_pos_y;
	/* this+292 */ DWORD m_lastingTime;
	/* this+296 */ int m_scope_size;
	/* this+300 */ float m_rot;
	/* this+304 */ float m_rot_speed;

private:
	static hook_func<void (CGroundScope::*)(matrix& vtm)> CGroundScope::_Render;
};
