#include "CharacterMgr.h"
#include "NpcEvt.h"


CNpcEvt::CNpcEvt() // 40-42
{
	//TODO
}


CNpcEvt::~CNpcEvt() // 45-46
{
	//TODO
}


void CNpcEvt::InitCore() // 53-69
{
	//TODO
}


void CNpcEvt::OnProcess() // 72-79
{
	//TODO
}


BOOL CNpcEvt::IsSellItem(unsigned short ITID) // 100-104
{
	for( std::list<int>::iterator it = m_sellList.begin(); it != m_sellList.end(); ++it )
		if( *it == ITID )
			return TRUE;

	return FALSE;
}


int CNpcEvt::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // 107-175
{
	return 0;
	//TODO
}


void CNpcEvt::OnPurchaseItem(CCharacter* character, const int in_GroupNum) // 218-264
{
	//TODO
}


void CNpcEvt::OnMsgFromNPCServer(unsigned long senderAID, unsigned long receiverAID, CMsg* msg, unsigned long par1, unsigned long par2) // 268-547
{
	if( msg == NULL )
		return;

	switch( msg->CMsg::GetMsgID() )
	{
	case NPC2ZMSG_SETARENAEVENTSIZE:
		this->CNpcEvt::SetArenaEventsize(msg->par1);
	break;
	case NPC2ZMSG_MAKEWAITINGROOM:
		this->CNpcEvt::OnMakeWaitingRoom(msg->par1, msg->par2, msg->par3);
	break;
	case NPC2ZMSG_ENABLEARENA:
		this->CNpcEvt::EnableArena();
	break;
	case NPC2ZMSG_DISABLEARENA:
		this->CNpcEvt::DisableArena();
	break;
	case NPC2ZMSG_WARPWAITINGPCTOARENA:
		this->CNpcEvt::OnWarpWaitingPCTOARENA(msg);
	break;
	case NPC2ZMSG_RESETMYMOB:
		this->CNPC::OnResetMyMob();
	break;
	case NPC2ZMSG_WARPALLPCINTHEMAP:
		this->CNpcEvt::OnWarpAllPCInTheMap(msg);
	break;
	case NPC2ZMSG_BROADCASTINTHEMAP:
		this->CNpcEvt::OnBroadcastInthemap(msg);
	break;
	case NPC2ZMSG_BROADCASTINTHEMAP2:
	case NPC2ZMSG_BROADCASTINSERVER:
		this->CNpcEvt::OnBroadcast(msg);
	break;
	case NPC2ZMSG_OPENDIALOG:
		this->CNpcEvt::OnOpenDiaLog(msg);
	break;
	case NPC2ZMSG_ENABLENPC:
		this->CNPC::Enable();
	break;
	case NPC2ZMSG_DISABLENPC:
		this->CNPC::Disable();
	break;
	case NPC2ZMSG_MAPMOVE:
		this->CNpcEvt::OnMapMove(msg);
	break;
	case NPC2ZMSG_DISABLEITEMMOVE:
		this->CNpcEvt::OnDisableItemMove(msg);
	break;
	case NPC2ZMSG_ENABLEITEMMOVE:
		this->CNpcEvt::OnEnableItemMove(msg);
	break;
	case NPC2ZMSG_SUCCESSREFITEM:
		this->CNpcEvt::OnSuccessRefItem(senderAID, msg);
	break;
	case NPC2ZMSG_FAILEDREFITEM:
		this->CNpcEvt::OnFailedRefItem(senderAID, msg);
	break;
	case NPC2ZMSG_SETEFFECTSTATE:
		this->CNpcEvt::OnSetEffectState(senderAID, msg->par2);
	break;
	case NPC2ZMSG_ARENAROOM_SETFEEZENY:
		this->CNpcEvt::OnSetFeeZeny(senderAID, msg->par1);
	break;
	case NPC2ZMSG_ARENAROOM_SETFEEITEM:
		this->CNpcEvt::OnSetFeeItem(senderAID, msg->par1, msg->par2);
	break;
	case NPC2ZMSG_ARENAROOM_SETLEVEL:
		this->CNpcEvt::OnSetLevel(senderAID, msg->par1, msg->par2);
	break;
	case NPC2ZMSG_ARENAROOM_SETEXJOB:
		this->CNpcEvt::OnSetExJob(senderAID, msg->par1);
	break;
	case NPC2ZMSG_CHANGE_MONEY:
		this->CNpcEvt::OnChangeMoney(senderAID, msg->par1);
	break;
	case NPC2ZMSG_RESET_STAT:
		this->CNpcEvt::OnResetStat(senderAID);
	break;
	case NPC2ZMSG_RESET_SKILL:
		this->CNpcEvt::OnResetSkill(senderAID);
	break;
	case NPC2ZMSG_SHOWIMAGE:
		this->CNpcEvt::OnShowImage(senderAID, msg->par1, msg->par2);
	break;
	case NPC2ZMSG_CHANGEPALLETE:
		this->CNpcEvt::OnChangePalete(senderAID, msg->par1, msg->par2);
	break;
	case NPC2ZMSG_COMPASS:
		this->CNpcEvt::OnCompass(senderAID, msg->par1, msg->par2, msg->par3, msg->par4, msg->par5);
	break;
	case NPC2ZMSG_CHECKPOINT:
		this->CNpcEvt::OnCheckPoint(senderAID, msg->par1, msg->par2, msg->par3);
	break;
	case NPC2ZMSG_WAITDIALOG:
		this->CNpcEvt::OnWaitDialog(senderAID);
	break;
	case NPC2ZMSG_CLOSEDIALOG:
		this->CNpcEvt::OnCloseDialog(senderAID);
	break;
	case NPC2ZMSG_SETITEM:
		this->CNpcEvt::OnSetItem(senderAID, msg->par1, msg->par2);
	break;
	case NPC2ZMSG_CHANGEITEM:
		this->CNpcEvt::OnChangeItem(senderAID, msg->par1, msg->par2, msg->par3, msg->par4, msg->par5);
	break;
	case NPC2ZMSG_HEAL:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, senderAID, 80, msg->par1, msg->par2, 0, 0);
	break;
	case NPC2ZMSG_CHANGEVAR:
		this->CNpcEvt::OnChangeVar(senderAID, msg->par1, msg->par2);
	break;
	case NPC2ZMSG_DLGWRITE:
		this->CNpcEvt::OnDLG_Write(senderAID);
	break;
	case NPC2ZMSG_NUDE:
		this->CNpcEvt::OnNude(senderAID);
	break;
	case NPC2ZMSG_CARTON:
		this->CNpcEvt::OnCartOn(senderAID);
	break;
	case NPC2ZMSG_STORE:
		this->CNpcEvt::OnNotifyStoredItem(senderAID);
	break;
	case NPC2ZMSG_MENU:
		this->CNpcEvt::OnMenu(senderAID, msg->par1, msg->par2);
	break;
	case NPC2ZMSG_TRADERCMD:
		this->CNpcEvt::OnTradeNpcCommandRegister(senderAID, msg->par1, msg->par2);
	break;
	case NPC2ZMSG_SHOWDIGIT:
		this->CNpcEvt::OnShowDigit(senderAID, msg->par1);
	break;
	case NPC2ZMSG_ENABLESKILL:
		this->CNpcEvt::OnEnableSkill(senderAID, msg->par1, msg->par2);
	break;
	case NPC2ZMSG_DISABLESKILL:
		this->CNpcEvt::OnDisableSkill(senderAID, msg->par1);
	break;
	case NPC2ZMSG_SOUND:
		this->CNpcEvt::OnSound(senderAID, msg);
	break;
	case NPC2ZMSG_DLGWRITESTR:
		this->CNpcEvt::OnDLG_WriteStr(senderAID);
	break;
	case NPC2ZMSG_CHANGE_EXP:
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, senderAID, 61, msg->par1, 0, 0, 0);
	break;
	case NPC2ZMSG_USESKILL_TO_PC:
		this->CNpcEvt::UseSkillToPC(senderAID, receiverAID, msg->par1, msg->par2, msg->par3, msg->par4);
	break;
	case NPC2ZMSG_CASHTRADERCMD:
		this->CNpcEvt::OnCashTradeNpcCommandRegister(receiverAID, msg);
	break;
	case NPC2ZMSG_CASHINFO:
		this->CNpcEvt::OnCashItemList(senderAID, msg);
	break;
	case NPC2ZMSG_RELOADMOBILE_EVENT:
		this->CNpcEvt::OnReloadMobileEvent(senderAID, msg);
	break;
	case NPC2ZMSG_QUEST_EVENTITEM:
		this->CNpcEvt::OnEventItem(senderAID, msg);
	break;
	case NPC2ZMSG_RELOADMOBILE_EVENT_EXCULUSIVE:
	case NPC2ZMSG_MYMOBSKILLUSE:
		this->CNpcEvt::OnMyMobSkillUse(receiverAID, msg);
	break;
	case NPC2ZMSG_WIDEMOBSKILLUSE:
		this->CNpcEvt::OnWideMobSkillUse(receiverAID, msg, par1, par2);
	break;
	case NPC2ZMSG_WIDEMOBSKILLUSE2:
		this->CNpcEvt::OnWideMobSkillUse2(receiverAID, msg);
	break;
	case NPC2ZMSG_GETITEMSOCKET:
		this->CNpcEvt::OnGetItemSocket(senderAID, msg, par1);
	break;
	case NPC2ZMSG_GETNONSLOTITEMSOCKET:
		this->CNpcEvt::OnNonSlotGetItemSocket(senderAID, msg, par1);
	break;
	case NPC2ZMSG_GETNONSLOTITEMSOCKET2:
		this->CNpcEvt::OnNonSlotGetItemSocket2(senderAID, msg, par1);
	break;
	case ZNPC2ZMSG_CLICK_MOBTOMB:
		this->CNpcEvt::MobTombClick(senderAID);
	break;
	default:
	break;
	};
}


