#include "GameMode.h"
#include "GameWorld.h"
#include "Globals.h"
#include "Insult.h"
#include "ModeMgr.h"
#include "MsgStrings.h"
#include "Player.h"
#include "Session.h"
#include "Base/Util.h"
#include "Device/Sound.h"
#include "Window/UIFrameWnd2.h"
#include "Window/UIMessengerWnd.h"
#include "common.h" // CharPrtLess, DComp, IListComp
////////////////////////////////////////


int& initCnt = VTOR<int>(SymDB::Add("initCnt", SAKEXE, "initCnt")); // = ?; //FIXME: uninitialized


////////////////////////////////////////


CSession::CSession(void) // line 36
{
}


CSession::~CSession(void) // line 40
{
	this->CSession::RerecordProhibitLog();
	m_reqAccountInfo.clear();
	m_chatProhibitLog.clear();
	m_recievedAccountName.clear();
}


hook_method<void (CSession::*)(void)> CSession::_Init(SAKEXE, "CSession::Init");
void CSession::Init(void) // line 48
{
	return (this->*_Init)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_Create(SAKEXE, "CSession::Create");
void CSession::Create(void) // line 535
{
	return (this->*_Create)();

	srand(timeGetTime());
	this->CSession::ChangeXorValue();
	this->CSession::InitTable(); //inlined
	Trace("세션 에서 테이블 초기화 끝");
	this->CSession::InitOptionWithRegistry();
}


hook_method<void (CSession::*)(void)> CSession::_InitTable(SAKEXE, "CSession::InitTable");
void CSession::InitTable(void) // line 557
{
	return (this->*_InitTable)();

	++initCnt;
	this->CSession::InitPcNameTable();
	this->CSession::InitWeaponSwingWaveName();
	this->CSession::InitWeaponHitWaveName();
	this->CSession::InitJobHitWaveName();
	this->CSession::InitEnableObjLightMapTable();
	this->CSession::InitMp3NameTable();
	this->CSession::InitIndoorRswTable(); //inlined
	this->CSession::InitSkillEffectIdTable();
	this->CSession::InitLanguageTable(); //inlined
	this->CSession::InitFogParameterTable();
	this->CSession::InitShadowFactorWithJob();
	this->CSession::InitJobNameTable();
	this->CSession::InitSkillUseAfterDelayTable(); //inlined
	this->CSession::InitTalkTypeTable();
	this->CSession::InitVariables();
	this->CSession::ClearPurchaseItem();
	this->CSession::ClearSellItem();
	this->CSession::ClearShopItem();
	this->CSession::ClearStoreItem();
	m_skillInfoList.clear(); //???
	this->CSession::ClearFriend();
	this->CSession::ClearParty();
	this->CSession::ClearExchangeItemList();
	this->CSession::ClearOtherExchangeItemList();
	this->CSession::InitWhenServerMove();
	this->CSession::InitShortCutTextFromReg();
}


hook_method<void (CSession::*)(void)> CSession::_InitLanguageTable(SAKEXE, "CSession::InitLanguageTable");
void CSession::InitLanguageTable(void) // line 544
{
	return (this->*_InitLanguageTable)();

	InitMsgStrings();
	g_insultFilter.CInsultFilter::Load("manner.txt");
	this->CSession::InitPetTalkTable();
	this->CSession::InitMapNameTable();
	ITEM_INFO::InitItemInfoTables();
	SKILL_INFO::InitSkillInfoTables();
}


hook_method<void (CSession::*)(void)> CSession::_InitVariables(SAKEXE, "CSession::InitVariables");
void CSession::InitVariables(void) // line 2194
{
	return (this->*_InitVariables)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitPcNameTable(SAKEXE, "CSession::InitPcNameTable");
void CSession::InitPcNameTable(void) // line 622
{
	return (this->*_InitPcNameTable)();

	m_newPcJobNameTable.resize(96, "초보자");
	m_newPcJobNameTable[0] = "초보자";
	m_newPcJobNameTable[1] = "검사";
	m_newPcJobNameTable[2] = "마법사";
	m_newPcJobNameTable[3] = "궁수";
	m_newPcJobNameTable[4] = "성직자";
	m_newPcJobNameTable[5] = "상인";
	m_newPcJobNameTable[6] = "도둑";
	m_newPcJobNameTable[7] = "기사";
	m_newPcJobNameTable[8] = "프리스트";
	m_newPcJobNameTable[9] = "위저드";
	m_newPcJobNameTable[10] = "제철공";
	m_newPcJobNameTable[11] = "헌터";
	m_newPcJobNameTable[12] = "어세신";
	m_newPcJobNameTable[13] = "페코페코_기사";
	m_newPcJobNameTable[14] = "크루세이더";
	m_newPcJobNameTable[15] = "몽크";
	m_newPcJobNameTable[16] = "세이지";
	m_newPcJobNameTable[17] = "로그";
	m_newPcJobNameTable[18] = "연금술사";
	m_newPcJobNameTable[19] = "바드";
	m_newPcJobNameTable[20] = "무희";
	m_newPcJobNameTable[21] = "신페코크루세이더";
	m_newPcJobNameTable[23] = "슈퍼노비스";
	m_newPcJobNameTable[22] = "결혼";
	m_newPcJobNameTable[51] = "초보자";
	m_newPcJobNameTable[52] = "검사";
	m_newPcJobNameTable[53] = "마법사";
	m_newPcJobNameTable[54] = "궁수";
	m_newPcJobNameTable[55] = "성직자";
	m_newPcJobNameTable[56] = "상인";
	m_newPcJobNameTable[57] = "도둑";
	m_newPcJobNameTable[58] = "기사_H";
	m_newPcJobNameTable[59] = "프리스트_H";
	m_newPcJobNameTable[60] = "위저드_H";
	m_newPcJobNameTable[61] = "제철공_H";
	m_newPcJobNameTable[62] = "헌터_H";
	m_newPcJobNameTable[63] = "어세신_H";
	m_newPcJobNameTable[64] = "페코페코_기사_H";
	m_newPcJobNameTable[65] = "크루세이더_H";
	m_newPcJobNameTable[66] = "몽크_H";
	m_newPcJobNameTable[67] = "세이지_H";
	m_newPcJobNameTable[68] = "로그_H";
	m_newPcJobNameTable[69] = "연금술사_H";
	m_newPcJobNameTable[70] = "바드_H";
	m_newPcJobNameTable[71] = "무희_H";
	m_newPcJobNameTable[72] = "신페코크루세이더_H";
	m_newPcJobNameTable[73] = "초보자";
	m_newPcJobNameTable[74] = "검사";
	m_newPcJobNameTable[75] = "마법사";
	m_newPcJobNameTable[76] = "궁수";
	m_newPcJobNameTable[77] = "성직자";
	m_newPcJobNameTable[78] = "상인";
	m_newPcJobNameTable[79] = "도둑";
	m_newPcJobNameTable[80] = "기사";
	m_newPcJobNameTable[81] = "프리스트";
	m_newPcJobNameTable[82] = "위저드";
	m_newPcJobNameTable[83] = "제철공";
	m_newPcJobNameTable[84] = "헌터";
	m_newPcJobNameTable[85] = "어세신";
	m_newPcJobNameTable[86] = "페코페코_기사";
	m_newPcJobNameTable[87] = "크루세이더";
	m_newPcJobNameTable[88] = "몽크";
	m_newPcJobNameTable[89] = "세이지";
	m_newPcJobNameTable[90] = "로그";
	m_newPcJobNameTable[91] = "연금술사";
	m_newPcJobNameTable[92] = "바드";
	m_newPcJobNameTable[93] = "무희";
	m_newPcJobNameTable[94] = "신페코크루세이더";
	m_newPcJobNameTable[95] = "슈퍼노비스";

	m_newPcJobImfNameTable.resize(96, "초보자");
	m_newPcJobImfNameTable[0] = "초보자";
	m_newPcJobImfNameTable[1] = "검사";
	m_newPcJobImfNameTable[2] = "마법사";
	m_newPcJobImfNameTable[3] = "궁수";
	m_newPcJobImfNameTable[4] = "성직자";
	m_newPcJobImfNameTable[5] = "상인";
	m_newPcJobImfNameTable[6] = "도둑";
	m_newPcJobImfNameTable[7] = "기사";
	m_newPcJobImfNameTable[8] = "프리스트";
	m_newPcJobImfNameTable[9] = "위저드";
	m_newPcJobImfNameTable[10] = "제철공";
	m_newPcJobImfNameTable[11] = "헌터";
	m_newPcJobImfNameTable[12] = "어세신";
	m_newPcJobImfNameTable[13] = "페코페코_기사";
	m_newPcJobImfNameTable[14] = "크루세이더";
	m_newPcJobImfNameTable[15] = "몽크";
	m_newPcJobImfNameTable[16] = "세이지";
	m_newPcJobImfNameTable[17] = "로그";
	m_newPcJobImfNameTable[18] = "연금술사";
	m_newPcJobImfNameTable[19] = "바드";
	m_newPcJobImfNameTable[20] = "무희";
	m_newPcJobImfNameTable[21] = "신페코크루세이더";
	m_newPcJobImfNameTable[23] = "초보자";
	m_newPcJobImfNameTable[22] = "결혼";
	m_newPcJobImfNameTable[51] = "초보자";
	m_newPcJobImfNameTable[52] = "검사";
	m_newPcJobImfNameTable[53] = "마법사";
	m_newPcJobImfNameTable[54] = "궁수";
	m_newPcJobImfNameTable[55] = "성직자";
	m_newPcJobImfNameTable[56] = "상인";
	m_newPcJobImfNameTable[57] = "도둑";
	m_newPcJobImfNameTable[58] = "기사";
	m_newPcJobImfNameTable[59] = "프리스트";
	m_newPcJobImfNameTable[60] = "위저드";
	m_newPcJobImfNameTable[61] = "제철공";
	m_newPcJobImfNameTable[62] = "헌터";
	m_newPcJobImfNameTable[63] = "어세신";
	m_newPcJobImfNameTable[64] = "페코페코_기사";
	m_newPcJobImfNameTable[65] = "크루세이더";
	m_newPcJobImfNameTable[66] = "몽크";
	m_newPcJobImfNameTable[67] = "세이지";
	m_newPcJobImfNameTable[68] = "로그";
	m_newPcJobImfNameTable[69] = "연금술사";
	m_newPcJobImfNameTable[70] = "바드";
	m_newPcJobImfNameTable[71] = "무희";
	m_newPcJobImfNameTable[72] = "신페코크루세이더";
	m_newPcJobImfNameTable[73] = "초보자";
	m_newPcJobImfNameTable[74] = "검사";
	m_newPcJobImfNameTable[75] = "마법사";
	m_newPcJobImfNameTable[76] = "궁수";
	m_newPcJobImfNameTable[77] = "성직자";
	m_newPcJobImfNameTable[78] = "상인";
	m_newPcJobImfNameTable[79] = "도둑";
	m_newPcJobImfNameTable[80] = "기사";
	m_newPcJobImfNameTable[81] = "프리스트";
	m_newPcJobImfNameTable[82] = "위저드";
	m_newPcJobImfNameTable[83] = "제철공";
	m_newPcJobImfNameTable[84] = "헌터";
	m_newPcJobImfNameTable[85] = "어세신";
	m_newPcJobImfNameTable[86] = "페코페코_기사";
	m_newPcJobImfNameTable[87] = "크루세이더";
	m_newPcJobImfNameTable[88] = "몽크";
	m_newPcJobImfNameTable[89] = "세이지";
	m_newPcJobImfNameTable[90] = "로그";
	m_newPcJobImfNameTable[91] = "연금술사";
	m_newPcJobImfNameTable[92] = "바드";
	m_newPcJobImfNameTable[93] = "무희";
	m_newPcJobImfNameTable[94] = "신페코크루세이더";
	m_newPcJobImfNameTable[95] = "초보자";

	m_newPcSexNameTable.resize(2, "여");
	m_newPcSexNameTable[0] = "여";
	m_newPcSexNameTable[1] = "남";

	m_newPcHeadNameTable_M.resize(20, "2");
	m_newPcHeadNameTable_M[0] = "2";
	m_newPcHeadNameTable_M[1] = "2";
	m_newPcHeadNameTable_M[2] = "1";
	m_newPcHeadNameTable_M[3] = "7";
	m_newPcHeadNameTable_M[4] = "5";
	m_newPcHeadNameTable_M[5] = "4";
	m_newPcHeadNameTable_M[6] = "3";
	m_newPcHeadNameTable_M[7] = "6";
	m_newPcHeadNameTable_M[8] = "8";
	m_newPcHeadNameTable_M[9] = "9";
	m_newPcHeadNameTable_M[10] = "10";
	m_newPcHeadNameTable_M[11] = "12";
	m_newPcHeadNameTable_M[12] = "11";
	m_newPcHeadNameTable_M[13] = "13";
	m_newPcHeadNameTable_M[14] = "14";
	m_newPcHeadNameTable_M[15] = "15";
	m_newPcHeadNameTable_M[16] = "16";
	m_newPcHeadNameTable_M[17] = "17";
	m_newPcHeadNameTable_M[18] = "18";
	m_newPcHeadNameTable_M[19] = "19";

	m_newPcHeadNameTable_F.resize(20, "2");
	m_newPcHeadNameTable_F[0] = "2";
	m_newPcHeadNameTable_F[1] = "2";
	m_newPcHeadNameTable_F[2] = "4";
	m_newPcHeadNameTable_F[3] = "7";
	m_newPcHeadNameTable_F[4] = "1";
	m_newPcHeadNameTable_F[5] = "5";
	m_newPcHeadNameTable_F[6] = "3";
	m_newPcHeadNameTable_F[7] = "6";
	m_newPcHeadNameTable_F[8] = "12";
	m_newPcHeadNameTable_F[9] = "10";
	m_newPcHeadNameTable_F[10] = "9";
	m_newPcHeadNameTable_F[11] = "11";
	m_newPcHeadNameTable_F[12] = "8";
	m_newPcHeadNameTable_F[13] = "13";
	m_newPcHeadNameTable_F[14] = "14";
	m_newPcHeadNameTable_F[15] = "15";
	m_newPcHeadNameTable_F[16] = "16";
	m_newPcHeadNameTable_F[17] = "17";
	m_newPcHeadNameTable_F[18] = "18";
	m_newPcHeadNameTable_F[19] = "19";

	m_newAccessoryNameTable.resize(ACCESSORY_LAST, "");
	m_newAccessoryNameTable[ACCESSORY_NONE] = "";
	m_newAccessoryNameTable[ACCESSORY_GOGGLES] = "_고글";
	m_newAccessoryNameTable[ACCESSORY_CATTYHAIRBAND] = "_고양이머리띠";
	m_newAccessoryNameTable[ACCESSORY_GLASS] = "_글래스"; // changed
	m_newAccessoryNameTable[ACCESSORY_FLOWER] = "_꽃";
	m_newAccessoryNameTable[ACCESSORY_FLORALHAIRBAND] = "_꽃머리띠";
	m_newAccessoryNameTable[ACCESSORY_HOOD] = "_두건";
	m_newAccessoryNameTable[ACCESSORY_ROUNDCAP] = "_둥근모자";
	m_newAccessoryNameTable[ACCESSORY_FLUMASK] = "_마스크";
	m_newAccessoryNameTable[ACCESSORY_HAIRBAND] = "_머리띠";
	m_newAccessoryNameTable[ACCESSORY_DIVERSGOGGLES] = "_물안경";
	m_newAccessoryNameTable[ACCESSORY_BIRETTA] = "_비레타";
	m_newAccessoryNameTable[ACCESSORY_SUNGLASS] = "_선글래스";
	m_newAccessoryNameTable[ACCESSORY_EYEBANDAGE] = "_안대";
	m_newAccessoryNameTable[ACCESSORY_CAP] = "_캡";
	m_newAccessoryNameTable[ACCESSORY_BUNNYBAND] = "_토끼머리띠";
	m_newAccessoryNameTable[ACCESSORY_HAT] = "_햇";
	m_newAccessoryNameTable[ACCESSORY_RIBBON] = "_리본";
	m_newAccessoryNameTable[ACCESSORY_CIRCLET] = "_서클릿";
	m_newAccessoryNameTable[ACCESSORY_TIARA] = "_티아라";
	m_newAccessoryNameTable[ACCESSORY_SANTAHAT] = "_산타모자"; // changed
	m_newAccessoryNameTable[ACCESSORY_BEARD] = "_턱수염";
	m_newAccessoryNameTable[ACCESSORY_MUSTACHE] = "_콧수염";
	m_newAccessoryNameTable[ACCESSORY_SPECTACLE] = "_외눈안경";
	m_newAccessoryNameTable[ACCESSORY_BLACK_BEARD] = "_수염";
	m_newAccessoryNameTable[ACCESSORY_WHITE_BEARD] = "_흰수염";
	m_newAccessoryNameTable[ACCESSORY_QUALITY_SUNGLASS] = "_고급선글래스";
	m_newAccessoryNameTable[ACCESSORY_SPIN_GLASS] = "_스핀글래스";
	m_newAccessoryNameTable[ACCESSORY_LARGE_RIBBON] = "_왕리본";
	m_newAccessoryNameTable[ACCESSORY_SWEET_GENTLE] = "_스위트젠틀";
	m_newAccessoryNameTable[ACCESSORY_GOLDEN_HEADGEAR] = "_골든헤드기어";
	m_newAccessoryNameTable[ACCESSORY_OLDSTER_ROMANCE] = "_올드스터로맨스";
	m_newAccessoryNameTable[ACCESSORY_WESTERN_GRACE] = "_웨스턴그레이스";
	m_newAccessoryNameTable[ACCESSORY_CORONET] = "_코로넷";
	m_newAccessoryNameTable[ACCESSORY_HAIR_STRING] = "_머리끈";
	m_newAccessoryNameTable[ACCESSORY_PRIEST_CAP] = "_성직자의모자";
	m_newAccessoryNameTable[ACCESSORY_WIZARD_HAT] = "_위저드햇";
	m_newAccessoryNameTable[ACCESSORY_SUNFLOWER] = "_장식용해바라기";
	m_newAccessoryNameTable[ACCESSORY_ANGEL_HAIRBAND] = "_천사의머리띠";
	m_newAccessoryNameTable[ACCESSORY_DEVIL_HAIRBAND] = "_악마의머리띠";
	m_newAccessoryNameTable[ACCESSORY_HELM] = "_헬름";
	m_newAccessoryNameTable[ACCESSORY_MAJESTIC_GOUT] = "_마제스틱고우트";
	m_newAccessoryNameTable[ACCESSORY_WHITE_HORN] = "_새하얀뿔";
	m_newAccessoryNameTable[ACCESSORY_SHARP_HEADGEAR] = "_샤프헤드기어";
	m_newAccessoryNameTable[ACCESSORY_WEDDING_VEIL] = "_면사포";
	m_newAccessoryNameTable[ACCESSORY_CROWN] = "_크라운";
	m_newAccessoryNameTable[ACCESSORY_PROPELLER] = "_프로펠라";
	m_newAccessoryNameTable[ACCESSORY_TINY_EYE_GLASSES] = "_미니글래스";
	m_newAccessoryNameTable[ACCESSORY_PRONTERA_ARMY_CAP] = "_프론테라군모";
	m_newAccessoryNameTable[ACCESSORY_PIERROTS_NOSE] = "_광대코";
	m_newAccessoryNameTable[ACCESSORY_PIRATES_EYEBANDAGE] = "_의적안대";
	m_newAccessoryNameTable[ACCESSORY_MUNAK_TURBAN] = "_무낙모자";
	m_newAccessoryNameTable[ACCESSORY_HIP_HOP_MASK] = "_시위용마스크";
	m_newAccessoryNameTable[ACCESSORY_IRONCANE] = "_아이언케인";
	m_newAccessoryNameTable[ACCESSORY_CIGAR] = "_담배";
	m_newAccessoryNameTable[ACCESSORY_CIGAR_PIPE] = "_파이프담배";
	m_newAccessoryNameTable[ACCESSORY_SENTIMENTAL_FLOWER] = "_꽃잎";
	m_newAccessoryNameTable[ACCESSORY_SENTIMENTAL_BLADE] = "_풀잎";
	m_newAccessoryNameTable[ACCESSORY_HEY_DUDE] = "_머리안경";
	m_newAccessoryNameTable[ACCESSORY_STOP_SIGNPOST] = "_정지표지판";
	m_newAccessoryNameTable[ACCESSORY_DOCTOR_BAND] = "_의사머리띠";
	m_newAccessoryNameTable[ACCESSORY_JAPANESE_GHOST] = "_망자의머리띠";
	m_newAccessoryNameTable[ACCESSORY_SCARLET_BANDANA] = "_반다나";
	m_newAccessoryNameTable[ACCESSORY_EAGLE_EYES] = "_도끼눈";
	m_newAccessoryNameTable[ACCESSORY_NURSE_CAP] = "_간호모";
	m_newAccessoryNameTable[ACCESSORY_SMILE] = "_스마일";
	m_newAccessoryNameTable[ACCESSORY_BOMB_WICK] = "_심지";
	m_newAccessoryNameTable[ACCESSORY_SAHT_GAHT] = "_삿갓";
	m_newAccessoryNameTable[ACCESSORY_MASQUERADE] = "_오페라가면";
	m_newAccessoryNameTable[ACCESSORY_SERAPHIC_RING] = "_영혼고리";
	m_newAccessoryNameTable[ACCESSORY_EARMUFFS] = "_귀마개";
	m_newAccessoryNameTable[ACCESSORY_MOOSE_HORN] = "_사슴뿔";
	m_newAccessoryNameTable[ACCESSORY_THE_APPLE_OF_WILHELM_TELL] = "_명사수의사과";
	m_newAccessoryNameTable[ACCESSORY_TINKER_BELL] = "_요정의귀";
	m_newAccessoryNameTable[ACCESSORY_PIRATE_BANDANA] = "_해적두건";
	m_newAccessoryNameTable[ACCESSORY_MUNCHS_SCREAM] = "_스크래치마스크";
	m_newAccessoryNameTable[ACCESSORY_POO_POO_HAT] = "_거시기";
	m_newAccessoryNameTable[ACCESSORY_KOEAN_FUNERAL_COSTUME] = "_장례건";
	m_newAccessoryNameTable[ACCESSORY_BUTTERFLY_MASQUE] = "_나비가면";
	m_newAccessoryNameTable[ACCESSORY_WELDER_MASK] = "_용접마스크";
	m_newAccessoryNameTable[ACCESSORY_PRETEND_TO_BE_MURDERED] = "_연극소도구";
	m_newAccessoryNameTable[ACCESSORY_STAR_DUST] = "_스타더스트";
	m_newAccessoryNameTable[ACCESSORY_EYE_MASK] = "_눈가리개";
	m_newAccessoryNameTable[ACCESSORY_BINOCULARS] = "_망원경";
	m_newAccessoryNameTable[ACCESSORY_GOBLIN_MASQUE] = "_고블린족가면";
	m_newAccessoryNameTable[ACCESSORY_GREEN_FEELER] = "_초록더듬이";
	m_newAccessoryNameTable[ACCESSORY_VIKING_HELMET] = "_오크족헬름";
	m_newAccessoryNameTable[ACCESSORY_HEAD_SET] = "_헤드폰";
	m_newAccessoryNameTable[ACCESSORY_GEMMED_CROWN] = "_쥬얼크라운";
	m_newAccessoryNameTable[ACCESSORY_PIERROT_CROWN] = "_광대모자";
	m_newAccessoryNameTable[ACCESSORY_OXYGEN_MASK] = "_산소마스크";
	m_newAccessoryNameTable[ACCESSORY_GAS_MASK] = "_가스마스크";
	m_newAccessoryNameTable[ACCESSORY_MACHO_MANS_GLASSES] = "_하트파운데이션";
	m_newAccessoryNameTable[ACCESSORY_LORD_CIRCLET] = "_로드서클릿";
	m_newAccessoryNameTable[ACCESSORY_PUPPY_LOVE] = "_풋사랑";
	m_newAccessoryNameTable[ACCESSORY_CRASH_HELMET] = "_안전모";
	m_newAccessoryNameTable[ACCESSORY_INDIAN_BAND] = "_원주민머리띠";
	m_newAccessoryNameTable[ACCESSORY_AERIAL] = "_안테나";
	m_newAccessoryNameTable[ACCESSORY_BA_HAT] = "_학사모";
	m_newAccessoryNameTable[ACCESSORY_HORN_OF_LORD_KAHO] = "_로드카호의뿔";
	m_newAccessoryNameTable[ACCESSORY_FIN_HELM] = "_핀헬름";
	m_newAccessoryNameTable[ACCESSORY_EGG_SHELL] = "_장식용알껍질";
	m_newAccessoryNameTable[ACCESSORY_KOREAN_SCHOOL_HAT] = "_학생모";
	m_newAccessoryNameTable[ACCESSORY_BONE_HELM] = "_본헬름";
	m_newAccessoryNameTable[ACCESSORY_WILHELM_TELLS_HAT] = "_깃털모자";
	m_newAccessoryNameTable[ACCESSORY_CORSAIR] = "_커세어";
	m_newAccessoryNameTable[ACCESSORY_BAND_OF_KAFRA] = "_카프라의머리띠";
	m_newAccessoryNameTable[ACCESSORY_LOST_MONEY_HEART] = "_돈잃은자의마음";
	m_newAccessoryNameTable[ACCESSORY_BUNDLE] = "_보따리모";
	m_newAccessoryNameTable[ACCESSORY_CAKE_HAT] = "_케이크모자";
	m_newAccessoryNameTable[ACCESSORY_ANGEL_HELM] = "_천사의투구";
	m_newAccessoryNameTable[ACCESSORY_COOKER_HAT] = "_요리사의모자";
	m_newAccessoryNameTable[ACCESSORY_MAGE_HAT] = "_마법사의모자";
	m_newAccessoryNameTable[ACCESSORY_CANDLE] = "_촛불";
	m_newAccessoryNameTable[ACCESSORY_SPORE_HAT] = "_스포아모자";
	m_newAccessoryNameTable[ACCESSORY_PANDA_HAT] = "_팬더곰모자";
	m_newAccessoryNameTable[ACCESSORY_MINE_HAT] = "_광산헬멧";
	m_newAccessoryNameTable[ACCESSORY_OUTSIDE_HAT] = "_나들이모자";
	m_newAccessoryNameTable[ACCESSORY_RACCOON_HAT] = "_너구리모자";
	m_newAccessoryNameTable[ACCESSORY_LAMP_BAND] = "_전구머리띠";
	m_newAccessoryNameTable[ACCESSORY_PORING_HAT] = "_포링모자";
	m_newAccessoryNameTable[ACCESSORY_CROSS_BAND] = "_십자머리띠";
	m_newAccessoryNameTable[ACCESSORY_NUT_SHELL] = "_열매껍질";
	m_newAccessoryNameTable[ACCESSORY_YOUNG_DEVIL_HAT] = "_새끼악마모자";
	m_newAccessoryNameTable[ACCESSORY_SPOT_EGG_SHELL] = "_알록달록알껍질";
	m_newAccessoryNameTable[ACCESSORY_DYE_RED] = "_발그레";
	m_newAccessoryNameTable[ACCESSORY_HEART_HAIRPIN] = "_하트머리핀";
	m_newAccessoryNameTable[ACCESSORY_HAIR_CLOTH] = "_머리포자기";
	m_newAccessoryNameTable[ACCESSORY_GHOST_MASK] = "_오페라유령가면";
	m_newAccessoryNameTable[ACCESSORY_DEVIL_WING] = "_악마의날개";
	m_newAccessoryNameTable[ACCESSORY_WIZARD_HEADGEAR] = "_마술사의모자";
	m_newAccessoryNameTable[ACCESSORY_FASION_SUNGLASSES] = "_패션선글래스";
	m_newAccessoryNameTable[ACCESSORY_MOON_HEARPIN] = "_초승달머리핀";
	m_newAccessoryNameTable[ACCESSORY_STRIPES_BAND] = "_줄무늬머리띠";
	m_newAccessoryNameTable[ACCESSORY_MYSTIC_NUT_SHELL] = "_신비한열매껍질";
	m_newAccessoryNameTable[ACCESSORY_CAT_BELL] = "_고양이방울";
	m_newAccessoryNameTable[ACCESSORY_BLUE_BAND] = "_청색머리띠";
	m_newAccessoryNameTable[ACCESSORY_SPHINX_HAT] = "_스핑크스모자";
	m_newAccessoryNameTable[ACCESSORY_SUN_GOD_HAT] = "_태양신의모자";
	m_newAccessoryNameTable[ACCESSORY_BOMGUN_HAT] = "_본건모자";
	m_newAccessoryNameTable[ACCESSORY_LOVE_NUT] = "_사랑의열매";

	m_pcJobNameTable.resize(96, "초보자\\초보자");
	m_pcJobNameTable[0] = "초보자\\초보자";
	m_pcJobNameTable[1] = "검사\\검사";
	m_pcJobNameTable[2] = "마법사\\마법사";
	m_pcJobNameTable[3] = "궁수\\궁수";
	m_pcJobNameTable[4] = "성직자\\성직자";
	m_pcJobNameTable[5] = "상인\\상인";
	m_pcJobNameTable[6] = "도둑\\도둑";
	m_pcJobNameTable[7] = "기사\\기사";
	m_pcJobNameTable[8] = "프리스트\\프리스트";
	m_pcJobNameTable[9] = "위저드\\위저드";
	m_pcJobNameTable[10] = "제철공\\제철공";
	m_pcJobNameTable[11] = "헌터\\헌터";
	m_pcJobNameTable[12] = "어세신\\어세신";
	m_pcJobNameTable[13] = "페코페코_기사\\페코페코_기사";
	m_pcJobNameTable[14] = "크루세이더\\크루세이더";
	m_pcJobNameTable[15] = "몽크\\몽크";
	m_pcJobNameTable[16] = "세이지\\세이지";
	m_pcJobNameTable[17] = "로그\\로그";
	m_pcJobNameTable[18] = "연금술사\\연금술사";
	m_pcJobNameTable[19] = "바드\\바드";
	m_pcJobNameTable[20] = "무희\\무희";
	m_pcJobNameTable[21] = "신페코크루세이더\\신페코크루세이더";
	m_pcJobNameTable[23] = "초보자\\초보자";
	m_pcJobNameTable[22] = "결혼\\결혼";
	m_pcJobNameTable[51] = "초보자\\초보자";
	m_pcJobNameTable[52] = "검사\\검사";
	m_pcJobNameTable[53] = "마법사\\마법사";
	m_pcJobNameTable[54] = "궁수\\궁수";
	m_pcJobNameTable[55] = "성직자\\성직자";
	m_pcJobNameTable[56] = "상인\\상인";
	m_pcJobNameTable[57] = "도둑\\도둑";
	m_pcJobNameTable[58] = "기사\\기사";
	m_pcJobNameTable[59] = "프리스트\\프리스트";
	m_pcJobNameTable[60] = "위저드\\위저드";
	m_pcJobNameTable[61] = "제철공\\제철공";
	m_pcJobNameTable[62] = "헌터\\헌터";
	m_pcJobNameTable[63] = "어세신\\어세신";
	m_pcJobNameTable[64] = "페코페코_기사\\페코페코_기사";
	m_pcJobNameTable[65] = "크루세이더\\크루세이더";
	m_pcJobNameTable[66] = "몽크\\몽크";
	m_pcJobNameTable[67] = "세이지\\세이지";
	m_pcJobNameTable[68] = "로그\\로그";
	m_pcJobNameTable[69] = "연금술사\\연금술사";
	m_pcJobNameTable[70] = "바드\\바드";
	m_pcJobNameTable[71] = "무희\\무희";
	m_pcJobNameTable[72] = "신페코크루세이더\\신페코크루세이더";
	m_pcJobNameTable[73] = "초보자\\초보자";
	m_pcJobNameTable[74] = "검사\\검사";
	m_pcJobNameTable[75] = "마법사\\마법사";
	m_pcJobNameTable[76] = "궁수\\궁수";
	m_pcJobNameTable[77] = "성직자\\성직자";
	m_pcJobNameTable[78] = "상인\\상인";
	m_pcJobNameTable[79] = "도둑\\도둑";
	m_pcJobNameTable[80] = "기사\\기사";
	m_pcJobNameTable[81] = "프리스트\\프리스트";
	m_pcJobNameTable[82] = "위저드\\위저드";
	m_pcJobNameTable[83] = "제철공\\제철공";
	m_pcJobNameTable[84] = "헌터\\헌터";
	m_pcJobNameTable[85] = "어세신\\어세신";
	m_pcJobNameTable[86] = "페코페코_기사\\페코페코_기사";
	m_pcJobNameTable[87] = "크루세이더\\크루세이더";
	m_pcJobNameTable[88] = "몽크\\몽크";
	m_pcJobNameTable[89] = "세이지\\세이지";
	m_pcJobNameTable[90] = "로그\\로그";
	m_pcJobNameTable[91] = "연금술사\\연금술사";
	m_pcJobNameTable[92] = "바드\\바드";
	m_pcJobNameTable[93] = "무희\\무희";
	m_pcJobNameTable[94] = "신페코크루세이더\\신페코크루세이더";
	m_pcJobNameTable[95] = "초보자\\초보자";

	m_pcSexNameTable.resize(2, "여");
	m_pcSexNameTable[0] = "_여";
	m_pcSexNameTable[1] = "_남";

	m_pcSexImfNameTable.resize(2, "f");
	m_pcSexImfNameTable[0] = "f";
	m_pcSexImfNameTable[1] = "";

	m_pcHeadNameTable.resize(20, "");
	m_pcHeadNameTable[0] = "";
	m_pcHeadNameTable[1] = "";
	m_pcHeadNameTable[2] = "";
	m_pcHeadNameTable[3] = "";
	m_pcHeadNameTable[4] = "";
	m_pcHeadNameTable[5] = "";
	m_pcHeadNameTable[6] = "";
	m_pcHeadNameTable[7] = "";

	m_pcHeadImfNameTable.resize(20, "");
	m_pcHeadImfNameTable[0] = "";
	m_pcHeadImfNameTable[1] = "_a";
	m_pcHeadImfNameTable[2] = "_b";
	m_pcHeadImfNameTable[4] = "_c";
	m_pcHeadImfNameTable[7] = "_d";
	m_pcHeadImfNameTable[3] = "_e";
	m_pcHeadImfNameTable[6] = "_f";
	m_pcHeadImfNameTable[5] = "_g";

	m_pcWeaponNameTable.resize(23, "");
	m_pcWeaponNameTable[0] = "";
	m_pcWeaponNameTable[1] = "_단검";
	m_pcWeaponNameTable[2] = "_검";
	m_pcWeaponNameTable[3] = "_검";
	m_pcWeaponNameTable[4] = "_창";
	m_pcWeaponNameTable[5] = "_창";
	m_pcWeaponNameTable[6] = "_도끼";
	m_pcWeaponNameTable[7] = "_도끼";
	m_pcWeaponNameTable[8] = "_클럽";
	m_pcWeaponNameTable[9] = "_클럽";
	m_pcWeaponNameTable[10] = "_롯드";
	m_pcWeaponNameTable[11] = "_활";
	m_pcWeaponNameTable[12] = "_너클";
	m_pcWeaponNameTable[13] = "_악기";
	m_pcWeaponNameTable[14] = "_채찍";
	m_pcWeaponNameTable[15] = "_책";
	m_pcWeaponNameTable[16] = "_카타르_카타르";
	m_pcWeaponNameTable[17] = "_단검_단검";
	m_pcWeaponNameTable[18] = "_검_검";
	m_pcWeaponNameTable[19] = "_도끼_도끼";
	m_pcWeaponNameTable[20] = "_단검_검";
	m_pcWeaponNameTable[21] = "_단검_도끼";
	m_pcWeaponNameTable[22] = "_검_도끼";

	m_accessoryNameTable.resize(ACCESSORY_LAST, "");
	m_accessoryNameTable[ACCESSORY_NONE] = "";
	m_accessoryNameTable[ACCESSORY_GOGGLES] = "_고글";
	m_accessoryNameTable[ACCESSORY_CATTYHAIRBAND] = "_고양이머리띠";
	m_accessoryNameTable[ACCESSORY_GLASS] = "_글라스";
	m_accessoryNameTable[ACCESSORY_FLOWER] = "_꽃";
	m_accessoryNameTable[ACCESSORY_FLORALHAIRBAND] = "_꽃머리띠";
	m_accessoryNameTable[ACCESSORY_HOOD] = "_두건";
	m_accessoryNameTable[ACCESSORY_ROUNDCAP] = "_둥근모자";
	m_accessoryNameTable[ACCESSORY_FLUMASK] = "_마스크";
	m_accessoryNameTable[ACCESSORY_HAIRBAND] = "_머리띠";
	m_accessoryNameTable[ACCESSORY_DIVERSGOGGLES] = "_물안경";
	m_accessoryNameTable[ACCESSORY_BIRETTA] = "_비레타";
	m_accessoryNameTable[ACCESSORY_SUNGLASS] = "_선글라스";
	m_accessoryNameTable[ACCESSORY_EYEBANDAGE] = "_안대";
	m_accessoryNameTable[ACCESSORY_CAP] = "_캡";
	m_accessoryNameTable[ACCESSORY_BUNNYBAND] = "_토끼머리띠";
	m_accessoryNameTable[ACCESSORY_HAT] = "_햇";
	m_accessoryNameTable[ACCESSORY_RIBBON] = "_리본";
	m_accessoryNameTable[ACCESSORY_CIRCLET] = "_서클릿";
	m_accessoryNameTable[ACCESSORY_TIARA] = "_티아라";
	m_accessoryNameTable[ACCESSORY_SANTAHAT] = "_털모자";
	m_accessoryNameTable[ACCESSORY_BEARD] = "_턱수염";
	m_accessoryNameTable[ACCESSORY_MUSTACHE] = "_콧수염";
	m_accessoryNameTable[ACCESSORY_SPECTACLE] = "_외눈안경";
	m_accessoryNameTable[ACCESSORY_BLACK_BEARD] = "_수염";
	m_accessoryNameTable[ACCESSORY_WHITE_BEARD] = "_흰수염";
	m_accessoryNameTable[ACCESSORY_QUALITY_SUNGLASS] = "_고급선글래스";
	m_accessoryNameTable[ACCESSORY_SPIN_GLASS] = "_스핀글래스";
	m_accessoryNameTable[ACCESSORY_LARGE_RIBBON] = "_왕리본";
	m_accessoryNameTable[ACCESSORY_SWEET_GENTLE] = "_스위트젠틀";
	m_accessoryNameTable[ACCESSORY_GOLDEN_HEADGEAR] = "_골든헤드기어";
	m_accessoryNameTable[ACCESSORY_OLDSTER_ROMANCE] = "_올드스터로맨스";
	m_accessoryNameTable[ACCESSORY_WESTERN_GRACE] = "_웨스턴그레이스";
	m_accessoryNameTable[ACCESSORY_CORONET] = "_코로넷";
	m_accessoryNameTable[ACCESSORY_HAIR_STRING] = "_머리끈";
	m_accessoryNameTable[ACCESSORY_PRIEST_CAP] = "_성직자의모자";
	m_accessoryNameTable[ACCESSORY_WIZARD_HAT] = "_위저드햇";
	m_accessoryNameTable[ACCESSORY_SUNFLOWER] = "_장식용해바라기";
	m_accessoryNameTable[ACCESSORY_ANGEL_HAIRBAND] = "_천사의머리띠";
	m_accessoryNameTable[ACCESSORY_DEVIL_HAIRBAND] = "_악마의머리띠";
	m_accessoryNameTable[ACCESSORY_HELM] = "_헬름";
	m_accessoryNameTable[ACCESSORY_MAJESTIC_GOUT] = "_마제스틱고우트";
	m_accessoryNameTable[ACCESSORY_WHITE_HORN] = "_새하얀뿔";
	m_accessoryNameTable[ACCESSORY_SHARP_HEADGEAR] = "_샤프헤드기어";
	m_accessoryNameTable[ACCESSORY_WEDDING_VEIL] = "_면사포";
	m_accessoryNameTable[ACCESSORY_CROWN] = "_크라운";
	m_accessoryNameTable[ACCESSORY_PROPELLER] = "_프로펠라";
	m_accessoryNameTable[ACCESSORY_TINY_EYE_GLASSES] = "_미니글래스";
	m_accessoryNameTable[ACCESSORY_PRONTERA_ARMY_CAP] = "_프론테라군모";
	m_accessoryNameTable[ACCESSORY_PIERROTS_NOSE] = "_광대코";
	m_accessoryNameTable[ACCESSORY_PIRATES_EYEBANDAGE] = "_의적안대";
	m_accessoryNameTable[ACCESSORY_MUNAK_TURBAN] = "_무낙모자";
	m_accessoryNameTable[ACCESSORY_HIP_HOP_MASK] = "_시위용마스크";
	m_accessoryNameTable[ACCESSORY_IRONCANE] = "_아이언케인";
	m_accessoryNameTable[ACCESSORY_CIGAR] = "_담배";
	m_accessoryNameTable[ACCESSORY_CIGAR_PIPE] = "_파이프담배";
	m_accessoryNameTable[ACCESSORY_SENTIMENTAL_FLOWER] = "_꽃잎";
	m_accessoryNameTable[ACCESSORY_SENTIMENTAL_BLADE] = "_풀잎";
	m_accessoryNameTable[ACCESSORY_HEY_DUDE] = "_머리안경";
	m_accessoryNameTable[ACCESSORY_STOP_SIGNPOST] = "_정지표지판";
	m_accessoryNameTable[ACCESSORY_DOCTOR_BAND] = "_의사머리띠";
	m_accessoryNameTable[ACCESSORY_JAPANESE_GHOST] = "_망자의머리띠";
	m_accessoryNameTable[ACCESSORY_SCARLET_BANDANA] = "_반다나";
	m_accessoryNameTable[ACCESSORY_EAGLE_EYES] = "_도끼눈";
	m_accessoryNameTable[ACCESSORY_NURSE_CAP] = "_간호모";
	m_accessoryNameTable[ACCESSORY_SMILE] = "_스마일";
	m_accessoryNameTable[ACCESSORY_BOMB_WICK] = "_심지";
	m_accessoryNameTable[ACCESSORY_SAHT_GAHT] = "_삿갓";
	m_accessoryNameTable[ACCESSORY_MASQUERADE] = "_오페라가면";
	m_accessoryNameTable[ACCESSORY_SERAPHIC_RING] = "_영혼고리";
	m_accessoryNameTable[ACCESSORY_EARMUFFS] = "_귀마개";
	m_accessoryNameTable[ACCESSORY_MOOSE_HORN] = "_사슴뿔";
	m_accessoryNameTable[ACCESSORY_THE_APPLE_OF_WILHELM_TELL] = "_명사수의사과";
	m_accessoryNameTable[ACCESSORY_TINKER_BELL] = "_요정의귀";
	m_accessoryNameTable[ACCESSORY_PIRATE_BANDANA] = "_해적두건";
	m_accessoryNameTable[ACCESSORY_MUNCHS_SCREAM] = "_스크래치마스크";
	m_accessoryNameTable[ACCESSORY_POO_POO_HAT] = "_거시기";
	m_accessoryNameTable[ACCESSORY_KOEAN_FUNERAL_COSTUME] = "_장례건";
	m_accessoryNameTable[ACCESSORY_BUTTERFLY_MASQUE] = "_나비가면";
	m_accessoryNameTable[ACCESSORY_WELDER_MASK] = "_용접마스크";
	m_accessoryNameTable[ACCESSORY_PRETEND_TO_BE_MURDERED] = "_연극소도구";
	m_accessoryNameTable[ACCESSORY_STAR_DUST] = "_스타더스트";
	m_accessoryNameTable[ACCESSORY_EYE_MASK] = "_눈가리개";
	m_accessoryNameTable[ACCESSORY_BINOCULARS] = "_망원경";
	m_accessoryNameTable[ACCESSORY_GOBLIN_MASQUE] = "_고블린족가면";
	m_accessoryNameTable[ACCESSORY_GREEN_FEELER] = "_초록더듬이";
	m_accessoryNameTable[ACCESSORY_VIKING_HELMET] = "_오크족헬름";
	m_accessoryNameTable[ACCESSORY_HEAD_SET] = "_헤드폰";
	m_accessoryNameTable[ACCESSORY_GEMMED_CROWN] = "_쥬얼크라운";
	m_accessoryNameTable[ACCESSORY_PIERROT_CROWN] = "_광대모자";
	m_accessoryNameTable[ACCESSORY_OXYGEN_MASK] = "_산소마스크";
	m_accessoryNameTable[ACCESSORY_GAS_MASK] = "_가스마스크";
	m_accessoryNameTable[ACCESSORY_MACHO_MANS_GLASSES] = "_하트파운데이션";
	m_accessoryNameTable[ACCESSORY_LORD_CIRCLET] = "_로드서클릿";
	m_accessoryNameTable[ACCESSORY_PUPPY_LOVE] = "_풋사랑";
	m_accessoryNameTable[ACCESSORY_CRASH_HELMET] = "_안전모";
	m_accessoryNameTable[ACCESSORY_INDIAN_BAND] = "_원주민머리띠";
	m_accessoryNameTable[ACCESSORY_AERIAL] = "_안테나";
	m_accessoryNameTable[ACCESSORY_BA_HAT] = "_학사모";
	m_accessoryNameTable[ACCESSORY_HORN_OF_LORD_KAHO] = "_로드카호의뿔";
	m_accessoryNameTable[ACCESSORY_FIN_HELM] = "_핀헬름";
	m_accessoryNameTable[ACCESSORY_EGG_SHELL] = "_장식용알껍질";
	m_accessoryNameTable[ACCESSORY_KOREAN_SCHOOL_HAT] = "_학생모";
	m_accessoryNameTable[ACCESSORY_BONE_HELM] = "_본헬름";
	m_accessoryNameTable[ACCESSORY_WILHELM_TELLS_HAT] = "_깃털모자";
	m_accessoryNameTable[ACCESSORY_CORSAIR] = "_커세어";

	m_headAccNameList.resize(20, "");
	m_headAccNameList[0] = "";
	m_headAccNameList[1] = "초보자";
	m_headAccNameList[2] = "검사";
	m_headAccNameList[3] = "마법사";
	m_headAccNameList[4] = "궁수";
	m_headAccNameList[5] = "성직자";
	m_headAccNameList[6] = "상인";
	m_headAccNameList[7] = "도둑";
	m_headAccNameList[8] = "1";
	m_headAccNameList[9] = "2";
	m_headAccNameList[10] = "3";
	m_headAccNameList[11] = "4";
	m_headAccNameList[12] = "5";
	m_headAccNameList[13] = "5";
	m_headAccNameList[14] = "5";
	m_headAccNameList[15] = "5";
	m_headAccNameList[16] = "5";
	m_headAccNameList[17] = "5";
	m_headAccNameList[18] = "5";
	m_headAccNameList[19] = "5";

	m_palHeadNameTable.resize(20, "");
	m_palHeadNameTable[0] = "";
	m_palHeadNameTable[1] = "초보자";
	m_palHeadNameTable[2] = "검사";
	m_palHeadNameTable[3] = "마법사";
	m_palHeadNameTable[4] = "궁수";
	m_palHeadNameTable[5] = "성직자";
	m_palHeadNameTable[6] = "상인";
	m_palHeadNameTable[7] = "도둑";
	m_palHeadNameTable[8] = "머리1";
	m_palHeadNameTable[9] = "머리2";
	m_palHeadNameTable[10] = "머리3";
	m_palHeadNameTable[11] = "머리4";
	m_palHeadNameTable[12] = "머리5";
	m_palHeadNameTable[13] = "머리5";
	m_palHeadNameTable[14] = "머리5";
	m_palHeadNameTable[15] = "머리5";
	m_palHeadNameTable[16] = "머리5";
	m_palHeadNameTable[17] = "머리5";
	m_palHeadNameTable[18] = "머리5";
	m_palHeadNameTable[19] = "머리5";

	m_palJobNameTable.resize(96, "초보자");
	m_palJobNameTable[0] = "초보자";
	m_palJobNameTable[1] = "검사";
	m_palJobNameTable[2] = "마법사";
	m_palJobNameTable[3] = "궁수";
	m_palJobNameTable[4] = "성직자";
	m_palJobNameTable[5] = "상인";
	m_palJobNameTable[6] = "도둑";
	m_palJobNameTable[7] = "기사";
	m_palJobNameTable[8] = "프리스트";
	m_palJobNameTable[9] = "위저드";
	m_palJobNameTable[10] = "제철공";
	m_palJobNameTable[11] = "헌터";
	m_palJobNameTable[12] = "어세신";
	m_palJobNameTable[13] = "페코페코_기사";
	m_palJobNameTable[14] = "기사";
	m_palJobNameTable[15] = "프리스트";
	m_palJobNameTable[16] = "위저드";
	m_palJobNameTable[17] = "어세신";
	m_palJobNameTable[18] = "제철공";
	m_palJobNameTable[19] = "헌터";
	m_palJobNameTable[20] = "헌터";
	m_palJobNameTable[21] = "페코페코_기사";
	m_palJobNameTable[23] = "슈퍼노비스";
	m_palJobNameTable[22] = "결혼";
	m_palJobNameTable[51] = "초보자";
	m_palJobNameTable[52] = "검사";
	m_palJobNameTable[53] = "마법사";
	m_palJobNameTable[54] = "궁수";
	m_palJobNameTable[55] = "성직자";
	m_palJobNameTable[56] = "상인";
	m_palJobNameTable[57] = "도둑";
	m_palJobNameTable[58] = "기사";
	m_palJobNameTable[59] = "프리스트";
	m_palJobNameTable[60] = "위저드";
	m_palJobNameTable[61] = "제철공";
	m_palJobNameTable[62] = "헌터";
	m_palJobNameTable[63] = "어세신";
	m_palJobNameTable[64] = "페코페코_기사";
	m_palJobNameTable[65] = "기사";
	m_palJobNameTable[66] = "프리스트";
	m_palJobNameTable[67] = "위저드";
	m_palJobNameTable[68] = "어세신";
	m_palJobNameTable[69] = "제철공";
	m_palJobNameTable[70] = "헌터";
	m_palJobNameTable[71] = "헌터";
	m_palJobNameTable[72] = "페코페코_기사";
	m_palJobNameTable[73] = "초보자";
	m_palJobNameTable[74] = "검사";
	m_palJobNameTable[75] = "마법사";
	m_palJobNameTable[76] = "궁수";
	m_palJobNameTable[77] = "성직자";
	m_palJobNameTable[78] = "상인";
	m_palJobNameTable[79] = "도둑";
	m_palJobNameTable[80] = "기사";
	m_palJobNameTable[81] = "프리스트";
	m_palJobNameTable[82] = "위저드";
	m_palJobNameTable[83] = "제철공";
	m_palJobNameTable[84] = "헌터";
	m_palJobNameTable[85] = "어세신";
	m_palJobNameTable[86] = "페코페코_기사";
	m_palJobNameTable[87] = "기사";
	m_palJobNameTable[88] = "프리스트";
	m_palJobNameTable[89] = "위저드";
	m_palJobNameTable[90] = "어세신";
	m_palJobNameTable[91] = "제철공";
	m_palJobNameTable[92] = "헌터";
	m_palJobNameTable[93] = "헌터";
	m_palJobNameTable[94] = "페코페코_기사";
	m_palJobNameTable[95] = "슈퍼노비스";

	m_shieldNameTable.resize(SHIELD_LAST, "");
	m_shieldNameTable[SHIELD_NONE] = "";
	m_shieldNameTable[SHIELD_GUARD] = "_가드";
	m_shieldNameTable[SHIELD_SHIELD] = "_쉴드";
	m_shieldNameTable[SHIELD_MIRRORSHIELD] = "_미러쉴드";
	m_shieldNameTable[SHIELD_BUCKLER] = "_버클러";
}


hook_method<void (CSession::*)(void)> CSession::_InitJobNameTable(SAKEXE, "CSession::InitJobNameTable");
void CSession::InitJobNameTable(void) // line 1357
{
	return (this->*_InitJobNameTable)();

	m_jobNameTable.resize(JT_LAST, "1_ETC_01");
	m_jobNameTable[JT_NOVICE] = "Novice";
	m_jobNameTable[JT_SWORDMAN] = "Swordman";
	m_jobNameTable[JT_MAGICIAN] = ( g_serviceType == 1 ) ? "Mage" : "Magician";
	m_jobNameTable[JT_ARCHER] = "Archer";
	m_jobNameTable[JT_ACOLYTE] = "Acolyte";
	m_jobNameTable[JT_MERCHANT] = "Merchant";
	m_jobNameTable[JT_THIEF] = "Thief";
	m_jobNameTable[JT_KNIGHT] = "Knight";
	m_jobNameTable[JT_PRIEST] = "Priest";
	m_jobNameTable[JT_WIZARD] = "Wizard";
	m_jobNameTable[JT_BLACKSMITH] = "Blacksmith";
	m_jobNameTable[JT_HUNTER] = "Hunter";
	m_jobNameTable[JT_ASSASSIN] = "Assassin";
	m_jobNameTable[JT_CHICKEN] = "Knight";
	m_jobNameTable[JT_CRUSADER] = "Crusader";
	m_jobNameTable[JT_MONK] = "Monk";
	m_jobNameTable[JT_SAGE] = "Sage";
	m_jobNameTable[JT_ROGUE] = "Rogue";
	m_jobNameTable[JT_ALCHEMIST] = "Alchemist";
	m_jobNameTable[JT_BARD] = "Bard";
	m_jobNameTable[JT_DANCER] = "Dancer";
	m_jobNameTable[JT_CHICKEN2] = "Crusader";
	m_jobNameTable[JT_SUPERNOVICE] = "Super Novice";
	m_jobNameTable[JT_NOVICE_H] = "Novice High";
	m_jobNameTable[JT_SWORDMAN_H] = "Swordman High";
	m_jobNameTable[JT_MAGICIAN_H] = "Magician High";
	m_jobNameTable[JT_ARCHER_H] = "Archer High";
	m_jobNameTable[JT_ACOLYTE_H] = "Acolyte High";
	m_jobNameTable[JT_MERCHANT_H] = "Merchant High";
	m_jobNameTable[JT_THIEF_H] = "Thief High";
	m_jobNameTable[JT_KNIGHT_H] = "Lord Knight";
	m_jobNameTable[JT_PRIEST_H] = "High Priest";
	m_jobNameTable[JT_WIZARD_H] = "High Wizard";
	m_jobNameTable[JT_BLACKSMITH_H] = "Whitesmith";
	m_jobNameTable[JT_HUNTER_H] = "Sniper";
	m_jobNameTable[JT_ASSASSIN_H] = "Assassin Cross";
	m_jobNameTable[JT_CHICKEN_H] = "Peko Knight";
	m_jobNameTable[JT_CRUSADER_H] = "Paladin";
	m_jobNameTable[JT_MONK_H] = "Champion";
	m_jobNameTable[JT_SAGE_H] = "Professor";
	m_jobNameTable[JT_ROGUE_H] = "Stalker";
	m_jobNameTable[JT_ALCHEMIST_H] = "Creator";
	m_jobNameTable[JT_BARD_H] = "Clown";
	m_jobNameTable[JT_DANCER_H] = "Gypsy";
	m_jobNameTable[JT_CHICKEN2_H] = "Paladin";
	m_jobNameTable[JT_NOVICE_B] = "Baby Novice";
	m_jobNameTable[JT_SWORDMAN_B] = "Baby Swordman";
	m_jobNameTable[JT_MAGICIAN_B] = "Baby Magician";
	m_jobNameTable[JT_ARCHER_B] = "Baby Archer";
	m_jobNameTable[JT_ACOLYTE_B] = "Baby Acolyte";
	m_jobNameTable[JT_MERCHANT_B] = "Baby Merchant";
	m_jobNameTable[JT_THIEF_B] = "Baby Thief";
	m_jobNameTable[JT_KNIGHT_B] = "Baby Knight";
	m_jobNameTable[JT_PRIEST_B] = "Baby Priest";
	m_jobNameTable[JT_WIZARD_B] = "Baby Wizard";
	m_jobNameTable[JT_BLACKSMITH_B] = "Baby Blacksmith";
	m_jobNameTable[JT_HUNTER_B] = "Baby Hunter";
	m_jobNameTable[JT_ASSASSIN_B] = "Baby Assassin";
	m_jobNameTable[JT_CHICKEN_B] = "Baby Knight";
	m_jobNameTable[JT_CRUSADER_B] = "Baby Crusader";
	m_jobNameTable[JT_MONK_B] = "Baby Monk";
	m_jobNameTable[JT_SAGE_B] = "Baby Sage";
	m_jobNameTable[JT_ROGUE_B] = "Baby Rogue";
	m_jobNameTable[JT_ALCHEMIST_B] = "Baby Alchemist";
	m_jobNameTable[JT_BARD_B] = "Baby Bard";
	m_jobNameTable[JT_DANCER_B] = "Baby Dancer";
	m_jobNameTable[JT_CHICKEN2_B] = "Baby Crusader";
	m_jobNameTable[JT_SUPERNOVICE_B] = "Baby Super Novice";
	m_jobNameTable[JT_WARPNPC] = "1_ETC_01";
	m_jobNameTable[JT_1_ETC_01] = "1_ETC_01";
	m_jobNameTable[JT_1_M_01] = "1_M_01";
	m_jobNameTable[JT_1_M_02] = "1_M_02";
	m_jobNameTable[JT_1_M_03] = "1_M_03";
	m_jobNameTable[JT_1_M_04] = "1_M_04";
	m_jobNameTable[JT_1_M_BARD] = "1_M_BARD";
	m_jobNameTable[JT_1_M_HOF] = "1_M_HOF";
	m_jobNameTable[JT_1_M_INNKEEPER] = "1_M_INNKEEPER";
	m_jobNameTable[JT_1_M_JOBGUIDER] = "1_M_JOBGUIDER";
	m_jobNameTable[JT_1_M_JOBTESTER] = "1_M_JOBTESTER";
	m_jobNameTable[JT_1_M_KNIGHTMASTER] = "1_M_KNIGHTMASTER";
	m_jobNameTable[JT_1_M_LIBRARYMASTER] = "1_M_LIBRARYMASTER";
	m_jobNameTable[JT_1_M_MERCHANT] = "1_M_MERCHANT";
	m_jobNameTable[JT_1_M_ORIENT01] = "1_M_ORIENT01";
	m_jobNameTable[JT_1_M_PASTOR] = "1_M_PASTOR";
	m_jobNameTable[JT_1_M_PUBMASTER] = "1_M_PUBMASTER";
	m_jobNameTable[JT_1_M_SIZ] = "1_M_SIZ";
	m_jobNameTable[JT_1_M_SMITH] = "1_M_SMITH";
	m_jobNameTable[JT_1_M_WIZARD] = "1_M_WIZARD";
	m_jobNameTable[JT_1_M_YOUNGKNIGHT] = "1_M_YOUNGKNIGHT";
	m_jobNameTable[JT_1_F_01] = "1_F_01";
	m_jobNameTable[JT_1_F_02] = "1_F_02";
	m_jobNameTable[JT_1_F_03] = "1_F_03";
	m_jobNameTable[JT_1_F_04] = "1_F_04";
	m_jobNameTable[JT_1_F_GYPSY] = "1_F_GYPSY";
	m_jobNameTable[JT_1_F_LIBRARYGIRL] = "1_F_LIBRARYGIRL";
	m_jobNameTable[JT_1_F_MARIA] = "1_F_MARIA";
	m_jobNameTable[JT_1_F_MERCHANT_01] = "1_F_MERCHANT_01";
	m_jobNameTable[JT_1_F_MERCHANT_02] = "1_F_MERCHANT_02";
	m_jobNameTable[JT_1_F_ORIENT_01] = "1_F_ORIENT_01";
	m_jobNameTable[JT_1_F_ORIENT_02] = "1_F_ORIENT_02";
	m_jobNameTable[JT_1_F_ORIENT_03] = "1_F_ORIENT_03";
	m_jobNameTable[JT_1_F_ORIENT_04] = "1_F_ORIENT_04";
	m_jobNameTable[JT_1_F_PRIEST] = "1_F_PRIEST";
	m_jobNameTable[JT_1_F_PUBGIRL] = "1_F_PUBGIRL";
	m_jobNameTable[JT_4_DOG01] = "4_DOG01";
	m_jobNameTable[JT_4_KID01] = "4_KID01";
	m_jobNameTable[JT_4_M_01] = "4_M_01";
	m_jobNameTable[JT_4_M_02] = "4_M_02";
	m_jobNameTable[JT_4_M_03] = "4_M_03";
	m_jobNameTable[JT_4_M_04] = "4_M_04";
	m_jobNameTable[JT_4_M_BARBER] = "4_M_BARBER";
	m_jobNameTable[JT_4_M_ORIENT01] = "4_M_ORIENT01";
	m_jobNameTable[JT_4_M_ORIENT02] = "4_M_ORIENT02";
	m_jobNameTable[JT_4_F_01] = "4_F_01";
	m_jobNameTable[JT_4_F_02] = "4_F_02";
	m_jobNameTable[JT_4_F_03] = "4_F_03";
	m_jobNameTable[JT_4_F_04] = "4_F_04";
	m_jobNameTable[JT_4_F_MAID] = "4_F_MAID";
	m_jobNameTable[JT_4_F_SISTER] = "4_F_SISTER";
	m_jobNameTable[JT_4W_KID] = "4W_KID";
	m_jobNameTable[JT_4W_M_01] = "4W_M_01";
	m_jobNameTable[JT_4W_M_02] = "4W_M_02";
	m_jobNameTable[JT_4W_M_03] = "4W_M_03";
	m_jobNameTable[JT_4W_SAILOR] = "4W_SAILOR";
	m_jobNameTable[JT_4W_F_01] = "4W_F_01";
	m_jobNameTable[JT_8_F] = "8_F";
	m_jobNameTable[JT_8_F_GRANDMOTHER] = "8_F_GRANDMOTHER";
	m_jobNameTable[JT_EFFECTLAUNCHER] = "1_ETC_01";
	m_jobNameTable[JT_8W_SOLDIER] = "8W_SOLDIER";
	m_jobNameTable[JT_1_M_MOC_LORD] = "1_M_MOC_LORD";
	m_jobNameTable[JT_1_M_PAY_ELDER] = "1_M_PAY_ELDER";
	m_jobNameTable[JT_1_M_PRON_KING] = "1_M_PRON_KING";
	m_jobNameTable[JT_4_M_MANAGER] = "4_M_MANAGER";
	m_jobNameTable[JT_4_M_MINISTER] = "4_M_MINISTER";
	m_jobNameTable[JT_HIDDEN_NPC] = "1_ETC_01";
	m_jobNameTable[JT_4_F_KAFRA7] = "4_F_KAFRA7"; //NOTE: out-of-order entry
	m_jobNameTable[JT_4_F_KAFRA6] = "4_F_KAFRA6";
	m_jobNameTable[JT_4_F_KAFRA5] = "4_F_KAFRA5";
	m_jobNameTable[JT_4_F_KAFRA4] = "4_F_KAFRA4";
	m_jobNameTable[JT_4_F_KAFRA3] = "4_F_KAFRA3";
	m_jobNameTable[JT_4_F_KAFRA2] = "4_F_KAFRA2";
	m_jobNameTable[JT_4_F_KAFRA1] = "4_F_KAFRA1";
	m_jobNameTable[JT_2_M_THIEFMASTER] = "2_M_THIEFMASTER";
	m_jobNameTable[JT_2_M_SWORDMASTER] = "2_M_SWORDMASTER";
	m_jobNameTable[JT_2_M_PHARMACIST] = "2_M_PHARMACIST";
	m_jobNameTable[JT_2_M_MOLGENSTEIN] = "2_M_MOLGENSTEIN";
	m_jobNameTable[JT_2_M_DYEINGER] = "2_M_DYEINGER";
	m_jobNameTable[JT_2_F_MAGICMASTER] = "2_F_MAGICMASTER";
	m_jobNameTable[JT_4_F_TELEPORTER] = "4_F_TELEPORTER";
	m_jobNameTable[JT_4_M_TELEPORTER] = "4_M_TELEPORTER";
//	m_jobNameTable[JT_SAFETYWALL]
//	m_jobNameTable[JT_FIREWALL]
//	m_jobNameTable[JT_WARPPORTAL]
//	m_jobNameTable[JT_PREWARPPORTAL]
//	m_jobNameTable[JT_BENEDICTIO]
//	m_jobNameTable[JT_SANCTUARY]
//	m_jobNameTable[JT_MAGNUS]
//	m_jobNameTable[JT_PNEUMA]
//	m_jobNameTable[JT_DUMMYSKILL]
//	m_jobNameTable[JT_PREFIREPILLAR]
//	m_jobNameTable[JT_FIREPILLAR]
//	m_jobNameTable[JT_HIDDEN_TRAP]
//	m_jobNameTable[JT_TRAP]
//	m_jobNameTable[JT_HIDDEN_WARP_NPC]
//	m_jobNameTable[JT_TRAPBOOM]
//	m_jobNameTable[JT_ICEWALL]
//	m_jobNameTable[JT_QUAGMIRE]
//	m_jobNameTable[JT_TRAP_BLASTMINE]
//	m_jobNameTable[JT_TRAP_SKIDTRAP]
//	m_jobNameTable[JT_TRAP_ANKLESNARE]
//	m_jobNameTable[JT_VENOMDUST]
//	m_jobNameTable[JT_TRAP_LANDMINE]
//	m_jobNameTable[JT_TRAP_SHOCKWAVE]
//	m_jobNameTable[JT_TRAP_SANDMAN]
//	m_jobNameTable[JT_TRAP_FLASHER]
//	m_jobNameTable[JT_TRAP_FREEZINGTRAP]
//	m_jobNameTable[JT_TRAP_CLAYMORETRAP]
//	m_jobNameTable[JT_TRAP_TALKIEBOX]
//	m_jobNameTable[JT_VOLCANO]
//	m_jobNameTable[JT_DELUGE]
//	m_jobNameTable[JT_VIOLENTGALE]
//	m_jobNameTable[JT_LANDPROTECTOR]
//	m_jobNameTable[JT_LULLABY]
//	m_jobNameTable[JT_RICHMANKIM]
//	m_jobNameTable[JT_ETERNALCHAOS]
//	m_jobNameTable[JT_DRUMBATTLEFIELD]
//	m_jobNameTable[JT_RINGNIBELUNGEN]
//	m_jobNameTable[JT_ROKISWEIL]
//	m_jobNameTable[JT_INTOABYSS]
//	m_jobNameTable[JT_SIEGFRIED]
//	m_jobNameTable[JT_DISSONANCE]
//	m_jobNameTable[JT_WHISTLE]
//	m_jobNameTable[JT_ASSASSINCROSS]
//	m_jobNameTable[JT_POEMBRAGI]
//	m_jobNameTable[JT_APPLEIDUN]
//	m_jobNameTable[JT_UGLYDANCE]
//	m_jobNameTable[JT_HUMMING]
//	m_jobNameTable[JT_DONTFORGETME]
//	m_jobNameTable[JT_FORTUNEKISS]
//	m_jobNameTable[JT_SERVICEFORYOU]
//	m_jobNameTable[JT_GRAFFITI]
//	m_jobNameTable[JT_DEMONSTRATION]
//	m_jobNameTable[JT_COUPLE]
//	m_jobNameTable[JT_GOSPEL]
//	m_jobNameTable[JT_BASILICA]
//	m_jobNameTable[JT_MOONLIT]
	m_jobNameTable[JT_8_F_GIRL] = "8_F_GIRL";
	m_jobNameTable[JT_4_M_SNOWMAN] = "4_M_SNOWMAN";
	m_jobNameTable[JT_4_F_05] = "4_F_05";
	m_jobNameTable[JT_4_M_05] = "4_M_05";
	m_jobNameTable[JT_4_M_06] = "4_M_06";
	m_jobNameTable[JT_4_F_06] = "4_F_06";
	m_jobNameTable[JT_4_M_PIERROT] = "4_M_PIERROT";
	m_jobNameTable[JT_4_M_KID2] = "4_M_KID2";
	m_jobNameTable[JT_4_F_KID3] = "4_F_KID3";
	m_jobNameTable[JT_4_M_SANTA] = "4_M_SANTA";
	m_jobNameTable[JT_4_F_GODEMOM] = "4_F_GODEMOM";
	m_jobNameTable[JT_4_F_GON] = "4_F_GON";
	m_jobNameTable[JT_4_F_KID2] = "4_F_KID2";
	m_jobNameTable[JT_4_M_BIBI] = "4_M_BIBI";
	m_jobNameTable[JT_4_M_GEF_SOLDIER] = "4_M_GEF_SOLDIER";
	m_jobNameTable[JT_4_M_KID1] = "4_M_KID1";
	m_jobNameTable[JT_4_M_MOC_SOLDIER] = "4_M_MOC_SOLDIER";
	m_jobNameTable[JT_4_M_PAY_SOLDIER] = "4_M_PAY_SOLDIER";
	m_jobNameTable[JT_4_M_SEAMAN] = "4_M_SEAMAN";
	m_jobNameTable[JT_4_F_NACORURI] = "4_F_NACORURI";
	m_jobNameTable[JT_4_F_SHAMAN] = "4_F_SHAMAN";
//	m_jobNameTable[JT_4_F_KAFRA7] // elsewhere
	m_jobNameTable[JT_GUILD_FLAG] = "Guildflag90_1.gr2";
	m_jobNameTable[JT_1_SHADOW_NPC] = "1_SHADOW_NPC";
	m_jobNameTable[JT_4_F_07] = "4_F_07";
	m_jobNameTable[JT_4_F_JOB_ASSASSIN] = "4_F_JOB_ASSASSIN";
	m_jobNameTable[JT_4_F_JOB_BLACKSMITH] = "4_F_JOB_BLACKSMITH";
	m_jobNameTable[JT_4_F_JOB_HUNTER] = "4_F_JOB_HUNTER";
	m_jobNameTable[JT_4_F_JOB_KNIGHT] = "4_F_JOB_KNIGHT";
	m_jobNameTable[JT_4_F_NOVICE] = "4_F_NOVICE";
	m_jobNameTable[JT_4_M_JOB_ASSASSIN] = "4_M_JOB_ASSASSIN";
	m_jobNameTable[JT_4_M_JOB_BLACKSMITH] = "4_M_JOB_BLACKSMITH";
	m_jobNameTable[JT_4_M_JOB_HUNTER] = "4_M_JOB_HUNTER";
	m_jobNameTable[JT_4_M_JOB_KNIGHT1] = "4_M_JOB_KNIGHT1";
	m_jobNameTable[JT_4_M_JOB_KNIGHT2] = "4_M_JOB_KNIGHT2";
	m_jobNameTable[JT_4_M_JOB_WIZARD] = "4_M_JOB_WIZARD";
	m_jobNameTable[JT_4_BAPHOMET] = "4_BAPHOMET";
	m_jobNameTable[JT_4_DARKLORD] = "4_DARKLORD";
	m_jobNameTable[JT_4_DEVIRUCHI] = "4_DEVIRUCHI";
	m_jobNameTable[JT_8_DOPPEL] = "8_DOPPEL";
	m_jobNameTable[JT_2_M_ALCHE] = "2_M_ALCHE";
	m_jobNameTable[JT_2_M_BARD_ORIENT] = "2_M_BARD_ORIENT";
	m_jobNameTable[JT_2_M_SAGE_B] = "2_M_SAGE_B";
	m_jobNameTable[JT_2_M_SAGE_OLD] = "2_M_SAGE_OLD";
	m_jobNameTable[JT_4_F_ALCHE] = "4_F_ALCHE";
	m_jobNameTable[JT_4_F_CRU] = "4_F_CRU";
	m_jobNameTable[JT_4_F_MONK] = "4_F_MONK";
	m_jobNameTable[JT_4_F_ROGUE] = "4_F_ROGUE";
	m_jobNameTable[JT_4_M_ALCHE_A] = "4_M_ALCHE_A";
	m_jobNameTable[JT_4_M_ALCHE_B] = "4_M_ALCHE_B";
	m_jobNameTable[JT_4_M_ALCHE_C] = "4_M_ALCHE_C";
	m_jobNameTable[JT_4_M_CRU] = "4_M_CRU";
	m_jobNameTable[JT_4_M_CRU_OLD] = "4_M_CRU_OLD";
	m_jobNameTable[JT_4_M_MONK] = "4_M_MONK";
	m_jobNameTable[JT_4_M_SAGE_A] = "4_M_SAGE_A";
	m_jobNameTable[JT_4_M_SAGE_C] = "4_M_SAGE_C";
	m_jobNameTable[JT_4_F_SON] = "4_F_SON";
	m_jobNameTable[JT_4_F_JPN2] = "4_F_JPN2";
	m_jobNameTable[JT_4_F_JPN] = "4_F_JPN";
	m_jobNameTable[JT_4_F_JPNCHIBI] = "4_F_JPNCHIBI";
	m_jobNameTable[JT_4_F_JPNOBA2] = "4_F_JPNOBA2";
	m_jobNameTable[JT_4_F_JPNOBA] = "4_F_JPNOBA";
	m_jobNameTable[JT_4_M_JPN2] = "4_M_JPN2";
	m_jobNameTable[JT_4_M_JPN] = "4_M_JPN";
	m_jobNameTable[JT_4_M_JPNCHIBI] = "4_M_JPNCHIBI";
	m_jobNameTable[JT_4_M_JPNOJI2] = "4_M_JPNOJI2";
	m_jobNameTable[JT_4_M_JPNOJI] = "4_M_JPNOJI";
	m_jobNameTable[JT_8_M_JPNSOLDIER] = "8_M_JPNSOLDIER";
	m_jobNameTable[JT_8_M_JPNMASTER] = "8_M_JPNMASTER";
	m_jobNameTable[JT_4_F_JPNMU] = "4_F_JPNMU";
	m_jobNameTable[JT_4_F_TWGIRL] = "4_F_TWGIRL";
	m_jobNameTable[JT_4_F_TWGRANDMOM] = "4_F_TWGRANDMOM";
	m_jobNameTable[JT_4_F_TWMASKGIRL] = "4_F_TWMASKGIRL";
	m_jobNameTable[JT_4_F_TWMIDWOMAN] = "4_F_TWMIDWOMAN";
	m_jobNameTable[JT_4_M_TWBOY] = "4_M_TWBOY";
	m_jobNameTable[JT_4_M_TWMASKMAN] = "4_M_TWMASKMAN";
	m_jobNameTable[JT_4_M_TWMIDMAN] = "4_M_TWMIDMAN";
	m_jobNameTable[JT_4_M_TWOLDMAN] = "4_M_TWOLDMAN";
	m_jobNameTable[JT_4_M_TWTEAMAN] = "4_M_TWTEAMAN";
	m_jobNameTable[JT_4_M_YOYOROGUE] = "4_M_YOYOROGUE";
	m_jobNameTable[JT_8_M_TWSOLDIER] = "8_M_TWSOLDIER";
	m_jobNameTable[JT_4_F_UMGIRL] = "4_F_UMGIRL";
	m_jobNameTable[JT_4_F_UMOLDWOMAN] = "4_F_UMOLDWOMAN";
	m_jobNameTable[JT_4_F_UMWOMAN] = "4_F_UMWOMAN";
	m_jobNameTable[JT_4_M_UMCHIEF] = "4_M_UMCHIEF";
	m_jobNameTable[JT_4_M_UMDANCEKID2] = "4_M_UMDANCEKID2";
	m_jobNameTable[JT_4_M_UMDANCEKID] = "4_M_UMDANCEKID";
	m_jobNameTable[JT_4_M_UMKID] = "4_M_UMKID";
	m_jobNameTable[JT_4_M_UMOLDMAN] = "4_M_UMOLDMAN";
	m_jobNameTable[JT_4_M_UMSOLDIER] = "4_M_UMSOLDIER";
	m_jobNameTable[JT_4_M_SALVATION] = "4_M_SALVATION";
	m_jobNameTable[JT_4_F_NFDEADKAFRA] = "4_F_NFDEADKAFRA";
	m_jobNameTable[JT_4_F_NFDEADMGCIAN] = "4_F_NFDEADMGCIAN";
	m_jobNameTable[JT_4_F_NFLOSTGIRL] = "4_F_NFLOSTGIRL";
	m_jobNameTable[JT_4_M_NFDEADMAN2] = "4_M_NFDEADMAN2";
	m_jobNameTable[JT_4_M_NFDEADMAN] = "4_M_NFDEADMAN";
	m_jobNameTable[JT_4_M_NFDEADSWDMAN] = "4_M_NFDEADSWDMAN";
	m_jobNameTable[JT_4_M_NFLOSTMAN] = "4_M_NFLOSTMAN";
	m_jobNameTable[JT_4_M_NFMAN] = "4_M_NFMAN";
	m_jobNameTable[JT_4_NFBAT] = "4_NFBAT";
	m_jobNameTable[JT_4_NFCOCK] = "4_NFCOCK";
	m_jobNameTable[JT_4_NFCOFFIN] = "4_NFCOFFIN";
	m_jobNameTable[JT_4_NFWISP] = "4_NFWISP";
	m_jobNameTable[JT_1_F_SIGNZISK] = "1_F_SIGNZISK";
	m_jobNameTable[JT_1_M_SIGN1] = "1_M_SIGN1";
	m_jobNameTable[JT_1_M_SIGNALCHE] = "1_M_SIGNALCHE";
	m_jobNameTable[JT_1_M_SIGNART] = "1_M_SIGNART";
	m_jobNameTable[JT_1_M_SIGNMCNT] = "1_M_SIGNMCNT";
	m_jobNameTable[JT_1_M_SIGNMONK2] = "1_M_SIGNMONK2";
	m_jobNameTable[JT_1_M_SIGNMONK] = "1_M_SIGNMONK";
	m_jobNameTable[JT_1_M_SIGNROGUE] = "1_M_SIGNROGUE";
	m_jobNameTable[JT_4_F_VALKYRIE] = "4_F_VALKYRIE";
	m_jobNameTable[JT_MON_BEGIN] = "Scorpion";
	m_jobNameTable[JT_SCORPION] = "Scorpion";
	m_jobNameTable[JT_PORING] = "Poring";
	m_jobNameTable[JT_THIEF_BUG_AGG] = "Thief_bug_egg";
	m_jobNameTable[JT_HORNET] = "Hornet";
	m_jobNameTable[JT_FARMILIAR] = "Farmiliar";
	m_jobNameTable[JT_THIEF_BUG_LARVA] = "Thief_bug_larva";
	m_jobNameTable[JT_FABRE] = "Fabre";
	m_jobNameTable[JT_PUPA] = "Pupa";
	m_jobNameTable[JT_CONDOR] = "Condor";
	m_jobNameTable[JT_WILOW] = "Wilow";
	m_jobNameTable[JT_CHONCHON] = "Chocho";
	m_jobNameTable[JT_RODA_FROG] = "Roda_frog";
	m_jobNameTable[JT_WOLF] = "Wolf";
	m_jobNameTable[JT_SPORE] = "Spore";
	m_jobNameTable[JT_ZOMBIE] = "Zombie";
	m_jobNameTable[JT_ARCHER_SKELETON] = "Skel_archer";
	m_jobNameTable[JT_THIEF_BUG_FEMALE] = "Thief_bug_female";
	m_jobNameTable[JT_CREAMY] = "Creamy";
	m_jobNameTable[JT_PECOPECO] = "Pecopeco";
	m_jobNameTable[JT_MANDRAGORA] = "Mandragora";
	m_jobNameTable[JT_THIEF_BUG_MALE] = "Thief_bug_male";
	m_jobNameTable[JT_WERE_WOLF] = "Were_wolf";
	m_jobNameTable[JT_ORK_WARRIOR] = "Ork_warrior";
	m_jobNameTable[JT_WORM_TAIL] = "Worm_tail";
	m_jobNameTable[JT_SNAKE] = "Snake";
	m_jobNameTable[JT_MUNAK] = "Munak";
	m_jobNameTable[JT_RAPTICE] = "Raptice";
	m_jobNameTable[JT_SOLDIER_SKELETON] = "Skel_soldier";
	m_jobNameTable[JT_ISIS] = "Isis";
	m_jobNameTable[JT_ANACONDAQ] = "Anacondaq";
	m_jobNameTable[JT_POPORING] = "Poporing";
	m_jobNameTable[JT_VERIT] = "Vorit";
	m_jobNameTable[JT_ELDER_WILOW] = "Elder_wilow";
	m_jobNameTable[JT_THARA_FROG] = "Thara_frog";
	m_jobNameTable[JT_HUNTER_FLY] = "Hunter_fly";
	m_jobNameTable[JT_GHOUL] = "Ghoul";
	m_jobNameTable[JT_SIDE_WINDER] = "Side_winder";
	m_jobNameTable[JT_OSIRIS] = "Osiris";
	m_jobNameTable[JT_BAPHOMET] = "Baphomet";
	m_jobNameTable[JT_GOLEM] = "Golem";
	m_jobNameTable[JT_MUMMY] = "Mummy";
	m_jobNameTable[JT_STEEL_CHONCHON] = "Steel_chocho";
	m_jobNameTable[JT_SEAHORES] = "Seahores";
	m_jobNameTable[JT_OBEAUNE] = "Obeaune";
	m_jobNameTable[JT_MARC] = "Marc";
	m_jobNameTable[JT_DOPPELGANGER] = "Doppelganger";
	m_jobNameTable[JT_PECOPECO_EGG] = "Peco_egg";
	m_jobNameTable[JT_THIEF_BUG_EGG] = "Thief_bug_egg";
	m_jobNameTable[JT_PICKY] = "Picky";
	m_jobNameTable[JT_PICKY_] = "Picky_";
	m_jobNameTable[JT_THIEF_BUG] = "Thief_bug_larva";
	m_jobNameTable[JT_ROCKER] = "Rocker";
	m_jobNameTable[JT_THIEF_BUG_] = "Thief_bug_female";
	m_jobNameTable[JT_THIEF_BUG__] = "Thief_bug_male";
	m_jobNameTable[JT_MUKA] = "Muka";
	m_jobNameTable[JT_SMOKIE] = "Smokie";
	m_jobNameTable[JT_YOYO] = "Yoyo";
	m_jobNameTable[JT_METALLER] = "Metaller";
	m_jobNameTable[JT_MISTRESS] = "Mistress";
	m_jobNameTable[JT_BIGFOOT] = "Bigfoot";
	m_jobNameTable[JT_NIGHTMARE] = "Nightmare";
	m_jobNameTable[JT_PORING_] = "Poring_";
	m_jobNameTable[JT_LUNATIC] = "Lunatic";
	m_jobNameTable[JT_MEGALODON] = "MEGALODON";
	m_jobNameTable[JT_STROUF] = "STROUF";
	m_jobNameTable[JT_VADON] = "VADON";
	m_jobNameTable[JT_CORNUTUS] = "CORNUTUS";
	m_jobNameTable[JT_HYDRA] = "HYDRA";
	m_jobNameTable[JT_SWORD_FISH] = "SWORD_FISH";
	m_jobNameTable[JT_KUKRE] = "KUKRE";
	m_jobNameTable[JT_PIRATE_SKEL] = "PIRATE_SKEL";
	m_jobNameTable[JT_KAHO] = "KAHO";
	m_jobNameTable[JT_CRAB] = "CRAB";
	m_jobNameTable[JT_SHELLFISH] = "SHELLFISH";
	m_jobNameTable[JT_TURTLE] = "TURTLE";
	m_jobNameTable[JT_SKELETON] = "SKELETON";
	m_jobNameTable[JT_POISON_SPORE] = "POISON_SPORE";
	m_jobNameTable[JT_RED_PLANT] = "RED_PLANT";
	m_jobNameTable[JT_BLUE_PLANT] = "BLUE_PLANT";
	m_jobNameTable[JT_GREEN_PLANT] = "GREEN_PLANT";
	m_jobNameTable[JT_YELLOW_PLANT] = "YELLOW_PLANT";
	m_jobNameTable[JT_WHITE_PLANT] = "WHITE_PLANT";
	m_jobNameTable[JT_SHINING_PLANT] = "SHINING_PLANT";
	m_jobNameTable[JT_BLACK_MUSHROOM] = "BLACK_MUSHROOM";
	m_jobNameTable[JT_RED_MUSHROOM] = "RED_MUSHROOM";
	m_jobNameTable[JT_GOLDEN_BUG] = "GOLDEN_BUG";
	m_jobNameTable[JT_ORK_HERO] = "ORK_HERO";
	m_jobNameTable[JT_VOCAL] = "VOCAL";
	m_jobNameTable[JT_TOAD] = "TOAD";
	m_jobNameTable[JT_MASTERING] = "MASTERING";
	m_jobNameTable[JT_DRAGON_FLY] = "DRAGON_FLY";
	m_jobNameTable[JT_VAGABOND_WOLF] = "VAGABOND_WOLF";
	m_jobNameTable[JT_ECLIPSE] = "ECLIPSE";
	m_jobNameTable[JT_PREFIREPILLAR] = "1_ETC_01"; //NOTE: out-of-order entry
	m_jobNameTable[JT_FIREPILLAR] = "1_ETC_01"; //NOTE: out-of-order entry
	m_jobNameTable[JT_AMBERNITE] = "AMBERNITE";
	m_jobNameTable[JT_ANDRE] = "ANDRE";
	m_jobNameTable[JT_ANGELING] = "ANGELING";
	m_jobNameTable[JT_ANT_EGG] = "ANT_EGG";
	m_jobNameTable[JT_ANUBIS] = "ANUBIS";
	m_jobNameTable[JT_ARGIOPE] = "ARGIOPE";
	m_jobNameTable[JT_ARGOS] = "ARGOS";
	m_jobNameTable[JT_BAPHOMET_] = "BAPHOMET_";
	m_jobNameTable[JT_BATHORY] = "BATHORY";
	m_jobNameTable[JT_CARAMEL] = "CARAMEL";
	m_jobNameTable[JT_COCO] = "COCO";
	m_jobNameTable[JT_DENIRO] = "DENIRO";
	m_jobNameTable[JT_DESERT_WOLF] = "DESERT_WOLF";
	m_jobNameTable[JT_DESERT_WOLF_B] = "DESERT_WOLF_B";
	m_jobNameTable[JT_DEVIACE] = "DEVIACE";
	m_jobNameTable[JT_DEVIRUCHI] = "DEVIRUCHI";
	m_jobNameTable[JT_DOKEBI] = "DOKEBI";
	m_jobNameTable[JT_DRAINLIAR] = "DRAINLIAR";
	m_jobNameTable[JT_DRAKE] = "DRAKE";
	m_jobNameTable[JT_DROPS] = "DROPS";
	m_jobNameTable[JT_DUSTINESS] = "DUSTINESS";
	m_jobNameTable[JT_EDDGA] = "EDDGA";
	m_jobNameTable[JT_EGGYRA] = "EGGYRA";
	m_jobNameTable[JT_EVIL_DRUID] = "EVIL_DRUID";
	m_jobNameTable[JT_FLORA] = "FLORA";
	m_jobNameTable[JT_FRILLDORA] = "FRILLDORA";
	m_jobNameTable[JT_GHOSTRING] = "GHOSTRING";
	m_jobNameTable[JT_GIEARTH] = "GIEARTH";
	m_jobNameTable[JT_GOBLIN_1] = "GOBLIN_1";
	m_jobNameTable[JT_GOBLIN_2] = "GOBLIN_2";
	m_jobNameTable[JT_GOBLIN_3] = "GOBLIN_3";
	m_jobNameTable[JT_GOBLIN_4] = "GOBLIN_4";
	m_jobNameTable[JT_GOBLIN_5] = "GOBLIN_5";
	m_jobNameTable[JT_HODE] = "HODE";
	m_jobNameTable[JT_HORN] = "HORN";
	m_jobNameTable[JT_HORONG] = "HORONG";
	m_jobNameTable[JT_JAKK] = "JAKK";
	m_jobNameTable[JT_JOKER] = "JOKER";
	m_jobNameTable[JT_KHALITZBURG] = "KHALITZBURG";
	m_jobNameTable[JT_KOBOLD_1] = "KOBOLD_1";
	m_jobNameTable[JT_KOBOLD_2] = "KOBOLD_2";
	m_jobNameTable[JT_KOBOLD_3] = "KOBOLD_3";
	m_jobNameTable[JT_KOBOLD_4] = "KOBOLD_4";
	m_jobNameTable[JT_KOBOLD_5] = "KOBOLD_5";
	m_jobNameTable[JT_MAGNOLIA] = "MAGNOLIA";
	m_jobNameTable[JT_MANTIS] = "MANTIS";
	m_jobNameTable[JT_MARDUK] = "MARDUK";
	m_jobNameTable[JT_MARINA] = "MARINA";
	m_jobNameTable[JT_MARINE_SPHERE] = "MARINE_SPHERE";
	m_jobNameTable[JT_MARIONETTE] = "MARIONETTE";
	m_jobNameTable[JT_MARSE] = "MARSE";
	m_jobNameTable[JT_MARTIN] = "MARTIN";
	m_jobNameTable[JT_MATYR] = "MATYR";
	m_jobNameTable[JT_MAYA] = "MAYA";
	m_jobNameTable[JT_MEDUSA] = "MEDUSA";
	m_jobNameTable[JT_MINOROUS] = "MINOROUS";
	m_jobNameTable[JT_MOONLIGHT] = "MOONLIGHT";
	m_jobNameTable[JT_MYST] = "MYST";
	m_jobNameTable[JT_ORC_SKELETON] = "ORC_SKELETON";
	m_jobNameTable[JT_ORC_ZOMBIE] = "ORC_ZOMBIE";
	m_jobNameTable[JT_PASANA] = "PASANA";
	m_jobNameTable[JT_PETIT] = "PETIT";
	m_jobNameTable[JT_PETIT_] = "PETIT_";
	m_jobNameTable[JT_PHARAOH] = "PHARAOH";
	m_jobNameTable[JT_PHEN] = "PHEN";
	m_jobNameTable[JT_PHREEONI] = "PHREEONI";
	m_jobNameTable[JT_PIERE] = "PIERE";
	m_jobNameTable[JT_PLANKTON] = "PLANKTON";
	m_jobNameTable[JT_RAFFLESIA] = "RAFFLESIA";
	m_jobNameTable[JT_RAYDRIC] = "RAYDRIC";
	m_jobNameTable[JT_REQUIEM] = "REQUIEM";
	m_jobNameTable[JT_SAND_MAN] = "SAND_MAN";
	m_jobNameTable[JT_SAVAGE] = "SAVAGE";
	m_jobNameTable[JT_SAVAGE_BABE] = "SAVAGE_BABE";
	m_jobNameTable[JT_SCORPION_KING] = "Pupa";
	m_jobNameTable[JT_SKEL_WORKER] = "SKEL_WORKER";
	m_jobNameTable[JT_SOHEE] = "SOHEE";
	m_jobNameTable[JT_SOLDIER_ANDRE] = "SOLDIER_ANDRE";
	m_jobNameTable[JT_SOLDIER_DENIRO] = "SOLDIER_DENIRO";
	m_jobNameTable[JT_SOLDIER_PIERE] = "SOLDIER_PIERE";
	m_jobNameTable[JT_STAINER] = "STAINER";
	m_jobNameTable[JT_TAROU] = "TAROU";
	m_jobNameTable[JT_VITATA] = "VITATA";
	m_jobNameTable[JT_ZENORC] = "ZENORC";
	m_jobNameTable[JT_ZEROM] = "ZEROM";
	m_jobNameTable[JT_WHISPER] = "WHISPER";
	m_jobNameTable[JT_NINE_TAIL] = "NINE_TAIL";
	m_jobNameTable[JT_ZOMBIE_DRAGON] = "dragon_5.gr2";
	m_jobNameTable[JT_THIEF_MUSHROOM] = "RED_MUSHROOM";
	m_jobNameTable[JT_CHONCHON_] = "CHOCHO";
	m_jobNameTable[JT_FABRE_] = "FABRE";
	m_jobNameTable[JT_WHISPER_] = "WHISPER";
	m_jobNameTable[JT_WHISPER_BOSS] = "WHISPER_BOSS";
	m_jobNameTable[JT_SWITCH] = "SWITCH";
	m_jobNameTable[JT_KARAKASA] = "KARAKASA"; //NOTE: out-of-order entry
	m_jobNameTable[JT_SHINOBI] = "SHINOBI"; //NOTE: out-of-order entry
	m_jobNameTable[JT_POISON_TOAD] = "POISON_TOAD"; //NOTE: out-of-order entry
	m_jobNameTable[JT_ANTIQUE_FIRELOCK] = "ANTIQUE_FIRELOCK"; //NOTE: out-of-order entry
	m_jobNameTable[JT_MIYABI_NINGYO] = "MIYABI_NINGYO"; //NOTE: out-of-order entry
	m_jobNameTable[JT_TENGU] = "TENGU"; //NOTE: out-of-order entry
	m_jobNameTable[JT_KAPHA] = "KAPHA"; //NOTE: out-of-order entry
	m_jobNameTable[JT_BON_GUN] = "BON_GUN";
	m_jobNameTable[JT_ORC_ARCHER] = "ORC_ARCHER";
	m_jobNameTable[JT_ORC_LORD] = "ORC_LORD";
	m_jobNameTable[JT_MIMIC] = "MIMIC";
	m_jobNameTable[JT_WRAITH] = "WRAITH";
	m_jobNameTable[JT_ALARM] = "ALARM";
	m_jobNameTable[JT_ARCLOUSE] = "ARCLOUSE";
	m_jobNameTable[JT_RIDEWORD] = "RIDEWORD";
	m_jobNameTable[JT_SKEL_PRISONER] = "SKEL_PRISONER";
	m_jobNameTable[JT_ZOMBIE_PRISONER] = "ZOMBIE_PRISONER";
//	m_jobNameTable[JT_DARK_PRIEST]
	m_jobNameTable[JT_PUNK] = "PUNK";
	m_jobNameTable[JT_ZHERLTHSH] = "ZHERLTHSH";
	m_jobNameTable[JT_RYBIO] = "RYBIO";
	m_jobNameTable[JT_PHENDARK] = "PHENDARK";
	m_jobNameTable[JT_MYSTELTAINN] = "MYSTELTAINN";
	m_jobNameTable[JT_TIRFING] = "TIRFING";
	m_jobNameTable[JT_EXECUTIONER] = "EXECUTIONER";
	m_jobNameTable[JT_ANOLIAN] = "ANOLIAN";
	m_jobNameTable[JT_STING] = "STING";
	m_jobNameTable[JT_WANDER_MAN] = "WANDER_MAN";
	m_jobNameTable[JT_CRAMP] = "CRAMP";
//	m_jobNameTable[JT_FILAMENTOUS]
	m_jobNameTable[JT_BRILIGHT] = "BRILIGHT";
	m_jobNameTable[JT_IRON_FIST] = "IRON_FIST";
	m_jobNameTable[JT_HIGH_ORC] = "HIGH_ORC";
	m_jobNameTable[JT_CHOCO] = "CHOCO";
	m_jobNameTable[JT_STEM_WORM] = "STEM_WORM";
	m_jobNameTable[JT_PENOMENA] = "PENOMENA";
//	m_jobNameTable[JT_ORC_WARRIOR]
//	m_jobNameTable[JT_PECO_EGG]
//	m_jobNameTable[JT_KNIGHT_OF_ABYSS] // elsewhere
	m_jobNameTable[JT_DESERT_WOLF_2] = "desert_wolf";
	m_jobNameTable[JT_SAVAGE_2] = "savage";
	m_jobNameTable[JT_HIGH_ORC_2] = "high_orc";
	m_jobNameTable[JT_ORC_WARRIOR_2] = "orc_warrior";
	m_jobNameTable[JT_POISON_SPORE_2] = "poison_spore";
	m_jobNameTable[JT_CHOCO_2] = "choco";
	m_jobNameTable[JT_KOBOLD_1_2] = "kobold_1";
	m_jobNameTable[JT_GOBLIN_1_2] = "goblin_1";
	m_jobNameTable[JT_PHEN_2] = "phen";
	m_jobNameTable[JT_FABRE_2] = "fabre";
	m_jobNameTable[JT_PUPA_2] = "pupa";
	m_jobNameTable[JT_CREAMY_2] = "creamy";
	m_jobNameTable[JT_PECO_EGG_2] = "peco_egg";
	m_jobNameTable[JT_PECOPECO_2] = "pecopeco";
	m_jobNameTable[JT_YOYO_2] = "yoyo";
	m_jobNameTable[JT_ORK_WARRIOR_2] = "ork_warrior";
	m_jobNameTable[JT_ANT_EGG_2] = "ant_egg";
	m_jobNameTable[JT_ANDRE_2] = "andre";
	m_jobNameTable[JT_PIERE_2] = "piere";
	m_jobNameTable[JT_DENIRO_2] = "deniro";
	m_jobNameTable[JT_PICKY_2] = "picky";
	m_jobNameTable[JT_PICKY__2] = "picky_";
	m_jobNameTable[JT_KNIGHT_OF_ABYSS] = "knight_of_abyss"; //NOTE: out-of-order entry
	m_jobNameTable[JT_MARIN] = "MARIN";
	m_jobNameTable[JT_SASQUATCH] = "SASQUATCH";
	m_jobNameTable[JT_JAKK_XMAS] = "JAKK_XMAS";
	m_jobNameTable[JT_GOBLINE_XMAS] = "GOBLINE_XMAS";
	m_jobNameTable[JT_COOKIE_XMAS] = "COOKIE_XMAS";
	m_jobNameTable[JT_ANTONIO] = "ANTONIO";
	m_jobNameTable[JT_CRUISER] = "CRUISER";
	m_jobNameTable[JT_MYSTCASE] = "MYSTCASE";
	m_jobNameTable[JT_CHEPET] = "CHEPET";
	m_jobNameTable[JT_KNIGHT_OF_WINDSTORM] = "KNIGHT_OF_WINDSTORM";
	m_jobNameTable[JT_GARM] = "GARM";
	m_jobNameTable[JT_GARGOYLE] = "Gargoyle";
	m_jobNameTable[JT_RAGGLER] = "Raggler";
	m_jobNameTable[JT_NERAID] = "Neraid";
	m_jobNameTable[JT_PEST] = "Pest";
	m_jobNameTable[JT_INJUSTICE] = "Injustice";
	m_jobNameTable[JT_GOBLIN_ARCHER] = "Goblin_Archer";
	m_jobNameTable[JT_GRYPHON] = "Gryphon";
	m_jobNameTable[JT_DARK_FRAME] = "Dark_Frame";
	m_jobNameTable[JT_WILD_ROSE] = "Wild_Rose";
	m_jobNameTable[JT_MUTANT_DRAGON] = "Mutant_Dragon";
	m_jobNameTable[JT_WIND_GHOST] = "Wind_Ghost";
	m_jobNameTable[JT_MERMAN] = "Merman";
	m_jobNameTable[JT_COOKIE] = "Cookie";
	m_jobNameTable[JT_ASTER] = "Aster";
	m_jobNameTable[JT_CARAT] = "Carat";
	m_jobNameTable[JT_BLOODY_KNIGHT] = "Bloody_Knight";
	m_jobNameTable[JT_CLOCK] = "Clock";
	m_jobNameTable[JT_C_TOWER_MANAGER] = "C_Tower_Manager";
	m_jobNameTable[JT_ALLIGATOR] = "Alligator";
	m_jobNameTable[JT_DARK_LORD] = "Dark_Lord";
	m_jobNameTable[JT_ORC_LADY] = "Orc_Lady";
	m_jobNameTable[JT_MEGALITH] = "Megalith";
	m_jobNameTable[JT_ALICE] = "Alice";
	m_jobNameTable[JT_RAYDRIC_ARCHER] = "Raydric_Archer";
	m_jobNameTable[JT_GREATEST_GENERAL] = "Greatest_General";
	m_jobNameTable[JT_STALACTIC_GOLEM] = "Stalactic_Golem";
	m_jobNameTable[JT_TRI_JOINT] = "Tri_Joint";
	m_jobNameTable[JT_STEAM_GOBLIN] = "Steam_Goblin";
	m_jobNameTable[JT_SAGEWORM] = "SageWorm";
	m_jobNameTable[JT_KOBOLD_ARCHER] = "Kobold_Archer";
	m_jobNameTable[JT_CHIMERA] = "Chimera";
	m_jobNameTable[JT_HUGELING] = "Hugeling90_6.gr2";
	m_jobNameTable[JT_ARCHER_GUARDIAN] = "Aguardian90_8.gr2";
	m_jobNameTable[JT_KNIGHT_GUARDIAN] = "Kguardian90_7.gr2";
	m_jobNameTable[JT_SOLDIER_GUARDIAN] = "Sguardian90_9.gr2";
	m_jobNameTable[JT_EMPELIUM] = "Empelium90_0.gr2";
	m_jobNameTable[JT_MAYA_PUPLE] = "maya_puple";
	m_jobNameTable[JT_SKELETON_GENERAL] = "SKELETON_GENERAL";
	m_jobNameTable[JT_WRAITH_DEAD] = "WRAITH_DEAD";
	m_jobNameTable[JT_MINI_DEMON] = "MINI_DEMON";
	m_jobNameTable[JT_CREMY_FEAR] = "CREMY_FEAR";
	m_jobNameTable[JT_KILLER_MANTIS] = "KILLER_MANTIS";
	m_jobNameTable[JT_OWL_BARON] = "OWL_BARON";
	m_jobNameTable[JT_KOBOLD_LEADER] = "KOBOLT_LEADER";
	m_jobNameTable[JT_ANCIENT_MUMMY] = "ANCIENT_MUMMY";
	m_jobNameTable[JT_ZOMBIE_MASTER] = "ZOMBIE_MASTER";
	m_jobNameTable[JT_GOBLIN_LEADER] = "GOBLIN_LEADER";
	m_jobNameTable[JT_CATERPILLAR] = "CATERPILLAR";
	m_jobNameTable[JT_AM_MUT] = "AM_MUT";
	m_jobNameTable[JT_DARK_ILLUSION] = "DARK_ILLUSION";
	m_jobNameTable[JT_GIANT_HONET] = "GIANT_HONET";
	m_jobNameTable[JT_GIANT_SPIDER] = "GIANT_SPIDER";
	m_jobNameTable[JT_ANCIENT_WORM] = "ANCIENT_WORM";
	m_jobNameTable[JT_LEIB_OLMAI] = "LEIB_OLMAI";
	m_jobNameTable[JT_CAT_O_NINE_TAIL] = "CAT_O_NINE_TAIL";
	m_jobNameTable[JT_PANZER_GOBLIN] = "PANZER_GOBLIN";
	m_jobNameTable[JT_GAJOMART] = "GAJOMART";
	m_jobNameTable[JT_MAJORUROS] = "MAJORUROS";
	m_jobNameTable[JT_GULLINBURSTI] = "GULLINBURSTI";
	m_jobNameTable[JT_TURTLE_GENERAL] = "TURTLE_GENERAL";
	m_jobNameTable[JT_MOBSTER] = "MOBSTER";
	m_jobNameTable[JT_PERMETER] = "PERMETER";
	m_jobNameTable[JT_ASSULTER] = "ASSULTER";
	m_jobNameTable[JT_SOLIDER] = "SOLIDER";
	m_jobNameTable[JT_FUR_SEAL] = "FUR_SEAL";
	m_jobNameTable[JT_HEATER] = "HEATER";
	m_jobNameTable[JT_FREEZER] = "FREEZER";
	m_jobNameTable[JT_OWL_DUKE] = "OWL_DUKE";
	m_jobNameTable[JT_DRAGON_TAIL] = "DRAGON_TAIL";
	m_jobNameTable[JT_SPRING_RABBIT] = "SPRING_RABBIT";
	m_jobNameTable[JT_SEE_OTTER] = "SEE_OTTER";
	m_jobNameTable[JT_TREASURE_BOX1] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX2] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX3] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX4] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX5] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX6] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX7] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX8] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX9] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX10] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX11] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX12] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX13] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX14] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX15] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX16] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX17] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX18] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX19] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX20] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX21] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX22] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX23] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX24] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX25] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX26] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX27] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX28] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX29] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX30] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX31] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX32] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX33] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX34] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX35] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX36] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX37] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX38] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX39] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_TREASURE_BOX40] = "TREASUREBOX_2.gr2";
	m_jobNameTable[JT_G_ASSULTER] = "G_ASSULTER";
	m_jobNameTable[JT_APOCALIPS] = "APOCALIPS";
	m_jobNameTable[JT_MEDUSA] = "MEDUSA"; //NOTE: out-of-place duplicate
	m_jobNameTable[JT_LAVA_GOLEM] = "LAVA_GOLEM";
	m_jobNameTable[JT_BLAZZER] = "BLAZZER";
	m_jobNameTable[JT_GEOGRAPHER] = "GEOGRAPHER";
	m_jobNameTable[JT_GRAND_PECO] = "GRAND_PECO";
	m_jobNameTable[JT_SUCCUBUS] = "SUCCUBUS";
	m_jobNameTable[JT_FAKE_ANGEL] = "FAKE_ANGEL";
	m_jobNameTable[JT_GOAT] = "GOAT";
	m_jobNameTable[JT_LORD_OF_DEATH] = "LORD_OF_DEATH";
	m_jobNameTable[JT_PASANA] = "PASANA"; //NOTE: out-of-place duplicate
	m_jobNameTable[JT_INCUBUS] = "INCUBUS";
	m_jobNameTable[JT_THE_PAPER] = "THE_PAPER";
	m_jobNameTable[JT_PHARAOH] = "PHARAOH"; //NOTE: out-of-place duplicate
	m_jobNameTable[JT_HARPY] = "HARPY";
	m_jobNameTable[JT_ELDER] = "ELDER";
	m_jobNameTable[JT_DEMON_PUNGUS] = "DEMON_PUNGUS";
	m_jobNameTable[JT_NIGHTMARE_TERROR] = "NIGHTMARE_TERROR";
	m_jobNameTable[JT_DRILLER] = "DRILLER";
	m_jobNameTable[JT_GRIZZLY] = "GRIZZLY";
	m_jobNameTable[JT_DIABOLIC] = "DIABOLIC";
	m_jobNameTable[JT_EXPLOSION] = "EXPLOSION";
	m_jobNameTable[JT_DELETER] = "DELETER";
	m_jobNameTable[JT_DELETER_] = "DELETER_";
	m_jobNameTable[JT_SLEEPER] = "SLEEPER";
	m_jobNameTable[JT_GIG] = "GIG";
	m_jobNameTable[JT_ARCHANGELING] = "ARCHANGELING";
	m_jobNameTable[JT_DRACULA] = "DRACULA";
	m_jobNameTable[JT_VIOLY] = "VIOLY";
	m_jobNameTable[JT_GALAPAGO] = "GALAPAGO";
	m_jobNameTable[JT_ROTAR_ZAIRO] = "ROTAR_ZAIRO";
