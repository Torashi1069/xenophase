#include "GameMode.h"
#include "GameWorld.h"
#include "Globals.h"
#include "Item.h"
#include "ModeMgr.h"
#include "Player.h"
#include "Session.h"
#include "Skill.h"
#include "Resource/Wave.h"


CPlayer::CPlayer(void) // line 17
{
	this->CPlayer::OnInit();
}


CPlayer::~CPlayer(void) // line 22
{
	this->CPlayer::OnExit(); //inlined
}


hook_method<void (CPlayer::*)(void)> CPlayer::_OnInit(SAKEXE, "CPlayer::OnInit");
void CPlayer::OnInit(void) // line 27
{
	return (this->*_OnInit)();

	//TODO
}


hook_method<void (CPlayer::*)(void)> CPlayer::_OnExit(SAKEXE, "CPlayer::OnExit");
void CPlayer::OnExit(void) // line 129
{
	return (this->*_OnExit)();

	;
}


hook_method<bool (CPlayer::*)(void)> CPlayer::_OnProcess(SAKEXE, "CPlayer::OnProcess");
bool CPlayer::OnProcess(void) // line 136
{
	return (this->*_OnProcess)();

	this->CGameActor::ProcessBodyState();
	this->CGameActor::ProcessEffectState();
	this->CGameActor::ProcessWillBeAttacked();
	this->CGameActor::ProcessChatBalloon();

	if( m_isSingleColor && timeGetTime() > m_singleColorStartTick + 100 )
	{
		m_colorOfSingleColor = 0xFFFF0000;
		m_isSingleColor = false;
	}

	if( m_sprArgb != -1 )
		this->CRenderObject::ModifyArgb(8, 8, 8, 8);

	if( m_preMoveOn && timeGetTime() > m_preMoveStartTick + g_session.m_averagePingTime/2 )
	{
		MOVESTRUCT ms;
		g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetServerCoor(m_pos.x, m_pos.z, ms.sx, ms.sy, ms.cellX, ms.cellY);
		ms.startTime = g_session.CSession::GetServerTime();
		ms.dx = m_destCellX;
		ms.dy = m_destCellZ;
		Trace("PreMove");
		this->SendMsg(NULL, 0, (int)&ms, 0, 0);
	}

	this->CPlayer::ProcessProceed();
	bool ret = this->ProcessState();
	this->CRenderObject::ProcessSound();

	if( m_isPlayHitWave )
	{
		vector3d& pos = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->m_player->m_pos;
		PlayWave(m_hitWaveName, m_pos.x - pos.x, 0.0, m_pos.z - pos.z, 250, 40, 1.0);
		m_isPlayHitWave = 0;
	}

	return ret;
}


hook_method<bool (CPlayer::*)(void)> CPlayer::_ProcessState(SAKEXE, "CPlayer::ProcessState");
bool CPlayer::ProcessState(void) // line 655
{
	return (this->*_ProcessState)();

	//TODO
}


