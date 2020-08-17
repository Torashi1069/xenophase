#pragma once


enum ServiceType
{
	ServiceKorea      = 0,
	ServiceAmerica    = 1,
	ServiceJapan      = 2,
	ServiceChina      = 3,
	ServiceTaiwan     = 4,
	ServiceThai       = 5,
	ServiceIndonesia  = 6,
	ServicePhilippine = 7,
	ServiceMalaysia   = 8,
	ServiceSingapore  = 9,
	ServiceGermany    = 10,
	ServiceIndia      = 11,
	ServiceBrazil     = 12,
	ServiceAustralia  = 13,
	ServiceRussia     = 14,
	ServiceVietnam    = 15,
	ServiceIndoor     = 16,
	ServiceChile      = 17,
	ServiceFrance     = 18,
	ServiceArabic     = 19,
	ServiceLast       = 20,
};


enum ServerType
{
	ServerPrimary      = 0,
	ServerSakray       = 1,
	ServerLocal        = 2,
	ServerInstantEvent = 3,
	ServerPVP          = 4,
	ServerPK           = 5,
	//TODO
};


enum ClientType
{
	CLIENTTYPE_KOREAN            = 0,
	CLIENTTYPE_ENGLISH           = 1,
	CLIENTTYPE_SAKRAY            = 2,
	CLIENTTYPE_JAPAN             = 3,
	CLIENTTYPE_CHINA             = 4,
	CLIENTTYPE_TAIWAN            = 5,
	CLIENTTYPE_HONGKONG          = 6,
	CLIENTTYPE_THAI              = 7,
	CLIENTTYPE_LOCAL             = 8,
	CLIENTTYPE_JAPAN_SAKRAY      = 9,
	CLIENTTYPE_THAI_SAKRAY       = 10,
	CLIENTTYPE_TAIWAN_SAKRAY     = 11,
	CLIENTTYPE_INDONESIA         = 12,
	CLIENTTYPE_INDONESIA_SAKRAY  = 13,
	CLIENTTYPE_ENGLISH_SAKRAY    = 14,
	CLIENTTYPE_PHILIPPINE        = 15,
	CLIENTTYPE_MALAYSIA          = 16,
	CLIENTTYPE_SINGAPORE         = 17,
	CLIENTTYPE_PHILIPPINE_SAKRAY = 18,
	CLIENTTYPE_THAI_FREE         = 19,
	CLIENTTYPE_GERMANY           = 20,
	CLIENTTYPE_INDIA             = 21,
	CLIENTTYPE_BRAZIL            = 22,
	CLIENTTYPE_AUSTRALIA         = 23,
	CLIENTTYPE_KOREAN_PK         = 24,
	CLIENTTYPE_RUSSIA            = 25,
	CLIENTTYPE_VIETNAM           = 26,
	CLIENTTYPE_PHILIPPINE_PK     = 27,
	CLIENTTYPE_JAPAN_PK          = 28,
	CLIENTTYPE_THAI_PK           = 29,
	CLIENTTYPE_CHILE             = 30,
	CLIENTTYPE_FRANCE            = 31,
	CLIENTTYPE_VIETNAM_PK        = 32,
	CLIENTTYPE_VIETNAM_SAKRAY    = 33,
	CLIENTTYPE_INDONESIA_PK      = 34,
	CLIENTTYPE_UAE               = 35,
	MAX_CLIENTTYPE               = 36,
};


enum LanguageType
{
	LanguageKorean             = 0,
	LanguageEnglish            = 1,
	LanguageJapanese           = 2,
	LanguageSimplifiedChinese  = 3,
	LanguageTraditionalChinese = 4,
	LanguageThai               = 5,
	LanguagePortuguese         = 6,
	LanguageVietnam            = 7,
	LanguageArabic             = 11,
};


enum TALKTYPE
{
};


enum PixelFormat
{
	PF_A1R5G5B5    = 0,
	PF_A4R4G4B4    = 1,
	PF_R5G6B5      = 2,
	PF_R5G5B5      = 3,
	PF_A8R8G8B8    = 4,
	PF_BUMP        = 5,
	PF_LAST        = 6,
	PF_UNSUPPORTED = -1,
};


