#include "GameMode.h"
#include "GameWorld.h"
#include "Item.h"
#include "ItemInfo.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Packet.h"
#include "Pc.h"
#include "Player.h"
#include "RagEffect.h"
#include "Session.h"
#include "Skill.h"
#include "SkillInfo.h"
#include "3dLib/Renderer.h"
#include "Device/Connection.h"
#include "Resource/Wave.h"
#include "Window/UIControl.h"
#include "Window/UINewChatWnd.h"
#include "Window/UIWaitWnd.h"
#include "Window/UIWindowMgr.h"
#include "Window/UISys.h"
#include "Enum.h"
#include "Globals.h"
#include "Struct.h"


hook_func<void (CGameMode::*)(void)> CGameMode::_PollNetworkStatus("CGameMode::PollNetworkStatus");
void CGameMode::PollNetworkStatus(void)
{
	return (this->*_PollNetworkStatus)();

	if( g_serviceType == ServiceKorea )
	{
		static int s_nPrevHoursPlayed;
		int nHoursPlayed = (timeGetTime() - g_session.m_playingTime) / 3600000;
		if( nHoursPlayed > 0 && s_nPrevHoursPlayed != nHoursPlayed )
		{
			m_broadCastTick = timeGetTime();

			if( m_broadcastBalloon == NULL )
			{
				m_broadcastBalloon = new UITransBalloonText();
				m_broadcastBalloon->UIWindow::Create(8, 8);
				g_windowMgr.UIWindowMgr::AddWindowFront(m_broadcastBalloon);
			}

			char msg[100];
			if( nHoursPlayed >= 3 )
				sprintf(msg, "%d 시간이 경과했습니다. 잠시 쉬었다 하시기 바랍니다.", nHoursPlayed); // "%d hours have elapsed. Please take a break."
			else
				sprintf(msg, "%d 시간이 경과했습니다.", nHoursPlayed); // "%d hours have elapsed."

			m_broadcastBalloon->UIBalloonText::SetText(msg, 72);
			m_broadcastBalloon->Move((g_renderer->CRenderer::GetWidth() - 640) / 2 - m_broadcastBalloon->UIWindow::GetWidth() / 2 + 320, 51);
			m_broadcastBalloon->UIBalloonText::SetFntColor(0x62B0FF, 0x000000);

			s_nPrevHoursPlayed = nHoursPlayed;
		}
	}
	else
	if( g_serviceType == ServiceVietnam )
	{
		int nHoursPlayed = (timeGetTime() - g_session.m_playingTime) / 3600000;
		if( nHoursPlayed == 3 || nHoursPlayed == 5 )
		{
			m_broadCastTick = timeGetTime();

			if( m_broadcastBalloon == NULL )
			{
				m_broadcastBalloon = new UITransBalloonText();
				m_broadcastBalloon->UIWindow::Create(8, 8);
				g_windowMgr.UIWindowMgr::AddWindowFront(m_broadcastBalloon);
			}

			char msg[100];
			if( nHoursPlayed == 3 )
				sprintf(msg, "%d %s", nHoursPlayed, MsgStr(MSI_VET_3HOUR));
			else //( nHoursPlayed == 5 )
				sprintf(msg, "%d %s", nHoursPlayed, MsgStr(MSI_VET_5HOUR));

			m_broadcastBalloon->UIBalloonText::SetText(msg, 72);
			m_broadcastBalloon->Move((g_renderer->CRenderer::GetWidth() - 640) / 2 - m_broadcastBalloon->UIWindow::GetWidth() / 2 + 320, 51);
			m_broadcastBalloon->UIBalloonText::SetFntColor(0x62B0FF, 0x000000);
		}
	}

	if( !CRagConnection::instanceR().CConnection::Poll() )
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_SOCKETERROR, 0, 0, 0);

	if( g_mustPumpOutReceiveQueue == TRUE )
	{
		unsigned long aid;
		if( CRagConnection::instanceR().CConnection::Recv((char*)&aid, 4, true) )
			g_mustPumpOutReceiveQueue = FALSE;

		return;
	}

	char buf[20480];
	while( CRagConnection::instanceR().CRagConnection::RecvPacket(buf) )
	{
		short packetType = CRagConnection::instanceR().CRagConnection::GetPacketType(buf);
		switch( packetType )
		{
		case HEADER_ZC_ACCEPT_ENTER                       : this->CGameMode::Zc_Accept_Enter(buf); break;
		case HEADER_ZC_NOTIFY_INITCHAR                    : break; // ignored
		case HEADER_ZC_NOTIFY_UPDATECHAR                  : break; // ignored
		case HEADER_ZC_NOTIFY_UPDATEPLAYER                : break; // ignored
		case HEADER_ZC_NOTIFY_STANDENTRY                  : this->CGameMode::Zc_Notify_Standentry(buf); break;
		case HEADER_ZC_NOTIFY_NEWENTRY                    : this->CGameMode::Zc_Notify_Newentry(buf); break;
		case HEADER_ZC_NOTIFY_ACTENTRY                    : this->CGameMode::Zc_Notify_Actentry(buf); break; // inlined
		case HEADER_ZC_NOTIFY_MOVEENTRY                   : this->CGameMode::Zc_Notify_Moveentry(buf); break;
		case HEADER_ZC_NOTIFY_STANDENTRY_NPC              : this->CGameMode::Zc_Notify_Standentry_Npc(buf); break;
		case HEADER_ZC_NOTIFY_TIME                        : this->CGameMode::Zc_Notify_Time(buf); break;
		case HEADER_ZC_NOTIFY_VANISH                      : this->CGameMode::Zc_Notify_Vanish(buf); break;
		case HEADER_SC_NOTIFY_BAN                         : this->CGameMode::Sc_Notify_Ban(buf); break;
		case HEADER_ZC_ACCEPT_QUIT                        : this->CGameMode::Zc_Accept_Quit(buf); break; // inlined
		case HEADER_ZC_REFUSE_QUIT                        : this->CGameMode::Zc_Refuse_Quit(buf); break; // inlined
		case HEADER_ZC_NOTIFY_MOVE                        : this->CGameMode::Zc_Notify_Move(buf); break; // inlined
		case HEADER_ZC_NOTIFY_PLAYERMOVE                  : this->CGameMode::Zc_Notify_Playermove(buf); break; // inlined
		case HEADER_ZC_STOPMOVE                           : this->CGameMode::Zc_Stopmove(buf); break;
		case HEADER_ZC_NOTIFY_ACT                         :
		{
			PACKET_ZC_NOTIFY_ACT& packet = *reinterpret_cast<PACKET_ZC_NOTIFY_ACT*>(buf);
			this->CGameMode::Zc_Notify_Act(packet.GID, packet.targetGID, packet.startTime, packet.attackMT, packet.attackedMT, packet.damage, packet.count, packet.action, packet.leftDamage);
		}
		break;
		case HEADER_ZC_NOTIFY_ACT_POSITION                : this->CGameMode::Zc_Notify_Act_Position(buf); break;
		case HEADER_ZC_NOTIFY_CHAT                        : this->CGameMode::Zc_Notify_Chat(buf); break;
		case HEADER_ZC_NOTIFY_PLAYERCHAT                  : this->CGameMode::Zc_Notify_Playerchat(buf); break;
		case HEADER_ZC_NPCACK_MAPMOVE                     : this->CGameMode::Zc_Npcack_Mapmove(buf); break;
		case HEADER_ZC_NPCACK_SERVERMOVE                  : this->CGameMode::Zc_Npcack_Servermove(buf); break;
		case HEADER_ZC_NPCACK_ENABLE                      : this->CGameMode::Zc_Npcack_Enable(buf); break;
		case HEADER_ZC_ACK_REQNAME                        : this->CGameMode::Zc_Ack_Reqname(buf); break;
		case HEADER_ZC_WHISPER                            : this->CGameMode::Zc_Whisper(buf); break;
		case HEADER_ZC_ACK_WHISPER                        : this->CGameMode::Zc_Ack_Whisper(buf); break;
		case HEADER_ZC_BROADCAST                          : this->CGameMode::Zc_Broadcast(buf); break;
		case HEADER_ZC_CHANGE_DIRECTION                   : this->CGameMode::Zc_Change_Direction(buf); break;
		case HEADER_ZC_ITEM_ENTRY                         : this->CGameMode::Zc_Item_Entry(buf); break;
		case HEADER_ZC_ITEM_FALL_ENTRY                    : this->CGameMode::Zc_Item_Fall_Entry(buf); break;
		case HEADER_ZC_ITEM_PICKUP_ACK                    : this->CGameMode::Zc_Item_Pickup_Ack(buf); break;
		case HEADER_ZC_ITEM_DISAPPEAR                     : this->CGameMode::Zc_Item_Disappear(buf); break;
		case HEADER_ZC_NORMAL_ITEMLIST                    : this->CGameMode::Zc_Normal_Itemlist(buf); break;
		case HEADER_ZC_EQUIPMENT_ITEMLIST                 : this->CGameMode::Zc_Equipment_Itemlist(buf); break;
		case HEADER_ZC_STORE_NORMAL_ITEMLIST              : this->CGameMode::Zc_Store_Normal_Itemlist(buf); break;
		case HEADER_ZC_STORE_EQUIPMENT_ITEMLIST           : this->CGameMode::Zc_Store_Equipment_Itemlist(buf); break;
		case HEADER_ZC_USE_ITEM_ACK                       : this->CGameMode::Zc_Use_Item_Ack(buf); break;
		case HEADER_ZC_REQ_WEAR_EQUIP_ACK                 : this->CGameMode::Zc_Req_Wear_Equip_Ack(buf); break;
		case HEADER_ZC_REQ_TAKEOFF_EQUIP_ACK              : this->CGameMode::Zc_Req_Takeoff_Equip_Ack(buf); break;
		case HEADER_ZC_ITEM_THROW_ACK                     : this->CGameMode::Zc_Item_Throw_Ack(buf); break;
		case HEADER_ZC_PAR_CHANGE                         : this->CGameMode::Zc_Par_Change(buf); break;
		case HEADER_ZC_LONGPAR_CHANGE                     : this->CGameMode::Zc_Longpar_Change(buf); break;
		case HEADER_ZC_RESTART_ACK                        : this->CGameMode::Zc_Restart_Ack(buf); break;
		case HEADER_ZC_SAY_DIALOG                         : this->CGameMode::Zc_Say_Dialog(buf); break;
		case HEADER_ZC_WAIT_DIALOG                        : this->CGameMode::Zc_Wait_Dialog(buf); break;
		case HEADER_ZC_CLOSE_DIALOG                       : this->CGameMode::Zc_Close_Dialog(buf); break;
		case HEADER_ZC_MENU_LIST                          : this->CGameMode::Zc_Menu_List(buf); break;
		case HEADER_ZC_STATUS_CHANGE_ACK                  : this->CGameMode::Zc_Status_Change_Ack(buf); break;
		case HEADER_ZC_STATUS                             : this->CGameMode::Zc_Status(buf); break;
		case HEADER_ZC_STATUS_CHANGE                      : this->CGameMode::Zc_Status_Change(buf); break;
		case HEADER_ZC_EMOTION                            : this->CGameMode::Zc_Emotion(buf); break;
		case HEADER_ZC_USER_COUNT                         : this->CGameMode::Zc_User_Count(buf); break;
		case HEADER_ZC_SPRITE_CHANGE                      : this->CGameMode::Zc_Sprite_Change(buf); break;
		case HEADER_ZC_SELECT_DEALTYPE                    : this->CGameMode::Zc_Select_Dealtype(buf); break;
		case HEADER_ZC_PC_PURCHASE_ITEMLIST               : this->CGameMode::Zc_Pc_Purchase_Itemlist(buf); break;
		case HEADER_ZC_PC_SELL_ITEMLIST                   : this->CGameMode::Zc_Pc_Sell_Itemlist(buf); break;
		case HEADER_ZC_PC_PURCHASE_RESULT                 : this->CGameMode::Zc_Pc_Purchase_Result(buf); break;
		case HEADER_ZC_PC_SELL_RESULT                     : this->CGameMode::Zc_Pc_Sell_Result(buf); break;
		case HEADER_ZC_ACK_DISCONNECT_CHARACTER           : this->CGameMode::Zc_Ack_Disconnect_Character(buf); break;
		case HEADER_ZC_SETTING_WHISPER_PC                 : this->CGameMode::Zc_Setting_Whisper_Pc(buf); break;
		case HEADER_ZC_SETTING_WHISPER_STATE              : this->CGameMode::Zc_Setting_Whisper_State(buf); break;
		case HEADER_ZC_WHISPER_LIST                       : this->CGameMode::Zc_Whisper_List(buf); break;
		case HEADER_ZC_ACK_CREATE_CHATROOM                : this->CGameMode::Zc_Ack_Create_Chatroom(buf); break;
		case HEADER_ZC_ROOM_NEWENTRY                      : this->CGameMode::Zc_Room_Newentry(buf); break;
		case HEADER_ZC_DESTROY_ROOM                       : this->CGameMode::Zc_Destroy_Room(buf); break;
		case HEADER_ZC_REFUSE_ENTER_ROOM                  : this->CGameMode::Zc_Refuse_Enter_Room(buf); break;
		case HEADER_ZC_ENTER_ROOM                         : this->CGameMode::Zc_Enter_Room(buf); break;
		case HEADER_ZC_MEMBER_NEWENTRY                    : this->CGameMode::Zc_Member_Newentry(buf); break;
		case HEADER_ZC_MEMBER_EXIT                        : this->CGameMode::Zc_Member_Exit(buf); break;
		case HEADER_ZC_CHANGE_CHATROOM                    : this->CGameMode::Zc_Change_Chatroom(buf); break;
		case HEADER_ZC_ROLE_CHANGE                        : this->CGameMode::Zc_Role_Change(buf); break;
		case HEADER_ZC_REQ_EXCHANGE_ITEM                  : this->CGameMode::Zc_Req_Exchange_Item(buf); break;
		case HEADER_ZC_ACK_EXCHANGE_ITEM                  : this->CGameMode::Zc_Ack_Exchange_Item(buf); break;
		case HEADER_ZC_ACK_ADD_EXCHANGE_ITEM              : this->CGameMode::Zc_Ack_Add_Exchange_Item(buf); break;
		case HEADER_ZC_CONCLUDE_EXCHANGE_ITEM             : this->CGameMode::Zc_Conclude_Exchange_Item(buf); break;
		case HEADER_ZC_CANCEL_EXCHANGE_ITEM               : this->CGameMode::Zc_Cancel_Exchange_Item(buf); break;
		case HEADER_ZC_EXEC_EXCHANGE_ITEM                 : this->CGameMode::Zc_Exec_Exchange_Item(buf); break;
		case HEADER_ZC_EXCHANGEITEM_UNDO                  : this->CGameMode::Zc_Exchangeitem_Undo(buf); break;
		case HEADER_ZC_NOTIFY_STOREITEM_COUNTINFO         : this->CGameMode::Zc_Notify_Storeitem_Countinfo(buf); break;
//		case HEADER_ZC_ADD_ITEM_TO_STORE                  : this->CGameMode::Zc_Add_Item_To_Store(buf); break; // unsupported
		case HEADER_ZC_DELETE_ITEM_FROM_STORE             : this->CGameMode::Zc_Delete_Item_From_Store(buf); break;
		case HEADER_ZC_CLOSE_STORE                        : this->CGameMode::Zc_Close_Store(buf); break;
		case HEADER_ZC_ACK_MAKE_GROUP                     : this->CGameMode::Zc_Ack_Make_Group(buf); break;
		case HEADER_ZC_GROUP_LIST                         : this->CGameMode::Zc_Group_List(buf); break;
		case HEADER_ZC_ACK_REQ_JOIN_GROUP                 : this->CGameMode::Zc_Ack_Req_Join_Group(buf); break;
		case HEADER_ZC_REQ_JOIN_GROUP                     : this->CGameMode::Zc_Req_Join_Group(buf); break;
		case HEADER_ZC_GROUPINFO_CHANGE                   : this->CGameMode::Zc_groupinfo_change(buf); break;
		case HEADER_ZC_ADD_MEMBER_TO_GROUP                : this->CGameMode::Zc_Add_Member_To_Group(buf); break;
		case HEADER_ZC_DELETE_MEMBER_FROM_GROUP           : this->CGameMode::Zc_Delete_Member_From_Group(buf); break;
		case HEADER_ZC_NOTIFY_HP_TO_GROUPM                : this->CGameMode::Zc_Notify_Hp_To_Groupm(buf); break;
		case HEADER_ZC_NOTIFY_POSITION_TO_GROUPM          : this->CGameMode::Zc_Notify_Position_To_Groupm(buf); break;
		case HEADER_ZC_NOTIFY_CHAT_PARTY                  : this->CGameMode::Zc_Notify_Chat_Party(buf); break;
		case HEADER_ZC_MVP_GETTING_ITEM                   : this->CGameMode::Zc_Mvp_Getting_Item(buf); break;
		case HEADER_ZC_MVP_GETTING_SPECIAL_EXP            : this->CGameMode::Zc_Mvp_Getting_Special_Exp(buf); break;
		case HEADER_ZC_MVP                                : this->CGameMode::Zc_Mvp(buf); break;
		case HEADER_ZC_THROW_MVPITEM                      : this->CGameMode::Zc_Throw_Mvpitem(buf); break;
		case HEADER_ZC_SKILLINFO_UPDATE                   : this->CGameMode::Zc_Skillinfo_Update(buf); break;
		case HEADER_ZC_SKILLINFO_LIST                     : this->CGameMode::Zc_Skillinfo_List(buf); break;
		case HEADER_ZC_ACK_TOUSESKILL                     : this->CGameMode::Zc_Ack_Touseskill(buf); break;
		case HEADER_ZC_ADD_SKILL                          : this->CGameMode::Zc_Add_Skill(buf); break;
		case HEADER_ZC_NOTIFY_SKILL                       : this->CGameMode::Zc_Notify_Skill(buf); break;
		case HEADER_ZC_NOTIFY_SKILL_POSITION              : this->CGameMode::Zc_Notify_Skill_Position(buf); break;
		case HEADER_ZC_NOTIFY_GROUNDSKILL                 : this->CGameMode::Zc_Notify_Groundskill(buf); break;
		case HEADER_ZC_STATE_CHANGE                       : this->CGameMode::Zc_State_Change(buf); break;
		case HEADER_ZC_USE_SKILL                          : this->CGameMode::Zc_Use_Skill(buf); break;
		case HEADER_ZC_WARPLIST                           : this->CGameMode::Zc_Warplist(buf); break;
		case HEADER_ZC_ACK_REMEMBER_WARPPOINT             : this->CGameMode::Zc_Ack_Remember_Warppoint(buf); break;
		case HEADER_ZC_SKILL_ENTRY                        : this->CGameMode::Zc_Skill_Entry(buf); break;
		case HEADER_ZC_SKILL_DISAPPEAR                    : this->CGameMode::Zc_Skill_Disappear(buf); break;
		case HEADER_ZC_NOTIFY_CARTITEM_COUNTINFO          : this->CGameMode::Zc_Notify_Cartitem_Countinfo(buf); break;
		case HEADER_ZC_CART_EQUIPMENT_ITEMLIST            : this->CGameMode::Zc_Cart_Equipment_Itemlist(buf); break;
		case HEADER_ZC_CART_NORMAL_ITEMLIST               : this->CGameMode::Zc_Cart_Normal_Itemlist(buf); break;
		case HEADER_ZC_ADD_ITEM_TO_CART                   : this->CGameMode::Zc_Add_Item_To_Cart(buf); break;
		case HEADER_ZC_DELETE_ITEM_FROM_CART              : this->CGameMode::Zc_Delete_Item_From_Cart(buf); break;
		case HEADER_ZC_CARTOFF                            : this->CGameMode::Zc_Cartoff(buf); break;
		case HEADER_ZC_ACK_ADDITEM_TO_CART                : this->CGameMode::Zc_Ack_Additem_To_Cart(buf); break;
		case HEADER_ZC_OPENSTORE                          : this->CGameMode::Zc_openstore(buf); break;
		case HEADER_ZC_STORE_ENTRY                        : this->CGameMode::Zc_store_entry(buf); break;
		case HEADER_ZC_DISAPPEAR_ENTRY                    : this->CGameMode::Zc_disappear_entry(buf); break;
		case HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC        : this->CGameMode::Zc_pc_purchase_itemlist_frommc(buf); break;
		case HEADER_ZC_PC_PURCHASE_RESULT_FROMMC          : this->CGameMode::Zc_pc_purchase_result_frommc(buf); break;
		case HEADER_ZC_PC_PURCHASE_MYITEMLIST             : this->CGameMode::Zc_pc_purchase_myitemlist(buf); break;
		case HEADER_ZC_DELETEITEM_FROM_MCSTORE            : this->CGameMode::Zc_deleteitem_from_mcstore(buf); break;
		case HEADER_ZC_ATTACK_FAILURE_FOR_DISTANCE        : this->CGameMode::Zc_attack_failure_for_distance(buf); break;
		case HEADER_ZC_ATTACK_RANGE                       : this->CGameMode::Zc_attack_range(buf); break;
		case HEADER_ZC_ACTION_FAILURE                     : this->CGameMode::Zc_action_failure(buf); break;
		case HEADER_ZC_EQUIP_ARROW                        : this->CGameMode::Zc_equip_arrow(buf); break;
		case HEADER_ZC_RECOVERY                           : this->CGameMode::Zc_recovery(buf); break;
		case HEADER_ZC_USESKILL_ACK                       : this->CGameMode::Zc_useskill_ack(buf, FALSE); break;
		case HEADER_ZC_COUPLESTATUS                       : this->CGameMode::Zc_couplestatus(buf); break;
		case HEADER_ZC_OPEN_EDITDLG                       : this->CGameMode::Zc_open_editdlg(buf); break;
		case HEADER_ZC_COMPASS                            : this->CGameMode::Zc_compass(buf); break;
		case HEADER_ZC_SHOW_IMAGE                         : this->CGameMode::Zc_show_image(buf); break;
		case HEADER_ZC_AUTORUN_SKILL                      : this->CGameMode::Zc_autorun_skill(buf); break;
		case HEADER_ZC_RESURRECTION                       : this->CGameMode::Zc_resurrection(buf); break;
		case HEADER_ZC_ACK_GIVE_MANNER_POINT              : this->CGameMode::Zc_ack_give_manner_point(buf); break;
		case HEADER_ZC_NOTIFY_MANNER_POINT_GIVEN          : this->CGameMode::Zc_notify_manner_point_given(buf); break;
		case HEADER_ZC_MYGUILD_BASIC_INFO                 : this->CGameMode::Zc_myguild_basic_info(buf); break;
		case HEADER_ZC_ACK_GUILD_MENUINTERFACE            : this->CGameMode::Zc_ack_guild_menuinterface(buf); break;
		case HEADER_ZC_GUILD_INFO                         : this->CGameMode::Zc_guild_info(buf); break;
		case HEADER_ZC_GUILD_EMBLEM_IMG                   : this->CGameMode::Zc_guild_emblem_img(buf); break;
		case HEADER_ZC_MEMBERMGR_INFO                     : this->CGameMode::Zc_membermgr_info(buf); break;
		case HEADER_ZC_ACK_REQ_CHANGE_MEMBERS             : this->CGameMode::Zc_ack_req_change_members(buf); break;
		case HEADER_ZC_ACK_OPEN_MEMBER_INFO               : this->CGameMode::Zc_ack_open_member_info(buf); break;
		case HEADER_ZC_ACK_LEAVE_GUILD                    : this->CGameMode::Zc_ack_leave_guild(buf); break;
		case HEADER_ZC_ACK_BAN_GUILD                      : this->CGameMode::Zc_ack_ban_guild(buf); break;
		case HEADER_ZC_ACK_DISORGANIZE_GUILD_RESULT       : this->CGameMode::Zc_ack_disorganize_guild_result(buf); break;
		case HEADER_ZC_ACK_DISORGANIZE_GUILD              : this->CGameMode::Zc_ack_disorganize_guild(buf); break;
		case HEADER_ZC_POSITION_INFO                      : this->CGameMode::Zc_position_info(buf); break;
		case HEADER_ZC_GUILD_SKILLINFO                    : this->CGameMode::Zc_GuildSkillInfo(buf); break;
		case HEADER_ZC_BAN_LIST                           : this->CGameMode::Zc_ban_list(buf); break;
		case HEADER_ZC_OTHER_GUILD_LIST                   : this->CGameMode::Zc_other_guild_list(buf); break;
		case HEADER_ZC_POSITION_ID_NAME_INFO              : this->CGameMode::Zc_position_id_name_info(buf); break;
		case HEADER_ZC_RESULT_MAKE_GUILD                  : this->CGameMode::Zc_result_make_guild(buf); break;
		case HEADER_ZC_ACK_REQ_JOIN_GUILD                 : this->CGameMode::Zc_ack_req_join_guild(buf); break;
		case HEADER_ZC_REQ_JOIN_GUILD                     : this->CGameMode::Zc_req_join_guild(buf); break;
		case HEADER_ZC_UPDATE_GDID                        : this->CGameMode::Zc_update_gdid(buf); break;
		case HEADER_ZC_UPDATE_CHARSTAT                    : this->CGameMode::Zc_update_charstat(buf); break;
		case HEADER_ZC_GUILD_NOTICE                       : this->CGameMode::Zc_guild_notice(buf); break;
		case HEADER_ZC_REQ_ALLY_GUILD                     : this->CGameMode::Zc_req_ally_guild(buf); break;
		case HEADER_ZC_ACK_REQ_ALLY_GUILD                 : this->CGameMode::Zc_ack_req_ally_guild(buf); break;
		case HEADER_ZC_ACK_CHANGE_GUILD_POSITIONINFO      : this->CGameMode::Zc_ack_change_guild_positioninfo(buf); break;
		case HEADER_ZC_ITEMIDENTIFY_LIST                  : this->CGameMode::Zc_itemidentify_list(buf); break;
		case HEADER_ZC_ACK_ITEMIDENTIFY                   : this->CGameMode::Zc_ack_itemidentify(buf); break;
		case HEADER_ZC_ITEMCOMPOSITION_LIST               : this->CGameMode::Zc_itemcomposition_list(buf); break;
		case HEADER_ZC_ACK_ITEMCOMPOSITION                : this->CGameMode::Zc_ack_itemcomposition(buf); break;
		case HEADER_ZC_GUILD_CHAT                         : this->CGameMode::Zc_guild_chat(buf); break;
		case HEADER_ZC_ACK_REQ_HOSTILE_GUILD              : this->CGameMode::Zc_ack_req_hostile_guild(buf); break;
		case HEADER_ZC_MEMBER_ADD                         : this->CGameMode::Zc_member_add(buf); break;
		case HEADER_ZC_DELETE_RELATED_GUILD               : this->CGameMode::Zc_delete_related_guild(buf); break;
		case HEADER_ZC_ADD_RELATED_GUILD                  : this->CGameMode::Zc_add_related_guild(buf); break;
		case HEADER_PING                                  : break; // ignored
		case HEADER_ZC_ACK_ITEMREFINING                   : this->CGameMode::Zc_ack_itemrefining(buf); break;
		case HEADER_ZC_NOTIFY_MAPINFO                     : this->CGameMode::Zc_notify_mapinfo(buf); break;
		case HEADER_ZC_ACK_REQ_DISCONNECT                 : this->CGameMode::Zc_ack_req_disconnect(buf); break;
		case HEADER_ZC_MONSTER_INFO                       : this->CGameMode::Zc_monster_info(buf); break;
		case HEADER_ZC_MAKABLEITEMLIST                    : this->CGameMode::Zc_makable_item_list(buf); break;
		case HEADER_ZC_ACK_REQMAKINGITEM                  : this->CGameMode::Zc_ack_req_itemmaking(buf); break;
		case HEADER_ZC_TALKBOX_CHATCONTENTS               : this->CGameMode::Zc_talkbox_chat_contents(buf); break;
		case HEADER_ZC_UPDATE_MAPINFO                     : this->CGameMode::Zc_update_mapinfo(buf); break;
		case HEADER_ZC_ACK_REQNAME_BYGID                  : this->CGameMode::Zc_Ack_Reqname_bygid(buf); break;
		case HEADER_ZC_ACK_REQNAMEALL                     : this->CGameMode::Zc_Ack_Reqnameall(buf); break;
		case HEADER_ZC_MSG_STATE_CHANGE                   : this->CGameMode::Zc_Msg_State_Change(buf); break;
		case HEADER_ZC_NOTIFY_MAPPROPERTY                 : this->CGameMode::Zc_Notify_Mapproperty(buf); break;
		case HEADER_ZC_NOTIFY_RANKING                     : this->CGameMode::Zc_Notify_Ranking(buf); break;
		case HEADER_ZC_NOTIFY_EFFECT                      : this->CGameMode::Zc_Notify_Effect(buf); break;
		case HEADER_ZC_START_CAPTURE                      : this->CGameMode::Zc_Start_Capture(buf); break;
		case HEADER_ZC_TRYCAPTURE_MONSTER                 : this->CGameMode::Zc_TryCapture_Monster(buf); break;
		case HEADER_ZC_PROPERTY_PET                       : this->CGameMode::Zc_Property_Pet(buf); break;
		case HEADER_ZC_FEED_PET                           : this->CGameMode::Zc_Feed_Pet(buf); break;
		case HEADER_ZC_CHANGESTATE_PET                    : this->CGameMode::Zc_Change_Pet_Status(buf); break;
		case HEADER_ZC_PETEGG_LIST                        : this->CGameMode::Zc_PetEgg_List(buf); break;
		case HEADER_ZC_PET_ACT                            : this->CGameMode::Zc_Pet_Act(buf); break;
		case HEADER_ZC_PAR_CHANGE_USER                    : this->CGameMode::Zc_Par_Change_User(buf); break;
		case HEADER_ZC_SKILL_UPDATE                       : this->CGameMode::Zc_Skill_Update(buf); break;
		case HEADER_ZC_MAKINGARROW_LIST                   : this->CGameMode::Zc_MakingArrowList(buf); break;
		case HEADER_ZC_NPCSPRITE_CHANGE                   : this->CGameMode::Zc_NpcSpriteChange(buf); break;
		case HEADER_ZC_SHOWDIGIT                          : this->CGameMode::Zc_ShowDigit(buf); break;
		case HEADER_ZC_SHOW_IMAGE2                        : this->CGameMode::Zc_show_image2(buf); break;
		case HEADER_ZC_CHANGE_GUILD                       : this->CGameMode::Zc_ChangeGuild(buf); break;
		case HEADER_ZC_GUILD_INFO2                        : this->CGameMode::Zc_GuildInfo2(buf); break;
		case HEADER_ZC_GUILD_ZENY_ACK                     : this->CGameMode::Zc_GuildZenyAck(buf); break;
		case HEADER_ZC_DISPEL                             : this->CGameMode::Zc_Dispel(buf); break;
		case HEADER_ZC_REPLY_REMAINTIME                   : this->CGameMode::Zc_Reply_RemainTime(buf); break;
		case HEADER_ZC_INFO_REMAINTIME                    : this->CGameMode::Zc_Info_RemainTime(buf); break;
		case HEADER_ZC_BROADCAST2                         : this->CGameMode::Zc_Broadcast2(buf); break;
		case HEADER_ZC_ADD_ITEM_TO_STORE2                 : this->CGameMode::Zc_AddItemToStore2(buf); break;
		case HEADER_ZC_ADD_ITEM_TO_CART2                  : this->CGameMode::Zc_Add_Item_To_Cart2(buf); break;
		case HEADER_SC_ACK_ENCRYPTION                     : this->CGameMode::Sc_Ack_Encryption(buf); break;
		case HEADER_ZC_USE_ITEM_ACK2                      : this->CGameMode::Zc_Use_Item_Ack2(buf); break;
		case HEADER_ZC_SKILL_ENTRY2                       : this->CGameMode::Zc_Skill_Entry2(buf); break;
		case HEADER_ZC_MONSTER_TALK                       : this->CGameMode::Zc_Monster_Talk(buf); break;
		case HEADER_ZC_AUTOSPELLLIST                      : this->CGameMode::Zc_AutoSpellList(buf); break;
		case HEADER_ZC_DEVOTIONLIST                       : this->CGameMode::Zc_DevotionList(buf); break;
		case HEADER_ZC_SPIRITS                            : this->CGameMode::Zc_Spirits(buf); break;
		case HEADER_ZC_BLADESTOP                          : this->CGameMode::Zc_BladeStop(buf); break;
		case HEADER_ZC_COMBODELAY                         : this->CGameMode::Zc_ComboDelay(buf); break;
		case HEADER_ZC_SOUND                              : this->CGameMode::Zc_Sound(buf); break;
		case HEADER_ZC_OPEN_EDITDLGSTR                    : this->CGameMode::Zc_Open_EditDlgStr(buf); break;
		case HEADER_ZC_NOTIFY_MAPPROPERTY2                : this->CGameMode::Zc_Notify_Mapproperty2(buf); break;
		case HEADER_ZC_SPRITE_CHANGE2                     : this->CGameMode::Zc_Sprite_Change2(buf); break;
		case HEADER_ZC_NOTIFY_STANDENTRY2                 : this->CGameMode::Zc_Notify_Standentry2(buf); break;
		case HEADER_ZC_NOTIFY_NEWENTRY2                   : this->CGameMode::Zc_Notify_Newentry2(buf); break;
		case HEADER_ZC_NOTIFY_MOVEENTRY2                  : this->CGameMode::Zc_Notify_Moveentry2(buf); break;
		case HEADER_ZC_NOTIFY_SKILL2                      : this->CGameMode::Zc_Notify_Skill2(buf); break;
		case HEADER_ZC_ACK_ACCOUNTNAME                    : this->CGameMode::Zc_Ack_AccountName(buf); break;
		case HEADER_ZC_SPIRITS2                           : this->CGameMode::Zc_Spirits2(buf); break;
		case HEADER_ZC_REQ_COUPLE                         : this->CGameMode::Zc_Req_Couple(buf); break;
		case HEADER_ZC_START_COUPLE                       : this->CGameMode::Zc_Start_Couple(buf); break;
		case HEADER_ZC_COUPLENAME                         : this->CGameMode::Zc_CoupleName(buf); break;
		case HEADER_ZC_ADD_MEMBER_TO_GROUP2               : this->CGameMode::Zc_Add_Member_To_Group2(buf); break;
		case HEADER_ZC_CONGRATULATION                     : this->CGameMode::Zc_Congratulation(buf); break;
		case HEADER_ZC_NOTIFY_POSITION_TO_GUILDM          : this->CGameMode::Zc_Notify_Position_To_Guildm(buf); break;
		case HEADER_ZC_GUILD_MEMBER_MAP_CHANGE            : this->CGameMode::Zc_Guild_Member_Map_Change(buf); break;
		case HEADER_ZC_NORMAL_ITEMLIST2                   : this->CGameMode::Zc_Normal_Itemlist2(buf); break;
		case HEADER_ZC_CART_NORMAL_ITEMLIST2              : this->CGameMode::Zc_Cart_Normal_Itemlist2(buf); break;
		case HEADER_ZC_STORE_NORMAL_ITEMLIST2             : this->CGameMode::Zc_Store_Normal_Itemlist2(buf); break;
		case HEADER_ZC_UPDATE_CHARSTAT2                   : this->CGameMode::Zc_update_charstat2(buf); break;
		case HEADER_ZC_NOTIFY_EFFECT2                     : this->CGameMode::Zc_Notify_Effect2(buf); break;
		case HEADER_ZC_REQ_EXCHANGE_ITEM2                 : this->CGameMode::Zc_Req_Exchange_Item2(buf); break;
		case HEADER_ZC_ACK_EXCHANGE_ITEM2                 : this->CGameMode::Zc_Ack_Exchange_Item2(buf); break;
		case HEADER_ZC_REQ_BABY                           : this->CGameMode::Zc_Req_Baby(buf); break;
		case HEADER_ZC_START_BABY                         : this->CGameMode::Zc_Start_Baby(buf); break;
		case HEADER_ZC_REPAIRITEMLIST                     : this->CGameMode::Zc_repair_item_list(buf); break;
		case HEADER_ZC_ACK_ITEMREPAIR                     : this->CGameMode::Zc_ack_itemrepair(buf); break;
		case HEADER_ZC_HIGHJUMP                           : this->CGameMode::Zc_HighJump(buf); break;
		case HEADER_ZC_FRIENDS_LIST                       : this->CGameMode::Zc_Friends_List(buf); break;
		case HEADER_ZC_DIVORCE                            : this->CGameMode::Zc_Divorce(buf); break;
		case HEADER_ZC_FRIENDS_STATE                      : this->CGameMode::Zc_Friends_State(buf); break;
		case HEADER_ZC_REQ_ADD_FRIENDS                    : this->CGameMode::Zc_Req_Join_Friend(buf); break;
		case HEADER_ZC_ADD_FRIENDS_LIST                   : this->CGameMode::Zc_Add_Friends_List(buf); break;
		case HEADER_ZC_DELETE_FRIENDS                     : this->CGameMode::Zc_Req_Delete_Friend(buf); break;
		case HEADER_ZC_STARSKILL                          : this->CGameMode::Zc_StarSkill(buf); break;
		case HEADER_ZC_ACK_PVPPOINT                       : this->CGameMode::Zc_Ack_PvpPoint(buf); break;
		case HEADER_ZC_ACK_STATUS_GM                      : this->CGameMode::Zc_Ack_Status_GM(buf); break;
		case HEADER_ZC_SKILLMSG                           : this->CGameMode::Zc_SKILLMSG(buf); break;
		case HEADER_ZC_BABYMSG                            : this->CGameMode::Zc_BABYMSG(buf); break;
		case HEADER_ZC_BLACKSMITH_RANK                    : this->CGameMode::ZC_BLACKSMITH_RANK(buf); break;
		case HEADER_ZC_ALCHEMIST_RANK                     : this->CGameMode::ZC_ALCHEMIST_RANK(buf); break;
		case HEADER_ZC_BLACKSMITH_POINT                   : this->CGameMode::ZC_BLACKSMITH_POINT(buf); break;
		case HEADER_ZC_ALCHEMIST_POINT                    : this->CGameMode::ZC_ALCHEMIST_POINT(buf); break;
		case HEADER_ZC_NOTIFY_PKINFO                      : this->CGameMode::Zc_Notify_PKinfo(buf); break;
		case HEADER_ZC_NOTIFY_CRAZYKILLER                 : this->CGameMode::Zc_Notify_CrazyKiller(buf); break;
		case HEADER_ZC_NOTIFY_WEAPONITEMLIST              : this->CGameMode::Zc_notify_weapon_item_list(buf); break;
		case HEADER_ZC_ACK_WEAPONREFINE                   : this->CGameMode::Zc_ack_weaponrefine(buf); break;
		case HEADER_ZC_TAEKWON_POINT                      : this->CGameMode::ZC_TAEKWON_POINT(buf); break;
		case HEADER_ZC_TAEKWON_RANK                       : this->CGameMode::ZC_TAEKWON_RANK(buf); break;
		case HEADER_ZC_GAME_GUARD                         : this->CGameMode::Zc_Game_Guard(buf); break;
		case HEADER_ZC_STATE_CHANGE3                      : this->CGameMode::Zc_State_Change3(buf); break;
		case HEADER_ZC_NOTIFY_STANDENTRY3                 : this->CGameMode::Zc_Notify_Standentry3(buf); break;
		case HEADER_ZC_NOTIFY_NEWENTRY3                   : this->CGameMode::Zc_Notify_Newentry3(buf); break;
		case HEADER_ZC_NOTIFY_MOVEENTRY3                  : this->CGameMode::Zc_Notify_Moveentry3(buf); break;
		case HEADER_ZC_PROPERTY_HOMUN                     : this->CGameMode::Zc_Property_Homun(buf); break;
		case HEADER_ZC_FEED_MER                           : this->CGameMode::Zc_Feed_Pet(buf); break;
		case HEADER_ZC_CHANGESTATE_MER                    : this->CGameMode::Zc_Change_Mer_Status(buf); break;
		case HEADER_ZC_HOSKILLINFO_LIST                   : this->CGameMode::Zc_Skillinfo_List(buf); break;
		case HEADER_ZC_KILLER_POINT                       : this->CGameMode::ZC_KILLER_POINT(buf); break;
		case HEADER_ZC_KILLER_RANK                        : this->CGameMode::ZC_KILLER_RANK(buf); break;
		case HEADER_ZC_HOSKILLINFO_UPDATE                 : this->CGameMode::Zc_Skillinfo_Update(buf); break;
		case HEADER_ZC_MAIL_REQ_GET_LIST                  : this->CGameMode::Zc_Mail_Req_Get_List(buf); break;
		case HEADER_ZC_MAIL_REQ_OPEN                      : this->CGameMode::Zc_Mail_Req_Open(buf); break;
		case HEADER_ZC_MAIL_REQ_GET_ITEM                  : this->CGameMode::Zc_Mail_Req_Get_Item(buf); break;
		case HEADER_ZC_MAIL_REQ_SEND                      : this->CGameMode::Zc_Mail_Req_Send(buf); break;
		case HEADER_ZC_MAIL_RECEIVE                       : this->CGameMode::Zc_Mail_Receive(buf); break;
		case HEADER_ZC_AUCTION_RESULT                     : this->CGameMode::Zc_Auction_Result(buf); break;
		case HEADER_ZC_AUCTION_ITEM_REQ_SEARCH            : this->CGameMode::Zc_Auction_Item_Req_Search(buf); break;
		case HEADER_ZC_STARPLACE                          : this->CGameMode::Zc_StarPlace(buf); break;
		case HEADER_ZC_ACK_MAIL_ADD_ITEM                  : this->CGameMode::Zc_Ack_Mail_Add_Item(buf); break;
		case HEADER_ZC_ACK_AUCTION_ADD_ITEM               : this->CGameMode::Zc_Ack_Auction_Add_Item(buf); break;
		case HEADER_ZC_ACK_MAIL_DELETE                    : this->CGameMode::Zc_Ack_Mail_Delete(buf); break;
		case HEADER_ZC_MAKINGITEM_LIST                    : this->CGameMode::Zc_MakingItemList(buf); break;
		case HEADER_CZ_AUCTION_REQ_MY_SELL_STOP           : this->CGameMode::Zc_Auction_My_Sell_Stop(buf); break;
		case HEADER_ZC_AUCTION_WINDOWS                    : this->CGameMode::Zc_Auction_Windows(buf); break;
		case HEADER_ZC_MAIL_WINDOWS                       : this->CGameMode::Zc_Mail_Windows(buf); break;
		case HEADER_ZC_ACK_MAIL_RETURN                    : this->CGameMode::Zc_Ack_Mail_Return(buf); break;
		case HEADER_ZC_HUNTINGLIST                        : this->CGameMode::Zc_HuntingList(buf); break;
		case HEADER_ZC_PCBANG_EFFECT                      : this->CGameMode::Zc_Pcbang_Effect(buf); break;
		case HEADER_ZC_GANGSI_POINT                       : this->CGameMode::ZC_GANGSI_POINT(buf); break;
		case HEADER_ZC_GANGSI_RANK                        : this->CGameMode::ZC_GANGSI_RANK(buf); break;
		case HEADER_ZC_AID                                : this->CGameMode::Zc_Aid(buf); break;
		case HEADER_ZC_NOTIFY_EFFECT3                     : this->CGameMode::Zc_Notify_Effect3(buf); break;
		case HEADER_ZC_DEATH_QUESTION                     : this->CGameMode::ZC_DEATH_QUESTION(buf); break;
		case HEADER_ZC_PC_CASH_POINT_ITEMLIST             : this->CGameMode::Zc_Pc_Cash_Point_ItemList(buf); break;
		case HEADER_ZC_PC_CASH_POINT_UPDATE               : this->CGameMode::Zc_Pc_Cash_Point_Update(buf); break;
		case HEADER_ZC_NPC_SHOWEFST_UPDATE                : this->CGameMode::Zc_Npc_Showefst_Update(buf); break;
		case HEADER_ZC_MSG                                : this->CGameMode::Zc_Msg(buf); break;
		case HEADER_ZC_BOSS_INFO                          : this->CGameMode::Zc_Boss_Info(buf); break;
		case HEADER_ZC_READ_BOOK                          : this->CGameMode::Zc_Read_Book(buf); break;
		case HEADER_ZC_EQUIPMENT_ITEMLIST2                : this->CGameMode::Zc_Equipment_Itemlist2(buf); break;
		case HEADER_ZC_STORE_EQUIPMENT_ITEMLIST2          : this->CGameMode::Zc_Store_Equipment_Itemlist2(buf); break;
		case HEADER_ZC_CART_EQUIPMENT_ITEMLIST2           : this->CGameMode::Zc_Cart_Equipment_Itemlist2(buf); break;
		case HEADER_ZC_CASH_TIME_COUNTER                  : this->CGameMode::Zc_Cash_Time_Counter(buf); break;
		case HEADER_ZC_CASH_ITEM_DELETE                   : this->CGameMode::Zc_Cash_Item_Delete(buf); break;
		case HEADER_ZC_ITEM_PICKUP_ACK2                   : this->CGameMode::Zc_Item_Pickup_Ack2(buf); break;
		case HEADER_ZC_MER_INIT                           : this->CGameMode::Zc_Mer_Init(buf); break;
		case HEADER_ZC_MER_SKILLINFO_LIST                 : this->CGameMode::Zc_Skillinfo_List(buf); break;
		case HEADER_ZC_MER_SKILLINFO_UPDATE               : this->CGameMode::Zc_Skillinfo_Update(buf); break;
		case HEADER_ZC_MER_PAR_CHANGE                     : this->CGameMode::Zc_Mer_Par_Change(buf); break;
		case HEADER_ZC_ALL_QUEST_LIST                     : this->CGameMode::Zc_All_Quest_List(buf); break;
		case HEADER_ZC_ALL_QUEST_MISSION                  : this->CGameMode::Zc_All_Quest_Mission(buf); break;
		case HEADER_ZC_ADD_QUEST                          : this->CGameMode::Zc_Add_Quest(buf); break;
		case HEADER_ZC_DEL_QUEST                          : this->CGameMode::Zc_Del_Quest(buf); break;
		case HEADER_ZC_UPDATE_MISSION_HUNT                : this->CGameMode::Zc_Update_Mission_Hunt(buf); break;
		case HEADER_ZC_ACTIVE_QUEST                       : this->CGameMode::Zc_Active_Quest(buf); break;
		case HEADER_ZC_ITEM_PICKUP_PARTY                  : this->CGameMode::Zc_Item_Pickup_Party(buf); break;
		case HEADER_ZC_SHORTCUT_KEY_LIST                  : this->CGameMode::Zc_ShortCut_Key_List(buf); break; //FIXME: incompatible (only supports v2)
		case HEADER_ZC_EQUIPITEM_DAMAGED                  : this->CGameMode::Zc_EquipItem_Damaged(buf); break;
		case HEADER_ZC_NPC_CHAT                           : this->CGameMode::Zc_Npc_Chat(buf); break;
		case HEADER_ZC_FORMATSTRING_MSG                   : this->CGameMode::Zc_Formatstring_Msg(buf); break;
		case HEADER_ZC_PARTY_JOIN_REQ_ACK                 : this->CGameMode::Zc_Ack_Req_Join_Group(buf); break;
		case HEADER_ZC_PARTY_JOIN_REQ                     : this->CGameMode::Zc_Req_Join_Group(buf); break;
		case HEADER_ZC_PARTY_CONFIG                       : this->CGameMode::Zc_Party_Config(buf); break;
		case HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_INFO  : this->CGameMode::Zc_MemorialDungeon_Subscription_Info(buf); break;
		case HEADER_ZC_MEMORIALDUNGEON_SUBSCRIPTION_NOTIFY: this->CGameMode::Zc_MemorialDungeon_Subscription_Notify(buf); break;
		case HEADER_ZC_MEMORIALDUNGEON_INFO               : this->CGameMode::Zc_MemorialDungeon_Info(buf); break;
		case HEADER_ZC_MEMORIALDUNGEON_NOTIFY             : this->CGameMode::Zc_MemorialDungeon_Notify(buf); break;
		case HEADER_ZC_EQUIPMENT_ITEMLIST3                : this->CGameMode::Zc_Equipment_Itemlist3(buf); break;
		case HEADER_ZC_STORE_EQUIPMENT_ITEMLIST3          : this->CGameMode::Zc_Store_Equipment_Itemlist3(buf); break;
		case HEADER_ZC_CART_EQUIPMENT_ITEMLIST3           : this->CGameMode::Zc_Cart_Equipment_Itemlist3(buf); break;
		case HEADER_ZC_NOTIFY_BIND_ON_EQUIP               : this->CGameMode::Zc_NotifyBindOnEquip(buf); break;
		case HEADER_ZC_ITEM_PICKUP_ACK3                   : this->CGameMode::Zc_Item_Pickup_Ack3(buf); break;
		case HEADER_ZC_ISVR_DISCONNECT                    : this->CGameMode::Zc_Isvr_Disconnect(buf); break;
		case HEADER_ZC_EQUIPWIN_MICROSCOPE                : this->CGameMode::Zc_EquipwinMicroscope(buf); break;
		case HEADER_ZC_CONFIG                             : this->CGameMode::Zc_Config(buf); break;
		case HEADER_ZC_CONFIG_NOTIFY                      : this->CGameMode::Zc_Config_Notify(buf); break;
		case HEADER_ZC_BATTLEFIELD_CHAT                   : this->CGameMode::Zc_Battlefield_Chat(buf); break;
		case HEADER_ZC_BATTLEFIELD_NOTIFY_CAMPINFO        : this->CGameMode::Zc_Battlefield_Notify_Campinfo(buf); break;
		case HEADER_ZC_BATTLEFIELD_NOTIFY_POINT           : this->CGameMode::Zc_Battlefield_Notify_Point(buf); break;
		case HEADER_ZC_BATTLEFIELD_NOTIFY_POSITION        : this->CGameMode::Zc_Battlefield_Notify_Position(buf); break;
		case HEADER_ZC_BATTLEFIELD_NOTIFY_HP              : this->CGameMode::Zc_Battlefield_Notify_Hp(buf); break;
		case HEADER_ZC_NOTIFY_ACT2                        :
		{
			PACKET_ZC_NOTIFY_ACT2& packet = *reinterpret_cast<PACKET_ZC_NOTIFY_ACT2*>(buf);
			this->CGameMode::Zc_Notify_Act(packet.GID, packet.targetGID, packet.startTime, packet.attackMT, packet.attackedMT, packet.damage, packet.count, packet.action, packet.leftDamage);
		}
		break;
		case HEADER_ZC_MAPPROPERTY                        : this->CGameMode::Zc_Mapproperty(buf); break;
		case HEADER_ZC_NORMAL_ITEMLIST3                   : this->CGameMode::Zc_Normal_Itemlist3(buf); break;
		case HEADER_ZC_CART_NORMAL_ITEMLIST3              : this->CGameMode::Zc_Cart_Normal_Itemlist3(buf); break;
		case HEADER_ZC_STORE_NORMAL_ITEMLIST3             : this->CGameMode::Zc_Store_Normal_Itemlist3(buf); break;
		case HEADER_ZC_ACCEPT_ENTER2                      : this->CGameMode::Zc_Accept_Enter2(buf); break;
		case HEADER_ZC_NOTIFY_MOVEENTRY4                  : this->CGameMode::Zc_Notify_Moveentry4(buf); break; //FIXME: incompatible (only supports v7)
		case HEADER_ZC_NOTIFY_NEWENTRY4                   : this->CGameMode::Zc_Notify_Newentry4(buf); break;
		case HEADER_ZC_NOTIFY_STANDENTRY4                 : this->CGameMode::Zc_Notify_Standentry4(buf); break;
		case HEADER_ZC_NOTIFY_FONT                        : this->CGameMode::Zc_Notify_Font(buf); break;
		case HEADER_ZC_PROGRESS                           : this->CGameMode::Zc_Progress(buf); break;
		case HEADER_ZC_PROGRESS_CANCEL                    : this->CGameMode::Zc_Progress_Cancel(buf); break;
		case HEADER_ZC_ITEM_FALL_ENTRY2                   : this->CGameMode::Zc_Item_Fall_Entry2(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY2__M1               : this->CGameMode::Zc_Item_Fall_Entry2_m1(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY2__M2               : this->CGameMode::Zc_Item_Fall_Entry2_m2(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY2__M3               : this->CGameMode::Zc_Item_Fall_Entry2_m3(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY2__M4               : this->CGameMode::Zc_Item_Fall_Entry2_m4(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY2__M5               : this->CGameMode::Zc_Item_Fall_Entry2_m5(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY2__M6               : this->CGameMode::Zc_Item_Fall_Entry2_m6(buf); break;
		case HEADER_ZC_NOTIFY_MOVEENTRY5                  : this->CGameMode::Zc_Notify_Moveentry5(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY5__M1              : this->CGameMode::Zc_Notify_Moveentry5__m1(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY5__M2              : this->CGameMode::Zc_Notify_Moveentry5__m2(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY5__M3              : this->CGameMode::Zc_Notify_Moveentry5__m3(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY5__M4              : this->CGameMode::Zc_Notify_Moveentry5__m4(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY5__M5              : this->CGameMode::Zc_Notify_Moveentry5__m5(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY5__M6              : this->CGameMode::Zc_Notify_Moveentry5__m6(buf); break;
		case HEADER_ZC_NOTIFY_NPC_STANDENTRY              : this->CGameMode::Zc_Notify_Npc_Standentry(buf); break;
//		case HEADER_ZC_NOTIFY_NPC_STANDENTRY__M1          : this->CGameMode::Zc_Notify_Npc_Standentry__m1(buf); break;
//		case HEADER_ZC_NOTIFY_NPC_STANDENTRY__M2          : this->CGameMode::Zc_Notify_Npc_Standentry__m2(buf); break;
//		case HEADER_ZC_NOTIFY_NPC_STANDENTRY__M3          : this->CGameMode::Zc_Notify_Npc_Standentry__m3(buf); break;
//		case HEADER_ZC_NOTIFY_NPC_STANDENTRY__M4          : this->CGameMode::Zc_Notify_Npc_Standentry__m4(buf); break;
//		case HEADER_ZC_NOTIFY_NPC_STANDENTRY__M5          : this->CGameMode::Zc_Notify_Npc_Standentry__m5(buf); break;
//		case HEADER_ZC_NOTIFY_NPC_STANDENTRY__M6          : this->CGameMode::Zc_Notify_Npc_Standentry__m6(buf); break;
		case HEADER_ZC_REASSEMBLY_CERTIFY                 : this->CGameMode::Zc_Reassembly_Certify(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M01            : this->CGameMode::Zc_Reassembly_Certify__m01(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M02            : this->CGameMode::Zc_Reassembly_Certify__m02(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M03            : this->CGameMode::Zc_Reassembly_Certify__m03(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M04            : this->CGameMode::Zc_Reassembly_Certify__m04(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M05            : this->CGameMode::Zc_Reassembly_Certify__m05(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M06            : this->CGameMode::Zc_Reassembly_Certify__m06(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M07            : this->CGameMode::Zc_Reassembly_Certify__m07(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M08            : this->CGameMode::Zc_Reassembly_Certify__m08(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M09            : this->CGameMode::Zc_Reassembly_Certify__m09(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M10            : this->CGameMode::Zc_Reassembly_Certify__m10(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M11            : this->CGameMode::Zc_Reassembly_Certify__m11(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M12            : this->CGameMode::Zc_Reassembly_Certify__m12(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M13            : this->CGameMode::Zc_Reassembly_Certify__m13(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M14            : this->CGameMode::Zc_Reassembly_Certify__m14(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M15            : this->CGameMode::Zc_Reassembly_Certify__m15(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M16            : this->CGameMode::Zc_Reassembly_Certify__m16(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M17            : this->CGameMode::Zc_Reassembly_Certify__m17(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M18            : this->CGameMode::Zc_Reassembly_Certify__m18(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M19            : this->CGameMode::Zc_Reassembly_Certify__m19(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M20            : this->CGameMode::Zc_Reassembly_Certify__m20(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M21            : this->CGameMode::Zc_Reassembly_Certify__m21(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M22            : this->CGameMode::Zc_Reassembly_Certify__m22(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M23            : this->CGameMode::Zc_Reassembly_Certify__m23(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M24            : this->CGameMode::Zc_Reassembly_Certify__m24(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M25            : this->CGameMode::Zc_Reassembly_Certify__m25(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M26            : this->CGameMode::Zc_Reassembly_Certify__m26(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M27            : this->CGameMode::Zc_Reassembly_Certify__m27(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M28            : this->CGameMode::Zc_Reassembly_Certify__m28(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M29            : this->CGameMode::Zc_Reassembly_Certify__m29(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M30            : this->CGameMode::Zc_Reassembly_Certify__m30(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M31            : this->CGameMode::Zc_Reassembly_Certify__m31(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M32            : this->CGameMode::Zc_Reassembly_Certify__m32(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M33            : this->CGameMode::Zc_Reassembly_Certify__m33(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M34            : this->CGameMode::Zc_Reassembly_Certify__m34(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M35            : this->CGameMode::Zc_Reassembly_Certify__m35(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M36            : this->CGameMode::Zc_Reassembly_Certify__m36(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M37            : this->CGameMode::Zc_Reassembly_Certify__m37(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M38            : this->CGameMode::Zc_Reassembly_Certify__m38(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M39            : this->CGameMode::Zc_Reassembly_Certify__m39(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M40            : this->CGameMode::Zc_Reassembly_Certify__m40(buf); break;
//		case HEADER_ZC_REASSEMBLY_CERTIFY__M41            : this->CGameMode::Zc_Reassembly_Certify__m41(buf); break;
		case HEADER_ZC_NOTIFY_MOVEENTRY6                  : this->CGameMode::Zc_Notify_Moveentry6(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M01             : this->CGameMode::Zc_Notify_Moveentry6__m01(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M02             : this->CGameMode::Zc_Notify_Moveentry6__m02(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M03             : this->CGameMode::Zc_Notify_Moveentry6__m03(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M04             : this->CGameMode::Zc_Notify_Moveentry6__m04(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M05             : this->CGameMode::Zc_Notify_Moveentry6__m05(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M06             : this->CGameMode::Zc_Notify_Moveentry6__m06(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M07             : this->CGameMode::Zc_Notify_Moveentry6__m07(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M08             : this->CGameMode::Zc_Notify_Moveentry6__m08(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M09             : this->CGameMode::Zc_Notify_Moveentry6__m09(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M10             : this->CGameMode::Zc_Notify_Moveentry6__m10(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M11             : this->CGameMode::Zc_Notify_Moveentry6__m11(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M12             : this->CGameMode::Zc_Notify_Moveentry6__m12(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M13             : this->CGameMode::Zc_Notify_Moveentry6__m13(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M14             : this->CGameMode::Zc_Notify_Moveentry6__m14(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M15             : this->CGameMode::Zc_Notify_Moveentry6__m15(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M16             : this->CGameMode::Zc_Notify_Moveentry6__m16(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M17             : this->CGameMode::Zc_Notify_Moveentry6__m17(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M18             : this->CGameMode::Zc_Notify_Moveentry6__m18(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M19             : this->CGameMode::Zc_Notify_Moveentry6__m19(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M20             : this->CGameMode::Zc_Notify_Moveentry6__m20(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M21             : this->CGameMode::Zc_Notify_Moveentry6__m21(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M22             : this->CGameMode::Zc_Notify_Moveentry6__m22(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M23             : this->CGameMode::Zc_Notify_Moveentry6__m23(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M24             : this->CGameMode::Zc_Notify_Moveentry6__m24(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M25             : this->CGameMode::Zc_Notify_Moveentry6__m25(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M26             : this->CGameMode::Zc_Notify_Moveentry6__m26(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M27             : this->CGameMode::Zc_Notify_Moveentry6__m27(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M28             : this->CGameMode::Zc_Notify_Moveentry6__m28(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M29             : this->CGameMode::Zc_Notify_Moveentry6__m29(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M30             : this->CGameMode::Zc_Notify_Moveentry6__m30(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M31             : this->CGameMode::Zc_Notify_Moveentry6__m31(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M32             : this->CGameMode::Zc_Notify_Moveentry6__m32(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M33             : this->CGameMode::Zc_Notify_Moveentry6__m33(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M34             : this->CGameMode::Zc_Notify_Moveentry6__m34(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M35             : this->CGameMode::Zc_Notify_Moveentry6__m35(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M36             : this->CGameMode::Zc_Notify_Moveentry6__m36(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M37             : this->CGameMode::Zc_Notify_Moveentry6__m37(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M38             : this->CGameMode::Zc_Notify_Moveentry6__m38(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M39             : this->CGameMode::Zc_Notify_Moveentry6__m39(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M40             : this->CGameMode::Zc_Notify_Moveentry6__m40(buf); break;
//		case HEADER_ZC_NOTIFY_MOVEENTRY6__M41             : this->CGameMode::Zc_Notify_Moveentry6__m41(buf); break;
		case HEADER_ZC_NOTIFY_STANDENTRY6                 : this->CGameMode::Zc_Notify_Standentry6(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M01            : this->CGameMode::Zc_Notify_Standentry6__m01(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M02            : this->CGameMode::Zc_Notify_Standentry6__m02(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M03            : this->CGameMode::Zc_Notify_Standentry6__m03(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M04            : this->CGameMode::Zc_Notify_Standentry6__m04(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M05            : this->CGameMode::Zc_Notify_Standentry6__m05(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M06            : this->CGameMode::Zc_Notify_Standentry6__m06(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M07            : this->CGameMode::Zc_Notify_Standentry6__m07(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M08            : this->CGameMode::Zc_Notify_Standentry6__m08(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M09            : this->CGameMode::Zc_Notify_Standentry6__m09(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M10            : this->CGameMode::Zc_Notify_Standentry6__m10(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M11            : this->CGameMode::Zc_Notify_Standentry6__m11(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M12            : this->CGameMode::Zc_Notify_Standentry6__m12(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M13            : this->CGameMode::Zc_Notify_Standentry6__m13(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M14            : this->CGameMode::Zc_Notify_Standentry6__m14(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M15            : this->CGameMode::Zc_Notify_Standentry6__m15(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M16            : this->CGameMode::Zc_Notify_Standentry6__m16(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M17            : this->CGameMode::Zc_Notify_Standentry6__m17(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M18            : this->CGameMode::Zc_Notify_Standentry6__m18(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M19            : this->CGameMode::Zc_Notify_Standentry6__m19(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M20            : this->CGameMode::Zc_Notify_Standentry6__m20(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M21            : this->CGameMode::Zc_Notify_Standentry6__m21(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M22            : this->CGameMode::Zc_Notify_Standentry6__m22(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M23            : this->CGameMode::Zc_Notify_Standentry6__m23(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M24            : this->CGameMode::Zc_Notify_Standentry6__m24(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M25            : this->CGameMode::Zc_Notify_Standentry6__m25(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M26            : this->CGameMode::Zc_Notify_Standentry6__m26(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M27            : this->CGameMode::Zc_Notify_Standentry6__m27(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M28            : this->CGameMode::Zc_Notify_Standentry6__m28(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M29            : this->CGameMode::Zc_Notify_Standentry6__m29(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M30            : this->CGameMode::Zc_Notify_Standentry6__m30(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M31            : this->CGameMode::Zc_Notify_Standentry6__m31(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M32            : this->CGameMode::Zc_Notify_Standentry6__m32(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M33            : this->CGameMode::Zc_Notify_Standentry6__m33(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M34            : this->CGameMode::Zc_Notify_Standentry6__m34(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M35            : this->CGameMode::Zc_Notify_Standentry6__m35(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M36            : this->CGameMode::Zc_Notify_Standentry6__m36(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M37            : this->CGameMode::Zc_Notify_Standentry6__m37(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M38            : this->CGameMode::Zc_Notify_Standentry6__m38(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M39            : this->CGameMode::Zc_Notify_Standentry6__m39(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M40            : this->CGameMode::Zc_Notify_Standentry6__m40(buf); break;
//		case HEADER_ZC_NOTIFY_STANDENTRY6__M41            : this->CGameMode::Zc_Notify_Standentry6__m41(buf); break;
		case HEADER_ZC_ITEM_FALL_ENTRY3                   : this->CGameMode::Zc_Item_Fall_Entry3(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M01              : this->CGameMode::Zc_Item_Fall_Entry3__m01(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M02              : this->CGameMode::Zc_Item_Fall_Entry3__m02(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M03              : this->CGameMode::Zc_Item_Fall_Entry3__m03(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M04              : this->CGameMode::Zc_Item_Fall_Entry3__m04(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M05              : this->CGameMode::Zc_Item_Fall_Entry3__m05(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M06              : this->CGameMode::Zc_Item_Fall_Entry3__m06(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M07              : this->CGameMode::Zc_Item_Fall_Entry3__m07(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M08              : this->CGameMode::Zc_Item_Fall_Entry3__m08(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M09              : this->CGameMode::Zc_Item_Fall_Entry3__m09(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M10              : this->CGameMode::Zc_Item_Fall_Entry3__m10(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M11              : this->CGameMode::Zc_Item_Fall_Entry3__m11(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M12              : this->CGameMode::Zc_Item_Fall_Entry3__m12(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M13              : this->CGameMode::Zc_Item_Fall_Entry3__m13(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M14              : this->CGameMode::Zc_Item_Fall_Entry3__m14(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M15              : this->CGameMode::Zc_Item_Fall_Entry3__m15(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M16              : this->CGameMode::Zc_Item_Fall_Entry3__m16(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M17              : this->CGameMode::Zc_Item_Fall_Entry3__m17(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M18              : this->CGameMode::Zc_Item_Fall_Entry3__m18(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M19              : this->CGameMode::Zc_Item_Fall_Entry3__m19(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M20              : this->CGameMode::Zc_Item_Fall_Entry3__m20(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M21              : this->CGameMode::Zc_Item_Fall_Entry3__m21(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M22              : this->CGameMode::Zc_Item_Fall_Entry3__m22(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M23              : this->CGameMode::Zc_Item_Fall_Entry3__m23(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M24              : this->CGameMode::Zc_Item_Fall_Entry3__m24(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M25              : this->CGameMode::Zc_Item_Fall_Entry3__m25(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M26              : this->CGameMode::Zc_Item_Fall_Entry3__m26(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M27              : this->CGameMode::Zc_Item_Fall_Entry3__m27(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M28              : this->CGameMode::Zc_Item_Fall_Entry3__m28(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M29              : this->CGameMode::Zc_Item_Fall_Entry3__m29(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M30              : this->CGameMode::Zc_Item_Fall_Entry3__m30(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M31              : this->CGameMode::Zc_Item_Fall_Entry3__m31(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M32              : this->CGameMode::Zc_Item_Fall_Entry3__m32(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M33              : this->CGameMode::Zc_Item_Fall_Entry3__m33(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M34              : this->CGameMode::Zc_Item_Fall_Entry3__m34(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M35              : this->CGameMode::Zc_Item_Fall_Entry3__m35(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M36              : this->CGameMode::Zc_Item_Fall_Entry3__m36(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M37              : this->CGameMode::Zc_Item_Fall_Entry3__m37(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M38              : this->CGameMode::Zc_Item_Fall_Entry3__m38(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M39              : this->CGameMode::Zc_Item_Fall_Entry3__m39(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M40              : this->CGameMode::Zc_Item_Fall_Entry3__m40(buf); break;
//		case HEADER_ZC_ITEM_FALL_ENTRY3__M41              : this->CGameMode::Zc_Item_Fall_Entry3__m41(buf); break;
		case HEADER_ZC_NOTIFY_ACT3                        : this->CGameMode::Zc_Notify_Act3(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M01                   : this->CGameMode::Zc_Notify_Act3__m01(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M02                   : this->CGameMode::Zc_Notify_Act3__m02(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M03                   : this->CGameMode::Zc_Notify_Act3__m03(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M04                   : this->CGameMode::Zc_Notify_Act3__m04(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M05                   : this->CGameMode::Zc_Notify_Act3__m05(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M06                   : this->CGameMode::Zc_Notify_Act3__m06(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M07                   : this->CGameMode::Zc_Notify_Act3__m07(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M08                   : this->CGameMode::Zc_Notify_Act3__m08(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M09                   : this->CGameMode::Zc_Notify_Act3__m09(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M10                   : this->CGameMode::Zc_Notify_Act3__m10(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M11                   : this->CGameMode::Zc_Notify_Act3__m11(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M12                   : this->CGameMode::Zc_Notify_Act3__m12(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M13                   : this->CGameMode::Zc_Notify_Act3__m13(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M14                   : this->CGameMode::Zc_Notify_Act3__m14(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M15                   : this->CGameMode::Zc_Notify_Act3__m15(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M16                   : this->CGameMode::Zc_Notify_Act3__m16(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M17                   : this->CGameMode::Zc_Notify_Act3__m17(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M18                   : this->CGameMode::Zc_Notify_Act3__m18(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M19                   : this->CGameMode::Zc_Notify_Act3__m19(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M20                   : this->CGameMode::Zc_Notify_Act3__m20(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M21                   : this->CGameMode::Zc_Notify_Act3__m21(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M22                   : this->CGameMode::Zc_Notify_Act3__m22(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M23                   : this->CGameMode::Zc_Notify_Act3__m23(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M24                   : this->CGameMode::Zc_Notify_Act3__m24(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M25                   : this->CGameMode::Zc_Notify_Act3__m25(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M26                   : this->CGameMode::Zc_Notify_Act3__m26(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M27                   : this->CGameMode::Zc_Notify_Act3__m27(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M28                   : this->CGameMode::Zc_Notify_Act3__m28(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M29                   : this->CGameMode::Zc_Notify_Act3__m29(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M30                   : this->CGameMode::Zc_Notify_Act3__m30(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M31                   : this->CGameMode::Zc_Notify_Act3__m31(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M32                   : this->CGameMode::Zc_Notify_Act3__m32(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M33                   : this->CGameMode::Zc_Notify_Act3__m33(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M34                   : this->CGameMode::Zc_Notify_Act3__m34(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M35                   : this->CGameMode::Zc_Notify_Act3__m35(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M36                   : this->CGameMode::Zc_Notify_Act3__m36(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M37                   : this->CGameMode::Zc_Notify_Act3__m37(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M38                   : this->CGameMode::Zc_Notify_Act3__m38(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M39                   : this->CGameMode::Zc_Notify_Act3__m39(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M40                   : this->CGameMode::Zc_Notify_Act3__m40(buf); break;
//		case HEADER_ZC_NOTIFY_ACT3__M41                   : this->CGameMode::Zc_Notify_Act3__m41(buf); break;
		case HEADER_ZC_BROADCAST3                         : this->CGameMode::Zc_Broadcast3(buf); break;
//		case HEADER_ZC_BROADCAST3__M01                    : this->CGameMode::Zc_Broadcast3__m01(buf); break;
//		case HEADER_ZC_BROADCAST3__M02                    : this->CGameMode::Zc_Broadcast3__m02(buf); break;
//		case HEADER_ZC_BROADCAST3__M03                    : this->CGameMode::Zc_Broadcast3__m03(buf); break;
//		case HEADER_ZC_BROADCAST3__M04                    : this->CGameMode::Zc_Broadcast3__m04(buf); break;
//		case HEADER_ZC_BROADCAST3__M05                    : this->CGameMode::Zc_Broadcast3__m05(buf); break;
//		case HEADER_ZC_BROADCAST3__M06                    : this->CGameMode::Zc_Broadcast3__m06(buf); break;
//		case HEADER_ZC_BROADCAST3__M07                    : this->CGameMode::Zc_Broadcast3__m07(buf); break;
//		case HEADER_ZC_BROADCAST3__M08                    : this->CGameMode::Zc_Broadcast3__m08(buf); break;
//		case HEADER_ZC_BROADCAST3__M09                    : this->CGameMode::Zc_Broadcast3__m09(buf); break;
//		case HEADER_ZC_BROADCAST3__M10                    : this->CGameMode::Zc_Broadcast3__m10(buf); break;
//		case HEADER_ZC_BROADCAST3__M11                    : this->CGameMode::Zc_Broadcast3__m11(buf); break;
//		case HEADER_ZC_BROADCAST3__M12                    : this->CGameMode::Zc_Broadcast3__m12(buf); break;
//		case HEADER_ZC_BROADCAST3__M13                    : this->CGameMode::Zc_Broadcast3__m13(buf); break;
//		case HEADER_ZC_BROADCAST3__M14                    : this->CGameMode::Zc_Broadcast3__m14(buf); break;
//		case HEADER_ZC_BROADCAST3__M15                    : this->CGameMode::Zc_Broadcast3__m15(buf); break;
//		case HEADER_ZC_BROADCAST3__M16                    : this->CGameMode::Zc_Broadcast3__m16(buf); break;
//		case HEADER_ZC_BROADCAST3__M17                    : this->CGameMode::Zc_Broadcast3__m17(buf); break;
//		case HEADER_ZC_BROADCAST3__M18                    : this->CGameMode::Zc_Broadcast3__m18(buf); break;
//		case HEADER_ZC_BROADCAST3__M19                    : this->CGameMode::Zc_Broadcast3__m19(buf); break;
//		case HEADER_ZC_BROADCAST3__M20                    : this->CGameMode::Zc_Broadcast3__m20(buf); break;
//		case HEADER_ZC_BROADCAST3__M21                    : this->CGameMode::Zc_Broadcast3__m21(buf); break;
//		case HEADER_ZC_BROADCAST3__M22                    : this->CGameMode::Zc_Broadcast3__m22(buf); break;
//		case HEADER_ZC_BROADCAST3__M23                    : this->CGameMode::Zc_Broadcast3__m23(buf); break;
//		case HEADER_ZC_BROADCAST3__M24                    : this->CGameMode::Zc_Broadcast3__m24(buf); break;
//		case HEADER_ZC_BROADCAST3__M25                    : this->CGameMode::Zc_Broadcast3__m25(buf); break;
//		case HEADER_ZC_BROADCAST3__M26                    : this->CGameMode::Zc_Broadcast3__m26(buf); break;
//		case HEADER_ZC_BROADCAST3__M27                    : this->CGameMode::Zc_Broadcast3__m27(buf); break;
//		case HEADER_ZC_BROADCAST3__M28                    : this->CGameMode::Zc_Broadcast3__m28(buf); break;
//		case HEADER_ZC_BROADCAST3__M29                    : this->CGameMode::Zc_Broadcast3__m29(buf); break;
//		case HEADER_ZC_BROADCAST3__M30                    : this->CGameMode::Zc_Broadcast3__m30(buf); break;
//		case HEADER_ZC_BROADCAST3__M31                    : this->CGameMode::Zc_Broadcast3__m31(buf); break;
//		case HEADER_ZC_BROADCAST3__M32                    : this->CGameMode::Zc_Broadcast3__m32(buf); break;
//		case HEADER_ZC_BROADCAST3__M33                    : this->CGameMode::Zc_Broadcast3__m33(buf); break;
//		case HEADER_ZC_BROADCAST3__M34                    : this->CGameMode::Zc_Broadcast3__m34(buf); break;
//		case HEADER_ZC_BROADCAST3__M35                    : this->CGameMode::Zc_Broadcast3__m35(buf); break;
//		case HEADER_ZC_BROADCAST3__M36                    : this->CGameMode::Zc_Broadcast3__m36(buf); break;
//		case HEADER_ZC_BROADCAST3__M37                    : this->CGameMode::Zc_Broadcast3__m37(buf); break;
//		case HEADER_ZC_BROADCAST3__M38                    : this->CGameMode::Zc_Broadcast3__m38(buf); break;
//		case HEADER_ZC_BROADCAST3__M39                    : this->CGameMode::Zc_Broadcast3__m39(buf); break;
//		case HEADER_ZC_BROADCAST3__M40                    : this->CGameMode::Zc_Broadcast3__m40(buf); break;
//		case HEADER_ZC_BROADCAST3__M41                    : this->CGameMode::Zc_Broadcast3__m41(buf); break;
		case HEADER_ZC_SKILL_POSTDELAY                    : this->CGameMode::Zc_Skill_Postdelay(buf); break;
		case HEADER_ZC_SKILL_POSTDELAY_LIST               : this->CGameMode::Zc_Skill_Postdelay_List(buf); break;
		case HEADER_ZC_MSG_STATE_CHANGE2                  : this->CGameMode::Zc_Msg_State_Change2(buf); break;
		case HEADER_ZC_MILLENNIUMSHIELD                   : this->CGameMode::Zc_MillenniumShield(buf); break;
		case HEADER_ZC_SKILLINFO_DELETE                   : this->CGameMode::Zc_Skillinfo_Delete(buf); break;
		case HEADER_ZC_SKILL_SELECT_REQUEST               : this->CGameMode::Zc_Skill_Select_Request(buf); break;
		case HEADER_ZC_QUEST_NOTIFY_EFFECT                : this->CGameMode::Zc_Quest_Notify_Effect(buf); break;
		case HEADER_ZC_REQ_GROUPINFO_CHANGE_V2            : this->CGameMode::Zc_Req_Groupinfo_Change_V2(buf); break;
		case HEADER_ZC_SHORTCUT_KEY_LIST_V2               : this->CGameMode::Zc_ShortCut_Key_List(buf); break;
		case HEADER_ZC_HO_PAR_CHANGE                      : this->CGameMode::Zc_Ho_Par_Change(buf); break;
		case HEADER_ZC_SEEK_PARTY                         : this->CGameMode::Zc_Seek_Party(buf); break;
		case HEADER_ZC_SKILLINFO_UPDATE2                  : this->CGameMode::Zc_Skillinfo_Update2(buf); break;
		case HEADER_ZC_MSG_VALUE                          : this->CGameMode::Zc_Msg_Value(buf); break;
		case HEADER_ZC_ITEMLISTWIN_OPEN                   : this->CGameMode::Zc_ItemListWin_Open(buf); break;
		case HEADER_ZC_MSG_SKILL                          : this->CGameMode::Zc_Msg_Skill(buf); break;
		case HEADER_ZC_NOTIFY_EXP                         : this->CGameMode::Zc_Notify_Exp(buf); break;
		case HEADER_ZC_NOTIFY_MOVEENTRY7                  : this->CGameMode::Zc_Notify_Moveentry4(buf); break;
		case HEADER_ZC_NOTIFY_NEWENTRY5                   : this->CGameMode::Zc_Notify_Newentry5(buf); break;
		case HEADER_ZC_NOTIFY_STANDENTRY5                 : this->CGameMode::Zc_Notify_Standentry5(buf); break;
		case HEADER_ZC_DELETE_ITEM_FROM_BODY              : this->CGameMode::Zc_Delete_Item_From_Body(buf); break;
		case HEADER_ZC_USESKILL_ACK2                      : this->CGameMode::Zc_useskill_ack(buf, TRUE); break;
		case HEADER_ZC_CHANGE_GROUP_MASTER                : this->CGameMode::Zc_Change_Group_Master(buf); break;
		case HEADER_ZC_BROADCASTING_SPECIAL_ITEM_OBTAIN   : this->CGameMode::Zc_Broadcasting_Special_Item_Obtain(buf); break;
		case HEADER_ZC_PLAY_NPC_BGM                       : this->CGameMode::Zc_Play_Npc_Bgm(buf); break;
		case HEADER_ZC_DEFINE_CHECK                       : this->CGameMode::Zc_Define_Check(buf); break;
		case HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC2       : this->CGameMode::Zc_pc_purchase_itemlist_frommc(buf); break;
		case HEADER_ZC_PARTY_BOOKING_ACK_REGISTER         : this->CGameMode::Zc_Party_Booking_Ack_Register(buf); break;
		case HEADER_ZC_PARTY_BOOKING_ACK_SEARCH           : this->CGameMode::Zc_Party_Booking_Ack_Search(buf); break;
		case HEADER_ZC_PARTY_BOOKING_ACK_DELETE           : this->CGameMode::Zc_Party_Booking_Ack_Delete(buf); break;
		case HEADER_ZC_PARTY_BOOKING_NOTIFY_INSERT        : this->CGameMode::Zc_Party_Booking_Notify_Insert(buf); break;
		case HEADER_ZC_PARTY_BOOKING_NOTIFY_UPDATE        : this->CGameMode::Zc_Party_Booking_Notify_Update(buf); break;
		case HEADER_ZC_PARTY_BOOKING_NOTIFY_DELETE        : this->CGameMode::Zc_Party_Booking_Notify_Delete(buf); break;
		case HEADER_ZC_NOTIFY_HP_TO_GROUPM_R2             : this->CGameMode::Zc_Notify_Hp_To_Groupm_R2(buf); break;
		case HEADER_ZC_ADD_EXCHANGE_ITEM2                 : this->CGameMode::Zc_Add_Exchange_Item2(buf); break;
		case HEADER_ZC_OPEN_BUYING_STORE                  : this->CGameMode::Zc_Open_Buying_Store(buf); break;
		case HEADER_ZC_FAILED_OPEN_BUYING_STORE_TO_BUYER  : this->CGameMode::Zc_Failed_Open_Buying_Store_To_Buyer(buf); break;
		case HEADER_ZC_MYITEMLIST_BUYING_STORE            : this->CGameMode::Zc_Myitemlist_Buying_Store(buf); break;
		case HEADER_ZC_BUYING_STORE_ENTRY                 : this->CGameMode::Zc_Buying_Store_Entry(buf); break;
		case HEADER_ZC_DISAPPEAR_BUYING_STORE_ENTRY       : this->CGameMode::Zc_Disappear_Buying_Store_Entry(buf); break;
		case HEADER_ZC_ACK_ITEMLIST_BUYING_STORE          : this->CGameMode::Zc_Ack_Itemlist_Buying_Store(buf); break;
		case HEADER_ZC_FAILED_TRADE_BUYING_STORE_TO_BUYER : this->CGameMode::Zc_Failed_Trade_Buying_Store_To_Buyer(buf); break;
		case HEADER_ZC_UPDATE_ITEM_FROM_BUYING_STORE      : this->CGameMode::Zc_Update_Item_From_Buying_Store(buf); break;
		case HEADER_ZC_ITEM_DELETE_BUYING_STORE           : this->CGameMode::Zc_Item_Delete_Buying_Store(buf); break;
		case HEADER_ZC_EL_INIT                            : this->CGameMode::Zc_El_Init(buf); break;
		case HEADER_ZC_EL_PAR_CHANGE                      : this->CGameMode::Zc_El_Par_Change(buf); break;
		case HEADER_ZC_BROADCAST4                         : this->CGameMode::Zc_Broadcast4(buf); break;
		case HEADER_ZC_FAILED_TRADE_BUYING_STORE_TO_SELLER: this->CGameMode::Zc_Failed_Trade_Buying_Store_To_Seller(buf); break;
		default:
			CRagConnection::instanceR().CConnection::ResetQueue();
		break;
		}
	}
}


void CGameMode::Zc_Accept_Enter(const char* buf)
{
	const PACKET_ZC_ACCEPT_ENTER& packet = *reinterpret_cast<const PACKET_ZC_ACCEPT_ENTER*>(buf);

	g_session.CSession::SetServerTime(packet.startTime);

	int x, y, dir;
	DecodePosDir(packet.PosDir, x, y, dir);
	g_session.CSession::SetPlayerPosDir(x, y, dir);

	char curMap[35];
	sprintf(curMap, "%s.rsw", g_session.m_curMap);
	g_modeMgr.CModeMgr::Switch(MT_GAME, curMap);

	CRagConnection::instanceR().CConnection::SetBlock(false);

	if( g_pingLog )
	{
		FILE* fp = fopen("PingLog.txt", "at");
		if( fp != NULL )
		{
			time_t currentTime;
			time(&currentTime);
			fprintf(fp, "\n");
			fprintf(fp, "server:%s\n", g_session.m_selectedServerName.c_str());
			fprintf(fp, "ip:%s\n", g_zoneServerAddr.ip);
			fprintf(fp, "map:%s.gat\n", g_session.m_curMap);
			fprintf(fp, "time:%s\n\n", ctime(&currentTime));
			fclose(fp);
		}

		g_pingLogList.clear();
		g_pingLogStart = 0;
	}
}


void CGameMode::Zc_Notify_Standentry(const char* buf)
{
	const PACKET_ZC_NOTIFY_STANDENTRY& packet = *reinterpret_cast<const PACKET_ZC_NOTIFY_STANDENTRY*>(buf);

	STANDENTRYSTRUCT s;
	s.job = packet.job;
	s.speed = packet.speed;
	s.sex = packet.sex;
	s.ySize = packet.ySize;
	s.weapon = packet.weapon;
	s.xSize = packet.xSize;
	s.head = packet.head;
	s.state = packet.state;
	s.accessory = packet.accessory;
	s.bodyState = packet.bodyState;
	s.healthState = packet.healthState;
	s.isPKModeON = packet.isPKModeON;
	s.effectState = packet.effectState;
	s.accessory2 = packet.accessory2;
	s.shield = packet.shield;
	s.headpalette = packet.headpalette;
	s.accessory3 = packet.accessory3;
	s.headDir = packet.headDir;
	s.bodypalette = packet.bodypalette;
	s.guildEmblemVersion = packet.GEmblemVer;
	s.GID = packet.GID;
	s.guildId = packet.GUID;
	s.virtue = packet.virtue;
	s.honor = packet.honor;
	DecodePosDir(packet.PosDir, s.x, s.y, s.dir);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor == NULL )
	{
		if( packet.job >= JT_WARPNPC && packet.job < JT_2004_JOB_BEGIN || g_session.CSession::IsMerOrHomun(packet.job) || packet.objecttype == NPC_MERSOL_TYPE )
		{
			if( g_session.CSession::IsMyHomunGID(packet.GID) )
				g_session.m_homunAlive = TRUE;

			if( g_session.CSession::IsMyMerGID(packet.GID) )
				g_session.m_merAlive = TRUE;

			actor = this->CGameMode::NewNpc(packet.job);
			s.sex = SEX_FEMALE;
		}
		else
		{
			actor = new CPc();
		}

		if( actor != NULL && s.head == 100 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		actor->m_objectType = packet.objecttype;

		m_world->m_gameObjectList.push_back(actor);
		m_world->m_actorList.push_back(actor);

		if( actor != NULL )
		{
			actor->SendMsg(NULL, AM_4, (int)&s, 0, 0);

			if( g_session.CSession::IsSiegeMode() && s.head != 100 && actor->m_emblemWnd == NULL )
			{
				if( g_session.CSession::IsPc(actor->CGameActor::GetJob()) )
					this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
				else
				if( g_session.CSession::IsGuardian(actor->CGameActor::GetJob()) )
					this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
			}

			if( actor->CGameActor::GetJob() > JT_WARPNPC && actor->CGameActor::GetJob() < JT_2004_JOB_BEGIN )
			{
				int GDID = (packet.accessory2 << 16) | packet.accessory3;
				int emblemVer = packet.shield;

				if( GDID != 0 )
					actor->SetGuildInfo(GDID, emblemVer);
			}
		}
	}
	else
	{
		if( actor->CGameActor::GetJob() > JT_WARPNPC && actor->CGameActor::GetJob() < JT_2004_JOB_BEGIN )
		{
			int GDID = (packet.accessory2 << 16) | packet.accessory3;
			int emblemVer = packet.shield;

			if( GDID != 0 && actor->GetGdid() == 0 )
				actor->SetGuildInfo(GDID, emblemVer);
		}

		if( s.head == 100 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		actor->SendMsg(NULL, AM_3, (int)&s, 0, 0);

		if( g_session.CSession::IsSiegeMode() && s.head != 100 && actor->m_emblemWnd == NULL )
		{
			if( g_session.CSession::IsPc(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
			else
			if( g_session.CSession::IsGuardian(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
		}
	}

	this->CGameMode::GameModeShowEFST(packet.GID, packet.effectState, packet.clevel, packet.virtue);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Newentry("CGameMode::Zc_Notify_Newentry");
void CGameMode::Zc_Notify_Newentry(const char* buf)
{
	return (this->*_Zc_Notify_Newentry)(buf);
}


void CGameMode::Zc_Notify_Actentry(const char* buf)
{
	const PACKET_ZC_NOTIFY_ACTENTRY& packet = *reinterpret_cast<const PACKET_ZC_NOTIFY_ACTENTRY*>(buf);

	// ignored
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Moveentry("CGameMode::Zc_Notify_Moveentry");
void CGameMode::Zc_Notify_Moveentry(const char* buf)
{
	return (this->*_Zc_Notify_Moveentry)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Standentry_Npc("CGameMode::Zc_Notify_Standentry_Npc");
void CGameMode::Zc_Notify_Standentry_Npc(const char* buf)
{
	return (this->*_Zc_Notify_Standentry_Npc)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Time("CGameMode::Zc_Notify_Time");
void CGameMode::Zc_Notify_Time(const char* buf)
{
	return (this->*_Zc_Notify_Time)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Vanish("CGameMode::Zc_Notify_Vanish");
void CGameMode::Zc_Notify_Vanish(const char* buf)
{
	return (this->*_Zc_Notify_Vanish)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Sc_Notify_Ban("CGameMode::Sc_Notify_Ban");
void CGameMode::Sc_Notify_Ban(const char* buf)
{
	return (this->*_Sc_Notify_Ban)(buf);
}


void CGameMode::Zc_Accept_Quit(const char* buf)
{
	const PACKET_ZC_ACCEPT_QUIT& packet = *reinterpret_cast<const PACKET_ZC_ACCEPT_QUIT*>(buf);

	// ignored
}


void CGameMode::Zc_Refuse_Quit(const char* buf)
{
	const PACKET_ZC_REFUSE_QUIT& packet = *reinterpret_cast<const PACKET_ZC_REFUSE_QUIT*>(buf);

	// ignored
}


void CGameMode::Zc_Notify_Move(const char* buf)
{
	const PACKET_ZC_NOTIFY_MOVE& packet = *reinterpret_cast<const PACKET_ZC_NOTIFY_MOVE*>(buf);

	MOVESTRUCT ms;
	ms.startTime = packet.moveStartTime;
	DecodeSrcDst(packet.MoveData, ms.sx, ms.sy, ms.dx, ms.dy, ms.cellX, ms.cellY);

	g_session.CSession::UpdateServerTime(ms.startTime);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor != NULL )
		actor->SendMsg(NULL, AM_0, (int)&ms, 0, 0);

}


void CGameMode::Zc_Notify_Playermove(const char* buf)
{
	const PACKET_ZC_NOTIFY_PLAYERMOVE& packet = *reinterpret_cast<const PACKET_ZC_NOTIFY_PLAYERMOVE*>(buf);

	MOVESTRUCT ms;
	ms.startTime = packet.moveStartTime;
	DecodeSrcDst(packet.MoveData, ms.sx, ms.sy, ms.dx, ms.dy, ms.cellX, ms.cellY);

	g_session.CSession::UpdateServerTime(ms.startTime);

	m_world->m_player->SendMsg(NULL, AM_0, (int)&ms, 0, 0);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Stopmove("CGameMode::Zc_Stopmove");
void CGameMode::Zc_Stopmove(const char* buf)
{
	return (this->*_Zc_Stopmove)(buf);
}


void CGameMode::Zc_Notify_Act(unsigned long GID, unsigned long targetGID, unsigned long startTime, int attackMT, int attackedMT, int damage, short count, unsigned char action, int leftDamage)
{
	if( damage == -30000 )
		return;

	ACTSTRUCT as;
	as.damage = damage;
	as.leftDamage = leftDamage;
	as.startTime = startTime;
	as.targetGID = targetGID;
	as.tCellX = -1;
	as.tCellY = -1;
	as.attackMT = attackMT;
	as.count = count;
	as.action = action;
	as.attackedMT = attackedMT;

	if( attackMT == 0.0 )
		as.attackMT = 1440;

	if( attackedMT == 0.0 && !g_session.CSession::IsAttack(action) )
		as.attackedMT = 1440;

	if( GID == g_session.m_aid )
	{
		CGameActor* player = m_world->m_player;

		if( player->m_stateId == 0
		&&  player->CGameActor::GetTargetGid() != targetGID
		&&  action != ACTION_ITEMPICKUP && action != ACTION_SIT && action != ACTION_STAND
		&&  m_world->CWorld::GetGameActorByAID(g_session.m_petGID) != 0 )
		{
			int nPetHungry = g_session.CSession::GetPetHungryState(g_session.m_petHungry);
			int nPetFriendly = g_session.CSession::GetPetFriendlyState(g_session.m_petFriendly);
 			int talkNum1 = g_session.m_petEmotionTable[nPetHungry][nPetFriendly][1];
			if( rand() % 100 < 25 )
			{
				int talkNum2 = g_session.CSession::GetPetTalkNumber(g_session.m_petJob, 1, nPetHungry);
				this->SendMsg(148, talkNum2, 0, 0);
				this->SendMsg(148, talkNum1, 0, 0);
			}
		}

		player->SendMsg(NULL, AM_11, (int)&as, 0, 0);
	}
	else
	{
		CGameActor* actor = m_world->CWorld::GetGameActorByAID(GID);
		if( actor == NULL )
			return;

		if( actor->m_stateId == 0
		&&  actor->CGameActor::GetTargetGid() != targetGID
		&&  action != ACTION_ITEMPICKUP && action != ACTION_SIT && action != ACTION_STAND )
		{
			char speak[256];
			g_session.CSession::GetMonsterTalkInfo(actor->CGameActor::GetJob(), 0, 0, speak, GID);

			if( strcmp(speak, "") != 0 )
			{
				actor->SendMsg(NULL, AM_7, (int)speak, 0, 0);
				if( g_session.m_isNoTalkMsg != TRUE && g_session.m_isNoTalkMsg2 != TRUE )
					g_windowMgr.UIWindowMgr::SendMsg(1, (int)speak, 0xFAFAFAu, 0, 0);
			}
		}

		actor->SendMsg(NULL, AM_11, (int)&as, 0, 0);
	}
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Act_Position("CGameMode::Zc_Notify_Act_Position");
void CGameMode::Zc_Notify_Act_Position(const char* buf)
{
	return (this->*_Zc_Notify_Act_Position)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Chat("CGameMode::Zc_Notify_Chat");
void CGameMode::Zc_Notify_Chat(const char* buf)
{
	return (this->*_Zc_Notify_Chat)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Playerchat("CGameMode::Zc_Notify_Playerchat");
void CGameMode::Zc_Notify_Playerchat(const char* buf)
{
	return (this->*_Zc_Notify_Playerchat)(buf);
}


void CGameMode::Zc_Npcack_Mapmove(const char* buf)
{
	const PACKET_ZC_NPCACK_MAPMOVE& packet = *reinterpret_cast<const PACKET_ZC_NPCACK_MAPMOVE*>(buf);

	g_session.m_posX = packet.xPos;
	g_session.m_posY = packet.yPos;

	char mapName[16+1];
	memcpy(mapName, packet.mapName, 16); mapName[countof(mapName)-1] = '\0';
	Trace("mapmove mapname == %s", mapName);

	mystd::string curMap = mapName;
	curMap.resize(curMap.size() - 4);

	if( strcmp(curMap.c_str(), g_session.m_curMap) != 0 )
	{// map change
		strcpy(g_session.m_curMap, curMap.c_str());
		curMap.append(".rsw");
		Trace("curMap == %s", curMap.c_str());
		g_modeMgr.CModeMgr::Switch(1, curMap.c_str());

		UIWaitWnd* wnd = (UIWaitWnd*)g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
		wnd->UIWaitWnd::SetMsg(MsgStr(MSI_PLEASE_BE_PATIENT), 17, 1);
		g_windowMgr.m_modalResult = 123;
	}
	else
	{// same map
		this->CGameMode::RemoveGameActorAllAndMake();
		this->CGameMode::Initialize();
		this->CMode::RunFadeOut(FALSE);
	}
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Npcack_Servermove("CGameMode::Zc_Npcack_Servermove");
void CGameMode::Zc_Npcack_Servermove(const char* buf)
{
	return (this->*_Zc_Npcack_Servermove)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Npcack_Enable("CGameMode::Zc_Npcack_Enable");
void CGameMode::Zc_Npcack_Enable(const char* buf)
{
	return (this->*_Zc_Npcack_Enable)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Reqname("CGameMode::Zc_Ack_Reqname");
void CGameMode::Zc_Ack_Reqname(const char* buf)
{
	return (this->*_Zc_Ack_Reqname)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Whisper("CGameMode::Zc_Whisper");
void CGameMode::Zc_Whisper(const char* buf)
{
	return (this->*_Zc_Whisper)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Whisper("CGameMode::Zc_Ack_Whisper");
void CGameMode::Zc_Ack_Whisper(const char* buf)
{
	return (this->*_Zc_Ack_Whisper)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Broadcast("CGameMode::Zc_Broadcast");
void CGameMode::Zc_Broadcast(const char* buf)
{
	const PACKET_ZC_BROADCAST& packet = *reinterpret_cast<const PACKET_ZC_BROADCAST*>(buf);
	return (this->*_Zc_Broadcast)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Change_Direction("CGameMode::Zc_Change_Direction");
void CGameMode::Zc_Change_Direction(const char* buf)
{
	return (this->*_Zc_Change_Direction)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Entry("CGameMode::Zc_Item_Entry");
void CGameMode::Zc_Item_Entry(const char* buf)
{
	return (this->*_Zc_Item_Entry)(buf);
}


void CGameMode::Zc_Item_Fall_Entry(const char* buf)
{
	const PACKET_ZC_ITEM_FALL_ENTRY& packet = *reinterpret_cast<const PACKET_ZC_ITEM_FALL_ENTRY*>(buf);

	ITEMSTANDENTRYSTRUCT s = {};
	_itoa(packet.ITID, s.name, 10);
	s.ITAID = packet.ITAID;
	s.x = packet.xPos;
	s.y = packet.yPos;
	s.subX = packet.subX;
	s.subY = packet.subY;
	s.isJumpEntry = TRUE;
	s.count = packet.count;
	s.isIdentified = packet.IsIdentified;

	CItem* item = m_world->CWorld::GetItemByAID(packet.ITAID);
	if ( item == NULL )
	{
		item = new CItem();
		m_world->m_gameObjectList.push_back(item);
		m_world->m_itemList.push_back(item);
	}

	item->SendMsg(NULL, AM_4, (int)&s, 0, 0);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Pickup_Ack("CGameMode::Zc_Item_Pickup_Ack");
void CGameMode::Zc_Item_Pickup_Ack(const char* buf)
{
	return (this->*_Zc_Item_Pickup_Ack)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Disappear("CGameMode::Zc_Item_Disappear");
void CGameMode::Zc_Item_Disappear(const char* buf)
{
	return (this->*_Zc_Item_Disappear)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Normal_Itemlist("CGameMode::Zc_Normal_Itemlist");
void CGameMode::Zc_Normal_Itemlist(const char* buf)
{
	return (this->*_Zc_Normal_Itemlist)(buf);
}


void CGameMode::Zc_Equipment_Itemlist(const char* buf)
{
	PACKET_ZC_EQUIPMENT_ITEMLIST& packet = *(PACKET_ZC_EQUIPMENT_ITEMLIST*)buf;
	int count = (packet.Length - sizeof(packet)) / sizeof(PACKET_ZC_EQUIPMENT_ITEMLIST::ITEM);

	g_session.CSession::ClearEquipItemInInventory();
	g_session.CSession::ClearEquipItem();

	for( int i = 0; i < count; ++i )
	{
		PACKET_ZC_EQUIPMENT_ITEMLIST::ITEM& item = packet.Item[i];

		ITEM_INFO itemInfo;
		itemInfo.m_itemType      = item.type;
		itemInfo.m_location      = item.location;
		itemInfo.m_num           = 1;
		itemInfo.m_itemIndex     = item.index;
		itemInfo.m_wearLocation  = item.wearLocation;
		itemInfo.m_slot[0]       = item.slot.info[0];
		itemInfo.m_slot[1]       = item.slot.info[1];
		itemInfo.m_slot[2]       = item.slot.info[2];
		itemInfo.m_slot[3]       = item.slot.info[3];
		itemInfo.ITEM_INFO::SetItemId(item.ITID);
		itemInfo.m_isIdentified  = item.IsIdentified;
		itemInfo.m_isDamaged     = ( item.isDamaged != 0 );
		itemInfo.m_refiningLevel = item.refiningLevel;

		if( g_session.CSession::IsPetEgg(atoi(itemInfo.m_itemName.c_str())) && itemInfo.m_isDamaged )
			g_session.m_petEggIndex = itemInfo.m_itemIndex;

		if( itemInfo.m_wearLocation != 0 )
		{
			g_session.CSession::AddEquipItem(&itemInfo);
		}
		else
		{
			g_session.CSession::AddItem(&itemInfo);
			g_session.CSession::SetItem(&itemInfo);
		}
	}
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Store_Normal_Itemlist("CGameMode::Zc_Store_Normal_Itemlist");
void CGameMode::Zc_Store_Normal_Itemlist(const char* buf)
{
	return (this->*_Zc_Store_Normal_Itemlist)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Store_Equipment_Itemlist("CGameMode::Zc_Store_Equipment_Itemlist");
void CGameMode::Zc_Store_Equipment_Itemlist(const char* buf)
{
	return (this->*_Zc_Store_Equipment_Itemlist)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Use_Item_Ack("CGameMode::Zc_Use_Item_Ack");
void CGameMode::Zc_Use_Item_Ack(const char* buf)
{
	return (this->*_Zc_Use_Item_Ack)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Wear_Equip_Ack("CGameMode::Zc_Req_Wear_Equip_Ack");
void CGameMode::Zc_Req_Wear_Equip_Ack(const char* buf)
{
	return (this->*_Zc_Req_Wear_Equip_Ack)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Takeoff_Equip_Ack("CGameMode::Zc_Req_Takeoff_Equip_Ack");
void CGameMode::Zc_Req_Takeoff_Equip_Ack(const char* buf)
{
	return (this->*_Zc_Req_Takeoff_Equip_Ack)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Throw_Ack("CGameMode::Zc_Item_Throw_Ack");
void CGameMode::Zc_Item_Throw_Ack(const char* buf)
{
	return (this->*_Zc_Item_Throw_Ack)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Par_Change("CGameMode::Zc_Par_Change");
void CGameMode::Zc_Par_Change(const char* buf)
{
	return (this->*_Zc_Par_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Longpar_Change("CGameMode::Zc_Longpar_Change");
void CGameMode::Zc_Longpar_Change(const char* buf)
{
	return (this->*_Zc_Longpar_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Restart_Ack("CGameMode::Zc_Restart_Ack");
void CGameMode::Zc_Restart_Ack(const char* buf)
{
	return (this->*_Zc_Restart_Ack)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Say_Dialog("CGameMode::Zc_Say_Dialog");
void CGameMode::Zc_Say_Dialog(const char* buf)
{
	return (this->*_Zc_Say_Dialog)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Wait_Dialog("CGameMode::Zc_Wait_Dialog");
void CGameMode::Zc_Wait_Dialog(const char* buf)
{
	return (this->*_Zc_Wait_Dialog)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Close_Dialog("CGameMode::Zc_Close_Dialog");
void CGameMode::Zc_Close_Dialog(const char* buf)
{
	return (this->*_Zc_Close_Dialog)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Menu_List("CGameMode::Zc_Menu_List");
void CGameMode::Zc_Menu_List(const char* buf)
{
	return (this->*_Zc_Menu_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Status_Change_Ack("CGameMode::Zc_Status_Change_Ack");
void CGameMode::Zc_Status_Change_Ack(const char* buf)
{
	return (this->*_Zc_Status_Change_Ack)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Status("CGameMode::Zc_Status");
void CGameMode::Zc_Status(const char* buf)
{
	return (this->*_Zc_Status)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Status_Change("CGameMode::Zc_Status_Change");
void CGameMode::Zc_Status_Change(const char* buf)
{
	return (this->*_Zc_Status_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Emotion("CGameMode::Zc_Emotion");
void CGameMode::Zc_Emotion(const char* buf)
{
	return (this->*_Zc_Emotion)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_User_Count("CGameMode::Zc_User_Count");
void CGameMode::Zc_User_Count(const char* buf)
{
	return (this->*_Zc_User_Count)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Sprite_Change("CGameMode::Zc_Sprite_Change");
void CGameMode::Zc_Sprite_Change(const char* buf)
{
	return (this->*_Zc_Sprite_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Select_Dealtype("CGameMode::Zc_Select_Dealtype");
void CGameMode::Zc_Select_Dealtype(const char* buf)
{
	return (this->*_Zc_Select_Dealtype)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Purchase_Itemlist("CGameMode::Zc_Pc_Purchase_Itemlist");
void CGameMode::Zc_Pc_Purchase_Itemlist(const char* buf)
{
	return (this->*_Zc_Pc_Purchase_Itemlist)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Sell_Itemlist("CGameMode::Zc_Pc_Sell_Itemlist");
void CGameMode::Zc_Pc_Sell_Itemlist(const char* buf)
{
	return (this->*_Zc_Pc_Sell_Itemlist)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Purchase_Result("CGameMode::Zc_Pc_Purchase_Result");
void CGameMode::Zc_Pc_Purchase_Result(const char* buf)
{
	return (this->*_Zc_Pc_Purchase_Result)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Sell_Result("CGameMode::Zc_Pc_Sell_Result");
void CGameMode::Zc_Pc_Sell_Result(const char* buf)
{
	return (this->*_Zc_Pc_Sell_Result)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Disconnect_Character("CGameMode::Zc_Ack_Disconnect_Character");
void CGameMode::Zc_Ack_Disconnect_Character(const char* buf)
{
	return (this->*_Zc_Ack_Disconnect_Character)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Setting_Whisper_Pc("CGameMode::Zc_Setting_Whisper_Pc");
void CGameMode::Zc_Setting_Whisper_Pc(const char* buf)
{
	return (this->*_Zc_Setting_Whisper_Pc)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Setting_Whisper_State("CGameMode::Zc_Setting_Whisper_State");
void CGameMode::Zc_Setting_Whisper_State(const char* buf)
{
	return (this->*_Zc_Setting_Whisper_State)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Whisper_List("CGameMode::Zc_Whisper_List");
void CGameMode::Zc_Whisper_List(const char* buf)
{
	return (this->*_Zc_Whisper_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Create_Chatroom("CGameMode::Zc_Ack_Create_Chatroom");
void CGameMode::Zc_Ack_Create_Chatroom(const char* buf)
{
	return (this->*_Zc_Ack_Create_Chatroom)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Room_Newentry("CGameMode::Zc_Room_Newentry");
void CGameMode::Zc_Room_Newentry(const char* buf)
{
	return (this->*_Zc_Room_Newentry)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Destroy_Room("CGameMode::Zc_Destroy_Room");
void CGameMode::Zc_Destroy_Room(const char* buf)
{
	return (this->*_Zc_Destroy_Room)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Refuse_Enter_Room("CGameMode::Zc_Refuse_Enter_Room");
void CGameMode::Zc_Refuse_Enter_Room(const char* buf)
{
	return (this->*_Zc_Refuse_Enter_Room)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Enter_Room("CGameMode::Zc_Enter_Room");
void CGameMode::Zc_Enter_Room(const char* buf)
{
	return (this->*_Zc_Enter_Room)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Member_Newentry("CGameMode::Zc_Member_Newentry");
void CGameMode::Zc_Member_Newentry(const char* buf)
{
	return (this->*_Zc_Member_Newentry)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Member_Exit("CGameMode::Zc_Member_Exit");
void CGameMode::Zc_Member_Exit(const char* buf)
{
	return (this->*_Zc_Member_Exit)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Change_Chatroom("CGameMode::Zc_Change_Chatroom");
void CGameMode::Zc_Change_Chatroom(const char* buf)
{
	return (this->*_Zc_Change_Chatroom)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Role_Change("CGameMode::Zc_Role_Change");
void CGameMode::Zc_Role_Change(const char* buf)
{
	return (this->*_Zc_Role_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Exchange_Item("CGameMode::Zc_Req_Exchange_Item");
void CGameMode::Zc_Req_Exchange_Item(const char* buf)
{
	return (this->*_Zc_Req_Exchange_Item)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Exchange_Item("CGameMode::Zc_Ack_Exchange_Item");
void CGameMode::Zc_Ack_Exchange_Item(const char* buf)
{
	return (this->*_Zc_Ack_Exchange_Item)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Add_Exchange_Item("CGameMode::Zc_Ack_Add_Exchange_Item");
void CGameMode::Zc_Ack_Add_Exchange_Item(const char* buf)
{
	return (this->*_Zc_Ack_Add_Exchange_Item)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Conclude_Exchange_Item("CGameMode::Zc_Conclude_Exchange_Item");
void CGameMode::Zc_Conclude_Exchange_Item(const char* buf)
{
	return (this->*_Zc_Conclude_Exchange_Item)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cancel_Exchange_Item("CGameMode::Zc_Cancel_Exchange_Item");
void CGameMode::Zc_Cancel_Exchange_Item(const char* buf)
{
	return (this->*_Zc_Cancel_Exchange_Item)(buf);
}



hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Exec_Exchange_Item("CGameMode::Zc_Exec_Exchange_Item");
void CGameMode::Zc_Exec_Exchange_Item(const char* buf)
{
	return (this->*_Zc_Exec_Exchange_Item)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Exchangeitem_Undo("CGameMode::Zc_Exchangeitem_Undo");
void CGameMode::Zc_Exchangeitem_Undo(const char* buf)
{
	return (this->*_Zc_Exchangeitem_Undo)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Storeitem_Countinfo("CGameMode::Zc_Notify_Storeitem_Countinfo");
void CGameMode::Zc_Notify_Storeitem_Countinfo(const char* buf)
{
	return (this->*_Zc_Notify_Storeitem_Countinfo)(buf);
}


void CGameMode::Zc_Add_Item_To_Store(const char* buf)
{
	const PACKET_ZC_ADD_ITEM_TO_STORE& packet = *reinterpret_cast<const PACKET_ZC_ADD_ITEM_TO_STORE*>(buf);

	ITEM_INFO incItem;
	incItem.m_itemIndex = packet.index;
	incItem.m_num = packet.count;
	incItem.ITEM_INFO::SetItemId(packet.ITID);
	incItem.m_isIdentified = packet.IsIdentified;
	incItem.m_isDamaged = packet.IsDamaged;
	incItem.m_refiningLevel = packet.refiningLevel;
	incItem.m_slot[0] = packet.slot.info[0];
	incItem.m_slot[1] = packet.slot.info[1];
	incItem.m_slot[2] = packet.slot.info[2];
	incItem.m_slot[3] = packet.slot.info[3];

	g_session.CSession::AddStoreItem(&incItem);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Delete_Item_From_Store("CGameMode::Zc_Delete_Item_From_Store");
void CGameMode::Zc_Delete_Item_From_Store(const char* buf)
{
	return (this->*_Zc_Delete_Item_From_Store)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Close_Store("CGameMode::Zc_Close_Store");
void CGameMode::Zc_Close_Store(const char* buf)
{
	return (this->*_Zc_Close_Store)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Make_Group("CGameMode::Zc_Ack_Make_Group");
void CGameMode::Zc_Ack_Make_Group(const char* buf)
{
	return (this->*_Zc_Ack_Make_Group)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Group_List("CGameMode::Zc_Group_List");
void CGameMode::Zc_Group_List(const char* buf)
{
	return (this->*_Zc_Group_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Req_Join_Group("CGameMode::Zc_Ack_Req_Join_Group");
void CGameMode::Zc_Ack_Req_Join_Group(const char* buf)
{
	return (this->*_Zc_Ack_Req_Join_Group)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Join_Group("CGameMode::Zc_Req_Join_Group");
void CGameMode::Zc_Req_Join_Group(const char* buf)
{
	return (this->*_Zc_Req_Join_Group)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_groupinfo_change("CGameMode::Zc_groupinfo_change");
void CGameMode::Zc_groupinfo_change(const char* buf)
{
	return (this->*_Zc_groupinfo_change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Member_To_Group("CGameMode::Zc_Add_Member_To_Group");
void CGameMode::Zc_Add_Member_To_Group(const char* buf)
{
	return (this->*_Zc_Add_Member_To_Group)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Delete_Member_From_Group("CGameMode::Zc_Delete_Member_From_Group");
void CGameMode::Zc_Delete_Member_From_Group(const char* buf)
{
	return (this->*_Zc_Delete_Member_From_Group)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Hp_To_Groupm("CGameMode::Zc_Notify_Hp_To_Groupm");
void CGameMode::Zc_Notify_Hp_To_Groupm(const char* buf)
{
	return (this->*_Zc_Notify_Hp_To_Groupm)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Position_To_Groupm("CGameMode::Zc_Notify_Position_To_Groupm");
void CGameMode::Zc_Notify_Position_To_Groupm(const char* buf)
{
	return (this->*_Zc_Notify_Position_To_Groupm)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Chat_Party("CGameMode::Zc_Notify_Chat_Party");
void CGameMode::Zc_Notify_Chat_Party(const char* buf)
{
	return (this->*_Zc_Notify_Chat_Party)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mvp_Getting_Item("CGameMode::Zc_Mvp_Getting_Item");
void CGameMode::Zc_Mvp_Getting_Item(const char* buf)
{
	return (this->*_Zc_Mvp_Getting_Item)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mvp_Getting_Special_Exp("CGameMode::Zc_Mvp_Getting_Special_Exp");
void CGameMode::Zc_Mvp_Getting_Special_Exp(const char* buf)
{
	return (this->*_Zc_Mvp_Getting_Special_Exp)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mvp("CGameMode::Zc_Mvp");
void CGameMode::Zc_Mvp(const char* buf)
{
	return (this->*_Zc_Mvp)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Throw_Mvpitem("CGameMode::Zc_Throw_Mvpitem");
void CGameMode::Zc_Throw_Mvpitem(const char* buf)
{
	return (this->*_Zc_Throw_Mvpitem)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skillinfo_Update("CGameMode::Zc_Skillinfo_Update");
void CGameMode::Zc_Skillinfo_Update(const char* buf)
{
	return (this->*_Zc_Skillinfo_Update)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skillinfo_List("CGameMode::Zc_Skillinfo_List");
void CGameMode::Zc_Skillinfo_List(const char* buf)
{
	return (this->*_Zc_Skillinfo_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Touseskill("CGameMode::Zc_Ack_Touseskill");
void CGameMode::Zc_Ack_Touseskill(const char* buf)
{
	return (this->*_Zc_Ack_Touseskill)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Skill("CGameMode::Zc_Add_Skill");
void CGameMode::Zc_Add_Skill(const char* buf)
{
	return (this->*_Zc_Add_Skill)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Skill("CGameMode::Zc_Notify_Skill");
void CGameMode::Zc_Notify_Skill(const char* buf)
{
	return (this->*_Zc_Notify_Skill)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Skill_Position("CGameMode::Zc_Notify_Skill_Position");
void CGameMode::Zc_Notify_Skill_Position(const char* buf)
{
	return (this->*_Zc_Notify_Skill_Position)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Groundskill("CGameMode::Zc_Notify_Groundskill");
void CGameMode::Zc_Notify_Groundskill(const char* buf)
{
	return (this->*_Zc_Notify_Groundskill)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_State_Change("CGameMode::Zc_State_Change");
void CGameMode::Zc_State_Change(const char* buf)
{
	return (this->*_Zc_State_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Use_Skill("CGameMode::Zc_Use_Skill");
void CGameMode::Zc_Use_Skill(const char* buf)
{
	return (this->*_Zc_Use_Skill)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Warplist("CGameMode::Zc_Warplist");
void CGameMode::Zc_Warplist(const char* buf)
{
	return (this->*_Zc_Warplist)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Remember_Warppoint("CGameMode::Zc_Ack_Remember_Warppoint");
void CGameMode::Zc_Ack_Remember_Warppoint(const char* buf)
{
	return (this->*_Zc_Ack_Remember_Warppoint)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Entry("CGameMode::Zc_Skill_Entry");
void CGameMode::Zc_Skill_Entry(const char* buf)
{
	return (this->*_Zc_Skill_Entry)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Disappear("CGameMode::Zc_Skill_Disappear");
void CGameMode::Zc_Skill_Disappear(const char* buf)
{
	return (this->*_Zc_Skill_Disappear)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Cartitem_Countinfo("CGameMode::Zc_Notify_Cartitem_Countinfo");
void CGameMode::Zc_Notify_Cartitem_Countinfo(const char* buf)
{
	return (this->*_Zc_Notify_Cartitem_Countinfo)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cart_Equipment_Itemlist("CGameMode::Zc_Cart_Equipment_Itemlist");
void CGameMode::Zc_Cart_Equipment_Itemlist(const char* buf)
{
	return (this->*_Zc_Cart_Equipment_Itemlist)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cart_Normal_Itemlist("CGameMode::Zc_Cart_Normal_Itemlist");
void CGameMode::Zc_Cart_Normal_Itemlist(const char* buf)
{
	return (this->*_Zc_Cart_Normal_Itemlist)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Item_To_Cart("CGameMode::Zc_Add_Item_To_Cart");
void CGameMode::Zc_Add_Item_To_Cart(const char* buf)
{
	return (this->*_Zc_Add_Item_To_Cart)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Delete_Item_From_Cart("CGameMode::Zc_Delete_Item_From_Cart");
void CGameMode::Zc_Delete_Item_From_Cart(const char* buf)
{
	return (this->*_Zc_Delete_Item_From_Cart)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cartoff("CGameMode::Zc_Cartoff");
void CGameMode::Zc_Cartoff(const char* buf)
{
	return (this->*_Zc_Cartoff)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Additem_To_Cart("CGameMode::Zc_Ack_Additem_To_Cart");
void CGameMode::Zc_Ack_Additem_To_Cart(const char* buf)
{
	return (this->*_Zc_Ack_Additem_To_Cart)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_openstore("CGameMode::Zc_openstore");
void CGameMode::Zc_openstore(const char* buf)
{
	return (this->*_Zc_openstore)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_store_entry("CGameMode::Zc_store_entry");
void CGameMode::Zc_store_entry(const char* buf)
{
	return (this->*_Zc_store_entry)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_disappear_entry("CGameMode::Zc_disappear_entry");
void CGameMode::Zc_disappear_entry(const char* buf)
{
	return (this->*_Zc_disappear_entry)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_pc_purchase_itemlist_frommc("CGameMode::Zc_pc_purchase_itemlist_frommc");
void CGameMode::Zc_pc_purchase_itemlist_frommc(const char* buf)
{
	return (this->*_Zc_pc_purchase_itemlist_frommc)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_pc_purchase_result_frommc("CGameMode::Zc_pc_purchase_result_frommc");
void CGameMode::Zc_pc_purchase_result_frommc(const char* buf)
{
	return (this->*_Zc_pc_purchase_result_frommc)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_pc_purchase_myitemlist("CGameMode::Zc_pc_purchase_myitemlist");
void CGameMode::Zc_pc_purchase_myitemlist(const char* buf)
{
	return (this->*_Zc_pc_purchase_myitemlist)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_deleteitem_from_mcstore("CGameMode::Zc_deleteitem_from_mcstore");
void CGameMode::Zc_deleteitem_from_mcstore(const char* buf)
{
	return (this->*_Zc_deleteitem_from_mcstore)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_attack_failure_for_distance("CGameMode::Zc_attack_failure_for_distance");
void CGameMode::Zc_attack_failure_for_distance(const char* buf)
{
	return (this->*_Zc_attack_failure_for_distance)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_attack_range("CGameMode::Zc_attack_range");
void CGameMode::Zc_attack_range(const char* buf)
{
	return (this->*_Zc_attack_range)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_action_failure("CGameMode::Zc_action_failure");
void CGameMode::Zc_action_failure(const char* buf)
{
	return (this->*_Zc_action_failure)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_equip_arrow("CGameMode::Zc_equip_arrow");
void CGameMode::Zc_equip_arrow(const char* buf)
{
	return (this->*_Zc_equip_arrow)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_recovery("CGameMode::Zc_recovery");
void CGameMode::Zc_recovery(const char* buf)
{
	return (this->*_Zc_recovery)(buf);
}


hook_func<void (CGameMode::*)(const char* buf, BOOL isV2)> CGameMode::_Zc_useskill_ack("CGameMode::Zc_useskill_ack");
void CGameMode::Zc_useskill_ack(const char* buf, BOOL isV2)
{
	return (this->*_Zc_useskill_ack)(buf, isV2);

	unsigned long AID;
	unsigned long targetID;
	int property;
	unsigned long delayTime;
	unsigned short SKID;
	bool isDisposable = false;
	short xPos;
	short yPos;

	if( isV2 == 0 )
	{
		const PACKET_ZC_USESKILL_ACK& Packet = *reinterpret_cast<const PACKET_ZC_USESKILL_ACK*>(buf);
		AID = Packet.AID;
		targetID = Packet.targetID;
		property = Packet.property;
		delayTime = Packet.delayTime;
		SKID = Packet.SKID;
		xPos = Packet.xPos;
		yPos = Packet.yPos;
	}
	else
	if( isV2 == 1 )
	{
		const PACKET_ZC_USESKILL_ACK2& Packet = *reinterpret_cast<const PACKET_ZC_USESKILL_ACK2*>(buf);
		AID = Packet.AID;
		targetID = Packet.targetID;
		property = Packet.property;
		delayTime = Packet.delayTime;
		isDisposable = Packet.isDisposable;
		SKID = Packet.SKID;
		xPos = Packet.xPos;
		yPos = Packet.yPos;
	}

	CGameActor* src_actor = ( AID == g_session.m_aid ) ? m_world->m_player : m_world->CWorld::GetGameActorByAID(AID);
	if( src_actor == NULL )
		return;

	CGameActor* dst_actor = ( targetID == g_session.m_aid ) ? m_world->m_player : m_world->CWorld::GetGameActorByAID(targetID);
	if( !isDisposable )
	{
		unsigned long src_gid = src_actor->CGameActor::GetGID();
		bool bIsParty = ( g_session.CSession::IsPartyMember(src_gid, 1) && g_session.m_aid != src_gid );
		if( g_session.m_aid == src_gid || bIsParty )
		{
			unsigned long dst_gid = ( dst_actor != NULL ) ? dst_actor->CGameActor::GetGID() : 0;
			mystd::string strSrcName = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetActorName2010(src_gid);
			mystd::string strDstName = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetActorName2010(dst_gid);
			mystd::string strSkillName = GetSkillName(SKID);

			if( strSrcName.size() == 0 )
				strSrcName = MsgStr(MSI_WHO_IS);

			if( dst_actor != NULL && strDstName.size() == 0 )
				strDstName = MsgStr(MSI_WHO_IS);

			NMSGTYPE msgType = NMSG_15;
			mystd::string msg = "";
			char buf[256];

			if( bIsParty )
			{
				msgType = NMSG_16;

				sprintf(buf, MsgStr(MSI_NOTIFY_WHO), strSrcName.c_str());
				msg += buf;
			}

			if( dst_actor != NULL )
			{
				sprintf(buf, MsgStr(MSI_NOTIFY_TARGET_WHO), strDstName.c_str());
				msg += buf;
			}

			sprintf(buf, MsgStr(MSI_NOTIFY_SKILL_TO_TARGET), strSkillName.c_str());
			msg += buf;

			if( msg.size() != 0 )
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg.c_str(), 0x00FFFF, msgType, 0);
		}
	}

	if( delayTime == 0 )
		return;

	int beginEffectId;
	int skillMotionType;
	g_session.CSession::GetSkillActionInfo2(SKID, beginEffectId, skillMotionType, property, src_actor->CGameActor::GetJob());

	if( SKID == SKID_KN_BOWLINGBASH || SKID == SKID_KN_BRANDISHSPEAR )
	{
		src_actor->SetState(skillMotionType);
		src_actor->m_isMotionFreezed = 1;
		src_actor->CGameActor::SetFreezeEndTick(delayTime + timeGetTime());
	}
	else
	{
		src_actor->SetState(skillMotionType);
		src_actor->SendMsg(NULL, 85, beginEffectId, delayTime / 16, 0);
		src_actor->SendMsg(NULL, 82, delayTime, 0, 0);

		switch( SKID )
		{
		case SKID_GC_POISONSMOKE:
			src_actor->CAbleToMakeEffect::LaunchEffect(768, vector3d(0.,0.,0.), 0.0);
		break;
		case SKID_WL_RECOGNIZEDSPELL:
			src_actor->CAbleToMakeEffect::LaunchEffect(803, vector3d(0.,0.,0.), 0.0);
		break;
		case SKID_NC_F_SIDESLIDE:
		{
			PlayWave("_heal_effect.wav", 0.0, 0.0, 0.0, 250, 40, 1.0);
			CRagEffect* effect = src_actor->CAbleToMakeEffect::LaunchEffect(216, vector3d(0.,0.,0.), 0.0);
			if( effect != NULL )
				effect->SendMsg(NULL, 14, (int)&src_actor->m_pos, 0, 0);
		}
		break;
		case SKID_SC_STARTMARK:
		break;
		case SKID_SC_FEINTBOMB:
		{
			CRagEffect* effect = src_actor->CAbleToMakeEffect::LaunchEffect(824, vector3d(0.,0.,0.), 0.0);
			if( effect != NULL )
				effect->SendMsg(NULL, 44, 0x00FFFF, 824, 0);
		}
		break;
		};

		if( !g_session.CSession::IsMonster(src_actor) )
		{
			if( SKID == SKID_WE_MALE || SKID == SKID_WE_FEMALE )
			{
				this->SendMsg(86, SKID, (int)src_actor, targetID);
			}
			else
			{
				this->SendMsg(86, SKID, (int)src_actor, 0);
			}
		}
		else
		{
			int act;
			int loopType;
			g_session.CSession::GetMonsterSkillInfo(g_session.m_jobNameTable[src_actor->CGameActor::GetJob()], SKID, act, loopType);

			if( act != -1 )
			{
				src_actor->SetAction(8 * act - 8, 1, (loopType == 0));

				if( SKID == SKID_NPC_METAMORPHOSIS )
					src_actor->CGameActor::SetMotionSpeed(float(delayTime / 300));
			}
		}
	}

	if( targetID != 0 )
	{
		CGameActor* dst_actor = ( targetID == g_session.m_aid ) ? m_world->m_player : m_world->CWorld::GetGameActorByAID(targetID);
		if( dst_actor != NULL && src_actor != dst_actor )
		{
			if( !g_session.CSession::IsMer(dst_actor->CGameActor::GetJob()) && dst_actor->m_objectType != NPC_MERSOL_TYPE )
				src_actor->SendMsg(NULL, 81, targetID, 0, 0);
			else
			if( !SKILL_INFO::IsGoodSkillForActor(SKID) || m_world->CWorld::IsPKZone() || m_world->CWorld::IsSiegeMode() )
				src_actor->SendMsg(NULL, 81, targetID, 0, 0);

			src_actor->CRenderObject::CalcDir(dst_actor->m_pos.x, dst_actor->m_pos.z);
			dst_actor->SendMsg(NULL, 86, 60, delayTime / 16, 0);

			if( SKID == SKID_CR_ACIDDEMONSTRATION )
			{
				CRagEffect* effect = src_actor->CAbleToMakeEffect::LaunchEffect(539, vector3d(0.,0.,0.), 0.0);
				if( effect != NULL )
					effect->SendMsg(NULL, 14, (int)&dst_actor->m_pos, 0, 0);
			}
			else
			if( SKID == SKID_NC_FLAMELAUNCHER )
			{
				CRagEffect* effect = src_actor->CAbleToMakeEffect::LaunchEffect(787, vector3d(0.,0.,0.), 0.0);
				if( effect != NULL )
					effect->SendMsg(NULL, 14, (int)&dst_actor->m_pos, 0, 0);
			}
		}
	}
	else
	{
		float cx, cy;
		g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetClientCoor(xPos, yPos, cx, cy);
		src_actor->CRenderObject::CalcDir(cx, cy);

		CGroundScope* gs = new CGroundScope();
		gs->SendMsg(NULL, 22, AID, 0, 0);
		gs->SendMsg(NULL, 14, xPos, yPos, 0);
		gs->SendMsg(NULL, 115, delayTime + timeGetTime(), 0, 0);
		gs->SendMsg(NULL, 117, SKID, 0, 0);
		m_world->m_gameObjectList.push_back(gs);
	}

	switch( SKID )
	{
	case SKID_MO_CALLSPIRITS:
		src_actor->CRenderObject::SetForceAnimation(96, 0, 0, 96, 0, 0, 0, 0);
	break;
	case SKID_MO_STEELBODY:
		src_actor->CRenderObject::SetForceAnimation(96, 0, 0, 96, 0, 1, delayTime + 1000, 0);
	break;
	case SKID_CH_SOULCOLLECT:
		src_actor->CRenderObject::SetForceAnimation(96, 0, 0, 96, 0, 0, 0, 0);
		src_actor->CAbleToMakeEffect::LaunchEffect(402, vector3d(0.,0.,0.), 0.0);
	break;
	case SKID_MO_KITRANSLATION:
		src_actor->CRenderObject::SetForceAnimation(96, 0, 0, 96, 0, 0, 0, 0);
	break;
	};
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_couplestatus("CGameMode::Zc_couplestatus");
void CGameMode::Zc_couplestatus(const char* buf)
{
	return (this->*_Zc_couplestatus)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_open_editdlg("CGameMode::Zc_open_editdlg");
void CGameMode::Zc_open_editdlg(const char* buf)
{
	return (this->*_Zc_open_editdlg)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_compass("CGameMode::Zc_compass");
void CGameMode::Zc_compass(const char* buf)
{
	return (this->*_Zc_compass)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_show_image("CGameMode::Zc_show_image");
void CGameMode::Zc_show_image(const char* buf)
{
	return (this->*_Zc_show_image)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_autorun_skill("CGameMode::Zc_autorun_skill");
void CGameMode::Zc_autorun_skill(const char* buf)
{
	return (this->*_Zc_autorun_skill)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_resurrection("CGameMode::Zc_resurrection");
void CGameMode::Zc_resurrection(const char* buf)
{
	return (this->*_Zc_resurrection)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_give_manner_point("CGameMode::Zc_ack_give_manner_point");
void CGameMode::Zc_ack_give_manner_point(const char* buf)
{
	return (this->*_Zc_ack_give_manner_point)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_notify_manner_point_given("CGameMode::Zc_notify_manner_point_given");
void CGameMode::Zc_notify_manner_point_given(const char* buf)
{
	return (this->*_Zc_notify_manner_point_given)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_myguild_basic_info("CGameMode::Zc_myguild_basic_info");
void CGameMode::Zc_myguild_basic_info(const char* buf)
{
	return (this->*_Zc_myguild_basic_info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_guild_menuinterface("CGameMode::Zc_ack_guild_menuinterface");
void CGameMode::Zc_ack_guild_menuinterface(const char* buf)
{
	return (this->*_Zc_ack_guild_menuinterface)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_guild_info("CGameMode::Zc_guild_info");
void CGameMode::Zc_guild_info(const char* buf)
{
	return (this->*_Zc_guild_info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_guild_emblem_img("CGameMode::Zc_guild_emblem_img");
void CGameMode::Zc_guild_emblem_img(const char* buf)
{
	return (this->*_Zc_guild_emblem_img)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_membermgr_info("CGameMode::Zc_membermgr_info");
void CGameMode::Zc_membermgr_info(const char* buf)
{
	return (this->*_Zc_membermgr_info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_change_members("CGameMode::Zc_ack_req_change_members");
void CGameMode::Zc_ack_req_change_members(const char* buf)
{
	return (this->*_Zc_ack_req_change_members)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_open_member_info("CGameMode::Zc_ack_open_member_info");
void CGameMode::Zc_ack_open_member_info(const char* buf)
{
	return (this->*_Zc_ack_open_member_info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_leave_guild("CGameMode::Zc_ack_leave_guild");
void CGameMode::Zc_ack_leave_guild(const char* buf)
{
	return (this->*_Zc_ack_leave_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_ban_guild("CGameMode::Zc_ack_ban_guild");
void CGameMode::Zc_ack_ban_guild(const char* buf)
{
	return (this->*_Zc_ack_ban_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_disorganize_guild_result("CGameMode::Zc_ack_disorganize_guild_result");
void CGameMode::Zc_ack_disorganize_guild_result(const char* buf)
{
	return (this->*_Zc_ack_disorganize_guild_result)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_disorganize_guild("CGameMode::Zc_ack_disorganize_guild");
void CGameMode::Zc_ack_disorganize_guild(const char* buf)
{
	return (this->*_Zc_ack_disorganize_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_position_info("CGameMode::Zc_position_info");
void CGameMode::Zc_position_info(const char* buf)
{
	return (this->*_Zc_position_info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_GuildSkillInfo("CGameMode::Zc_GuildSkillInfo");
void CGameMode::Zc_GuildSkillInfo(const char* buf)
{
	return (this->*_Zc_GuildSkillInfo)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ban_list("CGameMode::Zc_ban_list");
void CGameMode::Zc_ban_list(const char* buf)
{
	return (this->*_Zc_ban_list)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_other_guild_list("CGameMode::Zc_other_guild_list");
void CGameMode::Zc_other_guild_list(const char* buf)
{
	return (this->*_Zc_other_guild_list)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_position_id_name_info("CGameMode::Zc_position_id_name_info");
void CGameMode::Zc_position_id_name_info(const char* buf)
{
	return (this->*_Zc_position_id_name_info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_result_make_guild("CGameMode::Zc_result_make_guild");
void CGameMode::Zc_result_make_guild(const char* buf)
{
	return (this->*_Zc_result_make_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_join_guild("CGameMode::Zc_ack_req_join_guild");
void CGameMode::Zc_ack_req_join_guild(const char* buf)
{
	return (this->*_Zc_ack_req_join_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_req_join_guild("CGameMode::Zc_req_join_guild");
void CGameMode::Zc_req_join_guild(const char* buf)
{
	return (this->*_Zc_req_join_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_update_gdid("CGameMode::Zc_update_gdid");
void CGameMode::Zc_update_gdid(const char* buf)
{
	return (this->*_Zc_update_gdid)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_update_charstat("CGameMode::Zc_update_charstat");
void CGameMode::Zc_update_charstat(const char* buf)
{
	return (this->*_Zc_update_charstat)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_guild_notice("CGameMode::Zc_guild_notice");
void CGameMode::Zc_guild_notice(const char* buf)
{
	return (this->*_Zc_guild_notice)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_req_ally_guild("CGameMode::Zc_req_ally_guild");
void CGameMode::Zc_req_ally_guild(const char* buf)
{
	return (this->*_Zc_req_ally_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_ally_guild("CGameMode::Zc_ack_req_ally_guild");
void CGameMode::Zc_ack_req_ally_guild(const char* buf)
{
	return (this->*_Zc_ack_req_ally_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_change_guild_positioninfo("CGameMode::Zc_ack_change_guild_positioninfo");
void CGameMode::Zc_ack_change_guild_positioninfo(const char* buf)
{
	return (this->*_Zc_ack_change_guild_positioninfo)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_itemidentify_list("CGameMode::Zc_itemidentify_list");
void CGameMode::Zc_itemidentify_list(const char* buf)
{
	return (this->*_Zc_itemidentify_list)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_itemidentify("CGameMode::Zc_ack_itemidentify");
void CGameMode::Zc_ack_itemidentify(const char* buf)
{
	return (this->*_Zc_ack_itemidentify)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_itemcomposition_list("CGameMode::Zc_itemcomposition_list");
void CGameMode::Zc_itemcomposition_list(const char* buf)
{
	return (this->*_Zc_itemcomposition_list)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_itemcomposition("CGameMode::Zc_ack_itemcomposition");
void CGameMode::Zc_ack_itemcomposition(const char* buf)
{
	return (this->*_Zc_ack_itemcomposition)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_guild_chat("CGameMode::Zc_guild_chat");
void CGameMode::Zc_guild_chat(const char* buf)
{
	return (this->*_Zc_guild_chat)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_hostile_guild("CGameMode::Zc_ack_req_hostile_guild");
void CGameMode::Zc_ack_req_hostile_guild(const char* buf)
{
	return (this->*_Zc_ack_req_hostile_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_member_add("CGameMode::Zc_member_add");
void CGameMode::Zc_member_add(const char* buf)
{
	return (this->*_Zc_member_add)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_delete_related_guild("CGameMode::Zc_delete_related_guild");
void CGameMode::Zc_delete_related_guild(const char* buf)
{
	return (this->*_Zc_delete_related_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_add_related_guild("CGameMode::Zc_add_related_guild");
void CGameMode::Zc_add_related_guild(const char* buf)
{
	return (this->*_Zc_add_related_guild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_itemrefining("CGameMode::Zc_ack_itemrefining");
void CGameMode::Zc_ack_itemrefining(const char* buf)
{
	return (this->*_Zc_ack_itemrefining)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_notify_mapinfo("CGameMode::Zc_notify_mapinfo");
void CGameMode::Zc_notify_mapinfo(const char* buf)
{
	return (this->*_Zc_notify_mapinfo)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_disconnect("CGameMode::Zc_ack_req_disconnect");
void CGameMode::Zc_ack_req_disconnect(const char* buf)
{
	return (this->*_Zc_ack_req_disconnect)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_monster_info("CGameMode::Zc_monster_info");
void CGameMode::Zc_monster_info(const char* buf)
{
	return (this->*_Zc_monster_info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_makable_item_list("CGameMode::Zc_makable_item_list");
void CGameMode::Zc_makable_item_list(const char* buf)
{
	return (this->*_Zc_makable_item_list)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_itemmaking("CGameMode::Zc_ack_req_itemmaking");
void CGameMode::Zc_ack_req_itemmaking(const char* buf)
{
	return (this->*_Zc_ack_req_itemmaking)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_talkbox_chat_contents("CGameMode::Zc_talkbox_chat_contents");
void CGameMode::Zc_talkbox_chat_contents(const char* buf)
{
	return (this->*_Zc_talkbox_chat_contents)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_update_mapinfo("CGameMode::Zc_update_mapinfo");
void CGameMode::Zc_update_mapinfo(const char* buf)
{
	return (this->*_Zc_update_mapinfo)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Reqname_bygid("CGameMode::Zc_Ack_Reqname_bygid");
void CGameMode::Zc_Ack_Reqname_bygid(const char* buf)
{
	return (this->*_Zc_Ack_Reqname_bygid)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Reqnameall("CGameMode::Zc_Ack_Reqnameall");
void CGameMode::Zc_Ack_Reqnameall(const char* buf)
{
	return (this->*_Zc_Ack_Reqnameall)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Msg_State_Change("CGameMode::Zc_Msg_State_Change");
void CGameMode::Zc_Msg_State_Change(const char* buf)
{
	return (this->*_Zc_Msg_State_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Mapproperty("CGameMode::Zc_Notify_Mapproperty");
void CGameMode::Zc_Notify_Mapproperty(const char* buf)
{
	return (this->*_Zc_Notify_Mapproperty)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Ranking("CGameMode::Zc_Notify_Ranking");
void CGameMode::Zc_Notify_Ranking(const char* buf)
{
	return (this->*_Zc_Notify_Ranking)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Effect("CGameMode::Zc_Notify_Effect");
void CGameMode::Zc_Notify_Effect(const char* buf)
{
	return (this->*_Zc_Notify_Effect)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Start_Capture("CGameMode::Zc_Start_Capture");
void CGameMode::Zc_Start_Capture(const char* buf)
{
	return (this->*_Zc_Start_Capture)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_TryCapture_Monster("CGameMode::Zc_TryCapture_Monster");
void CGameMode::Zc_TryCapture_Monster(const char* buf)
{
	return (this->*_Zc_TryCapture_Monster)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Property_Pet("CGameMode::Zc_Property_Pet");
void CGameMode::Zc_Property_Pet(const char* buf)
{
	return (this->*_Zc_Property_Pet)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Feed_Pet("CGameMode::Zc_Feed_Pet");
void CGameMode::Zc_Feed_Pet(const char* buf)
{
	return (this->*_Zc_Feed_Pet)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Change_Pet_Status("CGameMode::Zc_Change_Pet_Status");
void CGameMode::Zc_Change_Pet_Status(const char* buf)
{
	return (this->*_Zc_Change_Pet_Status)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_PetEgg_List("CGameMode::Zc_PetEgg_List");
void CGameMode::Zc_PetEgg_List(const char* buf)
{
	return (this->*_Zc_PetEgg_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pet_Act("CGameMode::Zc_Pet_Act");
void CGameMode::Zc_Pet_Act(const char* buf)
{
	return (this->*_Zc_Pet_Act)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Par_Change_User("CGameMode::Zc_Par_Change_User");
void CGameMode::Zc_Par_Change_User(const char* buf)
{
	return (this->*_Zc_Par_Change_User)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Update("CGameMode::Zc_Skill_Update");
void CGameMode::Zc_Skill_Update(const char* buf)
{
	return (this->*_Zc_Skill_Update)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_MakingArrowList("CGameMode::Zc_MakingArrowList");
void CGameMode::Zc_MakingArrowList(const char* buf)
{
	return (this->*_Zc_MakingArrowList)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_NpcSpriteChange("CGameMode::Zc_NpcSpriteChange");
void CGameMode::Zc_NpcSpriteChange(const char* buf)
{
	return (this->*_Zc_NpcSpriteChange)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ShowDigit("CGameMode::Zc_ShowDigit");
void CGameMode::Zc_ShowDigit(const char* buf)
{
	return (this->*_Zc_ShowDigit)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_show_image2("CGameMode::Zc_show_image2");
void CGameMode::Zc_show_image2(const char* buf)
{
	return (this->*_Zc_show_image2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ChangeGuild("CGameMode::Zc_ChangeGuild");
void CGameMode::Zc_ChangeGuild(const char* buf)
{
	return (this->*_Zc_ChangeGuild)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_GuildInfo2("CGameMode::Zc_GuildInfo2");
void CGameMode::Zc_GuildInfo2(const char* buf)
{
	return (this->*_Zc_GuildInfo2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_GuildZenyAck("CGameMode::Zc_GuildZenyAck");
void CGameMode::Zc_GuildZenyAck(const char* buf)
{
	return (this->*_Zc_GuildZenyAck)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Dispel("CGameMode::Zc_Dispel");
void CGameMode::Zc_Dispel(const char* buf)
{
	return (this->*_Zc_Dispel)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Reply_RemainTime("CGameMode::Zc_Reply_RemainTime");
void CGameMode::Zc_Reply_RemainTime(const char* buf)
{
	return (this->*_Zc_Reply_RemainTime)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Info_RemainTime("CGameMode::Zc_Info_RemainTime");
void CGameMode::Zc_Info_RemainTime(const char* buf)
{
	return (this->*_Zc_Info_RemainTime)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Broadcast2("CGameMode::Zc_Broadcast2");
void CGameMode::Zc_Broadcast2(const char* buf)
{
	const PACKET_ZC_BROADCAST2& packet = *reinterpret_cast<const PACKET_ZC_BROADCAST2*>(buf);
	return (this->*_Zc_Broadcast2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_AddItemToStore2("CGameMode::Zc_AddItemToStore2");
void CGameMode::Zc_AddItemToStore2(const char* buf)
{
	return (this->*_Zc_AddItemToStore2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Item_To_Cart2("CGameMode::Zc_Add_Item_To_Cart2");
void CGameMode::Zc_Add_Item_To_Cart2(const char* buf)
{
	return (this->*_Zc_Add_Item_To_Cart2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Sc_Ack_Encryption("CGameMode::Sc_Ack_Encryption");
void CGameMode::Sc_Ack_Encryption(const char* buf)
{
	return (this->*_Sc_Ack_Encryption)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Use_Item_Ack2("CGameMode::Zc_Use_Item_Ack2");
void CGameMode::Zc_Use_Item_Ack2(const char* buf)
{
	return (this->*_Zc_Use_Item_Ack2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Entry2("CGameMode::Zc_Skill_Entry2");
void CGameMode::Zc_Skill_Entry2(const char* buf)
{
	return (this->*_Zc_Skill_Entry2)(buf);
}


void CGameMode::Zc_Monster_Talk(const char* buf)
{
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_AutoSpellList("CGameMode::Zc_AutoSpellList");
void CGameMode::Zc_AutoSpellList(const char* buf)
{
	return (this->*_Zc_AutoSpellList)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_DevotionList("CGameMode::Zc_DevotionList");
void CGameMode::Zc_DevotionList(const char* buf)
{
	return (this->*_Zc_DevotionList)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Spirits("CGameMode::Zc_Spirits");
void CGameMode::Zc_Spirits(const char* buf)
{
	return (this->*_Zc_Spirits)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_BladeStop("CGameMode::Zc_BladeStop");
void CGameMode::Zc_BladeStop(const char* buf)
{
	return (this->*_Zc_BladeStop)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ComboDelay("CGameMode::Zc_ComboDelay");
void CGameMode::Zc_ComboDelay(const char* buf)
{
	return (this->*_Zc_ComboDelay)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Sound("CGameMode::Zc_Sound");
void CGameMode::Zc_Sound(const char* buf)
{
	return (this->*_Zc_Sound)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Open_EditDlgStr("CGameMode::Zc_Open_EditDlgStr");
void CGameMode::Zc_Open_EditDlgStr(const char* buf)
{
	return (this->*_Zc_Open_EditDlgStr)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Mapproperty2("CGameMode::Zc_Notify_Mapproperty2");
void CGameMode::Zc_Notify_Mapproperty2(const char* buf)
{
	return (this->*_Zc_Notify_Mapproperty2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Sprite_Change2("CGameMode::Zc_Sprite_Change2");
void CGameMode::Zc_Sprite_Change2(const char* buf)
{
	return (this->*_Zc_Sprite_Change2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Standentry2("CGameMode::Zc_Notify_Standentry2");
void CGameMode::Zc_Notify_Standentry2(const char* buf)
{
	return (this->*_Zc_Notify_Standentry2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Newentry2("CGameMode::Zc_Notify_Newentry2");
void CGameMode::Zc_Notify_Newentry2(const char* buf)
{
	return (this->*_Zc_Notify_Newentry2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Moveentry2("CGameMode::Zc_Notify_Moveentry2");
void CGameMode::Zc_Notify_Moveentry2(const char* buf)
{
	return (this->*_Zc_Notify_Moveentry2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Skill2("CGameMode::Zc_Notify_Skill2");
void CGameMode::Zc_Notify_Skill2(const char* buf)
{
	return (this->*_Zc_Notify_Skill2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_AccountName("CGameMode::Zc_Ack_AccountName");
void CGameMode::Zc_Ack_AccountName(const char* buf)
{
	return (this->*_Zc_Ack_AccountName)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Spirits2("CGameMode::Zc_Spirits2");
void CGameMode::Zc_Spirits2(const char* buf)
{
	return (this->*_Zc_Spirits2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Couple("CGameMode::Zc_Req_Couple");
void CGameMode::Zc_Req_Couple(const char* buf)
{
	return (this->*_Zc_Req_Couple)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Start_Couple("CGameMode::Zc_Start_Couple");
void CGameMode::Zc_Start_Couple(const char* buf)
{
	return (this->*_Zc_Start_Couple)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_CoupleName("CGameMode::Zc_CoupleName");
void CGameMode::Zc_CoupleName(const char* buf)
{
	return (this->*_Zc_CoupleName)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Member_To_Group2("CGameMode::Zc_Add_Member_To_Group2");
void CGameMode::Zc_Add_Member_To_Group2(const char* buf)
{
	return (this->*_Zc_Add_Member_To_Group2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Congratulation("CGameMode::Zc_Congratulation");
void CGameMode::Zc_Congratulation(const char* buf)
{
	return (this->*_Zc_Congratulation)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Position_To_Guildm("CGameMode::Zc_Notify_Position_To_Guildm");
void CGameMode::Zc_Notify_Position_To_Guildm(const char* buf)
{
	return (this->*_Zc_Notify_Position_To_Guildm)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Guild_Member_Map_Change("CGameMode::Zc_Guild_Member_Map_Change");
void CGameMode::Zc_Guild_Member_Map_Change(const char* buf)
{
	return (this->*_Zc_Guild_Member_Map_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Normal_Itemlist2("CGameMode::Zc_Normal_Itemlist2");
void CGameMode::Zc_Normal_Itemlist2(const char* buf)
{
	return (this->*_Zc_Normal_Itemlist2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cart_Normal_Itemlist2("CGameMode::Zc_Cart_Normal_Itemlist2");
void CGameMode::Zc_Cart_Normal_Itemlist2(const char* buf)
{
	return (this->*_Zc_Cart_Normal_Itemlist2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Store_Normal_Itemlist2("CGameMode::Zc_Store_Normal_Itemlist2");
void CGameMode::Zc_Store_Normal_Itemlist2(const char* buf)
{
	return (this->*_Zc_Store_Normal_Itemlist2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_update_charstat2("CGameMode::Zc_update_charstat2");
void CGameMode::Zc_update_charstat2(const char* buf)
{
	return (this->*_Zc_update_charstat2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Effect2("CGameMode::Zc_Notify_Effect2");
void CGameMode::Zc_Notify_Effect2(const char* buf)
{
	return (this->*_Zc_Notify_Effect2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Exchange_Item2("CGameMode::Zc_Req_Exchange_Item2");
void CGameMode::Zc_Req_Exchange_Item2(const char* buf)
{
	return (this->*_Zc_Req_Exchange_Item2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Exchange_Item2("CGameMode::Zc_Ack_Exchange_Item2");
void CGameMode::Zc_Ack_Exchange_Item2(const char* buf)
{
	return (this->*_Zc_Ack_Exchange_Item2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Baby("CGameMode::Zc_Req_Baby");
void CGameMode::Zc_Req_Baby(const char* buf)
{
	return (this->*_Zc_Req_Baby)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Start_Baby("CGameMode::Zc_Start_Baby");
void CGameMode::Zc_Start_Baby(const char* buf)
{
	return (this->*_Zc_Start_Baby)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_repair_item_list("CGameMode::Zc_repair_item_list");
void CGameMode::Zc_repair_item_list(const char* buf)
{
	return (this->*_Zc_repair_item_list)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_itemrepair("CGameMode::Zc_ack_itemrepair");
void CGameMode::Zc_ack_itemrepair(const char* buf)
{
	return (this->*_Zc_ack_itemrepair)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_HighJump("CGameMode::Zc_HighJump");
void CGameMode::Zc_HighJump(const char* buf)
{
	return (this->*_Zc_HighJump)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Friends_List("CGameMode::Zc_Friends_List");
void CGameMode::Zc_Friends_List(const char* buf)
{
	return (this->*_Zc_Friends_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Divorce("CGameMode::Zc_Divorce");
void CGameMode::Zc_Divorce(const char* buf)
{
	return (this->*_Zc_Divorce)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Friends_State("CGameMode::Zc_Friends_State");
void CGameMode::Zc_Friends_State(const char* buf)
{
	return (this->*_Zc_Friends_State)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Join_Friend("CGameMode::Zc_Req_Join_Friend");
void CGameMode::Zc_Req_Join_Friend(const char* buf)
{
	return (this->*_Zc_Req_Join_Friend)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Friends_List("CGameMode::Zc_Add_Friends_List");
void CGameMode::Zc_Add_Friends_List(const char* buf)
{
	return (this->*_Zc_Add_Friends_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Delete_Friend("CGameMode::Zc_Req_Delete_Friend");
void CGameMode::Zc_Req_Delete_Friend(const char* buf)
{
	return (this->*_Zc_Req_Delete_Friend)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_StarSkill("CGameMode::Zc_StarSkill");
void CGameMode::Zc_StarSkill(const char* buf)
{
	return (this->*_Zc_StarSkill)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_PvpPoint("CGameMode::Zc_Ack_PvpPoint");
void CGameMode::Zc_Ack_PvpPoint(const char* buf)
{
	return (this->*_Zc_Ack_PvpPoint)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Status_GM("CGameMode::Zc_Ack_Status_GM");
void CGameMode::Zc_Ack_Status_GM(const char* buf)
{
	return (this->*_Zc_Ack_Status_GM)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_SKILLMSG("CGameMode::Zc_SKILLMSG");
void CGameMode::Zc_SKILLMSG(const char* buf)
{
	return (this->*_Zc_SKILLMSG)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_BABYMSG("CGameMode::Zc_BABYMSG");
void CGameMode::Zc_BABYMSG(const char* buf)
{
	return (this->*_Zc_BABYMSG)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_BLACKSMITH_RANK("CGameMode::ZC_BLACKSMITH_RANK");
void CGameMode::ZC_BLACKSMITH_RANK(const char* buf)
{
	return (this->*_ZC_BLACKSMITH_RANK)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_ALCHEMIST_RANK("CGameMode::ZC_ALCHEMIST_RANK");
void CGameMode::ZC_ALCHEMIST_RANK(const char* buf)
{
	return (this->*_ZC_ALCHEMIST_RANK)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_BLACKSMITH_POINT("CGameMode::ZC_BLACKSMITH_POINT");
void CGameMode::ZC_BLACKSMITH_POINT(const char* buf)
{
	return (this->*_ZC_BLACKSMITH_POINT)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_ALCHEMIST_POINT("CGameMode::ZC_ALCHEMIST_POINT");
void CGameMode::ZC_ALCHEMIST_POINT(const char* buf)
{
	return (this->*_ZC_ALCHEMIST_POINT)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_PKinfo("CGameMode::Zc_Notify_PKinfo");
void CGameMode::Zc_Notify_PKinfo(const char* buf)
{
	return (this->*_Zc_Notify_PKinfo)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_CrazyKiller("CGameMode::Zc_Notify_CrazyKiller");
void CGameMode::Zc_Notify_CrazyKiller(const char* buf)
{
	return (this->*_Zc_Notify_CrazyKiller)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_notify_weapon_item_list("CGameMode::Zc_notify_weapon_item_list");
void CGameMode::Zc_notify_weapon_item_list(const char* buf)
{
	return (this->*_Zc_notify_weapon_item_list)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_weaponrefine("CGameMode::Zc_ack_weaponrefine");
void CGameMode::Zc_ack_weaponrefine(const char* buf)
{
	return (this->*_Zc_ack_weaponrefine)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_TAEKWON_POINT("CGameMode::ZC_TAEKWON_POINT");
void CGameMode::ZC_TAEKWON_POINT(const char* buf)
{
	return (this->*_ZC_TAEKWON_POINT)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_TAEKWON_RANK("CGameMode::ZC_TAEKWON_RANK");
void CGameMode::ZC_TAEKWON_RANK(const char* buf)
{
	return (this->*_ZC_TAEKWON_RANK)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Game_Guard("CGameMode::Zc_Game_Guard");
void CGameMode::Zc_Game_Guard(const char* buf)
{
	return (this->*_Zc_Game_Guard)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_State_Change3("CGameMode::Zc_State_Change3");
void CGameMode::Zc_State_Change3(const char* buf)
{
	return (this->*_Zc_State_Change3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Standentry3("CGameMode::Zc_Notify_Standentry3");
void CGameMode::Zc_Notify_Standentry3(const char* buf)
{
	return (this->*_Zc_Notify_Standentry3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Newentry3("CGameMode::Zc_Notify_Newentry3");
void CGameMode::Zc_Notify_Newentry3(const char* buf)
{
	return (this->*_Zc_Notify_Newentry3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Moveentry3("CGameMode::Zc_Notify_Moveentry3");
void CGameMode::Zc_Notify_Moveentry3(const char* buf)
{
	return (this->*_Zc_Notify_Moveentry3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Property_Homun("CGameMode::Zc_Property_Homun");
void CGameMode::Zc_Property_Homun(const char* buf)
{
	return (this->*_Zc_Property_Homun)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Change_Mer_Status("CGameMode::Zc_Change_Mer_Status");
void CGameMode::Zc_Change_Mer_Status(const char* buf)
{
	return (this->*_Zc_Change_Mer_Status)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_KILLER_POINT("CGameMode::ZC_KILLER_POINT");
void CGameMode::ZC_KILLER_POINT(const char* buf)
{
	return (this->*_ZC_KILLER_POINT)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_KILLER_RANK("CGameMode::ZC_KILLER_RANK");
void CGameMode::ZC_KILLER_RANK(const char* buf)
{
	return (this->*_ZC_KILLER_RANK)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mail_Req_Get_List("CGameMode::Zc_Mail_Req_Get_List");
void CGameMode::Zc_Mail_Req_Get_List(const char* buf)
{
	return (this->*_Zc_Mail_Req_Get_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mail_Req_Open("CGameMode::Zc_Mail_Req_Open");
void CGameMode::Zc_Mail_Req_Open(const char* buf)
{
	return (this->*_Zc_Mail_Req_Open)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mail_Req_Get_Item("CGameMode::Zc_Mail_Req_Get_Item");
void CGameMode::Zc_Mail_Req_Get_Item(const char* buf)
{
	return (this->*_Zc_Mail_Req_Get_Item)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mail_Req_Send("CGameMode::Zc_Mail_Req_Send");
void CGameMode::Zc_Mail_Req_Send(const char* buf)
{
	return (this->*_Zc_Mail_Req_Send)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mail_Receive("CGameMode::Zc_Mail_Receive");
void CGameMode::Zc_Mail_Receive(const char* buf)
{
	return (this->*_Zc_Mail_Receive)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Auction_Result("CGameMode::Zc_Auction_Result");
void CGameMode::Zc_Auction_Result(const char* buf)
{
	return (this->*_Zc_Auction_Result)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Auction_Item_Req_Search("CGameMode::Zc_Auction_Item_Req_Search");
void CGameMode::Zc_Auction_Item_Req_Search(const char* buf)
{
	return (this->*_Zc_Auction_Item_Req_Search)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_StarPlace("CGameMode::Zc_StarPlace");
void CGameMode::Zc_StarPlace(const char* buf)
{
	return (this->*_Zc_StarPlace)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Mail_Add_Item("CGameMode::Zc_Ack_Mail_Add_Item");
void CGameMode::Zc_Ack_Mail_Add_Item(const char* buf)
{
	return (this->*_Zc_Ack_Mail_Add_Item)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Auction_Add_Item("CGameMode::Zc_Ack_Auction_Add_Item");
void CGameMode::Zc_Ack_Auction_Add_Item(const char* buf)
{
	return (this->*_Zc_Ack_Auction_Add_Item)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Mail_Delete("CGameMode::Zc_Ack_Mail_Delete");
void CGameMode::Zc_Ack_Mail_Delete(const char* buf)
{
	return (this->*_Zc_Ack_Mail_Delete)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_MakingItemList("CGameMode::Zc_MakingItemList");
void CGameMode::Zc_MakingItemList(const char* buf)
{
	return (this->*_Zc_MakingItemList)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Auction_My_Sell_Stop("CGameMode::Zc_Auction_My_Sell_Stop");
void CGameMode::Zc_Auction_My_Sell_Stop(const char* buf)
{
	return (this->*_Zc_Auction_My_Sell_Stop)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Auction_Windows("CGameMode::Zc_Auction_Windows");
void CGameMode::Zc_Auction_Windows(const char* buf)
{
	return (this->*_Zc_Auction_Windows)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mail_Windows("CGameMode::Zc_Mail_Windows");
void CGameMode::Zc_Mail_Windows(const char* buf)
{
	return (this->*_Zc_Mail_Windows)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Mail_Return("CGameMode::Zc_Ack_Mail_Return");
void CGameMode::Zc_Ack_Mail_Return(const char* buf)
{
	return (this->*_Zc_Ack_Mail_Return)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_HuntingList("CGameMode::Zc_HuntingList");
void CGameMode::Zc_HuntingList(const char* buf)
{
	return (this->*_Zc_HuntingList)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pcbang_Effect("CGameMode::Zc_Pcbang_Effect");
void CGameMode::Zc_Pcbang_Effect(const char* buf)
{
	return (this->*_Zc_Pcbang_Effect)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_GANGSI_POINT("CGameMode::ZC_GANGSI_POINT");
void CGameMode::ZC_GANGSI_POINT(const char* buf)
{
	return (this->*_ZC_GANGSI_POINT)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_GANGSI_RANK("CGameMode::ZC_GANGSI_RANK");
void CGameMode::ZC_GANGSI_RANK(const char* buf)
{
	return (this->*_ZC_GANGSI_RANK)(buf);
}


void CGameMode::Zc_Aid(const char* buf)
{
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Effect3("CGameMode::Zc_Notify_Effect3");
void CGameMode::Zc_Notify_Effect3(const char* buf)
{
	return (this->*_Zc_Notify_Effect3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_ZC_DEATH_QUESTION("CGameMode::ZC_DEATH_QUESTION");
void CGameMode::ZC_DEATH_QUESTION(const char* buf)
{
	return (this->*_ZC_DEATH_QUESTION)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Cash_Point_ItemList("CGameMode::Zc_Pc_Cash_Point_ItemList");
void CGameMode::Zc_Pc_Cash_Point_ItemList(const char* buf)
{
	return (this->*_Zc_Pc_Cash_Point_ItemList)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Cash_Point_Update("CGameMode::Zc_Pc_Cash_Point_Update");
void CGameMode::Zc_Pc_Cash_Point_Update(const char* buf)
{
	return (this->*_Zc_Pc_Cash_Point_Update)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Npc_Showefst_Update("CGameMode::Zc_Npc_Showefst_Update");
void CGameMode::Zc_Npc_Showefst_Update(const char* buf)
{
	return (this->*_Zc_Npc_Showefst_Update)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Msg("CGameMode::Zc_Msg");
void CGameMode::Zc_Msg(const char* buf)
{
	return (this->*_Zc_Msg)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Boss_Info("CGameMode::Zc_Boss_Info");
void CGameMode::Zc_Boss_Info(const char* buf)
{
	return (this->*_Zc_Boss_Info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Read_Book("CGameMode::Zc_Read_Book");
void CGameMode::Zc_Read_Book(const char* buf)
{
	return (this->*_Zc_Read_Book)(buf);
}


void CGameMode::Zc_Equipment_Itemlist2(const char* buf)
{
	PACKET_ZC_EQUIPMENT_ITEMLIST2& packet = *(PACKET_ZC_EQUIPMENT_ITEMLIST2*)buf;
	int count = (packet.Length - sizeof(packet)) / sizeof(PACKET_ZC_EQUIPMENT_ITEMLIST2::ITEM);

	g_session.CSession::ClearEquipItemInInventory();
	g_session.CSession::ClearEquipItem();

	for( int i = 0; i < count; ++i )
	{
		PACKET_ZC_EQUIPMENT_ITEMLIST2::ITEM& item = packet.Item[i];

		ITEM_INFO itemInfo;
		itemInfo.m_itemType      = item.type;
		itemInfo.m_location      = item.location;
		itemInfo.m_num           = 1;
		itemInfo.m_itemIndex     = item.index;
		itemInfo.m_wearLocation  = item.wearLocation;
		itemInfo.m_slot[0]       = item.slot.info[0];
		itemInfo.m_slot[1]       = item.slot.info[1];
		itemInfo.m_slot[2]       = item.slot.info[2];
		itemInfo.m_slot[3]       = item.slot.info[3];
		itemInfo.ITEM_INFO::SetItemId(item.ITID);
		itemInfo.m_isIdentified  = item.IsIdentified;
		itemInfo.m_isDamaged     = ( item.isDamaged != 0 );
		itemInfo.m_refiningLevel = item.refiningLevel;
		itemInfo.m_deleteTime    = item.HireExpireDate;

		if( g_session.CSession::IsPetEgg(atoi(itemInfo.m_itemName.c_str())) && itemInfo.m_isDamaged )
			g_session.m_petEggIndex = itemInfo.m_itemIndex;

		if( itemInfo.m_wearLocation != 0 )
		{
			g_session.CSession::AddEquipItem(&itemInfo);
		}
		else
		{
			g_session.CSession::AddItem(&itemInfo);
			g_session.CSession::SetItem(&itemInfo);
		}
	}
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Store_Equipment_Itemlist2("CGameMode::Zc_Store_Equipment_Itemlist2");
void CGameMode::Zc_Store_Equipment_Itemlist2(const char* buf)
{
	return (this->*_Zc_Store_Equipment_Itemlist2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cart_Equipment_Itemlist2("CGameMode::Zc_Cart_Equipment_Itemlist2");
void CGameMode::Zc_Cart_Equipment_Itemlist2(const char* buf)
{
	return (this->*_Zc_Cart_Equipment_Itemlist2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cash_Time_Counter("CGameMode::Zc_Cash_Time_Counter");
void CGameMode::Zc_Cash_Time_Counter(const char* buf)
{
	return (this->*_Zc_Cash_Time_Counter)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cash_Item_Delete("CGameMode::Zc_Cash_Item_Delete");
void CGameMode::Zc_Cash_Item_Delete(const char* buf)
{
	return (this->*_Zc_Cash_Item_Delete)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Pickup_Ack2("CGameMode::Zc_Item_Pickup_Ack2");
void CGameMode::Zc_Item_Pickup_Ack2(const char* buf)
{
	return (this->*_Zc_Item_Pickup_Ack2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mer_Init("CGameMode::Zc_Mer_Init");
void CGameMode::Zc_Mer_Init(const char* buf)
{
	return (this->*_Zc_Mer_Init)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mer_Par_Change("CGameMode::Zc_Mer_Par_Change");
void CGameMode::Zc_Mer_Par_Change(const char* buf)
{
	return (this->*_Zc_Mer_Par_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_All_Quest_List("CGameMode::Zc_All_Quest_List");
void CGameMode::Zc_All_Quest_List(const char* buf)
{
	return (this->*_Zc_All_Quest_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_All_Quest_Mission("CGameMode::Zc_All_Quest_Mission");
void CGameMode::Zc_All_Quest_Mission(const char* buf)
{
	return (this->*_Zc_All_Quest_Mission)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Quest("CGameMode::Zc_Add_Quest");
void CGameMode::Zc_Add_Quest(const char* buf)
{
	return (this->*_Zc_Add_Quest)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Del_Quest("CGameMode::Zc_Del_Quest");
void CGameMode::Zc_Del_Quest(const char* buf)
{
	return (this->*_Zc_Del_Quest)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Update_Mission_Hunt("CGameMode::Zc_Update_Mission_Hunt");
void CGameMode::Zc_Update_Mission_Hunt(const char* buf)
{
	return (this->*_Zc_Update_Mission_Hunt)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Active_Quest("CGameMode::Zc_Active_Quest");
void CGameMode::Zc_Active_Quest(const char* buf)
{
	return (this->*_Zc_Active_Quest)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Pickup_Party("CGameMode::Zc_Item_Pickup_Party");
void CGameMode::Zc_Item_Pickup_Party(const char* buf)
{
	return (this->*_Zc_Item_Pickup_Party)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ShortCut_Key_List("CGameMode::Zc_ShortCut_Key_List");
void CGameMode::Zc_ShortCut_Key_List(const char* buf)
{
	return (this->*_Zc_ShortCut_Key_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_EquipItem_Damaged("CGameMode::Zc_EquipItem_Damaged");
void CGameMode::Zc_EquipItem_Damaged(const char* buf)
{
	return (this->*_Zc_EquipItem_Damaged)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Npc_Chat("CGameMode::Zc_Npc_Chat");
void CGameMode::Zc_Npc_Chat(const char* buf)
{
	return (this->*_Zc_Npc_Chat)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Formatstring_Msg("CGameMode::Zc_Formatstring_Msg");
void CGameMode::Zc_Formatstring_Msg(const char* buf)
{
	return (this->*_Zc_Formatstring_Msg)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Party_Config("CGameMode::Zc_Party_Config");
void CGameMode::Zc_Party_Config(const char* buf)
{
	return (this->*_Zc_Party_Config)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_MemorialDungeon_Subscription_Info("CGameMode::Zc_MemorialDungeon_Subscription_Info");
void CGameMode::Zc_MemorialDungeon_Subscription_Info(const char* buf)
{
	return (this->*_Zc_MemorialDungeon_Subscription_Info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_MemorialDungeon_Subscription_Notify("CGameMode::Zc_MemorialDungeon_Subscription_Notify");
void CGameMode::Zc_MemorialDungeon_Subscription_Notify(const char* buf)
{
	return (this->*_Zc_MemorialDungeon_Subscription_Notify)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_MemorialDungeon_Info("CGameMode::Zc_MemorialDungeon_Info");
void CGameMode::Zc_MemorialDungeon_Info(const char* buf)
{
	return (this->*_Zc_MemorialDungeon_Info)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_MemorialDungeon_Notify("CGameMode::Zc_MemorialDungeon_Notify");
void CGameMode::Zc_MemorialDungeon_Notify(const char* buf)
{
	return (this->*_Zc_MemorialDungeon_Notify)(buf);
}


void CGameMode::Zc_Equipment_Itemlist3(const char* buf)
{
	PACKET_ZC_EQUIPMENT_ITEMLIST3& packet = *(PACKET_ZC_EQUIPMENT_ITEMLIST3*)buf;
	int count = (packet.Length - sizeof(packet)) / sizeof(PACKET_ZC_EQUIPMENT_ITEMLIST3::ITEM);

	g_session.CSession::ClearEquipItemInInventory();
	g_session.CSession::ClearEquipItem();

	for( int i = 0; i < count; ++i )
	{
		PACKET_ZC_EQUIPMENT_ITEMLIST3::ITEM& item = packet.Item[i];

		ITEM_INFO itemInfo;
		itemInfo.m_itemType      = item.type;
		itemInfo.m_location      = item.location;
		itemInfo.m_num           = 1;
		itemInfo.m_itemIndex     = item.index;
		itemInfo.m_wearLocation  = item.wearLocation;
		itemInfo.m_slot[0]       = item.slot.info[0];
		itemInfo.m_slot[1]       = item.slot.info[1];
		itemInfo.m_slot[2]       = item.slot.info[2];
		itemInfo.m_slot[3]       = item.slot.info[3];
		itemInfo.ITEM_INFO::SetItemId(item.ITID);
		itemInfo.m_isIdentified  = item.IsIdentified;
		itemInfo.m_isDamaged     = ( item.isDamaged != 0 );
		itemInfo.m_refiningLevel = item.refiningLevel;
		itemInfo.m_deleteTime    = item.HireExpireDate;
		itemInfo.m_isYours       = item.isBind;

		if( g_session.CSession::IsPetEgg(atoi(itemInfo.m_itemName.c_str())) && itemInfo.m_isDamaged )
			g_session.m_petEggIndex = itemInfo.m_itemIndex;

		if( itemInfo.m_wearLocation != 0 )
		{
			g_session.CSession::AddEquipItem(&itemInfo);
		}
		else
		{
			g_session.CSession::AddItem(&itemInfo);
			g_session.CSession::SetItem(&itemInfo);
		}
	}
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Store_Equipment_Itemlist3("CGameMode::Zc_Store_Equipment_Itemlist3");
void CGameMode::Zc_Store_Equipment_Itemlist3(const char* buf)
{
	return (this->*_Zc_Store_Equipment_Itemlist3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cart_Equipment_Itemlist3("CGameMode::Zc_Cart_Equipment_Itemlist3");
void CGameMode::Zc_Cart_Equipment_Itemlist3(const char* buf)
{
	return (this->*_Zc_Cart_Equipment_Itemlist3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_NotifyBindOnEquip("CGameMode::Zc_NotifyBindOnEquip");
void CGameMode::Zc_NotifyBindOnEquip(const char* buf)
{
	return (this->*_Zc_NotifyBindOnEquip)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Pickup_Ack3("CGameMode::Zc_Item_Pickup_Ack3");
void CGameMode::Zc_Item_Pickup_Ack3(const char* buf)
{
	return (this->*_Zc_Item_Pickup_Ack3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Isvr_Disconnect("CGameMode::Zc_Isvr_Disconnect");
void CGameMode::Zc_Isvr_Disconnect(const char* buf)
{
	return (this->*_Zc_Isvr_Disconnect)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_EquipwinMicroscope("CGameMode::Zc_EquipwinMicroscope");
void CGameMode::Zc_EquipwinMicroscope(const char* buf)
{
	return (this->*_Zc_EquipwinMicroscope)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Config("CGameMode::Zc_Config");
void CGameMode::Zc_Config(const char* buf)
{
	return (this->*_Zc_Config)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Config_Notify("CGameMode::Zc_Config_Notify");
void CGameMode::Zc_Config_Notify(const char* buf)
{
	return (this->*_Zc_Config_Notify)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Battlefield_Chat("CGameMode::Zc_Battlefield_Chat");
void CGameMode::Zc_Battlefield_Chat(const char* buf)
{
	return (this->*_Zc_Battlefield_Chat)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Battlefield_Notify_Campinfo("CGameMode::Zc_Battlefield_Notify_Campinfo");
void CGameMode::Zc_Battlefield_Notify_Campinfo(const char* buf)
{
	return (this->*_Zc_Battlefield_Notify_Campinfo)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Battlefield_Notify_Point("CGameMode::Zc_Battlefield_Notify_Point");
void CGameMode::Zc_Battlefield_Notify_Point(const char* buf)
{
	return (this->*_Zc_Battlefield_Notify_Point)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Battlefield_Notify_Position("CGameMode::Zc_Battlefield_Notify_Position");
void CGameMode::Zc_Battlefield_Notify_Position(const char* buf)
{
	return (this->*_Zc_Battlefield_Notify_Position)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Battlefield_Notify_Hp("CGameMode::Zc_Battlefield_Notify_Hp");
void CGameMode::Zc_Battlefield_Notify_Hp(const char* buf)
{
	return (this->*_Zc_Battlefield_Notify_Hp)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mapproperty("CGameMode::Zc_Mapproperty");
void CGameMode::Zc_Mapproperty(const char* buf)
{
	return (this->*_Zc_Mapproperty)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Normal_Itemlist3("CGameMode::Zc_Normal_Itemlist3");
void CGameMode::Zc_Normal_Itemlist3(const char* buf)
{
	return (this->*_Zc_Normal_Itemlist3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cart_Normal_Itemlist3("CGameMode::Zc_Cart_Normal_Itemlist3");
void CGameMode::Zc_Cart_Normal_Itemlist3(const char* buf)
{
	return (this->*_Zc_Cart_Normal_Itemlist3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Store_Normal_Itemlist3("CGameMode::Zc_Store_Normal_Itemlist3");
void CGameMode::Zc_Store_Normal_Itemlist3(const char* buf)
{
	return (this->*_Zc_Store_Normal_Itemlist3)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Accept_Enter2("CGameMode::Zc_Accept_Enter2");
void CGameMode::Zc_Accept_Enter2(const char* buf)
{
	return (this->*_Zc_Accept_Enter2)(buf);
}


//NOTE: only actually supports v7
hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Moveentry4("CGameMode::Zc_Notify_Moveentry4");
void CGameMode::Zc_Notify_Moveentry4(const char* buf)
{
	return (this->*_Zc_Notify_Moveentry4)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Newentry4("CGameMode::Zc_Notify_Newentry4");
void CGameMode::Zc_Notify_Newentry4(const char* buf)
{
	return (this->*_Zc_Notify_Newentry4)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Standentry4("CGameMode::Zc_Notify_Standentry4");
void CGameMode::Zc_Notify_Standentry4(const char* buf)
{
	return (this->*_Zc_Notify_Standentry4)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Font("CGameMode::Zc_Notify_Font");
void CGameMode::Zc_Notify_Font(const char* buf)
{
	return (this->*_Zc_Notify_Font)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Progress("CGameMode::Zc_Progress");
void CGameMode::Zc_Progress(const char* buf)
{
	return (this->*_Zc_Progress)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Progress_Cancel("CGameMode::Zc_Progress_Cancel");
void CGameMode::Zc_Progress_Cancel(const char* buf)
{
	return (this->*_Zc_Progress_Cancel)(buf);
}


void CGameMode::Inner_Zc_Item_Fall_Entry2(const unsigned long in_ITAID, const unsigned short in_ITID, const bool in_IsIdentified, const short in_count, const short in_xPos, const short in_yPos, const unsigned char in_subX, const unsigned char in_subY)
{
	ITEMSTANDENTRYSTRUCT s = {};
	_itoa(in_ITID, s.name, 10);
	s.ITAID = in_ITAID;
	s.x = in_xPos;
	s.y = in_yPos;
	s.subX = in_subX;
	s.subY = in_subY;
	s.isJumpEntry = TRUE;
	s.count = in_count;
	s.isIdentified = in_IsIdentified;

	CItem* item = m_world->CWorld::GetItemByAID(in_ITAID);
	if( item == NULL )
	{
		item = new CItem();
		m_world->m_gameObjectList.push_back(item);
		m_world->m_itemList.push_back(item);
	}

	item->SendMsg(NULL, AM_4, (int)&s, 0, 0);
}


void CGameMode::Zc_Item_Fall_Entry2(const char* buf)
{
	const PACKET_ZC_ITEM_FALL_ENTRY2& packet = *reinterpret_cast<const PACKET_ZC_ITEM_FALL_ENTRY2*>(buf);

	const_cast<char*>(buf)[5] ^= buf[13];
	const_cast<char*>(buf)[7] ^= buf[8];
	this->CGameMode::Inner_Zc_Item_Fall_Entry2(packet.ITAID, packet.ITID, packet.IsIdentified, packet.count, packet.xPos, packet.yPos, packet.subX, packet.subY);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Moveentry5("CGameMode::Zc_Notify_Moveentry5");
void CGameMode::Zc_Notify_Moveentry5(const char* buf)
{
	return (this->*_Zc_Notify_Moveentry5)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Npc_Standentry("CGameMode::Zc_Notify_Npc_Standentry");
void CGameMode::Zc_Notify_Npc_Standentry(const char* buf)
{
	return (this->*_Zc_Notify_Npc_Standentry)(buf);
}


void CGameMode::Zc_Reassembly_Certify(const char* buf)
{
	const PACKET_ZC_REASSEMBLY_CERTIFY& packet = *reinterpret_cast<const PACKET_ZC_REASSEMBLY_CERTIFY*>(buf);

	PACKET_CZ_REASSEMBLY_IDENTITY cz_reassembly_identity = {};
	cz_reassembly_identity.PacketType = HEADER_CZ_REASSEMBLY_IDENTITY;
	cz_reassembly_identity.PacketLength = sizeof(cz_reassembly_identity);

	// winsock
	if( !CRagConnection::instanceR().CConnection::CheckModulePt() )
		cz_reassembly_identity.ImportAddressTableModify.Winsock = TRUE;

	// gdi32
	HMODULE hGDI32 = LoadLibraryA("GDI32.dll");
	if( hGDI32 != NULL )
	{
		if( (char*)GetProcAddress(hGDI32, "TextOutW") != (char*)&TextOutW )
			cz_reassembly_identity.ImportAddressTableModify.GDI32 = TRUE;

		FreeLibrary(hGDI32);
	}

	// debugging
	cz_reassembly_identity.ImportAddressTableModify.Debugging = IsDebuggerPresent();

	CRagConnection::instanceR().CRagConnection::SendPacket(cz_reassembly_identity.PacketLength, (char*)&cz_reassembly_identity);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Moveentry6("CGameMode::Zc_Notify_Moveentry6");
void CGameMode::Zc_Notify_Moveentry6(const char* buf)
{
	return (this->*_Zc_Notify_Moveentry6)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Standentry6("CGameMode::Zc_Notify_Standentry6");
void CGameMode::Zc_Notify_Standentry6(const char* buf)
{
	return (this->*_Zc_Notify_Standentry6)(buf);
}


void CGameMode::Inner_Zc_Item_Fall_Entry3(const unsigned long in_ITAID, const unsigned short in_ITID, const bool in_IsIdentified, const short in_count, const short in_xPos, const short in_yPos, const unsigned char in_subX, const unsigned char in_subY)
{
	ITEMSTANDENTRYSTRUCT s = {};
	_itoa(in_ITID, s.name, 10);
	s.ITAID = in_ITAID;
	s.x = in_xPos;
	s.y = in_yPos;
	s.subX = in_subX;
	s.subY = in_subY;
	s.isJumpEntry = TRUE;
	s.count = in_count;
	s.isIdentified = in_IsIdentified;

	CItem* item = m_world->CWorld::GetItemByAID(in_ITAID);
	if( item == NULL )
	{
		item = new CItem();
		m_world->m_gameObjectList.push_back(item);
		m_world->m_itemList.push_back(item);
	}

	item->SendMsg(NULL, AM_4, (int)&s, 0, 0);
}


void CGameMode::Zc_Item_Fall_Entry3(const char* buf)
{
	const PACKET_ZC_ITEM_FALL_ENTRY3& packet = *reinterpret_cast<const PACKET_ZC_ITEM_FALL_ENTRY3*>(buf);

	*(DWORD*)&buf[4] ^= *(WORD*)&buf[0] ^ (*(WORD*)&buf[11] + ((BYTE)buf[16] << 16));
	this->CGameMode::Inner_Zc_Item_Fall_Entry3(packet.ITAID, packet.ITID, packet.IsIdentified, packet.count, packet.xPos, packet.yPos, packet.subX, packet.subY);
}


void CGameMode::Zc_Notify_Act3(const char* buf)
{
	const PACKET_ZC_NOTIFY_ACT3& packet = *reinterpret_cast<const PACKET_ZC_NOTIFY_ACT3*>(buf);

	*(DWORD*)&buf[4] ^= *(WORD*)&buf[0] ^ (*(WORD*)&buf[24] + (*(WORD*)&buf[12] << 16));
	*(DWORD*)&buf[8] ^= *(DWORD*)&buf[12] + (*(WORD*)&buf[0] << 16);
	this->CGameMode::Zc_Notify_Act(packet.GID, packet.targetGID, packet.startTime, packet.attackMT, packet.attackedMT, packet.damage, packet.count, packet.action, packet.leftDamage);
}


hook_func<void (CGameMode::*)(mystd::string strMessage, int fontSize, COLORREF fontColor)> CGameMode::_Inner_Zc_Broadcast3("CGameMode::Inner_Zc_Broadcast3");
void CGameMode::Inner_Zc_Broadcast3(mystd::string strMessage, int fontSize, COLORREF fontColor)
{
	return (this->*_Inner_Zc_Broadcast3)(strMessage, fontSize, fontColor);
}


void CGameMode::Zc_Broadcast3(const char* buf)
{
	const PACKET_ZC_BROADCAST3& packet = *reinterpret_cast<const PACKET_ZC_BROADCAST3*>(buf);

	mystd::string text(packet.Text, packet.PacketLength - sizeof(packet));
	this->CGameMode::Inner_Zc_Broadcast3(text, packet.fontSize, packet.fontColor);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Postdelay("CGameMode::Zc_Skill_Postdelay");
void CGameMode::Zc_Skill_Postdelay(const char* buf)
{
	return (this->*_Zc_Skill_Postdelay)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Postdelay_List("CGameMode::Zc_Skill_Postdelay_List");
void CGameMode::Zc_Skill_Postdelay_List(const char* buf)
{
	return (this->*_Zc_Skill_Postdelay_List)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Msg_State_Change2("CGameMode::Zc_Msg_State_Change2");
void CGameMode::Zc_Msg_State_Change2(const char* buf)
{
	return (this->*_Zc_Msg_State_Change2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_MillenniumShield("CGameMode::Zc_MillenniumShield");
void CGameMode::Zc_MillenniumShield(const char* buf)
{
	return (this->*_Zc_MillenniumShield)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skillinfo_Delete("CGameMode::Zc_Skillinfo_Delete");
void CGameMode::Zc_Skillinfo_Delete(const char* buf)
{
	return (this->*_Zc_Skillinfo_Delete)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Select_Request("CGameMode::Zc_Skill_Select_Request");
void CGameMode::Zc_Skill_Select_Request(const char* buf)
{
	return (this->*_Zc_Skill_Select_Request)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Quest_Notify_Effect("CGameMode::Zc_Quest_Notify_Effect");
void CGameMode::Zc_Quest_Notify_Effect(const char* buf)
{
	return (this->*_Zc_Quest_Notify_Effect)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Groupinfo_Change_V2("CGameMode::Zc_Req_Groupinfo_Change_V2");
void CGameMode::Zc_Req_Groupinfo_Change_V2(const char* buf)
{
	return (this->*_Zc_Req_Groupinfo_Change_V2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ho_Par_Change("CGameMode::Zc_Ho_Par_Change");
void CGameMode::Zc_Ho_Par_Change(const char* buf)
{
	return (this->*_Zc_Ho_Par_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Seek_Party("CGameMode::Zc_Seek_Party");
void CGameMode::Zc_Seek_Party(const char* buf)
{
	return (this->*_Zc_Seek_Party)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skillinfo_Update2("CGameMode::Zc_Skillinfo_Update2");
void CGameMode::Zc_Skillinfo_Update2(const char* buf)
{
	return (this->*_Zc_Skillinfo_Update2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Msg_Value("CGameMode::Zc_Msg_Value");
void CGameMode::Zc_Msg_Value(const char* buf)
{
	return (this->*_Zc_Msg_Value)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ItemListWin_Open("CGameMode::Zc_ItemListWin_Open");
void CGameMode::Zc_ItemListWin_Open(const char* buf)
{
	return (this->*_Zc_ItemListWin_Open)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Msg_Skill("CGameMode::Zc_Msg_Skill");
void CGameMode::Zc_Msg_Skill(const char* buf)
{
	return (this->*_Zc_Msg_Skill)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Exp("CGameMode::Zc_Notify_Exp");
void CGameMode::Zc_Notify_Exp(const char* buf)
{
	return (this->*_Zc_Notify_Exp)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Newentry5("CGameMode::Zc_Notify_Newentry5");
void CGameMode::Zc_Notify_Newentry5(const char* buf)
{
	return (this->*_Zc_Notify_Newentry5)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Standentry5("CGameMode::Zc_Notify_Standentry5");
void CGameMode::Zc_Notify_Standentry5(const char* buf)
{
	return (this->*_Zc_Notify_Standentry5)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Delete_Item_From_Body("CGameMode::Zc_Delete_Item_From_Body");
void CGameMode::Zc_Delete_Item_From_Body(const char* buf)
{
	return (this->*_Zc_Delete_Item_From_Body)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Change_Group_Master("CGameMode::Zc_Change_Group_Master");
void CGameMode::Zc_Change_Group_Master(const char* buf)
{
	return (this->*_Zc_Change_Group_Master)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Broadcasting_Special_Item_Obtain("CGameMode::Zc_Broadcasting_Special_Item_Obtain");
void CGameMode::Zc_Broadcasting_Special_Item_Obtain(const char* buf)
{
	return (this->*_Zc_Broadcasting_Special_Item_Obtain)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Play_Npc_Bgm("CGameMode::Zc_Play_Npc_Bgm");
void CGameMode::Zc_Play_Npc_Bgm(const char* buf)
{
	return (this->*_Zc_Play_Npc_Bgm)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Define_Check("CGameMode::Zc_Define_Check");
void CGameMode::Zc_Define_Check(const char* buf)
{
	return (this->*_Zc_Define_Check)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Party_Booking_Ack_Register("CGameMode::Zc_Party_Booking_Ack_Register");
void CGameMode::Zc_Party_Booking_Ack_Register(const char* buf)
{
	return (this->*_Zc_Party_Booking_Ack_Register)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Party_Booking_Ack_Search("CGameMode::Zc_Party_Booking_Ack_Search");
void CGameMode::Zc_Party_Booking_Ack_Search(const char* buf)
{
	return (this->*_Zc_Party_Booking_Ack_Search)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Party_Booking_Ack_Delete("CGameMode::Zc_Party_Booking_Ack_Delete");
void CGameMode::Zc_Party_Booking_Ack_Delete(const char* buf)
{
	return (this->*_Zc_Party_Booking_Ack_Delete)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Party_Booking_Notify_Insert("CGameMode::Zc_Party_Booking_Notify_Insert");
void CGameMode::Zc_Party_Booking_Notify_Insert(const char* buf)
{
	return (this->*_Zc_Party_Booking_Notify_Insert)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Party_Booking_Notify_Update("CGameMode::Zc_Party_Booking_Notify_Update");
void CGameMode::Zc_Party_Booking_Notify_Update(const char* buf)
{
	return (this->*_Zc_Party_Booking_Notify_Update)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Party_Booking_Notify_Delete("CGameMode::Zc_Party_Booking_Notify_Delete");
void CGameMode::Zc_Party_Booking_Notify_Delete(const char* buf)
{
	return (this->*_Zc_Party_Booking_Notify_Delete)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Hp_To_Groupm_R2("CGameMode::Zc_Notify_Hp_To_Groupm_R2");
void CGameMode::Zc_Notify_Hp_To_Groupm_R2(const char* buf)
{
	return (this->*_Zc_Notify_Hp_To_Groupm_R2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Exchange_Item2("CGameMode::Zc_Add_Exchange_Item2");
void CGameMode::Zc_Add_Exchange_Item2(const char* buf)
{
	return (this->*_Zc_Add_Exchange_Item2)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Open_Buying_Store("CGameMode::Zc_Open_Buying_Store");
void CGameMode::Zc_Open_Buying_Store(const char* buf)
{
	return (this->*_Zc_Open_Buying_Store)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Failed_Open_Buying_Store_To_Buyer("CGameMode::Zc_Failed_Open_Buying_Store_To_Buyer");
void CGameMode::Zc_Failed_Open_Buying_Store_To_Buyer(const char* buf)
{
	return (this->*_Zc_Failed_Open_Buying_Store_To_Buyer)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Myitemlist_Buying_Store("CGameMode::Zc_Myitemlist_Buying_Store");
void CGameMode::Zc_Myitemlist_Buying_Store(const char* buf)
{
	return (this->*_Zc_Myitemlist_Buying_Store)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Buying_Store_Entry("CGameMode::Zc_Buying_Store_Entry");
void CGameMode::Zc_Buying_Store_Entry(const char* buf)
{
	return (this->*_Zc_Buying_Store_Entry)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Disappear_Buying_Store_Entry("CGameMode::Zc_Disappear_Buying_Store_Entry");
void CGameMode::Zc_Disappear_Buying_Store_Entry(const char* buf)
{
	return (this->*_Zc_Disappear_Buying_Store_Entry)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Itemlist_Buying_Store("CGameMode::Zc_Ack_Itemlist_Buying_Store");
void CGameMode::Zc_Ack_Itemlist_Buying_Store(const char* buf)
{
	return (this->*_Zc_Ack_Itemlist_Buying_Store)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Failed_Trade_Buying_Store_To_Buyer("CGameMode::Zc_Failed_Trade_Buying_Store_To_Buyer");
void CGameMode::Zc_Failed_Trade_Buying_Store_To_Buyer(const char* buf)
{
	return (this->*_Zc_Failed_Trade_Buying_Store_To_Buyer)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Update_Item_From_Buying_Store("CGameMode::Zc_Update_Item_From_Buying_Store");
void CGameMode::Zc_Update_Item_From_Buying_Store(const char* buf)
{
	return (this->*_Zc_Update_Item_From_Buying_Store)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Delete_Buying_Store("CGameMode::Zc_Item_Delete_Buying_Store");
void CGameMode::Zc_Item_Delete_Buying_Store(const char* buf)
{
	return (this->*_Zc_Item_Delete_Buying_Store)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_El_Init("CGameMode::Zc_El_Init");
void CGameMode::Zc_El_Init(const char* buf)
{
	return (this->*_Zc_El_Init)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_El_Par_Change("CGameMode::Zc_El_Par_Change");
void CGameMode::Zc_El_Par_Change(const char* buf)
{
	return (this->*_Zc_El_Par_Change)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Broadcast4("CGameMode::Zc_Broadcast4");
void CGameMode::Zc_Broadcast4(const char* buf)
{
	return (this->*_Zc_Broadcast4)(buf);
}


hook_func<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Failed_Trade_Buying_Store_To_Seller("CGameMode::Zc_Failed_Trade_Buying_Store_To_Seller");
void CGameMode::Zc_Failed_Trade_Buying_Store_To_Seller(const char* buf)
{
	return (this->*_Zc_Failed_Trade_Buying_Store_To_Seller)(buf);
}