hook_method<void (CPlayer::*)(CGameObject* sender, int message, int arg1, int arg2, int arg3)> CPlayer::_SendMsg(SAKEXE, "CPlayer::SendMsg");
void CPlayer::SendMsg(CGameObject* sender, int message, int arg1, int arg2, int arg3) // line 683-998
{
	return (this->*_SendMsg)(sender, message, arg1, arg2, arg3);

	//TODO
/*
	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();

	switch( message )
	{
	case 66:
	{
		int values[4];
		values[0] = m_skillId;
		values[1] = m_gSkillDx;
		values[2] = m_gSkillDy;
		values[3] = m_skillUseLevel;

		if( m_skillId == SKID_HT_TALKIEBOX )
		{
			UIWindow* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_TALKBOXTRAPINPUTWND);
			wnd->SendMsg(NULL, UM_SET_SKILL_INFO, (int)values, 0, 0);
		}
		else
		if( m_skillId == SKID_RG_GRAFFITI )
		{
			UIWindow* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_GRAFFISTRBOXWND);
			wnd->SendMsg(NULL, UM_SET_SKILL_INFO, (int)values, 0, 0);
		}
		else
		{
			mode->SendMsg(MM_USE_SKILL_TOGROUND, (int)values, 0, 0);
		}
	}
	break;
	case 42:
	{
		mode->SendMsg(MM_USE_SKILL, m_skillId, m_proceedTargetGid, m_skillUseLevel);
	}
	break;
	case 40:
	{
		unsigned long targetGID = (unsigned long)arg1;
		int unknown = (int)arg2; //TODO

		if( unknown == 141 || unknown == 143 || unknown == 152 )
		{
			mode->SendMsg(MM_REQUEST_ACT, 7, targetGID, 0);
		}
		else
		{
			CGameActor* actor = mode->m_world->CWorld::GetGameActorByAID(m_proceedTargetGid);
			if( actor == NULL || actor->m_headType != 20 )
				mode->SendMsg(MM_REQUEST_ACT, 7, m_proceedTargetGid, 0);
		}
	}
	break;
	case 29:
	{
		unsigned long targetGID = (unsigned long)arg1;
		int unknown = (int)arg2; //TODO

		if( unknown == 141 || unknown == 143 || unknown == 152 )
		{
			mode->SendMsg(MM_REQUEST_ACT, 0, targetGID, 0);
		}
		else
		{
			mode->SendMsg(MM_REQUEST_ACT, 0, m_proceedTargetGid, 0);
		}
	}
	break;
	case 30:
	case 31:
	{
		if( !IsEffectStateBurrow(m_effectState) )
		{
			if( m_stateId == STATEID_STAND )
				mode->SendMsg(MM_REQUEST_ACT, 2, m_proceedTargetGid, 0);
			else
			if( m_stateId == STATEID_SIT )
				mode->SendMsg(MM_REQUEST_ACT, 3, m_proceedTargetGid, 0);
		}
	}
	break;
	case 17:
	{
		int x = (int)arg1;
		int y = (int)arg2;

		this->SendMsg(NULL, 13, 0, 0, 0);

		if( m_stateId == STATEID_ATTACK || m_stateId == STATEID_PICKUP || m_stateId == STATEID_SIT )
		{
			m_isPreengageStateOfMove = 1;
			m_preengageXOfMove = x;
			m_preengageYOfMove = y;
		}
		else
		{
			m_preengageXOfMove = -1;
			m_preengageYOfMove = -1;
			m_isPreengageStateOfMove = 0;
			this->SendMsg(NULL, 91, x, y, 0);
		}
	}
	break;
	case 91:
	{
		if( m_isWaitingMoveAck && timeGetTime() <= m_moveReqTick + 1000 )
			break;

		m_isWaitingMoveAck = 1;
		m_moveReqTick = timeGetTime();
		mode->SendMsg(151, arg1, arg2, 0);
	}
	break;
	case 16:
	{
		int sx = (int)arg1;
		int sy = (int)arg2;

		if( m_stateId != STATEID_STAND && m_stateId != STATEID_FLINCH && m_stateId != STATEID_SIT )
			return;

		float cx, cz;
		mode->CGameMode::GetClientCoor(sx, sy, cx, cz);

		float rotY = this->CRenderObject::CalcDir(m_pos.x, m_pos.z, cx, cz);
		int deltaY = (int)(m_roty - rotY);
		int huh = deltaY + ((char)-(deltaY < 0) & 360);
		int dirY = (unsigned __int64)(((double)huh + 22.5) / 45.0) + ((signed int)(((double)huh + 22.5) / 45.0) < 0 ? 8 : 0);
		if( dirY >= 8 )
			dirY -= 8;

		if( dirY == 0 || dirY == 4 )
		{
			m_roty = rotY;
			m_headDir = 0;
		}
		else
		if( dirY == 1 )
		{
			if( m_headDir != 1 )
			{
				m_headDir = 1;
			}
			else
			{
				m_roty = rotY;
				m_headDir = 0;
			}
		}
		else
		if( dirY == 2 || dirY == 3 )
		{
			m_headDir = 1;
			m_roty = rotY + 45.0;
			if( m_roty >= 360.0 )
				m_roty -= 360.0;
		}
		else
		if( dirY == 7 )
		{
			if( m_headDir != 2 )
			{
				m_headDir = 2;
			}
			else
			{
				m_roty = rotY;
				m_headDir = 0;
			}
		}
		else
		if( dirY == 5 || dirY == 6 )
		{
			m_headDir = 2;
			m_roty = rotY - 45.0;
			if( m_roty < 0.0 )
				m_roty += 360.0;
		}

		m_curMotion = m_headDir;
		int dir = ((int)m_roty + 180) / 45 % 8; // NOTE: inline of something
		mode->SendMsg(MM_CHANGE_DIRECTION, dir, m_headDir, 0);
	}
	break;
	case 9:
	{
		int destX = (int)arg1;
		int destZ = (int)arg2;

		m_preMoveOn = 1;
		m_preMoveStartTick = timeGetTime();
		m_destCellX = destX;
		m_destCellZ = destZ;
	}
	break;
	case 0:
	{
		UNKNOWN* unk1 = arg1;

		m_isWaitingMoveAck = 0;
		m_preMoveOn = 0;
		m_moveStartTime = *(_DWORD *)(unk1 + 0);
		if( this->CGameActor::FindPath(*(_DWORD *)(unk1 + 4), *(_DWORD *)(unk1 + 8), *(_DWORD *)(unk1 + 12), *(_DWORD *)(unk1 + 16), *(_DWORD *)(unk1 + 20), *(_DWORD *)(unk1 + 24), g_session.m_speed) )
		{
			m_moveDestX = *(_DWORD *)(unk1 + 20);
			m_moveDestY = *(_DWORD *)(unk1 + 24);
			this->SetState(1);
			m_pathStartCell = 0;
		}
		else
		{
			//TODO
			mode->CGameMode::GetServerCoor(m_pos.x, m_pos.z, (int *)&sender, &message, &arg3, &arg2);
			if( this->CGameActor::FindPath((int)sender, message, arg3, arg2, *(_DWORD *)(unk1 + 20), *(_DWORD *)(unk1 + 24), g_session.m_speed) )
			{
				m_moveDestX = *(_DWORD *)(unk1 + 20);
				m_moveDestY = *(_DWORD *)(unk1 + 24);
				this->SetState(1);
			}
		}
	}
	break;
	case 8:
	{
		this->SetState(0);
	}
	break;
	case 13:
	{
		m_isAttackRequest = 0;
		m_proceedType = PT_NOTHING;
		mode->SendMsg(MM_SETLOCKONMOUSE, 0, 0, 0);
	}
	break;
	case 15:
		if( m_proceedType == PT_ATTACK || m_proceedType == PT_ATTACK_2 )
		{
			if( m_attackMode != 0 )
			{
				m_attackMode = 2;
				if( m_totalAttackReqCnt != 0 )
				{
					this->SendMsg(NULL, 13, 0, 0, 0);
					mode->SendMsg(MM_CANCEL_LOCKON, 0, 0, 0);
				}
			}
		}
		else
		if( m_proceedType == PT_SKILL )
			mode->SendMsg(MM_SETLOCKONMOUSE, 0, 0, 0);
	break;
	case 90:
	{
		int skillUseLevel = (int)arg1;

		m_skillUseLevel = skillUseLevel;
	}
	break;
	case 65:
	{
		int skillId = (int)arg1;
		int gSkillDx = (int)arg2;
		int gSkillDy = (int)arg3;

		if( m_stateId == STATEID_SIT || IsEffectStateBurrow(m_effectState) )
			break;

		m_proceedType = PT_GROUNDSKILL;
		m_skillId = skillId;
		m_gSkillDx = gSkillDx;
		m_gSkillDy = gSkillDy;
		m_skillAttackRange = mode->m_skillUseInfo.m_attackRange;
		m_proceedTargetGid = 0;
	}
	break;
	case 41:
	{
		unsigned long targetGID = (unsigned long)arg1;
		int skillId = (int)arg2;
		int skillAttackRange = (int)arg3;

		if( m_stateId == STATEID_SIT || (IsEffectStateBurrow(m_effectState) && skillId != SKID_AS_GRIMTOOTH && skillId != SKID_RG_BACKSTAP) )
			break;

		m_skillId = skillId;
		m_proceedType = PT_SKILL;
		m_proceedTargetGid = targetGID;
		m_skillAttackRange = skillAttackRange;
	}
	break;
	case 60:
	{
		unsigned long targetGID = (unsigned long)arg1;

		if( m_stateId == STATEID_SIT || IsEffectStateBurrow(m_effectState) )
			break;

		m_proceedType = ( m_proceedType == PT_ATTACK ) ? PT_ATTACK_2 : PT_ATTACK;
		m_tickOfMoveForAttack = timeGetTime() - 1200;
		m_isAttackRequest = 0;
		m_totalAttackReqCnt = 0;
		m_proceedTargetGid = targetGID;
		m_destCellX = -1;
		m_destCellZ = -1;
	}
	break;
	case 10:
	{
		unsigned long targetGID = (unsigned long)arg1;
		int attackMode = (int)arg2;

		if( m_stateId == STATEID_SIT || IsEffectStateBurrow(m_effectState) )
			break;

		CGameActor* actor = mode->m_world->CWorld::GetGameActorByAID(targetGID);
		if( actor == NULL )
			break;

		m_proceedType = ( actor->m_speed <= g_session.m_speed * 4 / 3 ) ? PT_ATTACK : PT_ATTACK_2;
		m_isAttackRequest = 0;
		m_totalAttackReqCnt = 0;
		m_proceedTargetGid = targetGID;
		m_attackMode = attackMode;
	}
	break;
	case 18:
	{
		unsigned long targetGID = (unsigned long)arg1;

		if( m_stateId == STATEID_SIT || IsEffectStateBurrow(m_effectState) )
			break;

		m_proceedType = PT_PICKUPITEM;
		m_proceedTargetGid = targetGID;
	}
	break;
	case 103:
	{
		unsigned long targetGID = (unsigned long)arg1;
		UNKNOWN* unk2 = arg2;

		if( m_stateId == STATEID_SIT || IsEffectStateBurrow(m_effectState) )
			break;

		m_proceedType = PT_TOUCH_SKILL;
		m_skillId = *(_DWORD *)(unk2 + 4);
		m_skillUseLevel = *(_DWORD *)(unk2 + 12);
		m_skillAttackRange = *(_DWORD *)(unk2 + 8);;
		m_proceedTargetGid = targetGID;
	}
	break;
	default:
		this->CPc::SendMsg(sender, message, arg1, arg2, arg3);
	break;
	}
*/
};