//	m_jobNameTable[JT_G_MUMMY]
//	m_jobNameTable[JT_G_ZOMBIE]
	m_jobNameTable[JT_CRYSTAL_1] = "CRYSTAL_1";
	m_jobNameTable[JT_CRYSTAL_2] = "CRYSTAL_2";
	m_jobNameTable[JT_CRYSTAL_3] = "CRYSTAL_3";
	m_jobNameTable[JT_CRYSTAL_4] = "CRYSTAL_4";
	m_jobNameTable[JT_EVENT_BAPHO] = "EVENT_BAPHO";
//	m_jobNameTable[JT_KARAKASA] // elsewhere
//	m_jobNameTable[JT_SHINOBI] // elsewhere
//	m_jobNameTable[JT_POISON_TOAD] // elsewhere
//	m_jobNameTable[JT_ANTIQUE_FIRELOCK] // elsewhere
//	m_jobNameTable[JT_MIYABI_NINGYO] // elsewhere
//	m_jobNameTable[JT_TENGU] // elsewhere
//	m_jobNameTable[JT_KAPHA] // elsewhere
	m_jobNameTable[JT_DOKEBI_] = "DOKEBI_";
	m_jobNameTable[JT_BLOOD_BUTTERFLY] = "BLOOD_BUTTERFLY";
	m_jobNameTable[JT_RICE_CAKE_BOY] = "RICE_CAKE_BOY";
	m_jobNameTable[JT_LIVE_PEACH_TREE] = "LIVE_PEACH_TREE";
	m_jobNameTable[JT_PEACH_TREE_BULLET] = "PEACH_TREE_BULLET";
	m_jobNameTable[JT_EVIL_CLOUD_HERMIT] = "EVIL_CLOUD_HERMIT";
	m_jobNameTable[JT_WILD_GINSENG] = "WILD_GINSENG";
	m_jobNameTable[JT_GINSENG_BULLET] = "GINSENG_BULLET";
	m_jobNameTable[JT_BABY_LEOPARD] = "BABY_LEOPARD";
	m_jobNameTable[JT_WICKED_NYMPH] = "WICKED_NYMPH";
	m_jobNameTable[JT_ZIPPER_BEAR] = "ZIPPER_BEAR";
	m_jobNameTable[JT_DARK_SNAKE_LORD] = "DARK_SNAKE_LORD";
	m_jobNameTable[JT_G_FARMILIAR] = "FARMILIAR";
	m_jobNameTable[JT_G_ARCHER_SKELETON] = "Skel_archer";
	m_jobNameTable[JT_G_ISIS] = "ISIS";
	m_jobNameTable[JT_G_HUNTER_FLY] = "HUNTER_FLY";
	m_jobNameTable[JT_G_GHOUL] = "GHOUL";
	m_jobNameTable[JT_G_SIDE_WINDER] = "SIDE_WINDER";
	m_jobNameTable[JT_G_OBEAUNE] = "OBEAUNE";
	m_jobNameTable[JT_G_MARC] = "MARC";
	m_jobNameTable[JT_G_NIGHTMARE] = "NIGHTMARE";
	m_jobNameTable[JT_G_POISON_SPORE] = "POISON_SPORE";
	m_jobNameTable[JT_G_ARGIOPE] = "ARGIOPE";
	m_jobNameTable[JT_G_ARGOS] = "ARGOS";
	m_jobNameTable[JT_G_BAPHOMET_] = "BAPHOMET_";
	m_jobNameTable[JT_G_DESERT_WOLF] = "DESERT_WOLF";
	m_jobNameTable[JT_G_DEVIRUCHI] = "DEVIRUCHI";
	m_jobNameTable[JT_G_DRAINLIAR] = "DRAINLIAR";
	m_jobNameTable[JT_G_EVIL_DRUID] = "EVIL_DRUID";
	m_jobNameTable[JT_G_JAKK] = "JAKK";
	m_jobNameTable[JT_G_JOKER] = "JOKER";
	m_jobNameTable[JT_G_KHALITZBURG] = "KHALITZBURG";
	m_jobNameTable[JT_G_HIGH_ORC] = "HIGH_ORC";
	m_jobNameTable[JT_G_STEM_WORM] = "STEM_WORM";
	m_jobNameTable[JT_G_PENOMENA] = "PENOMENA";
	m_jobNameTable[JT_G_SASQUATCH] = "SASQUATCH";
	m_jobNameTable[JT_G_CRUISER] = "CRUISER";
	m_jobNameTable[JT_G_CHEPET] = "CHEPET";
	m_jobNameTable[JT_G_RAGGLER] = "RAGGLER";
	m_jobNameTable[JT_G_INJUSTICE] = "INJUSTICE";
	m_jobNameTable[JT_G_GRYPHON] = "GRYPHON";
	m_jobNameTable[JT_G_DARK_FRAME] = "DARK_FRAME";
	m_jobNameTable[JT_G_MUTANT_DRAGON] = "MUTANT_DRAGON";
	m_jobNameTable[JT_G_WIND_GHOST] = "WIND_GHOST";
	m_jobNameTable[JT_G_MERMAN] = "MERMAN";
	m_jobNameTable[JT_G_ORC_LADY] = "ORC_LADY";
	m_jobNameTable[JT_G_RAYDRIC_ARCHER] = "RAYDRIC_ARCHER";
	m_jobNameTable[JT_G_TRI_JOINT] = "TRI_JOINT";
	m_jobNameTable[JT_G_KOBOLD_ARCHER] = "KOBOLD_ARCHER";
	m_jobNameTable[JT_G_CHIMERA] = "CHIMERA";
	m_jobNameTable[JT_G_MANTIS] = "MANTIS";
	m_jobNameTable[JT_G_MARDUK] = "MARDUK";
	m_jobNameTable[JT_G_MARIONETTE] = "MARIONETTE";
	m_jobNameTable[JT_G_MATYR] = "MATYR";
	m_jobNameTable[JT_G_MINOROUS] = "MINOROUS";
	m_jobNameTable[JT_G_ORC_SKELETON] = "ORC_SKELETON";
	m_jobNameTable[JT_G_ORC_ZOMBIE] = "ORC_ZOMBIE";
	m_jobNameTable[JT_G_PASANA] = "PASANA";
	m_jobNameTable[JT_G_PETIT] = "PETIT";
	m_jobNameTable[JT_G_PETIT_] = "PETIT_";
	m_jobNameTable[JT_G_RAYDRIC] = "RAYDRIC";
	m_jobNameTable[JT_G_REQUIEM] = "REQUIEM";
	m_jobNameTable[JT_G_SKEL_WORKER] = "SKEL_WORKER";
	m_jobNameTable[JT_G_ZEROM] = "ZEROM";
	m_jobNameTable[JT_G_NINE_TAIL] = "NINE_TAIL";
	m_jobNameTable[JT_G_BON_GUN] = "BON_GUN";
	m_jobNameTable[JT_G_ORC_ARCHER] = "ORC_ARCHER";
	m_jobNameTable[JT_G_MIMIC] = "MIMIC";
	m_jobNameTable[JT_G_WRAITH] = "WRAITH";
	m_jobNameTable[JT_G_ALARM] = "ALARM";
	m_jobNameTable[JT_G_ARCLOUSE] = "ARCLOUSE";
	m_jobNameTable[JT_G_RIDEWORD] = "RIDEWORD";
	m_jobNameTable[JT_G_SKEL_PRISONER] = "SKEL_PRISONER";
	m_jobNameTable[JT_G_ZOMBIE_PRISONER] = "ZOMBIE_PRISONER";
	m_jobNameTable[JT_G_PUNK] = "PUNK";
	m_jobNameTable[JT_G_ZHERLTHSH] = "ZHERLTHSH";
	m_jobNameTable[JT_G_RYBIO] = "RYBIO";
	m_jobNameTable[JT_G_PHENDARK] = "PHENDARK";
	m_jobNameTable[JT_G_MYSTELTAINN] = "MYSTELTAINN";
	m_jobNameTable[JT_G_TIRFING] = "TIRFING";
	m_jobNameTable[JT_G_EXECUTIONER] = "EXECUTIONER";
	m_jobNameTable[JT_G_ANOLIAN] = "ANOLIAN";
	m_jobNameTable[JT_G_STING] = "STING";
	m_jobNameTable[JT_G_WANDER_MAN] = "WANDER_MAN";
	m_jobNameTable[JT_G_DOKEBI] = "DOKEBI";
	m_jobNameTable[JT_INCANTATION_SAMURAI] = "INCANTATION_SAMURAI";
	m_jobNameTable[JT_DRYAD] = "DRYAD";
	m_jobNameTable[JT_KIND_OF_BEETLE] = "KIND_OF_BEETLE";
	m_jobNameTable[JT_STONE_SHOOTER] = "STONE_SHOOTER";
	m_jobNameTable[JT_STONE_SHOOTER_BULLET] = "STONE_SHOOTER_BULLET";
	m_jobNameTable[JT_WOODEN_GOLEM] = "WOODEN_GOLEM";
	m_jobNameTable[JT_WOOTAN_SHOOTER] = "WOOTAN_SHOOTER";
	m_jobNameTable[JT_WOOTAN_FIGHTER] = "WOOTAN_FIGHTER";
	m_jobNameTable[JT_PARASITE] = "PARASITE";
	m_jobNameTable[JT_PARASITE_BULLET] = "PARASITE_BULLET";
	m_jobNameTable[JT_PORING_V] = "Poring";
	m_jobNameTable[JT_GIBBET] = "GIBBET";
	m_jobNameTable[JT_DULLAHAN] = "DULLAHAN";
	m_jobNameTable[JT_LOLI_RURI] = "LOLI_RURI";
	m_jobNameTable[JT_DISGUISE] = "DISGUISE";
	m_jobNameTable[JT_BLOODY_MURDERER] = "BLOODY_MURDERER";
	m_jobNameTable[JT_QUVE] = "QUVE";
	m_jobNameTable[JT_LUDE] = "LUDE";
	m_jobNameTable[JT_HYLOZOIST] = "HYLOZOIST";
	m_jobNameTable[JT_AMON_RA] = "AMON_RA";

	m_sexNameTable.resize(2, "F");
	m_sexNameTable[SEX_FEMALE] = "F";
	m_sexNameTable[SEX_MALE] = "M";

	m_guildSkillUseLevelList.resize(5, 0);
	m_skillUseLevelList.resize(383, 0);
}


