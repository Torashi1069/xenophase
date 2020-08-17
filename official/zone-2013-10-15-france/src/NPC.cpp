#include "CharacterMgr.h"
#include "Enum.h"
#include "MonParameterMgr.h"
#include "NPC.h"
#include "ZGuildMgr.h"
#include "ZoneProcess.h"
#include "ZoneProcessStuff.h"
#include "Common/Packet.h"


CNPC::CNPC() // 86-95 (68-74)
{
	m_type = NPC_TYPE;
	m_mapRes = NULL;
	m_nBanTime = 0;
	m_eatingItemMPool.CMemoryMgr<EATING_ITEM_INVENTORY>::Init(10);
	m_myParentGID = 0;
}


CNPC::~CNPC() // 98-99 (77-78)
{
}


const char* CNPC::GetNamePtr() const // (199.h)
{
	return m_characterInfo.accountName;
}


int CNPC::GetJobType() const // (201.h)
{
	return m_characterInfo.job;
}


unsigned char CNPC::GetNPCType() // (220.h)
{
	return m_npcType;
}


CCharacter* CNPC::GetMyOwner() // 270.h
{
	return static_cast<CCharacter*>(this);
}


int CNPC::GetErrorCount() // 271.h (238.h)
{
	return m_dwErrorCount;
}


void CNPC::SetErrorCount(int i) // 272.h (239.h)
{
	m_dwErrorCount = i;
}


int CNPC::GetModifiedValueByEnemySize(int value) // 294.h (260.h)
{
	return value;
}


int CNPC::GetBaseFlee() // 297.h
{
	return 100 + m_characterInfo.clevel + m_characterInfo.Agi;
}


int CNPC::GetBaseHit() // 298.h
{
	return 150 + m_characterInfo.clevel + m_characterInfo.Dex;
}


void CNPC::SetParentAID(unsigned long AID) // (263.h)
{
	m_myParentAID = AID;
}


unsigned long CNPC::GetParentAID() const // (264.h)
{
	return m_myParentAID;
}


void CNPC::SetParentGID(unsigned long GID)
{
	m_myParentGID = GID;
}


unsigned long CNPC::GetParentGID() const
{
	return m_myParentGID;
}


void CNPC::SetRegen(BOOL flag) // (265.h)
{
	m_characterInfo.IsRegen = flag;
}


BOOL CNPC::IsRegen() // (266.h)
{
	return m_characterInfo.IsRegen;
}


char* CNPC::GetAccountName() // (272.h)
{
	return m_characterInfo.accountName;
}


short CNPC::GetAttackRange() // ??? (274.h)
{
	return m_characterInfo.attackRange;
}


NpcInfo* CNPC::GetCharacterInfo() // (285.h)
{
	return &m_characterInfo;
}


unsigned long CNPC::GetCurrentFSMState() // (286.h)
{
	return m_currentState;
}


unsigned long CNPC::GetEnemyAID() // ??? (297.h)
{
	 return m_npcStateUpdater.m_npcStateInfo.enemyAID;
}


void CNPC::SetEnemyAID(unsigned long AID) // ??? (298-302.h)
{
	m_npcStateUpdater.m_npcStateInfo.enemyAID = AID;
}


BOOL CNPC::SetAccountID(int AID) // (324.h)
{
	return m_npcUpdater.CNPCUpdater::SetAccountID(AID);
}


int CNPC::GetSKLevel(const int in_SKID) const // 499.h (418.h)
{
	return 0;
}


void CNPC::OnDead(unsigned long killer) // 101-157 (81-104)
{
	//TODO
}


void CNPC::Init() // 160-209 (107-147)
{
	//TODO
}


void CNPC::Reset() // 212-264 (150-197)
{
	//TODO
}


void CNPC::InitCore() // 267-309
{
	//TODO
}


void CNPC::SetCurrentFSMState(unsigned long state) // 351-381
{
	//TODO
}


BOOL CNPC::IsRightProperty(int property) // 384-389 (301-306)
{
	return ( property == this->CNPC::GetCurrentState() % 10 );
}


int CNPC::GetRevivalTerm() // 392-394 (309-311)
{
	return max(1000, GetServerRandom(m_characterInfo.RegenMinTime, m_characterInfo.RegenMinTime + m_characterInfo.RegenMaxTime)); //FIXME: double evaluation
}