enum JOBTYPE
{
	JT_NOVICE           = 0,
	//...
	JT_USER_LAST        = 28,
	JT_WARPNPC          = 45,
	//...
	JT_MON_BEGIN        = 1000,
	//...
	JT_ARCHER_GUARDIAN  = 1285,
	JT_KNIGHT_GUARDIAN  = 1286,
	JT_SOLDIER_GUARDIAN = 1287,
	//...
	JT_EL_AGNI_S        = 2114,
	//...
	JT_EL_TERA_L        = 2125,
	//...
	JT_2004_JOB_BEGIN   = 4000,
	//...
	JT_NOVICE_B         = 4023,
	//...
	JT_THIEF_B          = 4029,
	JT_KNIGHT_B         = 4030,
	//...
	JT_CHICKEN2_B       = 4044,
	JT_SUPERNOVICE_B    = 4045,
	JT_TAEKWON          = 4046,
	JT_STAR             = 4047,
	JT_STAR2            = 4048,
	JT_LINKER           = 4049,
	//...
	JT_RUNE_KNIGHT_B    = 4096,
	//...
	JT_SHADOW_CHASER_B  = 4108,
	//...
	JT_MADOGEAR_B       = 4112,
	JT_THIRDJOB_END     = 4113,
	//...
	JT_MER_BEGIN        = 6000,
	//...
	JT_MER_ARCHER01     = 6017,
	//...
	JT_MER_LAST         = 6053,
};


/// @see CRenderObject::m_stateId
/// @custom
enum StateId
{
	STATEID_STAND = 0,
	STATEID_WALK = 1,
	STATEID_ATTACK = 2,
	STATEID_DEAD = 3,
	STATEID_FLINCH = 4,
	STATEID_PICKUP = 5,
	STATEID_SIT = 6,
	STATEID_CASTEND = 7,
	STATEID_CAST = 8,
	STATEID_MULTIATTACK = 9,
//	STATEID_10 = 10,
	STATEID_11 = 11,
	STATEID_12 = 12,
	STATEID_COUNTER = 13,
//	STATEID_14 = 14,
//	STATEID_15 = 15,
	STATEID_DANCE = 16,
	STATEID_SONG = 17,
	STATEID_18 = 18,
};


enum ENUM_SKILL_USE_TYPE
{
	SUT_NOSKILL      = 0,
	SUT_TO_GROUND    = 1,
	SUT_TO_CHARACTER = 2,
	SUT_TO_ITEM      = 3,
	SUT_TO_ALL       = 4,
	SUT_TO_SKILL     = 5,
	SUT_TO_SKILLGROUND_WITHTALKBOX = 6,
};


/// @see PACKET_ZC_NOTIFY::action
enum ACTIONTYPE
{
	ACTION_ATTACK                   = 0,
	ACTION_ITEMPICKUP               = 1,
	ACTION_SIT                      = 2,
	ACTION_STAND                    = 3,
	ACTION_ATTACK_NOMOTION          = 4,
	ACTION_SPLASH                   = 5,
	ACTION_SKILL                    = 6,
	ACTION_ATTACK_REPEAT            = 7,
	ACTION_ATTACK_MULTIPLE          = 8,
	ACTION_ATTACK_MULTIPLE_NOMOTION = 9,
	ACTION_ATTACK_CRITICAL          = 10,
	ACTION_ATTACK_LUCKY             = 11,
	ACTION_TOUCHSKILL               = 12,
};


enum SEX_TYPE
{
	SEX_FEMALE = 0,
	SEX_MALE = 1,
};


/// @see Zone's CClient::GetType()
enum eObjectType
{
	PC_TYPE         = 0,
	NPC_TYPE        = 1,
	ITEM_TYPE       = 2,
	SKILL_TYPE      = 3,
	UNKNOWN_TYPE    = 4,
	NPC_MOB_TYPE    = 5,
	NPC_EVT_TYPE    = 6,
	NPC_PET_TYPE    = 7,
	NPC_HO_TYPE     = 8,
	NPC_MERSOL_TYPE = 9,
};


