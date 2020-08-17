#include "CharacterMgr.h"
#include "ErrorLog.h"
#include "HSvrIO.h"
#include "MapInfo.h"
#include "NPC.h"
#include "CNpcMercenary.hpp"
#include "CNpcMob.hpp"
#include "PC.h"
#include "RoomMgr.h"
#include "CSpecialItemMgr.hpp"
#include "ZoneProcess.h" // MS_MAPMOVE
#include "Common/Packet.h"
#include "shared.h" // Trace()


hook_method<int (CPC::*)(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4)> CPC::_OnMsg(SERVER, "CPC::OnMsg");
int CPC::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // line 1152
{
	return (this->*_OnMsg)(sender, receiver, msgID, par1, par2, par3, par4);

	switch( msgID )
	{
	case CM_KILLED:
	{
		CCharacter* target = (CCharacter*)par1;

		if( target != NULL )
		{
			CNpcMercenary* merc = m_pcBattle.CPCBattle::GetMercenary();
			if( merc != NULL )
				g_characterMgr->CCharacterMgr::SendMsg(this, merc, CM_KILLED, (int)target, 0, 0, 0);
		}

		return 0;
	}

	case CM_MERCE_TYPICALJOBINFO_CHANGED:
		m_pcBattle.CPCBattle::Mercenary_TYPICALJOBINFO_CHANGED();
		return 0;

	case CM_MAPMOVE:
	{
		MS_MAPMOVE* msg = (MS_MAPMOVE*)par1;
		eVanishType type = (eVanishType)par2;

		if( this->CPC::GetRoomID() != 0 )
		{
			g_roomMgr->CRoomMgr::ExitRoom(this->CPC::GetRoomID(), m_characterInfo.characterName);
			this->CPC::SetRoomID(0);
		}

		this->CPC::DisableAllCommand();

		unsigned long masterAID = this->GetEffective(EFST_MARIONETTE, 0);
		if( masterAID != 0 )
			g_characterMgr->CCharacterMgr::SendMsg(NULL, masterAID, CM_RESETEFFECTIVE, EFST_MARIONETTE_MASTER, 0, 0, 0);
		else
			this->ResetEffective(EFST_MARIONETTE_MASTER, 0);

		if( this->GetEffective(EFST_SG_WARM, 0) || this->GetEffective(EFST_DAURA, 0) )
		{
			g_characterMgr->CCharacterMgr::SendMsg(NULL, this, CM_PLAYSKILL_CANCEL, 0, 0, 0, 0);
			m_pcSkill.CPCSkill::DestroyPlayingSkill();
		}

		if( !m_pcClientUpdater.CPCClientUpdater::MapMove(msg->mapName, msg->xPos, msg->yPos, msg->AID, type) )
		{
			PACKET_ZC_NPCACK_ENABLE packet;
			packet.PacketType = HEADER_ZC_NPCACK_ENABLE;
			this->CPC::Send(sizeof(packet), (char*)&packet);
		}

		m_lockCounter = 0;
		this->ResetEffective(EFST_BLADESTOP, 0);
		this->ResetEffective(EFST_BASILICA, 0);
		this->ResetEffective(EFST_RUN, 0);

		if( g_castleMapMoveCheck == 1 && g_mapInfo->CMapInfo::IsSiege(msg->mapName) == 1 )
		{
			PACKET_ZH_CASTLE_MAP_MOVE packet;
			packet.PacketType = HEADER_ZH_CASTLE_MAP_MOVE;
			packet.AID = m_characterInfo.accountID;
			g_hSvrIO->CSvrIO::Send(sizeof(packet), (char*)&packet);
		}

		return 0;
	}

	case CM_REFUSE_ENTER:
	{
		PACKET_ZC_REFUSE_ENTER packet;
		packet.PacketType = HEADER_ZC_REFUSE_ENTER;
		packet.ErrorCode; //FIXME: uninitialized
		this->CPC::Send(2, (char*)&packet); //FIXME: should be 3 bytes
		return 0;
	}

	case CM_NOTIFY_BAN:
		m_pcClientUpdater.CPCClientUpdater::NotifyBan(par1, par2);
		return 0;

	case CM_WARP_BETWEENSERVER:
		this->CPC::WarpBetweenServer();
		return 0;

	case CM_WHISPER:
		m_pcClientUpdater.CPCClientUpdater::OnWhisper(par1, par2, (char*)par3);
		return 0;

	case CM_WHISPER_ACK:
		m_pcClientUpdater.CPCClientUpdater::OnWhisperAck(par1);
		return 0;

	case CM_RESTART_HSERVER:
	{
		PACKET_ZC_RESTART_ACK packet;
		packet.PacketType = HEADER_ZC_RESTART_ACK;
		packet.type = 1;
		this->CPC::Send(sizeof(packet), (char*)&packet);
		return 0;
	}

	case CM_DIALOG:
		m_pcClientUpdater.CPCClientUpdater::OnDialog(par1, par2, par3);
		return 0;

	case CM_WAIT_DIALOG:
		m_pcClientUpdater.CPCClientUpdater::OnWaitDialog(par1);
		return 0;

	case CM_CLOSE_DIALOG:
		m_pcClientUpdater.CPCClientUpdater::OnCloseDialog(par1);
		return 0;

	case CM_MENU_LIST:
		m_pcClientUpdater.CPCClientUpdater::OnMenuList(par1, par2, par3);
		return 0;

	case CM_EXCHANGE_ITEM:
		m_pcitemInventoryMgr.CPCItemInventoryMgr::OnExchangeItem(par1);
		return 0;

	case CM_CHECKPOINT:
		this->CPC::OnCheckPoint(par1);
		return 0;

	case CM_SET_ITEM:
		m_pcitemInventoryMgr.CPCItemInventoryMgr::OnSetBodyItem(par1, par2, par3);
		return 0;

	case CM_USER_COUNT:
		m_pcClientUpdater.CPCClientUpdater::OnUserCount(par1);
		return 0;

	case CM_SEND_PACKET:
		this->CPC::Send(par1, (char*)par2);
		return 0;

	case CM_FORCESEND_PACKET:
		this->CPC::ForceSend(par1, (char*)par2);
		return 0;

	case CM_CHAT:
		m_pcClientUpdater.CPCClientUpdater::OnChat(sender, par1, (char*)par2);
		return 0;

	case CM_DESTROY_ROOM:
		if( this->CPC::GetRoomID() == par1 )
			return 0;
		this->CPC::Send(par2, (char*)par3);
		return 0;

	case CM_MULTICAST_DESTROY_ROOM:
		this->CPC::MulticastDestroyRoom();
		return 0;

	case CM_ROOM_NEWENTRY:
		this->CPC::RoomNewEntry(par1);
		return 0;

	case CM_MULTICAST_ROOM_NEWENTRY:
		this->CPC::MulticastRoomNewEntry(par1);
		return 0;

	case CM_SET_ROOMID:
		this->CPC::SetRoomID(par1);
		return 0;

	case CM_EXCHANGE_ITEM_CANCEL:
	{
		m_exchangeItemInfo.AID = 0;
		m_exchangeItemInfo.isPermited = 0;
		m_exchangeItemInfo.isConcluded = 0;
		m_pcitemInventoryMgr.CPCItemInventoryMgr::CancelExchangeItem();

		PACKET_ZC_CANCEL_EXCHANGE_ITEM packet;
		packet.PacketType = HEADER_ZC_CANCEL_EXCHANGE_ITEM;
		this->CPC::Send(sizeof(packet), (char*)&packet);
		return 0;
	}

	case CM_EXEC_EXCHANGE_ITEM:
		this->CPC::OnExecExchangeItem(par1);
		return 0;

	case CM_NOTIFY_STOREDITEM:
		if( g_storePasswordCheck != 0 )
			this->CPC::OnCM_NOTIFY_STOREDITEM();
		else
			this->CPC::AsyncLoadStore();
		return 0;

	case CM_CARTON:
		this->CPC::AsyncLoadCart(sender);
		return 0;

	case CM_CARTOFF:
		this->CPC::CartOff();
		return 0;

	case CM_ADD_MEMBER_TO_GROUP:
		this->CPC::OnAddMemberToGroup(par1, par2);
		return 0;

	case CM_DELETE_MEMBER_FROM_GROUP:
		this->CPC::OnDeleteMemberFromGroup(par1, par2);
		return 0;

	case CM_ACK_MAKE_GROUP:
		this->CPC::OnAckMakeGroup(par1, par2);
		return 0;

	case CM_GROUP_LIST:
		this->CPC::OnGroupList(par1, par2, par3);
		return 0;

	case CM_GROUPINFO_CHANGE:
		this->CPC::OnGroupInfoChange(par1);
		return 0;

	case CM_ACK_REQ_JOIN_GROUP:
		this->CPC::OnAckReqJoinGroup(par1, par2);
		return 0;

	case CM_REQ_JOIN_GROUP:
		this->CPC::OnReqJoinGroup(par1, par2);
		return 0;

	case CM_NOTIFY_POSITION_PARTY:
		this->CPC::OnNotifyPositionParty(sender, par1, par2, par3);
		return 0;

	case CM_NOTIFY_POSITION_GUILD:
		this->CPC::OnNotifyPositionGuild(sender, par1, par2, par3);
		return 0;

	case CM_NOTIFY_HP_PARTY:
		this->CPC::OnNotifyHpParty(sender, par1, par2, par3);
		return 0;

	case CM_GRID_UPDATE:
		this->CPC::OnGRIDUpdate(par1, par2);
		return 0;

	case CM_CHAT_PARTY:
		this->CPC::OnChatParty(par1, par2, par3);
		return 0;

	case CM_SAVE_ITEM:
		this->CPC::AsyncSaveBodyItem();
		return 0;

	case CM_ADD_EXP:
		this->CPC::OnAddExp(sender, par1, par2);
		return 0;

	case CM_SHARE_EXP:
		this->CPC::OnShareExp(sender, par1);
		return 0;

	case CM_ADD_VIRTUE:
		this->CPC::OnAddVirtue(par1);
		return 0;

	case CM_ADD_PARTYEXP:
		this->CPC::OnAddPartyExp(par1, par2, par3);
		return 0;

	case CM_ADD_JOBEXP:
		this->CPC::OnAddJobExp(sender, par1, par2, par3);
		return 0;

	case CM_SHARE_JOBEXP:
		this->CPC::OnShareJobExp(sender, par1);
		return 0;

	case CM_ADD_PARTYJOBEXP:
		this->CPC::OnAddPartyJOBExp(par1, par2, par3);
		return 0;

	case CM_ADD_MVPITEM:
		this->CPC::OnMVPItem(par1);
		return 0;

	case CM_ADD_MVPEXP:
		this->CPC::OnMVPExp(par1);
		return 0;

	case CM_ADDSKILL:
		this->CPC::OnAddSkill(par1);
		return 0;

	case CM_SKILL_LEVELUP:
		this->CPC::OnSkillLevelUp(par1);
		return 0;

	case CM_HP_PLUS:
		this->CPC::OnHPPlus(par1, par2, par3);
		return 0;

	case CM_ATTACKSKILL_TOCHARACTER:
		if( m_mapRes != NULL )
			m_pcBattle.CPCBattle::ActSkillToChar_ATK(par1, par2, par3);
		else
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCMsg.cpp", 1433, "MapRes == NULL, %s, SKILL(%d)", m_characterInfo.characterName, par1);
		return 0;

	case CM_OPERATIONSKILL_TOCHARACTER:
		if( m_mapRes != NULL )
			m_pcBattle.CPCBattle::OPSkillToCharacter(par1, par2, par3);
		else
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCMsg.cpp", 1441, "MapRes == NULL, %s, SKILL(%d)", m_characterInfo.characterName, par1);
		return 0;

	case CM_SPATTACKSKILL_TOCHARACTER:
		if( m_mapRes != NULL )
			this->CPC::ActSkillToChar_SpATK(par1, par2, par3);
		else
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCMsg.cpp", 1449, "MapRes == NULL, %s, SKILL(%d)", m_characterInfo.characterName, par1);
		return 0;

	case CM_OPERATIONSKILL_TOSELF:
		if( m_mapRes != NULL )
			m_pcBattle.CPCBattle::OPSkillToSelf(par1, par2, par3);
		else
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCMsg.cpp", 1457, "MapRes == NULL, %s, SKILL(%d)", m_characterInfo.characterName, par1);
		return 0;

	case CM_OPERSKILL_TO_GUILD:
		this->CPC::OPSkillToGuild(par1, par2, par3);
		return 0;

	case CM_OPERSKILL_TO_RANGEGUILD:
		this->CPC::OPSkillToRangeGuild(par1, par2, par3);
		return 0;

	case CM_SP_PLUS:
		this->CPC::OnSPPlus(par1, par2, par3);
		return 0;

	case CM_TOUCHED_SKILLOBJECT:
		this->CPC::OnTouchedSkillObject(par1, par2, par3);
		return 0;

	case CM_HEAL_HP:
		this->CPC::OnHealHP(par1);
		return 0;

	case CM_SKILL_GROUNDTYPE:
		this->CPC::OnGroundSkill(par1, par2, par3);
		return 0;

	case CM_AGI_CHANGE:
		this->CPC::OnChangeAGI(par1, par2, par3);
		return 0;

	case CM_DEX_CHANGE:
		this->CPC::OnChangeDEX(par1, par2, par3);
		return 0;

	case CM_INT_CHANGE:
		this->CPC::OnChangeINT(par1, par2, par3);
		return 0;

	case CM_LUK_CHANGE:
		this->CPC::OnChangeLUK(par1, par2, par3);
		return 0;

	case CM_STR_CHANGE:
		this->CPC::OnChangeSTR(par1, par2, par3);
		return 0;

	case CM_VIT_CHANGE:
		this->CPC::OnChangeVIT(par1, par2, par3);
		return 0;

	case CM_TELEPORT_CHARACTER:
		this->CPC::OnTeleportCharacter(par1, par2, par3);
		return 0;

	case CM_WARP_CHARACTER:
		this->CPC::OnWarpCharacter(par1, par2, par3);
		return 0;

	case CM_WARPPOSITION_REMEMBER:
		this->CPC::OnWarpPositionRemember(par1, par2, par3);
		return 0;

	case CM_BLESSING_FROM_ACOLYTE:
		this->CPC::OnBlessingFromAcolyte(sender, par1, par2, par3);
		return 0;

	case CM_CURE_FROM_ACOLYTE:
		this->CPC::OnCureFromAcolyte();
		return 0;

	case CM_SKILL_OWL:
		m_characterInfo.ArcherDex = par3;
		m_pcClientUpdater.CPCClientUpdater::NotifyStatusParameter(VAR_DEX, this->CPC::GetDefaultDexValue(), this->CPC::GetDexPlusValue());
		return 0;

	case CM_SKILL_VULTURE:
		this->CPC::OnPlusAttRangeOnVulture(par1, par2, par3);
		return 0;

	case CM_SKILL_INCCARRY:
		this->CPC::OnIncCarry(par3);
		return 0;

	case CM_SKILL_SG_KNOWLEDGE:
		if( par3 <= 0 )
			return 0;
		this->CPC::OnIncCarry2(par1, par2, par3);
		return 0;

	case CM_SKILL_SG_DEVIL:
		if( par3 <= 0 )
			return 0;
		this->CPC::OnSgDevil(par1, par2, par3);
		return 0;

	case CM_SKILL_SG_FRIEND:
		if( par3 <= 0 )
			return 0;
		this->CPC::OnSgFriend(par1, par2, par3);
		return 0;

	case CM_SKILL_VENDING:
		this->CPC::OnVending(par1, par2, par3);
		return 0;

	case CM_NOTIFY_INFOTOSECTION:
		this->CPC::NotifyInfoToSection();
		return 0;

	case CM_NOTIFY_ITEMINFO_INMCSTORE:
		this->CPC::OnNotifyItemInfoInMCStore(par1);
		return 0;

	case CM_MOVE_STOP:
		this->CPC::OnMoveStop(par1, par2, par3);
		return 0;

	case CM_USE_SKILL:
		this->CPC::OnUseSkill(par1, par2, par3, 0);
		m_magicTargetAID = 0;
		m_pcBattle.CPCBattle::OnDoubleCasting(par1, par2, par3, 0);
		return 0;

	case CM_USE_GROUNDSKILL:
		this->CPC::OnUseGroundSkill(par1, par2, par3, 0);
		return 0;

	case CM_ADD_ITEM:
		this->CPC::OnAddItem(par1, par2, par3, 0, 0);
		return 0;

	case CM_ADD_RESERVED_EMPELIUM_ITEM:
		this->CPC::OnAddReservedEmpeliumItem();
		return 0;

	case CM_DLG_WRITE:
		this->CPC::OnDlgWrite(par1);
		return 0;

	case CM_DLG_WRITE_STR:
		this->CPC::OnDlgWriteStr(par1);
		return 0;

	case CM_NUDE:
		m_pcitemInventoryMgr.CPCItemInventoryMgr::TakeOffAllEquip();
		this->CPC::CheckWeaponState();
		return 0;

	case CM_HEAL_BYPERCENT:
		this->CPC::OnHealByPercent(par1, par2);
		return 0;

	case CM_NZ_COMPASS:
		this->CPC::OnCompass(par1, par2, par3);
		return 0;

	case CM_SHOW_IMAGE:
		this->CPC::OnShowImage(par1, par2);
		return 0;

	case CM_CHANGEPALETTE:
		this->CPC::OnChangePalette(par1, par2);
		return 0;

	case CM_RESURRECTION:
		this->CPC::OnResurrection(par1, par2);
		return 0;

	case CM_PUSH_SKILLOBJECT:
	{
		int distance = (int)par1;

		int xPos, yPos;
		sender->GetParameterValue(VAR_CURXPOS, xPos);
		sender->GetParameterValue(VAR_CURYPOS, yPos);

		PosInfo destPos;
		destPos.x = xPos;
		destPos.y = yPos;

		PosInfo srcPos;
		srcPos.x = m_pathInfo.m_moveInfo.xPos;
		srcPos.y = m_pathInfo.m_moveInfo.yPos;

		PosInfo newPos;
		this->CCharacter::GetPushedPosition(srcPos, destPos, distance, newPos);
		g_characterMgr->CCharacterMgr::SendMsg(this, sender, CM_KNOCKBACK, newPos.x, newPos.y, 1, 0);

		return 0;
	}

	case CM_SETEFFECTIVE:
		this->SetEffective(par1, par2, par3, 0, 0, 0);
		return 0;

	case CM_RESETEFFECTIVE:
		this->ResetEffective(par1, 0);
		return 0;

	case CM_SETINVINCIBLE:
		this->CPC::SetInvincibleTimeInfo(par1, par2);
		return 0;

	case CM_NOTIFY_MANNER_POINT_GIVEN:
		this->CPC::OnNotifyMannerPointGiven(sender, par1, par2);
		return 0;

	case CM_SKILL_ITEMIDENTIFY:
		this->CPC::OnItemIdentifySkill(par1, par2, par3);
		return 0;

	case CM_SKILL_ADDIMITATION:
		m_pcSkill.CPCSkill::AddSkillImitation(par1, par2);
		return 0;

	case CM_SUCCESSOFITEMREF:
		this->CPC::OnSuccessOfItemRef(par1);
		return 0;

	case CM_FAILUREOFITEMREF:
		this->CPC::OnFailureOfItemRef(par1);
		return 0;

	case CM_ENABLEITEMMOVE:
		this->CPC::OnEnableItemMove(0);
		return 0;

	case CM_DISABLEITEMMOVE:
		this->CPC::OnDisableItemMove();
		return 0;

	case CM_SET_EFFFECTSTATE:
	case CM_SET_EFFECTSTATE:
		this->SetEffectState(par1);
		return 0;

	case CM_RESET_EFFECTSTATE:
		this->ResetEffectState(par1);
		return 0;

	case CM_TIME_BODYSTATE:
		this->CPC::SetBodyStateTimeInfo(par1, par2, par3);
		return 0;

	case CM_TIME_HEALTHSTATE:
		this->CPC::SetHealthStateTimeInfo(par1, par2, par3);
		return 0;

	case CM_SKILL_BANUMSPLASHER:
	{
		unsigned long targetID = (unsigned long)par1;
		int skillLV = (int)par2;

		CCharacter* ch = g_characterMgr->CCharacterMgr::FastFindCharacter(targetID);
		if( ch == NULL )
			return 0;

		int state;
		ch->GetParameterValue(VAR_STATE, state);
		if( state == CHARACTER_STATE_DEAD )
			return 0;

		int xPos, yPos;
		ch->GetParameterValue(VAR_CURXPOS, xPos);
		ch->GetParameterValue(VAR_CURYPOS, yPos);

		int rate = 500 + 50 * skillLV + 20 * m_pcSkill.CPCSkill::GetSkillLevel(SKID_AS_POISONREACT, 0);
		int count = max(1, this->CCharacter::GetCountInArea(xPos, yPos, 1, 0, 0, 1));
		int div = rate / count;

		int data[3];
		data[0] = SKID_AS_SPLASHER;
		data[1] = skillLV;
		data[2] = targetID;

		this->SplashAttack(div, xPos, yPos, 0, 2, 2, m_characterInfo.accountID, data, div, 1);
		return 0;
	}

	case CM_MODIFY_SKILLCOUNT:
	{
		int SKID = (int)par1;

		switch( SKID )
		{
		case SKID_MG_FIREWALL:
			m_pcSkill.CPCSkill::SetFireWallCount(par2, par3);
		break;
		case SKID_AL_WARP:
			--m_pcSkill.m_warpCount;
		break;
		case SKID_WZ_QUAGMIRE:
			if( par2 )
				break;
			m_pcSkill.CPCSkill::SetLimitedSkill(SKID, -1);
		break;
		case SKID_WZ_FIREPILLAR:
			m_pcSkill.CPCSkill::SetLimitedSkill(SKID, -1);
		break;
		case SKID_RG_GRAFFITI:
			if( *(int*)(sender + 0x160) != 0 ) //TODO: identify correct class
				break;
			m_pcSkill.m_graffitiAID = 0;
		break;
		case SKID_WE_CALLPARTNER:
			m_pcSkill.CPCSkill::SetLimitedSkill(SKID, -1);
		break;
		case SKID_PF_FOGWALL:
			if( par2 )
				break;
			m_pcSkill.CPCSkill::SetLimitedSkill(SKID, -1);
		break;
		case SKID_PF_SPIDERWEB:
		case SKID_WE_CALLPARENT:
		case SKID_WE_CALLBABY:
			m_pcSkill.CPCSkill::SetLimitedSkill(SKID, -1);
		break;
		case SKID_BD_LULLABY:
		case SKID_BD_RICHMANKIM:
		case SKID_BD_ETERNALCHAOS:
		case SKID_BD_DRUMBATTLEFIELD:
		case SKID_BD_RINGNIBELUNGEN:
		case SKID_BD_ROKISWEIL:
		case SKID_BD_INTOABYSS:
		case SKID_BD_SIEGFRIED:
		case SKID_BA_DISSONANCE:
		case SKID_BA_WHISTLE:
		case SKID_BA_ASSASSINCROSS:
		case SKID_BA_POEMBRAGI:
		case SKID_BA_APPLEIDUN:
		case SKID_DC_UGLYDANCE:
		case SKID_DC_HUMMING:
		case SKID_DC_DONTFORGETME:
		case SKID_DC_FORTUNEKISS:
		case SKID_DC_SERVICEFORYOU:
		case SKID_SG_SUN_WARM:
		case SKID_SG_MOON_WARM:
		case SKID_SG_STAR_WARM:
		case SKID_CG_HERMODE:
		case SKID_DE_AURA:
		case SKID_NC_NEUTRALBARRIER:
		case SKID_NC_STEALTHFIELD:
			m_pcSkill.CPCSkill::DeletePlayingSkill(sender->GetAccountID());
		break;
		default:
		break;
		}

		return 0;
	}

	case CM_NOTIFY_GROUNDSKILL:
		this->CPC::NotifyGroundSkillUsing(par1, par2, *(WORD*)(par3 + 0), *(WORD*)(par3 + 4), timeGetTime());
		return 0;

	case CM_CHANGE_MONEY:
		this->UpdateParameterValue(20, par1);
		return 0;

	case CM_RESET_STAT:
		this->CPC::OnResetStat();
		return 0;

	case CM_RESET_SKILL:
		this->CPC::OnResetSkill();
		return 0;

	case CM_PVP_PLUS_POINT:
		this->CPC::OnPVPPlusPoint(par1);
		return 0;

	case CM_RANKINGINFO:
		Trace("Ranking:%d/%d\n", par1, par2);
		this->CPC::OnNotifyRankingInfo(par1, par2);
		return 0;

	case CM_PET_DIE:
	{
		IVItItem* item = m_pcitemInventoryMgr.CPCItemInventoryMgr::SearchPet(par1);
		unsigned long ITID = ( item != NULL ) ? item->m_ID : 0;

		if( item != NULL )
			if( this->CPC::ConsumeItem(0, 1, item) )
				m_myPetID = 0;

		m_isPetOwner = 0;
		g_specialItmMgr->CSpecialItemMgr::SendMsg(ITID, 4, this->GetAccountID());
		return 0;
	}

	case CM_HOMUN_DIE:
		m_pcBattle.m_myHomunID = 0;
		m_pcBattle.CPCBattle::SetHomunDBInfo(NULL);
		return 0;

	case CM_MERCE_DELETE:
		if( par1 == m_pcBattle.m_mercenaryID )
			m_pcBattle.CPCBattle::Mercenary_Delete(par2);
		return 0;

	case CM_EMOTION:
		this->CPC::OnEmotion(par1);
		return 0;

	case CM_NPCEVENTADDSKILL:
		m_pcSkill.CPCSkill::AddSkillFromNPCEvent(par1, par2, 0);
		m_pcSkill.CPCSkill::NotifyAllSkillInfo();
		return 0;

	case CM_NPCEVENTDELETESKILL:
		m_pcSkill.CPCSkill::DeleteSkill(par1, 0);
		m_pcSkill.CPCSkill::SaveSkill();
		m_pcSkill.CPCSkill::NotifyAllSkillInfo();
		return 0;

	case CM_SHOWDIGIT:
	{
		PACKET_ZC_SHOWDIGIT packet;
		packet.PacketType = HEADER_ZC_SHOWDIGIT;
		packet.type = 0;
		packet.value = par1;

		this->CPC::Send(sizeof(packet), (char*)&packet);
		return 0;
	}

	case CM_CLEAR_EVENT:
		m_eventNo = 0;
		return 0;

	case CM_AUTHORIZE_ITEM:
	{
		CItem* item = (CItem*)par1;
		DWORD time = (DWORD)par2;

		item->CItem::AddPickupablePC(m_characterInfo.accountID, time);

		if( m_characterInfo.PartyItemPickupRule )
		{
			for( mystd::list<unsigned long>::iterator it = m_groupMember.begin(); it != m_groupMember.end(); ++it )
			{
				CCharacter* ch = g_characterMgr->CCharacterMgr::FindCharacter(*it, PC_TYPE);
				if( ch == NULL )
					continue;

				if( ch->GetAccountID() == m_characterInfo.accountID )
					continue;

				int mapID;
				ch->GetParameterValue(VAR_MAPID, mapID);
				if( m_characterInfo.mapID != mapID )
					continue;

				item->CItem::AddPickupablePC(ch->GetAccountID(), time);
			}
		}

		return 0;
	}

	case CM_ATTSKILL_TOCHAR22_1:
		if( m_mapRes != NULL )
			this->CPC::AttSkillToChar22_1(par1, par2, par3);
		else
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCMsg.cpp", 1921, "MapRes == NULL, %s, SKILL(%d)", m_characterInfo.characterName, par1);
		return 0;

	case CM_SPATTSKILL_TOCHAR22_1:
	{
		int index = (int)par1;
		int SKID = (int)par2;
		bool isPlaySolo = (bool)(par3 != 0);

		if( m_mapRes != NULL )
			this->CCharacter::ProcessGroundEffective(index, SKID, isPlaySolo);
		else
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCMsg.cpp", 1930, "MapRes == NULL, %s, SKILL(%d)", m_characterInfo.characterName, par1);
	}
		return 0;

	case CM_OPERSKILL_TOCHAR22_1:
		if( m_mapRes != NULL )
			this->CPC::OperSkillToChar22_1(par1, par2, par3);
		else
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCMsg.cpp", 1939, "MapRes == NULL, %s, SKILL(%d)", m_characterInfo.characterName, par1);
		return 0;

	case CM_OPERSKILL_TOSELF22_1:
		if( m_mapRes != NULL )
			this->CPC::OperSkillToSelf22_1(par1, par2, par3);
		else
			g_errorLogs->CErrorLog::CriticalErrorLogFmt(".\\PCMsg.cpp", 1948, "MapRes == NULL, %s, SKILL(%d)", m_characterInfo.characterName, par1);
		return 0;

	case CM_SKILL_GROUNDTYPE22_1:
		this->CPC::OnGroundSkill22_1(par1, par2, par3);
		return 0;

	case CM_ATTSKILL_TOCHAR22_2:
		this->CPC::AttSkillToChar22_2(par1, par2, par3);
		return 0;

	case CM_SPATTSKILL_TOCHAR22_2:
		this->CPC::SPAttSkillToChar22_2(par1, par2, par3);
		return 0;

	case CM_OPERSKILL_TOCHAR22_2:
		this->CPC::OperSkillToChar22_2(par1, par2, par3, par4);
		return 0;

	case CM_OPERSKILL_TOSELF22_2:
		this->CPC::OperSkillToSelf22_2(par1, par2, par3);
		return 0;

	case CM_SKILL_GROUNDTYPE22_2:
		this->CPC::OnGroundSkill22_2(par1, par2, par3);
		return 0;

	case CM_AUTOSPELLLIST:
		this->CPC::OnAutoSpellList(par1, par2, par3);
		return 0;

	case CM_PLAYSKILL_CANCEL:
		m_pcSkill.CPCSkill::DestroyPlayingSkill();
		return 0;

	case CM_DAMAGE_WEAPON:
		this->CPC::OnDamagedWeapon();
		return 0;

	case CM_DAMAGE_ARMOR:
		this->CPC::OnDamagedArmor();
		return 0;

	case CM_PROCESSEFFECT_ATTACK:
		m_pcBattle.CPCBattle::ProcessEffect_ATK(sender, par1, par2, par3);
		return 0;

	case CM_PROCESSEFFECT_KILL:
		m_pcBattle.CPCBattle::ProcessEffectOnKill((CCharacter *)par1, par2, par3);
		return 0;

	case CM_GETMARRIED:
		this->CPC::OnMakeCouple(par1);
		return 0;

	case CM_CREATE_ITEMOFMYGID:
		m_pcitemInventoryMgr.CPCItemInventoryMgr::CreateItemOfMyGID(par1, par2, 0);
		return 0;

	case CM_CREATE_ITEMOFOTHERGID:
		m_pcitemInventoryMgr.CPCItemInventoryMgr::CreateItemOfMyGID(par1, par2, par3);
		return 0;

	case CM_REMOVE_ITEMOFMYGID:
		m_pcitemInventoryMgr.CPCItemInventoryMgr::RemoveItemOfMyGID(par1, par2);
		return 0;

	case CM_DAMAGE_EQUIPMENT:
		this->CPC::OnDamageEquipment(par1);
		return 0;

	case CM_CHANGE_HAIRSTYLE:
		this->CPC::OnChangePalette(2, par1);
		return 0;

	case CM_CHANGE_STATUSPARM:
		this->OnChangeStatusAmount(par1, *(WORD *)par2, *(DWORD *)(par2 + 8), *(DWORD *)(par2 + 4));
		return 0;

	case CM_EXT_SETEFFECTIVE:
		this->SetEffective(par1, par2, *(DWORD *)(par3 + 0), *(DWORD *)(par3 + 4), *(DWORD *)(par3 + 8), *(DWORD *)(par3 + 12));
		return 0;

	case CM_MODIFYDAMAGE_ATTACKED:
	{
		int& damage = *(int*)((char*)par1 + 0);
		int& isRNGATK = *(int*)((char*)par1 + 4);
		int& type = *(int*)((char*)par1 + 8);
		int& property = *(int*)((char*)par1 + 12);
		int SKID = (int)par2;

		m_pcBattle.CPCBattle::ModifyDamage_ATKED(sender, damage, isRNGATK, type, property, SKID, 0);
		return damage;
	}

	case CM_SET_ATKPERCENT:
		m_pcBattle.CPCBattle::SetATKPercentInfo(par1, par2, par3);
		return 0;

	case CM_SET_DEFPERCENT:
		m_pcBattle.CPCBattle::SetDEFPercentInfo(par1, par2, par3);
		return 0;

	case CM_GET_SKILLLEVEL:
		return m_pcSkill.CPCSkill::GetSkillLevel(par1, par2);

	case CM_REFLECT_MAGIC:
		return m_pcBattle.CPCBattle::ReflectMagic(sender, (SKILLATTACK_MSG *)par1, par2);

	case CM_SEND_DAMAGEPACKET:
	{
		int& size = (int)par1;
		PACKET& buf = *(PACKET*)par2;

		if( this->IsItPossible(MAPPROPERTY_HIDING_DAMAGE) == 1 )
		{
			switch( buf.PacketType )
			{
			case HEADER_ZC_NOTIFY_ACT:
			{
				PACKET_ZC_NOTIFY_ACT dst;			
				memcpy(&dst, &buf, size);

				if( dst.damage != 0 )
					dst.damage = -29999;

				this->CPC::Send(size, (char*)&dst);
				this->CCharacter::MultiCast((char*)&dst, size);
				return 0;
			}
			break;
			case HEADER_ZC_NOTIFY_ACT2:
			{
				PACKET_ZC_NOTIFY_ACT2 dst;
				memcpy(&dst, &buf, size);

				if( dst.damage != 0 )
					dst.damage = -29999;

				this->CPC::Send(size, (char*)&dst);
				this->CCharacter::MultiCast((char*)&dst, size);
				return 0;
			}
			break;
			case HEADER_ZC_NOTIFY_SKILL2:
			{
				PACKET_ZC_NOTIFY_SKILL2 dst;
				memcpy(&dst, &buf, size);

				if( dst.damage != 0 )
					dst.damage = -29999;

				this->CPC::Send(size, (char*)&dst);
				this->CCharacter::MultiCast((char*)&dst, size);
				return 0;
			}
			break;
			}
		}

		this->CPC::Send(size, (char*)&buf);
		this->CCharacter::MultiCast((char*)&buf, size);
		return 0;
	}

	case CM_DELETE_FROM_GROUPLIST:
	case CM_NPCEVENT_RELOADMOBILEEVENT_EXCULUSIVE:
	case CM_SKILL_ADDIMITATION3rd:
		return 0;

	case CM_MOVED_SPITEM:
		if( par1 == 2 )
			m_pcItem.CPCItem::OnEquipedSpecialITM(par2);
		else
		if( par1 == 4 )
			m_pcItem.CPCItem::OnTakeOffSpecialITM(par2);
		return 0;

	case CM_GET_ENEMYAID:
		return m_pcBattle.m_enemyAID;

	case CM_GET_CHARACTERID:
		return this->CPC::GetCharacterID();

	case CM_GET_GRID_IFEXPSHARE:
		return this->CPC::GetGroupIDIFexpShare();

	case CM_MERCE_SETDBINFO:
		m_pcBattle.CPCBattle::SetHomunDBInfo((HOMUN_DBINFO*)par1);
		return 0;

	case CM_OPENAUCTION:
		this->CPC::AuctionOpen();
		return 0;

	case CM_OPENMAILING:
		this->CPC::MailOpen();
		return 0;

	case CM_CONSUMESPECIALITEM:
		this->CPC::OnConSumeSpecialItem(par1);
		return 0;

	case CM_HUNTINGLIST:
		this->CPC::OnHuntingList(par1);
		return 0;

	case CM_NOTIFY_BOSSINFO:
		this->CPC::OnNotifyBossInfo((char*)par1);
		return 0;

	case CM_SET_SCRIPT_EVENT_NO:
		m_itemScriptEventNo = par1;
		return 0;

	case CM_OPEN_EDITDLGSTR:
		this->CPC::OnDlgWriteStr(par1);
		return 0;

	case CM_BAN:
		this->AddErrorCount(".\\PCMsg.cpp", 2166, 4, timeGetTime());
		return 0;

	case CM_UPDATE_SKILL_LIMIT_CNT:
		m_pcSkill.CPCSkill::SetLimitedSkill(par1, par2);
		return 0;

	case CM_ADD_SPECIALZONELIST:
		this->CPC::AddSpeicalZoneList(par1);
		return 0;

	case CM_DEL_SPECIALZONELIST:
		this->CPC::DelSpecialZoneList();
		return 0;

	case CM_SET_MDEFPERCENT:
		m_pcBattle.CPCBattle::SetMDEFPercentInfo(par1, par2, par3);
		return 0;

	case CM_RESET_DEFPERCENT:
		m_pcBattle.CPCBattle::ResetDEFPercentInfo(par1);
		return 0;

	case CM_RESET_MDEFPERCENT:
		m_pcBattle.CPCBattle::ResetMDEFPercentInfo(par1);
		return 0;

	case CM_NPCEVENT_RELOADMOBILEEVENT:
		m_mobileEvent.CMobileEvent::ReLoad(this->GetAccountID());
		return 0;

	case CM_KNOCKBACK:
		if( m_pcBattle.m_optionInfo.neverKnockBack > 0 )
			return 0;
		this->CPC::OnMoveStop(par1, par2, par3);
		return 0;

	case CM_QUEST_EVENTITEM:
		m_questEvent.CPCQuestEvent::OnMessage(par1, par2, par3);
		return 0;

	case CM_QUESTMISSION_HUNTINGLIST:
		this->CPC::OnQuestHuntingList(par1);
		return 0;

	case CM_PROGRESSBAR:
		m_pcClientUpdater.CPCClientUpdater::OnProgress(par1, par2);
		return 0;

	case CM_PROGRESSBAR_CANCEL:
		m_pcClientUpdater.CPCClientUpdater::OnPorgressCancel();
		return 0;

	case CM_SET_ITEM_PARTY:
		m_pcitemInventoryMgr.CPCItemInventoryMgr::SetItemPartyInMap(par1, par2, par3);
		return 0;

	case CM_REQ_GROUPINFO_CHANGE_V2:
		this->CPC::ReqGroupInfoChangeV2(par1, par2);
		return 0;

	default:
		return this->CCharacter::OnMsg(sender, receiver, msgID, par1, par2, par3, 0);
	}
}