int CNpcEvt::GetArenaEventSize()
{
	return m_arenaEventSize;
}


void CNpcEvt::SetArenaEventsize(int size)
{
	m_arenaEventSize = size;
}


void CNpcEvt::SetGraffiti(int num)
{
	m_flagGraffitiNum = num;
}


void CNpcEvt::AddSkill(CMsg* msg)
{
	//TODO
}


void CNpcEvt::OnMakeWaitingRoom(int len, int bufpointer, int limitSize) // 563-590
{
	//TODO
}


void CNpcEvt::EnableArena()
{
	m_isArenaPossible = TRUE;
}


void CNpcEvt::DisableArena()
{
	m_isArenaPossible = FALSE;
}


void CNpcEvt::OnWarpWaitingPCTOARENA(CMsg* msg) // 593-634
{
	//TODO
}


void CNpcEvt::OnWarpAllPCInTheMap(CMsg* msg) // 637-695
{
	//TODO
}


void CNpcEvt::OnBroadcastInthemap(CMsg* msg) // 698-717
{
	//TODO
}


void CNpcEvt::OnBroadcast(CMsg* in_pMSG) // 722-745
{
	//TODO
}


void CNpcEvt::OnOpenDiaLog(CMsg* msg) // 777-797
{
	//TODO
}


