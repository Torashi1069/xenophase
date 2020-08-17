#include "Enum.h"
#include "GameMode.h"
#include "GameWorld.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Packet.h"
#include "Pc.h"
#include "Player.h"
#include "RagEffect.h"
#include "Skill.h"
#include "Struct.h"
#include "Device/Connection.h"
#include "Framework/Locale.h"
#include "Resource/Wave.h"
#include "Window/UIFrameWnd2.h"
#include "Window/UIGuildInfoManageWnd.h"
#include "Window/UIItemWnd.h"
#include "Window/UITransBalloonText.h"


hook_method<void (CGameMode::*)(void)> CGameMode::_PollNetworkStatus(SAKEXE, "CGameMode::PollNetworkStatus");
void CGameMode::PollNetworkStatus(void) // line 25
{
	return (this->*_PollNetworkStatus)();

	if( !g_connection.CConnection::Poll() )
		g_modeMgr.CModeMgr::GetCurMode()->SendMsg(MM_SOCKETERROR, 0, 0, 0);

	if( g_mustPumpOutReceiveQueue == TRUE )
	{
		unsigned long aid;
		if( g_connection.CConnection::Recv((char*)&aid, 4, true) )
			g_mustPumpOutReceiveQueue = FALSE;

		return;
	}

	char buf[20480];
	while( g_connection.CRagConnection::RecvPacket(buf) )
	{
		switch( g_connection.CRagConnection::GetPacketType(buf) )
		{
		case HEADER_ZC_NOTIFY_STANDENTRY: this->CGameMode::Zc_Notify_Standentry(buf); break;
		case HEADER_ZC_NOTIFY_STANDENTRY_NPC: this->CGameMode::Zc_Notify_Standentry_Npc(buf); break;
		case HEADER_ZC_NOTIFY_MOVEENTRY: this->CGameMode::Zc_Notify_Moveentry(buf); break;
		case HEADER_ZC_NOTIFY_VANISH: this->CGameMode::Zc_Notify_Vanish(buf); break;
		case HEADER_SC_NOTIFY_BAN: this->CGameMode::Sc_Notify_Ban(buf); break;
		case HEADER_ZC_NOTIFY_MOVE: this->CGameMode::Zc_Notify_Move(buf); break; // inlined
		case HEADER_ZC_NOTIFY_PLAYERMOVE: this->CGameMode::Zc_Notify_Playermove(buf); break; // inlined
		case HEADER_ZC_NOTIFY_ACT: this->CGameMode::Zc_Notify_Act(buf); break;
		case HEADER_ZC_NOTIFY_PLAYERCHAT: this->CGameMode::Zc_Notify_Playerchat(buf); break; // inlined
		case HEADER_ZC_NOTIFY_CHAT: this->CGameMode::Zc_Notify_Chat(buf); break;
		case HEADER_ZC_NOTIFY_TIME: this->CGameMode::Zc_Notify_Time(buf); break;
		case HEADER_ZC_NPCACK_MAPMOVE: this->CGameMode::Zc_Npcack_Mapmove(buf); // fall through
		case HEADER_ZC_NPCACK_ENABLE: this->CGameMode::Zc_Npcack_Enable(buf); break; // inlined
		case HEADER_ZC_NPCACK_SERVERMOVE: this->CGameMode::Zc_Npcack_Servermove(buf); break;
		case HEADER_ZC_ACCEPT_ENTER: this->CGameMode::Zc_Accept_Enter(buf); break;
		case HEADER_ZC_ACK_REQNAME: this->CGameMode::Zc_Ack_Reqname(buf); break; // inlined
		case HEADER_ZC_BROADCAST: this->CGameMode::Zc_Broadcast(buf); break;
		case HEADER_ZC_WHISPER: this->CGameMode::Zc_Whisper(buf); break;
		case HEADER_ZC_ACK_WHISPER: this->CGameMode::Zc_Ack_Whisper(buf); break;
		case HEADER_ZC_CHANGE_DIRECTION: this->CGameMode::Zc_Change_Direction(buf); break; // inlined
		case HEADER_ZC_ACK_DISCONNECT_CHARACTER: this->CGameMode::Zc_Ack_Disconnect_Character(buf); break; // inlined
		case HEADER_ZC_ITEM_ENTRY: this->CGameMode::Zc_Item_Entry(buf); break;
		case HEADER_ZC_ITEM_PICKUP_ACK: this->CGameMode::Zc_Item_Pickup_Ack(buf); break;
		case HEADER_ZC_ITEM_DISAPPEAR: this->CGameMode::Zc_Item_Disappear(buf); break; // inlined
		case HEADER_ZC_NORMAL_ITEMLIST: this->CGameMode::Zc_Normal_Itemlist(buf); break;
		case HEADER_ZC_NORMAL_ITEMLIST2: this->CGameMode::Zc_Normal_Itemlist2(buf); break;
		case HEADER_ZC_EQUIPMENT_ITEMLIST: this->CGameMode::Zc_Equipment_Itemlist(buf); break;
		case HEADER_ZC_ITEM_FALL_ENTRY: this->CGameMode::Zc_Item_Fall_Entry(buf); break;
		case HEADER_ZC_STOPMOVE: this->CGameMode::Zc_Stopmove(buf); break; // inlined
		case HEADER_ZC_PAR_CHANGE: this->CGameMode::Zc_Par_Change(buf); break;
		case HEADER_ZC_LONGPAR_CHANGE: this->CGameMode::Zc_Longpar_Change(buf); break;
		case HEADER_ZC_USE_ITEM_ACK: this->CGameMode::Zc_Use_Item_Ack(buf); break;
		case HEADER_ZC_REQ_WEAR_EQUIP_ACK: this->CGameMode::Zc_Req_Wear_Equip_Ack(buf); break;
		case HEADER_ZC_REQ_TAKEOFF_EQUIP_ACK: this->CGameMode::Zc_Req_Takeoff_Equip_Ack(buf); break; // inlined
		case HEADER_ZC_ITEM_THROW_ACK: this->CGameMode::Zc_Item_Throw_Ack(buf); break; // inlined
		case HEADER_ZC_SAY_DIALOG: this->CGameMode::Zc_Say_Dialog(buf); break; // inlined
		case HEADER_ZC_WAIT_DIALOG: this->CGameMode::Zc_Wait_Dialog(buf); break; // inlined
		case HEADER_ZC_CLOSE_DIALOG: this->CGameMode::Zc_Close_Dialog(buf); break; // inlined
		case HEADER_ZC_MENU_LIST: this->CGameMode::Zc_Menu_List(buf); break;
		case HEADER_ZC_RESTART_ACK: this->CGameMode::Zc_Restart_Ack(buf); break; // inlined
		case HEADER_ZC_STATUS_CHANGE_ACK: this->CGameMode::Zc_Status_Change_Ack(buf); break;
		case HEADER_ZC_STATUS: this->CGameMode::Zc_Status(buf); break;
		case HEADER_ZC_STATUS_CHANGE: this->CGameMode::Zc_Status_Change(buf); break;
		case HEADER_ZC_EMOTION: this->CGameMode::Zc_Emotion(buf); break; // inlined
		case HEADER_ZC_USER_COUNT: this->CGameMode::Zc_User_Count(buf); break; // inlined
		case HEADER_ZC_NOTIFY_NEWENTRY: this->CGameMode::Zc_Notify_Newentry(buf); break;
		case HEADER_ZC_SPRITE_CHANGE: this->CGameMode::Zc_Sprite_Change(buf); break;
		case HEADER_ZC_SELECT_DEALTYPE: this->CGameMode::Zc_Select_Dealtype(buf); break; // inlined
		case HEADER_ZC_PC_PURCHASE_ITEMLIST: this->CGameMode::Zc_Pc_Purchase_Itemlist(buf); break;
		case HEADER_ZC_PC_SELL_ITEMLIST: this->CGameMode::Zc_Pc_Sell_Itemlist(buf); break;
		case HEADER_ZC_PC_PURCHASE_RESULT: this->CGameMode::Zc_Pc_Purchase_Result(buf); break;
		case HEADER_ZC_PC_SELL_RESULT: this->CGameMode::Zc_Pc_Sell_Result(buf); break;
		case HEADER_ZC_SETTING_WHISPER_PC: this->CGameMode::Zc_Setting_Whisper_Pc(buf); break;
		case HEADER_ZC_SETTING_WHISPER_STATE: this->CGameMode::Zc_Setting_Whisper_State(buf); break;
		case HEADER_ZC_WHISPER_LIST: this->CGameMode::Zc_Whisper_List(buf); break;
		case HEADER_ZC_ACK_CREATE_CHATROOM: this->CGameMode::Zc_Ack_Create_Chatroom(buf); break;
		case HEADER_ZC_ROOM_NEWENTRY: this->CGameMode::Zc_Room_Newentry(buf); break;
		case HEADER_ZC_DESTROY_ROOM: this->CGameMode::Zc_Destroy_Room(buf); break; // inlined
		case HEADER_ZC_ENTER_ROOM: this->CGameMode::Zc_Enter_Room(buf); break;
		case HEADER_ZC_MEMBER_NEWENTRY: this->CGameMode::Zc_Member_Newentry(buf); break;
		case HEADER_ZC_MEMBER_EXIT: this->CGameMode::Zc_Member_Exit(buf); break;
		case HEADER_ZC_ROLE_CHANGE: this->CGameMode::Zc_Role_Change(buf); break; // inlined
		case HEADER_ZC_REFUSE_ENTER_ROOM: this->CGameMode::Zc_Refuse_Enter_Room(buf); break;
		case HEADER_ZC_CHANGE_CHATROOM: this->CGameMode::Zc_Change_Chatroom(buf); break;
		case HEADER_ZC_REQ_EXCHANGE_ITEM: this->CGameMode::Zc_Req_Exchange_Item(buf); break; // inlined
		case HEADER_ZC_REQ_EXCHANGE_ITEM2: this->CGameMode::Zc_Req_Exchange_Item2(buf); break; // inlined
		case HEADER_ZC_ACK_EXCHANGE_ITEM: this->CGameMode::Zc_Ack_Exchange_Item(buf); break;
		case HEADER_ZC_ACK_EXCHANGE_ITEM2: this->CGameMode::Zc_Ack_Exchange_Item2(buf); break;
		case HEADER_ZC_ADD_EXCHANGE_ITEM: this->CGameMode::Zc_Add_Exchange_Item(buf); break;
		case HEADER_ZC_ACK_ADD_EXCHANGE_ITEM: this->CGameMode::Zc_Ack_Add_Exchange_Item(buf); break;
		case HEADER_ZC_CONCLUDE_EXCHANGE_ITEM: this->CGameMode::Zc_Conclude_Exchange_Item(buf); break; // inlined
		case HEADER_ZC_CANCEL_EXCHANGE_ITEM: this->CGameMode::Zc_Cancel_Exchange_Item(buf); break; // inlined
		case HEADER_ZC_EXEC_EXCHANGE_ITEM: this->CGameMode::Zc_Exec_Exchange_Item(buf); break; // inlined
		case HEADER_ZC_EXCHANGEITEM_UNDO: this->CGameMode::Zc_Exchangeitem_Undo(buf); break; // inlined
		case HEADER_ZC_STORE_NORMAL_ITEMLIST: this->CGameMode::Zc_Store_Normal_Itemlist(buf); break;
		case HEADER_ZC_STORE_NORMAL_ITEMLIST2: this->CGameMode::Zc_Store_Normal_Itemlist2(buf); break;
		case HEADER_ZC_STORE_EQUIPMENT_ITEMLIST: this->CGameMode::Zc_Store_Equipment_Itemlist(buf); break;
		case HEADER_ZC_ADD_ITEM_TO_STORE: this->CGameMode::Zc_Add_Item_To_Store(buf); break;
		case HEADER_ZC_DELETE_ITEM_FROM_STORE: this->CGameMode::Zc_Delete_Item_From_Store(buf); break;
		case HEADER_ZC_CLOSE_STORE: this->CGameMode::Zc_Close_Store(buf); break; // inlined
		case HEADER_ZC_NOTIFY_STOREITEM_COUNTINFO: this->CGameMode::Zc_Notify_Storeitem_Countinfo(buf); break; // inlined
		case HEADER_ZC_ACK_MAKE_GROUP: this->CGameMode::Zc_Ack_Make_Group(buf); break; // inlined
		case HEADER_ZC_GROUP_LIST: this->CGameMode::Zc_Group_List(buf); break;
		case HEADER_ZC_ACK_REQ_JOIN_GROUP: this->CGameMode::Zc_Ack_Req_Join_Group(buf); break;
		case HEADER_ZC_REQ_JOIN_GROUP: this->CGameMode::Zc_Req_Join_Group(buf); break; // inlined
		case HEADER_ZC_REQ_COUPLE: this->CGameMode::Zc_Req_Couple(buf); break; // inlined
		case HEADER_ZC_REQ_BABY: this->CGameMode::Zc_Req_Baby(buf); break; // inlined
		case HEADER_ZC_ADD_MEMBER_TO_GROUP: this->CGameMode::Zc_Add_Member_To_Group(buf); break;
		case HEADER_ZC_ADD_MEMBER_TO_GROUP2: this->CGameMode::Zc_Add_Member_To_Group2(buf); break;
		case HEADER_ZC_DELETE_MEMBER_FROM_GROUP: this->CGameMode::Zc_Delete_Member_From_Group(buf); break;
		case HEADER_ZC_NOTIFY_HP_TO_GROUPM: this->CGameMode::Zc_Notify_Hp_To_Groupm(buf); break; // inlined
		case HEADER_ZC_NOTIFY_POSITION_TO_GROUPM: this->CGameMode::Zc_Notify_Position_To_Groupm(buf); break; // inlined
		case HEADER_ZC_NOTIFY_CHAT_PARTY: this->CGameMode::Zc_Notify_Chat_Party(buf); break;
		case HEADER_ZC_MVP_GETTING_ITEM: this->CGameMode::Zc_Mvp_Getting_Item(buf); break;
		case HEADER_ZC_MVP_GETTING_SPECIAL_EXP: this->CGameMode::Zc_Mvp_Getting_Special_Exp(buf); break; // inlined
		case HEADER_ZC_MVP: this->CGameMode::Zc_Mvp(buf); break; // inlined
		case HEADER_ZC_THROW_MVPITEM: this->CGameMode::Zc_Throw_Mvpitem(buf); break; // inlined
		case HEADER_ZC_SKILLINFO_UPDATE: this->CGameMode::Zc_Skillinfo_Update(buf); break; // inlined
		case HEADER_ZC_SKILLINFO_LIST: this->CGameMode::Zc_Skillinfo_List(buf); break;
		case HEADER_ZC_ACK_TOUSESKILL: this->CGameMode::Zc_Ack_Touseskill(buf); break;
		case HEADER_ZC_ADD_SKILL: this->CGameMode::Zc_Add_Skill(buf); break; // inlined
		case HEADER_ZC_NOTIFY_SKILL: this->CGameMode::Zc_Notify_Skill(buf); break;
		case HEADER_ZC_NOTIFY_GROUNDSKILL: this->CGameMode::Zc_Notify_Groundskill(buf); break;
		case HEADER_ZC_STATE_CHANGE: this->CGameMode::Zc_State_Change(buf); break;
		case HEADER_ZC_USE_SKILL: this->CGameMode::Zc_Use_Skill(buf); break;
		case HEADER_ZC_SKILL_ENTRY: this->CGameMode::Zc_Skill_Entry(buf); break;
		case HEADER_ZC_SKILL_DISAPPEAR: this->CGameMode::Zc_Skill_Disappear(buf); break; // inlined
		case HEADER_ZC_NOTIFY_ACT_POSITION: this->CGameMode::Zc_Notify_Act_Position(buf); break;
		case HEADER_ZC_NOTIFY_SKILL_POSITION: this->CGameMode::Zc_Notify_Skill_Position(buf); break;
		case HEADER_ZC_WARPLIST: this->CGameMode::Zc_Warplist(buf); break;
		case HEADER_ZC_ACK_REMEMBER_WARPPOINT: this->CGameMode::Zc_Ack_Remember_Warppoint(buf); break; // inlined
		case HEADER_ZC_NOTIFY_CARTITEM_COUNTINFO: this->CGameMode::Zc_Notify_Cartitem_Countinfo(buf); break; // inlined
		case HEADER_ZC_CART_NORMAL_ITEMLIST: this->CGameMode::Zc_Cart_Normal_Itemlist(buf); break;
		case HEADER_ZC_CART_NORMAL_ITEMLIST2: this->CGameMode::Zc_Cart_Normal_Itemlist2(buf); break;
		case HEADER_ZC_CART_EQUIPMENT_ITEMLIST: this->CGameMode::Zc_Cart_Equipment_Itemlist(buf); break;
		case HEADER_ZC_CARTOFF: this->CGameMode::Zc_Cartoff(buf); break; // inlined
		case HEADER_ZC_ACK_ADDITEM_TO_CART: this->CGameMode::Zc_Ack_Additem_To_Cart(buf); break; // inlined
		case HEADER_ZC_ADD_ITEM_TO_CART: this->CGameMode::Zc_Add_Item_To_Cart(buf); break;
		case HEADER_ZC_DELETE_ITEM_FROM_CART: this->CGameMode::Zc_Delete_Item_From_Cart(buf); break;
		case HEADER_ZC_OPENSTORE: this->CGameMode::Zc_openstore(buf); break;
		case HEADER_ZC_STORE_ENTRY: this->CGameMode::Zc_store_entry(buf); break; // inlined
		case HEADER_ZC_DISAPPEAR_ENTRY: this->CGameMode::Zc_disappear_entry(buf); break; // inlined
		case HEADER_ZC_PC_PURCHASE_ITEMLIST_FROMMC: this->CGameMode::Zc_pc_purchase_itemlist_frommc(buf); break;
		case HEADER_ZC_PC_PURCHASE_RESULT_FROMMC: this->CGameMode::Zc_pc_purchase_result_frommc(buf); break;
		case HEADER_ZC_PC_PURCHASE_MYITEMLIST: this->CGameMode::Zc_pc_purchase_myitemlist(buf); break;
		case HEADER_ZC_DELETEITEM_FROM_MCSTORE: this->CGameMode::Zc_deleteitem_from_mcstore(buf); break;
		case HEADER_ZC_ATTACK_FAILURE_FOR_DISTANCE: this->CGameMode::Zc_attack_failure_for_distance(buf); break; // inlined
		case HEADER_ZC_ATTACK_RANGE: this->CGameMode::Zc_attack_range(buf); break; // inlined
		case HEADER_ZC_ACTION_FAILURE: this->CGameMode::Zc_action_failure(buf); break;
		case HEADER_ZC_EQUIP_ARROW: this->CGameMode::Zc_equip_arrow(buf); break; // inlined
		case HEADER_ZC_RECOVERY: this->CGameMode::Zc_recovery(buf); break;
		case HEADER_ZC_USESKILL_ACK: this->CGameMode::Zc_useskill_ack(buf); break;
		case HEADER_ZC_GROUPINFO_CHANGE: this->CGameMode::Zc_groupinfo_change(buf); break;
		case HEADER_ZC_COUPLESTATUS: this->CGameMode::Zc_couplestatus(buf); break;
		case HEADER_ZC_OPEN_EDITDLG: this->CGameMode::Zc_open_editdlg(buf); break; // inlined
		case HEADER_ZC_COMPASS: this->CGameMode::Zc_compass(buf); break;
		case HEADER_ZC_SHOW_IMAGE: this->CGameMode::Zc_show_image(buf); break; // inlined
		case HEADER_ZC_SHOW_IMAGE2: this->CGameMode::Zc_show_image2(buf); break; // inlined
		case HEADER_ZC_AUTORUN_SKILL: this->CGameMode::Zc_autorun_skill(buf); break; // inlined
		case HEADER_ZC_RESURRECTION: this->CGameMode::Zc_resurrection(buf); break;
		case HEADER_ZC_GUILD_EMBLEM_IMG: this->CGameMode::Zc_guild_emblem_img(buf); break; // inlined
		case HEADER_ZC_GUILD_INFO: this->CGameMode::Zc_guild_info(buf); break;
		case HEADER_ZC_RESULT_MAKE_GUILD: this->CGameMode::Zc_result_make_guild(buf); break; // inlined
		case HEADER_ZC_ACK_REQ_JOIN_GUILD: this->CGameMode::Zc_ack_req_join_guild(buf); break; // inlined
		case HEADER_ZC_REQ_JOIN_GUILD: this->CGameMode::Zc_req_join_guild(buf); break; // inlined
		case HEADER_ZC_MYGUILD_BASIC_INFO: this->CGameMode::Zc_myguild_basic_info(buf); break;
		case HEADER_ZC_ACK_GUILD_MENUINTERFACE: this->CGameMode::Zc_ack_guild_menuinterface(buf); break; // inlined
		case HEADER_ZC_MEMBERMGR_INFO: this->CGameMode::Zc_membermgr_info(buf); break;
		case HEADER_ZC_ACK_REQ_CHANGE_MEMBERS: this->CGameMode::Zc_ack_req_change_members(buf); break; // inlined
		case HEADER_ZC_ACK_LEAVE_GUILD: this->CGameMode::Zc_ack_leave_guild(buf); break;
		case HEADER_ZC_ACK_BAN_GUILD: this->CGameMode::Zc_ack_ban_guild(buf); break;
		case HEADER_ZC_ACK_DISORGANIZE_GUILD_RESULT: this->CGameMode::Zc_ack_disorganize_guild_result(buf); break; // inlined
		case HEADER_ZC_ACK_DISORGANIZE_GUILD: this->CGameMode::Zc_ack_disorganize_guild(buf); break; // inlined
		case HEADER_ZC_POSITION_INFO: this->CGameMode::Zc_position_info(buf); break;
		case HEADER_ZC_BAN_LIST: this->CGameMode::Zc_ban_list(buf); break;
		case HEADER_ZC_POSITION_ID_NAME_INFO: this->CGameMode::Zc_position_id_name_info(buf); break; // inlined
		case HEADER_ZC_UPDATE_GDID: this->CGameMode::Zc_update_gdid(buf); break; // inlined
		case HEADER_ZC_UPDATE_CHARSTAT: this->CGameMode::Zc_update_charstat(buf); break; // inlined
		case HEADER_ZC_UPDATE_CHARSTAT2: this->CGameMode::Zc_update_charstat2(buf); break; // inlined
		case HEADER_ZC_NOTIFY_MANNER_POINT_GIVEN: this->CGameMode::Zc_notify_manner_point_given(buf); break; // inlined
		case HEADER_ZC_GUILD_NOTICE: this->CGameMode::Zc_guild_notice(buf); break;
		case HEADER_ZC_GUILD_CHAT: this->CGameMode::Zc_guild_chat(buf); break; // inlined
		case HEADER_ZC_REQ_ALLY_GUILD: this->CGameMode::Zc_req_ally_guild(buf); break; // inlined
		case HEADER_ZC_ACK_REQ_ALLY_GUILD: this->CGameMode::Zc_ack_req_ally_guild(buf); break;
		case HEADER_ZC_ACK_CHANGE_GUILD_POSITIONINFO: this->CGameMode::Zc_ack_change_guild_positioninfo(buf); break;
		case HEADER_ZC_ITEMIDENTIFY_LIST: this->CGameMode::Zc_itemidentify_list(buf); break;
		case HEADER_ZC_ACK_ITEMIDENTIFY: this->CGameMode::Zc_ack_itemidentify(buf); break;
		case HEADER_ZC_ITEMCOMPOSITION_LIST: this->CGameMode::Zc_itemcomposition_list(buf); break;
		case HEADER_ZC_ACK_ITEMCOMPOSITION: this->CGameMode::Zc_ack_itemcomposition(buf); break;
		case HEADER_ZC_ACK_REQ_HOSTILE_GUILD: this->CGameMode::Zc_ack_req_hostile_guild(buf); break; // inlined
		case HEADER_ZC_MEMBER_ADD: this->CGameMode::Zc_member_add(buf); break;
		case HEADER_ZC_DELETE_RELATED_GUILD: this->CGameMode::Zc_delete_related_guild(buf); break; // inlined
		case HEADER_ZC_ADD_RELATED_GUILD: this->CGameMode::Zc_add_related_guild(buf); break;
		case HEADER_ZC_ACK_ITEMREFINING: this->CGameMode::Zc_ack_itemrefining(buf); break;
		case HEADER_ZC_NOTIFY_MAPINFO: this->CGameMode::Zc_notify_mapinfo(buf); break; // inlined
		case HEADER_ZC_ACK_REQ_DISCONNECT: this->CGameMode::Zc_ack_req_disconnect(buf); break; // inlined
		case HEADER_ZC_MONSTER_INFO: this->CGameMode::Zc_monster_info(buf); break; // inlined
		case HEADER_ZC_MAKABLEITEMLIST: this->CGameMode::Zc_makable_item_list(buf); break;
		case HEADER_ZC_ACK_REQMAKINGITEM: this->CGameMode::Zc_ack_req_itemmaking(buf); break;
		case HEADER_ZC_TALKBOX_CHATCONTENTS: this->CGameMode::Zc_talkbox_chat_contents(buf); break;
		case HEADER_ZC_UPDATE_MAPINFO: this->CGameMode::Zc_update_mapinfo(buf); break; // inlined
		case HEADER_ZC_ACK_REQNAME_BYGID: this->CGameMode::Zc_Ack_Reqname_bygid(buf); break;
		case HEADER_ZC_ACK_REQNAMEALL: this->CGameMode::Zc_Ack_Reqnameall(buf); break;
		case HEADER_ZC_MSG_STATE_CHANGE: this->CGameMode::Zc_Msg_State_Change(buf); break;
		case HEADER_ZC_NOTIFY_MAPPROPERTY: this->CGameMode::Zc_Notify_Mapproperty(buf); break;
		case HEADER_ZC_NOTIFY_RANKING: this->CGameMode::Zc_Notify_Ranking(buf); break;
		case HEADER_ZC_NOTIFY_EFFECT: this->CGameMode::Zc_Notify_Effect(buf); break;
		case HEADER_ZC_NOTIFY_EFFECT2: this->CGameMode::Zc_Notify_Effect2(buf); break;
		case HEADER_ZC_START_CAPTURE: this->CGameMode::Zc_Start_Capture(buf); break;
		case HEADER_ZC_START_COUPLE: this->CGameMode::Zc_Start_Couple(buf); break;
		case HEADER_ZC_START_BABY: this->CGameMode::Zc_Start_Baby(buf); break;
		case HEADER_ZC_COUPLENAME: this->CGameMode::Zc_CoupleName(buf); break;
		case HEADER_ZC_CONGRATULATION: this->CGameMode::Zc_Congratulation(buf); break;
		case HEADER_ZC_TRYCAPTURE_MONSTER: this->CGameMode::Zc_TryCapture_Monster(buf); break;
		case HEADER_ZC_PETEGG_LIST: this->CGameMode::Zc_PetEgg_List(buf); break;
		case HEADER_ZC_CHANGESTATE_PET: this->CGameMode::Zc_Change_Pet_Status(buf); break;
		case HEADER_ZC_PROPERTY_PET: this->CGameMode::Zc_Property_Pet(buf); break;
		case HEADER_ZC_FEED_PET: this->CGameMode::Zc_Feed_Pet(buf); break;
		case HEADER_ZC_PET_ACT: this->CGameMode::Zc_Pet_Act(buf); break;
		case HEADER_ZC_PAR_CHANGE_USER: this->CGameMode::Zc_Par_Change_User(buf); break;
		case HEADER_ZC_SKILL_UPDATE: this->CGameMode::Zc_Skill_Update(buf); break;
		case HEADER_ZC_MAKINGARROW_LIST: this->CGameMode::Zc_MakingArrowList(buf); break;
		case HEADER_ZC_NPCSPRITE_CHANGE: this->CGameMode::Zc_NpcSpriteChange(buf); break;
		case HEADER_ZC_SHOWDIGIT: this->CGameMode::Zc_ShowDigit(buf); break;
		case HEADER_ZC_CHANGE_GUILD: this->CGameMode::Zc_ChangeGuild(buf); break;
		case HEADER_ZC_GUILD_INFO2: this->CGameMode::Zc_GuildInfo2(buf); break;
		case HEADER_ZC_GUILD_ZENY_ACK: this->CGameMode::Zc_GuildZenyAck(buf); break;
		case HEADER_ZC_DISPEL: this->CGameMode::Zc_Dispel(buf); break;
		case HEADER_ZC_REPLY_REMAINTIME: this->CGameMode::Zc_Reply_RemainTime(buf); break;
		case HEADER_ZC_INFO_REMAINTIME: this->CGameMode::Zc_Info_RemainTime(buf); break;
		case HEADER_ZC_BROADCAST2: this->CGameMode::Zc_Broadcast2(buf); break;
		case HEADER_ZC_GUILD_SKILLINFO: this->CGameMode::Zc_GuildSkillInfo(buf); break;
		case HEADER_ZC_ADD_ITEM_TO_STORE2: this->CGameMode::Zc_AddItemToStore2(buf); break;
		case HEADER_ZC_ADD_ITEM_TO_CART2: this->CGameMode::Zc_Add_Item_To_Cart2(buf); break;
		case HEADER_SC_ACK_ENCRYPTION: this->CGameMode::Sc_Ack_Encryption(buf); break; // inlined
		case HEADER_ZC_USE_ITEM_ACK2: this->CGameMode::Zc_Use_Item_Ack2(buf); break;
		case HEADER_ZC_SKILL_ENTRY2: this->CGameMode::Zc_Skill_Entry2(buf); break;
		case HEADER_ZC_AUTOSPELLLIST: this->CGameMode::Zc_AutoSpellList(buf); break;
		case HEADER_ZC_DEVOTIONLIST: this->CGameMode::Zc_DevotionList(buf); break;
		case HEADER_ZC_SPIRITS: this->CGameMode::Zc_Spirits(buf); break;
		case HEADER_ZC_SPIRITS2: this->CGameMode::Zc_Spirits2(buf); break;
		case HEADER_ZC_BLADESTOP: this->CGameMode::Zc_BladeStop(buf); break;
		case HEADER_ZC_COMBODELAY: this->CGameMode::Zc_ComboDelay(buf); break;
		case HEADER_ZC_SOUND: this->CGameMode::Zc_Sound(buf); break;
		case HEADER_ZC_OPEN_EDITDLGSTR: this->CGameMode::Zc_Open_EditDlgStr(buf); break;
		case HEADER_ZC_NOTIFY_MAPPROPERTY2: this->CGameMode::Zc_Notify_Mapproperty2(buf); break;
		case HEADER_ZC_SPRITE_CHANGE2: this->CGameMode::Zc_Sprite_Change2(buf); break;
		case HEADER_ZC_NOTIFY_STANDENTRY2: this->CGameMode::Zc_Notify_Standentry2(buf); break;
		case HEADER_ZC_NOTIFY_NEWENTRY2: this->CGameMode::Zc_Notify_Newentry2(buf); break;
		case HEADER_ZC_NOTIFY_MOVEENTRY2: this->CGameMode::Zc_Notify_Moveentry2(buf); break;
		case HEADER_ZC_NOTIFY_SKILL2: this->CGameMode::Zc_Notify_Skill2(buf); break;
		case HEADER_ZC_ACK_ACCOUNTNAME: this->CGameMode::Zc_Ack_AccountName(buf); break;
		case HEADER_ZC_NOTIFY_INITCHAR: break;
		case HEADER_ZC_NOTIFY_UPDATECHAR: break;
		case HEADER_ZC_NOTIFY_UPDATEPLAYER: break;
		case HEADER_ZC_NOTIFY_ACTENTRY: this->CGameMode::Zc_Notify_Actentry(buf); break; // inlined
		case HEADER_ZC_ACCEPT_QUIT: this->CGameMode::Zc_Accept_Quit(buf); break; // inlined
		case HEADER_ZC_REFUSE_QUIT: this->CGameMode::Zc_Refuse_Quit(buf); break; // inlined
		case HEADER_ZC_ACK_GIVE_MANNER_POINT: this->CGameMode::Zc_ack_give_manner_point(buf); break; // inlined
		case HEADER_ZC_ACK_OPEN_MEMBER_INFO: this->CGameMode::Zc_ack_open_member_info(buf); break; // inlined
		case HEADER_ZC_OTHER_GUILD_LIST: this->CGameMode::Zc_other_guild_list(buf); break; // inlined
		case HEADER_PING: break;
		case HEADER_ZC_MONSTER_TALK: this->CGameMode::Zc_Monster_Talk(buf); break; // inlined
		default:
			g_connection.CConnection::ResetQueue();
			break;
		}
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Newentry(SAKEXE, "CGameMode::Zc_Notify_Newentry");
void CGameMode::Zc_Notify_Newentry(const char* buf) // line 817-960
{
	return (this->*_Zc_Notify_Newentry)(buf);

	PACKET_ZC_NOTIFY_NEWENTRY& packet = *(PACKET_ZC_NOTIFY_NEWENTRY*)buf;

	STANDENTRYSTRUCT s;
	s.GID = packet.GID;
	s.job = packet.job;
	s.sex = packet.sex;
	s.speed = packet.speed;
	s.xSize = packet.xSize;
	s.ySize = packet.ySize;
	s.head = packet.head;
	s.weapon = packet.weapon;
	s.accessory = packet.accessory;
	s.healthState = packet.healthState;
	s.bodyState = packet.bodyState;
	s.effectState = packet.effectState;
	s.isPKModeON = packet.isPKModeON;
	s.shield = packet.shield;
	s.accessory2 = packet.accessory2;
	s.accessory3 = packet.accessory3;
	s.headpalette = packet.headpalette;
	s.bodypalette = packet.bodypalette;
	s.headDir = packet.headDir;
	s.guildId = packet.GUID;
	s.guildEmblemVersion = packet.GEmblemVer;
	s.honor = packet.honor;
	s.virtue = packet.virtue;
	s.state = 0;
	DecodePosDir(packet.PosDir, s.x, s.y, s.dir);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor == NULL )
	{
		bool isPc = false;

		if( packet.job < JT_WARPNPC || packet.job >= JT_2004_JOB_BEGIN )
		{
			isPc = true;
			actor = new CPc();
		}
		else
		{
			actor = this->CGameMode::NewNpc(packet.job);
			s.sex = SEX_FEMALE;
		}

		if( actor != NULL && s.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		m_world->m_gameObjectList.push_back(actor);
		m_world->m_actorList.push_back(actor);

		actor->SendMsg(NULL, AM_4_STANDENTRY_NEW, (int)&s, 2, 0);

		if( actor->CGameActor::GetJob() > JT_WARPNPC && actor->CGameActor::GetJob() < JT_2004_JOB_BEGIN )
		{
			int gdid = (packet.accessory2 << 16) | packet.accessory3;
			int version = packet.shield;

			if( gdid != 0 )
				actor->SetGuildInfo(gdid, version);
		}

		if( isPc && !IsGravityAid(packet.GID) && !IsEffectStateSpecialHiding(packet.effectState) )
			actor->CAbleToMakeEffect::LaunchEffect(344, vector3d(0.,0.,0.), 0.0);

		if( g_session.CSession::IsSiegeMode() && s.head != 20 && actor->m_emblemWnd == NULL )
		{
			if( g_session.CSession::IsPc(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
			else
			if( g_session.CSession::IsGuardian(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
		}
	}
	else
	{
		if( actor->CGameActor::GetJob() > JT_WARPNPC && actor->CGameActor::GetJob() < JT_2004_JOB_BEGIN )
		{
			int gdid = (packet.accessory2 << 16) | packet.accessory3;
			int version = packet.shield;

			if( gdid != 0 && actor->GetGdid() == 0 )
				actor->SetGuildInfo(gdid, version);
		}

		if( s.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		actor->SendMsg(NULL, AM_3_STANDENTRY_EXISTING, (int)&s, 0, 0);

		if( g_session.CSession::IsSiegeMode() && s.head != 20 && actor->m_emblemWnd == NULL )
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


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Standentry(SAKEXE, "CGameMode::Zc_Notify_Standentry");
void CGameMode::Zc_Notify_Standentry(const char* buf) // line 963
{
	return (this->*_Zc_Notify_Standentry)(buf);

	PACKET_ZC_NOTIFY_STANDENTRY& packet = *(PACKET_ZC_NOTIFY_STANDENTRY*)buf;

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
	s.headDir = packet.headDir;
	s.accessory3 = packet.accessory3;
	s.guildEmblemVersion = packet.GEmblemVer;
	s.bodypalette = packet.bodypalette;
	s.GID = packet.GID;
	s.guildId = packet.GUID;
	s.virtue = packet.virtue;
	s.honor = packet.honor;
	DecodePosDir(packet.PosDir, s.x, s.y, s.dir);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor == NULL )
	{
		if( packet.job < JT_WARPNPC || packet.job >= JT_2004_JOB_BEGIN )
		{
			actor = new CPc();
		}
		else
		{
			actor = this->CGameMode::NewNpc(packet.job);
			s.sex = 0;
		}

		if( actor != NULL && s.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		m_world->m_gameObjectList.push_back(actor);
		m_world->m_actorList.push_back(actor);

		if( actor != NULL )
		{
			actor->SendMsg(NULL, AM_4_STANDENTRY_NEW, (int)&s, 0, 0);

			if( g_session.CSession::IsSiegeMode() && s.head != 20 && actor->m_emblemWnd == NULL )
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

		if( s.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		actor->SendMsg(NULL, AM_3_STANDENTRY_EXISTING, (int)&s, 0, 0);

		if( g_session.CSession::IsSiegeMode() && s.head != 20 && actor->m_emblemWnd == NULL )
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


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Standentry_Npc(SAKEXE, "CGameMode::Zc_Notify_Standentry_Npc");
void CGameMode::Zc_Notify_Standentry_Npc(const char* buf) // line 1136
{
	return (this->*_Zc_Notify_Standentry_Npc)(buf);

	PACKET_ZC_NOTIFY_STANDENTRY_NPC& packet = *(PACKET_ZC_NOTIFY_STANDENTRY_NPC*)buf;

	STANDENTRYSTRUCT s;
	s.state = 0;
	s.guildId = 0;
	s.guildEmblemVersion = 0;
	s.honor = 0;
	s.virtue = 0;
	s.job = packet.job;
	s.sex = packet.sex;
	s.speed = packet.speed;
	s.xSize = packet.xSize;
	s.ySize = packet.ySize;
	s.head = packet.head;
	s.weapon = packet.weapon;
	s.accessory = packet.accessory;
	s.healthState = packet.healthState;
	s.bodyState = packet.bodyState;
	s.effectState = packet.effectState;
	s.shield = packet.shield;
	s.isPKModeON = packet.isPKModeON;
	s.accessory2 = packet.accessory2;
	s.accessory3 = packet.accessory3;
	s.headpalette = packet.headpalette;
	s.bodypalette = packet.bodypalette;
	s.headDir = packet.headDir;
	s.GID = packet.GID;
	DecodePosDir(packet.PosDir, s.x, s.y, s.dir);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor != NULL )
	{// existing entry
		actor->SendMsg(NULL, AM_3_STANDENTRY_EXISTING, (int)&s, 0, 0);

		if( actor->CGameActor::GetJob() > JT_WARPNPC && actor->CGameActor::GetJob() < JT_2004_JOB_BEGIN )
		{
			int gdid = (packet.accessory2 << 16) | packet.accessory3;
			int version = packet.shield;

			if( gdid != 0 && actor->GetGdid() == 0 )
				actor->SetGuildInfo(gdid, version);
		}
	}
	else
	{// new entry
		actor = this->CGameMode::NewNpc(packet.job);

		s.sex = 0;
		m_world->m_gameObjectList.push_back(actor);
		m_world->m_actorList.push_back(actor);

		actor->SendMsg(NULL, AM_4_STANDENTRY_NEW, (int)&s, 1, 0);

		if( actor->CGameActor::GetJob() > JT_WARPNPC && actor->CGameActor::GetJob() < JT_2004_JOB_BEGIN )
		{
			int gdid = (packet.accessory2 << 16) | packet.accessory3;
			int version = packet.shield;

			if( gdid != 0 )
				actor->SetGuildInfo(gdid, version);
		}
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Refuse_Quit(SAKEXE, "CGameMode::Zc_Refuse_Quit");
void CGameMode::Zc_Refuse_Quit(const char* buf) // line 1206
{
	return (this->*_Zc_Refuse_Quit)(buf);

	;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Move(SAKEXE, "CGameMode::Zc_Notify_Move");
void CGameMode::Zc_Notify_Move(const char* buf) // line 1209
{
	return (this->*_Zc_Notify_Move)(buf);

	PACKET_ZC_NOTIFY_MOVE& packet = *(PACKET_ZC_NOTIFY_MOVE*)buf;

	MOVESTRUCT ms;
	ms.startTime = packet.moveStartTime;
	DecodeSrcDst(packet.MoveData, ms.sx, ms.sy, ms.dx, ms.dy, ms.cellY, ms.cellX);

	g_session.CSession::UpdateServerTime(ms.startTime);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor != NULL )
		actor->SendMsg(NULL, 0, (int)&ms, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Playermove(SAKEXE, "CGameMode::Zc_Notify_Playermove");
void CGameMode::Zc_Notify_Playermove(const char* buf) // line 1222
{
	return (this->*_Zc_Notify_Playermove)(buf);

	PACKET_ZC_NOTIFY_PLAYERMOVE& packet = *(PACKET_ZC_NOTIFY_PLAYERMOVE*)buf;

	MOVESTRUCT ms;
	ms.startTime = packet.moveStartTime;
	DecodeSrcDst(packet.MoveData, ms.sx, ms.sy, ms.dy, ms.dx, ms.cellX, ms.cellY);

	g_session.CSession::UpdateServerTime(packet.moveStartTime);

	m_world->m_player->SendMsg(NULL, 0, (int)&ms, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Act(SAKEXE, "CGameMode::Zc_Notify_Act");
void CGameMode::Zc_Notify_Act(const char* buf) // line 1235
{
	return (this->*_Zc_Notify_Act)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Act_Position(SAKEXE, "CGameMode::Zc_Notify_Act_Position");
void CGameMode::Zc_Notify_Act_Position(const char* buf) // line 1307
{
	return (this->*_Zc_Notify_Act_Position)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Playerchat(SAKEXE, "CGameMode::Zc_Notify_Playerchat");
void CGameMode::Zc_Notify_Playerchat(const char* buf) // line 1334
{
	return (this->*_Zc_Notify_Playerchat)(buf);

	PACKET_ZC_NOTIFY_PLAYERCHAT& packet = *(PACKET_ZC_NOTIFY_PLAYERCHAT*)buf;

	char chatMsg[256];
	memcpy(chatMsg, packet.Text, packet.PacketLength - sizeof(packet));

	if( g_windowMgr.UIWindowMgr::GetChatRoomWnd() != NULL )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSH_INTO_CHATROOM, (int)chatMsg, 0x007800, 0);
	}
	else
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)chatMsg, 0x00FF00, 0);
		m_world->m_player->SendMsg(NULL, 7, (int)chatMsg, 0, 0);
	}

	if( g_session.m_isSaveChat != 0 )
		this->CGameMode::WriteChat(chatMsg);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Chat(SAKEXE, "CGameMode::Zc_Notify_Chat");
void CGameMode::Zc_Notify_Chat(const char* buf) // line 1353
{
	return (this->*_Zc_Notify_Chat)(buf);

	PACKET_ZC_NOTIFY_CHAT& packet = *(PACKET_ZC_NOTIFY_CHAT*)buf;

	if( g_session.CSession::IsExAid(packet.GID) )
		return;

	char chatMsg[256];
	memcpy(chatMsg, packet.Text, packet.PacketLength - sizeof(packet));

	if( g_windowMgr.UIWindowMgr::GetChatRoom() != NULL )
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSH_INTO_CHATROOM, (int)chatMsg, 0x222222, 0);
	else
	{
		if( IsNameYellow(packet.GID) )
		{
			if( g_serviceType == ServiceThai )
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)chatMsg, 0xFFFF00, 0);
			else
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)chatMsg, 0x00FFFF, 0);
		}
		else
		{
			if( !g_session.m_isNoTalkMsg )
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)chatMsg, 0xFFFFFF, 0);
		}

		CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
		if( actor != NULL )
			actor->SendMsg(NULL, 7, (int)chatMsg, 0, 0);
	}

	if( g_session.m_isSaveChat )
		this->CGameMode::WriteChat(chatMsg);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Time(SAKEXE, "CGameMode::Zc_Notify_Time");
void CGameMode::Zc_Notify_Time(const char* buf) // line 1389
{
	return (this->*_Zc_Notify_Time)(buf);

	PACKET_ZC_NOTIFY_TIME& packet = *(PACKET_ZC_NOTIFY_TIME*)buf;

	if( g_pingLog )
	{
		FILE* f = fopen("PingLog.txt", "at");
		if( f != NULL )
		{
			unsigned long time = g_pingLogList.front();
			fprintf(f, "%10.2f\t%10d\n", (double)(time - g_pingLogStart) / 1000., timeGetTime() - time);
			fclose(f);
		}

		g_pingLogList.pop_front();
	}

	if( m_numNotifyTime )
		g_session.CSession::UpdateServerTime(packet.time);
	else
		g_session.CSession::SetServerTime(packet.time);

	m_receiveSyneRequestTime = 1;
	m_numNotifyTime = m_numNotifyTime + 1;
	g_session.CSession::RecalcAveragePingTime(timeGetTime() - m_syncRequestTime);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Npcack_Mapmove(SAKEXE, "CGameMode::Zc_Npcack_Mapmove");
void CGameMode::Zc_Npcack_Mapmove(const char* buf) // line 1415
{
	return (this->*_Zc_Npcack_Mapmove)(buf);

	PACKET_ZC_NPCACK_MAPMOVE& packet = *(PACKET_ZC_NPCACK_MAPMOVE*)buf;

	g_session.m_posX = packet.xPos;
	g_session.m_posY = packet.yPos;

	char mapName[16+1];
	mapName[countof(mapName)-1] = '\0';
	memcpy(mapName, packet.mapName, sizeof(packet.mapName));

	mystd::string curMap = mapName;
	curMap.resize(curMap.size() - 4);

	if( strcmp(curMap.c_str(), g_session.m_curMap) != 0 )
	{// map change
		strcpy(g_session.m_curMap, curMap.c_str());

		curMap += ".rsw";
		g_modeMgr.CModeMgr::Switch(1, curMap.c_str());

		UIWaitWnd* wnd = (UIWaitWnd*)g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
		wnd->UIWaitWnd::SetMsg(MsgStr(MSI_PLEASE_BE_PATIENT), 17, 1);
	}
	else
	{// same map
		this->CGameMode::RemoveGameActorAllAndMake();
		this->CGameMode::Initialize();
		this->CMode::RunFadeOut(0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Npcack_Enable(SAKEXE, "CGameMode::Zc_Npcack_Enable");
void CGameMode::Zc_Npcack_Enable(const char* buf) // line 1443
{
	return (this->*_Zc_Npcack_Enable)(buf);

	PACKET_ZC_NPCACK_ENABLE& packet = *(PACKET_ZC_NPCACK_ENABLE*)buf;

	m_noMove = 0;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Npcack_Servermove(SAKEXE, "CGameMode::Zc_Npcack_Servermove");
void CGameMode::Zc_Npcack_Servermove(const char* buf) // line 1447
{
	return (this->*_Zc_Npcack_Servermove)(buf);

	PACKET_ZC_NPCACK_SERVERMOVE& packet = *(PACKET_ZC_NPCACK_SERVERMOVE*)buf;

	g_session.CSession::InitWhenServerMove();

	char mapName[16+1];
	mapName[countof(mapName)-1] = '\0';
	memcpy(mapName, packet.mapName, sizeof(packet.mapName));

	mystd::string curMap = mapName;
	curMap.resize(curMap.size() - 4);

	strcpy(g_session.m_curMap, curMap.c_str());
	g_session.m_posX = packet.xPos;
	g_session.m_posY = packet.yPos;

	strcpy(g_zoneServerAddr.ip, inet_ntoa(*(in_addr*)&packet.addr.ip));
	g_zoneServerAddr.port = packet.addr.port;

	g_connection.CConnection::Disconnect();
	stateId.clear();

	m_noMove = 1;
	m_noMoveStartTick = timeGetTime();
	m_world->m_player->SendMsg(NULL, 8, 0, 0, 0);

	m_isConnected = g_connection.CConnection::Connect(&g_zoneServerAddr);
	if( m_isConnected )
	{
		g_mustPumpOutReceiveQueue = TRUE;
		g_connection.CConnection::SetDelay(timeGetTime() + 1000);

		PACKET_CZ_ENTER p;
		p.PacketType = HEADER_CZ_ENTER;
		p.clientTime = timeGetTime();
		p.GID = g_session.CSession::GetGid();
		p.AID = g_session.CSession::GetAid();
		p.AuthCode = g_session.m_authCode;
		p.Sex = g_session.CSession::GetSex();
		g_connection.CRagConnection::SendPacket(g_connection.CRagConnection::GetPacketSize(HEADER_CZ_ENTER), (const char*)&p);

		g_connection.CConnection::SetBlock(true);

		UIWaitWnd* wnd = (UIWaitWnd*)g_windowMgr.UIWindowMgr::MakeWindow(WID_WAITWND);
		wnd->UIWaitWnd::SetMsg(MsgStr(MSI_WAITING_RESPONSE_FROM_SERVER), 16, 1);
	}
	else
	{
		g_connection.CConnection::Disconnect();

		if( g_windowMgr.UIWindowMgr::ErrorMsg(MsgStr(MSI_SERVER_CONNECTION_FAILED), 1, 1, 1, 0) != 178 )
			this->SendMsg(MM_QUIT_TO_IDENTRY, 0, 0, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Accept_Enter(SAKEXE, "CGameMode::Zc_Accept_Enter");
void CGameMode::Zc_Accept_Enter(const char* buf) // line 1501
{
	return (this->*_Zc_Accept_Enter)(buf);

	PACKET_ZC_ACCEPT_ENTER& packet = *(PACKET_ZC_ACCEPT_ENTER*)buf;

	g_session.CSession::SetServerTime(packet.startTime);

	int x, y, dir;
	DecodePosDir(packet.PosDir, x, y, dir);
	g_session.CSession::SetPlayerPosDir(x, y, dir);

	char curMap[35];
	sprintf(curMap, "%s.rsw", g_session.m_curMap);
	g_modeMgr.CModeMgr::Switch(MT_GAME, curMap);

	g_connection.CConnection::SetBlock(false);

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


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Reqname(SAKEXE, "CGameMode::Zc_Ack_Reqname");
void CGameMode::Zc_Ack_Reqname(const char* buf) // line 1535
{
	return (this->*_Zc_Ack_Reqname)(buf);

	PACKET_ZC_ACK_REQNAME& packet = *(PACKET_ZC_ACK_REQNAME*)buf;

	NamePair& name = m_actorNameList[packet.AID];
	name.cName = packet.CName;

	this->CGameMode::RemoveActorNameRequestTimer(packet.AID);

	if( packet.AID == g_session.m_petGID )
	{
		sprintf(g_session.m_petName, packet.CName); //FIXME: uncontrolled format string vulnerability
		if( g_windowMgr.UIWindowMgr::GetPetInfoWnd() != NULL )
			g_windowMgr.UIWindowMgr::GetPetInfoWnd()->m_newName->SetText(packet.CName);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Reqname_bygid(SAKEXE, "CGameMode::Zc_Ack_Reqname_bygid");
void CGameMode::Zc_Ack_Reqname_bygid(const char* buf) // line 1550
{
	return (this->*_Zc_Ack_Reqname_bygid)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Reqnameall(SAKEXE, "CGameMode::Zc_Ack_Reqnameall");
void CGameMode::Zc_Ack_Reqnameall(const char* buf) // line 1558
{
	return (this->*_Zc_Ack_Reqnameall)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Broadcast(SAKEXE, "CGameMode::Zc_Broadcast");
void CGameMode::Zc_Broadcast(const char* buf) // line 1568
{
	return (this->*_Zc_Broadcast)(buf);

	PACKET_ZC_BROADCAST& packet = *(PACKET_ZC_BROADCAST*)buf;

	char chatMsg[1023+1];
	int count = packet.PacketLength - sizeof(packet);
	if( count > sizeof(chatMsg)-1 )
		count = sizeof(chatMsg)-1;
	memcpy(chatMsg, packet.Text, count);
	chatMsg[count] = '\0';

	int len = strlen(chatMsg);

	char temp3[4+1];
	memcpy(temp3, chatMsg, min(strlen(chatMsg), sizeof(temp3)-1));
	temp3[sizeof(temp3)-1] = '\0';
	strlwr(temp3);

	mystd::string wMsg = chatMsg;

	//NOTE: this is used to skip the hidden part of npc names in npc broadcasts
	int subStrSize1 = wMsg.find('#'); // skip block start
	int subStrSize2 = wMsg.find(':'); // skip block end
	wMsg.find("blue");

	COLORREF color = 0x00FFFF; // yellow
	if( subStrSize1 > 0 && subStrSize1 < len )
	{// text contains skip block
		char temp[1024];
		memcpy(temp, chatMsg, subStrSize1);
		temp[subStrSize1] = '\0';
		wMsg = temp;

		if( subStrSize2 > 0 && subStrSize2 < len )
		{
			char temp2[1024];
			memcpy(temp2, &chatMsg[subStrSize2], len - subStrSize2 + 1);
			if( strlen(temp2) != 0 )
				wMsg.append(temp2);
		}
	}
	else
	{// simple text
		if( strcmp(temp3, "blue") == 0 || strcmp(temp3, "블루") == 0 )
		{
			char temp[1024];
			memcpy(temp, &chatMsg[4], len - 4);
			temp[len - 4] = '\0';
			wMsg = temp;
			
			color = 0xFFFF00; // blue
		}
	}

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)wMsg.c_str(), color, 0);
	m_broadCastTick = timeGetTime();

	if( m_broadcastBalloon == NULL )
	{
		m_broadcastBalloon = new UITransBalloonText();
		m_broadcastBalloon->UIWindow::Create(8, 8);
		g_windowMgr.UIWindowMgr::AddWindowFront(m_broadcastBalloon);
	}

	m_broadcastBalloon->UIBalloonText::SetText(wMsg.c_str(), 72);
	m_broadcastBalloon->Move((g_renderer->CRenderer::GetWidth() - 640) / 2 - m_broadcastBalloon->UIWindow::GetWidth() / 2 + 320, 51);
	m_broadcastBalloon->UIBalloonText::SetFntColor(color, 0x000000); // inlined
}


void CGameMode::Zc_Whisper(const char* buf) // line 1631-1669
{
	const PACKET_ZC_WHISPER& packet = *reinterpret_cast<const PACKET_ZC_WHISPER*>(buf);

	char cName[24+1];
	memcpy(cName, packet.sender, sizeof(cName)-1);
	cName[sizeof(cName)-1] = '\0';

	if( g_session.CSession::IsExName(cName) )
		return; // ignored.

	char chatMsg[255+1];
	memcpy(chatMsg, packet.Text, packet.PacketLength - sizeof(packet));
	chatMsg[sizeof(chatMsg)-1] = '\0';

	mystd::string imMsg = (mystd::string)cName + " : " + chatMsg;
	if( !g_windowMgr.UIWindowMgr::AddWhisperChatToWhisperWnd(cName, imMsg.c_str(), 0x222222) )
	{
		mystd::string wMsg = (mystd::string)"(From " + cName + ") : " + chatMsg;

		if( strcmp(cName, g_session.CSession::GetCharName()) != 0 )
		{
			g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)wMsg.c_str(), 0x00FFFF, 0);

			g_windowMgr.UIWindowMgr::AddWhisperCharName(cName);

			if( g_session.m_isSaveChat )
				this->CGameMode::WriteChat(const_cast<char*>(wMsg.c_str()));
		}
	}
}


void CGameMode::Zc_Ack_Whisper(const char* buf) // line 1672-1723
{
	const PACKET_ZC_ACK_WHISPER& packet = *reinterpret_cast<const PACKET_ZC_ACK_WHISPER*>(buf);

	switch( packet.result )
	{
	case WHISPER_SEND_SUCCEED:
	{
		mystd::string imMsg = (mystd::string)g_session.CSession::GetCharName() + " : " + m_lastWhisper;

		if( !g_windowMgr.UIWindowMgr::AddWhisperChatToWhisperWnd(m_lastWhisperName.c_str(), imMsg.c_str(), 0x007800) )
		{
			mystd::string msg = "(To " + m_lastWhisperName + ") : " + m_lastWhisper;

			g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg.c_str(), 0x00FFFF, 0);

			if( g_session.m_isSaveChat )
				this->CGameMode::WriteChat(const_cast<char*>(msg.c_str()));
		}
	}
	break;
	case WHISPER_SEND_FAILED_PC_ABSENCE:
	{
		mystd::string imMsg = "(" + m_lastWhisperName + ")" + MsgStr(MSI_NOT_EXIST_CHARACTER);

		if( !g_windowMgr.UIWindowMgr::AddWhisperChatToWhisperWnd(m_lastWhisperName.c_str(), imMsg.c_str(), 0x007800) )
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)imMsg.c_str(), 0x00FFFF, 0);
	}
	break;
	case WHISPER_SEND_FAILED_PC_REFUSAL:
	{
		mystd::string imMsg = "(" + m_lastWhisperName + ")" + MsgStr(MSI_NO_RECEIVE_MODE);

		if( !g_windowMgr.UIWindowMgr::AddWhisperChatToWhisperWnd(m_lastWhisperName.c_str(), imMsg.c_str(), 0x007800) )
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)imMsg.c_str(), 0x00FFFF, 0);
	}
	break;
	case WHISPER_SEND_FAILED_PC_REFUSAL_ALL:
	{
		mystd::string imMsg = "(" + m_lastWhisperName + ")" + MsgStr(MSI_NO_RECEIVE_MODE_FOR_ALL);

		if( !g_windowMgr.UIWindowMgr::AddWhisperChatToWhisperWnd(m_lastWhisperName.c_str(), imMsg.c_str(), 0x007800) )
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)imMsg.c_str(), 0x00FFFF, 0);
	}
	break;
	default:
	{
		mystd::string msg = "(" + m_lastWhisperName + ")" + MsgStr(MSI_NOT_EXIST_CHARACTER);

		if( !g_windowMgr.UIWindowMgr::AddWhisperChatToWhisperWnd(m_lastWhisperName.c_str(), msg.c_str(), 0x007800) )
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg.c_str(), 0x00FFFF, 0);

		if( g_session.m_isSaveChat )
			this->CGameMode::WriteChat(const_cast<char*>(msg.c_str()));
	}
	break;
	};
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Change_Direction(SAKEXE, "CGameMode::Zc_Change_Direction");
void CGameMode::Zc_Change_Direction(const char* buf) // line 1726
{
	return (this->*_Zc_Change_Direction)(buf);

	PACKET_ZC_CHANGE_DIRECTION& packet = *(PACKET_ZC_CHANGE_DIRECTION*)buf;

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.AID);
	if( actor == NULL )
		return;

	actor->m_roty = (float)(45 * (packet.dir + 4));
	actor->SendMsg(NULL, 100, packet.headDir, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Disconnect_Character(SAKEXE, "CGameMode::Zc_Ack_Disconnect_Character");
void CGameMode::Zc_Ack_Disconnect_Character(const char* buf) // line 1736
{
	return (this->*_Zc_Ack_Disconnect_Character)(buf);

	PACKET_ZC_ACK_DISCONNECT_CHARACTER& packet = *(PACKET_ZC_ACK_DISCONNECT_CHARACTER*)buf;

	char msg[80];

	if( packet.result != 0 )
		sprintf(msg, MsgStr(MSI_SUCCESS_DISCONNECT_CHARACTER));
	else
		sprintf(msg, MsgStr(MSI_FAIL_DISCONNECT_CHARACTER));

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg, 0x0032FF, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Actentry(SAKEXE, "CGameMode::Zc_Notify_Actentry");
void CGameMode::Zc_Notify_Actentry(const char* buf) // line 1793
{
	return (this->*_Zc_Notify_Actentry)(buf);

	;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Moveentry(SAKEXE, "CGameMode::Zc_Notify_Moveentry");
void CGameMode::Zc_Notify_Moveentry(const char* buf) // line 1796-1928
{
	return (this->*_Zc_Notify_Moveentry)(buf);

	PACKET_ZC_NOTIFY_MOVEENTRY& packet = *(PACKET_ZC_NOTIFY_MOVEENTRY*)buf;

	MOVEENTRYSTRUCT ms;
	ms.GID = packet.GID;
	ms.job = packet.job;
	ms.sex = packet.sex;
	ms.speed = packet.speed;
	ms.head = packet.head;
	ms.weapon = packet.weapon;
	ms.accessory = packet.accessory;
	ms.healthState = packet.healthState;
	ms.bodyState = packet.bodyState;
	ms.effectState = packet.effectState;
	ms.isPKModeON = packet.isPKModeON;
	ms.shield = packet.shield;
	ms.accessory2 = packet.accessory2;
	ms.accessory3 = packet.accessory3;
	ms.headpalette = packet.headpalette;
	ms.headDir = packet.headDir;
	ms.bodypalette = packet.bodypalette;
	ms.guildEmblemVersion = packet.GEmblemVer;
	ms.guildId = packet.GUID;
	ms.virtue = packet.virtue;
	ms.honor = packet.honor;
	ms.moveStartTime = packet.moveStartTime;
	DecodeSrcDst(packet.MoveData, ms.sx, ms.sy, ms.dx, ms.dy, ms.cellX, ms.cellY);

	g_session.CSession::UpdateServerTime(packet.moveStartTime);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor == NULL )
	{
		if( packet.job < JT_WARPNPC || packet.job >= JT_2004_JOB_BEGIN )
		{
			actor = new CPc();
		}
		else
		{
			actor = this->CGameMode::NewNpc(packet.job);
			ms.sex = SEX_FEMALE;
		}

		if( actor != NULL && ms.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = ms.accessory;

			if( ms.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(ms.accessory));
		}

		m_world->m_gameObjectList.push_back(actor);
		m_world->m_actorList.push_back(actor);

		actor->SendMsg(NULL, 6, (int)&ms, 0, 0);

		if( actor->CGameActor::GetJob() > JT_WARPNPC && actor->CGameActor::GetJob() < JT_2004_JOB_BEGIN )
		{
			unsigned long GDID = packet.accessory3 | (packet.accessory2 << 16);
			unsigned long emblemVer = packet.shield;

			if( GDID != 0 && actor->GetGdid() == 0 )
				actor->SetGuildInfo(GDID, emblemVer);
		}

		if( g_session.CSession::IsSiegeMode() && ms.head != 20 && actor->m_emblemWnd == NULL )
		{
			if( g_session.CSession::IsPc(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
			else
			if( g_session.CSession::IsGuardian(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
		}
	}
	else
	{
		actor->SendMsg(NULL, 5, (int)&ms, 0, 0);

		if( actor->CGameActor::GetJob() > JT_WARPNPC && actor->CGameActor::GetJob() < JT_2004_JOB_BEGIN )
		{
			unsigned long GDID = packet.accessory3 | (packet.accessory2 << 16);
			unsigned long emblemVer = packet.shield;

			if( GDID != 0 )
				actor->SetGuildInfo(GDID, emblemVer);
		}

		if( ms.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = ms.accessory;

			if( ms.accessory != 0 && !actor->GetGdid() )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(ms.accessory));
		}

		if( g_session.CSession::IsSiegeMode() && ms.head != 20 && actor->m_emblemWnd == NULL )
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


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Vanish(SAKEXE, "CGameMode::Zc_Notify_Vanish");
void CGameMode::Zc_Notify_Vanish(const char* buf) // line 1931
{
	return (this->*_Zc_Notify_Vanish)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Sc_Notify_Ban(SAKEXE, "CGameMode::Sc_Notify_Ban");
void CGameMode::Sc_Notify_Ban(const char* buf) // line 2052
{
	return (this->*_Sc_Notify_Ban)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Accept_Quit(SAKEXE, "CGameMode::Zc_Accept_Quit");
void CGameMode::Zc_Accept_Quit(const char* buf) // line 2133
{
	return (this->*_Zc_Accept_Quit)(buf);

	;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Entry(SAKEXE, "CGameMode::Zc_Item_Entry");
void CGameMode::Zc_Item_Entry(const char* buf) // line 2136
{
	return (this->*_Zc_Item_Entry)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Fall_Entry(SAKEXE, "CGameMode::Zc_Item_Fall_Entry");
void CGameMode::Zc_Item_Fall_Entry(const char* buf) // line 2161
{
	return (this->*_Zc_Item_Fall_Entry)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Pickup_Ack(SAKEXE, "CGameMode::Zc_Item_Pickup_Ack");
void CGameMode::Zc_Item_Pickup_Ack(const char* buf) // line 2185
{
	return (this->*_Zc_Item_Pickup_Ack)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Disappear(SAKEXE, "CGameMode::Zc_Item_Disappear");
void CGameMode::Zc_Item_Disappear(const char* buf) // line 2326
{
	return (this->*_Zc_Item_Disappear)(buf);

	PACKET_ZC_ITEM_DISAPPEAR& packet = *(PACKET_ZC_ITEM_DISAPPEAR*)buf;

	m_world->CWorld::RemoveItem(packet.ITAID);
	this->CGameMode::RemovePickupItemNaid(packet.ITAID);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Normal_Itemlist(SAKEXE, "CGameMode::Zc_Normal_Itemlist");
void CGameMode::Zc_Normal_Itemlist(const char* buf) // line 2333
{
	return (this->*_Zc_Normal_Itemlist)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Normal_Itemlist2(SAKEXE, "CGameMode::Zc_Normal_Itemlist2");
void CGameMode::Zc_Normal_Itemlist2(const char* buf) // line 2364
{
	return (this->*_Zc_Normal_Itemlist2)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Equipment_Itemlist(SAKEXE, "CGameMode::Zc_Equipment_Itemlist");
void CGameMode::Zc_Equipment_Itemlist(const char* buf) // line 2399
{
	return (this->*_Zc_Equipment_Itemlist)(buf);

	PACKET_ZC_EQUIPMENT_ITEMLIST& packet = *(PACKET_ZC_EQUIPMENT_ITEMLIST*)buf;
	int count = (packet.Length - sizeof(packet)) / sizeof(EQUIPMENTITEM_EXTRAINFO);

	g_session.CSession::ClearEquipItemInInventory();
	g_session.CSession::ClearEquipItem();

	for( int i = 0; i < count; ++i )
	{
		EQUIPMENTITEM_EXTRAINFO& item = packet.Item[i];

		ITEM_INFO itemInfo;
		itemInfo.m_itemType      = item.type;
		itemInfo.m_location      = item.location;
		itemInfo.m_itemIndex     = item.index;
		itemInfo.m_wearLocation  = item.WearState;
		itemInfo.m_num           = 1;
		itemInfo.m_slot[0]       = item.slot.info[0];
		itemInfo.m_slot[1]       = item.slot.info[1];
		itemInfo.m_slot[2]       = item.slot.info[2];
		itemInfo.m_slot[3]       = item.slot.info[3];
		itemInfo.ITEM_INFO::SetItemId(item.ITID);
		itemInfo.m_isIdentified  = item.IsIdentified;
		itemInfo.m_isDamaged     = item.IsDamaged;
		itemInfo.m_refiningLevel = item.RefiningLevel;

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


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Stopmove(SAKEXE, "CGameMode::Zc_Stopmove");
void CGameMode::Zc_Stopmove(const char* buf) // line 2453
{
	return (this->*_Zc_Stopmove)(buf);

	PACKET_ZC_STOPMOVE& packet = *(PACKET_ZC_STOPMOVE*)buf;

	if( packet.AID == g_session.CSession::GetAid() )
	{
		m_world->m_player->SendMsg(NULL, 19, packet.xPos, packet.yPos, 0);
	}
	else
	{
		CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.AID);
		if( actor != NULL )
			actor->SendMsg(NULL, 19, packet.xPos, packet.yPos, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Par_Change(SAKEXE, "CGameMode::Zc_Par_Change");
void CGameMode::Zc_Par_Change(const char* buf) // line 2465-2713
{
	return (this->*_Zc_Par_Change)(buf);

	PACKET_ZC_PAR_CHANGE& packet = *(PACKET_ZC_PAR_CHANGE*)buf;
	short varID = packet.varID;
	int value = packet.count;

	switch( varID )
	{
	case 0x0: // VAR_SPEED
		if( value != g_session.CSession::GetSpeed() )
			g_session.CSession::SetSpeed(value); //inline
	break;
	case 0x3: // VAR_VIRTUE
		g_session.CSession::SetVirtue(value); //inline
	break;
	case 0x4: // VAR_HONOR
		if( value < 0 )
		{
			char msg[256];
			sprintf(msg, MsgStr(MSI_BAD_MANNER_REMAIN), -value); //FIXME: uncontrolled format string vulnerability
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg, 0x00FFFF, 0);
			m_world->m_player->SendMsg(NULL, 21, 34, 0, 0);
		}
		else
		{
			char msg[256];
			sprintf(msg, MsgStr(MSI_BAD_MANNER_END)); //FIXME: uncontrolled format string vulnerability
			g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg, 0x00FFFF, 0);
			m_world->m_player->SendMsg(NULL, 118, 0, 0, 0);
		}

		g_session.CSession::SetHonor(value); //inline
	break;
	case 0x5: // VAR_HP
		if( 100 * g_session.CSession::GetHp() / g_session.CSession::GetMaxhp() < 25
			&& 100 * value / g_session.CSession::GetMaxhp() < 25
			&& m_world->CWorld::GetGameActorByAID(g_session.m_petGID) != NULL
			&& rand() % 100 < 50 )
		{
			int hungry = g_session.CSession::GetPetHungryState(g_session.m_petHungry);
			int friendly = g_session.CSession::GetPetFriendlyState(g_session.m_petFriendly);
			this->SendMsg(0xA1, g_session.CSession::GetPetTalkNumber(g_session.m_petJob, 2, hungry), 0, 0);
			this->SendMsg(0xA1, g_session.m_petEmotionTable[hungry][friendly][2], 0, 0);
		}

		g_session.CSession::SetHp(value); //inline
	break;
	case 0x6: // VAR_MAXHP
		g_session.CSession::SetMaxhp(value); //inline
	break;
	case 0x7: // VAR_SP
		g_session.CSession::SetSp(value); //inline
	case 0x8: // VAR_MAXSP
		g_session.CSession::SetMaxsp(value); //inline
	break;
	case 0x9: // VAR_POINT
		g_session.CSession::SetPoint(value); //inline
		if( g_windowMgr.UIWindowMgr::GetStatusWnd() != 0 )
			g_windowMgr.UIWindowMgr::GetStatusWnd()->SendMsg(NULL, 0x23, 0, 0, 0);
	break;
	case 0xB: // VAR_CLEVEL
		g_session.CSession::SetLevel(value); //inline
		PlayWave("levelup.wav", 0.0, 0.0, 0.0, 250, 40, 1.0);
		if( g_session.CSession::GetJob() == JT_SUPERNOVICE || g_session.CSession::GetJob() == JT_SUPERNOVICE_B )
			m_world->m_player->CAbleToMakeEffect::LaunchEffect(0x152, vector3d(0,0,0), 0);
		else
			m_world->m_player->CAbleToMakeEffect::LaunchEffect(0x173, vector3d(0,0,0), 0);

		g_windowMgr.UIWindowMgr::MakeWindow(WID_NOTIFYLEVELUPWND);
		if ( m_world->CWorld::GetGameActorByAID(g_session.m_petGID) != NULL )
		{
			int hungry = g_session.CSession::GetPetHungryState(g_session.m_petHungry);
			int friendly = g_session.CSession::GetPetFriendlyState(g_session.m_petFriendly);
			this->SendMsg(0xA1, g_session.CSession::GetPetTalkNumber(g_session.m_petJob, 6, hungry), 0, 0);
			this->SendMsg(0xA1, g_session.m_petEmotionTable[hungry][friendly][6], 0, 0);
		}
	break;
	case 0xC: // VAR_SPPOINT
		g_session.CSession::SetSkillPoint(value); //inline
		g_session.CSession::RefreshSkillItemWnd();
	break;
	case 0xD: // VAR_STR
		g_session.CSession::SetStr(value); //inline
	break;
	case 0xE: // VAR_AGI
		g_session.CSession::SetAgi(value); //inline
	break;
	case 0xF: // VAR_VIT
		g_session.CSession::SetVit(value); //inline
	break;
	case 0x10: // VAR_INT
		g_session.CSession::SetInt(value); //inline
	break;
	case 0x11: // VAR_DEX
		g_session.CSession::SetDex(value); //inline
	break;
	case 0x12: // VAR_LUK
		g_session.CSession::SetLuk(value); //inline
	break;
	case 0x18: // VAR_WEIGHT
	{
		int oldPercent = 100 * g_session.CSession::GetWeight() / min(g_session.CSession::GetMaxWeight(), 1);
		g_session.CSession::SetWeight(value / 10); //inline
		if( g_session.CSession::GetMaxWeight() != 0 )
		{
			int newPercent = 100 * g_session.CSession::GetWeight() / min(g_session.CSession::GetMaxWeight(), 1);
			if( newPercent > oldPercent )
			{
				if( newPercent >= 50 && oldPercent < 50 )
				{
					g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
					g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_NO_RECOVER_OVERWEIGHT), 0x0000FF, 0);
				}

				if( newPercent >= 90 && oldPercent < 90 )
				{
					g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
					g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_NO_ATTACK_OVERWEIGHT), 0x0000FF, 0);
				}
			}
			else
			{
				if ( newPercent < 50 && oldPercent >= 50 )
				{
					g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
					g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_NO_RECOVER_OVERWEIGHT_RELEASED), 0xFFFF00, 0);
				}

				if ( newPercent < 90 && oldPercent >= 90 )
				{
					g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
					g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_NO_ATTACK_OVERWEIGHT_RELEASED), 0xFFFF00, 0);
				}
			}
		}
	}
	break;
	case 0x19: // VAR_MAXWEIGHT
	{
		int oldMaxWeight = g_session.CSession::GetMaxWeight();
		int oldPercent = 100 * g_session.CSession::GetWeight() / min(oldMaxWeight, 1);
		g_session.CSession::SetMaxWeight(value / 10); //inline
		if( oldMaxWeight != 0 && oldMaxWeight < g_session.CSession::GetMaxWeight() )
		{
			int newPercent = 100 * g_session.CSession::GetWeight() / min(g_session.CSession::GetMaxWeight(), 1);
			if ( newPercent < 50 && oldPercent >= 50 )
			{
				g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_NO_RECOVER_OVERWEIGHT_RELEASED), 0xFFFF00, 0);
			}

			if ( newPercent < 90 && oldPercent >= 90 )
			{
				g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_NO_ATTACK_OVERWEIGHT_RELEASED), 0xFFFF00, 0);
			}
		}
	}
	break;
	case 0x29: // VAR_ATTPOWER
		g_session.CSession::SetAttPower(value); //inline
	break;
	case 0x2A: // VAR_REFININGPOWER
		g_session.CSession::SetRefiningPower(value); //inline
	break;
	case 0x2B: // VAR_MAX_MATTPOWER
		g_session.CSession::SetMax_mattPower(value); //inline
	break;
	case 0x2C: // VAR_MIN_MATTPOWER
		g_session.CSession::SetMin_mattPower(value); //inline
	break;
	case 0x2D: // VAR_ITEMDEFPOWER
		g_session.CSession::SetItemDefPower(value); //inline
	break;
	case 0x2E: // VAR_PLUSDEFPOWER
		g_session.CSession::SetPlusdefPower(value); //inline
	break;
	case 0x2F: // VAR_MDEFPOWER
		g_session.CSession::SetMdefPower(value); //inline
	break;
	case 0x30: // VAR_PLUSMDEFPOWER
		g_session.CSession::SetPlusmdefPower(value); //inline
	break;
	case 0x31: // VAR_HITSUCCESSVALUE
		g_session.CSession::SetHitSuccessValue(value); //inline
	break;
	case 0x32: // VAR_AVOIDSUCCESSVALUE
		g_session.CSession::SetAvoidSuccessValue(value); //inline
	break;
	case 0x33: // VAR_PLUSAVOIDSUCCESSVALUE
		g_session.CSession::SetPlusAvoidSuccessValue(value); //inline
	break;
	case 0x34: // VAR_CRITICALSUCCESSVALUE
		g_session.CSession::SetCriticalSuccessValue(value); //inline
	break;
	case 0x35: // VAR_ASPD
		g_session.CSession::SetASPD(value); //inline
	break;
	case 0x36: // VAR_PLUSASPD
		g_session.CSession::SetPlusASPD(value); //inline
	break;
	case 0x37: // VAR_JOBLEVEL
		g_session.CSession::SetJoblevel(value); //inline
		if( value <= 50 )
			m_world->m_player->CAbleToMakeEffect::LaunchEffect(0x9E, vector3d(0,0,0), 0);
		else
			m_world->m_player->CAbleToMakeEffect::LaunchEffect(0x151, vector3d(0,0,0), 0);

		g_windowMgr.UIWindowMgr::MakeWindow(WID_NOTIFYJOBLEVELUPWND);
	break;
	default:
	break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Longpar_Change(SAKEXE, "CGameMode::Zc_Longpar_Change");
void CGameMode::Zc_Longpar_Change(const char* buf) // line 2716-2767
{
	return (this->*_Zc_Longpar_Change)(buf);
	
	PACKET_ZC_LONGPAR_CHANGE& packet = *(PACKET_ZC_LONGPAR_CHANGE*)buf;
	short varID = packet.varID;
	int value = packet.amount;

	switch( varID )
	{
	case 0x1: // VAR_EXP
		if( g_session.CSession::IsMasterAid(2) )
		{
			if( value != 0 && value != g_session.CSession::GetExp() )
			{
				char msg[256];
				sprintf(msg, "%d : %d/%d More : %d", value - g_session.CSession::GetExp(), value, g_session.CSession::GetNextExp(), g_session.CSession::GetNextExp() - g_session.CSession::GetExp());
				g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg, 0xF51EF5, 0);
			}
		}

		g_session.CSession::SetExp(value); //inline
	break;
	case 0x2: // VAR_JOBEXP
		g_session.CSession::SetJobexp(value); //inline
	break;
	case 0x14: // VAR_MONEY
		if( m_isWaitingCancelExchangeItem != 0 )
		{
			m_isWaitingCancelExchangeItem = 0;
			g_session.CSession::CancelExchangeNoRefresh();
		}

		g_session.CSession::SetGold(value); //inline
	break;
	case 0x16: // VAR_MAXEXP
		g_session.CSession::SetNextexp(value); //inline
	break;
	case 0x17: // VAR_MAXJOBEXP
		g_session.CSession::SetJobnextexp(value); //inline
	break;
	default:
	break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Use_Item_Ack(SAKEXE, "CGameMode::Zc_Use_Item_Ack");
void CGameMode::Zc_Use_Item_Ack(const char* buf) // line 2770
{
	return (this->*_Zc_Use_Item_Ack)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Wear_Equip_Ack(SAKEXE, "CGameMode::Zc_Req_Wear_Equip_Ack");
void CGameMode::Zc_Req_Wear_Equip_Ack(const char* buf) // line 2786
{
	return (this->*_Zc_Req_Wear_Equip_Ack)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Takeoff_Equip_Ack(SAKEXE, "CGameMode::Zc_Req_Takeoff_Equip_Ack");
void CGameMode::Zc_Req_Takeoff_Equip_Ack(const char* buf) // line 2811
{
	return (this->*_Zc_Req_Takeoff_Equip_Ack)(buf);

	PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK& packet = *(PACKET_ZC_REQ_TAKEOFF_EQUIP_ACK*)buf;

	m_waitingTakeoffEquipAck = timeGetTime() - 2000;
	if( packet.result && packet.wearLocation != 0 )
		g_session.CSession::MoveItemFromEquipWndToItemWnd(packet.wearLocation);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Item_Throw_Ack(SAKEXE, "CGameMode::Zc_Item_Throw_Ack");
void CGameMode::Zc_Item_Throw_Ack(const char* buf) // line 2824
{
	return (this->*_Zc_Item_Throw_Ack)(buf);

	PACKET_ZC_ITEM_THROW_ACK& packet = *(PACKET_ZC_ITEM_THROW_ACK*)buf;

	if( m_isWaitingCancelExchangeItem != 0 )
	{
		m_isWaitingCancelExchangeItem = 0;
		g_session.CSession::CancelExchangeNoRefresh();
	}

	g_session.CSession::DecItem(packet.Index, packet.count);
	m_waitingItemThrowAck = 0;

	Trace("PACKET_ZC_ITEM_THROW_ACK - index==%d, count==%d", packet.Index, packet.count);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Say_Dialog(SAKEXE, "CGameMode::Zc_Say_Dialog");
void CGameMode::Zc_Say_Dialog(const char* buf) // line 2836
{
	return (this->*_Zc_Say_Dialog)(buf);

	PACKET_ZC_SAY_DIALOG& packet = *(PACKET_ZC_SAY_DIALOG*)buf;
	int size = packet.PacketLength - sizeof(packet);

	m_isOnQuest = 1;
	m_lastNaid = packet.NAID;

	char dialogSay[2048];
	memcpy(dialogSay, packet.Text, size);
	dialogSay[size] = '\0';

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_SAYDIALOGWND);
	wnd->SendMsg(NULL, 26, (int)dialogSay, packet.NAID, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Wait_Dialog(SAKEXE, "CGameMode::Zc_Wait_Dialog");
void CGameMode::Zc_Wait_Dialog(const char* buf) // line 2853
{
	return (this->*_Zc_Wait_Dialog)(buf);

	PACKET_ZC_WAIT_DIALOG& packet = *(PACKET_ZC_WAIT_DIALOG*)buf;

	m_isOnQuest = 1;
	m_lastNaid = packet.NAID;
	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_SAYDIALOGWND);
	wnd->SendMsg(NULL, 25, 0, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Close_Dialog(SAKEXE, "CGameMode::Zc_Close_Dialog");
void CGameMode::Zc_Close_Dialog(const char* buf) // line 2862
{
	return (this->*_Zc_Close_Dialog)(buf);

	PACKET_ZC_CLOSE_DIALOG& packet = *(PACKET_ZC_CLOSE_DIALOG*)buf;

	if( g_windowMgr.UIWindowMgr::GetSayDialogWnd() != NULL )
	{
		g_windowMgr.UIWindowMgr::GetSayDialogWnd()->SendMsg(NULL, 32, 0, 0, 0);
		g_windowMgr.UIWindowMgr::GetSayDialogWnd()->SendMsg(NULL, 63, 0, 0, 0);
	}
	else
	{
		m_isOnQuest = 0;
		m_lastNaid = packet.NAID;
		g_windowMgr.UIWindowMgr::DeleteWindow(WID_SAYDIALOGWND);
		g_windowMgr.UIWindowMgr::DeleteWindow(WID_CHOOSEWND);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Menu_List(SAKEXE, "CGameMode::Zc_Menu_List");
void CGameMode::Zc_Menu_List(const char* buf) // line 2878
{
	return (this->*_Zc_Menu_List)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Restart_Ack(SAKEXE, "CGameMode::Zc_Restart_Ack");
void CGameMode::Zc_Restart_Ack(const char* buf) // line 2906
{
	return (this->*_Zc_Restart_Ack)(buf);

	PACKET_ZC_RESTART_ACK& packet = *(PACKET_ZC_RESTART_ACK*)buf;

	if( packet.type == 1 )
	{
		g_connection.CConnection::Disconnect();
		g_loginStartMode = 5;
		g_modeMgr.CModeMgr::Switch(0, "login.rsw");
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Status_Change_Ack(SAKEXE, "CGameMode::Zc_Status_Change_Ack");
void CGameMode::Zc_Status_Change_Ack(const char* buf) // line 2917
{
	return (this->*_Zc_Status_Change_Ack)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Status(SAKEXE, "CGameMode::Zc_Status");
void CGameMode::Zc_Status(const char* buf) // line 3007
{
	return (this->*_Zc_Status)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Status_Change(SAKEXE, "CGameMode::Zc_Status_Change");
void CGameMode::Zc_Status_Change(const char* buf) // line 3050-3076
{
	return (this->*_Zc_Status_Change)(buf);

	const PACKET_ZC_STATUS_CHANGE& packet = *(PACKET_ZC_STATUS_CHANGE*)buf;
	short type = packet.statusID;
	unsigned char value = packet.value;

	switch( type )
	{
	case 0x20: // VAR_STANDARD_STR
		g_session.CSession::SetStandardStr(value); //inline
	break;
	case 0x21: // VAR_STANDARD_AGI
		g_session.CSession::SetStandardAgi(value); //inline
	break;
	case 0x22: // VAR_STANDARD_VIT
		g_session.CSession::SetStandardVit(value); //inline
	break;
	case 0x23: // VAR_STANDARD_INT
		g_session.CSession::SetStandardInt(value); //inline
	break;
	case 0x24: // VAR_STANDARD_DEX
		g_session.CSession::SetStandardDex(value); //inline
	break;
	case 0x25: // VAR_STANDARD_LUK
		g_session.CSession::SetStandardLuk(value); //inline
	break;
	}

	if( g_windowMgr.UIWindowMgr::GetStatusWnd() != NULL )
		g_windowMgr.UIWindowMgr::GetStatusWnd()->SendMsg(NULL, 35, 0, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Emotion(SAKEXE, "CGameMode::Zc_Emotion");
void CGameMode::Zc_Emotion(const char* buf) // line 3079
{
	return (this->*_Zc_Emotion)(buf);

	PACKET_ZC_EMOTION& packet = *(PACKET_ZC_EMOTION*)buf;

	if( g_session.CSession::IsExAid(packet.GID) )
		return;

	if( packet.GID == g_session.CSession::GetAid() )
	{
		m_world->m_player->SendMsg(NULL, 21, packet.type, 0, 0);
	}
	else
	{
		CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
		if( actor != NULL )
			actor->SendMsg(NULL, 21, packet.type, 0, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_User_Count(SAKEXE, "CGameMode::Zc_User_Count");
void CGameMode::Zc_User_Count(const char* buf) // line 3099
{
	return (this->*_Zc_User_Count)(buf);

	PACKET_ZC_USER_COUNT& packet = *(PACKET_ZC_USER_COUNT*)buf;

	char msg[128];
	sprintf(msg, MsgStr(MSI_NUMPEOPLE), packet.count);

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg, 0x00FFFF, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Sprite_Change(SAKEXE, "CGameMode::Zc_Sprite_Change");
void CGameMode::Zc_Sprite_Change(const char* buf) // line 3109-3205
{
	return (this->*_Zc_Sprite_Change)(buf);

	PACKET_ZC_SPRITE_CHANGE& packet = *(PACKET_ZC_SPRITE_CHANGE*)buf;

	CGameActor* actor;

	if( packet.GID == g_session.CSession::GetAid() )
	{
		actor = m_world->m_player;

		switch( packet.type )
		{
		case SPRITETYPE_JOB:
			g_session.CSession::SetJob(packet.value);
			g_session.CSession::InvalidateUI();
			g_session.CSession::InvalidateJob();
		break;
		case SPRITETYPE_HEAD:
			g_session.m_head = packet.value;
		break;
		case SPRITETYPE_WEAPON:
			g_session.m_weapon = packet.value;
		break;
		case SPRITETYPE_ACCESSORY:
			g_session.m_accessory = packet.value;
		break;
		case SPRITETYPE_HEADPALETTE:
			g_session.m_headPalette = packet.value;
		break;
		case SPRITETYPE_BODYPALATTE:
			g_session.m_bodyPalette = packet.value;
		break;
		case SPRITETYPE_ACCESSORY2:
			g_session.m_accessory2 = packet.value;
		break;
		case SPRITETYPE_ACCESSORY3:
			g_session.m_accessory3 = packet.value;
		break;
		case SPRITETYPE_SHIELD:
			g_session.m_shield = packet.value;
		break;
		default:
		break;
		}
	}
	else
	{
		actor = m_world->CWorld::GetGameActorByAID(packet.GID);
		if( actor == NULL )
		{
			CSkill* skill = m_world->CWorld::GetSkillByAID(packet.GID);
			if( skill != NULL && packet.type == 0 )
				skill->SendMsg(NULL, 47, packet.value, 0, 0);

			return;
		}
	}

	switch( packet.type )
	{
	case SPRITETYPE_JOB:
		actor->CGameActor::SetJob(packet.value);
		actor->SetImfFileName();
		actor->SetHeadPaletteName();
		actor->SetBodyPaletteName();
	break;
	case SPRITETYPE_HEAD:
		actor->SetSprHead(packet.value);
		actor->SetImfFileName();
		actor->SetHeadPaletteName();
	break;
	case SPRITETYPE_WEAPON:
		actor->SetSprWeapon(packet.value);
	break;
	case SPRITETYPE_ACCESSORY:
		actor->SetSprAccessory(packet.value);
	break;
	case SPRITETYPE_HEADPALETTE:
		actor->SetHeadPalette(packet.value);
	break;
	case SPRITETYPE_BODYPALATTE:
		actor->SetBodyPalette(packet.value);
	break;
	case SPRITETYPE_ACCESSORY2:
		actor->SetSprAccessory2(packet.value);
	break;
	case SPRITETYPE_ACCESSORY3:
		actor->SetSprAccessory3(packet.value);
	break;
	case SPRITETYPE_SHIELD:
		actor->SetSprShield(packet.value);
	break;
	default:
	break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Select_Dealtype(SAKEXE, "CGameMode::Zc_Select_Dealtype");
void CGameMode::Zc_Select_Dealtype(const char* buf) // line 3208
{
	return (this->*_Zc_Select_Dealtype)(buf);

	PACKET_ZC_SELECT_DEALTYPE& packet = *(PACKET_ZC_SELECT_DEALTYPE*)buf;

	m_isOnQuest = 1;
	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_CHOOSESELLBUYWND);
	wnd->SendMsg(NULL, 28, packet.NAID, 0, 0);
	g_windowMgr.UIWindowMgr::DeleteWindow(WID_ITEMSHOPWND);
	g_windowMgr.UIWindowMgr::DeleteWindow(WID_ITEMPURCHASEWND);
	g_windowMgr.UIWindowMgr::DeleteWindow(WID_ITEMSELLWND);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Purchase_Itemlist(SAKEXE, "CGameMode::Zc_Pc_Purchase_Itemlist");
void CGameMode::Zc_Pc_Purchase_Itemlist(const char* buf) // line 3222
{
	return (this->*_Zc_Pc_Purchase_Itemlist)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Sell_Itemlist(SAKEXE, "CGameMode::Zc_Pc_Sell_Itemlist");
void CGameMode::Zc_Pc_Sell_Itemlist(const char* buf) // line 3251
{
	return (this->*_Zc_Pc_Sell_Itemlist)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Purchase_Result(SAKEXE, "CGameMode::Zc_Pc_Purchase_Result");
void CGameMode::Zc_Pc_Purchase_Result(const char* buf) // line 3284
{
	return (this->*_Zc_Pc_Purchase_Result)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pc_Sell_Result(SAKEXE, "CGameMode::Zc_Pc_Sell_Result");
void CGameMode::Zc_Pc_Sell_Result(const char* buf) // line 3314
{
	return (this->*_Zc_Pc_Sell_Result)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Setting_Whisper_Pc(SAKEXE, "CGameMode::Zc_Setting_Whisper_Pc");
void CGameMode::Zc_Setting_Whisper_Pc(const char* buf) // line 3335
{
	return (this->*_Zc_Setting_Whisper_Pc)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Setting_Whisper_State(SAKEXE, "CGameMode::Zc_Setting_Whisper_State");
void CGameMode::Zc_Setting_Whisper_State(const char* buf) // line 3371
{
	return (this->*_Zc_Setting_Whisper_State)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Whisper_List(SAKEXE, "CGameMode::Zc_Whisper_List");
void CGameMode::Zc_Whisper_List(const char* buf) // line 3402
{
	return (this->*_Zc_Whisper_List)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Create_Chatroom(SAKEXE, "CGameMode::Zc_Ack_Create_Chatroom");
void CGameMode::Zc_Ack_Create_Chatroom(const char* buf) // line 3427
{
	return (this->*_Zc_Ack_Create_Chatroom)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Room_Newentry(SAKEXE, "CGameMode::Zc_Room_Newentry");
void CGameMode::Zc_Room_Newentry(const char* buf) // line 3462
{
	return (this->*_Zc_Room_Newentry)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Destroy_Room(SAKEXE, "CGameMode::Zc_Destroy_Room");
void CGameMode::Zc_Destroy_Room(const char* buf) // line 3483
{
	return (this->*_Zc_Destroy_Room)(buf);

	PACKET_ZC_DESTROY_ROOM& packet = *(PACKET_ZC_DESTROY_ROOM*)buf;

	mystd::pair<mystd::map<unsigned long,unsigned long>::iterator,bool> ib;
	ib = m_aidList.insert(mystd::pair<unsigned long,unsigned long>(packet.roomID, 0)); //FIXME: leaves useless entry in db?
	CGameActor* owner = m_world->CWorld::GetGameActorByAID(ib.first->second);

	if( owner != NULL )
		owner->SendMsg(NULL, 33, 0, 0, 0);

	if( g_windowMgr.UIWindowMgr::GetChatRoomWnd() != NULL && g_windowMgr.UIWindowMgr::GetChatRoomWnd()->m_roomInfo.roomId == packet.roomID )
	{
		g_windowMgr.UIWindowMgr::DeleteWindow(WID_CHATROOMWND);
		g_windowMgr.UIWindowMgr::DeleteWindow(WID_CHATROOMCHANGEWND);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Enter_Room(SAKEXE, "CGameMode::Zc_Enter_Room");
void CGameMode::Zc_Enter_Room(const char* buf) // line 3499
{
	return (this->*_Zc_Enter_Room)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Member_Newentry(SAKEXE, "CGameMode::Zc_Member_Newentry");
void CGameMode::Zc_Member_Newentry(const char* buf) // line 3550
{
	return (this->*_Zc_Member_Newentry)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Member_Exit(SAKEXE, "CGameMode::Zc_Member_Exit");
void CGameMode::Zc_Member_Exit(const char* buf) // line 3577
{
	return (this->*_Zc_Member_Exit)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Role_Change(SAKEXE, "CGameMode::Zc_Role_Change");
void CGameMode::Zc_Role_Change(const char* buf) // line 3611
{
	return (this->*_Zc_Role_Change)(buf);

	PACKET_ZC_ROLE_CHANGE& packet = *(PACKET_ZC_ROLE_CHANGE*)buf;

	char memberName[24+1];
	memcpy(memberName, packet.name, sizeof(packet.name));
	memberName[sizeof(memberName)-1] = '\0';

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_CHATROOMWND);
	wnd->SendMsg(NULL, 46, (int)memberName, packet.role, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Refuse_Enter_Room(SAKEXE, "CGameMode::Zc_Refuse_Enter_Room");
void CGameMode::Zc_Refuse_Enter_Room(const char* buf) // line 3626
{
	return (this->*_Zc_Refuse_Enter_Room)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Change_Chatroom(SAKEXE, "CGameMode::Zc_Change_Chatroom");
void CGameMode::Zc_Change_Chatroom(const char* buf) // line 3671
{
	return (this->*_Zc_Change_Chatroom)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Exchange_Item(SAKEXE, "CGameMode::Zc_Req_Exchange_Item");
void CGameMode::Zc_Req_Exchange_Item(const char* buf) // line 3690
{
	return (this->*_Zc_Req_Exchange_Item)(buf);

	PACKET_ZC_REQ_EXCHANGE_ITEM& packet = *(PACKET_ZC_REQ_EXCHANGE_ITEM*)buf;

	char name[24+1];
	memcpy(name, packet.name, sizeof(packet.name));
	name[sizeof(name)-1] = '\0';

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_EXCHANGEACCEPTWND);
	wnd->SendMsg(NULL, 50, (int)name, 0, 0);

	m_lastExchangeCharacterName = name;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Exchange_Item2(SAKEXE, "CGameMode::Zc_Req_Exchange_Item2");
void CGameMode::Zc_Req_Exchange_Item2(const char* buf) // line 3703
{
	return (this->*_Zc_Req_Exchange_Item2)(buf);

	PACKET_ZC_REQ_EXCHANGE_ITEM2& packet = *(PACKET_ZC_REQ_EXCHANGE_ITEM2*)buf;

	char name[24+1];
	memcpy(name, packet.name, sizeof(packet.name));
	name[sizeof(name)-1] = '\0';

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_EXCHANGEACCEPTWND);
	wnd->SendMsg(NULL, 50, (int)name, packet.GID, packet.level);

	m_lastExchangeCharacterName = name;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Exchange_Item(SAKEXE, "CGameMode::Zc_Ack_Exchange_Item");
void CGameMode::Zc_Ack_Exchange_Item(const char* buf) // line 3715
{
	return (this->*_Zc_Ack_Exchange_Item)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Exchange_Item2(SAKEXE, "CGameMode::Zc_Ack_Exchange_Item2");
void CGameMode::Zc_Ack_Exchange_Item2(const char* buf) // line 3748
{
	return (this->*_Zc_Ack_Exchange_Item2)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Exchange_Item(SAKEXE, "CGameMode::Zc_Add_Exchange_Item");
void CGameMode::Zc_Add_Exchange_Item(const char* buf) // line 3783
{
	return (this->*_Zc_Add_Exchange_Item)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Add_Exchange_Item(SAKEXE, "CGameMode::Zc_Ack_Add_Exchange_Item");
void CGameMode::Zc_Ack_Add_Exchange_Item(const char* buf) // line 3807
{
	return (this->*_Zc_Ack_Add_Exchange_Item)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Conclude_Exchange_Item(SAKEXE, "CGameMode::Zc_Conclude_Exchange_Item");
void CGameMode::Zc_Conclude_Exchange_Item(const char* buf) // line 3832
{
	return (this->*_Zc_Conclude_Exchange_Item)(buf);

	PACKET_ZC_CONCLUDE_EXCHANGE_ITEM& packet = *(PACKET_ZC_CONCLUDE_EXCHANGE_ITEM*)buf;

	if( g_windowMgr.UIWindowMgr::GetExchangeWnd() != NULL )
	{
		if( packet.who == 0 )
		{
			g_windowMgr.UIWindowMgr::GetExchangeWnd()->SendMsg(NULL, 51, 0, 0, 0);
		}
		else
		if( packet.who == 1 )
		{
			g_windowMgr.UIWindowMgr::GetExchangeWnd()->SendMsg(NULL, 52, 0, 0, 0);
		}
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cancel_Exchange_Item(SAKEXE, "CGameMode::Zc_Cancel_Exchange_Item");
void CGameMode::Zc_Cancel_Exchange_Item(const char* buf) // line 3848
{
	return (this->*_Zc_Cancel_Exchange_Item)(buf);

	PACKET_ZC_CANCEL_EXCHANGE_ITEM& packet = *(PACKET_ZC_CANCEL_EXCHANGE_ITEM*)buf;

	m_isWaitingAddExchangeItem = 0;
	this->SendMsg(19, 0, 0, 0);
	g_windowMgr.UIWindowMgr::DeleteWindow(WID_EXCHANGEWND);

	m_isWaitingCancelExchangeItem = 0;
	g_session.CSession::CancelExchange();

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_DEAL_IS_CANCELED), 0x0000FF, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Exec_Exchange_Item(SAKEXE, "CGameMode::Zc_Exec_Exchange_Item");
void CGameMode::Zc_Exec_Exchange_Item(const char* buf) // line 3862
{
	return (this->*_Zc_Exec_Exchange_Item)(buf);

	PACKET_ZC_EXEC_EXCHANGE_ITEM& packet = *(PACKET_ZC_EXEC_EXCHANGE_ITEM*)buf;

	this->SendMsg(MM_CANCEL_DRAG, 0, 0, 0);
	g_windowMgr.UIWindowMgr::DeleteWindow(WID_EXCHANGEWND);
	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);

	if( packet.result == 0 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_DEAL_SUCCESS), 0xFFFF00, 0);
	}
	else
	if( packet.result == 1 )
	{
		m_isWaitingCancelExchangeItem = 0;
		g_session.CSession::CancelExchange();
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_DEAL_FAILED), 0x0000FF, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Exchangeitem_Undo(SAKEXE, "CGameMode::Zc_Exchangeitem_Undo");
void CGameMode::Zc_Exchangeitem_Undo(const char* buf) // line 3882
{
	return (this->*_Zc_Exchangeitem_Undo)(buf);

	PACKET_ZC_EXCHANGEITEM_UNDO& packet = *(PACKET_ZC_EXCHANGEITEM_UNDO*)buf;

	m_isWaitingCancelExchangeItem = 0;
	g_session.CSession::CancelExchangeNoRefresh();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Store_Normal_Itemlist(SAKEXE, "CGameMode::Zc_Store_Normal_Itemlist");
void CGameMode::Zc_Store_Normal_Itemlist(const char* buf) // line 3887
{
	return (this->*_Zc_Store_Normal_Itemlist)(buf);

	PACKET_ZC_STORE_NORMAL_ITEMLIST& packet = *(PACKET_ZC_STORE_NORMAL_ITEMLIST*)buf;
	int count = (packet.Length - sizeof(packet)) / sizeof(NORMALITEM_EXTRAINFO);

	g_windowMgr.UIWindowMgr::MakeWindow(WID_ITEMSTOREWND);

	for( int i = 0; i < count; ++i )
	{
		NORMALITEM_EXTRAINFO& item = packet.Item[i];

		ITEM_INFO itemInfo;
		itemInfo.m_itemType      = item.type;
		itemInfo.m_location      = 0;
		itemInfo.m_itemIndex     = item.index;
		itemInfo.m_wearLocation  = item.WearState;
		itemInfo.m_num           = item.count;
		itemInfo.m_slot[0]       = 0;
		itemInfo.m_slot[1]       = 0;
		itemInfo.m_slot[2]       = 0;
		itemInfo.m_slot[3]       = 0;
		itemInfo.ITEM_INFO::SetItemId(item.ITID);
		itemInfo.m_isIdentified  = item.IsIdentified;
		itemInfo.m_isDamaged     = false;
		itemInfo.m_refiningLevel = 0;

		g_session.CSession::AddStoreItem(itemInfo);
	}

	g_session.CSession::RefreshStoreItemWnd();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Store_Normal_Itemlist2(SAKEXE, "CGameMode::Zc_Store_Normal_Itemlist2");
void CGameMode::Zc_Store_Normal_Itemlist2(const char* buf) // line 3920-3950
{
	return (this->*_Zc_Store_Normal_Itemlist2)(buf);

	PACKET_ZC_STORE_NORMAL_ITEMLIST2& packet = *(PACKET_ZC_STORE_NORMAL_ITEMLIST2*)buf;
	int count = (packet.Length - sizeof(packet)) / sizeof(NORMALITEM_EXTRAINFO2);

	g_windowMgr.UIWindowMgr::MakeWindow(WID_ITEMSTOREWND);

	for( int i = 0; i < count; ++i )
	{
		NORMALITEM_EXTRAINFO2& item = packet.Item[i];

		ITEM_INFO itemInfo;
		itemInfo.m_itemType      = item.type;
		itemInfo.m_location      = 0;
		itemInfo.m_itemIndex     = item.index;
		itemInfo.m_wearLocation  = item.WearState;
		itemInfo.m_num           = item.count;
		itemInfo.m_slot[0]       = item.slot.info[0];
		itemInfo.m_slot[1]       = item.slot.info[1];
		itemInfo.m_slot[2]       = item.slot.info[2];
		itemInfo.m_slot[3]       = item.slot.info[3];
		itemInfo.ITEM_INFO::SetItemId(item.ITID);
		itemInfo.m_isIdentified  = item.IsIdentified;
		itemInfo.m_isDamaged     = false;
		itemInfo.m_refiningLevel = 0;

		g_session.CSession::AddStoreItem(itemInfo);
	}

	g_session.CSession::RefreshStoreItemWnd();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Store_Equipment_Itemlist(SAKEXE, "CGameMode::Zc_Store_Equipment_Itemlist");
void CGameMode::Zc_Store_Equipment_Itemlist(const char* buf) // line 3954
{
	return (this->*_Zc_Store_Equipment_Itemlist)(buf);

	PACKET_ZC_STORE_EQUIPMENT_ITEMLIST& packet = *(PACKET_ZC_STORE_EQUIPMENT_ITEMLIST*)buf;
	int count = (packet.Length - sizeof(packet)) / sizeof(EQUIPMENTITEM_EXTRAINFO);

	g_windowMgr.UIWindowMgr::MakeWindow(WID_ITEMSTOREWND);

	for( int i = 0; i < count; ++i )
	{
		EQUIPMENTITEM_EXTRAINFO& item = packet.Item[i];

		ITEM_INFO itemInfo;
		itemInfo.m_itemType = item.type;
		itemInfo.m_location = item.location;
		itemInfo.m_itemIndex = item.index;
		itemInfo.m_wearLocation = item.WearState;
		itemInfo.m_num = 1;
		itemInfo.m_slot[0] = item.slot.info[0];
		itemInfo.m_slot[1] = item.slot.info[1];
		itemInfo.m_slot[2] = item.slot.info[2];
		itemInfo.m_slot[3] = item.slot.info[3];
		itemInfo.ITEM_INFO::SetItemId(item.ITID);
		itemInfo.m_isIdentified = item.IsIdentified;
		itemInfo.m_isDamaged = item.IsDamaged;
		itemInfo.m_refiningLevel = item.RefiningLevel;

		g_session.CSession::AddStoreItem(itemInfo);
	}

	g_session.CSession::RefreshStoreItemWnd();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Item_To_Store(SAKEXE, "CGameMode::Zc_Add_Item_To_Store");
void CGameMode::Zc_Add_Item_To_Store(const char* buf) // line 3985
{
	return (this->*_Zc_Add_Item_To_Store)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Delete_Item_From_Store(SAKEXE, "CGameMode::Zc_Delete_Item_From_Store");
void CGameMode::Zc_Delete_Item_From_Store(const char* buf) // line 4006
{
	return (this->*_Zc_Delete_Item_From_Store)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Close_Store(SAKEXE, "CGameMode::Zc_Close_Store");
void CGameMode::Zc_Close_Store(const char* buf) // line 4018
{
	return (this->*_Zc_Close_Store)(buf);

	PACKET_ZC_CLOSE_STORE& packet = *(PACKET_ZC_CLOSE_STORE*)buf;

	g_windowMgr.UIWindowMgr::DeleteWindow(WID_ITEMSTOREWND);
	g_session.CSession::ClearStoreItem();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Storeitem_Countinfo(SAKEXE, "CGameMode::Zc_Notify_Storeitem_Countinfo");
void CGameMode::Zc_Notify_Storeitem_Countinfo(const char* buf) // line 4023
{
	return (this->*_Zc_Notify_Storeitem_Countinfo)(buf);

	PACKET_ZC_NOTIFY_STOREITEM_COUNTINFO& packet = *(PACKET_ZC_NOTIFY_STOREITEM_COUNTINFO*)buf;

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_ITEMSTOREWND);
	wnd->SendMsg(NULL, 55, packet.curCount, packet.maxCount, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Make_Group(SAKEXE, "CGameMode::Zc_Ack_Make_Group");
void CGameMode::Zc_Ack_Make_Group(const char* buf) // line 4031
{
	return (this->*_Zc_Ack_Make_Group)(buf);

	PACKET_ZC_ACK_MAKE_GROUP& packet = *(PACKET_ZC_ACK_MAKE_GROUP*)buf;

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);

	if( packet.result == 0 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_PARTY_MAKE_SUCCEED), 0xFFFF00, 0);
		g_windowMgr.UIWindowMgr::MakeWindow(WID_MESSENGERGROUPWND);
	}
	else
	if( packet.result == 1 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_SAME_PARTY_NAME), 0x0000FF, 0);
	}
	else
	if( packet.result == 2 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_YOU_ARE_ALREADY_IN_PARTY), 0x0000FF, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Group_List(SAKEXE, "CGameMode::Zc_Group_List");
void CGameMode::Zc_Group_List(const char* buf) // line 4051
{
	return (this->*_Zc_Group_List)(buf);

	PACKET_ZC_GROUP_LIST& packet = *(PACKET_ZC_GROUP_LIST*)buf;
	int count = (packet.PacketLength - sizeof(packet))/sizeof(PACKET_ZC_GROUP_LIST::GROUPMEMBER_INFO);
	
	g_session.CSession::ClearParty();

	char groupName[24+1];
	memcpy(groupName, packet.groupName, sizeof(groupName)-1);
	groupName[sizeof(groupName)-1] = '\0';

	g_session.m_partyName = groupName;

	for( int i = 0; i < count; ++i )
	{
		PACKET_ZC_GROUP_LIST::GROUPMEMBER_INFO& info = packet.Info[i];

		char characterName[24+1];
		memcpy(characterName, info.characterName, sizeof(characterName)-1);
		characterName[sizeof(characterName)-1] = '\0';

		char mapName[16+1];
		memcpy(mapName, info.mapName, sizeof(mapName)-1);
		mapName[sizeof(mapName)-1] = '\0';

		FRIEND_INFO fInfo;
		fInfo.isValid = 1;
		fInfo.AID = info.AID;
		fInfo.characterName = characterName;
		fInfo.mapName = mapName;
		fInfo.role = info.Role;
		fInfo.state = info.State;
		g_session.CSession::AddMemberToParty(fInfo);

		if( fInfo.AID == g_session.CSession::GetAid() && info.Role == 0 )
			g_session.m_amIPartyMaster = 1;
	}

	g_session.CSession::RefreshPartyUI();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Req_Join_Group(SAKEXE, "CGameMode::Zc_Ack_Req_Join_Group");
void CGameMode::Zc_Ack_Req_Join_Group(const char* buf) // line 4095
{
	return (this->*_Zc_Ack_Req_Join_Group)(buf);

	PACKET_ZC_ACK_REQ_JOIN_GROUP& packet = *(PACKET_ZC_ACK_REQ_JOIN_GROUP*)buf;

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);

	switch( packet.result )
	{
	case 0: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_CHARACTER_IS_ALREADY_IN_PARTY), 0x0000FF, 0); break;
	case 1: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_CHARACTER_REJECT_JOIN), 0x0000FF, 0); break;
	case 2: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_CHARACTER_ACCEPT_JOIN), 0xFFFF00, 0); break;
	case 3: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_TOO_MANY_PEOPLE_IN_PARTY), 0x0000FF, 0); break;
	case 4: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_ALREADY_SAME_AID_JOINED), 0x0000FF, 0); break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Join_Group(SAKEXE, "CGameMode::Zc_Req_Join_Group");
void CGameMode::Zc_Req_Join_Group(const char* buf) // line 4120
{
	return (this->*_Zc_Req_Join_Group)(buf);

	PACKET_ZC_REQ_JOIN_GROUP& packet = *(PACKET_ZC_REQ_JOIN_GROUP*)buf;

	char groupName[24+1];
	strncpy(groupName, packet.groupName, sizeof(packet.groupName));
	groupName[sizeof(groupName)-1] = '\0';

	g_session.m_partyName = groupName;

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_JOINPARTYACCEPTWND);
	wnd->SendMsg(NULL, 56, packet.GRID, (int)groupName, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Couple(SAKEXE, "CGameMode::Zc_Req_Couple");
void CGameMode::Zc_Req_Couple(const char* buf) // line 4133
{
	return (this->*_Zc_Req_Couple)(buf);

	PACKET_ZC_REQ_COUPLE& packet = *(PACKET_ZC_REQ_COUPLE*)buf;

	char TheName[24+1];
	strncpy(TheName, packet.name, sizeof(packet.name));
	TheName[sizeof(TheName)-1] = '\0';

	m_lastCouplePacketAid = packet.AID;
	m_lastCouplePacketGid = packet.GID;

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_COUPLEACCEPTWND);
	wnd->SendMsg(NULL, 90, packet.GID, (int)TheName, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Req_Baby(SAKEXE, "CGameMode::Zc_Req_Baby");
void CGameMode::Zc_Req_Baby(const char* buf) // line 4148
{
	return (this->*_Zc_Req_Baby)(buf);

	PACKET_ZC_REQ_BABY& packet = *(PACKET_ZC_REQ_BABY*)buf;

	char TheName[24+1];
	strncpy(TheName, packet.name, sizeof(packet.name));
	TheName[sizeof(TheName)-1] = '\0';

	m_lastCouplePacketAid = packet.AID;
	m_lastCouplePacketGid = packet.GID;

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_BABYACCEPTWND);
	wnd->SendMsg(NULL, 91, packet.GID, (int)TheName, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Member_To_Group(SAKEXE, "CGameMode::Zc_Add_Member_To_Group");
void CGameMode::Zc_Add_Member_To_Group(const char* buf) // line 4163
{
	return (this->*_Zc_Add_Member_To_Group)(buf);
	
	PACKET_ZC_ADD_MEMBER_TO_GROUP& packet = *(PACKET_ZC_ADD_MEMBER_TO_GROUP*)buf;

	char characterName[24+1];
	memcpy(characterName, packet.characterName, sizeof(packet.characterName));
	characterName[countof(characterName)-1] = '\0';

	char groupName[24+1];
	strncpy(groupName, packet.groupName, sizeof(packet.groupName));
	groupName[countof(groupName)-1] = '\0';

	g_session.m_partyName = groupName;

	char mapName[16+1];
	mapName[countof(mapName)-1] = '\0';
	memcpy(mapName, packet.mapName, sizeof(packet.mapName));

	FRIEND_INFO fInfo;
	fInfo.isValid = 1;
	fInfo.characterName = characterName;
	fInfo.AID = packet.AID;
	fInfo.mapName = mapName;
	fInfo.role = packet.Role;
	fInfo.state = packet.state;

	if( fInfo.AID == g_session.CSession::GetAid() )
	{
		if( packet.Role == 0 )
			g_session.m_amIPartyMaster = 1;
	}
	else
	if( packet.state == 1 )
	{
		this->SendMsg(70, packet.AID, 0, 0);
	}
	else
	{
		mystd::string mapName_ = fInfo.mapName;
		mystd::string mapName2 = m_rswName;

		if( mapName_.size() > 4 )
			mapName_.resize(mapName_.size() - 3);

		if( mapName2.size() > 4 )
			mapName2.resize(mapName2.size() - 3);

		if( mapName_ != mapName2 )
			this->SendMsg(70, packet.AID, 0, 0);
	}

	g_session.CSession::AddMemberToParty(fInfo);
	g_session.CSession::RefreshPartyUI();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Member_To_Group2(SAKEXE, "CGameMode::Zc_Add_Member_To_Group2");
void CGameMode::Zc_Add_Member_To_Group2(const char* buf) // line 4210
{
	return (this->*_Zc_Add_Member_To_Group2)(buf);

	PACKET_ZC_ADD_MEMBER_TO_GROUP2& packet = *(PACKET_ZC_ADD_MEMBER_TO_GROUP2*)buf;

	char characterName[24+1];
	memcpy(characterName, packet.characterName, sizeof(packet.characterName));
	characterName[countof(characterName)-1] = '\0';

	char groupName[24+1];
	strncpy(groupName, packet.groupName, sizeof(packet.groupName));
	groupName[countof(groupName)-1] = '\0';

	g_session.m_partyName = groupName;

	char mapName[16+1];
	mapName[countof(mapName)-1] = '\0';
	memcpy(mapName, packet.mapName, sizeof(packet.mapName));

	FRIEND_INFO fInfo;
	fInfo.isValid = 1;
	fInfo.characterName = characterName;
	fInfo.AID = packet.AID;
	fInfo.mapName = mapName;
	fInfo.role = packet.Role;
	fInfo.state = packet.state;

	if( fInfo.AID == g_session.CSession::GetAid() )
	{
		if( packet.Role == 0 )
			g_session.m_amIPartyMaster = 1;
	}
	else
	if( packet.state == 1 )
	{
		this->SendMsg(70, packet.AID, 0, 0);
	}
	else
	{
		mystd::string mapName_ = fInfo.mapName;
		mystd::string mapName2 = m_rswName;

		if( mapName_.size() > 4 )
			mapName_.resize(mapName_.size() - 3);

		if( mapName2.size() > 4 )
			mapName2.resize(mapName2.size() - 3);

		if( mapName_ != mapName2 )
			this->SendMsg(70, packet.AID, 0, 0);
	}

	g_session.m_itemDivType = ( packet.ItemDivisionRule != 0 );
	g_session.m_itemCollectType = ( packet.ItemPickupRule != 0 );
	g_session.CSession::GetNumParty();
	g_session.CSession::AddMemberToParty(fInfo);
	g_session.CSession::RefreshPartyUI();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Delete_Member_From_Group(SAKEXE, "CGameMode::Zc_Delete_Member_From_Group");
void CGameMode::Zc_Delete_Member_From_Group(const char* buf) // line 4277
{
	return (this->*_Zc_Delete_Member_From_Group)(buf);

	PACKET_ZC_DELETE_MEMBER_FROM_GROUP& packet = *(PACKET_ZC_DELETE_MEMBER_FROM_GROUP*)buf;

	char characterName[24+1];
	memcpy(characterName, packet.characterName, sizeof(packet.characterName));
	characterName[countof(characterName)-1] = '\0';

	this->SendMsg(70, g_session.CSession::GetMemberAidFromParty(characterName), 0, 0);

	if( packet.result == 0 )
	{
		g_session.CSession::DeleteMemberFromParty(characterName);
	}
	else if( packet.result == 1 )
	{
		g_session.CSession::DeleteMemberFromParty(characterName);
	}

	if( strcmp(g_session.CSession::GetCharName(), characterName) == 0 )
	{
		g_session.m_amIPartyMaster = 0;
		g_session.CSession::ClearParty();
		g_session.m_partyName = "";
		g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_YOU_LEAVE_FROM_PARTY), 0xFFFF00, 0);
		g_windowMgr.UIWindowMgr::DeleteWindow(WID_PARTYSETTINGWND);
		this->SendMsg(71, 0, 0, 0);
	}

	g_session.CSession::RefreshPartyUI();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Hp_To_Groupm(SAKEXE, "CGameMode::Zc_Notify_Hp_To_Groupm");
void CGameMode::Zc_Notify_Hp_To_Groupm(const char* buf) // line 4312
{
	return (this->*_Zc_Notify_Hp_To_Groupm)(buf);

	PACKET_ZC_NOTIFY_HP_TO_GROUPM& packet = *(PACKET_ZC_NOTIFY_HP_TO_GROUPM*)buf;

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.AID);
	if( actor != NULL )
		actor->SendMsg(NULL, 34, packet.hp, packet.maxhp, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Position_To_Groupm(SAKEXE, "CGameMode::Zc_Notify_Position_To_Groupm");
void CGameMode::Zc_Notify_Position_To_Groupm(const char* buf) // line 4323
{
	return (this->*_Zc_Notify_Position_To_Groupm)(buf);

	PACKET_ZC_NOTIFY_POSITION_TO_GROUPM& packet = *(PACKET_ZC_NOTIFY_POSITION_TO_GROUPM*)buf;
	this->SendMsg(69, packet.AID, packet.xPos, packet.yPos);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Chat_Party(SAKEXE, "CGameMode::Zc_Notify_Chat_Party");
void CGameMode::Zc_Notify_Chat_Party(const char* buf) // line 4368
{
	return (this->*_Zc_Notify_Chat_Party)(buf);

	PACKET_ZC_NOTIFY_CHAT_PARTY& packet = *(PACKET_ZC_NOTIFY_CHAT_PARTY*)buf;
	size_t size = packet.PacketLength - sizeof(packet); //FIXME: no size cap/check

	char chatMsg[256];
	memcpy(chatMsg, packet.Text, size);
	chatMsg[size-1] = '\0';
	chatMsg[sizeof(chatMsg)-1] = '\0';

	if( g_session.CSession::GetAid() == packet.AID )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)chatMsg, 0x00C8FF, 0);
		m_world->m_player->SendMsg(NULL, 7, (int)chatMsg, 0, 0);
	}
	else
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)chatMsg, 0xC8C8FF, 0);

		CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.AID);
		if( actor != NULL )
			actor->SendMsg(NULL, 7, (int)chatMsg, 0, 0);
	}

	if( g_session.m_isSaveChat )
		this->CGameMode::WriteChat(chatMsg);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mvp_Getting_Item(SAKEXE, "CGameMode::Zc_Mvp_Getting_Item");
void CGameMode::Zc_Mvp_Getting_Item(const char* buf) // line 4391
{
	return (this->*_Zc_Mvp_Getting_Item)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mvp_Getting_Special_Exp(SAKEXE, "CGameMode::Zc_Mvp_Getting_Special_Exp");
void CGameMode::Zc_Mvp_Getting_Special_Exp(const char* buf) // line 4413
{
	return (this->*_Zc_Mvp_Getting_Special_Exp)(buf);

	PACKET_ZC_MVP_GETTING_SPECIAL_EXP& packet = *(PACKET_ZC_MVP_GETTING_SPECIAL_EXP*)buf;

	char msg[256];
	sprintf(msg, "%s%d%s", MsgStr(MSI_YOU_RECEIVE_MVP_EXP), packet.exp, MsgStr(MSI_YOU_RECEIVE_MVP_EXP2));

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg, 0xFFFF00, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Mvp(SAKEXE, "CGameMode::Zc_Mvp");
void CGameMode::Zc_Mvp(const char* buf) // line 4424
{
	return (this->*_Zc_Mvp)(buf);

	PACKET_ZC_MVP& packet = *(PACKET_ZC_MVP*)buf;

	if( packet.AID == g_session.CSession::GetAid() )
	{
		m_world->m_player->SendMsg(NULL, 36, 0, 0, 0);
	}
	else
	{
		CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.AID);
		if( actor != NULL )
			actor->SendMsg(NULL, 36, 0, 0, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Throw_Mvpitem(SAKEXE, "CGameMode::Zc_Throw_Mvpitem");
void CGameMode::Zc_Throw_Mvpitem(const char* buf) // line 4438
{
	return (this->*_Zc_Throw_Mvpitem)(buf);

	PACKET_ZC_THROW_MVPITEM& packet = *(PACKET_ZC_THROW_MVPITEM*)buf;

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_YOU_THROW_MVPITEM), 0x0000FF, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skillinfo_Update(SAKEXE, "CGameMode::Zc_Skillinfo_Update");
void CGameMode::Zc_Skillinfo_Update(const char* buf) // line 4443
{
	return (this->*_Zc_Skillinfo_Update)(buf);

	PACKET_ZC_SKILLINFO_UPDATE& packet = *(PACKET_ZC_SKILLINFO_UPDATE*)buf;

	m_isReqUpgradeSkillLevel = 0;

	SKILL_INFO skillInfo = g_session.CSession::GetSkillItemInfoBySkillId(packet.SKID);
	skillInfo.level = packet.level;
	skillInfo.SKID = packet.SKID;
	skillInfo.spcost = packet.spcost;
	skillInfo.upgradable = packet.upgradable;
	skillInfo.attackRange = packet.attackRange;

	g_session.CSession::AddSkillItem(skillInfo, true);
	g_session.CSession::RefreshSkillItemWnd();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skillinfo_List(SAKEXE, "CGameMode::Zc_Skillinfo_List");
void CGameMode::Zc_Skillinfo_List(const char* buf) // line 4459
{
	return (this->*_Zc_Skillinfo_List)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Touseskill(SAKEXE, "CGameMode::Zc_Ack_Touseskill");
void CGameMode::Zc_Ack_Touseskill(const char* buf) // line 4489
{
	return (this->*_Zc_Ack_Touseskill)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Skill(SAKEXE, "CGameMode::Zc_Add_Skill");
void CGameMode::Zc_Add_Skill(const char* buf) // line 4592
{
	return (this->*_Zc_Add_Skill)(buf);

	PACKET_ZC_ADD_SKILL& packet = *(PACKET_ZC_ADD_SKILL*)buf;

	SKILL_INFO skillInfo;
	skillInfo.m_isValid = 1;
	skillInfo.level = packet.data.level;
	skillInfo.type = packet.data.type;
	skillInfo.skillName = NULL;
	skillInfo.SKID = packet.data.SKID;
	skillInfo.upgradable = packet.data.upgradable;
	skillInfo.skillName = skillInfo.SKILL_INFO::GetSkillIdName();
	skillInfo.spcost = packet.data.spcost;
	skillInfo.attackRange = packet.data.attackRange;

	g_session.CSession::AddSkillItem(skillInfo, true);
	g_session.CSession::RefreshSkillItemWnd();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Skill(SAKEXE, "CGameMode::Zc_Notify_Skill");
void CGameMode::Zc_Notify_Skill(const char* buf) // line 4615
{
	return (this->*_Zc_Notify_Skill)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Skill_Position(SAKEXE, "CGameMode::Zc_Notify_Skill_Position");
void CGameMode::Zc_Notify_Skill_Position(const char* buf) // line 4690
{
	return (this->*_Zc_Notify_Skill_Position)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Groundskill(SAKEXE, "CGameMode::Zc_Notify_Groundskill");
void CGameMode::Zc_Notify_Groundskill(const char* buf) // line 4758-4827
{
	return (this->*_Zc_Notify_Groundskill)(buf);

	PACKET_ZC_NOTIFY_GROUNDSKILL& packet = *(PACKET_ZC_NOTIFY_GROUNDSKILL*)buf;

	GROUNDSKILLSTRUCT gss;
	gss.skillId = packet.SKID;
	gss.startTime = packet.startTime;
	gss.cellX = packet.xPos;
	gss.cellY = packet.yPos;
	gss.level = packet.level;

	CGameActor* theActor = NULL;
	if( packet.AID == g_session.CSession::GetAid() )
	{
		theActor = m_world->m_player;
		theActor->SendMsg(NULL, 38, (int)&gss, 0, 0);
	}
	else
	{
		theActor = m_world->CWorld::GetGameActorByAID(packet.AID);
		if( theActor != NULL )
			theActor->SendMsg(NULL, 38, (int)&gss, 0, 0);
	}

	int job = -1;
	if( theActor != NULL )
		job = theActor->CGameActor::GetJob();

	if( g_session.CSession::IsMonster(job) )
	{
		int act, loopType;
		g_session.CSession::GetMonsterSkillInfo(const_cast<char*>(g_session.m_jobNameTable[job]), packet.SKID, act, loopType);
	}
	else
	{
		this->SendMsg(99, packet.SKID, (int)theActor, packet.level);

		if( packet.SKID == 345 )
			PlayWave("effect\\바실리카.wav", 0.0, 0.0, 0.0, 250, 40, 1.0);
		else
		if( packet.SKID == 352 )
			PlayWave("effect\\가스펠.wav", 0.0, 0.0, 0.0, 250, 40, 1.0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_State_Change(SAKEXE, "CGameMode::Zc_State_Change");
void CGameMode::Zc_State_Change(const char* buf) // line 4830
{
	return (this->*_Zc_State_Change)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Entry(SAKEXE, "CGameMode::Zc_Skill_Entry");
void CGameMode::Zc_Skill_Entry(const char* buf) // line 4864
{
	return (this->*_Zc_Skill_Entry)(buf);

	PACKET_ZC_SKILL_ENTRY& packet = *(PACKET_ZC_SKILL_ENTRY*)buf;

	SKILLSTANDENTRYSTRUCT s;
	s.AID = packet.AID;
	s.creatorAID = packet.creatorAID;
	s.job = packet.job;
	s.xPos = packet.xPos;
	s.yPos = packet.yPos;
	s.isVisible = true;
	packet.isVisible = true;

	CSkill* skill = m_world->CWorld::GetSkillByAID(packet.AID);

	if( s.creatorAID != g_session.CSession::GetAid() )
	{
		for( mystd::list<unsigned long>::iterator it = m_visibleTrapList.begin(); it != m_visibleTrapList.end(); ++it )
		{
			if( *it == packet.AID )
			{
				m_visibleTrapList.erase(it);
				s.isVisible = false;
				packet.isVisible = false;
				break;
			}
		}
	}

	if( s.isVisible )
		m_visibleTrapList.push_back(packet.AID);

	if( skill == NULL )
	{
		if( packet.job >= JT_WARPNPC && packet.job < JT_2004_JOB_BEGIN )
		{
			skill = new CSkill();
			m_world->m_gameObjectList.push_back(skill);
			m_world->m_skillList.push_back(skill);
		}
	}

	if( skill != NULL )
		skill->SendMsg(NULL, 45, (int)&s, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Disappear(SAKEXE, "CGameMode::Zc_Skill_Disappear");
void CGameMode::Zc_Skill_Disappear(const char* buf) // line 4908
{
	return (this->*_Zc_Skill_Disappear)(buf);

	PACKET_ZC_SKILL_DISAPPEAR& packet = *(PACKET_ZC_SKILL_DISAPPEAR*)buf;
	m_world->CWorld::RemoveSkill(packet.AID);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Warplist(SAKEXE, "CGameMode::Zc_Warplist");
void CGameMode::Zc_Warplist(const char* buf) // line 4914
{
	return (this->*_Zc_Warplist)(buf);

	PACKET_ZC_WARPLIST& packet = *(PACKET_ZC_WARPLIST*)buf;

	g_windowMgr.UIWindowMgr::DeleteWindow(WID_CHOOSEWARPWND);
	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_CHOOSEWARPWND);
	wnd->SendMsg(NULL, 59, packet.SKID, 0, 0);

	for( int i = 0; i < countof(packet.mapName); ++i )
		if( strlen(packet.mapName[i]) != 0 )
			wnd->SendMsg(NULL, 27, (int)packet.mapName[i], 0, 0);

	wnd->SendMsg(NULL, 27, (int)"cancel", 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Remember_Warppoint(SAKEXE, "CGameMode::Zc_Ack_Remember_Warppoint");
void CGameMode::Zc_Ack_Remember_Warppoint(const char* buf) // line 4929
{
	return (this->*_Zc_Ack_Remember_Warppoint)(buf);

	PACKET_ZC_ACK_REMEMBER_WARPPOINT& packet = *(PACKET_ZC_ACK_REMEMBER_WARPPOINT*)buf;

	if( packet.errorCode == 0 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_WARPPOINTSTORED), 0xFFFF00, 0);
	}
	else
	if( packet.errorCode == 1 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_NOTENOUGHSKILLLEVEL), 0x0000FF, 0);
	}
	else
	if( packet.errorCode == 2 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_NOWARPSKILL), 0x0000FF, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Cartitem_Countinfo(SAKEXE, "CGameMode::Zc_Notify_Cartitem_Countinfo");
void CGameMode::Zc_Notify_Cartitem_Countinfo(const char* buf) // line 4946
{
	return (this->*_Zc_Notify_Cartitem_Countinfo)(buf);

	PACKET_ZC_NOTIFY_CARTITEM_COUNTINFO& packet = *(PACKET_ZC_NOTIFY_CARTITEM_COUNTINFO*)buf;

	g_session.m_cartMaxCount = packet.maxCount;
	g_session.m_cartCurCount = packet.curCount;
	g_session.m_cartCurWeight = packet.curWeight / 10;
	g_session.m_cartMaxWeight = packet.maxWeight / 10;

	if( g_windowMgr.UIWindowMgr::GetMerchantItemWnd() != 0 )
		g_windowMgr.UIWindowMgr::GetMerchantItemWnd()->SendMsg(0, 55, 0, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cart_Normal_Itemlist(SAKEXE, "CGameMode::Zc_Cart_Normal_Itemlist");
void CGameMode::Zc_Cart_Normal_Itemlist(const char* buf) // line 4967
{
	return (this->*_Zc_Cart_Normal_Itemlist)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cart_Normal_Itemlist2(SAKEXE, "CGameMode::Zc_Cart_Normal_Itemlist2");
void CGameMode::Zc_Cart_Normal_Itemlist2(const char* buf) // line 5001
{
	return (this->*_Zc_Cart_Normal_Itemlist2)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cart_Equipment_Itemlist(SAKEXE, "CGameMode::Zc_Cart_Equipment_Itemlist");
void CGameMode::Zc_Cart_Equipment_Itemlist(const char* buf) // line 5036
{
	return (this->*_Zc_Cart_Equipment_Itemlist)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Cartoff(SAKEXE, "CGameMode::Zc_Cartoff");
void CGameMode::Zc_Cartoff(const char* buf) // line 5068
{
	return (this->*_Zc_Cartoff)(buf);

	PACKET_ZC_CARTOFF& packet = *(PACKET_ZC_CARTOFF*)buf;

	g_session.CSession::ClearMerchantItem();
	g_windowMgr.UIWindowMgr::DeleteWindow(WID_MERCHANTITEMWND);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_Additem_To_Cart(SAKEXE, "CGameMode::Zc_Ack_Additem_To_Cart");
void CGameMode::Zc_Ack_Additem_To_Cart(const char* buf) // line 5073
{
	return (this->*_Zc_Ack_Additem_To_Cart)(buf);

	PACKET_ZC_ACK_ADDITEM_TO_CART& packet = *(PACKET_ZC_ACK_ADDITEM_TO_CART*)buf;

	if( packet.result == 0 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_OVER_WEIGHT), 0x0000FF, 0);
	}
	else
	if( packet.result == 1 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_INSUFFICIENT_OVER_COUNT), 0x0000FF, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Item_To_Cart(SAKEXE, "CGameMode::Zc_Add_Item_To_Cart");
void CGameMode::Zc_Add_Item_To_Cart(const char* buf) // line 5088
{
	return (this->*_Zc_Add_Item_To_Cart)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Delete_Item_From_Cart(SAKEXE, "CGameMode::Zc_Delete_Item_From_Cart");
void CGameMode::Zc_Delete_Item_From_Cart(const char* buf) // line 5107
{
	return (this->*_Zc_Delete_Item_From_Cart)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_openstore(SAKEXE, "CGameMode::Zc_openstore");
void CGameMode::Zc_openstore(const char* buf) // line 5116
{
	return (this->*_Zc_openstore)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_store_entry(SAKEXE, "CGameMode::Zc_store_entry");
void CGameMode::Zc_store_entry(const char* buf) // line 5138
{
	return (this->*_Zc_store_entry)(buf);

	PACKET_ZC_STORE_ENTRY& packet = *(PACKET_ZC_STORE_ENTRY*)buf;

	char storeName[80+1];
	strncpy(storeName, packet.storeName, sizeof(packet.storeName));
	storeName[sizeof(storeName)-1] = '\0';

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.makerAID);
	if( actor != NULL )
		actor->SendMsg(NULL, 55, (int)storeName, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_disappear_entry(SAKEXE, "CGameMode::Zc_disappear_entry");
void CGameMode::Zc_disappear_entry(const char* buf) // line 5150
{
	return (this->*_Zc_disappear_entry)(buf);

	PACKET_ZC_DISAPPEAR_ENTRY& packet = *(PACKET_ZC_DISAPPEAR_ENTRY*)buf;

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.makerAID);
	if( actor != NULL )
		actor->SendMsg(NULL, 54, 0, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_pc_purchase_itemlist_frommc(SAKEXE, "CGameMode::Zc_pc_purchase_itemlist_frommc");
void CGameMode::Zc_pc_purchase_itemlist_frommc(const char* buf) // line 5158
{
	return (this->*_Zc_pc_purchase_itemlist_frommc)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_pc_purchase_myitemlist(SAKEXE, "CGameMode::Zc_pc_purchase_myitemlist");
void CGameMode::Zc_pc_purchase_myitemlist(const char* buf) // line 5196
{
	return (this->*_Zc_pc_purchase_myitemlist)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_pc_purchase_result_frommc(SAKEXE, "CGameMode::Zc_pc_purchase_result_frommc");
void CGameMode::Zc_pc_purchase_result_frommc(const char* buf) // line 5231
{
	return (this->*_Zc_pc_purchase_result_frommc)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_deleteitem_from_mcstore(SAKEXE, "CGameMode::Zc_deleteitem_from_mcstore");
void CGameMode::Zc_deleteitem_from_mcstore(const char* buf) // line 5273
{
	return (this->*_Zc_deleteitem_from_mcstore)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_attack_failure_for_distance(SAKEXE, "CGameMode::Zc_attack_failure_for_distance");
void CGameMode::Zc_attack_failure_for_distance(const char* buf) // line 5312
{
	return (this->*_Zc_attack_failure_for_distance)(buf);

	PACKET_ZC_ATTACK_FAILURE_FOR_DISTANCE& packet = *(PACKET_ZC_ATTACK_FAILURE_FOR_DISTANCE*)buf;

	Trace("PACKET_ZC_ATTACK_FAILURE_FOR_DISTANCE");

	g_session.m_attackRange = packet.currentAttRange;

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.targetAID);
	if( actor != NULL )
		actor->SendMsg(NULL, 61, packet.targetXPos, packet.targetYPos, 0);

	m_world->m_player->SendMsg(NULL, 61, packet.xPos, packet.yPos, 0);
	m_world->m_player->SendMsg(NULL, 60, packet.targetAID, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_attack_range(SAKEXE, "CGameMode::Zc_attack_range");
void CGameMode::Zc_attack_range(const char* buf) // line 5325
{
	return (this->*_Zc_attack_range)(buf);

	PACKET_ZC_ATTACK_RANGE& packet = *(PACKET_ZC_ATTACK_RANGE*)buf;
	g_session.m_attackRange = packet.currentAttRange;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_action_failure(SAKEXE, "CGameMode::Zc_action_failure");
void CGameMode::Zc_action_failure(const char* buf) // line 5331
{
	return (this->*_Zc_action_failure)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_equip_arrow(SAKEXE, "CGameMode::Zc_equip_arrow");
void CGameMode::Zc_equip_arrow(const char* buf) // line 5358
{
	return (this->*_Zc_equip_arrow)(buf);

	PACKET_ZC_EQUIP_ARROW& packet = *(PACKET_ZC_EQUIP_ARROW*)buf;

	g_session.CSession::SetEquipArrowIndwx(packet.index);
	m_waitingWearEquipAck = timeGetTime() - 2000;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_recovery(SAKEXE, "CGameMode::Zc_recovery");
void CGameMode::Zc_recovery(const char* buf) // line 5372
{
	return (this->*_Zc_recovery)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_useskill_ack(SAKEXE, "CGameMode::Zc_useskill_ack");
void CGameMode::Zc_useskill_ack(const char* buf) // line 5405
{
	return (this->*_Zc_useskill_ack)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Use_Skill(SAKEXE, "CGameMode::Zc_Use_Skill");
void CGameMode::Zc_Use_Skill(const char* buf) // line 5517
{
	return (this->*_Zc_Use_Skill)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_groupinfo_change(SAKEXE, "CGameMode::Zc_groupinfo_change");
void CGameMode::Zc_groupinfo_change(const char* buf) // line 6502
{
	return (this->*_Zc_groupinfo_change)(buf);

	PACKET_ZC_GROUPINFO_CHANGE& packet = *(PACKET_ZC_GROUPINFO_CHANGE*)buf;

	g_session.m_expDivType = packet.expDivType;
	if( g_windowMgr.UIWindowMgr::GetPartySettingWnd() != NULL )
		g_windowMgr.UIWindowMgr::GetPartySettingWnd()->SendMsg(NULL, 60, 0, 0, 0);

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);

	if( g_session.m_expDivType == 0 )
	{
		char text[128];
		sprintf(text, "%s - %s : %s", MsgStr(MSI_PARTYSETTING), MsgStr(MSI_HOWEXPDIV), MsgStr(MSI_EXPDIV1));
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)text, 0x00FFFF, 0);
	}
	else if( g_session.m_expDivType == 1 )
	{
		char text[128];
		sprintf(text, "%s - %s : %s", MsgStr(MSI_PARTYSETTING), MsgStr(MSI_HOWEXPDIV), MsgStr(MSI_EXPDIV2));
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)text, 0x00FFFF, 0);
	}
	else if( g_session.m_expDivType == 2 )
	{
		char text[128];
		sprintf(text, "%s", MsgStr(MSI_PARTYSETTING_CHANGE_IMPOSSIBLE), MsgStr(MSI_HOWEXPDIV), MsgStr(MSI_EXPDIV2));
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)text, 0x00FFFF, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_couplestatus(SAKEXE, "CGameMode::Zc_couplestatus");
void CGameMode::Zc_couplestatus(const char* buf) // line 6531-6562
{
	return (this->*_Zc_couplestatus)(buf);

	PACKET_ZC_COUPLESTATUS& packet = *(PACKET_ZC_COUPLESTATUS*)buf;
	int type = packet.statusType;
	int value = packet.defaultStatus;
	int plusvalue = packet.plusStatus;

	switch( type )
	{
	case 0xD: // VAR_STR
		g_session.CSession::SetStr(value); //inline
		g_session.CSession::SetPlusStr(plusvalue); //inline
	break;
	case 0xE: // VAR_AGI
		g_session.CSession::SetAgi(value); //inline
		g_session.CSession::SetPlusAgi(plusvalue); //inline
	break;
	case 0xF: // VAR_VIT
		g_session.CSession::SetVit(value); //inline
		g_session.CSession::SetPlusVit(plusvalue); //inline
	break;
	case 0x10: // VAR_INT
		g_session.CSession::SetInt(value); //inline
		g_session.CSession::SetPlusInt(plusvalue); //inline
	break;
	case 0x11: // VAR_DEX
		g_session.CSession::SetDex(value); //inline
		g_session.CSession::SetPlusDex(plusvalue); //inline
	break;
	case 0x12: // VAR_LUK
		g_session.CSession::SetLuk(value); //inline
		g_session.CSession::SetPlusLuk(plusvalue); //inline
	break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_open_editdlg(SAKEXE, "CGameMode::Zc_open_editdlg");
void CGameMode::Zc_open_editdlg(const char* buf) // line 6565
{
	return (this->*_Zc_open_editdlg)(buf);

	PACKET_ZC_OPEN_EDITDLG& packet = *(PACKET_ZC_OPEN_EDITDLG*)buf;

	if( m_world->CWorld::GetGameActorByAID(packet.NAID) )
	{
		UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_NPCEDITDIALOGWND);
		wnd->SendMsg(NULL, 28, packet.NAID, 0, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_compass(SAKEXE, "CGameMode::Zc_compass");
void CGameMode::Zc_compass(const char* buf) // line 6576
{
	return (this->*_Zc_compass)(buf);

	PACKET_ZC_COMPASS& packet = *(PACKET_ZC_COMPASS*)buf;

	if( packet.type == 2 )
	{
		this->CGameMode::DeleteCompassPos(packet.id);
	}
	else
	{
		m_compassPosList[packet.id].x = packet.xPos;
		m_compassPosList[packet.id].y = packet.yPos;
		m_compassPosList[packet.id].color = packet.color | 0xFF000000;
		m_compassPosList[packet.id].type = packet.type;
		m_compassPosList[packet.id].startTime = timeGetTime();
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_show_image(SAKEXE, "CGameMode::Zc_show_image");
void CGameMode::Zc_show_image(const char* buf) // line 6595
{
	return (this->*_Zc_show_image)(buf);

	PACKET_ZC_SHOW_IMAGE& packet = *(PACKET_ZC_SHOW_IMAGE*)buf;

	char imageName[16+1];
	strncpy(imageName, packet.imageName, sizeof(packet.imageName));
	imageName[sizeof(imageName)-1] = '\0';

	int type = packet.type;
	if( type == 255 )
		type = -1;

	this->SendMsg(113, (int)imageName, type, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_show_image2(SAKEXE, "CGameMode::Zc_show_image2");
void CGameMode::Zc_show_image2(const char* buf) // line 6608
{
	return (this->*_Zc_show_image2)(buf);

	PACKET_ZC_SHOW_IMAGE2& packet = *(PACKET_ZC_SHOW_IMAGE2*)buf;

	char imageName[64+1];
	strncpy(imageName, packet.imageName, sizeof(packet.imageName));
	imageName[sizeof(imageName)-1] = '\0';

	int type = packet.type;
	if( type == 255 )
		type = -1;

	this->SendMsg(113, (int)imageName, type, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_autorun_skill(SAKEXE, "CGameMode::Zc_autorun_skill");
void CGameMode::Zc_autorun_skill(const char* buf) // line 6621
{
	return (this->*_Zc_autorun_skill)(buf);

	PACKET_ZC_AUTORUN_SKILL& packet = *(PACKET_ZC_AUTORUN_SKILL*)buf;

	SKILL_INFO skillInfo;
	skillInfo.level = packet.data.level;
	skillInfo.type = packet.data.type;
	skillInfo.m_isValid = 1;
	skillInfo.skillName = NULL;
	skillInfo.SKID = packet.data.SKID;
	skillInfo.upgradable = packet.data.upgradable;
	skillInfo.skillName = skillInfo.SKILL_INFO::GetSkillIdName();
	skillInfo.spcost = packet.data.spcost;
	skillInfo.attackRange = packet.data.attackRange;

	g_session.CSession::AddTempSkillItem(skillInfo);
	this->SendMsg(126, (int)&skillInfo, skillInfo.level, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_resurrection(SAKEXE, "CGameMode::Zc_resurrection");
void CGameMode::Zc_resurrection(const char* buf) // line 6640
{
	return (this->*_Zc_resurrection)(buf);

	PACKET_ZC_RESURRECTION& packet = *(PACKET_ZC_RESURRECTION*)buf;

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.AID);
	if( actor != NULL )
		actor->SendMsg(NULL, 98, 0, 0, 0);

	if( packet.AID == g_session.CSession::GetAid() )
	{
		m_world->m_player->SendMsg(NULL, 98, 0, 0, 0);
		m_isOnQuest = 0;
		m_isPlayerDead = 0;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_guild_emblem_img(SAKEXE, "CGameMode::Zc_guild_emblem_img");
void CGameMode::Zc_guild_emblem_img(const char* buf) // line 6662
{
	return (this->*_Zc_guild_emblem_img)(buf);

	PACKET_ZC_GUILD_EMBLEM_IMG& packet = *(PACKET_ZC_GUILD_EMBLEM_IMG*)buf;
	int size = packet.PacketLength - sizeof(packet);

	g_session.CSession::SetCompressedEmblemImage(packet.Emblem, size, packet.GDID, packet.emblemVersion);
	if( g_guildInfo.m_gdid == packet.GDID )
	{
		m_world->m_player->SetGuildInfo(packet.GDID, packet.emblemVersion);

		if( g_windowMgr.UIWindowMgr::GetGuildInfoManageWnd() != NULL )
			g_windowMgr.UIWindowMgr::GetGuildInfoManageWnd()->SendMsg(0, 60, 0, 0, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_guild_info(SAKEXE, "CGameMode::Zc_guild_info");
void CGameMode::Zc_guild_info(const char* buf) // line 6684
{
	return (this->*_Zc_guild_info)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_myguild_basic_info(SAKEXE, "CGameMode::Zc_myguild_basic_info");
void CGameMode::Zc_myguild_basic_info(const char* buf) // line 6725
{
	return (this->*_Zc_myguild_basic_info)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_guild_menuinterface(SAKEXE, "CGameMode::Zc_ack_guild_menuinterface");
void CGameMode::Zc_ack_guild_menuinterface(const char* buf) // line 6749
{
	return (this->*_Zc_ack_guild_menuinterface)(buf);

	PACKET_ZC_ACK_GUILD_MENUINTERFACE& packet = *(PACKET_ZC_ACK_GUILD_MENUINTERFACE*)buf;
	g_guildInfo.m_guildTabBitmask = packet.guildMemuFlag;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_position_id_name_info(SAKEXE, "CGameMode::Zc_position_id_name_info");
void CGameMode::Zc_position_id_name_info(const char* buf) // line 6755
{
	return (this->*_Zc_position_id_name_info)(buf);

	PACKET_ZC_POSITION_ID_NAME_INFO& packet = *(PACKET_ZC_POSITION_ID_NAME_INFO*)buf;
	int count = (packet.PacketLength - sizeof(packet))/sizeof(PACKET_ZC_POSITION_ID_NAME_INFO::MEMBER_POSITION_ID_NAME_INFO);

	char posName[24+1];
	posName[sizeof(posName)-1] = '\0';

	for( int i = 0; i < count; ++i )
	{
		PACKET_ZC_POSITION_ID_NAME_INFO::MEMBER_POSITION_ID_NAME_INFO& info = packet.Info[i];
		memcpy(posName, info.posName, sizeof(info.posName));
		g_guildInfo.m_positionIdNameMap[info.positionID] = posName;
	}

	g_windowMgr.UIWindowMgr::InvalidateGuildWnd();
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_change_members(SAKEXE, "CGameMode::Zc_ack_req_change_members");
void CGameMode::Zc_ack_req_change_members(const char* buf) // line 6771
{
	return (this->*_Zc_ack_req_change_members)(buf);

	PACKET_ZC_ACK_REQ_CHANGE_MEMBERS& packet = *(PACKET_ZC_ACK_REQ_CHANGE_MEMBERS*)buf;
	int count = (packet.PacketLength - sizeof(packet))/sizeof(MEMBER_POSITION_INFORMATION);

	for( int i = 0; i < count; ++i )
	{
		MEMBER_POSITION_INFORMATION& info = packet.Info[i];
		g_guildInfo.GuildInfo::ChangeMemberPosition(info.AID, info.GID, info.positionID);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_membermgr_info(SAKEXE, "CGameMode::Zc_membermgr_info");
void CGameMode::Zc_membermgr_info(const char* buf) // line 6784
{
	return (this->*_Zc_membermgr_info)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_open_member_info(SAKEXE, "CGameMode::Zc_ack_open_member_info");
void CGameMode::Zc_ack_open_member_info(const char* buf) // line 6831
{
	return (this->*_Zc_ack_open_member_info)(buf);

	;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_leave_guild(SAKEXE, "CGameMode::Zc_ack_leave_guild");
void CGameMode::Zc_ack_leave_guild(const char* buf) // line 6834
{
	return (this->*_Zc_ack_leave_guild)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_ban_guild(SAKEXE, "CGameMode::Zc_ack_ban_guild");
void CGameMode::Zc_ack_ban_guild(const char* buf) // line 6869
{
	return (this->*_Zc_ack_ban_guild)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_disorganize_guild_result(SAKEXE, "CGameMode::Zc_ack_disorganize_guild_result");
void CGameMode::Zc_ack_disorganize_guild_result(const char* buf) // line 6914
{
	return (this->*_Zc_ack_disorganize_guild_result)(buf);

	PACKET_ZC_ACK_DISORGANIZE_GUILD_RESULT& packet = *(PACKET_ZC_ACK_DISORGANIZE_GUILD_RESULT*)buf;

	if( packet.reason == 0 )
	{
		g_guildInfo.GuildInfo::Init();
		g_windowMgr.UIWindowMgr::DeleteWindow(WID_GUILDWND);
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_DISORGANIZE_GUILD_SUCCESS), 0x00FFFF, 0);
	}
	else
	if( packet.reason == 1 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_DISORGANIZE_GUILD_INVALIDKEY), 0x00FFFF, 0);
	}
	else
	if( packet.reason == 2 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_DISORGANIZE_GUILD_MEMBEREXIST), 0x00FFFF, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_disorganize_guild(SAKEXE, "CGameMode::Zc_ack_disorganize_guild");
void CGameMode::Zc_ack_disorganize_guild(const char* buf) // line 6938
{
	return (this->*_Zc_ack_disorganize_guild)(buf);

	PACKET_ZC_ACK_DISORGANIZE_GUILD& packet = *(PACKET_ZC_ACK_DISORGANIZE_GUILD*)buf;

	char reasonDesc[40+1];
	memcpy(reasonDesc, packet.reasonDesc, sizeof(packet.reasonDesc));
	reasonDesc[sizeof(reasonDesc)-1] = '\0';

	char message[1024];
	sprintf(message, MsgStr(MSI_DISORGANIZATION_REASON), reasonDesc);

	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)message, 0x00FFFF, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_position_info(SAKEXE, "CGameMode::Zc_position_info");
void CGameMode::Zc_position_info(const char* buf) // line 6951
{
	return (this->*_Zc_position_info)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ban_list(SAKEXE, "CGameMode::Zc_ban_list");
void CGameMode::Zc_ban_list(const char* buf) // line 6981
{
	return (this->*_Zc_ban_list)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_other_guild_list(SAKEXE, "CGameMode::Zc_other_guild_list");
void CGameMode::Zc_other_guild_list(const char* buf) // line 7019
{
	return (this->*_Zc_other_guild_list)(buf);

	;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_result_make_guild(SAKEXE, "CGameMode::Zc_result_make_guild");
void CGameMode::Zc_result_make_guild(const char* buf) // line 7022
{
	return (this->*_Zc_result_make_guild)(buf);

	PACKET_ZC_RESULT_MAKE_GUILD& packet = *(PACKET_ZC_RESULT_MAKE_GUILD*)buf;

	switch( packet.result )
	{
	case 0: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_GUILD_MAKE_SUCCESS), 0xFFFF00, 0); break;
	case 1: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_GUILD_MAKE_ALREADY_MEMBER), 0x00FFFF, 0); break;
	case 2: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_GUILD_MAKE_GUILD_EXIST), 0x00FFFF, 0); break;
	case 3: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_GUILD_MAKE_GUILD_NONE_ITEM), 0x00FFFF, 0); break;
	default: break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_join_guild(SAKEXE, "CGameMode::Zc_ack_req_join_guild");
void CGameMode::Zc_ack_req_join_guild(const char* buf) // line 7041
{
	return (this->*_Zc_ack_req_join_guild)(buf);

	PACKET_ZC_ACK_REQ_JOIN_GUILD& packet = *(PACKET_ZC_ACK_REQ_JOIN_GUILD*)buf;

	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);

	switch( packet.answer )
	{
	case 0: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_CHARACTER_IS_ALREADY_IN_GUILD), 0x0000FF, 0); break;
	case 1: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_CHARACTER_REJECT_JOIN_GUILD), 0x0000FF, 0); break;
	case 2: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_CHARACTER_ACCEPT_JOIN_GUILD), 0xFFFF00, 0); break;
	case 3: g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_TOO_MANY_PEOPLE_IN_GUILD), 0x0000FF, 0); break;
	default: break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_req_join_guild(SAKEXE, "CGameMode::Zc_req_join_guild");
void CGameMode::Zc_req_join_guild(const char* buf) // line 7063
{
	return (this->*_Zc_req_join_guild)(buf);

	PACKET_ZC_REQ_JOIN_GUILD& packet = *(PACKET_ZC_REQ_JOIN_GUILD*)buf;

	char guildName[24+1];
	memcpy(guildName, packet.guildName, sizeof(packet.guildName));
	guildName[sizeof(guildName)-1] = '\0';

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_JOINGUILDACCEPTWND);
	wnd->SendMsg(NULL, 73, packet.GDID, (int)guildName, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_update_gdid(SAKEXE, "CGameMode::Zc_update_gdid");
void CGameMode::Zc_update_gdid(const char* buf) // line 7076
{
	return (this->*_Zc_update_gdid)(buf);

	PACKET_ZC_UPDATE_GDID& packet = *(PACKET_ZC_UPDATE_GDID*)buf;

	g_guildInfo.m_rightPunish = (packet.right >> 4) & 1;
	g_guildInfo.m_gdid = packet.GDID;
	g_guildInfo.m_rightJoin = packet.right & 1;
	g_guildInfo.m_amIMaster = packet.isMaster;
	m_world->m_player->SetGuildInfo(packet.GDID, packet.emblemVersion);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_update_charstat(SAKEXE, "CGameMode::Zc_update_charstat");
void CGameMode::Zc_update_charstat(const char* buf) // line 7086
{
	return (this->*_Zc_update_charstat)(buf);

	PACKET_ZC_UPDATE_CHARSTAT& packet = *(PACKET_ZC_UPDATE_CHARSTAT*)buf;

	g_guildInfo.GuildInfo::SetMemberInfoState(packet.AID, packet.status);
	const NamePair& names = this->CGameMode::GetActorNameByGID(packet.GID);
	if( names.cName.size() != 0 )
		this->SendMsg(153, (int)names.cName.c_str(), packet.status, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_update_charstat2(SAKEXE, "CGameMode::Zc_update_charstat2");
void CGameMode::Zc_update_charstat2(const char* buf) // line 7100
{
	return (this->*_Zc_update_charstat2)(buf);

	PACKET_ZC_UPDATE_CHARSTAT2& packet = *(PACKET_ZC_UPDATE_CHARSTAT2*)buf;

	g_guildInfo.GuildInfo::SetMemberInfoState2(packet.AID, packet.status, packet.GID, packet.sex, packet.head, packet.headPalette);
	const NamePair& names = this->CGameMode::GetActorNameByGID(packet.GID);
	if( names.cName.size() != 0 )
		this->SendMsg(153, (int)names.cName.c_str(), packet.status, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_give_manner_point(SAKEXE, "CGameMode::Zc_ack_give_manner_point");
void CGameMode::Zc_ack_give_manner_point(const char* buf) // line 7120
{
	return (this->*_Zc_ack_give_manner_point)(buf);

	;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_notify_manner_point_given(SAKEXE, "CGameMode::Zc_notify_manner_point_given");
void CGameMode::Zc_notify_manner_point_given(const char* buf) // line 7123
{
	return (this->*_Zc_notify_manner_point_given)(buf);

	PACKET_ZC_NOTIFY_MANNER_POINT_GIVEN& packet = *(PACKET_ZC_NOTIFY_MANNER_POINT_GIVEN*)buf;

	char charName[24+1];
	memcpy(charName, packet.otherCharName, sizeof(packet.otherCharName));
	charName[sizeof(charName)-1] = '\0';

	if( packet.type == 0 )
	{
		char msg[128];
		sprintf(msg, MsgStr(MSI_RECEIVE_PLUS_MANNER_POINT), charName);
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)msg, 0xFFFF00, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_guild_notice(SAKEXE, "CGameMode::Zc_guild_notice");
void CGameMode::Zc_guild_notice(const char* buf) // line 7147
{
	return (this->*_Zc_guild_notice)(buf);

	PACKET_ZC_GUILD_NOTICE& packet = *(PACKET_ZC_GUILD_NOTICE*)buf;

	packet.notice[countof(packet.notice)-1] = '\0';
	packet.subject[countof(packet.subject)-1] = '\0';

	g_guildInfo.m_subjectName = packet.subject;
	g_guildInfo.m_noticeName = packet.notice;

	mystd::string subject;
	subject += "[ ";
	subject += packet.subject;
	subject += " ]";
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)subject.c_str(), 0x80FFFF, 0);

	mystd::string notice;
	notice += "[ ";
	notice += packet.notice;
	notice += " ]";
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)notice.c_str(), 0x80FFFF, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_guild_chat(SAKEXE, "CGameMode::Zc_guild_chat");
void CGameMode::Zc_guild_chat(const char* buf) // line 7167
{
	return (this->*_Zc_guild_chat)(buf);

	PACKET_ZC_GUILD_CHAT& packet = *(PACKET_ZC_GUILD_CHAT*)buf;
	size_t size = packet.PacketLength - sizeof(packet); //FIXME: no size cap/check

	char guildChat[2048];
	memcpy(guildChat, packet.Text, size);
	guildChat[size-1] = '\0';
	guildChat[sizeof(guildChat)-1] = '\0';

	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)guildChat, 0xB4FFB4, 0);
	if( g_session.m_isSaveChat != 0 )
		this->CGameMode::WriteChat(guildChat);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_req_ally_guild(SAKEXE, "CGameMode::Zc_req_ally_guild");
void CGameMode::Zc_req_ally_guild(const char* buf) // line 7184
{
	return (this->*_Zc_req_ally_guild)(buf);

	PACKET_ZC_REQ_ALLY_GUILD& packet = *(PACKET_ZC_REQ_ALLY_GUILD*)buf;

	char guildName[24+1];
	memcpy(guildName, packet.guildName, sizeof(packet.guildName));
	guildName[sizeof(guildName)-1] = '\0';

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_ALLYGUILDACCEPTWND);
	wnd->SendMsg(0, 74, packet.otherAID, (int)guildName, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_ally_guild(SAKEXE, "CGameMode::Zc_ack_req_ally_guild");
void CGameMode::Zc_ack_req_ally_guild(const char* buf) // line 7195
{
	return (this->*_Zc_ack_req_ally_guild)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_change_guild_positioninfo(SAKEXE, "CGameMode::Zc_ack_change_guild_positioninfo");
void CGameMode::Zc_ack_change_guild_positioninfo(const char* buf) // line 7218
{
	return (this->*_Zc_ack_change_guild_positioninfo)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_itemidentify_list(SAKEXE, "CGameMode::Zc_itemidentify_list");
void CGameMode::Zc_itemidentify_list(const char* buf) // line 7248
{
	return (this->*_Zc_itemidentify_list)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_itemidentify(SAKEXE, "CGameMode::Zc_ack_itemidentify");
void CGameMode::Zc_ack_itemidentify(const char* buf) // line 7271
{
	return (this->*_Zc_ack_itemidentify)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_itemcomposition_list(SAKEXE, "CGameMode::Zc_itemcomposition_list");
void CGameMode::Zc_itemcomposition_list(const char* buf) // line 7289
{
	return (this->*_Zc_itemcomposition_list)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_itemcomposition(SAKEXE, "CGameMode::Zc_ack_itemcomposition");
void CGameMode::Zc_ack_itemcomposition(const char* buf) // line 7311
{
	return (this->*_Zc_ack_itemcomposition)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_hostile_guild(SAKEXE, "CGameMode::Zc_ack_req_hostile_guild");
void CGameMode::Zc_ack_req_hostile_guild(const char* buf) // line 7343
{
	return (this->*_Zc_ack_req_hostile_guild)(buf);

	PACKET_ZC_ACK_REQ_HOSTILE_GUILD& packet = *(PACKET_ZC_ACK_REQ_HOSTILE_GUILD*)buf;

	if( packet.result == 0 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_HOSTILE_GUILD_SUCCEESS), 0xFFFF00, 0);
	}
	else
	if( packet.result == 1 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_TOO_MANY_HOSTILE_GUILD), 0x0000FF, 0);
	}
	else
	if( packet.result == 2 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_ALREADY_REGISTERED_HOSTILE_GUILD), 0x0000FF, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_member_add(SAKEXE, "CGameMode::Zc_member_add");
void CGameMode::Zc_member_add(const char* buf) // line 7359
{
	return (this->*_Zc_member_add)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_delete_related_guild(SAKEXE, "CGameMode::Zc_delete_related_guild");
void CGameMode::Zc_delete_related_guild(const char* buf) // line 7396
{
	return (this->*_Zc_delete_related_guild)(buf);

	PACKET_ZC_DELETE_RELATED_GUILD& packet = *(PACKET_ZC_DELETE_RELATED_GUILD*)buf;

	if( g_guildInfo.m_isRequestInfo[0] != 0 )
		g_guildInfo.GuildInfo::DeleteRelatedGuild(packet.OpponentGDID, packet.Relation);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_add_related_guild(SAKEXE, "CGameMode::Zc_add_related_guild");
void CGameMode::Zc_add_related_guild(const char* buf) // line 7406
{
	return (this->*_Zc_add_related_guild)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_itemrefining(SAKEXE, "CGameMode::Zc_ack_itemrefining");
void CGameMode::Zc_ack_itemrefining(const char* buf) // line 7425
{
	return (this->*_Zc_ack_itemrefining)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_notify_mapinfo(SAKEXE, "CGameMode::Zc_notify_mapinfo");
void CGameMode::Zc_notify_mapinfo(const char* buf) // line 7445
{
	return (this->*_Zc_notify_mapinfo)(buf);

	PACKET_ZC_NOTIFY_MAPINFO& packet = *(PACKET_ZC_NOTIFY_MAPINFO*)buf;

	if( packet.type == 0 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_IMPOSSIBLE_TELEPORT_AREA), 0x0000FF, 0);
	}
	else
	if( packet.type == 1 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_POSSIBLE_TELEPORT_AREA), 0xFFFF00, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_disconnect(SAKEXE, "CGameMode::Zc_ack_req_disconnect");
void CGameMode::Zc_ack_req_disconnect(const char* buf) // line 7458
{
	return (this->*_Zc_ack_req_disconnect)(buf);

	PACKET_ZC_ACK_REQ_DISCONNECT& packet = *(PACKET_ZC_ACK_REQ_DISCONNECT*)buf;

	if( packet.result == 0 )
	{
		g_connection.CConnection::Disconnect();
		this->SendMsg(MM_QUIT, 0, 0, 0);
	}
	else
	if( packet.result == 1 )
	{
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr(MSI_CANT_EXIT_NOW), 0x0000FF, 0);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_monster_info(SAKEXE, "CGameMode::Zc_monster_info");
void CGameMode::Zc_monster_info(const char* buf) // line 7473
{
	return (this->*_Zc_monster_info)(buf);

	PACKET_ZC_MONSTER_INFO& packet = *(PACKET_ZC_MONSTER_INFO*)buf;

	if( packet.job == JT_ARCHER_GUARDIAN || packet.job == JT_KNIGHT_GUARDIAN || packet.job == JT_SOLDIER_GUARDIAN )
		return;

	UIFrameWnd* wnd = g_windowMgr.UIWindowMgr::MakeWindow(WID_MONSTERINFOWND);
	wnd->SendMsg(NULL, 79, (int)buf, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_makable_item_list(SAKEXE, "CGameMode::Zc_makable_item_list");
void CGameMode::Zc_makable_item_list(const char* buf) // line 7486
{
	return (this->*_Zc_makable_item_list)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ack_req_itemmaking(SAKEXE, "CGameMode::Zc_ack_req_itemmaking");
void CGameMode::Zc_ack_req_itemmaking(const char* buf) // line 7503
{
	return (this->*_Zc_ack_req_itemmaking)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_talkbox_chat_contents(SAKEXE, "CGameMode::Zc_talkbox_chat_contents");
void CGameMode::Zc_talkbox_chat_contents(const char* buf) // line 7543
{
	return (this->*_Zc_talkbox_chat_contents)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_update_mapinfo(SAKEXE, "CGameMode::Zc_update_mapinfo");
void CGameMode::Zc_update_mapinfo(const char* buf) // line 7552
{
	return (this->*_Zc_update_mapinfo)(buf);

	PACKET_ZC_UPDATE_MAPINFO& packet = *(PACKET_ZC_UPDATE_MAPINFO*)buf;
	g_modeMgr.CModeMgr::GetGameMode()->m_world->m_attr->C3dAttr::SetCellInfo(packet.type, packet.xPos, packet.yPos);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Msg_State_Change(SAKEXE, "CGameMode::Zc_Msg_State_Change");
void CGameMode::Zc_Msg_State_Change(const char* buf) // line 7568
{
	return (this->*_Zc_Msg_State_Change)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Mapproperty(SAKEXE, "CGameMode::Zc_Notify_Mapproperty");
void CGameMode::Zc_Notify_Mapproperty(const char* buf) // line 7986
{
	return (this->*_Zc_Notify_Mapproperty)(buf);

	PACKET_ZC_NOTIFY_MAPPROPERTY& packet = *(PACKET_ZC_NOTIFY_MAPPROPERTY*)buf;

	g_session.m_isMinEffect = g_session.m_isMinEffectOld;

	switch( packet.type )
	{
	case 1:
		m_world->CWorld::SetPKZone(TRUE);
	break;
	case 2:
		m_world->CWorld::SetEventPVPMode(TRUE);
	break;
	case 3:
		m_world->CWorld::SetSiegeMode(TRUE);
		g_session.m_isMinEffect = TRUE;
	break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Mapproperty2(SAKEXE, "CGameMode::Zc_Notify_Mapproperty2");
void CGameMode::Zc_Notify_Mapproperty2(const char* buf) // line 8001
{
	return (this->*_Zc_Notify_Mapproperty2)(buf);

	PACKET_ZC_NOTIFY_MAPPROPERTY2& packet = *(PACKET_ZC_NOTIFY_MAPPROPERTY2*)buf;

	g_session.m_isMinEffect = g_session.m_isMinEffectOld;
	g_session.m_curMapType = packet.type;

	if( packet.type == MAPTYPE_PENALTY_FREEPKZONE || packet.type == MAPTYPE_NOPENALTY_FREEPKZONE )
	{
		m_world->CWorld::SetPKZone(TRUE);
	}
	else
	if( g_session.CSession::IsEnableSiegeMode() )
	{
		m_world->CWorld::SetSiegeMode(TRUE);
		g_session.m_isMinEffect = TRUE;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Ranking(SAKEXE, "CGameMode::Zc_Notify_Ranking");
void CGameMode::Zc_Notify_Ranking(const char* buf) // line 8021
{
	return (this->*_Zc_Notify_Ranking)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Effect(SAKEXE, "CGameMode::Zc_Notify_Effect");
void CGameMode::Zc_Notify_Effect(const char* buf) // line 8100
{
	return (this->*_Zc_Notify_Effect)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Effect2(SAKEXE, "CGameMode::Zc_Notify_Effect2");
void CGameMode::Zc_Notify_Effect2(const char* buf) // line 8157
{
	return (this->*_Zc_Notify_Effect2)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Start_Capture(SAKEXE, "CGameMode::Zc_Start_Capture");
void CGameMode::Zc_Start_Capture(const char* buf) // line 8181
{
	return (this->*_Zc_Start_Capture)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Start_Couple(SAKEXE, "CGameMode::Zc_Start_Couple");
void CGameMode::Zc_Start_Couple(const char* buf) // line 8190
{
	return (this->*_Zc_Start_Couple)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Start_Baby(SAKEXE, "CGameMode::Zc_Start_Baby");
void CGameMode::Zc_Start_Baby(const char* buf) // line 8199
{
	return (this->*_Zc_Start_Baby)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_CoupleName(SAKEXE, "CGameMode::Zc_CoupleName");
void CGameMode::Zc_CoupleName(const char* buf) // line 8206
{
	return (this->*_Zc_CoupleName)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Congratulation(SAKEXE, "CGameMode::Zc_Congratulation");
void CGameMode::Zc_Congratulation(const char* buf) // line 8212
{
	return (this->*_Zc_Congratulation)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_TryCapture_Monster(SAKEXE, "CGameMode::Zc_TryCapture_Monster");
void CGameMode::Zc_TryCapture_Monster(const char* buf) // line 8235
{
	return (this->*_Zc_TryCapture_Monster)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Change_Pet_Status(SAKEXE, "CGameMode::Zc_Change_Pet_Status");
void CGameMode::Zc_Change_Pet_Status(const char* buf) // line 8251
{
	return (this->*_Zc_Change_Pet_Status)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_PetEgg_List(SAKEXE, "CGameMode::Zc_PetEgg_List");
void CGameMode::Zc_PetEgg_List(const char* buf) // line 8330
{
	return (this->*_Zc_PetEgg_List)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Property_Pet(SAKEXE, "CGameMode::Zc_Property_Pet");
void CGameMode::Zc_Property_Pet(const char* buf) // line 8350
{
	return (this->*_Zc_Property_Pet)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Feed_Pet(SAKEXE, "CGameMode::Zc_Feed_Pet");
void CGameMode::Zc_Feed_Pet(const char* buf) // line 8380
{
	return (this->*_Zc_Feed_Pet)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Pet_Act(SAKEXE, "CGameMode::Zc_Pet_Act");
void CGameMode::Zc_Pet_Act(const char* buf) // line 8403
{
	return (this->*_Zc_Pet_Act)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Par_Change_User(SAKEXE, "CGameMode::Zc_Par_Change_User");
void CGameMode::Zc_Par_Change_User(const char* buf) // line 8462-8476
{
	return (this->*_Zc_Par_Change_User)(buf);

	PACKET_ZC_PAR_CHANGE_USER& packet = *(PACKET_ZC_PAR_CHANGE_USER*)buf;
	unsigned long AID = packet.AID;
	short type = packet.varID;
	int value = packet.count;

	CGameActor* other = m_world->CWorld::GetGameActorByAID(AID);
	if( other == NULL )
		return; // user not found

	switch( type )
	{
	case 0x4: // VAR_HONOR
		other->SetHonor(value);
	break;
	default:
	break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Update(SAKEXE, "CGameMode::Zc_Skill_Update");
void CGameMode::Zc_Skill_Update(const char* buf) // line 8479
{
	return (this->*_Zc_Skill_Update)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_MakingArrowList(SAKEXE, "CGameMode::Zc_MakingArrowList");
void CGameMode::Zc_MakingArrowList(const char* buf) // line 8505
{
	return (this->*_Zc_MakingArrowList)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ChangeCartList(SAKEXE, "CGameMode::Zc_ChangeCartList");
void CGameMode::Zc_ChangeCartList(const char* buf) // line 8522
{
	return (this->*_Zc_ChangeCartList)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_NpcSpriteChange(SAKEXE, "CGameMode::Zc_NpcSpriteChange");
void CGameMode::Zc_NpcSpriteChange(const char* buf) // line 8527
{
	return (this->*_Zc_NpcSpriteChange)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ShowDigit(SAKEXE, "CGameMode::Zc_ShowDigit");
void CGameMode::Zc_ShowDigit(const char* buf) // line 8542
{
	return (this->*_Zc_ShowDigit)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ChangeGuild(SAKEXE, "CGameMode::Zc_ChangeGuild");
void CGameMode::Zc_ChangeGuild(const char* buf) // line 8567
{
	return (this->*_Zc_ChangeGuild)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_GuildInfo2(SAKEXE, "CGameMode::Zc_GuildInfo2");
void CGameMode::Zc_GuildInfo2(const char* buf) // line 8576
{
	return (this->*_Zc_GuildInfo2)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_GuildZenyAck(SAKEXE, "CGameMode::Zc_GuildZenyAck");
void CGameMode::Zc_GuildZenyAck(const char* buf) // line 8618
{
	return (this->*_Zc_GuildZenyAck)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Dispel(SAKEXE, "CGameMode::Zc_Dispel");
void CGameMode::Zc_Dispel(const char* buf) // line 8643
{
	return (this->*_Zc_Dispel)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Reply_RemainTime(SAKEXE, "CGameMode::Zc_Reply_RemainTime");
void CGameMode::Zc_Reply_RemainTime(const char* buf) // line 8663
{
	return (this->*_Zc_Reply_RemainTime)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Info_RemainTime(SAKEXE, "CGameMode::Zc_Info_RemainTime");
void CGameMode::Zc_Info_RemainTime(const char* buf) // line 8700
{
	return (this->*_Zc_Info_RemainTime)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Broadcast2(SAKEXE, "CGameMode::Zc_Broadcast2");
void CGameMode::Zc_Broadcast2(const char* buf) // line 8729
{
	return (this->*_Zc_Broadcast2)(buf);

	PACKET_ZC_BROADCAST2& packet = *(PACKET_ZC_BROADCAST2*)buf;

	char chatMsg[255+1];
	memcpy(chatMsg, packet.Text, packet.PacketLength - sizeof(packet));
	int len = strlen(chatMsg);

	mystd::string wMsg = chatMsg;

	//NOTE: this is used to skip the hidden part of npc names in npc broadcasts
	int subStrSize1 = wMsg.find('#'); // skip block start
	int subStrSize2 = wMsg.find(':'); // skip block end

	if( subStrSize1 > 0 && subStrSize1 < len )
	{// text contains skip block
		char temp[256];
		memcpy(temp, chatMsg, subStrSize1);
		temp[subStrSize1] = '\0';
		wMsg = temp;

		if( subStrSize2 > 0 && subStrSize2 < len )
		{
			char temp2[256];
			memcpy(temp2, &chatMsg[subStrSize2], len - subStrSize2 + 1);
			if( strlen(temp2) != 0 )
				wMsg.append(temp2);
		}
	}

	m_broadCastTick = timeGetTime();

	if( m_broadcastBalloon == NULL )
	{
		m_broadcastBalloon = new UITransBalloonText();
		m_broadcastBalloon->UIWindow::Create(8, 8);
		g_windowMgr.UIWindowMgr::AddWindowFront(m_broadcastBalloon);
	}

	m_broadcastBalloon->UIBalloonText::SetText(wMsg.c_str(), 72);
	m_broadcastBalloon->UIBalloonText::SetFntSize(packet.fontSize);
	m_broadcastBalloon->Move(320 + (g_renderer->CRenderer::GetWidth() - 640) / 2 - m_broadcastBalloon->UIWindow::GetWidth() / 2, 51);

	BYTE r = BYTE(packet.fontColor >> 16);
	BYTE g = BYTE(packet.fontColor >>  8);
	BYTE b = BYTE(packet.fontColor >>  0);
	COLORREF color = RGB(r, g, b);

	m_broadcastBalloon->UIBalloonText::SetFntColor(color, 0x000000); // inlined
	g_windowMgr.UIWindowMgr::SendMsg(UIM_OPENCHATWND, 0, 0, 0);
	g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)wMsg.c_str(), (int)color, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_GuildSkillInfo(SAKEXE, "CGameMode::Zc_GuildSkillInfo");
void CGameMode::Zc_GuildSkillInfo(const char* buf) // line 8771
{
	return (this->*_Zc_GuildSkillInfo)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_AddItemToStore2(SAKEXE, "CGameMode::Zc_AddItemToStore2");
void CGameMode::Zc_AddItemToStore2(const char* buf) // line 8800
{
	return (this->*_Zc_AddItemToStore2)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Add_Item_To_Cart2(SAKEXE, "CGameMode::Zc_Add_Item_To_Cart2");
void CGameMode::Zc_Add_Item_To_Cart2(const char* buf) // line 8821
{
	return (this->*_Zc_Add_Item_To_Cart2)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Sc_Ack_Encryption(SAKEXE, "CGameMode::Sc_Ack_Encryption");
void CGameMode::Sc_Ack_Encryption(const char* buf) // line 8844
{
	return (this->*_Sc_Ack_Encryption)(buf);

	ErrorMsg("No Packet Encryption !!!");
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Use_Item_Ack2(SAKEXE, "CGameMode::Zc_Use_Item_Ack2");
void CGameMode::Zc_Use_Item_Ack2(const char* buf) // line 8848
{
	return (this->*_Zc_Use_Item_Ack2)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Skill_Entry2(SAKEXE, "CGameMode::Zc_Skill_Entry2");
void CGameMode::Zc_Skill_Entry2(const char* buf) // line 8871
{
	return (this->*_Zc_Skill_Entry2)(buf);

	PACKET_ZC_SKILL_ENTRY2& packet = *(PACKET_ZC_SKILL_ENTRY2*)buf;

	SKILLSTANDENTRYSTRUCT s;
	s.AID = packet.AID;
	s.creatorAID = packet.creatorAID;
	s.job = packet.job;
	s.xPos = packet.xPos;
	s.yPos = packet.yPos;
	s.isVisible = true;
	packet.isVisible = true;

	if( packet.isContens == 1 )
	{
		CGraffiSkill* skill = new CGraffiSkill();
		m_world->m_gameObjectList.push_back(skill);
		m_world->m_skillList.push_back(skill);
		skill->SendMsg(NULL, 22, packet.AID, 0, 0);
		skill->SendMsg(NULL, 117, (int)packet.msg, packet.xPos, packet.yPos);
		return;
	}

	CSkill* skill = m_world->CWorld::GetSkillByAID(packet.AID);

	if( s.creatorAID != g_session.CSession::GetAid() )
	{
		for( mystd::list<unsigned long>::iterator it = m_visibleTrapList.begin(); it != m_visibleTrapList.end(); ++it )
		{
			if( *it == packet.AID )
			{
				m_visibleTrapList.erase(it);
				s.isVisible = false;
				packet.isVisible = false;
				break;
			}
		}
	}

	if( s.isVisible )
		m_visibleTrapList.push_back(packet.AID);

	if( skill == NULL )
	{
		if( packet.job >= JT_WARPNPC && packet.job <= JT_2004_JOB_BEGIN )
		{
			skill = new CSkill();
			m_world->m_gameObjectList.push_back(skill);
			m_world->m_skillList.push_back(skill);
		}
	}

	if( skill != NULL )
		skill->SendMsg(NULL, 45, (int)&s, 0, 0);
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Monster_Talk(SAKEXE, "CGameMode::Zc_Monster_Talk");
void CGameMode::Zc_Monster_Talk(const char* buf) // line 8938
{
	return (this->*_Zc_Monster_Talk)(buf);

	;
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_AutoSpellList(SAKEXE, "CGameMode::Zc_AutoSpellList");
void CGameMode::Zc_AutoSpellList(const char* buf) // line 8955
{
	return (this->*_Zc_AutoSpellList)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_DevotionList(SAKEXE, "CGameMode::Zc_DevotionList");
void CGameMode::Zc_DevotionList(const char* buf) // line 8984
{
	return (this->*_Zc_DevotionList)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Spirits(SAKEXE, "CGameMode::Zc_Spirits");
void CGameMode::Zc_Spirits(const char* buf) // line 9041
{
	return (this->*_Zc_Spirits)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Spirits2(SAKEXE, "CGameMode::Zc_Spirits2");
void CGameMode::Zc_Spirits2(const char* buf) // line 9082
{
	return (this->*_Zc_Spirits2)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_BladeStop(SAKEXE, "CGameMode::Zc_BladeStop");
void CGameMode::Zc_BladeStop(const char* buf) // line 9118
{
	return (this->*_Zc_BladeStop)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Open_EditDlgStr(SAKEXE, "CGameMode::Zc_Open_EditDlgStr");
void CGameMode::Zc_Open_EditDlgStr(const char* buf) // line 9160
{
	return (this->*_Zc_Open_EditDlgStr)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Sound(SAKEXE, "CGameMode::Zc_Sound");
void CGameMode::Zc_Sound(const char* buf) // line 9169
{
	return (this->*_Zc_Sound)(buf);

	//TODO
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_ComboDelay(SAKEXE, "CGameMode::Zc_ComboDelay");
void CGameMode::Zc_ComboDelay(const char* buf) // line 9212
{
	return (this->*_Zc_ComboDelay)(buf);

	PACKET_ZC_COMBODELAY& packet = *(PACKET_ZC_COMBODELAY*)buf;

	g_session.CSession::SetForceAnimEndTick(packet.AID, packet.delayTime);

	if( packet.AID == g_session.CSession::GetAid() )
	{
		m_world->m_player->CRenderObject::SetForceAnimEndTick(packet.delayTime);
	}
	else
	{
		CRenderObject* actor = m_world->CWorld::GetGameActorByAID(packet.AID);
		if( actor != NULL )
			actor->CRenderObject::SetForceAnimEndTick(packet.delayTime);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Sprite_Change2(SAKEXE, "CGameMode::Zc_Sprite_Change2");
void CGameMode::Zc_Sprite_Change2(const char* buf) // line 9229
{
	return (this->*_Zc_Sprite_Change2)(buf);

	PACKET_ZC_SPRITE_CHANGE2& packet = *(PACKET_ZC_SPRITE_CHANGE2*)buf;

	CGameActor* actor;

	if( packet.GID == g_session.CSession::GetAid() )
	{
		actor = m_world->m_player;

		switch( packet.type )
		{
		case SPRITETYPE_JOB:
			g_session.CSession::SetJob(packet.value);
			g_session.CSession::InvalidateUI();
			g_session.CSession::InvalidateJob();
		break;
		case SPRITETYPE_HEAD:
			g_session.m_head = packet.value;
		break;
		case SPRITETYPE_WEAPON:
		{
			int left = HIWORD(packet.value);
			int right = LOWORD(packet.value);
			int type = g_session.CSession::GetWeaponType(left);

			if( right != 0 && type == -1 )
			{// shield in left hand
				g_session.m_shield = left;
				g_session.m_weapon = right | (left << 16);
				packet.value = g_session.m_weapon;
			}
			else
			{// dual-wielded weapons
				g_session.m_weapon = packet.value;
			}
		}
		break;
		case SPRITETYPE_ACCESSORY:
			g_session.m_accessory = packet.value;
		break;
		case SPRITETYPE_HEADPALETTE:
			g_session.m_headPalette = packet.value;
		break;
		case SPRITETYPE_BODYPALATTE:
			g_session.m_bodyPalette = packet.value;
		break;
		case SPRITETYPE_ACCESSORY2:
			g_session.m_accessory2 = packet.value;
		break;
		case SPRITETYPE_ACCESSORY3:
			g_session.m_accessory3 = packet.value;
		break;
		default:
		break;
		}

		if( actor == NULL )
			return;
	}
	else
	{
		actor = m_world->CWorld::GetGameActorByAID(packet.GID);
		if( actor == NULL )
		{
			CSkill* skill = m_world->CWorld::GetSkillByAID(packet.GID);
			if( skill != NULL && packet.type == 0 )
				skill->SendMsg(NULL, 47, packet.value, 0, 0);

			return;
		}
	}

	switch( packet.type )
	{
	case SPRITETYPE_JOB:
		actor->CGameActor::SetJob(packet.value);
		actor->SetImfFileName();
		actor->SetHeadPaletteName();
		actor->SetHeadPaletteName();
	break;
	case SPRITETYPE_HEAD:
		actor->SetSprHead(packet.value);
		actor->SetImfFileName();
		actor->SetHeadPaletteName();
	break;
	case SPRITETYPE_WEAPON:
	{
		int left = HIWORD(packet.value);
		int right = LOWORD(packet.value);
		int type = g_session.CSession::GetWeaponType(left);

		if( actor->CGameActor::GetJob() == JT_ASSASSIN || actor->CGameActor::GetJob() == JT_ASSASSIN_H || actor->CGameActor::GetJob() == JT_ASSASSIN_B )
			right = packet.value;

		actor->SetSprWeapon2(right);
		if( type == -1 || left == 0 )
			actor->SetSprShield(left);
	}
	break;
	case SPRITETYPE_ACCESSORY:
		actor->SetSprAccessory(packet.value);
	break;
	case SPRITETYPE_HEADPALETTE:
		actor->SetHeadPalette(packet.value);
	break;
	case SPRITETYPE_BODYPALATTE:
		actor->SetBodyPalette(packet.value);
	break;
	case SPRITETYPE_ACCESSORY2:
		actor->SetSprAccessory2(packet.value);
	break;
	case SPRITETYPE_ACCESSORY3:
		actor->SetSprAccessory3(packet.value);
	break;
	case SPRITETYPE_SHOE:
		actor->SetSprShoe(packet.value);
	break;
	default:
	break;
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Newentry2(SAKEXE, "CGameMode::Zc_Notify_Newentry2");
void CGameMode::Zc_Notify_Newentry2(const char* buf) // line 9355-9492
{
	return (this->*_Zc_Notify_Newentry2)(buf);

	PACKET_ZC_NOTIFY_NEWENTRY2& packet = *(PACKET_ZC_NOTIFY_NEWENTRY2*)buf;

	STANDENTRYSTRUCT s;
	s.GID = packet.GID;
	s.job = packet.job;
	s.sex = packet.sex;
	s.speed = packet.speed;
	s.xSize = packet.xSize;
	s.ySize = packet.ySize;
	s.head = packet.head;
	s.weapon = packet.weapon;
	s.accessory = packet.accessory;
	s.healthState = packet.healthState;
	s.bodyState = packet.bodyState;
	s.effectState = packet.effectState;
	s.isPKModeON = packet.isPKModeON;
	s.shield = 0;
	s.accessory2 = packet.accessory2;
	s.accessory3 = packet.accessory3;
	s.bodypalette = packet.bodypalette;
	s.headpalette = packet.headpalette;
	s.headDir = packet.headDir;
	s.guildId = packet.GUID;
	s.guildEmblemVersion = packet.GEmblemVer;
	s.honor = packet.honor;
	s.virtue = packet.virtue;
	s.state = 0;
	DecodePosDir(packet.PosDir, s.x, s.y, s.dir);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor == NULL )
	{
		bool isPc = false;

		if( packet.job < JT_WARPNPC || packet.job > JT_2004_JOB_BEGIN )
		{
			isPc = true;
			actor = new CPc();
		}
		else
		{
			actor = this->CGameMode::NewNpc(packet.job);
			s.sex = SEX_FEMALE;
		}

		if( actor != NULL && s.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		m_world->m_gameObjectList.push_back(actor);
		m_world->m_actorList.push_back(actor);

		actor->SendMsg(NULL, 121, (int)&s, 2, 0);

		if( isPc && !IsGravityAid(packet.GID) && !IsEffectStateSpecialHiding(packet.effectState) )
			actor->CAbleToMakeEffect::LaunchEffect(344, vector3d(0.,0.,0.), 0.0);

		if( g_session.CSession::IsSiegeMode() && s.head != 20 && actor->m_emblemWnd == NULL )
		{
			if( g_session.CSession::IsPc(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
			else
			if( g_session.CSession::IsGuardian(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
		}
	}
	else
	{
		if( s.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		actor->SendMsg(NULL, 124, (int)&s, 0, 0);

		if( g_session.CSession::IsSiegeMode() && s.head != 20 && actor->m_emblemWnd == NULL )
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


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Standentry2(SAKEXE, "CGameMode::Zc_Notify_Standentry2");
void CGameMode::Zc_Notify_Standentry2(const char* buf) // line 9496
{
	return (this->*_Zc_Notify_Standentry2)(buf);

	PACKET_ZC_NOTIFY_STANDENTRY2& packet = *(PACKET_ZC_NOTIFY_STANDENTRY2*)buf;

	STANDENTRYSTRUCT s;
	s.GID = packet.GID;
	s.job = packet.job;
	s.sex = packet.sex;
	s.speed = packet.speed;
	s.xSize = packet.xSize;
	s.ySize = packet.ySize;
	s.head = packet.head;
	s.weapon = packet.weapon;
	s.accessory = packet.accessory;
	s.state = packet.state;
	s.healthState = packet.healthState;
	s.bodyState = packet.bodyState;
	s.effectState = packet.effectState;
	s.isPKModeON = packet.isPKModeON;
	s.accessory2 = packet.accessory2;
	s.accessory3 = packet.accessory3;
	s.headpalette = packet.headpalette;
	s.bodypalette = packet.bodypalette;
	s.headDir = packet.headDir;
	s.guildId = packet.GUID;
	s.guildEmblemVersion = packet.GEmblemVer;
	s.honor = packet.honor;
	s.virtue = packet.virtue;
	DecodePosDir(packet.PosDir, s.x, s.y, s.dir);
	s.shield = 0;

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor == NULL )
	{
		CGameActor* newGameActor;

		if( packet.job < JT_WARPNPC || packet.job > JT_2004_JOB_BEGIN )
		{
			newGameActor = new CPc();
		}
		else
		{
			newGameActor = this->CGameMode::NewNpc(packet.job);
			s.sex = 0;
		}

		if ( newGameActor != NULL && s.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				newGameActor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		m_world->m_gameObjectList.push_back(newGameActor);
		m_world->m_actorList.push_back(newGameActor);

		if( newGameActor != NULL )
		{
			newGameActor->SendMsg(NULL, 121, (int)&s, 0, 0);
			
			if( g_session.CSession::IsSiegeMode() && s.head != 20 && newGameActor->m_emblemWnd == NULL )
			{
				if( g_session.CSession::IsPc(newGameActor->CGameActor::GetJob()) )
					this->CGameMode::MakeEmblemWnd(newGameActor, packet.GUID, packet.GEmblemVer);
				else
				if( g_session.CSession::IsGuardian(newGameActor->CGameActor::GetJob()) )
					this->CGameMode::MakeEmblemWnd(newGameActor, packet.GUID, packet.GEmblemVer);
			}
		}
	}
	else
	{
		if( s.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = s.accessory;

			if( s.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(s.accessory));
		}

		actor->SendMsg(NULL, 124, (int)&s, 0, 0);

		if( g_session.CSession::IsSiegeMode() && s.head != 20 && actor->m_emblemWnd == NULL )
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


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Moveentry2(SAKEXE, "CGameMode::Zc_Notify_Moveentry2");
void CGameMode::Zc_Notify_Moveentry2(const char* buf) // line 9628-9770
{
	return (this->*_Zc_Notify_Moveentry2)(buf);

	PACKET_ZC_NOTIFY_MOVEENTRY2& packet = *(PACKET_ZC_NOTIFY_MOVEENTRY2*)buf;

	MOVEENTRYSTRUCT ms;
	ms.GID = packet.GID;
	ms.job = packet.job;
	ms.sex = packet.sex;
	ms.speed = packet.speed;
	ms.head = packet.head;
	ms.weapon = packet.weapon;
	ms.accessory = packet.accessory;
	ms.healthState = packet.healthState;
	ms.bodyState = packet.bodyState;
	ms.effectState = packet.effectState;
	ms.accessory2 = packet.accessory2;
	ms.isPKModeON = packet.isPKModeON;
	ms.headpalette = packet.headpalette;
	ms.accessory3 = packet.accessory3;
	ms.headDir = packet.headDir;
	ms.bodypalette = packet.bodypalette;
	ms.guildId = packet.GUID;
	ms.guildEmblemVersion = packet.GEmblemVer;
	ms.honor = packet.honor;
	ms.virtue = packet.virtue;
	ms.moveStartTime = packet.moveStartTime;
	DecodeSrcDst(packet.MoveData, ms.sx, ms.sy, ms.dx, ms.dy, ms.cellX, ms.cellY);

	g_session.CSession::UpdateServerTime(packet.moveStartTime);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(packet.GID);
	if( actor == NULL )
	{
		if( packet.job < JT_WARPNPC || packet.job >= JT_2004_JOB_BEGIN )
		{
			actor = new CPc();
		}
		else
		{
			actor = this->CGameMode::NewNpc(packet.job);
			ms.sex = SEX_FEMALE;
		}

		if( actor != NULL && ms.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = ms.accessory;

			if( ms.accessory != 0 )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(ms.accessory));
		}

		m_world->m_gameObjectList.push_back(actor);
		m_world->m_actorList.push_back(actor);

		actor->SendMsg(NULL, 122, (int)&ms, 0, 0);

		if( g_session.CSession::IsSiegeMode() && ms.head != 20 && actor->m_emblemWnd == NULL )
		{
			if( g_session.CSession::IsPc(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
			else
			if( g_session.CSession::IsGuardian(actor->CGameActor::GetJob()) )
				this->CGameMode::MakeEmblemWnd(actor, packet.GUID, packet.GEmblemVer);
		}
	}
	else
	{
		actor->SendMsg(NULL, 123, (int)&ms, 0, 0);

		if( ms.head == 20 )
		{
			if( g_session.m_petGID == packet.GID )
				g_session.m_petAcc = ms.accessory;

			if( ms.accessory != 0 && !actor->GetGdid() )
				actor->CRenderObject::SetActName(g_session.CSession::GetPetAccActName(ms.accessory));
		}

		if( g_session.CSession::IsSiegeMode() && ms.head != 20 && actor->m_emblemWnd == NULL )
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


hook_method<void (CGameMode::*)(int GID, int effectState, int clevel, int showEFST)> CGameMode::_GameModeShowEFST(SAKEXE, "CGameMode::GameModeShowEFST");
void CGameMode::GameModeShowEFST(int GID, int effectState, int clevel, int showEFST) // line 9774
{
	return (this->*_GameModeShowEFST)(GID, effectState, clevel, showEFST);

	CGameActor* actor = m_world->CWorld::GetGameActorByAID(GID);
	if( actor == NULL )
		return;

	if( clevel == 99 && !IsEffectStateSpecialHiding(effectState) )
		actor->SendMsg(NULL, 125, 0, 0, 0);

	if( showEFST & SHOW_EFST_QUICKEN )
	{
		if( !actor->CAbleToMakeEffect::IsEffectExist(166) )
		{
			CRagEffect* effect = actor->CAbleToMakeEffect::LaunchEffect(166, vector3d(0.,0.,0.), 0.0);
			if( effect != NULL )
				effect->SendMsg(NULL, 44, 0x0000FFFF, 130, 0);
		}
	}
	else
	if( showEFST & SHOW_EFST_OVERTHRUST )
	{
		if( !actor->CAbleToMakeEffect::IsEffectExist(166) )
		{
			CRagEffect* effect = actor->CAbleToMakeEffect::LaunchEffect(166, vector3d(0.,0.,0.), 0.0);
			if( effect != NULL )
				effect->SendMsg(NULL, 44, 0x0000FFFF, 128, 0);
		}
	}
	else
	if( showEFST & SHOW_EFST_ENERGYCOAT )
	{
		if( !actor->CAbleToMakeEffect::IsEffectExist(166) )
		{
			CRagEffect* effect = actor->CAbleToMakeEffect::LaunchEffect(166, vector3d(0.,0.,0.), 0.0);
			if( effect != NULL )
				effect->SendMsg(NULL, 44, 0x0000FFFF, 169, 0);
		}
	}

	if( showEFST & SHOW_EFST_EXPLOSIONSPIRITS )
		if( !actor->CAbleToMakeEffect::IsEffectExist(203) )
			actor->CAbleToMakeEffect::LaunchEffect(203, vector3d(0.,0.,0.), 0.0);

	if( showEFST & SHOW_EFST_STEELBODY )
		if( !actor->CAbleToMakeEffect::IsEffectExist(254) )
			actor->CAbleToMakeEffect::LaunchEffect(254, vector3d(0.,0.,0.), 0.0);

	if( showEFST & SHOW_EFST_AURABLADE )
		if( !actor->CAbleToMakeEffect::IsEffectExist(367) )
			actor->CAbleToMakeEffect::LaunchEffect(367, vector3d(0.,0.,0.), 0.0);

	if( showEFST & SHOW_EFST_LIGHTBLADE )
		if( !actor->CAbleToMakeEffect::IsEffectExist(382) )
			actor->CAbleToMakeEffect::LaunchEffect(382, vector3d(0.,0.,0.), 0.0);

	if( showEFST & SHOW_EFST_REDBODY )
		if( !actor->CAbleToMakeEffect::IsEffectExist(368) )
			actor->CAbleToMakeEffect::LaunchEffect(368, vector3d(0.,0.,0.), 0.0);

	if( showEFST & SHOW_EFST_MOON )
		if( !actor->CAbleToMakeEffect::IsEffectExist(394) )
			actor->CAbleToMakeEffect::LaunchEffect(394, vector3d(0.,0.,0.), 0.0);

	if( showEFST & SHOW_EFST_PINKBODY )
		if( !actor->CAbleToMakeEffect::IsEffectExist(396) )
			actor->CAbleToMakeEffect::LaunchEffect(396, vector3d(0.,0.,0.), 0.0);

	if( showEFST & SHOW_EFST_BLADESTOP )
	{
		if( actor->CGameActor::GetJob() == JT_MONK || actor->CGameActor::GetJob() == JT_MONK_H || actor->CGameActor::GetJob() == JT_MONK_B )
			actor->CRenderObject::SetForceAnimation(96, 4, 4, 96, 4, 1, 0x5F5E0FFu, 0);
		else
			actor->m_isMotionFreezed = true;

		actor->m_isSprArgbFixed = true;
		actor->CRenderObject::SetArgb(-1, 0x40, 0x40, 0x40);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Notify_Skill2(SAKEXE, "CGameMode::Zc_Notify_Skill2");
void CGameMode::Zc_Notify_Skill2(const char* buf) // line 9898
{
	return (this->*_Zc_Notify_Skill2)(buf);

	PACKET_ZC_NOTIFY_SKILL2& packet = *(PACKET_ZC_NOTIFY_SKILL2*)buf;

	SKILLSTRUCT skill;
	skill.skillId = packet.SKID;
	skill.action = packet.action;
	skill.startTime = packet.startTime;
	skill.damage = packet.damage;
	skill.targetGID = packet.targetID;
	skill.count = packet.count;
	skill.attackMT = packet.attackMT;
	skill.tCellX = -1;
	skill.tCellY = -1;
	skill.level = packet.level;
	skill.attackedMT = packet.attackedMT;

	CGameActor* actor = NULL;
	int job = -1;

	if( packet.AID == g_session.CSession::GetAid() )
	{
		m_world->m_player->SendMsg(NULL, 37, (int)&skill, 0, 0);
		actor = m_world->m_player;
		job = actor->CGameActor::GetJob();
	}
	else
	{
		actor = m_world->CWorld::GetGameActorByAID(packet.AID);
		if( actor != NULL )
		{
			actor->SendMsg(NULL, 37, (int)&skill, 0, 0);
			job = actor->CGameActor::GetJob();
		}
		else
		{
			CSkill* skill = m_world->CWorld::GetSkillByAID(packet.AID);
			if( skill != NULL )
				skill->SendMsg(NULL, 37, (int)&skill, 0, 0);
		}
	}

	if( g_session.CSession::IsMonster(job) )
	{
		int act;
		int loopType;
		g_session.CSession::GetMonsterSkillInfo((char*)g_session.m_jobNameTable[job], skill.skillId, act, loopType);

		if( act != -1 )
		{
			if( actor != NULL )
				actor->SetAction(8 * act - 8, 1, (loopType == 0));
		}
	}
	else
	{
		this->SendMsg(99, packet.SKID, (int)actor, packet.level);
	}
}


hook_method<void (CGameMode::*)(const char* buf)> CGameMode::_Zc_Ack_AccountName(SAKEXE, "CGameMode::Zc_Ack_AccountName");
void CGameMode::Zc_Ack_AccountName(const char* buf) // line 9969
{
	return (this->*_Zc_Ack_AccountName)(buf);

	PACKET_ZC_ACK_ACCOUNTNAME& packet = *(PACKET_ZC_ACK_ACCOUNTNAME*)buf;

	REQ_ACCOUNT_AID accAID;
	accAID.AID = packet.AID;
	accAID.accountName = packet.name;

	g_session.m_recievedAccountName.push_back(accAID);
	g_session.CSession::DeleteAssignAID(packet.AID);
}