hook_method<void (CSession::*)(void)> CSession::_InitTalkTypeTable(SAKEXE, "CSession::InitTalkTypeTable");
void CSession::InitTalkTypeTable(void) // line 4888
{
	return (this->*_InitTalkTypeTable)();

	m_talkTypeTable.clear();

	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/help", TT_HELP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/h", TT_HELP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/killall", TT_DISCONNECT_ALL_CHARACTER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/wjqthrwk", TT_REQ_NUM_USER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/snrn", TT_REQ_NUM_USER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/who", TT_REQ_NUM_USER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/w", TT_REQ_NUM_USER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/dmadkr", TT_MUSIC_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/bgm", TT_MUSIC_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/effect", TT_EFFECT_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/dlvprxm", TT_EFFECT_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/sound", TT_EFFECT_SOUND_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/gyrhkdma", TT_EFFECT_SOUND_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/skip", TT_FRAMESKIP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/ex", TT_REQ_WHISPER_LIST));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/inall", TT_REQ_WHISPER_STATE_IN));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/exall", TT_REQ_WHISPER_STATE_EX));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/sit", TT_REQ_SIT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/dkswrl", TT_REQ_SIT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/stand", TT_REQ_STAND));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/tjrl", TT_REQ_STAND));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/coxldqkd", TT_MAKE_CHATROOMMAKEWND));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/chat", TT_MAKE_CHATROOMMAKEWND));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/xkfxhl", TT_REQ_LEAVE_GROUP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/leave", TT_REQ_LEAVE_GROUP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/stat", TT_STAT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_SURPRISE), TT_REQ_EMOTION_SURPRISE));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_QUESTION), TT_REQ_EMOTION_QUESTION));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/delight", TT_REQ_EMOTION_DELIGHT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/q", TT_REQ_EXIT_ROOM));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/rlQma", TT_REQ_EMOTION_DELIGHT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/heart", TT_REQ_EMOTION_THROB));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/gkxm", TT_REQ_EMOTION_THROB));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/sweat", TT_REQ_EMOTION_SWEAT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/Eka", TT_REQ_EMOTION_SWEAT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/wnajr", TT_REQ_EMOTION_ROCK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/qh", TT_REQ_EMOTION_WRAP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/bo", TT_REQ_EMOTION_WRAP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/rkdnl", TT_REQ_EMOTION_SCISSOR));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/gawi", TT_REQ_EMOTION_SCISSOR));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/bawi", TT_REQ_EMOTION_ROCK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/qkdnl", TT_REQ_EMOTION_ROCK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/whkvy", TT_MAP_POS));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/wkdth", TT_MAP_POS));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/where", TT_MAP_POS));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_THINK), TT_REQ_EMOTION_THINK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/money", TT_REQ_EMOTION_MONEY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/ehs", TT_REQ_EMOTION_MONEY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/anger", TT_REQ_EMOTION_ANGER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/ghk", TT_REQ_EMOTION_ANGER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/fret", TT_REQ_EMOTION_FRET));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/Wkwmd", TT_REQ_EMOTION_FRET));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/aha", TT_REQ_EMOTION_AHA));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/dkgk", TT_REQ_EMOTION_AHA));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/tip", TT_OPEN_TIP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/rldjr", TT_REMEMBER_WARPPOINT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/memo", TT_REMEMBER_WARPPOINT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/snap", TT_ATTACK_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/tmsoq", TT_ATTACK_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/skillsnap", TT_SKILL_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/tmzlftmsoq", TT_SKILL_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/itemsnap", TT_ITEM_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/dkdlxpatmsoq", TT_ITEM_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/rkfanfl", TT_REQ_SAVE_CHAT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/savechat", TT_REQ_SAVE_CHAT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/miss", TT_MISS_EFFECT_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/noshift", TT_NOSHIFT_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/noctrl", TT_NOCTRL_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/ns", TT_NOSHIFT_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/nc", TT_NOCTRL_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/aura", TT_AURA_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/doridori", TT_DORIDORI_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/bingbing", TT_BINGBING_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/bangbang", TT_BANGBANG_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/skillfail", TT_SKILLFAIL_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/sf", TT_SKILLFAIL_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/quickspell", TT_QUICKSPELL_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/q1", TT_QUICKSPELL_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/quickspell2", TT_QUICKSPELL2_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/q2", TT_QUICKSPELL2_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/q3", TT_QUICKSPELL3_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/notalkmsg", TT_NOTALKMSG_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/nm", TT_NOTALKMSG_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/set1", TT_SET1_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/camera", TT_FIXED_CAMERA_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/tp", TT_TESTPACKET));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/fog", TT_FOG));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xC7", TT_HELP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC1\xA2\xBC\xD3\xC0\xDA", TT_REQ_NUM_USER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xB4\xA9\xB1\xB8", TT_REQ_NUM_USER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xB8", TT_REQ_NUM_USER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC1\xC8", TT_REQ_NUM_USER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC0\xBD\xBE\xC7", TT_MUSIC_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xD0\xC8\xE5", TT_MUSIC_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC0\xCC\xC6\xE5\xC6\xAE", TT_EFFECT_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC8\xBF\xB0\xFA\xC0\xBD", TT_EFFECT_SOUND_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xB3\xAA\xA4\xC1\xA4\xC4", TT_FRAMESKIP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC2\xF7\xB4\xDC", TT_REQ_WHISPER_LIST));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC7\xD8\xC1\xA6\xC0\xFC\xBA\xCE", TT_REQ_WHISPER_STATE_IN));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC2\xF7\xB4\xDC\xC0\xFC\xBA\xCE", TT_REQ_WHISPER_STATE_EX));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBE\xC9\xB1\xE2", TT_REQ_SIT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\x86\x6E", TT_REQ_SIT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBC\xAD\xB1\xE2", TT_REQ_STAND));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xA4\xA4\xB5\xB9\xB6", TT_REQ_STAND));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC3\xA4\xC6\xC3\xB9\xE6", TT_MAKE_CHATROOMMAKEWND));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC3\xCE\xA4\xB5", TT_MAKE_CHATROOMMAKEWND));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xB2", TT_REQ_EXIT_ROOM));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC5\xBB\xC5\xF0", TT_REQ_LEAVE_GROUP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_DELIGHT), TT_REQ_EMOTION_DELIGHT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_THROB), TT_REQ_EMOTION_THROB));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_SWEAT), TT_REQ_EMOTION_SWEAT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC1\xD6\xB8\xD4", TT_REQ_EMOTION_ROCK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBA\xB8", TT_REQ_EMOTION_WRAP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xB0\xA1\xC0\xA7", TT_REQ_EMOTION_SCISSOR));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xB9\xD9\xC0\xA7", TT_REQ_EMOTION_ROCK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC1\xC2\xC7\xA5", TT_MAP_POS));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC0\xE5\xBC\xD2", TT_MAP_POS));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_MONEY), TT_REQ_EMOTION_MONEY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_ANGER), TT_REQ_EMOTION_ANGER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_FRET), TT_REQ_EMOTION_FRET));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_AHA), TT_REQ_EMOTION_AHA));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBB\xFE\xA4\xC4", TT_OPEN_TIP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xB1\xE2\xBE\xEF", TT_REMEMBER_WARPPOINT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xB4\xA9\xB8\xDE", TT_ATTACK_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBD\xBA\xB3\xC0", TT_ATTACK_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xB3\xAA\xA4\xC1\xA4\xD3\xA4\xD3\xB4\xA9\xB8\xDE", TT_SKILL_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBD\xBA\xC5\xB3\xBD\xBA\xB3\xC0", TT_SKILL_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xC1\xA4\xB5\xB5\xE5\xB4\xA9\xB8\xDE", TT_ITEM_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBE\xC6\xC0\xCC\xC5\xDB\xBD\xBA\xB3\xC0", TT_ITEM_SNAP_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xB0\xA5\xB9\xAB\xB8\xAE", TT_REQ_SAVE_CHAT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/autosavechat", TT_REQ_AUTO_SAVE_CHAT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/night", TT_TOGGLE_NIGHT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/rain", TT_TOGGLE_RAIN));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/snow", TT_TOGGLE_SNOW));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/objlight", TT_TOGGLE_OBJLIGHT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/weather", TT_TOGGLE_WEATHER));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/battlemode", TT_BATTLE_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/bm", TT_BATTLE_ON_OFF));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_BIGTHROB), TT_REQ_EMOTION_BIGTHROB));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_THANKS), TT_REQ_EMOTION_THANKS));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xA3", TT_REQ_EMOTION_THANKS));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_KEK), TT_REQ_EMOTION_KEK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_SORRY), TT_REQ_EMOTION_SORRY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/sorry", TT_REQ_EMOTION_SORRY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_SMILE), TT_REQ_EMOTION_SMILE));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC7\xCF\xC7\xCF", TT_REQ_EMOTION_SMILE));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xB7", TT_REQ_EMOTION_SMILE));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/smile", TT_REQ_EMOTION_SMILE));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xA1", TT_REQ_EMOTION_DELIGHT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_PROFUSELY_SWEAT), TT_REQ_EMOTION_PROFUSELY_SWEAT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_SCRATCH), TT_REQ_EMOTION_SCRATCH));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_BEST), TT_REQ_EMOTION_BEST));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBF\xF8\xC3\xF2", TT_REQ_EMOTION_BEST));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xBA", TT_REQ_EMOTION_BEST));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_STARE_ABOUT), TT_REQ_EMOTION_STARE_ABOUT));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_HUK), TT_REQ_EMOTION_HUK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xBE", TT_REQ_EMOTION_HUK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_O), TT_REQ_EMOTION_O));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/o", TT_REQ_EMOTION_O));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_X), TT_REQ_EMOTION_X));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/x", TT_REQ_EMOTION_X));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_HELP), TT_REQ_EMOTION_HELP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xBA\xA4\xBA", TT_REQ_EMOTION_HELP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/help", TT_REQ_EMOTION_HELP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_GO), TT_REQ_EMOTION_GO));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_CRY), TT_REQ_EMOTION_CRY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_KIK), TT_REQ_EMOTION_KIK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC5\xB1", TT_REQ_EMOTION_KIK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xBB", TT_REQ_EMOTION_KIK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC4\xC9\xC4\xC9", TT_REQ_EMOTION_KIK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_CHUP), TT_REQ_EMOTION_CHUP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_CHUPCHUP), TT_REQ_EMOTION_CHUPCHUP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_HNG), TT_REQ_EMOTION_HNG));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xB2\xF4\xB4\xF6", TT_REQ_EMOTION_OK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_OK), TT_REQ_EMOTION_OK));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC0\xCC\xB8\xF0\xBC\xC7", TT_SHOW_EMOTIONLIST));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/emotion", TT_SHOW_EMOTIONLIST));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/clipmouse", TT_CLIPMOUSE));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/lightmap", TT_LIGHTMAP));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_STARE), TT_REQ_EMOTION_STARE));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xB9", TT_REQ_EMOTION_STARE));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_HUNGRY), TT_REQ_EMOTION_HUNGRY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_COOL), TT_REQ_EMOTION_COOL));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_MERONG), TT_REQ_EMOTION_MERONG));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_SHY), TT_REQ_EMOTION_SHY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBA\xCE", TT_REQ_EMOTION_SHY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_GOODBOY), TT_REQ_EMOTION_GOODBOY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_SPTIME), TT_REQ_EMOTION_SPTIME));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xBF\xA5", TT_REQ_EMOTION_SPTIME));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_SEXY), TT_REQ_EMOTION_SEXY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_COMEON), TT_REQ_EMOTION_COMEON));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_SLEEPY), TT_REQ_EMOTION_SLEEPY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xB8", TT_REQ_EMOTION_SLEEPY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_CONGRATULATION), TT_REQ_EMOTION_CONGRATULATION));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xA4\xBA\xA4\xBB", TT_REQ_EMOTION_CONGRATULATION));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>(MsgStr(MSI_EMOTION_HPTIME), TT_REQ_EMOTION_HPTIME));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/\xC7\xC7", TT_REQ_EMOTION_HPTIME));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e1", TT_REQ_EMOTION_STARE));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e2", TT_REQ_EMOTION_HUNGRY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e3", TT_REQ_EMOTION_COOL));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e4", TT_REQ_EMOTION_MERONG));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e5", TT_REQ_EMOTION_SHY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e6", TT_REQ_EMOTION_GOODBOY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e7", TT_REQ_EMOTION_SPTIME));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e8", TT_REQ_EMOTION_SEXY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e9", TT_REQ_EMOTION_COMEON));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e10", TT_REQ_EMOTION_SLEEPY));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e11", TT_REQ_EMOTION_CONGRATULATION));
	m_talkTypeTable.push_back(mystd::pair<const char*, enum TALKTYPE>("/e12", TT_REQ_EMOTION_HPTIME));

	mystd::stable_sort(m_talkTypeTable.begin(), m_talkTypeTable.end(), DComp());
}