void CNpcEvt::OnMapMove(CMsg* msg) // 808-817
{
	//TODO
}


void CNpcEvt::OnDisableItemMove(CMsg* msg) // 820-826
{
	//TODO
}


void CNpcEvt::OnEnableItemMove(CMsg* msg) // 829-835
{
	//TODO
}


void CNpcEvt::OnSuccessRefItem(int receiverAID, CMsg* msg) // 838-844
{
	//TODO
}


void CNpcEvt::OnFailedRefItem(int receiverAID, CMsg* msg) // 847-853
{
	//TODO
}


void CNpcEvt::OnSetEffectState(int senderAID, int enu) // 856-881
{
	//TODO
}


void CNpcEvt::OnSetFeeZeny(int senderAID, int zeny) // 884-889
{
	//TODO
}


void CNpcEvt::OnSetFeeItem(int senderAID, int ITID, int count) // 892-893
{
	//TODO
}


void CNpcEvt::OnSetLevel(int senderAID, int lowLevel, int highLevel) // 900-905
{
	//TODO
}


void CNpcEvt::OnSetExJob(int senderAID, int job) // 908-913
{
	//TODO
}


void CNpcEvt::OnChangeMoney(int senderAID, int amount) // 916-938
{
	//TODO
}


void CNpcEvt::OnResetStat(int senderAID) // 941-944
{
	//TODO
}


void CNpcEvt::OnResetSkill(int senderAID) // 947-950
{
	//TODO
}


void CNpcEvt::OnShowImage(unsigned long senderAID, int type, int imageName) // 953-955
{
	//TODO
}


void CNpcEvt::OnChangePalete(unsigned long pcID, int where, int type) // 958-969
{
	//TODO
}


void CNpcEvt::OnCompass(unsigned long senderAID, int id, int x, int y, int type, int color) // 972-979
{
	//TODO
}


void CNpcEvt::OnCheckPoint(unsigned long senderAID, int x, int y, int mapName) // 982-992
{
	//TODO
}


void CNpcEvt::OnWaitDialog(unsigned long senderAID) // 995-997
{
	//TODO
}


void CNpcEvt::OnCloseDialog(unsigned long senderAID) // 1007-1009
{
	//TODO
}


void CNpcEvt::OnSetItem(unsigned long senderAID, int ITID, int num) // 1012-1017
{
	//TODO
}


void CNpcEvt::OnChangeItem(const unsigned long in_SenderAID, const int in_ITID, const int in_Num, const int in_Event, const int in_bBroadcasting, const int in_bLog) // 1043-1117
{
	//TODO
}


void CNpcEvt::OnGetItemSocket(unsigned long senderAID, CMsg* msg, int event) // 1178-1801
{
	//TODO
}


void CNpcEvt::OnNonSlotGetItemSocket(unsigned long senderAID, CMsg* msg, int event) // 1804-1828
{
	//TODO
}