/// @see CGameActor::SendMsg()
enum ACTORMESSAGE
{
	AM_0 = 0,
	AM_3 = 3,
	AM_4 = 4,
	AM_7 = 7,
	AM_11 = 11,
};


enum ITEM_ID
{
	ITEM_10001_PETACC_BAPHO           = 10001,
	ITEM_10002_PETACC_CHONCHON        = 10002,
	ITEM_10003_PETACC_DESERTWOLF      = 10003,
	ITEM_10004_PETACC_DEVIRUCHI       = 10004,
	ITEM_10005_PETACC_DOKEBI          = 10005,
	ITEM_10006_PETACC_ISIS            = 10006,
	ITEM_10007_PETACC_LUNATIC         = 10007,
	ITEM_10008_PETACC_MUNAK           = 10008,
	ITEM_10009_PETACC_ORCWARRIOR      = 10009,
	ITEM_10010_PETACC_PECOPECO        = 10010,
	ITEM_10011_PETACC_PETITE          = 10011,
	ITEM_10012_PETACC_PICKY           = 10012,
	ITEM_10013_PETACC_PORING          = 10013,
	ITEM_10014_PETACC_ROCKER          = 10014,
	ITEM_10015_PETACC_SAVAGEBABE      = 10015,
	ITEM_10016_PETACC_SOHEE           = 10016,
	ITEM_10017_PETACC_SPORE           = 10017,
	ITEM_10018_PETACC_YOYO            = 10018,
	ITEM_10019_PETACC_SMOKIE          = 10019,
	ITEM_10020_PETACC_BONGUN          = 10020,
	ITEM_10021_PETACC_BACSOJIN        = 10021,
	ITEM_10022_PETACC_CIVILSERVANT    = 10022,
	ITEM_10023_PETACC_LEAFCAT         = 10023,
	ITEM_10024_PETACC_LOLIRURI        = 10024,
	ITEM_10025_PETACC_MARIONETTE      = 10025,
	ITEM_10026_PETACC_SHINOBI         = 10026,
	ITEM_10027_PETACC_WHISPER         = 10027,
	ITEM_10028_PETACC_GOBLINLEADER    = 10028,
	ITEM_10029_PETACC_WICKEDNYMPH     = 10029,
	ITEM_10030_PETACC_MIYABININGYO    = 10030,
	ITEM_10031_PETACC_DULLAHAN        = 10031,
	ITEM_10032_PETACC_MEDUSA          = 10032,
	ITEM_10033_PETACC_STONESHOOTER    = 10033,
	ITEM_10034_PETACC_INCUBUS         = 10034,
	ITEM_10035_PETACC_GOLEM           = 10035,
	ITEM_10036_PETACC_NIGHTMARETERROR = 10036,
	ITEM_10037_PETACC_SUCCUBUS        = 10037,
	ITEM_10038_PETACC_IMP             = 10038,
};


enum SKILLID
{
	SKID_KN_BRANDISHSPEAR     = 57,
	SKID_KN_BOWLINGBASH       = 62,
	SKID_NPC_METAMORPHOSIS    = 193,
	SKID_MO_CALLSPIRITS       = 261,
	SKID_MO_STEELBODY         = 268,
	SKID_WE_MALE              = 334,
	SKID_WE_FEMALE            = 335,
	SKID_CH_SOULCOLLECT       = 401,
	SKID_CR_ACIDDEMONSTRATION = 490,
	SKID_MO_KITRANSLATION     = 1015,
	SKID_GC_POISONSMOKE       = 2032,
	SKID_WL_RECOGNIZEDSPELL   = 2206,
	SKID_NC_FLAMELAUNCHER     = 2259,
	SKID_NC_F_SIDESLIDE       = 2264,
	SKID_SC_STARTMARK         = 2284,
	SKID_SC_FEINTBOMB         = 2304,
};
