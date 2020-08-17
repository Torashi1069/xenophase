#include "ItemInfo.h"
#include "GameActor.h"
#include "GameMode.h"
#include "GameWorld.h"
#include "Globals.h"
#include "ModeMgr.h"
#include "Session.h"
#include "Window/UIWindow.h"
#include "Window/UIWindowMgr.h"


CSession& g_session = VTOR<CSession>(SymDB::Find("g_session"));


hook_func<void (CSession::*)(void)> CSession::_Init("CSession::Init");
void CSession::Init(void)
{
	return (this->*_Init)();
}


hook_func<void (CSession::*)(void)> CSession::_Create("CSession::Create");
void CSession::Create(void)
{
	return (this->*_Create)();
}


hook_func<char* (CSession::*)(int job, int* head, int sex, int accessory, char* buf)> CSession::_GetAccessoryActName("CSession::GetAccessoryActName");
char* CSession::GetAccessoryActName(int job, int* head, int sex, int accessory, char* buf)
{
	return (this->*_GetAccessoryActName)(job, head, sex, accessory, buf);

	//TODO
}


hook_func<void (CSession::*)(void)> CSession::_InitPetTalkTable("CSession::InitPetTalkTable");
void CSession::InitPetTalkTable(void)
{
	return (this->*_InitPetTalkTable)();

	//TODO
}


hook_func<void (CSession::*)(void)> CSession::_InvalidateBasicWnd("CSession::InvalidateBasicWnd");
void CSession::InvalidateBasicWnd(void)
{
	return (this->*_InvalidateBasicWnd)();

	CGameMode* gamemode = g_modeMgr.CModeMgr::GetGameMode();
	if( gamemode == NULL )
		return;

	UIWindow* wnd = (UIWindow*)g_windowMgr.UIWindowMgr::GetBasicInfoWnd();
	if( wnd != NULL )
	{
		wnd->Invalidate();
		wnd->UIWindow::InvalidateChildren();
	}

	gamemode->CGameMode::InvalidatePlayerGage();
}


hook_func<void (CSession::*)(void)> CSession::_InitTalkTypeTable("CSession::InitTalkTypeTable");
void CSession::InitTalkTypeTable(void)
{
	return (this->*_InitTalkTypeTable)();

	//TODO
}


hook_func<int (CSession::*)(const char* chatBuf, TALKTYPE* talkType, mystd::string param[3])> CSession::_GetTalkType("CSession::GetTalkType");
int CSession::GetTalkType(const char* chatBuf, TALKTYPE* talkType, mystd::string param[3])
{
	return (this->*_GetTalkType)(chatBuf, talkType, param);

	//TODO
}


hook_func<TALKTYPE (CSession::*)(const char* command)> CSession::_GetNoParamTalkType("CSession::GetNoParamTalkType");
TALKTYPE CSession::GetNoParamTalkType(const char* command)
{
	return (this->*_GetNoParamTalkType)(command);

	//TODO
}


hook_func<void (CSession::*)(void)> CSession::_ChangeXorValue("CSession::ChangeXorValue");
void CSession::ChangeXorValue(void)
{
	return (this->*_ChangeXorValue)();
}


hook_func<void (CSession::*)(void)> CSession::_WriteOptionToLuaFile("CSession::WriteOptionToLuaFile");
void CSession::WriteOptionToLuaFile(void)
{
	return (this->*_WriteOptionToLuaFile)();
}


hook_func<void (CSession::*)(void)> CSession::_ClearEquipItem("CSession::ClearEquipItem");
void CSession::ClearEquipItem(void)
{
	return (this->*_ClearEquipItem)();
}


hook_func<void (CSession::*)(void)> CSession::_ClearEquipItemInInventory("CSession::ClearEquipItemInInventory");
void CSession::ClearEquipItemInInventory(void)
{
	return (this->*_ClearEquipItemInInventory)();
}


hook_func<BOOL (CSession::*)(int itemId)> CSession::_IsPetEgg("CSession::IsPetEgg");
BOOL CSession::IsPetEgg(int itemId)
{
	return (this->*_IsPetEgg)(itemId);

	return ( itemId > 9000 && itemId <= 9099 );
}