hook_method<void (CPlayer::*)(int stateId)> CPlayer::_SetState(SAKEXE, "CPlayer::SetState");
void CPlayer::SetState(int stateId) // line 661
{
	return (this->*_SetState)(stateId);

	if( m_stateId == STATEID_DEAD )
		return;

	if( stateId != STATEID_WALK )
	{
		m_destCellX = -1;
		m_destCellZ = -1;
	}

	if( m_isPreengageStateOfMove && (m_stateId == STATEID_ATTACK || m_stateId == STATEID_PICKUP || m_stateId == STATEID_SIT) )
	{
		m_preengageXOfMove = -1;
		m_preengageYOfMove = -1;
		m_isPreengageStateOfMove = 0;
		this->SendMsg(NULL, 91, m_preengageXOfMove, m_preengageYOfMove, 0);
	}

	if( stateId == STATEID_DEAD )
	{
		CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();
		mode->SendMsg(5, 0, 0, 0);
		mode->CGameMode::PlaceEffect(&m_pos, 372, 300, 0);
	}

	this->CPc::SetState(stateId);
}


hook_method<void (CPlayer::*)(void)> CPlayer::_RegisterPos(SAKEXE, "CPlayer::RegisterPos");
void CPlayer::RegisterPos(void) // line 957 (GameActor.h)
{
	return (this->*_RegisterPos)();

	;
}