void CNPC::OnProcess() // ??? (329-330)
{
}


unsigned long CNPC::GetAccountID() // 416-418 (333-335)
{
	return m_characterInfo.accountID;
}


int CNPC::OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4) // 421-684 (338-574)
{
	return 0;
	//TODO
}


void CNPC::OnEmotion(int type) // 710-716
{
	PACKET_ZC_EMOTION outpacket;
	outpacket.PacketType = HEADER_ZC_EMOTION;
	outpacket.GID = this->GetAccountID();
	outpacket.type = type;
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


int CNPC::GetParameterValue(unsigned short id, int& value) // 719-911 (586-776)
{
	return 0;
	//TODO
}


int CNPC::UpdateParameterValue(unsigned short id, int value) // 914-1168 (779-1025)
{
	return 0;
	//TODO
}


void CNPC::InsertCommand(COMMAND_QUEUE* command) // (1029-1035)
{
	m_commandQueue.push_back(*command);
}


void CNPC::CheckCommandQueue() // 1183-1254 (1040-1091)
{
	//TODO
}


BOOL CNPC::IsMyArea(CCharacter* ch, int range) // 1258-1260 (1095-1096)
{
	return m_npcUpdater.CNPCUpdater::IsMyArea(ch, range);
}


short CNPC::GetBodyState() // 1265-1267 (1102-1104)
{
	return static_cast<short>(m_characterPInfo.bodyState);
}


short CNPC::GetHealthState() // 1270-1272 (1107-1109)
{
	return static_cast<short>(m_characterPInfo.healthState);
}


short CNPC::GetCurrentState() // 1275-1288 (1112-1123)
{
	if( m_characterPInfo.bodyState == BODYSTATE_FREEZING )
		return PROPERTY_WATER1;
	else
	if( m_characterPInfo.bodyState == BODYSTATE_STONECURSE )
		return PROPERTY_GROUND1;

	return static_cast<short>(m_characterPInfo.currentProperty);
}


int CNPC::GetEffectState() // 1291-1293 (1126-1128)
{
	return m_characterPInfo.effectState;
}


void CNPC::ResetHealthState(short state) // 1316-1353 (1151-1177)
{
	//TODO
}


void CNPC::SetHealthState(short state) // 1356-1390
{
	//TODO
}


void CNPC::SetEffectState(int state) // 1399-1420 (1223-1237)
{
	if( state != EFFECTSTATE_NOTHING )
	{
		m_characterPInfo.effectState |= state;
	}
	else
	{
		m_characterPInfo.effectState &= ~EFFECTSTATE_PUSHCART;

		this->ResetEffective(EFST_HIDING, 0);
		this->ResetEffective(EFST_CLOAKING, 0);
		this->ResetEffective(EFST_CLOAKINGEXCEED, 0);
	}

	this->CNPC::MultiCastStateInfo();
}


void CNPC::ResetEffectState(int state) // 1423-1452 (1240-1269)
{
	//TODO
}


unsigned long CNPC::GetState() // 1473-1475
{
	return m_pathInfo.m_moveInfo.state;
}


BOOL CNPC::IsAvoidable(int race, int _class, int level) // 1517-1532 (1333-1344)
{
	return ( this->GetState() == CHARACTER_STATE_DEAD || m_characterPInfo.effectState & (EFFECTSTATE_BURROW | EFFECTSTATE_HIDING) );
}


void CNPC::MultiCastStateInfo() // 1561-1570 (1561-1570)
{
	PACKET_ZC_STATE_CHANGE3 outpacket;
	outpacket.PacketType = HEADER_ZC_STATE_CHANGE3;
	outpacket.AID = this->GetAccountID();
	outpacket.bodyState = static_cast<short>(m_characterPInfo.bodyState);
	outpacket.healthState = static_cast<short>(m_characterPInfo.healthState);
	outpacket.effectState = m_characterPInfo.effectState;
	outpacket.isPKModeON = false;
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


void CNPC::OnChangeAGI(int par1, int par2, int par3) // 1626-1636 (1429-1449)
{
	int SKID = (int)par3;
	unsigned long time = (unsigned long)par2;
	int amount = (int)par1;

	if( SKID == SKID_AL_INCAGI )
		this->CActor::ResetStatusAmount(SKID_AL_DECAGI, VAR_AGI);
	else
	if( SKID == SKID_AL_DECAGI )
		this->CActor::ResetStatusAmount(SKID_AL_INCAGI, VAR_AGI);

	this->OnChangeStatusAmount(SKID, VAR_AGI, time, amount);
}


void CNPC::OnChangeDEX(int par1, int par2, int par3) // 1639-1643 (1452-1466)
{
	int SKID = (int)par3;
	unsigned long time = (unsigned long)par2;
	int amount = (int)par1;

	this->OnChangeStatusAmount(SKID, VAR_DEX, time, amount);
}


void CNPC::OnChangeINT(int par1, int par2, int par3) // ??? (1469-1483)
{
	int SKID = (int)par3;
	unsigned long time = (unsigned long)par2;
	int amount = (int)par1;

	this->OnChangeStatusAmount(SKID, VAR_INT, time, amount);
}


void CNPC::OnChangeLUK(int par1, int par2, int par3) // ??? (1486-1500)
{
	int SKID = (int)par3;
	unsigned long time = (unsigned long)par2;
	int amount = (int)par1;

	this->OnChangeStatusAmount(SKID, VAR_LUK, time, amount);
}


void CNPC::OnChangeSTR(int par1, int par2, int par3) // 1660-1664 (1503-1517)
{
	int SKID = (int)par3;
	unsigned long time = (unsigned long)par2;
	int amount = (int)par1;

	this->OnChangeStatusAmount(SKID, VAR_STR, time, amount);
}


void CNPC::OnChangeVIT(int par1, int par2, int par3) // ??? (1520-1534)
{
	int SKID = (int)par3;
	unsigned long time = (unsigned long)par2;
	int amount = (int)par1;

	this->OnChangeStatusAmount(SKID, VAR_VIT, time, amount);
}


void CNPC::SetSpeed(int speed) // 1675-1677 (1538-1540)
{
	m_characterInfo.speed = speed;
}


int CNPC::GetSpeed() // 1680-1705 (1543-1568)
{
	return 0;
	//TODO
}


void CNPC::DisableCommand(unsigned long commandID) // 2073-2082 (1868-1877)
{
	//TODO
}


int CNPC::GetScale() // 2685-2687 (2600-2602)
{
	return m_characterInfo.scale;
}


void CNPC::SetEffectStateTimeInfo(unsigned long time, int state) // 2712-2721 (2632-2641)
{
	m_effectStateTimeL[state] = ( time != 9999 ) ? timeGetTime() + time : 9999;
	this->SetEffectState(state);
}


void CNPC::ResetEffective(int index, int val) // 2859-3418 (2803-3291)
{
	//TODO
}


BOOL CNPC::IsEnable() // 3421-3424 (3294-3297)
{
	return ( (m_characterPInfo.effectState & EFFECTSTATE_BURROW) != EFFECTSTATE_BURROW );
}


void CNPC::Enable() // 3427-3429
{
	this->SetEffectState(EFFECTSTATE_NOTHING);
}


void CNPC::Disable() // 3432-3434
{
	this->SetEffectState(EFFECTSTATE_BURROW);
}


void CNPC::InitSkill() // 3452-3455
{
	//TODO
/*
	m_npcSkill.m_isRebirth = FALSE;
	m_npcSkill.m_npcJob = m_characterInfo.job;
*/
}


BOOL CNPC::IsDamageMotionPossible() // 1455-1470 (1272-1292)
{
	if( m_characterTimeInfo.DamageNoMotionTime == 0 )
		return TRUE;

	if( m_characterTimeInfo.DamageNoMotionTime != 9999 && timeGetTime() >= m_characterTimeInfo.DamageNoMotionTime )
	{
		m_characterTimeInfo.DamageNoMotionTime = 0;
		return TRUE;
	}

	return FALSE;
}


int CNPC::GetAttackMotionTime() // 2692-2696 (2607-2616)
{
	return m_characterInfo.attackMT;
}


int CNPC::GetAttackedMotionTime() // 2699-2701 (2619-2621)
{
	return m_characterInfo.attackedMT;
}


void CNPC::ResetEffective_after_EFST_DEFENDER() // ??? (2793-2795)
{
}


BOOL CNPC::InitByPacket(void* p) // 3501-3699 (3374-3538)
{
	return FALSE;
	//TODO
}


BOOL CNPC::OnMove(PACKET_CZ_REQUEST_MOVE* p) // 3859-3865
{
	return FALSE; //TODO
	/*
	if( !this->CNPC::IsMovable() )
		return FALSE;

	if( !this->CNPC::StartPath(p, timeGetTime()) )
		return FALSE;

	return TRUE;
	*/
}


BOOL CNPC::IsTarget(CCharacter* ch, unsigned long flag) // 3911-4046 (3735-3872)
{
	return FALSE;
	//TODO
}


void CNPC::Revival() // 4049-4052 (3875-3878)
{
/*
	if( m_currentState != DEAD_ST )
		return;

	m_npcStateUpdater.CNPCStateUpdater::OnRevival(IDLE_ST);
*/
}


void CNPC::OnChangeDefense(int defense, BOOL isInit) // 4055-4141
{
	//TODO
/*
	static int table[4][3] = {
		///  hp def mdef
		{ 28634, 35, 60 }, // archer
		{ 30214, 55, 30 }, // knight
		{ 15670, 35,  0 }, // soldier
		{   700, 40, 50 }, // emperium
	};

	int index;
	if( m_characterInfo.job == JT_ARCHER_GUARDIAN )
		index = 0;
	else
	if( m_characterInfo.job == JT_KNIGHT_GUARDIAN )
		index = 1;
	else
	if( m_characterInfo.job == JT_SOLDIER_GUARDIAN )
		index = 2;
	else
	if( m_characterInfo.job == JT_EMPELIUM )
		index = 3;
	else
		return;

	int maxhp = table[index][0] + 1000 * defense;
	m_characterInfo.maxhp = maxhp;
	if( isInit )
	{
		if( index == 3 )
		{
			maxhp = g_empelium_hp * (table[3][0] + 50 * defense / 5);
			m_characterInfo.maxhp = maxhp;
		}

		m_characterInfo.hp = maxhp;
	}

	if( m_characterInfo._class == NPC_CLASS_GUARDIAN )
	{
		if( m_characterInfo.GuildID != 0 )
		{
			int skLevel = g_ZGuildMgr.CZGuildMgr::GetGuildSkillLevel(m_characterInfo.GuildID, SKID_GD_GUARDUP);
			int atkBonus = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(NULL, SKID_GD_GUARDUP, SM_GETINFO_SKILL, skLevel, 0, 0, 0);
			if( atkBonus != 0 )
			{
				this->CNPC::SetATKPercentInfo(SKID_GD_GUARDUP, 9999, atkBonus);
				int aspdBonus = g_skillTypeInfoMgr.CSkillTypeInfoMgr::SendMsg(NULL, SKID_GD_GUARDUP, SM_GETINFO_SKILL1, skLevel, 0, 0, 0);
				this->SetEffective(EFST_ATTHASTE_INFINITY, 9999, aspdBonus, 0, 0, 0);
			}
		}
	}

	int defBonus = (defense + 2) / 3;
	m_characterInfo.def = table[index][1] + defBonus;
	m_characterInfo.mdef = table[index][2] + defBonus;
*/
}


void CNPC::OnChangeGuildID() // 4145-4194 (3971-3995)
{
	if( !m_characterInfo.isValid )
		return;

	if( !this->CNPC::IsEnable() )
		return;

	short emblemVersion = 0;
	int GDID = 0;

	if( m_characterInfo.GuildID != 0 )
	{
		CGuild* g = g_ZGuildMgr.CGuildMgr::SearchGuild(m_characterInfo.GuildID);
		if( g != NULL )
		{
			emblemVersion = static_cast<short>(g->CGuild::GetEmblemVersion());
			GDID = m_characterInfo.GuildID;
		}
	}

	PACKET_ZC_CHANGE_GUILD packet;
	packet.PacketType = HEADER_ZC_CHANGE_GUILD;
	packet.AID = this->GetAccountID();
	packet.GDID = GDID;
	packet.emblemVersion = emblemVersion;
	this->CCharacter::MultiCast((char*)&packet, sizeof(packet));
}


void CNPC::SetATKPercentInfo(int SKID, DWORD time, int val) // 4204-4233 (4005-4034)
{
	std::map<int,AMOUNT_INFO>::iterator iter = m_ATKPercentList.find(SKID);
	if( iter != m_ATKPercentList.end() )
	{
		if( abs(val) < abs(iter->second.amount) )
			return;

		m_characterInfo.ATKPercent -= iter->second.amount;
	}

	m_characterInfo.ATKPercent += val;
	if( m_characterInfo.ATKPercent < 0 )
		m_characterInfo.ATKPercent = 0;

	if( time != 9999 )
		time += timeGetTime();

	AMOUNT_INFO* info = &m_ATKPercentList[SKID];
	info->time = time;
	info->amount = val;
	this->UpdateParameterValue(VAR_STATUSATTACKPOWER, 0);

	if( SKID == -2 )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, this, CM_LUK_CHANGE, -m_characterInfo.Luk, time, 0, 0);
}


void CNPC::SetDEFPercentInfo(int SKID, DWORD time, int val) // 4236-4259 (4037-4060)
{
	std::map<int,AMOUNT_INFO>::iterator iter = m_DEFPercentList.find(SKID);
	if( iter != m_DEFPercentList.end() )
	{
		if( abs(val) < abs(iter->second.amount) )
			return;

		m_characterInfo.DEFPercent -= iter->second.amount;
	}

	m_characterInfo.DEFPercent += val;
	if( m_characterInfo.DEFPercent < 0 )
		m_characterInfo.DEFPercent = 0;

	if( time != 9999 )
		time += timeGetTime();

	AMOUNT_INFO* info = &m_DEFPercentList[SKID];
	info->time = time;
	info->amount = val;
}


void CNPC::ResetATKPercentInfo(int SKID) // 4262-4272 (4063-4073)
{
	std::map<int,AMOUNT_INFO>::iterator iter = m_ATKPercentList.find(SKID);
	if( iter == m_ATKPercentList.end() )
		return;

	m_characterInfo.ATKPercent -= iter->second.amount;
	iter->second.time = 0;
	iter->second.amount = 0;

	this->UpdateParameterValue(VAR_STATUSATTACKPOWER, 0);
}


void CNPC::ResetDEFPercentInfo(int SKID) // 4275-4284 (4076-4085)
{
	std::map<int,AMOUNT_INFO>::iterator iter = m_DEFPercentList.find(SKID);
	if( iter == m_DEFPercentList.end() )
		return;

	m_characterInfo.DEFPercent -= iter->second.amount;
	iter->second.time = 0;
	iter->second.amount = 0;
}


int CNPC::GetEmblemVersion() // 4288-4306 (4089-4098)
{
	if( m_characterInfo.GuildID == 0 )
		return 0;
	
	CGuild* g = g_ZGuildMgr.CGuildMgr::SearchGuild(m_characterInfo.GuildID);
	if( g == NULL )
		return 0;

	return g->CGuild::GetEmblemVersion();
}


BOOL CNPC::SpawnMyMob(unsigned long spriteType) // 4309-4354 (4101-4146)
{
	MONSPAWN_SETINFO* info = g_monParameter.CMonParameterMgr::GetMonSpawnInfo(spriteType);
	if( info == NULL )
		return FALSE;
	
	const char* npcName = g_monParameter.CMonParameterMgr::GetMonsterName(info->spriteType);
	if( npcName == NULL )
		return FALSE;

	PACKET_NZ_NEWNPC packet;
	packet.NAID = 0;
	packet.xSize = 0;
	packet.ySize = 0;
	packet.force = 1;
	packet.direction = 0;
	packet.RegenMinTime = 1;
	packet.RegenMaxTime = 1;
	packet.RegenType = 0;
//	packet.sizeType = 0;

	for( int i = 0; i < info->count; ++i )
	{
		packet.xPos = static_cast<short>(m_pathInfo.m_moveInfo.xPos);
		packet.yPos = static_cast<short>(m_pathInfo.m_moveInfo.yPos);
		packet.spriteType = static_cast<short>(info->spriteType);
		packet.npcType = static_cast<unsigned char>(info->npcType);
		memcpy_s(packet.mapName, sizeof(packet.mapName), m_characterInfo.mapName, sizeof(m_characterInfo.mapName)); packet.mapName[countof(packet.mapName)-1] = '\0';
		memcpy_s(packet.NPCName, sizeof(packet.NPCName), npcName, 24); packet.NPCName[countof(packet.NPCName)-1] = '\0';

		CNPC* npc = CCharacterMgr::GetObj()->CCharacterMgr::AddNPC(&packet, this->GetAccountID(), 0);
		if( npc != NULL && info->npcType == MONSTER_TYPE_24 )
			npc->CNPC::SetSpeed(this->GetSpeed()); // inherit
	}

	return TRUE;
}


BOOL CNPC::IsSiegeMode() // ??? (4150-4152)
{
	return this->IsItPossible(MAPPROPERTY_SIEGE);
}


void CNPC::NotifyParameter(unsigned short type, int count) // ??? (4157-4159)
{
}


int CNPC::SetEffective(int index, int tm, int val1, int val2, int val3, BOOL isSend) // 4380-5003 (4167-4680)
{
	return 0;
	//TODO
}


COMMAND_QUEUE* CNPC::SearchCommand(unsigned long commandID) // 4653-4658 (4416-4425)
{
	for( std::list<COMMAND_QUEUE>::iterator iter = m_commandQueue.begin(); iter != m_commandQueue.end(); ++iter )
		if( iter->commandID == commandID )
			return &*iter;

	return NULL;
}


void CNPC::OnResetMyMob() // 5014-5019 (4691-4703)
{
	for( std::list<MYMOBDATA>::iterator it = m_myMobList.begin(); it != m_myMobList.end(); ++it )
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(this, it->AID, CM_DISAPPEAR, 1, 0, 0, 0);

	m_myMobList.clear();
}


void CNPC::OnShowEffect(int effect) // 5171-5177 (4907-4913)
{
	PACKET_ZC_NOTIFY_EFFECT2 outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_EFFECT2;
	outpacket.AID = this->GetAccountID();
	outpacket.effectID = effect;
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


void CNPC::OnShowEffect3(int effect, int numdata) // 5180-5187 (4916-4923)
{
	PACKET_ZC_NOTIFY_EFFECT3 outpacket;
	outpacket.PacketType = HEADER_ZC_NOTIFY_EFFECT3;
	outpacket.AID = this->GetAccountID();
	outpacket.effectID = effect;
	outpacket.numdata = numdata;
	this->CCharacter::MultiCast((char*)&outpacket, sizeof(outpacket));
}


void CNPC::OnShowScript(const char* In_Msg) // 5195-5207
{
	//TODO
}


void CNPC::OnChangeStatusAmount(int SKID, unsigned short type, unsigned long time, int amount) // 5336-5370
{
	//TODO
}


void CNPC::NotifyStatusAmount(unsigned short type, int amount) // 5373-5375 (5088-5090)
{
	//TODO
}


bool CNPC::ApplyStatusAmount(unsigned short type, int& amount) // 5378-5451 (5093-5166)
{
	return false;
	//TODO
}


bool CNPC::IsGroundEffective(int index, int& SKID, bool& isPlaySolo) // 5454-5483 (5169-5195)
{
	return false;
	//TODO
}


void CNPC::ProcessGroundEffective(int index, int SKID, bool isPlaySolo) // 5486-5503 (5198-5202)
{
	//TODO
}


int CNPC::GetMaxHP() // 5508-5516 (5207-5215)
{
	return 0;
	//TODO
}


int CNPC::GetMaxSP() // ??? (5218-5220)
{
	return 0;
}


short CNPC::GetAvoidPercent_Client() // 5524-5530 (5223-5229)
{
	return 0;
	//TODO
}


short CNPC::GetDexValue() // ??? (5232-5234)
{
	return m_characterInfo.Dex + m_characterInfo.DexAmount;
}


short CNPC::GetIntValue() // ??? (5237-5239)
{
	return m_characterInfo.Int + m_characterInfo.IntAmount;
}


void CNPC::Send(const int in_Length, char* in_pBuffer) // ??? (5253-5255)
{
}


void CNPC::OnMsgFromItemServer(unsigned long AID, CITZMsg* reqMsg) // 5559-5592 (5258-5291)
{
	//TODO
}


void CNPC::Chat(const char* buf, unsigned long color) // 5595-5612 (5294-5315)
{
	if( buf == NULL )
		return;

	char text[1024] = {};
	sprintf_s(text, countof(text), "%s : %s", m_characterInfo.accountName, buf);

	PACKET_ZC_NPC_CHAT p;
	p.PacketType = HEADER_ZC_NPC_CHAT;
	p.packetLength = sizeof(p) + strlen(text) + 1;
	p.accountID = this->GetAccountID();
	p.color = color;

	char packet[1024] = {};
	memcpy_s(packet, sizeof(packet), &p, sizeof(p));
	memcpy_s(packet + sizeof(p), sizeof(packet) - sizeof(p), text, strlen(text) + 1);
	this->CCharacter::MultiCast(packet, p.packetLength);
}


char CNPC::GetCampID() // 5616-5634 (5319-5337)
{
	if( m_myParentAID != 0 )
	{
		CCharacter* parent = CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(m_myParentAID, UNKNOWN_TYPE);
		if( parent != NULL )
		{
			int type = parent->GetType();
			if( type == PC_TYPE || type == NPC_MOB_TYPE )
				return parent->GetCampID();
		}
	}

	return m_characterInfo.campID;
}


void CNPC::SetCampID(char campID)
{
	m_characterInfo.campID = campID;
}


void CNPC::SetOnShowEFST(int value) // 583.h
{
	//TODO
}


void CNPC::SetOffShowEFST(int value) // 584.h
{
	//TODO
}


void CNPC::SetUseTomb(const bool bUse)
{
	m_TombInfo.bUse = bUse;
}


bool CNPC::GetUseTomb()
{
	return m_TombInfo.bUse;
}


void CNPC::DisappearBossTomb() // 5776-5782
{
	PACKET_ZC_NOTIFY_VANISH packet;
	packet.PacketType = HEADER_ZC_NOTIFY_VANISH;
	packet.GID = this->GetAccountID();
	packet.type = VT_DEAD;
	this->CCharacter::MultiCast((char*)&packet, sizeof(packet));
}


bool CNPC::OpSKToChar_SKID_ML_DEVOTION(CCharacter* in_TargetCH, MSG_TYPE4_FIVEDWORD* in_pData) // 1604-1606 (NPC2nd.cpp)
{
	return false;
}


void CNPC::OpSKToSelf_SKID_ML_DEFENDER(const int in_SKlevel) // 2406-2408 (NPC2nd.cpp)
{
	this->SetEffective(EFST_DEFENDER, 180000, in_SKlevel, 0, 0, 0);
}


void CNPC::OpSKToSelf_SKID_MER_MAGNIFICAT(const int in_SKLevel, const int in_EFST, const int in_EFST_time, const int in_EFST_value) // 2415-2417 (NPC2nd.cpp)
{
}


void CNPC::OpSKToSelf_SKID_MER_AUTOBERSERK() // 2420-2425 (NPC2nd.cpp)
{
	if( this->GetEffective(EFST_AUTOBERSERK, 0) == 0 )
		this->SetEffective(EFST_AUTOBERSERK, 9999, 1, 0, 0, 1);
	else
		this->ResetEffective(EFST_AUTOBERSERK, 0);
}


int CNPC::SplashAttack2(int plusATTPower, PosInfo dest, int type, int halfWidth, int height, MSG_TYPE1_TWODWORD* msgData, int count, int plusHitPercent, PosInfo* specialSrc) // 3481-3641 (NPC2nd.cpp)
{
	return 0;
	//TODO
}


void CNPC::DetectHidingCharacter(int range, SKILLATTACK_MSG* msg, int plusAttPower, int deltaX, int deltaY) // 5703-5802 (NPC2nd.cpp)
{
	//TODO
}


int CNPC::IsRechargeTime() // 5829-5849 (NPC2nd.cpp)
{
	return 0;
	//TODO
}


short CNPC::SplashAttack(int val1, short xPos, short yPos, int type, int range, int rangeIn, unsigned long exceptAID, void* msgDataPtr, int val2, int count) // 5866-6103 (NPC2nd.cpp)
{
	return 0;
	//TODO
}


void CNPC::ModifyAttackPowerByEffective(CCharacter* ch, int attackProperty, int& damage) // 6670-6737 (NPC2nd.cpp)
{
	//TODO
}


void CNPC::SkillUseAck(unsigned short SKID, unsigned short NUM, bool result, unsigned char cause) // 6786-6796 (NPC2nd.cpp)
{
	//TODO
}


void CNPC::ApplyExtraDEF(int& def, CCharacter* in_cpAtkerCH) // 513-549 (NPCFormula_Physics.cpp)
{
	//TODO
}


int CNPC::GetAttackFinalDamage(ATTACK_INFO* info) // 566.h
{
	return this->CNPC::GetAttackFinalDamage(info->target, info->plusATTPowerPercent, info->plusATTSuccessPercent, info->SKID, info->skillProperty, info->isRangeAttack);
}


int CNPC::GetAttackFinalDamage(CCharacter* other, int plusATKPercent, int plusHITPercent, unsigned short SKID, int SKProperty, int isRNGATK) // 22-24 (NPCFormula_Physics.cpp)
{
	return this->CNPC::GetPhysicsFinalDamage(other, plusATKPercent, plusHITPercent, SKID, SKProperty, isRNGATK);
}


int CNPC::GetPhysicsFinalDamage(CCharacter* in_cpTarget, int in_PlusATKPercent, int in_PlusHITPercent, unsigned short in_SKID, int in_SKATKProperty, int in_IsRangeAttack) // 35-64 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


int CNPC::GetAttackPoint(CCharacter* other, unsigned short SKID, int property) // 67-69 (NPCFormula_Physics.cpp)
{
	return this->CNPC::GetPhysicsBaseATKPower(other, SKID, property);
}


int CNPC::GetPhysicsBaseATKPower(CCharacter* in_cpTarget, unsigned short in_SKID, int in_ATKProperty) // 77-97 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


BOOL CNPC::ProcessRevengeEnemy(CCharacter* in_cpTarget) // 116-236 (NPCFormula_Physics.cpp)
{
	return FALSE;
	//TODO
}


short CNPC::GetStatusDef() // 241-253 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


short CNPC::GetDefencePoint() // 259-282 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


int CNPC::GetModifiedTargetItemMDEF2(CCharacter* in_cpTargetCH) // 286-290 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


int CNPC::GetAvoidableSuccessPercent() // 295-338 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


short CNPC::GetAttSucPercent() // 342-347 (NPCFormula_Physics.cpp)
{
	return this->GetBaseHit() + m_charBuff2.CCharBuff::GetParameterValue(VAR_HITSUCCESSVALUE) + this->GetEffective(EFST_CONCENTRATION, 0);
}


short CNPC::GetAttackSuccessPercent(CCharacter* other, const int in_SKATKPattern, int isRNGATK, const int in_SKID) // 374-429 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


int CNPC::GetModifiedTargetStatusDEF2(CCharacter* in_cpTargetCH) // 433-470 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


int CNPC::GetModifiedTargetStatusDEF(CCharacter* target) // 473-509 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


int CNPC::GetItemAttPower() // 554-575 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


int CNPC::GetStatusAttPower() // 578-580 (NPCFormula_Physics.cpp)
{
	return 0;
	//TODO
}


short CNPC::GetItemMagicDef() // 112-121 (NPCFormula_Magic.cpp)
{
	return 0;
	//TODO
}


short CNPC::GetStatusMagicDef() // 126-133 (NPCFormula_Magic.cpp)
{
	return 0;
	//TODO
}


int CNPC::GetMagicAttPower() // 138-158 (NPCFormula_Magic.cpp)
{
	return 0;
	//TODO
}


void CNPC::ApplyExtraMDEF(int& mdef) // 163-179 (NPCFormula_Magic.cpp)
{
	//TODO
}


int CNPC::SkillAttack(SKILLATTACK_MSG* in_Msg, int in_PlusATKPercent, int in_PlusHITPercent, const bool in_bHideSkill) // 42-244 (NPCSkillAttack.cpp)
{
	return 0;
	//TODO
}