void CNpcEvt::OnNonSlotGetItemSocket2(unsigned long senderAID, CMsg* msg, int event) // 1832-1865
{
	//TODO
}


void CNpcEvt::OnChangeVar(unsigned long senderAID, int var, int num) // 1147-1152
{
	//TODO
}


void CNpcEvt::OnDLG_Write(unsigned long senderAID) // 1267-1276
{
	//TODO
}


void CNpcEvt::OnNude(unsigned long senderAID) // 1160-1162
{
	//TODO
}


void CNpcEvt::OnCartOn(unsigned long senderAID) // 1165-1167
{
	CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, senderAID, CM_CARTON, 0, 0, 0, 0);
}


void CNpcEvt::OnNotifyStoredItem(unsigned long senderAID) // 1170-1172
{
	//TODO
}


void CNpcEvt::OnMenu(unsigned long senderAID, int len, int str) // 1175-1177
{
	//TODO
}


void CNpcEvt::OnTradeNpcCommandRegister(unsigned long senderAID, int type, int ITID) // 1192-1207
{
	//TODO
}


void CNpcEvt::OnShowDigit(unsigned long senderAID, int time) // 1211-1213
{
	//TODO
}


void CNpcEvt::OnEnableSkill(unsigned long senderAID, int skill, int level) // 1216-1218
{
	//TODO
}


void CNpcEvt::OnDisableSkill(unsigned long senderAID, int skill) // 1221-1223
{
	//TODO
}


void CNpcEvt::OnSound(unsigned long senderAID, CMsg* msg) // 1226-1264
{
	//TODO
}


void CNpcEvt::OnDLG_WriteStr(unsigned long senderAID) // 1267-1276
{
	//TODO
}


void CNpcEvt::OnZNCloseDialog(int par1) // 1279-1288
{
	//TODO
}


void CNpcEvt::OnInputEditDlg(int inputValue, unsigned long CAID) // 1291-1300
{
	//TODO
}


void CNpcEvt::OnInputEditDlgStr(int answer, unsigned long CAID) // 1303-1312
{
	//TODO
}


int CNpcEvt::IsArenaPossible() // 1315-1325
{
	return 0;
	//TODO
}


int CNpcEvt::GetEmblemVersion() // 1328-1350
{
	return 0;
	//TODO
}


CRoom* CNpcEvt::GetMyRoom() // 1353-1361
{
	return NULL;
	//TODO
}


void CNpcEvt::OnWarpCharBetweenServer(unsigned long AID) // 1364-1372
{
	//TODO
}


void CNpcEvt::MulticastRoomNewEntry(unsigned long roomID) // 1375-1390
{
	//TODO
}


void CNpcEvt::UseSkillToPC(unsigned long senderAID, unsigned long receiverAID, int SKID, int skLevel, int statPoint, int cLevel) // 1395-1472
{
	//TODO
}


void CNpcEvt::CheckTouchObjects() // 1480-1503
{
	//TODO
}


bool CNpcEvt::IsTouchObject(unsigned long id) // 1509-1514
{
	return ( m_touchObjects.find(id) != m_touchObjects.end() );
}


void CNpcEvt::AddTouchObjects(unsigned long id) // 1519-1521
{
	//TODO
}


void CNpcEvt::OnCashTradeNpcCommandRegister(unsigned long receiverAID, CMsg* msg) // 1525-1555
{
	//TODO
}


void CNpcEvt::OnCashItemList(unsigned long senderAID, CMsg* msg) // 1559-1630
{
	//TODO
}


void CNpcEvt::OnAddMoveNpcCommand(unsigned long npcId, CMsg* msg)
{
	//TODO
}


void CNpcEvt::OnUpdateContectPcList(unsigned long pcID, CMsg* msg)
{
	//TODO
}


void CNpcEvt::OnMoveNpcSpeedChange(int speed)
{
	//TODO
}


void CNpcEvt::OnReloadMobileEvent(unsigned long pcID, CMsg* msg) // 1659-1661
{
	//TODO
}


void CNpcEvt::OnEventItem(unsigned long senderAID, CMsg* msg) // 1665-1667
{
	//TODO
}


void CNpcEvt::OnMyMobSkillUse(unsigned long npcId, CMsg* msg) // 1679-1685
{
	//TODO
}


void CNpcEvt::OnWideMobSkillUse(unsigned long npcId, CMsg* msg, int xPos, int yPos) // 1688-1724
{
	//TODO
}


void CNpcEvt::OnWideMobSkillUse2(unsigned long npcId, CMsg* msg) // 1727-1773
{
	//TODO
}


void CNpcEvt::MobTombClick(const unsigned int PC_AID) // 1875-1897
{
	//TODO
}


void CNpcEvt::Dialog(const char* Msg, const unsigned int PC_AID) // 1900-1918
{
	//TODO
}