hook_func<void (CSession::*)(ITEM_INFO* itemInfo)> CSession::_SetItem("CSession::SetItem");
void CSession::SetItem(ITEM_INFO* itemInfo)
{
	return (this->*_SetItem)(itemInfo);
}


hook_func<bool (CSession::*)(ITEM_INFO* itemInfo)> CSession::_AddItem("CSession::AddItem");
bool CSession::AddItem(ITEM_INFO* itemInfo)
{
	return (this->*_AddItem)(itemInfo);
}


hook_func<void (CSession::*)(unsigned long index, int numItem)> CSession::_DecItem("CSession::DecItem");
void CSession::DecItem(unsigned long index, int numItem)
{
	return (this->*_DecItem)(index, numItem);
}


hook_func<bool (CSession::*)(ITEM_INFO* itemInfo)> CSession::_AddEquipItem("CSession::AddEquipItem");
bool CSession::AddEquipItem(ITEM_INFO* itemInfo)
{
	return (this->*_AddEquipItem)(itemInfo);
}


hook_func<bool (CSession::*)(ITEM_INFO* itemInfo)> CSession::_AddStoreItem("CSession::AddStoreItem");
bool CSession::AddStoreItem(ITEM_INFO* itemInfo)
{
	return (this->*_AddStoreItem)(itemInfo);
}


BOOL CSession::IsMerOrHomun(int job)
{
	return ( job > JT_MER_BEGIN && job < JT_MER_LAST );
}


bool CSession::IsMyHomunGID(int GID)
{
	if( GID == -1 )
		return false;

	return ( GID == m_homunGID );
}


bool CSession::IsMyMerGID(int GID)
{
	if( GID == -1 )
		return false;

	return ( GID == m_merGID );
}


BOOL CSession::IsPc(int job)
{
	return this->CSession::IsThisPC(job);
}


BOOL CSession::IsThisPC(int job)
{
	return ( job > JT_2004_JOB_BEGIN && job < JT_MER_BEGIN || job >= JT_NOVICE && job < JT_USER_LAST );
}