hook_method<int (CSession::*)(void)> CSession::_IsEnableSiegeMode(SAKEXE, "CSession::IsEnableSiegeMode");
int CSession::IsEnableSiegeMode() // line 3487-3489 (Session2.cpp)
{
	return (this->*_IsEnableSiegeMode)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_InitMapNameTable(SERVER, "CSession::InitMapNameTable");
int CSession::InitMapNameTable(void) // line 5254
{
	return (this->*_InitMapNameTable)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_InitMp3NameTable(SERVER, "CSession::InitMp3NameTable");
int CSession::InitMp3NameTable(void) // line 5314
{
	return (this->*_InitMp3NameTable)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_InitIndoorRswTable(SERVER, "CSession::InitIndoorRswTable");
int CSession::InitIndoorRswTable(void) // line 5353
{
	return (this->*_InitIndoorRswTable)();

    m_objParser.CommonObject::TokenFileToPCharList(m_indoorRswTable, "indoorRswTable.txt", false);
	mystd::sort(m_indoorRswTable.begin(), m_indoorRswTable.end(), CharPrtLess()); //inlined
	return 1;
}


hook_method<int (CSession::*)(void)> CSession::_InitEnableObjLightMapTable(SERVER, "CSession::InitEnableObjLightMapTable");
int CSession::InitEnableObjLightMapTable(void) // line 5283
{
	return (this->*_InitEnableObjLightMapTable)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_RefreshSkillItemWnd(SAKEXE, "CSession::RefreshSkillItemWnd");
void CSession::RefreshSkillItemWnd(void) // line 145 (Session2.cpp)
{
	return (this->*_RefreshSkillItemWnd)();

	//TODO
}


hook_method<bool (CSession::*)(SKILL_INFO& skillInfo, bool needRefresh)> CSession::_AddSkillItem(SAKEXE, "CSession::AddSkillItem");
bool CSession::AddSkillItem(SKILL_INFO& skillInfo, bool needRefresh) // line 197 (Session2.cpp)
{
	return (this->*_AddSkillItem)(skillInfo, needRefresh);

	//TODO
}


hook_method<SKILL_INFO (CSession::*)(int id)> CSession::_GetSkillItemInfoBySkillId(SAKEXE, "CSession::GetSkillItemInfoBySkillId");
SKILL_INFO CSession::GetSkillItemInfoBySkillId(int id) // line 86
{
	return (this->*_GetSkillItemInfoBySkillId)(id);

	//TODO
}


hook_method<SKILL_INFO (CSession::*)(int sequence)> CSession::_GetSkillItemInfoBySequence(SAKEXE, "CSession::GetSkillItemInfoBySequence");
SKILL_INFO CSession::GetSkillItemInfoBySequence(int sequence) // line 1873
{
	return (this->*_GetSkillItemInfoBySequence)(sequence);

	//TODO
}


hook_method<SKILL_INFO (CSession::*)(const char* skillName)> CSession::_GetSkillItemInfoByName(SAKEXE, "CSession::GetSkillItemInfoByName");
SKILL_INFO CSession::GetSkillItemInfoByName(const char* skillName) // line 1882
{
	return (this->*_GetSkillItemInfoByName)(skillName);

	//TODO
}


hook_method<bool (CSession::*)(SKILL_INFO& skillInfo)> CSession::_AddTempSkillItem(SAKEXE, "CSession::AddTempSkillItem");
bool CSession::AddTempSkillItem(SKILL_INFO& skillInfo) // line 3251
{
	return (this->*_AddTempSkillItem)(skillInfo);

	//TODO
}


hook_method<SKILL_INFO (CSession::*)(int skillId)> CSession::_GetTempSkillItemInfoBySkillId(SAKEXE, "CSession::GetTempSkillItemInfoBySkillId");
SKILL_INFO CSession::GetTempSkillItemInfoBySkillId(int skillId) // line 3270-3281
{
	return (this->*_GetTempSkillItemInfoBySkillId)(skillId);

	//TODO
}


hook_method<int (CSession::*)(int slot)> CSession::_GetShortenSkillUseLevel(SAKEXE, "?GetShortenSkillUseLevel@CSession@@QAEHH@Z");
int CSession::GetShortenSkillUseLevel(int slot) // line 1900
{
	return (this->*_GetShortenSkillUseLevel)(slot);

	//TODO
}


hook_method<void (CSession::*)(int skillUseLevel, int slot)> CSession::_SetShortenSkillUseLevel2(SAKEXE, "?SetShortenSkillUseLevel@CSession@@QAEXHH@Z");
void CSession::SetShortenSkillUseLevel(int skillUseLevel, int slot) // line 1909
{
	return (this->*_SetShortenSkillUseLevel2)(skillUseLevel, slot);

	//TODO
}


hook_func<bool (__cdecl *)(mystd::vector< mystd::pair< mystd::string,mystd::vector<int> > >* integerListPair, char* fName)> _TokenFileToIntegerListPair(SAKEXE, "TokenFileToIntegerListPair");
bool __cdecl TokenFileToIntegerListPair(mystd::vector< mystd::pair< mystd::string,mystd::vector<int> > >* integerListPair, char* fName) // line 7029
{
	return (_TokenFileToIntegerListPair)(integerListPair, fName);

	integerListPair->clear();

	CFile fp;
	if( !fp.CFile::Open(fName, 0) )
		return false;

	char* base = (char*)fp.CFile::GetCurBuf(0);
	char* buf = (char*)fp.CFile::GetCurBuf(0);
	char* buf_end = (char*)fp.CFile::GetCurBuf(fp.CFile::GetLength());

	mystd::string a;
	mystd::vector<int> tmpList;

	while( buf < buf_end )
	{
		switch( *buf )
		{
		case '@':
			integerListPair->push_back(mystd::pair< mystd::string,mystd::vector<int> >(a, tmpList));
			a.erase(0, a.size());
			tmpList.clear();
			break;
		case '#':
			if( a.size() == 0 )
				a.replace(a.begin(), a.end(), base, buf);
			else
				tmpList.push_back(atoi(base));
			base = buf + 1;
			break;
		case '\n':
		case '\r':
			base = buf + 1;
			break;
		default:
			break;
		}

		++buf;
	}

	mystd::sort(integerListPair->begin(), integerListPair->begin(), IListComp());
	return true;
}


hook_method<void (CSession::*)(void)> CSession::_InitSkillEffectIdTable(SERVER, "CSession::InitSkillEffectIdTable");
void CSession::InitSkillEffectIdTable(void) // line 239 (Session2.cpp)
{
	return (this->*_InitSkillEffectIdTable)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_InitSkillUseAfterDelayTable(SERVER, "CSession::InitSkillUseAfterDelayTable");
int CSession::InitSkillUseAfterDelayTable(void) // line 7076
{
	return (this->*_InitSkillUseAfterDelayTable)();

	return ( TokenFileToIntegerListPair(&m_skillAfterDelayTable, "skillAfterDelay.txt") ) ? 1 : 0;
}


hook_method<void (CSession::*)(const char* itemName, char* buf)> CSession::_GetSkillBitmapFileName(SAKEXE, "CSession::GetSkillBitmapFileName");
void CSession::GetSkillBitmapFileName(const char* itemName, char* buf) // line 5144
{
	return (this->*_GetSkillBitmapFileName)(itemName, buf);

	//TODO
}


hook_method<const char* (CSession::*)(const char* itemName)> CSession::_GetItemSpriteFileName_Skill(SAKEXE, "CSession::GetItemSpriteFileName_Skill");
const char* CSession::GetItemSpriteFileName_Skill(const char* itemName) // line 5136
{
	return (this->*_GetItemSpriteFileName_Skill)(itemName);

	static mystd::string itemSpriteFileName;
	itemSpriteFileName = "아이템\\";
	itemSpriteFileName += itemName;
	return itemSpriteFileName.c_str();
}


hook_method<void (CSession::*)(void)> CSession::_InitWithClear(SAKEXE, "CSession::InitWithClear");
void CSession::InitWithClear(void) // line 598
{
	return (this->*_InitWithClear)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitJobHitWaveName(SERVER, "CSession::InitJobHitWaveName");
void CSession::InitJobHitWaveName(void) // line 5477
{
	return (this->*_InitJobHitWaveName)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_InitFogParameterTable(SERVER, "CSession::InitFogParameterTable");
int CSession::InitFogParameterTable(void) // line 5369
{
	return (this->*_InitFogParameterTable)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitWeaponHitWaveName(SERVER, "CSession::InitWeaponHitWaveName");
void CSession::InitWeaponHitWaveName(void) // line 5563
{
	return (this->*_InitWeaponHitWaveName)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitShadowFactorWithJob(SERVER, "CSession::InitShadowFactorWithJob");
void CSession::InitShadowFactorWithJob(void) // line 6033
{
	return (this->*_InitShadowFactorWithJob)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitWeaponSwingWaveName(SERVER, "CSession::InitWeaponSwingWaveName");
void CSession::InitWeaponSwingWaveName(void) // line 5618
{
	return (this->*_InitWeaponSwingWaveName)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_WriteOptionToRegistry(SAKEXE, "CSession::WriteOptionToRegistry");
void CSession::WriteOptionToRegistry(void) // line 439
{
	return (this->*_WriteOptionToRegistry)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_WriteExListToRegistry(SAKEXE, "CSession::WriteExListToRegistry");
void CSession::WriteExListToRegistry(void) // line 230
{
	return (this->*_WriteExListToRegistry)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitExListWithRegistry(SAKEXE, "CSession::InitExListWithRegistry");
void CSession::InitExListWithRegistry(void) // line 166
{
	return (this->*_InitExListWithRegistry)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitOptionWithRegistry(SAKEXE, "CSession::InitOptionWithRegistry");
void CSession::InitOptionWithRegistry(void) // line 235
{
	return (this->*_InitOptionWithRegistry)();

	int REG_TYPE;
	int DATALENGTH;

	char OptionPath[512];
	strcpy(OptionPath, g_regPath);
	strcat(OptionPath, g_optionPath);

	HKEY hResultKey;
	if( RegOpenKeyExA(HKEY_LOCAL_MACHINE, g_regPath, 0, KEY_QUERY_VALUE, &hResultKey) == ERROR_SUCCESS )
	{
		RegCloseKey(hResultKey);

		HKEY hKey;
		if( RegOpenKeyExA(HKEY_LOCAL_MACHINE, g_regPath, 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS )
		{
			REG_TYPE = 4;
			DATALENGTH = 4;

			if( RegQueryValueExA(hKey, "FOG", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_fogOn, (LPDWORD)&DATALENGTH) )
				m_fogOn = 1;
			m_fogOn = !!m_fogOn;

			RegCloseKey(hKey);
		}
	}

	HKEY hResultKey2;
	if( RegOpenKeyExA(HKEY_LOCAL_MACHINE, OptionPath, 0, KEY_QUERY_VALUE, &hResultKey2) == ERROR_SUCCESS )
	{
		RegCloseKey(hResultKey2);

		HKEY hKey;
		if( RegOpenKeyExA(HKEY_LOCAL_MACHINE, OptionPath, 0, KEY_QUERY_VALUE, &hKey) != ERROR_SUCCESS )
			return; // ?how is this possible?

		REG_TYPE = 4;
		DATALENGTH = 4;

		if( RegQueryValueExA(hKey, "isEffectOn", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_isEffectOn, (LPDWORD)&DATALENGTH) )
			m_isEffectOn = 1;
		m_isEffectOn = !!m_isEffectOn;

		if( RegQueryValueExA(hKey, "bgmIsPaused", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_bgmIsPaused, (LPDWORD)&DATALENGTH) )
			m_bgmIsPaused = 0;
		m_bgmIsPaused = !!m_bgmIsPaused;

		if( RegQueryValueExA(hKey, "isSoundOn", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&g_isSoundOn, (LPDWORD)&DATALENGTH) )
			g_isSoundOn = 1;
		g_isSoundOn = !!g_isSoundOn;

		int streamVolume;
		if( RegQueryValueExA(hKey, "streamVolume", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&streamVolume, (LPDWORD)&DATALENGTH) )
			streamVolume = 100;

		int soundVolume;
		if( RegQueryValueExA(hKey, "soundVolume", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&soundVolume, (LPDWORD)&DATALENGTH) )
			soundVolume = 100;

		if( RegQueryValueExA(hKey, "m_bAutoOpenDetailWindowIfLowMemory", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_bAutoOpenDetailWindowIfLowMemory, (LPDWORD)&DATALENGTH) )
			m_bAutoOpenDetailWindowIfLowMemory = 1;

		g_session.m_BgmVolume = streamVolume;
		SetStreamVolume(streamVolume);
		Set2DVolume(soundVolume);
		Set3DVolume(soundVolume);

		if( RegQueryValueExA(hKey, "m_monsterSnapOn_Skill", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_monsterSnapOn_Skill, (LPDWORD)&DATALENGTH) )
			m_monsterSnapOn_Skill = 1;
		m_monsterSnapOn_Skill = !!m_monsterSnapOn_Skill;

		if( RegQueryValueExA(hKey, "m_monsterSnapOn_NoSkill", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_monsterSnapOn_NoSkill, (LPDWORD)&DATALENGTH) )
			m_monsterSnapOn_NoSkill = 0;
		m_monsterSnapOn_NoSkill = !!m_monsterSnapOn_NoSkill;

		if( RegQueryValueExA(hKey, "m_isItemSnap", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_isItemSnap, (LPDWORD)&DATALENGTH) )
			m_isItemSnap = 0;
		m_isItemSnap = !!m_isItemSnap;

		if( RegQueryValueExA(hKey, "m_isOpaque", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_isOpaque, (LPDWORD)&DATALENGTH) )
			m_isOpaque = 0;
		m_isOpaque = !!m_isOpaque;

		if( RegQueryValueExA(hKey, "m_isShowWhisperWnd", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_isShowWhisperWnd, (LPDWORD)&DATALENGTH) )
			m_isShowWhisperWnd = 1;
		m_isShowWhisperWnd = !!m_isShowWhisperWnd;

		if( RegQueryValueExA(hKey, "m_isShowWhisperWnd_Friend", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_isShowWhisperWnd_Friend, (LPDWORD)&DATALENGTH) )
			m_isShowWhisperWnd_Friend = 1;
		m_isShowWhisperWnd_Friend = !!m_isShowWhisperWnd_Friend;

		if( RegQueryValueExA(hKey, "m_isPlayWhisperOpenSound", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&m_isPlayWhisperOpenSound, (LPDWORD)&DATALENGTH) )
			m_isPlayWhisperOpenSound = 1;
		m_isPlayWhisperOpenSound = !!m_isPlayWhisperOpenSound;

		m_isMonsterSnap = !!m_monsterSnapOn_NoSkill;

		if( RegQueryValueExA(hKey, "m_bMakeMissEffect", 0, (LPDWORD)&REG_TYPE, (LPBYTE)m_bMakeMissEffect, (LPDWORD)&DATALENGTH) )
			m_bMakeMissEffect = 1;
		m_bMakeMissEffect = !!m_bMakeMissEffect;

		if( RegQueryValueExA(hKey, "g_isFixedCamera", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&g_isFixedCamera, (LPDWORD)&DATALENGTH) )
			g_isFixedCamera = 0;
		g_isFixedCamera = !!g_isFixedCamera;

		if( RegQueryValueExA(hKey, "g_outdoorViewLatitude", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&g_outdoorViewLatitude, (LPDWORD)&DATALENGTH) )
			g_outdoorViewLatitude = -45.0f;
		if( RegQueryValueExA(hKey, "g_outdoorViewDistance", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&g_outdoorViewDistance, (LPDWORD)&DATALENGTH) )
			g_outdoorViewDistance = 300.0f;
		if( RegQueryValueExA(hKey, "g_indoorViewLatitude", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&g_indoorViewLatitude, (LPDWORD)&DATALENGTH) )
			g_indoorViewLatitude = -45.0f;
		if( RegQueryValueExA(hKey, "g_indoorViewDistance", 0, (LPDWORD)&REG_TYPE, (LPBYTE)&g_indoorViewDistance, (LPDWORD)&DATALENGTH) )
			g_indoorViewDistance = 300.0f;

		if( g_indoorViewLatitude < -55.0f )
			g_indoorViewLatitude = -55.0f;
		else
		if( g_indoorViewLatitude > -35.0f )
			g_indoorViewLatitude = -35.0f;

		if( g_indoorViewDistance < CLOSE_DIST )
			g_indoorViewDistance = CLOSE_DIST;
		if( g_indoorViewDistance > AVG_DIST )
			g_indoorViewDistance = AVG_DIST;

		if( g_outdoorViewLatitude < -65.0f )
			g_outdoorViewLatitude = -65.0f;
		else
		if( g_outdoorViewLatitude > -25.0f )
			g_outdoorViewLatitude = -25.0f;

		if( g_outdoorViewDistance < CLOSE_DIST )
			g_outdoorViewDistance = CLOSE_DIST;
		if( g_outdoorViewDistance > FAR_DIST )
			g_outdoorViewDistance = FAR_DIST;

		REG_TYPE = 1;
		DATALENGTH = 128;

		char skinName[128+1];
		if( RegQueryValueExA(hKey, "SKINNAME", 0, (LPDWORD)&REG_TYPE, (LPBYTE)skinName, (LPDWORD)&DATALENGTH) )
			strcpy(skinName, "<Basic Skin>");
		g_skinMgr.m_savedSkinName = skinName;

		RegCloseKey(hKey);
	}
	else
	{// fail, fall back to defaults
		m_bgmIsPaused = 0;
		m_fogOn = 1;
		m_isEffectOn = 1;
		g_isSoundOn = 1;
		SetStreamVolume(100);
		Set2DVolume(100);
		Set3DVolume(100);
	}
}


hook_method<void (CSession::*)(void)> CSession::_InitWhenServerMove(SAKEXE, "CSession::InitWhenServerMove");
void CSession::InitWhenServerMove(void) // line 2350
{
	return (this->*_InitWhenServerMove)();

	m_itemList.clear(); //inlined
	m_pingTimeList.clear(); //inlined
	memset(m_equipedItems, 0, sizeof(m_equipedItems));
}


hook_method<unsigned long (CSession::*)(void)> CSession::_GetServerTime(SAKEXE, "CSession::GetServerTime");
unsigned long CSession::GetServerTime(void) // line 4119
{
	return (this->*_GetServerTime)();

	return timeGetTime() - m_diffTime - 72;
}


hook_method<void (CSession::*)(unsigned long startTime)> CSession::_SetServerTime(SAKEXE, "CSession::SetServerTime");
void CSession::SetServerTime(unsigned long startTime) // line 4113
{
	return (this->*_SetServerTime)(startTime);

	m_numLatePacket = 0;
	m_diffTime = timeGetTime() - startTime;
}


hook_method<bool (CSession::*)(const char* chat)> CSession::_IsOnlyEnglish(SAKEXE, "CSession::IsOnlyEnglish");
bool CSession::IsOnlyEnglish(const char* chat) // line 5424
{
	return (this->*_IsOnlyEnglish)(chat);

	//TODO
}


hook_method<void (CSession::*)(unsigned long startTime)> CSession::_UpdateServerTime(SAKEXE, "CSession::UpdateServerTime");
void CSession::UpdateServerTime(unsigned long startTime) // line 4098
{
	return (this->*_UpdateServerTime)(startTime);

	//TODO
}


hook_method<void (CSession::*)(unsigned long pingTime)> CSession::_RecalcAveragePingTime(SAKEXE, "CSession::RecalcAveragePingTime");
void CSession::RecalcAveragePingTime(unsigned long pingTime) // line 2335
{
	return (this->*_RecalcAveragePingTime)(pingTime);

	//TODO
}


hook_method<void (CSession::*)(int x, int y, int dir)> CSession::_SetPlayerPosDir(SAKEXE, "CSession::SetPlayerPosDir");
void CSession::SetPlayerPosDir(int x, int y, int dir) // line 4088
{
	return (this->*_SetPlayerPosDir)(x, y, dir);

	m_posX = x;
	m_posY = y;
	m_dir = dir;
}


hook_method<bool (CSession::*)(const char* chat)> CSession::_IsBadNameWithSpaceChar(SERVER, "CSession::IsBadNameWithSpaceChar");
bool CSession::IsBadNameWithSpaceChar(const char* chat) // line 5434
{
	return (this->*_IsBadNameWithSpaceChar)(chat);

	size_t len = strlen(chat);
	return ( len == 1 || chat[0] == ' ' || chat[len - 1] == ' ' );
}


/// @param param Pointer to array of three strings (output).
/// @return Offset of 'message' inside chatBuf, or -1 if not applicable.
hook_method<int (CSession::*)(const char* chatBuf, TALKTYPE* talkType, mystd::string param[3])> CSession::_GetTalkType(SAKEXE, "CSession::GetTalkType");
int CSession::GetTalkType(const char* chatBuf, TALKTYPE* talkType, mystd::string param[3]) // line 4654
{
	return (this->*_GetTalkType)(chatBuf, talkType, param);

	if( chatBuf == NULL )
	{
		*talkType = TT_UNKNOWN;
		return -1;
	}

	CTokenizer t(chatBuf);

	if( t.NumTokens() == 0 )
	{
		*talkType = TT_UNKNOWN;
		return -1;
	}

	MakeStringLower(t[0]);

	if( *chatBuf != '/' )
	{
		*talkType = TT_NORMAL;
		return 0;
	}

	int pos = 0;
	if( t[0] == "/\xA4\xD0" )
	{
		*talkType = TT_BROADCAST;
		pos = 3;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/b" )
	{
		*talkType = TT_BROADCAST;
		pos = 2;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/lb" )
	{
		*talkType = TT_LOCALBROADCAST;
		pos = 3;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/\xA4\xD3\xA4\xD0" )
	{
		*talkType = TT_LOCALBROADCAST;
		pos = 5;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/nb" )
	{
		*talkType = TT_NAMELESS_BROADCAST;
		pos = 3;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/\xA4\xCC\xA4\xD0" )
	{
		*talkType = TT_NAMELESS_BROADCAST;
		pos = 5;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/nlb" )
	{
		*talkType = TT_NAMELESS_LOCALBROADCAST;
		pos = 4;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/\xA4\xCF\xA4\xD0" )
	{
		*talkType = TT_NAMELESS_LOCALBROADCAST;
		pos = 5;
		goto LABEL_SKIPSPACE;
	}
	if( t[0] == "/\xC6\xC4\xB6\xF5\xB8\xBB" )
	{
		*talkType = TT_NAMELESS_BLUEBROADCAST;
		pos = 7;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/bb" )
	{
		*talkType = TT_NAMELESS_BLUEBROADCAST;
		pos = 3; // fixed from '7'
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/\xC1\xF6\xBF\xAA\xC6\xC4\xB6\xF5\xB8\xBB" )
	{
		*talkType = TT_NAMELESS_BLUELOCALBROADCAST;
		pos = 11;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/mb" )
	{
		*talkType = TT_NAMELESS_BLUELOCALBROADCAST;
		pos = 3; // fixed from '11'
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/kill" )
	{
		*talkType = TT_DISCONNECT_CHARACTER;
		pos = 5;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/v" || t[0] == "/\xA4\xBD" )
	{
		*talkType = TT_VOLUME;
		if( t.NumTokens() >= 2 )
		{
			param[0] = t[1];
		}
		else
		{
			char buf[36];
			param[0] = itoa(Get2DVolume(), buf, 10);
		}
		return -1;
	}

	if( t[0] == "/bv" || t[0] == "/\xA4\xD0\xA4\xBD" )
	{
		*talkType = TT_BVOLUME;
		if( t.NumTokens() >= 2 )
		{
			param[0] = t[1];
		}
		else
		{
			char buf[36];
			param[0] = itoa(GetStreamVolume(), buf, 10);
		}
		return -1;
	}

	if( (t[0] == "/gc" || t[0] == "/guildchat") && t.NumTokens() >= 2 )
	{
		*talkType = TT_GUILD_CHAT;
		if( t[0] != "/gc" )
			param[0] = chatBuf + 11;
		else
			param[0] = chatBuf + 4;
		return -1;
	}

	if( (t[0] == "/ex" || t[0] == "/\xC2\xF7\xB4\xDC") && t.NumTokens() >= 2 )
	{
		*talkType = TT_REQ_WHISPER_PC_EX;
		if( t[0] == "/ex" )
			param[0] = chatBuf + 6;
		else
			param[0] = chatBuf + 4;
		return -1;
	}

	if( (t[0] == "/in" || t[0] == "/\xC7\xD8\xC1\xA6") && t.NumTokens() >= 2 )
	{
		*talkType = TT_REQ_WHISPER_PC_IN;
		if( t[0] != "/in" )
			param[0] = chatBuf + 6;
		else
			param[0] = chatBuf + 4;
		return -1;
	}

	if( t[0] == "/red" )
	{
		*talkType = TT_IS_REDCELL;
		for( int i = 1; i < t.NumTokens(); ++i )
		{
			param[0] += t[i];
			param[0] += " ";
		}
		return -1;
	}

	if( (t[0] == "/\xB0\xC5\xB7\xA1" || t[0] == "/rjfo" || t[0] == "/\xB1\xB3\xC8\xAF" || t[0] == "/ryghks" || t[0] == "/deal" || t[0] == "/\xA4\xB7\xA4\xA7\xB9\xCC") && t.NumTokens() == 2 )
	{
		*talkType = TT_REQ_EXCHANGE_ITEM;
		param[0] = t[1];
		return -1;
	}

	if( (t[0] == "/\xB1\xE6\xB5\xE5" || t[0] == "/rlfem" || t[0] == "/guild") && t.NumTokens() == 2 )
	{
		*talkType = TT_REQ_MAKE_GUILD;
		param[0] = t[1];
		return -1;
	}

	if( (t[0] == "/\xC7\xD8\xC3\xBC" || t[0] == "/gocp" || t[0] == "/breakguild") && t.NumTokens() == 2 )
	{
		*talkType = TT_REQ_BREAK_GUILD;
		param[0] = t[1];
		return -1;
	}

	if( (t[0] == "/\xB0\xE1\xBC\xBA" || t[0] == "/ruftjd" || t[0] == "/organize") && t.NumTokens() == 2 )
	{
		*talkType = TT_REQ_MAKE_GROUP;
		param[0] = t[1];
		return -1;
	}

	if( (t[0] == "/\xB8\xF3\xBD\xBA\xC5\xCD" || t[0] == "/\xBE\xC6\xC0\xCC\xC5\xDB" || t[0] == "/item" || t[0] == "/monster") && t.NumTokens() == 2 )
	{
		*talkType = TT_REQ_ITEM_CREATE;
		param[0] = t[1];
		return -1;
	}

	if( (t[0] == "/\xB8\xCA\xC0\xCC\xB5\xBF" || t[0] == "/mapmove" || t[0] == "/mm") && t.NumTokens() > 1 )
	{
		*talkType = TT_REQ_MOVETO_MAP;
		param[0] = t[1];
		if( t.NumTokens() == 4 )
		{
			param[1] = t[2];
			param[2] = t[3];
		}
		else
		{
			param[1] = param[2] = "0";
		}
		return -1;
	}

	if( (t[0] == "/\xC1\xA6\xB8\xED" || t[0] == "/wpaud" || t[0] == "/expel") && t.NumTokens() == 2 )
	{
		*talkType = TT_REQ_EXPEL_GROUP_MEMBER;
		param[0] = t[1];
		return -1;
	}

	if( (t[0] == "/\xA4\xC4\xA4\xBF" || t[0] == "/pk") && t.NumTokens() == 2 )
	{
		*talkType = TT_REQ_PK;
		param[0] = t[1];
		return -1;
	}

	if( t[0] == "/sm" && t.NumTokens() == 2 )
	{
		*talkType = TT_TEST_SHOW_IMAGE;
		param[0] = t[1];
		return -1;
	}

	if( t[0] == "/resetstate" )
	{
		*talkType = TT_REQ_RESETSTATE;
		return -1;
	}

	if( t[0] == "/resetskill" )
	{
		*talkType = TT_REQ_RESETSKILL;
		return -1;
	}

	if( (t[0] == "/changemaptype" || t[0] == "/cmt") && t.NumTokens() == 4 )
	{
		*talkType = TT_CHANGE_MAPTYPE;
		param[0] = t[1];
		param[1] = t[2];
		param[2] = t[3];
		return -1;
	}

	if( t[0] == "/emblem" || t[0] == "/\xBF\xA5\xBA\xED\xB7\xBD" || t[0] == "/\xBE\xDA\xBA\xED\xB7\xBD" || t[0] == "/dpaqmffpa" || t[0] == "/doaqmffpa" )
	{
		*talkType = TT_TOGGLE_EMBLEM;
		return -1;
	}

	if( t[0] == "/hide" )
	{
		*talkType = TT_HIDE;
		return -1;
	}

	if( t[0] == "/\xC6\xF9\xC6\xAE" || t[0] == "/font" )
	{
		*talkType = TT_FONT;
		return -1;
	}

	if( t[0] == "/mineffect" || t[0] == MsgStr(MSI_MINEFFECT) )
	{
		m_isMinEffect = 1 - m_isMinEffect;
		m_isMinEffectOld = 1 - m_isMinEffect;
		g_windowMgr.UIWindowMgr::SendMsg(UIM_PUSHINTOCHATHISTORY, (int)MsgStr((m_isMinEffect == 1)?MSI_MINEFFECT_ON:MSI_MINEFFECT_OFF), 0x64FFFF, 0);
		if( *talkType == TT_NORMAL )
			return 0;
		goto LABEL_SKIPSPACE;
	}

	if( t[0] == "/remove" && t.NumTokens() == 2 )
	{
		*talkType = TT_REMOVE;
		param[0] = t[1];
		return -1;
	}

	if( t[0] == "/shift" )
	{
		*talkType = TT_SHIFT;
		for( int i = 0; i < t.NumTokens() - 1; ++i )
			param[i] = t[i + 1];
		return -1;
	}

	if( t[0] == "/recall" && t.NumTokens() == 2 )
	{
		*talkType = TT_RECALL_AID;
		param[0] = t[1];
		return -1;
	}

	if( t[0] == "/summon" && t.NumTokens() == 2 )
	{
		*talkType = TT_RECALL_GID;
		param[0] = t[1];
		return -1;
	}

	if( t[0] == "/\xBF\xE4\xB1\xDD" )
	{
		*talkType = TT_BILLING_INFO;
		return -1;
	}

	if( t[0] == "/\xC0\xCC\xB8\xA7\xC7\xA5\xBD\xC3" || t[0] == "/showname" )
	{
		*talkType = TT_SHOW_NAME_TYPE;

LABEL_SKIPSPACE:
		// skip whitespace after command
		while( chatBuf[pos] == ' ' )
			++pos;
		return pos;
	}

	*talkType = this->CSession::GetNoParamTalkType(t[0].c_str());
	return -1;
}


hook_method<void (CSession::*)(void)> CSession::_ClearPlusValue(SAKEXE, "CSession::ClearPlusValue");
void CSession::ClearPlusValue(void)
{
	return (this->*_ClearPlusValue)();

	//TODO
}


hook_method<const char* (CSession::*)(const char* msg, char* buf)> CSession::_RemoveUnderbar(SAKEXE, "CSession::RemoveUnderbar");
const char* CSession::RemoveUnderbar(const char* msg, char* buf)
{
	return (this->*_RemoveUnderbar)(msg, buf);

	strcpy(buf, msg);

	for( char* i = buf; *i != '\0'; i = CharNextExA((WORD)g_codePage, i, CP_ACP) )
		if( *i == '_' )
			*i = ' ';

	return buf;
}


hook_method<void (CSession::*)(void)> CSession::_DeleteAllExNameList(SAKEXE, "CSession::DeleteAllExNameList");
void CSession::DeleteAllExNameList(void) // line 6737
{
	return (this->*_DeleteAllExNameList)();

	//TODO
}


BOOL CSession::IsExName(const char* exName)
{
	mystd::list<mystd::string>::const_iterator it;
	for( it = m_exNameList.begin(); it != m_exNameList.end(); ++it )
		if( *it == exName )
			break;

	return ( it != m_exNameList.end() ) ? TRUE : FALSE;
}


hook_method<void (CSession::*)(const char* exName)> CSession::_AddToExNameList(SAKEXE, "CSession::AddToExNameList");
void CSession::AddToExNameList(const char* exName) // line 6708-6710
{
	return (this->*_AddToExNameList)(exName);

	m_exNameList.push_back(exName);
}


hook_method<void (CSession::*)(const char* exName)> CSession::_DeleteFromExNameList(SAKEXE, "CSession::DeleteFromExNameList");
void CSession::DeleteFromExNameList(const char* exName) // line 6713-6722
{
	return (this->*_DeleteFromExNameList)(exName);

	for( mystd::list<mystd::string>::iterator it = m_exNameList.begin(); it != m_exNameList.end(); ++it )
	{
		if( *it == exName )
		{
			m_exNameList.erase(it);
			break;
		}
	}
}


hook_method<int (CSession::*)(unsigned long aid)> CSession::_IsExAid(SAKEXE, "CSession::IsExAid");
int CSession::IsExAid(unsigned long aid) // line 6770
{
	return (this->*_IsExAid)(aid);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_DeleteAllExAidList(SAKEXE, "CSession::DeleteAllExAidList");
void CSession::DeleteAllExAidList(void) // line 6782
{
	return (this->*_DeleteAllExAidList)();

	//TODO
}


hook_method<void (CSession::*)(unsigned long aid)> CSession::_AddToExAidList(SAKEXE, "CSession::AddToExAidList");
void CSession::AddToExAidList(unsigned long aid) // line 6753-6755
{
	return (this->*_AddToExAidList)(aid);

	m_exAidList.push_back(aid);
}


hook_method<void (CSession::*)(unsigned long aid)> CSession::_DeleteFromExAidList(SAKEXE, "CSession::DeleteFromExAidList");
void CSession::DeleteFromExAidList(unsigned long aid) // line 6758-6767
{
	return (this->*_DeleteFromExAidList)(aid);

	for( mystd::list<unsigned long>::iterator it = m_exAidList.begin(); it != m_exAidList.end(); ++it )
	{
		if( *it == aid )
		{
			m_exAidList.erase(it);
			break;
		}
	}
}


hook_method<mystd::list<mystd::string>& (CSession::*)(void)> CSession::_GetNumExNameList(SAKEXE, "CSession::GetNumExNameList");
mystd::list<mystd::string>& CSession::GetNumExNameList(void) // line 6748
{
	return (this->*_GetNumExNameList)();

	//TODO
}


hook_method<const char* (CSession::*)(int attr)> CSession::_GetAttrWaveName(SAKEXE, "CSession::GetAttrWaveName");
const char* CSession::GetAttrWaveName(int attr) // line 5636
{
	return (this->*_GetAttrWaveName)(attr);

	//TODO
}


hook_method<const char* (CSession::*)(int job)> CSession::_GetJobHitWaveName(SAKEXE, "CSession::GetJobHitWaveName");
const char* CSession::GetJobHitWaveName(int job) // line 5551
{
	return (this->*_GetJobHitWaveName)(job);

	//TODO
}


hook_method<const char* (CSession::*)(const char* rswName)> CSession::_GetMp3Name(SAKEXE, "CSession::GetMp3Name");
const char* CSession::GetMp3Name(const char* rswName) // line 5331
{
	return (this->*_GetMp3Name)(rswName);

	//TODO
}


hook_method<const char* (CSession::*)(const char* rswName)> CSession::_GetMapName(SAKEXE, "CSession::GetMapName");
const char* CSession::GetMapName(const char* rswName) // line 5271
{
	return (this->*_GetMapName)(rswName);

	//TODO
}


hook_method<const char* (CSession::*)(int weapon)> CSession::_GetWeaponHitWaveName(SAKEXE, "CSession::GetWeaponHitWaveName");
const char* CSession::GetWeaponHitWaveName(int weapon) // line 5581-5615
{
	return (this->*_GetWeaponHitWaveName)(weapon);

	if( weapon == -1 )
	{
		switch( rand() % 4 )
		{
		case 0: return "_enemy_hit_normal1.wav";
		case 1: return "_enemy_hit_normal2.wav";
		case 2: return "_enemy_hit_normal3.wav";
		case 3: return "_enemy_hit_normal4.wav";
		}
	}

	if( weapon == 0 )
	{
		switch( rand() % 4 )
		{
		case 0: return "_hit_fist1.wav";
		case 1: return "_hit_fist2.wav";
		case 2: return "_hit_fist3.wav";
		case 3: return "_hit_fist4.wav";
		}
	}

	return m_weaponHitWaveNameTable[weapon].c_str();
}


hook_method<const char* (CSession::*)(int weapon)> CSession::_GetWeaponSwingWaveName(SAKEXE, "CSession::GetWeaponSwingWaveName");
const char* CSession::GetWeaponSwingWaveName(int weapon) // 5681-5700
{
	return (this->*_GetWeaponSwingWaveName)(weapon);

	if( weapon == -1 )
	{
		switch( rand() % 4 )
		{
		case 0: return "_enemy_hit_normal1.wav";
		case 1: return "_enemy_hit_normal2.wav";
		case 2: return "_enemy_hit_normal3.wav";
		case 3: return "_enemy_hit_normal4.wav";
		}
	}

	return m_weaponSwingWaveNameTable[weapon].c_str();
}


hook_method<const char* (CSession::*)(const char* gatName)> CSession::_GatName2RswName(SAKEXE, "CSession::GatName2RswName");
const char* CSession::GatName2RswName(const char* gatName) // line 5340
{
	return (this->*_GatName2RswName)(gatName);

	//TODO
}


hook_method<const char* (CSession::*)(const char* itemName, int isIdentified)> CSession::_GetItemSpriteFileName(SERVER, "CSession::GetItemSpriteFileName");
const char* CSession::GetItemSpriteFileName(const char* itemName, int isIdentified)
{
	return (this->*_GetItemSpriteFileName)(itemName, isIdentified);

	static mystd::string itemSpriteFileName;//XXX: static variable local to this function
	itemSpriteFileName = "아이템\\";
	if( isIdentified )
		itemSpriteFileName += ITEM_INFO::GetItemDesc(atoi(itemName)).identifiedDisplayName;
	else
		itemSpriteFileName += ITEM_INFO::GetItemDesc(atoi(itemName)).unidentifiedDisplayName;
	return itemSpriteFileName.c_str();
}


hook_method<bool (CSession::*)(const char* rswName)> CSession::_IsIndoorRswName(SAKEXE, "CSession::IsIndoorRswName");
bool CSession::IsIndoorRswName(const char* rswName) // line 5360-5366
{
	return (this->*_IsIndoorRswName)(rswName);

	mystd::vector<const char*>::const_iterator it;
	it = mystd::lower_bound(m_indoorRswTable.begin(), m_indoorRswTable.end(), rswName, LPCSTRComp()); //inlined
	return ( it != m_indoorRswTable.end() && strcmp(*it, rswName) == 0 );
}


hook_method<bool (CSession::*)(const char* rswName)> CSession::_IsEnableObjLightMap(SAKEXE, "CSession::IsEnableObjLightMap");
bool CSession::IsEnableObjLightMap(const char* rswName) // line 5303
{
	return (this->*_IsEnableObjLightMap)(rswName);

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_GetNumItem(SAKEXE, "CSession::GetNumItem");
int CSession::GetNumItem(void) // line 2479
{
	return (this->*_GetNumItem)();

	//TODO
}


hook_method<bool (CSession::*)(JOBTYPE jobType)> CSession::_IsVisibleNPC(SAKEXE, "CSession::IsVisibleNPC");
bool CSession::IsVisibleNPC(JOBTYPE jobType)
{
	return (this->*_IsVisibleNPC)(jobType);

	return ( jobType != JT_WARPNPC && jobType != JT_EFFECTLAUNCHER && jobType != JT_HIDDEN_NPC );
}


hook_method<ITEM_INFO (CSession::*)(int id)> CSession::_GetItemInfoById(SAKEXE, "CSession::GetItemInfoById");
ITEM_INFO CSession::GetItemInfoById(int id) // line 2933
{
	return (this->*_GetItemInfoById)(id);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int index)> CSession::_GetItemInfoByIndex(SAKEXE, "CSession::GetItemInfoByIndex");
ITEM_INFO CSession::GetItemInfoByIndex(int index) // line 2920
{
	return (this->*_GetItemInfoByIndex)(index);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int sequence)> CSession::_GetItemInfoBySequence(SAKEXE, "CSession::GetItemInfoBySequence");
ITEM_INFO CSession::GetItemInfoBySequence(int sequence) // line 2506
{
	return (this->*_GetItemInfoBySequence)(sequence);

	//TODO
}


hook_method<char* (CSession::*)(int job, int sex, char* buf)> CSession::_GetJobActName(SAKEXE, "CSession::GetJobActName");
char* CSession::GetJobActName(int job, int sex, char* buf) // line 4521
{
	return (this->*_GetJobActName)(job, sex, buf);

	const char* pcJobName = ( job <= 3950 ) ? m_newPcJobNameTable[job] : m_newPcJobNameTable[job - 3950];
	sprintf(buf, "인간족\\몸통\\%s\\%s%s.act", m_newPcSexNameTable[sex], pcJobName, m_pcSexNameTable[sex]);
	return buf;
}


hook_method<char* (CSession::*)(int job, int sex, char* buf)> CSession::_GetJobSprName(SAKEXE, "CSession::GetJobSprName");
char* CSession::GetJobSprName(int job, int sex, char* buf) // line 4534
{
	return (this->*_GetJobSprName)(job, sex, buf);

	const char* pcJobName = ( job <= 3950 ) ? m_newPcJobNameTable[job] : m_newPcJobNameTable[job - 3950];
    sprintf(buf, "인간족\\몸통\\%%s\\%s%s.spr", m_newPcSexNameTable[sex], pcJobName, m_pcSexNameTable[sex]);
    return buf;
}


hook_method<char* (CSession::*)(int job, int head, int sex, char* buf)> CSession::_GetImfName(SAKEXE, "CSession::GetImfName");
char* CSession::GetImfName(int job, int head, int sex, char* buf) // line 4613
{
	return (this->*_GetImfName)(job, head, sex, buf);

	int j = ( job <= 3950 ) ? job : job - 3950;
	sprintf(buf, "%s%s.imf", m_newPcJobImfNameTable[j], m_pcSexNameTable[sex]);
	return buf;
}


hook_method<char* (CSession::*)(int job, int& head, int sex, char* buf)> CSession::_GetHeadActName(SAKEXE, "CSession::GetHeadActName");
char* CSession::GetHeadActName(int job, int& head, int sex, char* buf) // line 4546
{
	return (this->*_GetHeadActName)(job, head, sex, buf);

	//TODO
}


hook_method<char* (CSession::*)(int job, int& head, int sex, char* buf)> CSession::_GetHeadSprName(SAKEXE, "CSession::GetHeadSprName");
char* CSession::GetHeadSprName(int job, int& head, int sex, char* buf) // line 4568
{
	return (this->*_GetHeadSprName)(job, head, sex, buf);

	//TODO
}


hook_method<char* (CSession::*)(int job, int sex, int shield, char* buf)> CSession::_GetShieldActName(SAKEXE, "CSession::GetShieldActName");
char* CSession::GetShieldActName(int job, int sex, int shield, char* buf) // line 6653
{
	return (this->*_GetShieldActName)(job, sex, shield, buf);

	//TODO
}


hook_method<char* (CSession::*)(int job, int sex, int shield, char* buf)> CSession::_GetShieldSprName(SAKEXE, "CSession::GetShieldSprName");
char* CSession::GetShieldSprName(int job, int sex, int shield, char* buf) // line 6671
{
	return (this->*_GetShieldSprName)(job, sex, shield, buf);

	//TODO
}


hook_method<char* (CSession::*)(int job, int& head, int sex, int accessory, char* buf)> CSession::_GetAccessoryActName(SAKEXE, "CSession::GetAccessoryActName");
char* CSession::GetAccessoryActName(int job, int& head, int sex, int accessory, char* buf) // line 4623
{
	return (this->*_GetAccessoryActName)(job, head, sex, accessory, buf);

	if( accessory == 0 )
		*buf = '\0';
	else
	if( sex == SEX_MALE && (accessory == ACCESSORY_CIRCLET || accessory == ACCESSORY_TIARA) )
		*buf = '\0';
	else
		sprintf(buf, "악세사리\\%s\\%s%s.act", m_newPcSexNameTable[sex], m_newPcSexNameTable[sex], m_newAccessoryNameTable[accessory]); //FIXME: no bounds check

	return buf;
}


hook_method<char* (CSession::*)(int job, int& head, int sex, int accessory, char* buf)> CSession::_GetAccessorySprName(SAKEXE, "CSession::GetAccessorySprName");
char* CSession::GetAccessorySprName(int job, int& head, int sex, int accessory, char* buf) // line 4642
{
	return (this->*_GetAccessorySprName)(job, head, sex, accessory, buf);

	if( accessory == 0 )
		*buf = 0;
	else
		sprintf(buf, "악세사리\\%s\\%s%s.spr", m_newPcSexNameTable[sex], m_newPcSexNameTable[sex], m_newAccessoryNameTable[accessory]); //FIXME: no bounds check

	return buf;
}


hook_method<void (CSession::*)(ITEM_INFO* itemInfo)> CSession::_SetItem(SAKEXE, "CSession::SetItem");
void CSession::SetItem(ITEM_INFO* itemInfo) // line 2817
{
	return (this->*_SetItem)(itemInfo);

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO* itemInfo)> CSession::_AddItem(SAKEXE, "CSession::AddItem");
bool CSession::AddItem(ITEM_INFO* itemInfo) // line 2852-2865
{
	return (this->*_AddItem)(itemInfo);

	for( mystd::list<ITEM_INFO>::iterator it = m_itemList.begin(); it != m_itemList.end(); ++it )
	{
		if( it->m_itemIndex == itemInfo->m_itemIndex )
		{
			it->m_num += itemInfo->m_num;
			g_windowMgr.UIWindowMgr::RefreshItem();
			return false; // add to existing
		}
	}

	m_itemList.push_back(*itemInfo);
	g_windowMgr.UIWindowMgr::RefreshItem();
	return true; // insert
}


hook_method<void (CSession::*)(unsigned long index, int numItem)> CSession::_DecItem(SAKEXE, "CSession::DecItem");
void CSession::DecItem(unsigned long index, int numItem) // line 2680
{
	return (this->*_DecItem)(index, numItem);

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO* itemInfo)> CSession::_AddEquipItem(SAKEXE, "CSession::AddEquipItem");
bool CSession::AddEquipItem(ITEM_INFO* itemInfo) // line 2787
{
	return (this->*_AddEquipItem)(itemInfo);

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO* itemInfo)> CSession::_AddItemNoRefresh(SAKEXE, "CSession::AddItemNoRefresh");
bool CSession::AddItemNoRefresh(ITEM_INFO* itemInfo) // line 2837-2849
{
	return (this->*_AddItemNoRefresh)(itemInfo);

	for( mystd::list<ITEM_INFO>::iterator it = m_itemList.begin(); it != m_itemList.end(); ++it )
	{
		if( it->m_itemIndex == itemInfo->m_itemIndex )
		{
			it->m_num += itemInfo->m_num;
			g_windowMgr.UIWindowMgr::RefreshItem(); // FIXME probably wasn't supposed to call this, copy paste artifact from CSession::AddItem?
			return false; // add to existing
		}
	}

	m_itemList.push_back(*itemInfo);
	return true; // insert
}


hook_method<bool (CSession::*)(int itemIndex)> CSession::_IsValidItemIndexInUnequiped(SAKEXE, "CSession::IsValidItemIndexInUnequiped");
bool CSession::IsValidItemIndexInUnequiped(int itemIndex) // line 2909-2917
{
	return (this->*_IsValidItemIndexInUnequiped)(itemIndex);

	//TODO
}


hook_method<bool (CSession::*)(int itemIndex)> CSession::_IsValidItemIndexInEquiped(SAKEXE, "CSession::IsValidItemIndexInEquiped");
bool CSession::IsValidItemIndexInEquiped(int itemIndex) // line 2898-2906
{
	return (this->*_IsValidItemIndexInEquiped)(itemIndex);

	//TODO
}


hook_method<bool (CSession::*)(int wearLocation)> CSession::_MoveItemFromEquipWndToItemWnd(SAKEXE, "CSession::MoveItemFromEquipWndToItemWnd");
bool CSession::MoveItemFromEquipWndToItemWnd(int wearLocation) // line 2745
{
	return (this->*_MoveItemFromEquipWndToItemWnd)(wearLocation);

	//TODO
}


hook_method<void (CSession::*)(int wearLocation, int* slotNum)> CSession::_BitMaskToSlotNum(SAKEXE, "CSession::BitMaskToSlotNum");
void CSession::BitMaskToSlotNum(int wearLocation, int* slotNum) // line 2701-2723
{
	return (this->*_BitMaskToSlotNum)(wearLocation, slotNum);

	slotNum[0] = -1;
	slotNum[1] = -1;
	slotNum[2] = -1;

	if( wearLocation == 0x8000 )
	{
		slotNum[0] = 15;
		return;
	}

	int n = 0; //FIXME: no bounds check, 'slotNum' can only hold 3 values
	for( int i = 0, loc = wearLocation; i < 10; ++i, loc >>= 1 )
	{
		if( loc & 1 )
		{
			slotNum[n] = i;
			++n;
		}
	}
}


hook_method<void (CSession::*)(void)> CSession::_ClearItem(SAKEXE, "CSession::ClearItem");
void CSession::ClearItem(void)
{
	return (this->*_ClearItem)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearShopItem(SAKEXE, "CSession::ClearShopItem");
void CSession::ClearShopItem(void) // line 3668
{
	return (this->*_ClearShopItem)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearDealItems(SAKEXE, "CSession::ClearDealItems");
void CSession::ClearDealItems(void) // line 609-613
{
	return (this->*_ClearDealItems)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearEquipItem(SAKEXE, "CSession::ClearEquipItem");
void CSession::ClearEquipItem(void) // line 2781
{
	return (this->*_ClearEquipItem)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearEquipItemInInventory(SAKEXE, "CSession::ClearEquipItemInInventory");
void CSession::ClearEquipItemInInventory(void) // line 2657
{
	return (this->*_ClearEquipItemInInventory)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearMerchantMyShopItem(SAKEXE, "CSession::ClearMerchantMyShopItem");
void CSession::ClearMerchantMyShopItem(void)
{
	return (this->*_ClearMerchantMyShopItem)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_GetNumMerchantShopItem(SAKEXE, "CSession::GetNumMerchantShopItem");
int CSession::GetNumMerchantShopItem(void) // line 2369
{
	return (this->*_GetNumMerchantShopItem)();

	return m_merchantShopItemList.size();
}


hook_method<ITEM_INFO (CSession::*)(int sequence)> CSession::_GetMerchantShopItemInfoBySequence(SAKEXE, "CSession::GetMerchantShopItemInfoBySequence");
ITEM_INFO CSession::GetMerchantShopItemInfoBySequence(int sequence) // line 3854
{
	return (this->*_GetMerchantShopItemInfoBySequence)(sequence);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearPurchaseItem(SERVER, "CSession::ClearPurchaseItem");
void CSession::ClearPurchaseItem(void) // line 2948
{
	return (this->*_ClearPurchaseItem)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_GetNumPurchaseItem(SAKEXE, "CSession::GetNumPurchaseItem");
int CSession::GetNumPurchaseItem(void) // line 2373-2375
{
	return (this->*_GetNumPurchaseItem)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_GetPurchaseItemTotalPrice(SAKEXE, "CSession::GetPurchaseItemTotalPrice");
int CSession::GetPurchaseItemTotalPrice(void) // line 2966-2975
{
	return (this->*_GetPurchaseItemTotalPrice)();

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int sequence)> CSession::_GetPurchaseItemInfoBySequence(SAKEXE, "CSession::GetPurchaseItemInfoBySequence");
ITEM_INFO CSession::GetPurchaseItemInfoBySequence(int sequence) // line 2953-2963
{
	return (this->*_GetPurchaseItemInfoBySequence)(sequence);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(const char* itemName)> CSession::_GetPurchaseItemInfoByName(SAKEXE, "CSession::GetPurchaseItemInfoByName");
ITEM_INFO CSession::GetPurchaseItemInfoByName(const char* itemName) // line 3008-3016
{
	return (this->*_GetPurchaseItemInfoByName)(itemName);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearMerchantPurchaseItem(SAKEXE, "CSession::ClearMerchantPurchaseItem");
void CSession::ClearMerchantPurchaseItem(void) // line 3056-3058
{
	return (this->*_ClearMerchantPurchaseItem)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_GetNumMerchantPurchaseItem(SAKEXE, "CSession::GetNumMerchantPurchaseItem");
int CSession::GetNumMerchantPurchaseItem(void) // line 2378-2380
{
	return (this->*_GetNumMerchantPurchaseItem)();

	//TODO
}


hook_method<void (CSession::*)(ITEM_INFO& itemInfo)> CSession::_AddMerchantPurchaseItem(SAKEXE, "CSession::AddMerchantPurchaseItem");
void CSession::AddMerchantPurchaseItem(ITEM_INFO& itemInfo) // line 3086
{
	return (this->*_AddMerchantPurchaseItem)(itemInfo);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int sequence)> CSession::_GetMerchantPurchaseItemInfoBySequence(SAKEXE, "CSession::GetMerchantPurchaseItemInfoBySequence");
ITEM_INFO CSession::GetMerchantPurchaseItemInfoBySequence(int sequence) // line 3061-3071
{
	return (this->*_GetMerchantPurchaseItemInfoBySequence)(sequence);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_CloneMerchantPurchaseItemToMerchantPurchaseItemSaved(SAKEXE, "CSession::CloneMerchantPurchaseItemToMerchantPurchaseItemSaved");
void CSession::CloneMerchantPurchaseItemToMerchantPurchaseItemSaved(void) // line 3033-3040
{
	return (this->*_CloneMerchantPurchaseItemToMerchantPurchaseItemSaved)();

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(const char* itemName)> CSession::_GetMerchantPurchaseItemInfoByName(SAKEXE, "CSession::GetMerchantPurchaseItemInfoByName");
ITEM_INFO CSession::GetMerchantPurchaseItemInfoByName(const char* itemName) // line 3116-3124
{
	return (this->*_GetMerchantPurchaseItemInfoByName)(itemName);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearSellItem(SERVER, "CSession::ClearSellItem");
void CSession::ClearSellItem(void) // line 3153
{
	return (this->*_ClearSellItem)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_GetNumSellItem(SAKEXE, "CSession::GetNumSellItem");
int CSession::GetNumSellItem(void) // line 2383-2385
{
	return (this->*_GetNumSellItem)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_IsSellItemValid(SAKEXE, "CSession::IsSellItemValid");
int CSession::IsSellItemValid(void) // line 3184-3197
{
	return (this->*_IsSellItemValid)();

	//TODO
}


hook_method<void (CSession::*)(ITEM_INFO& itemInfo)> CSession::_AddSellItem(SAKEXE, "CSession::AddSellItem");
void CSession::AddSellItem(ITEM_INFO& itemInfo) // line 3216-3234
{
	return (this->*_AddSellItem)(itemInfo);

	//TODO
}


hook_method<void (CSession::*)(ITEM_INFO& itemInfo)> CSession::_DecSellItem(SAKEXE, "CSession::DecSellItem");
void CSession::DecSellItem(ITEM_INFO& itemInfo) // line 3200-3213
{
	return (this->*_DecSellItem)(itemInfo);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int index)> CSession::_GetSellItemInfoByIndex(SAKEXE, "CSession::GetSellItemInfoByIndex");
ITEM_INFO CSession::GetSellItemInfoByIndex(int index) // line 3173-3181
{
	return (this->*_GetSellItemInfoByIndex)(index);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int sequence)> CSession::_GetSellItemInfoBySequence(SAKEXE, "CSession::GetSellItemInfoBySequence");
ITEM_INFO CSession::GetSellItemInfoBySequence(int sequence) // line 3158-3170
{
	return (this->*_GetSellItemInfoBySequence)(sequence);

	//TODO
}


hook_method<void (CSession::*)(ITEM_INFO& itemInfo)> CSession::_DecMerchantPurchaseItem(SAKEXE, "CSession::DecMerchantPurchaseItem");
void CSession::DecMerchantPurchaseItem(ITEM_INFO& itemInfo) // line 3100
{
	return (this->*_DecMerchantPurchaseItem)(itemInfo);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearStoreItem(SAKEXE, "CSession::ClearStoreItem");
void CSession::ClearStoreItem(void) // line 3581
{
	return (this->*_ClearStoreItem)();

	m_storeItemList.clear(); //inlined
}


hook_method<int (CSession::*)(void)> CSession::_GetNumStoreItem(SAKEXE, "CSession::GetNumStoreItem");
int CSession::GetNumStoreItem(void)
{
	return (this->*_GetNumStoreItem)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_RefreshStoreItemWnd(SAKEXE, "CSession::RefreshStoreItemWnd");
void CSession::RefreshStoreItemWnd(void)
{
	return (this->*_RefreshStoreItemWnd)();

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO& itemInfo)> CSession::_AddStoreItem(SAKEXE, "CSession::AddStoreItem");
bool CSession::AddStoreItem(ITEM_INFO& itemInfo) // line 3608-3622
{
	return (this->*_AddStoreItem)(itemInfo);

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO& itemInfo)> CSession::_DecStoreItem(SAKEXE, "CSession::DecStoreItem");
bool CSession::DecStoreItem(ITEM_INFO& itemInfo) // line 3625-3641
{
	return (this->*_DecStoreItem)(itemInfo);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int index)> CSession::_GetStoreItemInfoByIndex(SAKEXE, "CSession::GetStoreItemInfoByIndex");
ITEM_INFO CSession::GetStoreItemInfoByIndex(int index) // line 3644-3652
{
	return (this->*_GetStoreItemInfoByIndex)(index);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int sequence)> CSession::_GetStoreItemInfoBySequence(SAKEXE, "CSession::GetStoreItemInfoBySequence");
ITEM_INFO CSession::GetStoreItemInfoBySequence(int sequence) // line 3593-3605
{
	return (this->*_GetStoreItemInfoBySequence)(sequence);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearMerchantItem(SAKEXE, "CSession::ClearMerchantItem");
void CSession::ClearMerchantItem(void) // line 3391
{
	return (this->*_ClearMerchantItem)();

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int index)> CSession::_GetMerchantItemInfoByIndex(SAKEXE, "CSession::GetMerchantItemInfoByIndex");
ITEM_INFO CSession::GetMerchantItemInfoByIndex(int index) // line 3455-3463
{
	return (this->*_GetMerchantItemInfoByIndex)(index);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int sequence)> CSession::_GetMerchantItemInfoBySequence(SAKEXE, "CSession::GetMerchantItemInfoBySequence");
ITEM_INFO CSession::GetMerchantItemInfoBySequence(int sequence) // line 3403-3415
{
	return (this->*_GetMerchantItemInfoBySequence)(sequence);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearMerchantMirrorItem(SAKEXE, "CSession::ClearMerchantMirrorItem");
void CSession::ClearMerchantMirrorItem(void) // line 3492-3494
{
	return (this->*_ClearMerchantMirrorItem)();

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO& itemInfo)> CSession::_AddMerchantMirrorItem(SAKEXE, "CSession::AddMerchantMirrorItem");
bool CSession::AddMerchantMirrorItem(ITEM_INFO& itemInfo) // line 3519-3533
{
	return (this->*_AddMerchantMirrorItem)(itemInfo);

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO& itemInfo)> CSession::_DecMerchantMirrorItem(SAKEXE, "CSession::DecMerchantMirrorItem");
bool CSession::DecMerchantMirrorItem(ITEM_INFO& itemInfo) // line 3536-3553
{
	return (this->*_DecMerchantMirrorItem)(itemInfo);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int index)> CSession::_GetMerchantMirrorItemInfoByIndex(SAKEXE, "CSession::GetMerchantMirrorItemInfoByIndex");
ITEM_INFO CSession::GetMerchantMirrorItemInfoByIndex(int index) // line 3556-3564
{
	return (this->*_GetMerchantMirrorItemInfoByIndex)(index);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int sequence)> CSession::_GetMerchantMirrorItemInfoBySequence(SAKEXE, "CSession::GetMerchantMirrorItemInfoBySequence");
ITEM_INFO CSession::GetMerchantMirrorItemInfoBySequence(int sequence) // line 3504-3516
{
	return (this->*_GetMerchantMirrorItemInfoBySequence)(sequence);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearMerchantHopeToSellItem(SAKEXE, "CSession::ClearMerchantHopeToSellItem");
void CSession::ClearMerchantHopeToSellItem(void) // line 3286
{
	return (this->*_ClearMerchantHopeToSellItem)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_GetNumMerchantHopeToSellItem(SAKEXE, "CSession::GetNumMerchantHopeToSellItem");
int CSession::GetNumMerchantHopeToSellItem(void) // line 2404
{
	return (this->*_GetNumMerchantHopeToSellItem)();

	//TODO
}


hook_method<int (CSession::*)(int itemIndex)> CSession::_GetMerchantHopeToSellItemNum(SAKEXE, "CSession::GetMerchantHopeToSellItemNum");
int CSession::GetMerchantHopeToSellItemNum(int itemIndex) // line 3377
{
	return (this->*_GetMerchantHopeToSellItemNum)(itemIndex);

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO& itemInfo)> CSession::_AddMerchantHopeToSellItem(SAKEXE, "CSession::AddMerchantHopeToSellItem");
bool CSession::AddMerchantHopeToSellItem(ITEM_INFO& itemInfo) // line 3329
{
	return (this->*_AddMerchantHopeToSellItem)(itemInfo);

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO& itemInfo)> CSession::_DecMerchantHopeToSellItem(SAKEXE, "CSession::DecMerchantHopeToSellItem");
bool CSession::DecMerchantHopeToSellItem(ITEM_INFO& itemInfo) // line 3346
{
	return (this->*_DecMerchantHopeToSellItem)(itemInfo);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int index)> CSession::_GetMerchantHopeToSellItemInfoByIndex(SAKEXE, "CSession::GetMerchantHopeToSellItemInfoByIndex");
ITEM_INFO CSession::GetMerchantHopeToSellItemInfoByIndex(int index) // line 3366
{
	return (this->*_GetMerchantHopeToSellItemInfoByIndex)(index);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int sequence)> CSession::_GetMerchantHopeToSellItemInfoBySequence(SAKEXE, "CSession::GetMerchantHopeToSellItemInfoBySequence");
ITEM_INFO CSession::GetMerchantHopeToSellItemInfoBySequence(int sequence) // line 3298
{
	return (this->*_GetMerchantHopeToSellItemInfoBySequence)(sequence);

	//TODO
}


hook_method<void (CSession::*)(int sequence, int price)> CSession::_SetMerchantHopeToSellItemPrice(SAKEXE, "CSession::SetMerchantHopeToSellItemPrice");
void CSession::SetMerchantHopeToSellItemPrice(int sequence, int price) // line 3313
{
	return (this->*_SetMerchantHopeToSellItemPrice)(sequence, price);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearExchangeItemList(SERVER, "CSession::ClearExchangeItemList");
void CSession::ClearExchangeItemList(void) // line 2409
{
	return (this->*_ClearExchangeItemList)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_IsExchangeItemListFull(SAKEXE, "CSession::IsExchangeItemListFull");
int CSession::IsExchangeItemListFull(void) // line 2519-2521
{
	return (this->*_IsExchangeItemListFull)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_GetFilledExchangeItemList(SAKEXE, "CSession::GetFilledExchangeItemList");
int CSession::GetFilledExchangeItemList(void) // line 2524-2531
{
	return (this->*_GetFilledExchangeItemList)();

	//TODO
}


hook_method<void (CSession::*)(ITEM_INFO itemInfo)> CSession::_AddToExchangeList(SAKEXE, "CSession::AddToExchangeList");
void CSession::AddToExchangeList(ITEM_INFO itemInfo) // line 2491-2516
{
	return (this->*_AddToExchangeList)(itemInfo);

	//TODO
}


hook_method<void (CSession::*)(ITEM_INFO itemInfo)> CSession::_SetToExchangeList(SAKEXE, "CSession::SetToExchangeList");
void CSession::SetToExchangeList(ITEM_INFO itemInfo) // line 2462-2488
{
	return (this->*_SetToExchangeList)(itemInfo);

	//TODO
}


hook_method<bool (CSession::*)(int index)> CSession::_IsExistIndexInMyChangeList(SAKEXE, "CSession::IsExistIndexInMyChangeList");
bool CSession::IsExistIndexInMyChangeList(int index) // line 2542-2550
{
	return (this->*_IsExistIndexInMyChangeList)(index);

	//TODO
}


hook_method<bool (CSession::*)(ITEM_INFO itemInfo)> CSession::_MoveItemToExchangeList(SAKEXE, "CSession::MoveItemToExchangeList");
bool CSession::MoveItemToExchangeList(ITEM_INFO itemInfo) // line 2441-2447
{
	return (this->*_MoveItemToExchangeList)(itemInfo);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_CancelExchange(SAKEXE, "CSession::CancelExchange");
void CSession::CancelExchange(void) // line 2428-2432
{
	return (this->*_CancelExchange)();

	if( g_bOldServer != 0 )
	{
		for( int i = 0; i < countof(m_exchangeItems); ++i )
		{
			if( m_exchangeItems[i].m_num == 0 )
				continue; // empty

			this->CSession::AddItem(&m_exchangeItems[i]); //inline
		}

		m_gold += m_myExchangeMoney;
		g_windowMgr.UIWindowMgr::InvalidateUpdateNeededUI();
	}

	m_myExchangeMoney = 0;
	for( int i = 0; i < countof(m_exchangeItems); ++i )
		m_exchangeItems[i].m_num = 0;
}


hook_method<void (CSession::*)(void)> CSession::_ClearOtherExchangeItemList(SERVER, "CSession::ClearOtherExchangeItemList");
void CSession::ClearOtherExchangeItemList(void) // line 2536
{
	return (this->*_ClearOtherExchangeItemList)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_CancelExchangeNoRefresh(SAKEXE, "CSession::CancelExchangeNoRefresh");
void CSession::CancelExchangeNoRefresh(void) // line 2415-2419
{
	return (this->*_CancelExchangeNoRefresh)();

	if( g_bOldServer != 0 )
	{
		for( int i = 0; i < countof(m_exchangeItems); ++i )
		{
			if( m_exchangeItems[i].m_num == 0 )
				continue; // empty

			this->CSession::AddItemNoRefresh(&m_exchangeItems[i]); //inline
		}

		m_gold += m_myExchangeMoney;
	}

	m_myExchangeMoney = 0;
	for( int i = 0; i < countof(m_exchangeItems); ++i )
		m_exchangeItems[i].m_num = 0;
}


hook_method<void (CSession::*)(void)> CSession::_ClearFriend(SERVER, "CSession::ClearFriend");
void CSession::ClearFriend(void) // line 4032
{
	return (this->*_ClearFriend)();

	m_friendList.clear(); //inlined
}


hook_method<int (CSession::*)(void)> CSession::_GetNumFriend(SAKEXE, "CSession::GetNumFriend");
int CSession::GetNumFriend(void) // line 4039
{
	return (this->*_GetNumFriend)();

	return m_friendList.size();
}


hook_method<FRIEND_INFO (CSession::*)(int sequence)> CSession::_GetFriendInfoBySequence(SAKEXE, "CSession::GetFriendInfoBySequence");
FRIEND_INFO CSession::GetFriendInfoBySequence(int sequence) // line 4043
{
	return (this->*_GetFriendInfoBySequence)(sequence);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ClearParty(SERVER, "CSession::ClearParty");
void CSession::ClearParty(void) // line 3913
{
	return (this->*_ClearParty)();

	m_partyList.clear(); //inlined
	m_amIPartyMaster = 0;
	m_partyName = "";
}


hook_method<int (CSession::*)(void)> CSession::_GetNumParty(SAKEXE, "CSession::GetNumParty");
int CSession::GetNumParty(void) // line 3921
{
	return (this->*_GetNumParty)();

	return m_partyList.size();
}


hook_method<void (CSession::*)(void)> CSession::_RefreshPartyUI(SAKEXE, "CSession::RefreshPartyUI");
void CSession::RefreshPartyUI(void) // line 3985
{
	return (this->*_RefreshPartyUI)();

	UIMessengerGroupWnd* messengerGroupWnd = g_windowMgr.UIWindowMgr::GetMessengerGroupWnd(); //inlined
	if( messengerGroupWnd != NULL )
		messengerGroupWnd->SendMsg(NULL, 23, 0, 0, 0);
}


hook_method<FRIEND_INFO (CSession::*)(unsigned long aid)> CSession::_GetPartyInfoByAid(SAKEXE, "CSession::GetPartyInfoByAid");
FRIEND_INFO CSession::GetPartyInfoByAid(unsigned long aid) // line 4019
{
	return (this->*_GetPartyInfoByAid)(aid);

	for( mystd::list<FRIEND_INFO>::const_iterator it = m_partyList.begin(); it != m_partyList.end(); ++it )
		if( it->AID == aid )
			return *it;

	return 0;
}


hook_method<void (CSession::*)(FRIEND_INFO& info)> CSession::_AddMemberToParty(SAKEXE, "CSession::AddMemberToParty");
void CSession::AddMemberToParty(FRIEND_INFO& info) // line 3925
{
	return (this->*_AddMemberToParty)(info);

	if( info.mapName.size() > 4 )
	{
		info.mapName.resize(info.mapName.size() - 3);
		info.mapName.append("rsw");
	}

	int count = 0;
	for( mystd::list<FRIEND_INFO>::iterator it = m_partyList.begin(); it != m_partyList.end(); ++it )
	{
		if( it->characterName == info.characterName )
		{
			info.color = this->CSession::GetPartyColorBySeq(count); //inlined
			*it = info;
			return;
		}

		++count;
	}

	info.color = this->CSession::GetPartyColorBySeq(count); //inlined
	m_partyList.push_back(info);
}


hook_method<FRIEND_INFO (CSession::*)(int sequence)> CSession::_GetPartyInfoBySequence(SAKEXE, "CSession::GetPartyInfoBySequence");
FRIEND_INFO CSession::GetPartyInfoBySequence(int sequence) // line 3991
{
	return (this->*_GetPartyInfoBySequence)(sequence);

	//TODO
}


hook_method<FRIEND_INFO (CSession::*)(const char* name)> CSession::_GetPartyInfoByName(SAKEXE, "CSession::GetPartyInfoByName");
FRIEND_INFO CSession::GetPartyInfoByName(const char* name) // line 4005-4016
{
	return (this->*_GetPartyInfoByName)(name);

	//TODO
}


hook_method<void (CSession::*)(const char* characterName)> CSession::_DeleteMemberFromParty(SAKEXE, "CSession::DeleteMemberFromParty");
void CSession::DeleteMemberFromParty(const char* characterName)
{
	return (this->*_DeleteMemberFromParty)(characterName);

	for( mystd::list<FRIEND_INFO>::iterator it = m_partyList.begin(); it != m_partyList.end(); ++it )
	{
		if( it->characterName == characterName )
		{
			m_partyList.erase(it);
			return;
		}
	}
}


hook_method<unsigned long (CSession::*)(const char* characterName)> CSession::_GetMemberAidFromParty(SAKEXE, "CSession::GetMemberAidFromParty");
unsigned long CSession::GetMemberAidFromParty(const char* characterName)
{
	return (this->*_GetMemberAidFromParty)(characterName);

	for( mystd::list<FRIEND_INFO>::iterator it = m_partyList.begin(); it != m_partyList.end(); ++it )
	{
		if( it->characterName == characterName )
			return it->AID;
	}

	return 0;
}


hook_method<int (CSession::*)(int itemID)> CSession::_GetWeaponType(SAKEXE, "CSession::GetWeaponType");
int CSession::GetWeaponType(int itemID) // line 3492 (Session2.cpp)
{
	return (this->*_GetWeaponType)(itemID);

	if( itemID == ITEM_NONE )
		return WEAPONTYPE_NONE;
	if( itemID >= ITEM_SWORD_TYPE_START && itemID < ITEM_TWOHANDSWORD_START )
		return WEAPONTYPE_SWORD;
	if( itemID >= ITEM_TWOHANDSWORD_START && itemID < ITEM_SHORTSWORD_START )
		return WEAPONTYPE_TWOHANDSWORD;
	if( itemID >= ITEM_SHORTSWORD_START && itemID < ITEM_CATARRH_START )
		return WEAPONTYPE_SHORTSWORD;
	if( itemID >= ITEM_CATARRH_START && itemID < ITEM_AXE_START )
		return WEAPONTYPE_CATARRH;
	if( itemID >= ITEM_AXE_START && itemID < ITEM_TWOHANDAXE_START )
		return WEAPONTYPE_AXE;
	if( itemID >= ITEM_TWOHANDAXE_START && itemID < ITEM_SPEAR_START )
		return WEAPONTYPE_TWOHANDAXE;
	if( itemID >= ITEM_SPEAR_START && itemID < ITEM_TWOHANDSPEAR_START )
		return WEAPONTYPE_SPEAR;
	if( itemID >= ITEM_TWOHANDSPEAR_START && itemID < ITEM_MACE_START )
	{
		if( itemID == ITEM_STAFF_OF_SOUL || itemID == ITEM_WIZARDRY_STAFF )
			return WEAPONTYPE_ROD;

		return WEAPONTYPE_TWOHANDSPEAR;
	}
	if( itemID >= ITEM_MACE_START && itemID < ITEM_BOOK_START )
		return WEAPONTYPE_MACE;
	if( itemID >= ITEM_BOOK_START && itemID < ITEM_ROD_START )
		return WEAPONTYPE_BOOK;
	if( itemID >= ITEM_ROD_START && itemID < ITEM_BOW_START )
		return WEAPONTYPE_ROD;
	if( itemID >= ITEM_BOW_START && itemID < ITEM_KNUKLE_START )
		return WEAPONTYPE_BOW;
	if( itemID >= ITEM_KNUKLE_START && itemID < ITEM_INSTRUMENT_START )
		return WEAPONTYPE_KNUKLE;
	if( itemID >= ITEM_INSTRUMENT_START && itemID < ITEM_WHIP_START )
		return WEAPONTYPE_INSTRUMENT;
	if( itemID >= ITEM_WHIP_START && itemID < ITEM_2000 )
		return WEAPONTYPE_WHIP;

	return -1;
}


hook_method<const char* (CSession::*)(int slot)> CSession::_GetShortenItemName(SAKEXE, "CSession::GetShortenItemName");
const char* CSession::GetShortenItemName(int slot) // line 2807
{
	return (this->*_GetShortenItemName)(slot);

	return m_shortenItemName[slot].c_str();
}


hook_method<int (CSession::*)(void)> CSession::_GetSex(SAKEXE, "CSession::GetSex");
int CSession::GetSex(void) // line 39 (Session2.cpp)
{
	return (this->*_GetSex)();

	if( m_sex != m_sexCheck )
		m_sex = m_sexCheck;

	return m_sex;
}


hook_method<void (CSession::*)(int sex)> CSession::_SetSex(SAKEXE, "CSession::SetSex");
void CSession::SetSex(int sex) // line 31 (Session2.cpp)
{
	return (this->*_SetSex)(sex);

	m_sex = sex & 1;
	m_sexCheck = m_sex;
}


hook_method<unsigned long (CSession::*)(void)> CSession::_GetAid(SAKEXE, "CSession::GetAid");
unsigned long CSession::GetAid(void) // line 561 (Session.h)
{
	return (this->*_GetAid)();

	return m_aid;
}


hook_method<unsigned long (CSession::*)(void)> CSession::_GetGid(SAKEXE, "CSession::GetGid");
unsigned long CSession::GetGid(void) // line 562 (Session.h)
{
	return (this->*_GetGid)();

	return m_gid;
}


//hook_method<void (CSession::*)(unsigned long aid)> CSession::_SetAid(SAKEXE, "CSession::SetAid");
void CSession::SetAid(unsigned long aid) // line ???
{
//	return (this->*_SetAid)(aid);

	m_aid = aid;
}


//hook_method<void (CSession::*)(unsigned long gid)> CSession::_SetGid(SAKEXE, "CSession::SetGid");
void CSession::SetGid(unsigned long gid) // line ???
{
//	return (this->*_SetGid)(gid);

	m_gid = gid;
}


hook_method<int (CSession::*)(void)> CSession::_GetJob(SAKEXE, "CSession::GetJob");
int CSession::GetJob(void) // line 7088-7104
{
	return (this->*_GetJob)();

	return m_job;
}


//hook_method<int (CSession::*)(void)> CSession::_GetExp(SAKEXE, "CSession::GetExp");
int CSession::GetExp(void) // line ???
{
//	return (this->*_GetExp)();

	return m_exp;
}


//hook_method<int (CSession::*)(void)> CSession::_GetSpeed(SAKEXE, "CSession::GetSpeed");
int CSession::GetSpeed(void) // line ???
{
//	return (this->*_GetSpeed)();

	return m_speed;
}


//hook_method<int (CSession::*)(void)> CSession::_GetWeight(SAKEXE, "CSession::GetWeight");
int CSession::GetWeight(void) // line ????
{
//	return (this->*_GetWeight)();

	return m_weight;
}


//hook_method<int (CSession::*)(void)> CSession::_GetNextExp(SAKEXE, "CSession::GetNextExp");
int CSession::GetNextExp(void) // line ???
{
//	return (this->*_GetNextExp)();

	return m_nextexp;
}


//hook_method<int (CSession::*)(void)> CSession::_GetMaxWeight(SAKEXE, "CSession::GetMaxWeight");
int CSession::GetMaxWeight(void) // line ????
{
//	return (this->*_GetMaxWeight)();

	return m_maxWeight;
}


hook_method<int (CSession::*)(void)> CSession::_GetEquipArrowIndex(SAKEXE, "CSession::GetEquipArrowIndex");
int CSession::GetEquipArrowIndex(void) // line 605 (Session.h)
{
	return (this->*_GetEquipArrowIndex)();

	//TODO
}


hook_method<const char* (CSession::*)(void)> CSession::_GetCharName(SAKEXE, "CSession::GetCharName");
const char* CSession::GetCharName(void) // line 14 (Session2.cpp)
{
	return (this->*_GetCharName)();

	//TODO
}


hook_method<void (CSession::*)(bool isShorten, bool isBold)> CSession::_SetTextType(SAKEXE, "CSession::SetTextType");
void CSession::SetTextType(bool isShorten, bool isBold) // line 570 (Framework/Locale.cpp)
{
	return (this->*_SetTextType)(isShorten, isBold);

	//TODO
}


/// Rotate 'value' 1 byte to the right.
static hook_func<int (__cdecl *)(int value)> _MoveBitForward(SAKEXE, "MoveBitForward");
static int __cdecl MoveBitForward(int value) // line 6824
{
	return (_MoveBitForward)(value);

	return (value << 24) & 0xFF000000
		 + (value >>  8) & 0x00FF0000
		 + (value >>  8) & 0x0000FF00
		 + (value >>  8) & 0x000000FF;
}


static hook_func<int (__cdecl *)(int value, int moveCnt)> _MoveBitForwardCnt(SAKEXE, "MoveBitForwardCnt");
int __cdecl MoveBitForwardCnt(int value, int moveCnt) // line 6834
{
	return (_MoveBitForwardCnt)(value, moveCnt);

	//TODO
}


hook_method<int (CSession::*)(int number, int encodeValue)> CSession::_Encode(SAKEXE, "CSession::Encode");
int CSession::Encode(int number, int encodeValue) // line 6846
{
	return (this->*_Encode)(number, encodeValue);

	int val = number;
	int count = (encodeValue % 6) * 2 + 2;

	for( int i = 0; i < count; ++i )
		val = MoveBitForwardCnt(encodeValue, i) ^ MoveBitForward(val);

	return val;
}


hook_method<int (CSession::*)(int number, int decodeValue)> CSession::_Decode(SAKEXE, "CSession::Decode");
int CSession::Decode(int number, int decodeValue) // line 6859
{
	return (this->*_Decode)(number, decodeValue);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_ChangeXorValue(SAKEXE, "CSession::ChangeXorValue");
void CSession::ChangeXorValue(void) // line 6792
{
	return (this->*_ChangeXorValue)();

	static int s_isFirst = 1;
	if( s_isFirst )
	{
		s_isFirst = 0;
		m_xorIndex = rand() % 12;
		m_hpIndex = rand() % 12;
		m_maxhpIndex = rand() % 12;
		m_spIndex = rand() % 12;
		m_maxspIndex = rand() % 12;
	}

	int hp = this->CSession::GetHp(); //inlined
	int maxhp = this->CSession::GetMaxhp(); //inlined
	int sp = this->CSession::GetSp(); //inlined
	int maxsp = this->CSession::GetMaxsp(); //inlined

	m_xorIndex = rand() % 12;
	m_hpIndex = rand() % 12;
	m_maxhpIndex = rand() % 12;
	m_spIndex = rand() % 12;
	m_maxspIndex = rand() % 12;

	for( int i = 0; i < 12; ++i )
		m_xorValue[i] = rand();

	this->CSession::SetHp(hp); //inlined
	this->CSession::SetMaxhp(maxhp); //inlined
	this->CSession::SetSp(sp); //inlined
	this->CSession::SetMaxsp(maxsp); //inlined
}


//hook_method<void (CSession::*)(int hp)> CSession::_SetHp(SAKEXE, "CSession::SetHp");
void CSession::SetHp(int hp) // line ????
{
//	return (this->*_SetHp)(hp);

	int enc_hp = this->CSession::Encode(hp, m_xorValue[m_xorIndex]); //inlined
	if( enc_hp != m_hp[m_hpIndex] )
	{
		m_hp[m_hpIndex] = enc_hp;
		this->CSession::InvalidateBasicWnd();
	}
}


//hook_method<void (CSession::*)(int maxhp)> CSession::_SetMaxhp(SAKEXE, "CSession::SetMaxhp");
void CSession::SetMaxhp(int maxhp) // line ????
{
//	return (this->*_SetMaxhp)(maxhp);

	int enc_maxhp = this->CSession::Encode(maxhp, m_xorValue[m_xorIndex]); //inlined
	if( enc_maxhp != m_maxhp[m_maxhpIndex] )
	{
		m_maxhp[m_maxhpIndex] = enc_maxhp;
		this->CSession::InvalidateBasicWnd();
	}
}


//hook_method<void (CSession::*)(int sp)> CSession::_SetSp(SAKEXE, "CSession::SetSp");
void CSession::SetSp(int sp) // line ????
{
//	return (this->*_SetSp)(sp);

	int enc_sp = this->CSession::Encode(sp, m_xorValue[m_xorIndex]); //inlined
	if( enc_sp != m_sp[m_spIndex] )
	{
		m_sp[m_spIndex] = enc_sp;
		this->CSession::InvalidateBasicWnd();
	}
}


//hook_method<void (CSession::*)(int maxsp)> CSession::_SetMaxsp(SAKEXE, "CSession::SetMaxsp");
void CSession::SetMaxsp(int maxsp) // line ????
{
//	return (this->*_SetMaxsp)(maxsp);

	int enc_maxsp = this->CSession::Encode(maxsp, m_xorValue[m_xorIndex]); //inlined
	if( enc_maxsp != m_maxsp[m_maxspIndex] )
	{
		m_maxsp[m_maxspIndex] = enc_maxsp;
		this->CSession::InvalidateBasicWnd();
	}
}


//hook_method<int (CSession::*)(void)> CSession::_GetHp(SAKEXE, "CSession::GetHp");
int CSession::GetHp(void) // line ????
{
//	return (this->*_GetHp)();

	return this->CSession::Decode(m_hp[m_hpIndex], m_xorValue[m_xorIndex]);
}


hook_method<int (CSession::*)(void)> CSession::_GetSp(SAKEXE, "CSession::GetSp");
int CSession::GetSp(void) // line 655 (Session.h)
{
	return (this->*_GetSp)();

	return this->CSession::Decode(m_sp[m_spIndex], m_xorValue[m_xorIndex]);
}


//hook_method<int (CSession::*)(void)> CSession::_GetMaxhp(SAKEXE, "CSession::GetMaxhp");
int CSession::GetMaxhp(void) // line ????
{
//	return (this->*_GetMaxhp)();

	return this->CSession::Decode(m_maxhp[m_maxhpIndex], m_xorValue[m_xorIndex]);
}


//hook_method<int (CSession::*)(void)> CSession::_GetMaxsp(SAKEXE, "CSession::GetMaxsp");
int CSession::GetMaxsp(void) // line ????
{
//	return (this->*_GetMaxsp)();

	return this->CSession::Decode(m_maxsp[m_maxspIndex], m_xorValue[m_xorIndex]);
}


hook_method<void (CSession::*)(void)> CSession::_InvalidateUI(SAKEXE, "CSession::InvalidateUI");
void CSession::InvalidateUI(void) // line 4142
{
	return (this->*_InvalidateUI)();

	g_windowMgr.UIWindowMgr::InvalidateUpdateNeededUI();
}


hook_method<void (CSession::*)(void)> CSession::_InvalidateJob(SAKEXE, "CSession::InvalidateJob");
void CSession::InvalidateJob(void) // line 4125
{
	return (this->*_InvalidateJob)();

	UIBasicInfoWnd* wnd = g_windowMgr.UIWindowMgr::GetBasicInfoWnd();
	if( wnd != NULL )
		wnd->UIBasicInfoWnd::NewHeight(wnd->UIWindow::GetHeight());
}


hook_method<void (CSession::*)(void)> CSession::_InvalidateBasicWnd(SAKEXE, "CSession::InvalidateBasicWnd");
void CSession::InvalidateBasicWnd(void) // line 4131
{
	return (this->*_InvalidateBasicWnd)();

	CGameMode* gamemode = g_modeMgr.CModeMgr::GetGameMode();
	if( gamemode == NULL )
		return;

	UIBasicInfoWnd* wnd = g_windowMgr.UIWindowMgr::GetBasicInfoWnd();
	if( wnd != NULL )
	{
		wnd->Invalidate();
		wnd->UIWindow::InvalidateChildren();
	}

	gamemode->CGameMode::InvalidatePlayerGage(); //inlined
}


//hook_method<void (CSession::*)(int str)> CSession::_SetStr(SAKEXE, "CSession::SetStr");
void CSession::SetStr(int str) // line ????
{
//	return (this->*_SetStr)(str);

	m_str = str;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int agi)> CSession::_SetAgi(SAKEXE, "CSession::SetAgi");
void CSession::SetAgi(int agi) // line ????
{
//	return (this->*_SetAgi)(agi);

	m_agi = agi;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int vit)> CSession::_SetVit(SAKEXE, "CSession::SetVit");
void CSession::SetVit(int vit) // line ????
{
//	return (this->*_SetVit)(vit);

	m_vit = vit;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int int_)> CSession::_SetInt(SAKEXE, "CSession::SetInt");
void CSession::SetInt(int int_) // line ????
{
//	return (this->*_SetInt)(int_);

	m_int = int_;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int dex)> CSession::_SetDex(SAKEXE, "CSession::SetDex");
void CSession::SetDex(int dex) // line ????
{
//	return (this->*_SetDex)(dex);

	m_dex = dex;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int luk)> CSession::_SetLuk(SAKEXE, "CSession::SetLuk");
void CSession::SetLuk(int luk) // line ????
{
//	return (this->*_SetLuk)(luk);

	m_luk = luk;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int exp)> CSession::_SetExp(SAKEXE, "CSession::SetExp");
void CSession::SetExp(int exp) // line ????
{
//	return (this->*_SetExp)(exp);

	m_exp = exp;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int level)> CSession::_SetLevel(SAKEXE, "CSession::SetLevel");
void CSession::SetLevel(int level) // line ????
{
//	return (this->*_SetLevel)(level);

	m_level = level;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int point)> CSession::_SetPoint(SAKEXE, "CSession::SetPoint");
void CSession::SetPoint(int point) // line ????
{
//	return (this->*_SetPoint)(point);

	m_point = point;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusstr)> CSession::_SetPlusStr(SAKEXE, "CSession::SetPlusStr");
void CSession::SetPlusStr(int plusstr) // line ????
{
//	return (this->*_SetPlusStr)(plusstr);

	m_plusStr = plusstr;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusagi)> CSession::_SetPlusAgi(SAKEXE, "CSession::SetPlusAgi");
void CSession::SetPlusAgi(int plusagi) // line ????
{
//	return (this->*_SetPlusAgi)(plusagi);

	m_plusAgi = plusagi;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusvit)> CSession::_SetPlusVit(SAKEXE, "CSession::SetPlusVit");
void CSession::SetPlusVit(int plusvit) // line ????
{
//	return (this->*_SetPlusVit)(plusvit);

	m_plusVit = plusvit;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusint)> CSession::_SetPlusInt(SAKEXE, "CSession::SetPlusInt");
void CSession::SetPlusInt(int plusint) // line ????
{
//	return (this->*_SetPlusInt)(plusint);

	m_plusInt = plusint;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusdex)> CSession::_SetPlusDex(SAKEXE, "CSession::SetPlusDex");
void CSession::SetPlusDex(int plusdex) // line ????
{
//	return (this->*_SetPlusDex)(plusdex);

	m_plusDex = plusdex;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusluk)> CSession::_SetPlusLuk(SAKEXE, "CSession::SetPlusLuk");
void CSession::SetPlusLuk(int plusluk) // line ????
{
//	return (this->*_SetPlusLuk)(plusluk);

	m_plusLuk = plusluk;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int skillpoint)> CSession::_SetSkillPoint(SAKEXE, "CSession::SetSkillPoint");
void CSession::SetSkillPoint(int skillpoint) // line ????
{
//	return (this->*_SetSkillPoint)(skillpoint);

	m_skillPoint = skillpoint;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int nextexp)> CSession::_SetNextexp(SAKEXE, "CSession::SetNextexp");
void CSession::SetNextexp(int nextexp) // line ???
{
//	return (this->*_SetSkillPoint)(skillpoint);

	m_nextexp = nextexp;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int str)> CSession::_SetStandardStr(SAKEXE, "CSession::SetStandardStr");
void CSession::SetStandardStr(int str) // line ???
{
//	return (this->*_SetStandardStr)(str);

	m_standardStr = str;
}


//hook_method<void (CSession::*)(int agi)> CSession::_SetStandardAgi(SAKEXE, "CSession::SetStandardAgi");
void CSession::SetStandardAgi(int agi) // line ???
{
//	return (this->*_SetStandardAgi)(agi);

	m_standardAgi = agi;
}


//hook_method<void (CSession::*)(int vit)> CSession::_SetStandardVit(SAKEXE, "CSession::SetStandardVit");
void CSession::SetStandardVit(int vit) // line ???
{
//	return (this->*_SetStandardVit)(vit);

	m_standardVit = vit;
}


//hook_method<void (CSession::*)(int int_)> CSession::_SetStandardInt(SAKEXE, "CSession::SetStandardInt");
void CSession::SetStandardInt(int int_) // line ???
{
//	return (this->*_SetStandardInt)(int_);

	m_standardInt = int_;
}


//hook_method<void (CSession::*)(int dex)> CSession::_SetStandardDex(SAKEXE, "CSession::SetStandardDex");
void CSession::SetStandardDex(int dex) // line ???
{
//	return (this->*_SetStandardDex)(dex);

	m_standardDex = dex;
}


//hook_method<void (CSession::*)(int luk)> CSession::_SetStandardLuk(SAKEXE, "CSession::SetStandardLuk");
void CSession::SetStandardLuk(int luk) // line ???
{
//	return (this->*_SetStandardLuk)(luk);

	m_standardLuk = luk;
}


//hook_method<void (CSession::*)(int job)> CSession::_SetJob(SAKEXE, "CSession::SetJob");
void CSession::SetJob(int job) // line ????
{
//	return (this->*_SetJob)(job);

	m_job = job;
	this->CSession::InvalidateUI();
	this->CSession::InvalidateJob();
}


//hook_method<void (CSession::*)(int joblevel)> CSession::_SetJoblevel(SAKEXE, "CSession::SetJoblevel");
void CSession::SetJoblevel(int joblevel) // line ????
{
//	return (this->*_SetJoblevel)(joblevel);

	m_joblevel = joblevel;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int gold)> CSession::_SetGold(SAKEXE, "CSession::SetGold");
void CSession::SetGold(int gold) // line ????
{
//	return (this->*_SetGold)(gold);

	m_gold = gold;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int jobexp)> CSession::_SetJobexp(SAKEXE, "CSession::SetJobexp");
void CSession::SetJobexp(int jobexp) // line ????
{
//	return (this->*_SetJobexp)(jobexp);

	m_jobexp = jobexp;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int speed)> CSession::_SetSpeed(SAKEXE, "CSession::SetSpeed");
void CSession::SetSpeed(int speed) // line ????
{
//	return (this->*_SetSpeed)(speed);

	m_speed = speed;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int honor)> CSession::_SetHonor(SAKEXE, "CSession::SetHonor");
void CSession::SetHonor(int honor) // line ????
{
//	return (this->*_SetHonor)(honor);

	m_honor = honor;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int weight)> CSession::_SetWeight(SAKEXE, "CSession::SetWeight");
void CSession::SetWeight(int weight) // line ????
{
//	return (this->*_SetWeight)(weight);

	m_weight = weight;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int virtue)> CSession::_SetVirtue(SAKEXE, "CSession::SetVirtue");
void CSession::SetVirtue(int virtue) // line ????
{
//	return (this->*_SetVirtue)(virtue);

	m_virtue = virtue;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int jobnextexp)> CSession::_SetJobnextexp(SAKEXE, "CSession::SetJobnextexp");
void CSession::SetJobnextexp(int jobnextexp)
{
//	return (this->*_SetJobnextexp)(jobnextexp);

	m_jobnextexp = jobnextexp;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int maxweight)> CSession::_SetMaxWeight(SAKEXE, "CSession::SetMaxWeight");
void CSession::SetMaxWeight(int maxweight) // line ????
{
//	return (this->*_SetMaxWeight)(maxweight);

	m_maxWeight = maxweight;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int attpower)> CSession::_SetAttPower(SAKEXE, "CSession::SetAttPower");
void CSession::SetAttPower(int attpower) // line ????
{
//	return (this->*_SetAttPower)(attpower);

	m_attPower = attpower;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int mdefpower)> CSession::_SetMdefPower(SAKEXE, "CSession::SetMdefPower");
void CSession::SetMdefPower(int mdefpower) // line ????
{
//	return (this->*_SetMdefPower)(mdefpower);

	m_mdefPower = mdefpower;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int itemdefpower)> CSession::_SetItemDefPower(SAKEXE, "CSession::SetItemDefPower");
void CSession::SetItemDefPower(int itemdefpower) // line ????
{
//	return (this->*_SetItemDefPower)(itemdefpower);

	m_itemDefPower = itemdefpower;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusdefpower)> CSession::_SetPlusdefPower(SAKEXE, "CSession::SetPlusdefPower");
void CSession::SetPlusdefPower(int plusdefpower) // line ???
{
//	return (this->*_SetPlusdefPower)(plusdefpower);

	m_plusdefPower = plusdefpower;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int refiningpower)> CSession::_SetRefiningPower(SAKEXE, "CSession::SetRefiningPower");
void CSession::SetRefiningPower(int refiningpower) // line ???
{
//	return (this->*_SetRefiningPower)(refiningpower);

	m_refiningPower = refiningpower;
	this->CSession::InvalidateUI();
}



//hook_method<void (CSession::*)(int mattpower)> CSession::_SetMax_mattPower(SAKEXE, "CSession::SetMax_mattPower");
void CSession::SetMax_mattPower(int mattpower) // line ???
{
//	return (this->*_SetMax_mattPower)(mattpower);

	m_max_mattPower = mattpower;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int mattpower)> CSession::_SetMin_mattPower(SAKEXE, "CSession::SetMin_mattPower");
void CSession::SetMin_mattPower(int mattpower) // line ???
{
//	return (this->*_SetMin_mattPower)(mattpower);

	m_min_mattPower = mattpower;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int aspd)> CSession::_SetASPD(SAKEXE, "CSession::SetASPD");
void CSession::SetASPD(int aspd) // line ???
{
//	return (this->*_SetASPD)(aspd);

	m_ASPD = aspd;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusaspd)> CSession::_SetPlusASPD(SAKEXE, "CSession::SetPlusASPD");
void CSession::SetPlusASPD(int plusaspd) // line ???
{
//	return (this->*_SetPlusASPD)(plusaspd);

	m_plusASPD = plusaspd;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusmdefpower)> CSession::_SetPlusmdefPower(SAKEXE, "CSession::SetPlusmdefPower");
void CSession::SetPlusmdefPower(int plusmdefpower) // line ???
{
//	return (this->*_SetPlusmdefPower)(plusmdefpower);

	m_plusmdefPower = plusmdefpower;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int hitsuccessvalue)> CSession::_SetHitSuccessValue(SAKEXE, "CSession::SetHitSuccessValue");
void CSession::SetHitSuccessValue(int hitsuccessvalue) // line ???
{
//	return (this->*_SetHitSuccessValue)(hitsuccessvalue);

	m_hitSuccessValue = hitsuccessvalue;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int avoidsuccessvalue)> CSession::_SetAvoidSuccessValue(SAKEXE, "CSession::SetAvoidSuccessValue");
void CSession::SetAvoidSuccessValue(int avoidsuccessvalue) // line ???
{
//	return (this->*_SetAvoidSuccessValue)(avoidsuccessvalue);

	m_avoidSuccessValue = avoidsuccessvalue;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int criticalsuccessvalue)> CSession::_SetCriticalSuccessValue(SAKEXE, "CSession::SetCriticalSuccessValue");
void CSession::SetCriticalSuccessValue(int criticalsuccessvalue) // line ???
{
//	return (this->*_SetCriticalSuccessValue)(criticalsuccessvalue);

	m_criticalSuccessValue = criticalsuccessvalue;
	this->CSession::InvalidateUI();
}


//hook_method<void (CSession::*)(int plusavoidsuccessvalue)> CSession::_SetPlusAvoidSuccessValue(SAKEXE, "CSession::SetPlusAvoidSuccessValue");
void CSession::SetPlusAvoidSuccessValue(int plusavoidsuccessvalue) // line ???
{
//	return (this->*_SetPlusAvoidSuccessValue)(plusavoidsuccessvalue);

	m_plusAvoidSuccessValue = plusavoidsuccessvalue;
	this->CSession::InvalidateUI();
}


hook_method<unsigned long (CSession::*)(int seq)> CSession::_GetPartyColorBySeq(SAKEXE, "CSession::GetPartyColorBySeq");
unsigned long CSession::GetPartyColorBySeq(int seq) // line 4481
{
	return (this->*_GetPartyColorBySeq)(seq);

	switch( seq )
	{
	case 0: return 0xFF0A3278;
	case 1: return 0xFF007878;
	case 2: return 0xFF000000;
	case 3:
	case 15: return 0xFF780000;
	case 4: return 0xFF007800;
	case 5: return 0xFF787800;
	case 6: return 0xFF780078;
	case 7: return 0xFF783200;
	case 8: return 0xFF787878;
	case 9: return 0xFF000078;
	case 10: return 0xFF003232;
	case 11: return 0xFF320000;
	case 12: return 0xFF003200;
	case 13: return 0xFF323200;
	case 14: return 0xFF320032;
	default: return 0xFF323232;
	}
}


hook_method<void (CSession::*)(int value)> CSession::_SetEquipArrowIndwx(SAKEXE, "CSession::SetEquipArrowIndwx");
void CSession::SetEquipArrowIndwx(int value) // line 4475
{
	return (this->*_SetEquipArrowIndwx)(value);

	//TODO
}


hook_method<ITEM_INFO (CSession::*)(int wearLocation)> CSession::_GetEquipedItems(SAKEXE, "CSession::GetEquipedItems");
ITEM_INFO CSession::GetEquipedItems(int wearLocation) // line 4464-4472
{
	return (this->*_GetEquipedItems)(wearLocation);

	if( wearLocation == WEARLOCATION_ARROW )
		return this->CSession::GetItemInfoByIndex(m_equipArrowIndex);

	if( wearLocation < WEARLOCATION_HEAD || wearLocation > WEARLOCATION_HEAD3 )
		return ITEM_INFO();

	return m_equipedItems[wearLocation];
}


hook_method<TALKTYPE (CSession::*)(const char* command)> CSession::_GetNoParamTalkType(SAKEXE, "CSession::GetNoParamTalkType");
TALKTYPE CSession::GetNoParamTalkType(const char* command) // line 5119
{
	return (this->*_GetNoParamTalkType)(command);

	mystd::vector< mystd::pair<const char*, enum TALKTYPE> >::const_iterator it;
	it = mystd::lower_bound(m_talkTypeTable.begin(), m_talkTypeTable.end(), command, DComp()); //inlined
	return ( it != m_talkTypeTable.end() && strcmp(it->first, command) == 0 ) ? it->second : TT_UNKNOWN;
}


hook_method<bool (CSession::*)(int job, int sex, int weapon)> CSession::_IsSecondAttack(SAKEXE, "CSession::IsSecondAttack");
bool CSession::IsSecondAttack(int job, int sex, int weapon) // line 5745
{
	return (this->*_IsSecondAttack)(job, sex, weapon);

	//TODO
}


hook_method<float (CSession::*)(int job, int sex, int weapon, int isSecondAttack)> CSession::_GetPCAttackMotion(SAKEXE, "CSession::GetPCAttackMotion");
float CSession::GetPCAttackMotion(int job, int sex, int weapon, int isSecondAttack) // line 5703
{
	return (this->*_GetPCAttackMotion)(job, sex, weapon, isSecondAttack);

	//TODO
}


hook_method<float (CSession::*)(int job)> CSession::_GetShadowFactorWithJob(SAKEXE, "CSession::GetShadowFactorWithJob");
float CSession::GetShadowFactorWithJob(int job) // line 6441
{
	return (this->*_GetShadowFactorWithJob)(job);

	return m_shadowFactorTable[job];
}


hook_method<bool (CSession::*)(int job, int weapon)> CSession::_IsProperWeapon(SAKEXE, "CSession::IsProperWeapon");
bool CSession::IsProperWeapon(int job, int weapon)
{
	return (this->*_IsProperWeapon)(job, weapon);

	//TODO
}


hook_method<const char* (CSession::*)(int job, int sex, int palNum, char* buf)> CSession::_GetBodyPaletteName(SAKEXE, "CSession::GetBodyPaletteName");
const char* CSession::GetBodyPaletteName(int job, int sex, int palNum, char* buf) // line 6517
{
	return (this->*_GetBodyPaletteName)(job, sex, palNum, buf);

	//TODO
}


hook_method<const char* (CSession::*)(int head, int job, int sex, int palNum, char* buf)> CSession::_GetHeadPaletteName(SAKEXE, "CSession::GetHeadPaletteName");
const char* CSession::GetHeadPaletteName(int head, int job, int sex, int palNum, char* buf) // line 6503
{
	return (this->*_GetHeadPaletteName)(head, job, sex, palNum, buf);

	//TODO
}


hook_method<const char* (CSession::*)(int job)> CSession::_GetJobName(SAKEXE, "CSession::GetJobName");
const char* CSession::GetJobName(int job) // line 7022
{
	return (this->*_GetJobName)(job);

	return m_jobNameTable[job];
}


hook_method<void (CSession::*)(void)> CSession::_PreLoadAlwaysNeededRes(SAKEXE, "CSession::PreLoadAlwaysNeededRes");
void CSession::PreLoadAlwaysNeededRes(void) // line 6872
{
	return (this->*_PreLoadAlwaysNeededRes)();

	//TODO
}


int CSession::GetShieldType(int ShieldId) // line 3534-3561
{
	switch( ShieldId )
	{
	default:
		return SHIELD_NONE;

	case ITEM_GUARD:
	case ITEM_GUARD_:
		return SHIELD_GUARD;

	case ITEM_BUCKLER:
	case ITEM_BUCKLER_:
		return SHIELD_BUCKLER;

	case ITEM_SHIELD:
	case ITEM_SHIELD_:
		return SHIELD_SHIELD;

	case ITEM_MIRROR_SHIELD:
	case ITEM_MIRROR_SHIELD_:
	case ITEM_HOLY_GUARD:
	case ITEM_HERALD_OF_GOD:
		return SHIELD_MIRRORSHIELD;
	}
}


hook_method<void (CSession::*)(void)> CSession::_RerecordProhibitLog(SAKEXE, "CSession::RerecordProhibitLog");
void CSession::RerecordProhibitLog(void) // line 3758 (Session2.cpp)
{
	return (this->*_RerecordProhibitLog)();

	//TODO
}


hook_method<void (CSession::*)(unsigned long AID)> CSession::_DeleteAssignAID(SAKEXE, "CSession::DeleteAssignAID");
void CSession::DeleteAssignAID(unsigned long AID) // line 3746 (Session2.cpp)
{
	return (this->*_DeleteAssignAID)(AID);

	//TODO
}


hook_method<void (CSession::*)(unsigned long AID, unsigned long prohibitTime)> CSession::_EraseProhibit(SAKEXE, "CSession::EraseProhibit");
void CSession::EraseProhibit(unsigned long AID, unsigned long prohibitTime) // line 3872-3896 (Session2.cpp)
{
	return (this->*_EraseProhibit)(AID, prohibitTime);

	//TODO
}


hook_method<void (CSession::*)(unsigned long AID, unsigned long prohibitTime)> CSession::_AppendProhibit(SAKEXE, "CSession::AppendProhibit");
void CSession::AppendProhibit(unsigned long AID, unsigned long prohibitTime) // line 3664-3743 (Session2.cpp)
{
	return (this->*_AppendProhibit)(AID, prohibitTime);

	//TODO
}


hook_method<int (CSession::*)(int job)> CSession::_IsPc(SAKEXE, "CSession::IsPc");
int CSession::IsPc(int job) // line 3202 (Session2.cpp)
{
	return (this->*_IsPc)(job);

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_IsSiegeMode(SAKEXE, "CSession::IsSiegeMode");
int CSession::IsSiegeMode(void) // line 3213 (Session2.cpp)
{
	return (this->*_IsSiegeMode)();

	//TODO
}


COLORREF CSession::GetItemDisColor(ITEM_INFO* itemInfo) // 5167-5172
{
	return ( itemInfo->m_isIdentified ) ? 0xFFFFFFFF : 0xFFAAAAAA;
}


hook_method<bool (CSession::*)(void)> CSession::_GetEmblemState(SAKEXE, "CSession::GetEmblemState");
bool CSession::GetEmblemState(void) // line 792 (Session.h)
{
	return (this->*_GetEmblemState)();

	return m_emblemState;
}


hook_method<void (CSession::*)(char* buffer, int gdid, int version)> CSession::_GetEmblemFileName(SAKEXE, "CSession::GetEmblemFileName");
void CSession::GetEmblemFileName(char* buffer, int gdid, int version) // line 7012
{
	return (this->*_GetEmblemFileName)(buffer, gdid, version);

	//TODO
}


//hook_method<void (CSession::*)(bool emblemState)> CSession::_SetEmblemState(SAKEXE, "CSession::SetEmblemState");
void CSession::SetEmblemState(bool emblemState) // line ????
{
//	return (this->*_SetEmblemState)(emblemState);

	m_emblemState = emblemState;
}


hook_method<void (CSession::*)(const char* compressedEmblemImage, unsigned long emblemLen, int GDID, int emblemVersion)> CSession::_SetCompressedEmblemImage(SAKEXE, "CSession::SetCompressedEmblemImage");
void CSession::SetCompressedEmblemImage(const char* compressedEmblemImage, unsigned long emblemLen, int GDID, int emblemVersion) // line 6971
{
	return (this->*_SetCompressedEmblemImage)(compressedEmblemImage, emblemLen, GDID, emblemVersion);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitShortCutTextFromReg(SERVER, "CSession::InitShortCutTextFromReg");
void CSession::InitShortCutTextFromReg(void) // line 1965 (Session2.cpp)
{
	return (this->*_InitShortCutTextFromReg)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_IsKorean(SAKEXE, "CSession::IsKorean");
int CSession::IsKorean(void) // line 5176
{
	return (this->*_IsKorean)();

	return ( g_serviceType == 0 );
}


hook_method<int (CSession::*)(int job)> CSession::_IsMonster(SAKEXE, "CSession::IsMonster");
int CSession::IsMonster(int job) // line 3195 (Session2.cpp)
{
	return (this->*_IsMonster)(job);

	//TODO
}


hook_method<int (CSession::*)(int gdid)> CSession::_IsMyGuild(SAKEXE, "CSession::IsMyGuild");
int CSession::IsMyGuild(int gdid) // line 3226 (Session2.cpp)
{
	return (this->*_IsMyGuild)(gdid);

	if( gdid == 0 )
		return 0;

	CPlayer* p = g_modeMgr.CModeMgr::GetGameMode()->CGameMode::GetWorld()->m_player;
	if( p == NULL )
		return 0;

	return ( gdid == p->GetGdid() );
}


hook_method<int (CSession::*)(int job)> CSession::_IsGuardian(SAKEXE, "CSession::IsGuardian");
int CSession::IsGuardian(int job) // line 3238 (Session2.cpp)
{
	return (this->*_IsGuardian)(job);

	//TODO
}


hook_method<int (CSession::*)(int itemId)> CSession::_IsPetEgg(SAKEXE, "CSession::IsPetEgg");
int CSession::IsPetEgg(int itemId) // line 3245 (Session2.cpp)
{
	return (this->*_IsPetEgg)(itemId);

	return ( itemId > 9000 && itemId <= 9025 );
}


hook_method<int (CSession::*)(int showLevel)> CSession::_IsMasterAid(SAKEXE, "CSession::IsMasterAid");
int CSession::IsMasterAid(int showLevel) // line 5199
{
	return (this->*_IsMasterAid)(showLevel);

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitPetTables(SERVER, "CSession::InitPetTables");
void CSession::InitPetTables(void) // line 2299 (Session2.cpp)
{
	return (this->*_InitPetTables)();

	//TODO
}


hook_method<void (CSession::*)(void)> CSession::_InitPetTalkTable(SERVER, "CSession::InitPetTalkTable");
void CSession::InitPetTalkTable(void) // line 2507 (Session2.cpp)
{
	return (this->*_InitPetTalkTable)();

	//TODO
}


hook_method<void (CSession::*)(char* Name, int skillId, int& act, int& loopType)> CSession::_GetMonsterSkillInfo(SAKEXE, "CSession::GetMonsterSkillInfo");
void CSession::GetMonsterSkillInfo(char* Name, int skillId, int& act, int& loopType) // line 2575 (Session2.cpp)
{
	return (this->*_GetMonsterSkillInfo)(Name, skillId, act, loopType);

	//TODO
}


hook_method<char* (CSession::*)(int accId)> CSession::_GetPetAccActName(SAKEXE, "CSession::GetPetAccActName");
char* CSession::GetPetAccActName(int accId) // line 2851 (Session2.cpp)
{
	return (this->*_GetPetAccActName)(accId);

	//TODO
}


hook_method<int (CSession::*)(int Hunger)> CSession::_GetPetHungryState(SAKEXE, "CSession::GetPetHungryState");
int CSession::GetPetHungryState(int Hunger) // line 3002 (Session2.cpp)
{
	return (this->*_GetPetHungryState)(Hunger);

	if( Hunger > 90 && Hunger <= 100 ) return 4;
	if( Hunger > 75 && Hunger <= 90 )  return 3;
	if( Hunger > 25 && Hunger <= 75 )  return 2;
	if( Hunger > 10 && Hunger <= 25 )  return 1;
	                                   return 0;
}


hook_method<int (CSession::*)(int Friendly)> CSession::_GetPetFriendlyState(SAKEXE, "CSession::GetPetFriendlyState");
int CSession::GetPetFriendlyState(int Friendly) // line 3022 (Session2.cpp)
{
	return (this->*_GetPetFriendlyState)(Friendly);

	if( Friendly != 0 )
		Friendly = Friendly / 10;
	if( Friendly > 90 && Friendly <= 100 ) return 4;
	if( Friendly > 75 && Friendly <= 90 )  return 3;
	if( Friendly > 25 && Friendly <= 75 )  return 2;
	if( Friendly > 10 && Friendly <= 25 )  return 1;
	                                       return 0;
}


hook_method<int (CSession::*)(int job, int act, int hungry)> CSession::_GetPetTalkNumber(SAKEXE, "CSession::GetPetTalkNumber");
int CSession::GetPetTalkNumber(int job, int act, int hungry) // line 3129 (Session2.cpp)
{
	return (this->*_GetPetTalkNumber)(job, act, hungry);

	return 100 * job + 10 * act + hungry + ( this->CSession::GetSex() == SEX_MALE ? 50000 : 90000 ) - 100000;
}


hook_method<void (CSession::*)(unsigned long AID, unsigned long tick)> CSession::_SetForceAnimEndTick(SAKEXE, "CSession::SetForceAnimEndTick");
void CSession::SetForceAnimEndTick(unsigned long AID, unsigned long tick) // line 3329 (Session2.cpp)
{
	return (this->*_SetForceAnimEndTick)(AID, tick);

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_IsEFST_TrickDead(SAKEXE, "CSession::IsEFST_TrickDead");
int CSession::IsEFST_TrickDead(void) // line 3175-3183 (Session2.cpp)
{
	return (this->*_IsEFST_TrickDead)();

	//TODO
}


hook_method<int (CSession::*)(void)> CSession::_IsEFST_Berserk(SAKEXE, "CSession::IsEFST_Berserk");
int CSession::IsEFST_Berserk(void) // line 3186-3192 (Session2.cpp)
{
	return (this->*_IsEFST_Berserk)();

	//TODO
}


////////////////////////////////////////


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateNothing(SAKEXE, "IsEffectStateNothing");
bool __cdecl IsEffectStateNothing(unsigned long effectState) // line 7136
{
	return (_IsEffectStateNothing)(effectState);

	return effectState == 0;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateSight(SAKEXE, "IsEffectStateSight");
bool __cdecl IsEffectStateSight(unsigned long effectState) // line 7137
{
	return (_IsEffectStateSight)(effectState);

	return effectState & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateRuwach(SAKEXE, "IsEffectStateRuwach");
bool __cdecl IsEffectStateRuwach(unsigned long effectState) // line 7138
{
	return (_IsEffectStateRuwach)(effectState);

	return (effectState >> 13) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateBurrow(SAKEXE, "IsEffectStateBurrow");
bool __cdecl IsEffectStateBurrow(unsigned long effectState) // line 7139
{
	return (_IsEffectStateBurrow)(effectState);

	return (effectState >> 1) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateHiding(SAKEXE, "IsEffectStateHiding");
bool __cdecl IsEffectStateHiding(unsigned long effectState) // line 7140
{
	return (_IsEffectStateHiding)(effectState);

	return (effectState >> 2) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStatePushCart(SAKEXE, "IsEffectStatePushCart");
bool __cdecl IsEffectStatePushCart(unsigned long effectState) // line 7142
{
	return (_IsEffectStatePushCart)(effectState);

	return( (effectState >> 3) & 1
	     || (effectState >> 7) & 1
	     || (effectState >> 8) & 1
	     || (effectState >> 9) & 1
	     || (effectState >> 10) & 1 );
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateBird(SAKEXE, "IsEffectStateBird");
bool __cdecl IsEffectStateBird(unsigned long effectState) // line 7160
{
	return (_IsEffectStateBird)(effectState);

	return (effectState >> 4) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateChicken(SAKEXE, "IsEffectStateChicken");
bool __cdecl IsEffectStateChicken(unsigned long effectState) // line 7161
{
	return (_IsEffectStateChicken)(effectState);

	return (effectState >> 5) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateSpecialHiding(SAKEXE, "IsEffectStateSpecialHiding");
bool __cdecl IsEffectStateSpecialHiding(unsigned long effectState) // line 7162
{
	return (_IsEffectStateSpecialHiding)(effectState);

	return (effectState >> 6) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateOrcFace(SAKEXE, "IsEffectStateOrcFace");
bool __cdecl IsEffectStateOrcFace(unsigned long effectState) // line 7163
{
	return (_IsEffectStateOrcFace)(effectState);

	return (effectState >> 11) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateMarried(SAKEXE, "IsEffectStateMarried");
bool __cdecl IsEffectStateMarried(unsigned long effectState) // line 7164
{
	return (_IsEffectStateMarried)(effectState);

	return (effectState >> 12) & 1;
}


hook_func<bool (__cdecl *)(unsigned long effectState)> _IsEffectStateFootPrint(SAKEXE, "IsEffectStateFootPrint");
bool __cdecl IsEffectStateFootPrint(unsigned long effectState) // line 7165
{
	return (_IsEffectStateFootPrint)(effectState);

	return (effectState >> 14) & 1;
}


hook_func<bool (__cdecl *)(unsigned int effectState, unsigned int oldEffectState)> _IsEffectStateSightChanged(SAKEXE, "IsEffectStateSightChanged");
bool __cdecl IsEffectStateSightChanged(unsigned int effectState, unsigned int oldEffectState) // line 7167
{
	return (_IsEffectStateSightChanged)(effectState, oldEffectState);

	return (effectState ^ oldEffectState) & 1;
}


hook_func<bool (__cdecl *)(unsigned int effectState, unsigned int oldEffectState)> _IsEffectStateRuwachChanged(SAKEXE, "IsEffectStateRuwachChanged");
bool __cdecl IsEffectStateRuwachChanged(unsigned int effectState, unsigned int oldEffectState) // line 7168
{
	return (_IsEffectStateRuwachChanged)(effectState, oldEffectState);

	return ((oldEffectState >> 13) ^ (effectState >> 13)) & 1;
}


hook_func<bool (__cdecl *)(unsigned int effectState, unsigned int oldEffectState)> _IsEffectStateBurrowChanged(SAKEXE, "IsEffectStateBurrowChanged");
bool __cdecl IsEffectStateBurrowChanged(unsigned int effectState, unsigned int oldEffectState) // line 7169
{
	return (_IsEffectStateBurrowChanged)(effectState, oldEffectState);

	return ((oldEffectState >> 1) ^ (effectState >> 1)) & 1;
}


hook_func<bool (__cdecl *)(unsigned int effectState, unsigned int oldEffectState)> _IsEffectStateHidingChanged(SAKEXE, "IsEffectStateHidingChanged");
bool __cdecl IsEffectStateHidingChanged(unsigned int effectState, unsigned int oldEffectState) // line 7170
{
	return (_IsEffectStateHidingChanged)(effectState, oldEffectState);

	return ((oldEffectState >> 2) ^ (effectState >> 2)) & 1;
}


hook_func<bool (__cdecl *)(unsigned int effectState, unsigned int oldEffectState)> _IsEffectStatePushCartChanged(SAKEXE, "IsEffectStatePushCartChanged");
bool __cdecl IsEffectStatePushCartChanged(unsigned int effectState, unsigned int oldEffectState) // line 7172
{
	return (_IsEffectStatePushCartChanged)(effectState, oldEffectState);
	
	if( effectState == oldEffectState )
		return false;
	return( ((oldEffectState >> 3) ^ (effectState >> 3)) & 1
	     || ((oldEffectState >> 7) ^ (effectState >> 7)) & 1
	     || ((oldEffectState >> 8) ^ (effectState >> 8)) & 1
	     || ((oldEffectState >> 9) ^ (effectState >> 9)) & 1
	     || ((oldEffectState >> 10) ^ (effectState >> 10)) & 1 );
}


hook_func<bool (__cdecl *)(unsigned int effectState, unsigned int oldEffectState)> _IsEffectStateBirdChanged(SAKEXE, "IsEffectStateBirdChanged");
bool __cdecl IsEffectStateBirdChanged(unsigned int effectState, unsigned int oldEffectState) // line 7196
{
	return (_IsEffectStateBirdChanged)(effectState, oldEffectState);

	return ((oldEffectState >> 4) ^ (effectState >> 4)) & 1;
}


hook_func<bool (__cdecl *)(unsigned int effectState, unsigned int oldEffectState)> _IsEffectStateChickenChanged(SAKEXE, "IsEffectStateChickenChanged");
bool __cdecl IsEffectStateChickenChanged(unsigned int effectState, unsigned int oldEffectState) // line 7197
{
	return (_IsEffectStateChickenChanged)(effectState, oldEffectState);

	return ((oldEffectState >> 5) ^ (effectState >> 5)) & 1;
}


hook_func<bool (__cdecl *)(unsigned int effectState, unsigned int oldEffectState)> _IsEffectStateSpecialHidingChanged(SAKEXE, "IsEffectStateSpecialHidingChanged");
bool __cdecl IsEffectStateSpecialHidingChanged(unsigned int effectState, unsigned int oldEffectState) // line 7198
{
	return (_IsEffectStateSpecialHidingChanged)(effectState, oldEffectState);

	return ((oldEffectState >> 6) ^ (effectState >> 6)) & 1;
}


hook_func<bool (__cdecl *)(unsigned int effectState, unsigned int oldEffectState)> _IsEffectStateOrcFaceChanged(SAKEXE, "IsEffectStateOrcFaceChanged");
bool __cdecl IsEffectStateOrcFaceChanged(unsigned int effectState, unsigned int oldEffectState) // line 7199
{
	return (_IsEffectStateOrcFaceChanged)(effectState, oldEffectState);

	return ((oldEffectState >> 11) ^ (effectState >> 11)) & 1;
}


hook_func<void (__cdecl *)(unsigned long* effectState)> _SetEffectStateSpecialHiding(SAKEXE, "SetEffectStateSpecialHiding");
void __cdecl SetEffectStateSpecialHiding(unsigned long* effectState) // line 7201
{
	return (_SetEffectStateSpecialHiding)(effectState);

	*effectState |= (1 << 6);
}


hook_func<void (__cdecl *)(unsigned long* effectState)> _ClearEffectStateSpecialHiding(SAKEXE, "ClearEffectStateSpecialHiding");
void __cdecl ClearEffectStateSpecialHiding(unsigned long* effectState) // line 7203
{
	return (_ClearEffectStateSpecialHiding)(effectState);

	*effectState &= ~(1 << 6);
}


////////////////////////////////////////
