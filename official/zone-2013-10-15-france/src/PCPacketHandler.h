#pragma once
#include "Common/Packet.h"
#include "GameGuard/CSAuth.h"
#include "NetLib/PacketHandler.h"
class CPC;


class CPCPacketHandler : public CPacketHandler
{
public:
	CPCPacketHandler();
	virtual ~CPCPacketHandler();

public:
	virtual void OnRecvOverflow(int byteTransferred);
	virtual void OnRecv(int byteTransferred);
	virtual void OnClose();
	virtual int OnProcess();
	void SetMyOwner(CPC* pc);
	virtual void AddSendBytes(int len);
	void Init();
	void OnBroadCast(int len);
	void OnMove(PACKET_CZ_REQUEST_MOVE* move_req);
	BOOL StartPath(const unsigned char in_dest[3], const DWORD in_startTime);
	void LockOnAttack();
	void RequestSit();
	void CounterAttack(unsigned long targetID);
	void OnSit();
	void UseForcedSkill(char* buf);
	void UnLockCashPoint();

private:
	int OnShandaProcess(); // not implemented
	int DispatchPacket(short Header, int packetSize);
	void OnEnter(const unsigned long in_AID, const unsigned long in_GID, const int in_AuthCode, const unsigned long in_clientTime, const unsigned char in_Sex);
	void OnChat(const PACKET_CZ_REQUEST_CHAT* in_pPacket);
	void OnCZ_REQUEST_MOVE(const unsigned char* in_dest);
	void OnRequestTime(const unsigned long in_clientTime);
	void OnActorInit(int len);
	void OnCZ_CONTACTNPC(const PACKET_CZ_CONTACTNPC& in_Packet);
	void OnReqName(const unsigned long in_AID);
	void OnWhisper(int len);
	void OnChangeDir(const short in_headDir, const unsigned char in_dir);
	void OnDisconnectCharacter(int len);
	void OnDisconnectAllCharacter(int len);
	void OnReqAct1(int packetSize, char* buf);
	void OnReqAct2(const unsigned long in_targetGID, const unsigned char in_action, const bool in_bRequestClient);
	void OnMakeGroup(int len);
	void OnReqJoinGroup(int len);
	void OnJoinGroup(int len);
	void OnCZ_REQ_JOIN_GUILD2(const PACKET_CZ_REQ_JOIN_GUILD2& in_Packet);
	void OnReqExpelGroupMember(int len);
	void OnReqNameByGID(const unsigned long in_GID);
	void OnCZ_ITEM_PICKUP(const unsigned long in_ITAID);
	void OnThrowItem(const unsigned short in_Index, const short in_count);
	void OnUseItem(int len);
	void OnUseItem2(const unsigned short in_index, const unsigned long in_AID);
	void OnWearEquip(int len);
	void OnTakeOffEquip(int len);
	void OnPurchaseItem(int len);
	void OnSellItem(int len);
	void OnItemExplanationByName(int len);
	void OnChooseMenu(int len);
	void OnReqNextScript(int len);
	void OnRestart(int len);
	void OnRestart_QUIT_RESTART();
	void OnRestart_QUIT_EXIT();
	bool OnRestart_QUIT_EXIT_Part1();
public:
	void OnRestart_QUIT_EXIT_Part2();
private:
	void OnStatusChange(const PACKET_CZ_STATUS_CHANGE& in_packet);
	void OnReqEmotion(int len);
	void OnReqUserCount(int len);
	void OnSelectDealType(int len);
	void OnSettingWhisperPC(int len);
	void OnSettingWhisperState(int len);
	void OnReqWhisperList(int len2);
	void OnCreateChatRoom(int len);
	void OnReqEnterRoom(int len);
	void OnChangeChatRoom(int len);
	void OnReqChangeRole(int len);
	void OnReqExpelMember(int len);
	void OnExitRoom(int len);
	void OnReqExchangeItem(int len);
	void OnAckReqExchangeItem(int len);
	void OnExecExchangeItem(int len);
	void OnAddExchangeItem(int len);
	void OnConcludeExchangeItem(int len);
	void OnCancelExchangeItem(int len);
	void OnCancelLockOn(int len);
	void OnMoveItemFromBodyToStore(const short in_index, const int in_count);
	void OnMoveItemFromStoreToBody(const short in_index, const int in_count);
	void OnMoveItemFromBodyToCart(int len);
	void OnMoveItemFromCartToBody(int len);
	void OnMoveItemFromStoreToCart(int len);
	void OnMoveItemFromCartToStore(int len);
	void OnCloseStore(int len);
	void OnChatParty(int len);
	void OnUpgradeSkillLevel(int len);
	void OnUseSkill(const unsigned short in_SKID, const short in_selectedLevel, unsigned long in_targetID);
	void OnUseGuildSkill(const unsigned short in_SKID, const short in_selectedLevel, const unsigned long in_targetID);
	void OnUseSkill_Merce(const unsigned short in_SKID, const short in_selectedLevel, const unsigned long in_targetID);
	void OnSelectWarpPoint(int len);
	void OnRememberWarpPoint(int len);
	void OnCartOff(int len);
	void OnReqCloseMCStore(int len);
	void OnReqOpenMCStore(int len);
	void OnReqOpenMCStore2(int len);
	void PurchaseItemFromMCStore(int len);
	void PurchaseItemFromMCStore2(int len);
	void OnReqItemListFromMCStore(int len);
	void OnPKModeChange(int len);
	void OnItemCreate(const std::string in_cmdline);
	void OnAdminMapMove(int len);
	void OnInputEditDlg(int len);
	void OnCloseDialog(int len);
	void OnReqItemIdentify(int len);
	void OnReqItemCompositionList(int len);
	void OnReqItemComposition(int len);
	void OnReqDisconnect(int len);
	void OnSelectAutoSpell(int len);
	void OnReqGuildMenuInterface(int len);
	void OnReqGuildMenu(int len);
	void OnReqGuildEmblemImg(int len);
	void OnRegisterGuildEmblemImg(int len);
	void OnReqChangeMemberPos(int len);
	void OnReqOpenMemberInfo(int len);
	void OnReqLeaveGuild(int len);
	void OnReqBanGuild(int len);
	void OnReqDisorganizeGuild(int len);
	void OnReqChangeGuildPositionInfo(int len);
	void OnReqHostileGuild(int len);
	void SendAckReqAllyGuild(unsigned long AID, unsigned char answer);
	void SendAckReqHostileGuild(unsigned long AID, unsigned char answer);
	void OnReqAllyGuild(int packetSize);
	void OnAllyGuild(int packetSize);
	void OnGuildNotice(int packetSize);
	void OnGuildChat(int packetSize);
	void OnReqMakeGuild(int packetLen);
	void OnReqJoinGuild(int packetSize);
	void OnJoinGuild(int packetSize);
	void OnReqDeleteRelatedGuild(int Len);
	void OnReqGuildMemberInfo(int len);
	void OnResetParameter(int len);
	void OnChangeMapType(int len);
	void OnLocalBroadCast(int len);
	void OnShift(int len);
	void OnChangeEffectState(int len);
public:
	void ResetReqGuildTime();
private:
	void OnGuildZeny(int len);
	void OnReqMakingItem(int len);
	void OnReqUSE_SKILL_TOGROUND_WITHTALKBOX(const short in_selectedLevel, const unsigned short in_SKID, const short in_xPos, const short in_yPos, const char* in_contents);
	void OnGiveMannerPoint(int packetSize);
	void OnGiveMannerPointByName(int len);
	void OnTryCaptureMonster(int len);
	void OnCommandPet(int len);
	void OnRenamePet(int len);
	void OnRenameHomun(int len);
	void OnSelectPetEgg(int len);
	void OnPetEggInfo(int len);
	void OnPetAct(int len);
	void OnMakingItem();
	void OnCZ_REMOVE_AID(const PACKET_CZ_REMOVE_AID& in_packet);
	void OnRecall(int len);
	void OnRecallGID(int len);
	void OnReqEncryption(int len);
	void OnInputEditDlgStr(int len);
	void OnAddFriend(int len);
	void OnDeleteFriend(int len);
	void OnAckReqAddFriends(int len);
	void OnReqPVPPoint(int len);
	void OnReqStatus(int len);
	void OnReqMakerRanking(const short in_PacketType, const int in_PacketLength);
	void OnReqKSY(int len);
	void OnLessEffect(int len);
	void OnAckGameGuard(int len);
	void OnRequestMoveToOwner(int len);
	void OnRequestMoveNpc(int len);
	void OnRequestActNpc(int len);
	void OnCommandMercenary(int len);
	void OnAckStorePassword(int len);
	void OnMailGetList(int len);
	void OnMailOpen(int len);
	void OnMailDelete(int len);
	void OnMailGetItem(int len);
	void OnMailResetItem(int len);
	void OnMailAddItem(int len);
	void OnMailSend(int len);
	void OnMailReturn(int len);
	void OnAuctionCreate(int len);
	void OnAuctionAddItem(int len);
	void OnAuctionAdd(int len);
	void OnAuctionAddCancel(int len);
	void OnAuctionBuy(int len);
	void OnAuctionItemSearch(int len);
	void OnAuctionReqMyInfo(int len);
	void OnAuctionMySellStop(int len);
	void OnHuntingList(int len);
	void OnPCBuyCashPointItem(const int len);
	void OnPCBuyCashPointItemSimpleShop(int len);
	void OnStandingResurrection(int len);
	void OnReqOpenBuyingStore(const int len);
	void OnReqClickToBuyingStore(const int len);
	void OnReqTradeBuyingStore(const int len);
	void OnReqCloseBuyingStore(const int len);
	void OnReqPossibleTradeItemBuyingStore(const int len); //TODO
	void OnSearchStoreInfo(const int len);
	void OnSearchStoreInfoNexPage(const int len);
	void OnCloseSearchStoreInfo(const int len);
	void OnSSIListItemClick(const int len);
	void OnCashPassword(int len);
	void OnShortcutKey_Change(int len);
	void OnActiveQuest(int len);
	void OnBattleFieldChat(int len);
	void OnProgress(int len);
	void OnCzOpenSimpleCashShopItemList(int len);
	void OnCZOnCloseWindow(int len);
	void OnCZClientVersion(int len);
	void OnCZCloseSimpleCashShop(int len);
	void OnCZSimpleCashBtnShow(int len);
	void OnCZMove_AID_SSO(const int len);
	void OnCZRecall_SSO(const int len);
	void OnCZ_SE_CASHSHOP_OPEN(const PACKET_CZ_SE_CASHSHOP_OPEN& in_packet);
	void OnCZReqSeCashTabCode(const int len);
	void OnCZSePcBuyCashItemList(const int len);
	void OnCZSeCashShopClose(const int len);
	void OnCZReqSchedulerCashItem(const PACKET_CZ_REQ_SCHEDULER_CASHITEM& packet);
	bool CheckRequestNpcTime();
	bool SendMsgItemScriptEvent(int senderAID, unsigned long msgID, int par1, int par2, int par3);
	bool CheckMap(unsigned long AID, unsigned long type);
	bool CheckSameMap(unsigned long AID, unsigned long type);
	bool ForcedCloseDialog(unsigned long NPCID);
public:
	void NotifyBattleFieldPoint();
private:
	void OnChangeGroupMaster(int len);
	void OnSeekParty(int len);
	void OnSeekPartyMember(int len);
	void OnCZ_USE_SKILL(const int in_SKID, const int in_Level, const unsigned long in_TargetID);
	void BroadcastNewPosition(int dx, int dy);

private:
	/* this+  0 */ //CPacketHandler baseclass_0;
	/* this+  8 */ CPC* m_pc;
	/* this+ 12 */ DWORD m_ReqGuildEmblemTime;
	/* this+ 16 */ DWORD m_ReqGuildMenuTime[4];
	/* this+ 32 */ DWORD m_RequestNpcTime;
	/* this+ 36 */ CCSAuth m_csAuth;
	/* this+156 */ BOOL m_bLockCashPoint;

private:
	void OnMercenary_Command(const PACKET_CZ_MER_COMMAND* in_pPacket);
	void OnMercenary_RequestActNpc(const PACKET_CZ_REQUEST_ACTNPC* in_pPacket);
	void OnMercenary_UseSkill(const unsigned short in_SKID, const short in_selectedLevel, unsigned long in_targetID);
	void OnCZ_USE_SKILL_TOGROUND(const int in_SKID, const int in_SelectedLevel, const int in_targetXpos, const int in_targetYpos);
	void OnMercenary_UseSkill_ToGround(const int in_SKID, const int in_SelectedLevel, const int in_targetXpos, const int in_targetYpos);
	void OnUseSkillToGround_Homun(const int in_SKID, const int in_SelectedLevel, const int in_targetXpos, const int in_targetYpos);
	void OnUseSkillToGround(const int in_SKID, const int in_SelectedLevel, const int in_targetXpos, const int in_targetYpos);
	void OnCZ_PARTY_JOIN_REQ(const PACKET_CZ_PARTY_JOIN_REQ& in_packet);
	void OnCZ_PARTY_CONFIG(const PACKET_CZ_PARTY_CONFIG& in_packet);
	void OnCZ_PARTY_JOIN_REQ_ACK(const PACKET_CZ_PARTY_JOIN_REQ_ACK& in_packet);
	void OnCZ_MEMORIALDUNGEON_COMMAND(const PACKET_CZ_MEMORIALDUNGEON_COMMAND& in_packet);
	void OnCZ_EQUIPWIN_MICROSCOPE(const PACKET_CZ_EQUIPWIN_MICROSCOPE& in_packet);
	void OnCZ_CONFIG(const PACKET_CZ_CONFIG& in_packet);
	void OnCZ_REQ_LEAVE_GROUP(const PACKET_CZ_REQ_LEAVE_GROUP& in_packet);
	void OnCZ_SKILL_SELECT_RESPONSE(const PACKET_CZ_SKILL_SELECT_RESPONSE& in_packet);
	void OnCZ_ITEMLISTWIN_RES(const unsigned char* in_pPacket, const int in_PacketSize);
	void OnCZ_GM_FULLSTRIP(const PACKET_CZ_GM_FULLSTRIP& in_packet);
	void OnCZ_MACRO_USE_SKILL(const PACKET_CZ_MACRO_USE_SKILL& in_packet);
	void OnCZ_MACRO_USE_SKILL_TOGROUND(const PACKET_CZ_MACRO_USE_SKILL_TOGROUND in_packet);
	void OnCZ_MACRO_REQUEST_MOVE(const PACKET_CZ_MACRO_REQUEST_MOVE& in_packet);
	void OnCZ_MACRO_ITEM_PICKUP(const PACKET_CZ_MACRO_ITEM_PICKUP in_packet);
	void OnCZ_MACRO_REQUEST_ACT(const PACKET_CZ_MACRO_REQUEST_ACT& in_packet);
	void OnCZ_MACRO_START(const PACKET_CZ_MACRO_START& in_packet);
	void OnCZ_MACRO_STOP(const PACKET_CZ_MACRO_STOP& in_packet);
	void OnCZ_GPK_DYNCODE_RELOAD(const PACKET_CZ_GPK_DYNCODE_RELOAD& in_packet);
	void OnCZ_GPK_AUTH(const PACKET_CZ_GPK_AUTH& in_packet);
	void OnZC_REASSEMBLY_AUTH(const int ); //TODO
	void OnCZ_IRMAIL_SEND(const PACKET_CZ_IRMAIL_SEND* const ); //TODO
	void OnCZ_IRMAIL_LIST(const PACKET_CZ_IRMAIL_LIST& ); //TODO
	void OnCZ_PC_SELL_ITEMLIST(const PACKET_CZ_PC_SELL_ITEMLIST* const in_pPacket);
	void OnCZ_GROUPINFO_CHANGE_V2(const PACKET_CZ_GROUPINFO_CHANGE_V2& in_packet);
	void OnCZ_CHOPOKGI(const PACKET_CZ_CHOPOKGI& in_packet);
	void OnCZ_TRYCOLLECTION(const PACKET_CZ_TRYCOLLECTION& in_packet);
	void OnCZ_REQ_ENTRY_QUEUE_APPLY(const PACKET_CZ_REQ_ENTRY_QUEUE_APPLY& in_packet);
	void OnCZ_REQ_ENTRY_QUEUE_CANCEL(const PACKET_CZ_REQ_ENTRY_QUEUE_CANCEL& in_packet);
	void OnCZ_REPLY_ENTRY_QUEUE_ADMISSION(const PACKET_CZ_REPLY_ENTRY_QUEUE_ADMISSION& in_packet);
	void OnCZ_REPLY_LOBBY_ADMISSION(const PACKET_CZ_REPLY_LOBBY_ADMISSION& in_packet);
	void OnCZ_REQ_ENTRY_QUEUE_RANKING(const PACKET_CZ_REQ_ENTRY_QUEUE_RANKING& in_packet);
	void OnCZ_INVENTORY_TAB(const PACKET_CZ_INVENTORY_TAB& in_packet);
	void OnCZ_SELECTCART(const PACKET_CZ_SELECTCART& in_packet);
	void OnCZ_REQ_CHANGECART(const PACKET_CZ_REQ_CHANGECART& in_packet);
	void OnCZ_REQ_MERGE_ITEM(const int in_packetSize, const char* in_pPacket);
	void OnCZ_CANCEL_MERGE_ITEM();
	void OnCZ_REQ_RANKING(const PACKET_CZ_REQ_RANKING& in_packet);
	void OnCZ_CLAN_CHAT(const int len);
	void ON_CZ_ITEM_CREATE(const PACKET_CZ_ITEM_CREATE& in_packet); //TODO
	void ON_CZ_ITEM_CREATE_EX(const PACKET_CZ_ITEM_CREATE_EX& in_packet);
	void OnCZ_NPROTECTGAMEGUARDCSAUTH(const PACKET_CZ_NPROTECTGAMEGUARDCSAUTH* in_pPacket);
};


void Sned_PACKET_ZC_PARTY_JOIN_REQ_ACK(CPC* const in_pToPlayer, const char* in_pTargetCharName, PACKET_ZC_PARTY_JOIN_REQ_ACK::enumAnswer in_Answer);