char* CSession::GetPetAccActName(int accId)
{
    switch( accId )
    {
        case ITEM_10001_PETACC_BAPHO          : return "몬스터\\BAPHOMET_뼉다구모자.act";
        case ITEM_10002_PETACC_CHONCHON       : return "몬스터\\chocho_방독면.act";
        case ITEM_10003_PETACC_DESERTWOLF     : return "몬스터\\DESERT_WOLF_B_우주복머리.act";
        case ITEM_10004_PETACC_DEVIRUCHI      : return "몬스터\\DEVIRUCHI_젖꼭지.act";
        case ITEM_10005_PETACC_DOKEBI         : return "몬스터\\DOKEBI_아후로머리.act";
        case ITEM_10006_PETACC_ISIS           : return "몬스터\\isis_클레오파트라머리띠.act";
        case ITEM_10007_PETACC_LUNATIC        : return "몬스터\\lunatic_리본.act";
        case ITEM_10008_PETACC_MUNAK          : return "몬스터\\munak_요술봉.act";
        case ITEM_10009_PETACC_ORCWARRIOR     : return "몬스터\\ork_warrior_꽃.act";
        case ITEM_10010_PETACC_PECOPECO       : return "몬스터\\pecopeco_냄비.act";
        case ITEM_10011_PETACC_PETITE         : return "몬스터\\PETIT_별.act";
        case ITEM_10012_PETACC_PICKY          : return "몬스터\\picky_알껍질.act";
        case ITEM_10013_PETACC_PORING         : return "몬스터\\poring_책가방.act";
        case ITEM_10014_PETACC_ROCKER         : return "몬스터\\rocker_메뚜기안경.act";
        case ITEM_10015_PETACC_SAVAGEBABE     : return "몬스터\\savage_babe_레이스.act";
        case ITEM_10016_PETACC_SOHEE          : return "몬스터\\SOHEE_방울.act";
        case ITEM_10017_PETACC_SPORE          : return "몬스터\\spore_원주민치마.act";
        case ITEM_10018_PETACC_YOYO           : return "몬스터\\yoyo_머리띠.act";
        case ITEM_10019_PETACC_SMOKIE         : return "몬스터\\smokie_머플러.act";
        case ITEM_10020_PETACC_BONGUN         : return "몬스터\\bon_gun_영환도사검.act";
        case ITEM_10021_PETACC_BACSOJIN       : return "몬스터\\BACSOJIN_동그란머리장식.act";
        case ITEM_10022_PETACC_CIVILSERVANT   : return "몬스터\\CIVIL_SERVANT_금빛귀걸이.act";
        case ITEM_10023_PETACC_LEAFCAT        : return "몬스터\\LEAF_CAT_초록복주머니.act";
        case ITEM_10024_PETACC_LOLIRURI       : return "몬스터\\LOLI_RURI_패션안경.act";
        case ITEM_10025_PETACC_MARIONETTE     : return "몬스터\\MARIONETTE_별모양머리띠.act";
        case ITEM_10026_PETACC_SHINOBI        : return "몬스터\\SHINOBI_두루마기용술.act";
        case ITEM_10027_PETACC_WHISPER        : return "몬스터\\WHISPER_영혼고리_.act";
        case ITEM_10028_PETACC_GOBLINLEADER   : return "몬스터\\GOBLIN_LEADER_멋진휘장.act";
        case ITEM_10029_PETACC_WICKEDNYMPH    : return "몬스터\\WICKED_NYMPH_옥노리개.act";
        case ITEM_10030_PETACC_MIYABININGYO   : return "몬스터\\MIYABI_NINGYO_여름부채.act";
        case ITEM_10031_PETACC_DULLAHAN       : return "몬스터\\DULLAHAN_죽음의고리.act";
        case ITEM_10032_PETACC_MEDUSA         : return "몬스터\\MEDUSA_여왕의코로넷.act";
        case ITEM_10033_PETACC_STONESHOOTER   : return "몬스터\\STONE_SHOOTER_아프로헤어.act";
        case ITEM_10034_PETACC_INCUBUS        : return "몬스터\\INCUBUS_무도회가면.act";
        case ITEM_10035_PETACC_GOLEM          : return "몬스터\\GOLEM_태엽.act";
        case ITEM_10036_PETACC_NIGHTMARETERROR: return "몬스터\\NIGHTMARE_TERROR_지옥의뿔.act";
        case ITEM_10037_PETACC_SUCCUBUS       : return "몬스터\\SUCCUBUS_검은나비가면.act";
        case ITEM_10038_PETACC_IMP            : return "몬스터\\IMP_뿔보호대.act";
        default                               : return "몬스터\\chocho_방독면.act";
    };
}


int CSession::IsSiegeMode()
{
	return g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->CWorld::IsSiegeMode();
}


int CSession::IsGuardian(int job)
{
	return ( job == JT_ARCHER_GUARDIAN || job == JT_KNIGHT_GUARDIAN || job == JT_SOLDIER_GUARDIAN );
}


void CSession::SetServerTime(DWORD startTime)
{
	m_numLatePacket = 0;
	m_diffTime = timeGetTime() - startTime;
}


hook_func<void (CSession::*)(unsigned long startTime)> CSession::_UpdateServerTime("CSession::UpdateServerTime");
void CSession::UpdateServerTime(unsigned long startTime)
{
	return (this->*_UpdateServerTime)(startTime);
}


void CSession::SetPlayerPosDir(int x, int y, int dir)
{
	m_dir = dir;
	m_posX = x;
	m_posY = y;
}


int CSession::IsAttack(int act)
{
	return ( act == ACTION_ATTACK || act == ACTION_ATTACK_NOMOTION );
}