hook_method<void (CPlayer::*)(void)> CPlayer::_UnRegisterPos(SAKEXE, "CPlayer::UnRegisterPos");
void CPlayer::UnRegisterPos(void) // line 958 (GameActor.h)
{
	return (this->*_UnRegisterPos)();

	;
}


hook_method<void (CPlayer::*)(void)> CPlayer::_ProcessProceed(SAKEXE, "CPlayer::ProcessProceed");
void CPlayer::ProcessProceed(void) // line 348
{
	return (this->*_ProcessProceed)();

	CGameMode* mode = g_modeMgr.CModeMgr::GetGameMode();

	switch( m_proceedType )
	{
	case PT_ATTACK:
	case PT_ATTACK_2:
	{// attack (single or continuous)
		CGameActor* actor = mode->CGameMode::GetWorld()->CWorld::GetGameActorByAID(m_proceedTargetGid);
		if( actor == NULL )
		{
			this->SendMsg(NULL, 13, 0, 0, 0);
			return;
		}

		if( actor->m_stateId == STATEID_DEAD )
			return;

		int sx, sy;
		mode->CGameMode::GetServerCoor(m_pos.x, m_pos.z, sx, sy);

		if( this->CGameActor::GetJob() != JT_SAGE
		 && this->CGameActor::GetJob() != JT_SAGE_H
		 && this->CGameActor::GetJob() != JT_SAGE_B
		 && m_stateId != STATEID_WALK
		 && m_stateId != STATEID_STAND
		 && m_stateId != STATEID_FLINCH )
			return;

		float dist = actor->CRenderObject::CalcDist(m_pos.x, m_pos.y, m_pos.z);
		if( actor->CGameActor::GetActorType() == 1 )
		{
			dist -= 20.0;
			if( dist < 0.0 )
				dist = 0.0;
		}

		if( (m_destCellX == sx && m_destCellZ == sy) || dist <= 5 * g_session.m_attackRange + 5.5 )
		{
			if( m_attackMode == 2 )
				this->SendMsg(NULL, 13, 0, 0, 0);

			if( !m_isAttackRequest && m_attackReqTime + 1200 < timeGetTime() )
			{
				m_attackReqTime = timeGetTime();
				m_totalAttackReqCnt = m_totalAttackReqCnt + 1;
				m_isAttackRequest = 1;

				if( m_attackMode == 2 )
					this->SendMsg(NULL, 29, 0, 0, 0);
				else
					this->SendMsg(NULL, 40, 0, 0, 0);
			}
		}
		else
		{
			int delay = ( m_proceedType != PT_ATTACK_2 ) ? 450 : 1200;
			bool enoughDelayed = ( timeGetTime() > delay + m_tickOfMoveForAttack );
			bool notAtkState = ( m_stateId != STATEID_ATTACK );

			float cx, cz;
			if( m_proceedType == PT_ATTACK_2 )
			{
				cx = actor->m_pos.x;
				cz = actor->m_pos.z;
			}
			else
			{
				mode->CGameMode::GetClientCoor(actor->m_moveDestX, actor->m_moveDestY, cx, cz);
			}

			int fdx = actor->m_moveDestX;
			int fdz = actor->m_moveDestY;

			if( actor->CGameActor::GetActorType() == 1 )
			{
				float dir = this->CRenderObject::CalcDir(m_pos.x, m_pos.z, cx, cz);

				if( dir >= 0.0 && dir < 25.0 )
				{
					fdz += 5;
				}
				else
				if( dir >= 25.0 && dir < 70.0 )
				{
					fdx += 5;
					fdz += 5;
				}
				else
				if( dir >= 70.0 && dir < 115.0 )
				{
					fdx += 5;
				}
				else
				if( dir >= 115.0 && dir < 160.0 )
				{
					fdx += 5;
					fdz -= 5;
				}
				else
				if( dir >= 160.0 && dir < 205.0 )
				{
					fdz -= 5;
				}
				else
				if( dir >= 205.0 && dir < 250.0 )
				{
					fdx -= 5;
					fdz += 5;
				}
				else
				if( dir >= 250.0 && dir < 295.0 )
				{
					fdx -= 5;
				}
				else
				if( dir >= 295.0 && dir < 340.0 )
				{
					fdx -= 5;
					fdz -= 5;
				}
				else //( dir >= 340.0 && dir < 385.0 )
				{
					fdz += 5;
				}
			}

			mode->CGameMode::ConvertToNumCellCloseAndFindNoRedCell(m_pos.x, m_pos.z, cx, cz, fdx, fdz, g_session.m_attackRange);
			if( m_destCellX != fdx || m_destCellZ != fdz )
			{
				if( notAtkState && !m_isAttackRequest && enoughDelayed )
				{
					m_destCellX = fdx;
					m_destCellZ = fdz;
					m_tickOfMoveForAttack = timeGetTime();
					this->SendMsg(NULL, 91, fdx, fdz, 0);
				}
			}
		}
	}
	break;
	case PT_SKILL:
	{// use skill to target
		CGameActor* actor = ( m_proceedTargetGid == g_session.CSession::GetAid() ) ? this : mode->CGameMode::GetWorld()->CWorld::GetGameActorByAID(m_proceedTargetGid);
		if( actor == NULL )
		{
			this->SendMsg(NULL, 13, 0, 0, 0);
			return;
		}

		int sx, sz;
		mode->CGameMode::GetServerCoor(m_pos.x, m_pos.z, sx, sz);

		int fdx = actor->m_moveDestX;
		int fdz = actor->m_moveDestY;
		mode->CGameMode::ConvertToNumCellCloseAndFindNoRedCell(m_pos.x, m_pos.z, actor->m_pos.x, actor->m_pos.z, fdx, fdz, m_skillAttackRange);

		if( m_stateId != STATEID_WALK && m_stateId != STATEID_STAND && m_stateId != STATEID_FLINCH && m_stateId != STATEID_SONG && m_stateId != STATEID_DANCE )
			return;

		float dist = actor->CRenderObject::CalcDist(m_pos.x, m_pos.y, m_pos.z);
		if( actor->CGameActor::GetActorType() == 1 )
		{
			dist -= 20.0;
			if( dist < 0.0 )
				dist = 0.0;
		}

		if( dist <= 5 * m_skillAttackRange + 5.5 || m_destCellX == sx && m_destCellZ == sz )
		{
			this->SendMsg(NULL, 42, 0, 0, 0);
			this->SendMsg(NULL, 13, 0, 0, 0);
			return;
		}

		if( (m_destCellX == fdx && m_destCellZ == fdz) || m_stateId == STATEID_ATTACK )
			return;

		m_destCellX = fdx;
		m_destCellZ = fdz;

		if( actor->CGameActor::GetActorType() == 1 )
		{
			float dir = this->CRenderObject::CalcDir(m_pos.x, m_pos.z, actor->m_pos.x, actor->m_pos.z);

			if( dir >= 0.0 && dir < 25.0 )
			{
				fdz += 5;
			}
			else
			if( dir >= 25.0 && dir < 70.0 )
			{
				fdx += 5;
				fdz += 5;
			}
			else
			if( dir >= 70.0 && dir < 115.0 )
			{
				fdx += 5;
			}
			else
			if( dir >= 115.0 && dir < 160.0 )
			{
				fdx += 5;
				fdz -= 5;
			}
			else
			if( dir >= 160.0 && dir < 205.0 )
			{
				fdz -= 5;
			}
			else
			if( dir >= 205.0 && dir < 250.0 )
			{
				fdx -= 5;
				fdz += 5;
			}
			else
			if( dir >= 250.0 && dir < 295.0 )
			{
				fdx -= 5;
			}
			else
			if( dir >= 295.0 && dir < 340.0 )
			{
				fdx -= 5;
				fdz -= 5;
			}
			else //( dir >= 340.0 && dir < 385.0 )
			{
				fdz += 5;
			}
		}

		this->SendMsg(NULL, 91, fdx, fdz, 0);
	}
	break;
	case PT_GROUNDSKILL:
	{// use skill to ground
		int selfX, selfZ;
		mode->CGameMode::GetServerCoor(m_pos.x, m_pos.z, selfX, selfZ);

		float cx, cz;
		mode->CGameMode::GetClientCoor(m_gSkillDx, m_gSkillDy, cx, cz);

		int dx, dz;
		mode->CGameMode::ConvertToNumCellCloseAndFindNoRedCell(m_pos.x, m_pos.z, cx, cz, dx, dz, m_skillAttackRange);

		if( m_stateId != STATEID_WALK && m_stateId != STATEID_STAND && m_stateId != STATEID_FLINCH )
			return;

		float dist = this->CRenderObject::CalcDist(cx, m_pos.y, cz);
		if( dist <= 5 * m_skillAttackRange + 5.5 || m_destCellX == selfX && m_destCellZ == selfZ )
		{
			this->SendMsg(NULL, 66, 0, 0, 0);
			this->SendMsg(NULL, 13, 0, 0, 0);
		}
		else
		if( (m_destCellX != dx || m_destCellZ != dz) && m_stateId != STATEID_ATTACK )
		{
			m_destCellX = dx;
			m_destCellZ = dz;
			this->SendMsg(NULL, 91, dx, dz, 0);
		}
	}
	break;
	case PT_PICKUPITEM:
	{// pick up item
		CItem* item = mode->CGameMode::GetWorld()->CWorld::GetItemByAID(m_proceedTargetGid);
		if( item == NULL )
		{
			this->SendMsg(NULL, 13, 0, 0, 0);
			return;
		}

		int selfX, selfZ;
		mode->CGameMode::GetServerCoor(m_pos.x, m_pos.z, selfX, selfZ);

		int sx, sz;
		mode->CGameMode::GetServerCoor(item->m_pos.x, item->m_pos.z, sx, sz);

		int dx = sx, dz = sz;
		mode->CGameMode::ConvertToNoRedCell(selfX, selfZ, dx, dz);

		if( m_stateId != STATEID_STAND )
			return;

		if( mode->CGameMode::IsInsideCell(selfX, selfZ, dx, dz, 1) )
		{
			this->SendMsg(NULL, 16, dx, dz, 0);
			if( !mode->CGameMode::IsReqPickupItemNaid(m_proceedTargetGid) )
			{
				mode->CGameMode::AddPickupItemNaid(m_proceedTargetGid);
				mode->SendMsg(149, m_proceedTargetGid, 0, 0);
			}
			this->SendMsg(NULL, 13, 0, 0, 0);
		}
		else
		if( m_destCellX != sx || m_destCellZ != sz )
		{
			m_destCellX = sx;
			m_destCellZ = sz;
			this->SendMsg(NULL, 91, sx, sz, 0);
		}
	}
	break;
	case PT_TOUCH_SKILL:
	{
		CSkill* skill = mode->CGameMode::GetWorld()->CWorld::GetSkillByAID(m_proceedTargetGid);
		if( skill == NULL )
		{
			this->SendMsg(NULL, 13, 0, 0, 0);
			return;
		}

		int selfX, selfZ;
		mode->CGameMode::GetServerCoor(m_pos.x, m_pos.z, selfX, selfZ);

		int sx, sz;
		mode->CGameMode::GetServerCoor(skill->m_pos.x, skill->m_pos.z, sx, sz);

		float cx, cz;
		mode->CGameMode::GetClientCoor(sx, sz, cx, cz);

		int dx, dz;
		mode->CGameMode::ConvertToNumCellCloseAndFindNoRedCell(m_pos.x, m_pos.z, cx, cz, dx, dz, m_skillAttackRange);

		if( m_stateId != STATEID_WALK && m_stateId != STATEID_STAND && m_stateId != STATEID_FLINCH )
			return;

		float dist = this->CRenderObject::CalcDist(cx, m_pos.y, cz);
		if( dist <= 5 * m_skillAttackRange + 5.5 || m_destCellX == selfX && m_destCellZ == selfZ )
		{
			if( m_skillId == 0 && (skill->CGameActor::GetJob() == JT_ICEWALL || skill->CGameActor::GetJob() == JT_TRAP_BLASTMINE || skill->CGameActor::GetJob() == JT_TRAP_CLAYMORETRAP) )
			{
				this->SendMsg(NULL, 29, 0, 0, 0);
			}
			else
			{
				this->SendMsg(NULL, 42, 0, 0, 0);
				this->SendMsg(NULL, 13, 0, 0, 0);
			}
		}
		else
		if( m_destCellX != dx || m_destCellZ != dz )
		{
			if( m_stateId != STATEID_ATTACK || skill->CGameActor::GetJob() == JT_ICEWALL || skill->CGameActor::GetJob() == JT_TRAP_BLASTMINE || skill->CGameActor::GetJob() == JT_TRAP_CLAYMORETRAP )
			{
				m_destCellX = dx;
				m_destCellZ = dz;
				this->SendMsg(NULL, 91, dx, dz, 0);
			}
		}
	}
	break;
	default:
	break;
	}
}


hook_method<void (CPlayer::*)(void)> CPlayer::_ProcessPreengageMove(SAKEXE, "CPlayer::ProcessPreengageMove");
void CPlayer::ProcessPreengageMove(void) // line 335
{
	return (this->*_ProcessPreengageMove)();

	//TODO
}


hook_method<void (CPlayer::*)(void)> CPlayer::_ReLaunchBlurEffects(SAKEXE, "CPlayer::ReLaunchBlurEffects");
void CPlayer::ReLaunchBlurEffects(void) // line 1002
{
	return (this->*_ReLaunchBlurEffects)();

	//TODO
}