int CSession::GetPetHungryState(int Hunger)
{
	if( Hunger > 90 && Hunger <= 100 )
		return 4;
	else
	if( Hunger > 75 && Hunger <= 90 )
		return 3;
	else
	if( Hunger > 25 && Hunger <= 75 )
		return 2;
	else
	if( Hunger > 10 && Hunger <= 25 )
		return 1;
	else //( Hunger <= 10 )
		return 0;
}


int CSession::GetPetFriendlyState(int Friendly)
{
	if( Friendly != 0 )
		Friendly = Friendly / 10;

	if( Friendly > 90 && Friendly <= 100 )
		return 4;
	else
	if( Friendly > 75 && Friendly <= 90 )
		return 3;
	else
	if( Friendly > 25 && Friendly <= 75 )
		return 2;
	else
	if( Friendly > 10 && Friendly <= 25 )
		return 1;
	else //( Friendly <= 10 )
		return 0;
}


hook_func<int (CSession::*)(int job, int act, int hungry)> CSession::_GetPetTalkNumber("CSession::GetPetTalkNumber");
int CSession::GetPetTalkNumber(int job, int act, int hungry)
{
	return (this->*_GetPetTalkNumber)(job, act, hungry);
}


hook_func<void (CSession::*)(int job, int stateId, int arg1, char* speak, unsigned long gid)> CSession::_GetMonsterTalkInfo("CSession::GetMonsterTalkInfo");
void CSession::GetMonsterTalkInfo(int job, int stateId, int arg1, char* speak, unsigned long gid)
{
	return (this->*_GetMonsterTalkInfo)(job, stateId, arg1, speak, gid);
}


BOOL CSession::IsFriendName(const char* cName)
{
	mystd::list<FRIEND_INFO>::const_iterator it;
	for( it = m_friendList.begin(); it != m_friendList.end(); ++it )
		if( it->characterName == cName )
			break; // found.

	return ( it != m_friendList.end() ) ? TRUE : FALSE;
}


hook_func<BOOL (CSession::*)(const char* cName)> CSession::_IsGuildMember("CSession::IsGuildMember");
BOOL CSession::IsGuildMember(const char* cName)
{
	return (this->*_IsGuildMember)(cName);
}


BOOL CSession::IsCheatName(const char* cName)
{
	mystd::list<FRIEND_INFO>::const_iterator it;
	for( it = m_friendList.begin(); it != m_friendList.end(); ++it )
		if( !this->CSession::CompareTwoNames(cName, it->characterName.c_str()) )
			break;

	return ( it != m_friendList.end() ) ? TRUE : FALSE;
}


hook_func<BOOL (CSession::*)(const char* cName)> CSession::_IsCheatGuildName("CSession::IsCheatGuildName");
BOOL CSession::IsCheatGuildName(const char* cName)
{
	return (this->*_IsCheatGuildName)(cName);
}


hook_val<const char*> szCharNameEcryption("szCharNameEcryption"); // = "가나다라마바사아자차카타파하가나다라마바사아자차카타파하"; //FIXME: length < 64
const char* CSession::GetCharName()
{
	static char cName[64];

    memcpy(cName, m_cName, sizeof(cName));
	for( size_t i = 0; i < sizeof(cName); ++i )
		cName[i] ^= szCharNameEcryption[i];

    return cName;
}


void CSession::SetCharName(const char* cName)
{
	memcpy(m_cName, cName, sizeof(m_cName));
	for( size_t i = 0; i < sizeof(m_cName); ++i )
		m_cName[i] ^= szCharNameEcryption[i];
}


hook_func<BOOL (CSession::*)(const char* cName1, const char* cName2)> CSession::_CompareTwoNames("CSession::CompareTwoNames");
BOOL CSession::CompareTwoNames(const char* cName1, const char* cName2)
{
	return (this->*_CompareTwoNames)(cName1, cName2);
}


const char* CSession::GetItemResName_WithId(const char* itemName, BOOL isIdentified)
{
	if( isIdentified )
		return ITEM_INFO::GetItemDesc(itemName).identifiedResourceName;
	else
		return ITEM_INFO::GetItemDesc(itemName).unidentifiedResourceName;
}


void CSession::GetItemBitmapFileName(const char* itemName, char* buf, BOOL isIdentified)
{
	sprintf(buf, "유저인터페이스\\item\\%s.bmp", this->CSession::GetItemResName_WithId(itemName, isIdentified));
}


hook_func<void (CSession::*)(int skillId, int& beginEffectId, int& motionType, int property, int sjob)> CSession::_GetSkillActionInfo2("CSession::GetSkillActionInfo2");
void CSession::GetSkillActionInfo2(int skillId, int& beginEffectId, int& motionType, int property, int sjob)
{
	return (this->*_GetSkillActionInfo2)(skillId, beginEffectId, motionType, property, sjob);

	//TODO
}


BOOL CSession::IsPartyMember(int AID, bool bCheckOnline)
{
	mystd::list<FRIEND_INFO>::const_iterator it;
	for( it = m_partyList.begin(); it != m_partyList.end(); ++it )
		if( it->AID == AID )
			break;

	if( it == m_partyList.end() )
		return FALSE; // not in party

	if( bCheckOnline && it->state != 0 )
		return FALSE; // member is offline

	return TRUE;
}


BOOL CSession::IsMonster(CGameActor* pActor)
{
	return pActor != NULL
	    && ( pActor->CGameActor::GetJob() < JT_EL_AGNI_S || pActor->CGameActor::GetJob() > JT_EL_TERA_L )
	    && pActor->m_objectType != NPC_MERSOL_TYPE
	    && pActor->CGameActor::GetJob() > JT_MON_BEGIN
	    && pActor->CGameActor::GetJob() < JT_2004_JOB_BEGIN;
}


hook_func<void (CSession::*)(const char* Name, int skillId, int& act, int& loopType)> CSession::_GetMonsterSkillInfo("CSession::GetMonsterSkillInfo");
void CSession::GetMonsterSkillInfo(const char* Name, int skillId, int& act, int& loopType)
{
	return (this->*_GetMonsterSkillInfo)(Name, skillId, act, loopType);

	//TODO
}


BOOL CSession::IsMer(int job)
{
	return ( job > JT_MER_ARCHER01 && job < JT_MER_LAST ); //FIXME: shouldn't that be >= ?
}


hook_func<int (CSession::*)(const char* szOptionName, int nDefault)> CSession::_GetOptionValue("CSession::GetOptionValue");
int CSession::GetOptionValue(const char* szOptionName, int nDefault)
{
	return (this->*_GetOptionValue)(szOptionName, nDefault);

	//TODO
}


unsigned long CSession::GetAid()
{
	return m_aid;
}


unsigned long CSession::GetGid()
{
	return m_gid;
}


void CSession::SetAid(unsigned long aid)
{
	m_aid = aid;
}


void CSession::SetGid(unsigned long gid)
{
	m_gid = gid;
}


////////////////////////////////////////


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateBurrow("IsEffectStateBurrow");
bool __cdecl IsEffectStateBurrow(unsigned long effectState)
{
	return (_IsEffectStateBurrow)(effectState);

	return (effectState >> 1) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateHiding("IsEffectStateHiding");
bool __cdecl IsEffectStateHiding(unsigned long effectState)
{
	return (_IsEffectStateHiding)(effectState);

	return (effectState >> 2) & 1;
}


hook_func<bool (__cdecl *)(unsigned int effectState)> _IsEffectStateSpecialHiding("IsEffectStateSpecialHiding");
bool __cdecl IsEffectStateSpecialHiding(unsigned int effectState)
{
	return (_IsEffectStateSpecialHiding)(effectState);

	return (effectState >> 6) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateOrcFace("IsEffectStateOrcFace");
bool __cdecl IsEffectStateOrcFace(unsigned long effectState)
{
	return (_IsEffectStateOrcFace)(effectState);

	return (effectState >> 11) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateFootPrint("IsEffectStateFootPrint");
bool __cdecl IsEffectStateFootPrint(unsigned long effectState)
{
	return (_IsEffectStateFootPrint)(effectState);

	return (effectState >> 14) & 1;
}
