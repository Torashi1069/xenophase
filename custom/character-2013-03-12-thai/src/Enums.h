#pragma once


enum enumSERVERTYPE
{
	SERVERTYPE_NONE             = 0,
	SERVERTYPE_ACCOUNT          = 1,
	SERVERTYPE_CHARACTER        = 2,
	SERVERTYPE_ZONE             = 3,
	SERVERTYPE_INTER            = 4,
	SERVERTYPE_NPC              = 5,
	SERVERTYPE_ENGLISHCHARACTER = 6,
	SERVERTYPE_MONITOR          = 7,
	SERVERTYPE_BILLING          = 8,
	SERVERTYPE_GUM              = 9,
};


enum enumCLIENTTYPE
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


enum enumDISCONNECTEDTYPE
{
	NORMAL_DISCONNECT = 0,
	MOVE_SERVER       = 1,
	RESTART_HSERVER   = 2,
	HZMOVE            = 3,
	HAMOVE            = 4,
};


/*
enum enumHEADTYPE
{
Data           :   constant 0 int HEADTYPE_SAMEASJOB;
Data           :   constant 1 int HEADTYPE_NOVICE;
Data           :   constant 2 int HEADTYPE_SWORDMAN;
Data           :   constant 3 int HEADTYPE_MAGICIAN;
Data           :   constant 4 int HEADTYPE_ARCHER;
Data           :   constant 5 int HEADTYPE_ACOLYTE;
Data           :   constant 6 int HEADTYPE_MERCHANT;
Data           :   constant 7 int HEADTYPE_THIEF;
Data           :   constant 8 int HEADTYPE_ADD1;
Data           :   constant 9 int HEADTYPE_ADD2;
Data           :   constant 10 int HEADTYPE_ADD3;
Data           :   constant 11 int HEADTYPE_ADD4;
Data           :   constant 12 int HEADTYPE_ADD5;
Data           :   constant 13 int HEADTYPE_ADD6;
Data           :   constant 14 int HEADTYPE_ADD7;
Data           :   constant 15 int HEADTYPE_ADD8;
Data           :   constant 16 int HEADTYPE_ADD9;
Data           :   constant 17 int HEADTYPE_ADD10;
Data           :   constant 18 int HEADTYPE_ADD11;
Data           :   constant 19 int HEADTYPE_ADD12;
Data           :   constant 20 int HEADTYPE_ADD13;
Data           :   constant 21 int HEADTYPE_ADD14;
Data           :   constant 22 int HEADTYPE_ADD15;
Data           :   constant 23 int HEADTYPE_ADD16;
Data           :   constant 24 int HEADTYPE_ADD17;
Data           :   constant 25 int HEADTYPE_ADD18;
Data           :   constant 26 int HEADTYPE_ADD19;
Data           :   constant 27 int HEADTYPE_ADD20;
Data           :   constant 28 int HEADTYPE_ADD21;
Data           :   constant 29 int HEADTYPE_ADD22;
Data           :   constant 100 int HEADTYPE_LAST;
};
*/


/*
enum enumLOCATION
{
Data           :   constant 0 int LOCATION_NOTHING;
Data           :   constant 1 int LOCATION_HEAD;
Data           :   constant 16 int LOCATION_BODY;
Data           :   constant 32 int LOCATION_LARM;
Data           :   constant 2 int LOCATION_RARM;
Data           :   constant 4 int LOCATION_ROBE;
Data           :   constant 64 int LOCATION_SHOES;
Data           :   constant 8 int LOCATION_ACCESSORY1;
Data           :   constant 128 int LOCATION_ACCESSORY2;
Data           :   constant 256 int LOCATION_HEAD2;
Data           :   constant 512 int LOCATION_HEAD3;
Data           :   constant 32768 int LOCATION_ARROW;
Data           :   constant 1024 int LOCATION_COSTUME_HEAD2;
Data           :   constant 2048 int LOCATION_COSTUME_HEAD3;
Data           :   constant 4096 int LOCATION_COSTUME_HEAD;
Data           :   constant 8192 int LOCATION_COSTUME_ROBE;
Data           :   constant 16384 int LOCATION_COSTUME_FLOOR;
Data           :   constant 65536 int LOCATION_ARMOR_SHADOW;
Data           :   constant 131072 int LOCATION_WEAPON_SHADOW;
Data           :   constant 262144 int LOCATION_SHIELD_SHADOW;
Data           :   constant 524288 int LOCATION_SHOES_SHADOW;
Data           :   constant 1048576 int LOCATION_R_ACCESSORY_SHADOW;
Data           :   constant 2097152 int LOCATION_L_ACCESSORY_SHADOW;
Data           :   constant 257 int LOCATION_HEAD_TB;
Data           :   constant 768 int LOCATION_HEAD_TM;
Data           :   constant 513 int LOCATION_HEAD_MB;
Data           :   constant 769 int LOCATION_HEAD_TMB;
Data           :   constant 5120 int LOCATION_COSTUME_HEAD_TB;
Data           :   constant 3072 int LOCATION_COSTUME_HEAD_TM;
Data           :   constant 6144 int LOCATION_COSTUME_HEAD_MB;
Data           :   constant 7168 int LOCATION_COSTUME_HEAD_TMB;
Data           :   constant 65535 int LOCATION_LAST;
};
*/


/*
enum enumPROPERTY
{
Data           :   constant 0 int PROPERTY_NOTHING;
Data           :   constant 1 int PROPERTY_WATER;
Data           :   constant 2 int PROPERTY_GROUND;
Data           :   constant 3 int PROPERTY_FIRE;
Data           :   constant 4 int PROPERTY_WIND;
Data           :   constant 5 int PROPERTY_POISON;
Data           :   constant 6 int PROPERTY_SAINT;
Data           :   constant 7 int PROPERTY_DARKNESS;
Data           :   constant 8 int PROPERTY_TELEKINESIS;
Data           :   constant 9 int PROPERTY_UNDEAD;
Data           :   constant 20 int PROPERTY_NOTHING1;
Data           :   constant 21 int PROPERTY_WATER1;
Data           :   constant 22 int PROPERTY_GROUND1;
Data           :   constant 23 int PROPERTY_FIRE1;
Data           :   constant 24 int PROPERTY_WIND1;
Data           :   constant 25 int PROPERTY_POISON1;
Data           :   constant 26 int PROPERTY_SAINT1;
Data           :   constant 27 int PROPERTY_DARKNESS1;
Data           :   constant 28 int PROPERTY_TELEKINESIS1;
Data           :   constant 29 int PROPERTY_UNDEAD1;
Data           :   constant 40 int PROPERTY_NOTHING2;
Data           :   constant 41 int PROPERTY_WATER2;
Data           :   constant 42 int PROPERTY_GROUND2;
Data           :   constant 43 int PROPERTY_FIRE2;
Data           :   constant 44 int PROPERTY_WIND2;
Data           :   constant 45 int PROPERTY_POISON2;
Data           :   constant 46 int PROPERTY_SAINT2;
Data           :   constant 47 int PROPERTY_DARKNESS2;
Data           :   constant 48 int PROPERTY_TELEKINESIS2;
Data           :   constant 49 int PROPERTY_UNDEAD2;
Data           :   constant 60 int PROPERTY_NOTHING3;
Data           :   constant 61 int PROPERTY_WATER3;
Data           :   constant 62 int PROPERTY_GROUND3;
Data           :   constant 63 int PROPERTY_FIRE3;
Data           :   constant 64 int PROPERTY_WIND3;
Data           :   constant 65 int PROPERTY_POISON3;
Data           :   constant 66 int PROPERTY_SAINT3;
Data           :   constant 67 int PROPERTY_DARKNESS3;
Data           :   constant 68 int PROPERTY_TELEKINESIS3;
Data           :   constant 69 int PROPERTY_UNDEAD3;
Data           :   constant 80 int PROPERTY_NOTHING4;
Data           :   constant 81 int PROPERTY_WATER4;
Data           :   constant 82 int PROPERTY_GROUND4;
Data           :   constant 83 int PROPERTY_FIRE4;
Data           :   constant 84 int PROPERTY_WIND4;
Data           :   constant 85 int PROPERTY_POISON4;
Data           :   constant 86 int PROPERTY_SAINT4;
Data           :   constant 87 int PROPERTY_DARKNESS4;
Data           :   constant 88 int PROPERTY_TELEKINESIS4;
Data           :   constant 89 int PROPERTY_UNDEAD4;
Data           :   constant 90 int PROPERTY_LAST;
};
*/


enum enumBANTYPE
{
	BAN_UNFAIR                               = 0,
	BAN_SERVER_SHUTDOWN                      = 1,
	BAN_ANOTHER_LOGIN                        = 2,
	BAN_DETECTED_SPEEDHACK                   = 3,
	BAN_PC_OVERFLOW                          = 4,
	BAN_UNDER_AGE                            = 5,
	BAN_NOT_SETTLED                          = 6,
	BAN_ACCOUNT_BUSY                         = 7,
	BAN_INFORMATION_REMAINED                 = 8,
	BAN_IP_OVERFLOW                          = 9,
	BAN_PAY_OUT                              = 10,
	BAN_PAY_SUSPEND                          = 11,
	BAN_PAY_CHANGE                           = 12,
	BAN_PAY_WRONGIP                          = 13,
	BAN_PAY_PNGAMEROOM                       = 14,
	BAN_OP_FORCE                             = 15,
	BAN_JAPAN_REFUSE1                        = 16,
	BAN_JAPAN_REFUSE2                        = 17,
	BAN_INFORMATION_REMAINED_ANOTHER_ACCOUNT = 18,
	BAN_PC_IP_UNFAIR                         = 100,
	BAN_PC_IP_COUNT_ALL                      = 101,
	BAN_PC_IP_COUNT                          = 102,
	BAN_GRAVITY_MEM_AGREE                    = 103,
	BAN_GAME_MEM_AGREE                       = 104,
	BAN_HAN_VALID                            = 105,
	BAN_PC_IP_LIMIT_ACCESS                   = 106,
	BAN_OVER_CHARACTER_LIST                  = 107,
	BAN_IP_BLOCK                             = 108,
	BAN_INVALID_PWD_CNT                      = 109,
	BAN_NOT_ALLOWED_JOBCLASS                 = 110,
	BAN_MAX_CONNECT_USER_COUNT               = 111,
	BAN_INVALID_SECOND_PWD                   = 112,
	BAN_SHUTDOWN_TEENAGER                    = 113,
	BAN_BILLING_SERVER_ERROR                 = 114,
	BAN_PLANNED_TIME_SHUTDOWN                = 115,
	BAN_END                                  = 255,
};


enum enumSEXTYPE
{
	SEX_FEMALE = 0,
	SEX_MALE   = 1,
};


enum enumMAPTYPE
{
	MAPTYPE_VILLAGE               = 0,
	MAPTYPE_VILLAGE_IN            = 1,
	MAPTYPE_FIELD                 = 2,
	MAPTYPE_DUNGEON               = 3,
	MAPTYPE_ARENA                 = 4,
	MAPTYPE_PENALTY_FREEPKZONE    = 5,
	MAPTYPE_NOPENALTY_FREEPKZONE  = 6,
	MAPTYPE_EVENT_GUILDWAR        = 7,
	MAPTYPE_AGIT                  = 8,
	MAPTYPE_DUNGEON2              = 9,
	MAPTYPE_DUNGEON3              = 10,
	MAPTYPE_PKSERVER              = 11,
	MAPTYPE_PVPSERVER             = 12,
	MAPTYPE_DENYSKILL             = 13,
	MAPTYPE_TURBOTRACK            = 14,
	MAPTYPE_JAIL                  = 15,
	MAPTYPE_MONSTERTRACK          = 16,
	MAPTYPE_PORINGBATTLE          = 17,
	MAPTYPE_AGIT_SIEGEV15         = 18,
	MAPTYPE_BATTLEFIELD           = 19,
	MAPTYPE_PVP_TOURNAMENT        = 20,
	MAPTYPE_SIEGE_LOWLEVEL        = 25,
	MAPTYPE_2012_RWC_BATTLE_FIELD = 26,
	MAPTYPE_UNUSED                = 29,
	MAPTYPE_LAST                  = 30,
};


/*
enum enumSKILLID
{
Data           :   constant 1 int SKID_NV_BASIC;
Data           :   constant 2 int SKID_SM_SWORD;
Data           :   constant 3 int SKID_SM_TWOHAND;
Data           :   constant 4 int SKID_SM_RECOVERY;
Data           :   constant 5 int SKID_SM_BASH;
Data           :   constant 6 int SKID_SM_PROVOKE;
Data           :   constant 7 int SKID_SM_MAGNUM;
Data           :   constant 8 int SKID_SM_ENDURE;
Data           :   constant 9 int SKID_MG_SRECOVERY;
Data           :   constant 10 int SKID_MG_SIGHT;
Data           :   constant 11 int SKID_MG_NAPALMBEAT;
Data           :   constant 12 int SKID_MG_SAFETYWALL;
Data           :   constant 13 int SKID_MG_SOULSTRIKE;
Data           :   constant 14 int SKID_MG_COLDBOLT;
Data           :   constant 15 int SKID_MG_FROSTDIVER;
Data           :   constant 16 int SKID_MG_STONECURSE;
Data           :   constant 17 int SKID_MG_FIREBALL;
Data           :   constant 18 int SKID_MG_FIREWALL;
Data           :   constant 19 int SKID_MG_FIREBOLT;
Data           :   constant 20 int SKID_MG_LIGHTNINGBOLT;
Data           :   constant 21 int SKID_MG_THUNDERSTORM;
Data           :   constant 22 int SKID_AL_DP;
Data           :   constant 23 int SKID_AL_DEMONBANE;
Data           :   constant 24 int SKID_AL_RUWACH;
Data           :   constant 25 int SKID_AL_PNEUMA;
Data           :   constant 26 int SKID_AL_TELEPORT;
Data           :   constant 27 int SKID_AL_WARP;
Data           :   constant 28 int SKID_AL_HEAL;
Data           :   constant 29 int SKID_AL_INCAGI;
Data           :   constant 30 int SKID_AL_DECAGI;
Data           :   constant 31 int SKID_AL_HOLYWATER;
Data           :   constant 32 int SKID_AL_CRUCIS;
Data           :   constant 33 int SKID_AL_ANGELUS;
Data           :   constant 34 int SKID_AL_BLESSING;
Data           :   constant 35 int SKID_AL_CURE;
Data           :   constant 36 int SKID_MC_INCCARRY;
Data           :   constant 37 int SKID_MC_DISCOUNT;
Data           :   constant 38 int SKID_MC_OVERCHARGE;
Data           :   constant 39 int SKID_MC_PUSHCART;
Data           :   constant 40 int SKID_MC_IDENTIFY;
Data           :   constant 41 int SKID_MC_VENDING;
Data           :   constant 42 int SKID_MC_MAMMONITE;
Data           :   constant 43 int SKID_AC_OWL;
Data           :   constant 44 int SKID_AC_VULTURE;
Data           :   constant 45 int SKID_AC_CONCENTRATION;
Data           :   constant 46 int SKID_AC_DOUBLE;
Data           :   constant 47 int SKID_AC_SHOWER;
Data           :   constant 48 int SKID_TF_DOUBLE;
Data           :   constant 49 int SKID_TF_MISS;
Data           :   constant 50 int SKID_TF_STEAL;
Data           :   constant 51 int SKID_TF_HIDING;
Data           :   constant 52 int SKID_TF_POISON;
Data           :   constant 53 int SKID_TF_DETOXIFY;
Data           :   constant 54 int SKID_ALL_RESURRECTION;
Data           :   constant 55 int SKID_KN_SPEARMASTERY;
Data           :   constant 56 int SKID_KN_PIERCE;
Data           :   constant 57 int SKID_KN_BRANDISHSPEAR;
Data           :   constant 58 int SKID_KN_SPEARSTAB;
Data           :   constant 59 int SKID_KN_SPEARBOOMERANG;
Data           :   constant 60 int SKID_KN_TWOHANDQUICKEN;
Data           :   constant 61 int SKID_KN_AUTOCOUNTER;
Data           :   constant 62 int SKID_KN_BOWLINGBASH;
Data           :   constant 63 int SKID_KN_RIDING;
Data           :   constant 64 int SKID_KN_CAVALIERMASTERY;
Data           :   constant 65 int SKID_PR_MACEMASTERY;
Data           :   constant 66 int SKID_PR_IMPOSITIO;
Data           :   constant 67 int SKID_PR_SUFFRAGIUM;
Data           :   constant 68 int SKID_PR_ASPERSIO;
Data           :   constant 69 int SKID_PR_BENEDICTIO;
Data           :   constant 70 int SKID_PR_SANCTUARY;
Data           :   constant 71 int SKID_PR_SLOWPOISON;
Data           :   constant 72 int SKID_PR_STRECOVERY;
Data           :   constant 73 int SKID_PR_KYRIE;
Data           :   constant 74 int SKID_PR_MAGNIFICAT;
Data           :   constant 75 int SKID_PR_GLORIA;
Data           :   constant 76 int SKID_PR_LEXDIVINA;
Data           :   constant 77 int SKID_PR_TURNUNDEAD;
Data           :   constant 78 int SKID_PR_LEXAETERNA;
Data           :   constant 79 int SKID_PR_MAGNUS;
Data           :   constant 80 int SKID_WZ_FIREPILLAR;
Data           :   constant 81 int SKID_WZ_SIGHTRASHER;
Data           :   constant 82 int SKID_WZ_FIREIVY;
Data           :   constant 83 int SKID_WZ_METEOR;
Data           :   constant 84 int SKID_WZ_JUPITEL;
Data           :   constant 85 int SKID_WZ_VERMILION;
Data           :   constant 86 int SKID_WZ_WATERBALL;
Data           :   constant 87 int SKID_WZ_ICEWALL;
Data           :   constant 88 int SKID_WZ_FROSTNOVA;
Data           :   constant 89 int SKID_WZ_STORMGUST;
Data           :   constant 90 int SKID_WZ_EARTHSPIKE;
Data           :   constant 91 int SKID_WZ_HEAVENDRIVE;
Data           :   constant 92 int SKID_WZ_QUAGMIRE;
Data           :   constant 93 int SKID_WZ_ESTIMATION;
Data           :   constant 94 int SKID_BS_IRON;
Data           :   constant 95 int SKID_BS_STEEL;
Data           :   constant 96 int SKID_BS_ENCHANTEDSTONE;
Data           :   constant 97 int SKID_BS_ORIDEOCON;
Data           :   constant 98 int SKID_BS_DAGGER;
Data           :   constant 99 int SKID_BS_SWORD;
Data           :   constant 100 int SKID_BS_TWOHANDSWORD;
Data           :   constant 101 int SKID_BS_AXE;
Data           :   constant 102 int SKID_BS_MACE;
Data           :   constant 103 int SKID_BS_KNUCKLE;
Data           :   constant 104 int SKID_BS_SPEAR;
Data           :   constant 105 int SKID_BS_HILTBINDING;
Data           :   constant 106 int SKID_BS_FINDINGORE;
Data           :   constant 107 int SKID_BS_WEAPONRESEARCH;
Data           :   constant 108 int SKID_BS_REPAIRWEAPON;
Data           :   constant 109 int SKID_BS_SKINTEMPER;
Data           :   constant 110 int SKID_BS_HAMMERFALL;
Data           :   constant 111 int SKID_BS_ADRENALINE;
Data           :   constant 112 int SKID_BS_WEAPONPERFECT;
Data           :   constant 113 int SKID_BS_OVERTHRUST;
Data           :   constant 114 int SKID_BS_MAXIMIZE;
Data           :   constant 115 int SKID_HT_SKIDTRAP;
Data           :   constant 116 int SKID_HT_LANDMINE;
Data           :   constant 117 int SKID_HT_ANKLESNARE;
Data           :   constant 118 int SKID_HT_SHOCKWAVE;
Data           :   constant 119 int SKID_HT_SANDMAN;
Data           :   constant 120 int SKID_HT_FLASHER;
Data           :   constant 121 int SKID_HT_FREEZINGTRAP;
Data           :   constant 122 int SKID_HT_BLASTMINE;
Data           :   constant 123 int SKID_HT_CLAYMORETRAP;
Data           :   constant 124 int SKID_HT_REMOVETRAP;
Data           :   constant 125 int SKID_HT_TALKIEBOX;
Data           :   constant 126 int SKID_HT_BEASTBANE;
Data           :   constant 127 int SKID_HT_FALCON;
Data           :   constant 128 int SKID_HT_STEELCROW;
Data           :   constant 129 int SKID_HT_BLITZBEAT;
Data           :   constant 130 int SKID_HT_DETECTING;
Data           :   constant 131 int SKID_HT_SPRINGTRAP;
Data           :   constant 132 int SKID_AS_RIGHT;
Data           :   constant 133 int SKID_AS_LEFT;
Data           :   constant 134 int SKID_AS_KATAR;
Data           :   constant 135 int SKID_AS_CLOAKING;
Data           :   constant 136 int SKID_AS_SONICBLOW;
Data           :   constant 137 int SKID_AS_GRIMTOOTH;
Data           :   constant 138 int SKID_AS_ENCHANTPOISON;
Data           :   constant 139 int SKID_AS_POISONREACT;
Data           :   constant 140 int SKID_AS_VENOMDUST;
Data           :   constant 141 int SKID_AS_SPLASHER;
Data           :   constant 142 int SKID_NV_FIRSTAID;
Data           :   constant 143 int SKID_NV_TRICKDEAD;
Data           :   constant 144 int SKID_SM_MOVINGRECOVERY;
Data           :   constant 145 int SKID_SM_FATALBLOW;
Data           :   constant 146 int SKID_SM_AUTOBERSERK;
Data           :   constant 147 int SKID_AC_MAKINGARROW;
Data           :   constant 148 int SKID_AC_CHARGEARROW;
Data           :   constant 149 int SKID_TF_SPRINKLESAND;
Data           :   constant 150 int SKID_TF_BACKSLIDING;
Data           :   constant 151 int SKID_TF_PICKSTONE;
Data           :   constant 152 int SKID_TF_THROWSTONE;
Data           :   constant 153 int SKID_MC_CARTREVOLUTION;
Data           :   constant 154 int SKID_MC_CHANGECART;
Data           :   constant 155 int SKID_MC_LOUD;
Data           :   constant 156 int SKID_AL_HOLYLIGHT;
Data           :   constant 157 int SKID_MG_ENERGYCOAT;
Data           :   constant 158 int SKID_NPC_PIERCINGATT;
Data           :   constant 159 int SKID_NPC_MENTALBREAKER;
Data           :   constant 160 int SKID_NPC_RANGEATTACK;
Data           :   constant 161 int SKID_NPC_ATTRICHANGE;
Data           :   constant 162 int SKID_NPC_CHANGEWATER;
Data           :   constant 163 int SKID_NPC_CHANGEGROUND;
Data           :   constant 164 int SKID_NPC_CHANGEFIRE;
Data           :   constant 165 int SKID_NPC_CHANGEWIND;
Data           :   constant 166 int SKID_NPC_CHANGEPOISON;
Data           :   constant 167 int SKID_NPC_CHANGEHOLY;
Data           :   constant 168 int SKID_NPC_CHANGEDARKNESS;
Data           :   constant 169 int SKID_NPC_CHANGETELEKINESIS;
Data           :   constant 170 int SKID_NPC_CRITICALSLASH;
Data           :   constant 171 int SKID_NPC_COMBOATTACK;
Data           :   constant 172 int SKID_NPC_GUIDEDATTACK;
Data           :   constant 173 int SKID_NPC_SELFDESTRUCTION;
Data           :   constant 174 int SKID_NPC_SPLASHATTACK;
Data           :   constant 175 int SKID_NPC_SUICIDE;
Data           :   constant 176 int SKID_NPC_POISON;
Data           :   constant 177 int SKID_NPC_BLINDATTACK;
Data           :   constant 178 int SKID_NPC_SILENCEATTACK;
Data           :   constant 179 int SKID_NPC_STUNATTACK;
Data           :   constant 180 int SKID_NPC_PETRIFYATTACK;
Data           :   constant 181 int SKID_NPC_CURSEATTACK;
Data           :   constant 182 int SKID_NPC_SLEEPATTACK;
Data           :   constant 183 int SKID_NPC_RANDOMATTACK;
Data           :   constant 184 int SKID_NPC_WATERATTACK;
Data           :   constant 185 int SKID_NPC_GROUNDATTACK;
Data           :   constant 186 int SKID_NPC_FIREATTACK;
Data           :   constant 187 int SKID_NPC_WINDATTACK;
Data           :   constant 188 int SKID_NPC_POISONATTACK;
Data           :   constant 189 int SKID_NPC_HOLYATTACK;
Data           :   constant 190 int SKID_NPC_DARKNESSATTACK;
Data           :   constant 191 int SKID_NPC_TELEKINESISATTACK;
Data           :   constant 192 int SKID_NPC_MAGICALATTACK;
Data           :   constant 193 int SKID_NPC_METAMORPHOSIS;
Data           :   constant 194 int SKID_NPC_PROVOCATION;
Data           :   constant 195 int SKID_NPC_SMOKING;
Data           :   constant 196 int SKID_NPC_SUMMONSLAVE;
Data           :   constant 197 int SKID_NPC_EMOTION;
Data           :   constant 198 int SKID_NPC_TRANSFORMATION;
Data           :   constant 199 int SKID_NPC_BLOODDRAIN;
Data           :   constant 200 int SKID_NPC_ENERGYDRAIN;
Data           :   constant 201 int SKID_NPC_KEEPING;
Data           :   constant 202 int SKID_NPC_DARKBREATH;
Data           :   constant 203 int SKID_NPC_DARKBLESSING;
Data           :   constant 204 int SKID_NPC_BARRIER;
Data           :   constant 205 int SKID_NPC_DEFENDER;
Data           :   constant 206 int SKID_NPC_LICK;
Data           :   constant 207 int SKID_NPC_HALLUCINATION;
Data           :   constant 208 int SKID_NPC_REBIRTH;
Data           :   constant 209 int SKID_NPC_SUMMONMONSTER;
Data           :   constant 210 int SKID_RG_SNATCHER;
Data           :   constant 211 int SKID_RG_STEALCOIN;
Data           :   constant 212 int SKID_RG_BACKSTAP;
Data           :   constant 213 int SKID_RG_TUNNELDRIVE;
Data           :   constant 214 int SKID_RG_RAID;
Data           :   constant 215 int SKID_RG_STRIPWEAPON;
Data           :   constant 216 int SKID_RG_STRIPSHIELD;
Data           :   constant 217 int SKID_RG_STRIPARMOR;
Data           :   constant 218 int SKID_RG_STRIPHELM;
Data           :   constant 219 int SKID_RG_INTIMIDATE;
Data           :   constant 220 int SKID_RG_GRAFFITI;
Data           :   constant 221 int SKID_RG_FLAGGRAFFITI;
Data           :   constant 222 int SKID_RG_CLEANER;
Data           :   constant 223 int SKID_RG_GANGSTER;
Data           :   constant 224 int SKID_RG_COMPULSION;
Data           :   constant 225 int SKID_RG_PLAGIARISM;
Data           :   constant 226 int SKID_AM_AXEMASTERY;
Data           :   constant 227 int SKID_AM_LEARNINGPOTION;
Data           :   constant 228 int SKID_AM_PHARMACY;
Data           :   constant 229 int SKID_AM_DEMONSTRATION;
Data           :   constant 230 int SKID_AM_ACIDTERROR;
Data           :   constant 231 int SKID_AM_POTIONPITCHER;
Data           :   constant 232 int SKID_AM_CANNIBALIZE;
Data           :   constant 233 int SKID_AM_SPHEREMINE;
Data           :   constant 234 int SKID_AM_CP_WEAPON;
Data           :   constant 235 int SKID_AM_CP_SHIELD;
Data           :   constant 236 int SKID_AM_CP_ARMOR;
Data           :   constant 237 int SKID_AM_CP_HELM;
Data           :   constant 238 int SKID_AM_BIOETHICS;
Data           :   constant 239 int SKID_AM_BIOTECHNOLOGY;
Data           :   constant 240 int SKID_AM_CREATECREATURE;
Data           :   constant 241 int SKID_AM_CULTIVATION;
Data           :   constant 242 int SKID_AM_FLAMECONTROL;
Data           :   constant 243 int SKID_AM_CALLHOMUN;
Data           :   constant 244 int SKID_AM_REST;
Data           :   constant 245 int SKID_AM_DRILLMASTER;
Data           :   constant 246 int SKID_AM_HEALHOMUN;
Data           :   constant 247 int SKID_AM_RESURRECTHOMUN;
Data           :   constant 248 int SKID_CR_TRUST;
Data           :   constant 249 int SKID_CR_AUTOGUARD;
Data           :   constant 250 int SKID_CR_SHIELDCHARGE;
Data           :   constant 251 int SKID_CR_SHIELDBOOMERANG;
Data           :   constant 252 int SKID_CR_REFLECTSHIELD;
Data           :   constant 253 int SKID_CR_HOLYCROSS;
Data           :   constant 254 int SKID_CR_GRANDCROSS;
Data           :   constant 255 int SKID_CR_DEVOTION;
Data           :   constant 256 int SKID_CR_PROVIDENCE;
Data           :   constant 257 int SKID_CR_DEFENDER;
Data           :   constant 258 int SKID_CR_SPEARQUICKEN;
Data           :   constant 259 int SKID_MO_IRONHAND;
Data           :   constant 260 int SKID_MO_SPIRITSRECOVERY;
Data           :   constant 261 int SKID_MO_CALLSPIRITS;
Data           :   constant 262 int SKID_MO_ABSORBSPIRITS;
Data           :   constant 263 int SKID_MO_TRIPLEATTACK;
Data           :   constant 264 int SKID_MO_BODYRELOCATION;
Data           :   constant 265 int SKID_MO_DODGE;
Data           :   constant 266 int SKID_MO_INVESTIGATE;
Data           :   constant 267 int SKID_MO_FINGEROFFENSIVE;
Data           :   constant 268 int SKID_MO_STEELBODY;
Data           :   constant 269 int SKID_MO_BLADESTOP;
Data           :   constant 270 int SKID_MO_EXPLOSIONSPIRITS;
Data           :   constant 271 int SKID_MO_EXTREMITYFIST;
Data           :   constant 272 int SKID_MO_CHAINCOMBO;
Data           :   constant 273 int SKID_MO_COMBOFINISH;
Data           :   constant 274 int SKID_SA_ADVANCEDBOOK;
Data           :   constant 275 int SKID_SA_CASTCANCEL;
Data           :   constant 276 int SKID_SA_MAGICROD;
Data           :   constant 277 int SKID_SA_SPELLBREAKER;
Data           :   constant 278 int SKID_SA_FREECAST;
Data           :   constant 279 int SKID_SA_AUTOSPELL;
Data           :   constant 280 int SKID_SA_FLAMELAUNCHER;
Data           :   constant 281 int SKID_SA_FROSTWEAPON;
Data           :   constant 282 int SKID_SA_LIGHTNINGLOADER;
Data           :   constant 283 int SKID_SA_SEISMICWEAPON;
Data           :   constant 284 int SKID_SA_DRAGONOLOGY;
Data           :   constant 285 int SKID_SA_VOLCANO;
Data           :   constant 286 int SKID_SA_DELUGE;
Data           :   constant 287 int SKID_SA_VIOLENTGALE;
Data           :   constant 288 int SKID_SA_LANDPROTECTOR;
Data           :   constant 289 int SKID_SA_DISPELL;
Data           :   constant 290 int SKID_SA_ABRACADABRA;
Data           :   constant 291 int SKID_SA_MONOCELL;
Data           :   constant 292 int SKID_SA_CLASSCHANGE;
Data           :   constant 293 int SKID_SA_SUMMONMONSTER;
Data           :   constant 294 int SKID_SA_REVERSEORCISH;
Data           :   constant 295 int SKID_SA_DEATH;
Data           :   constant 296 int SKID_SA_FORTUNE;
Data           :   constant 297 int SKID_SA_TAMINGMONSTER;
Data           :   constant 298 int SKID_SA_QUESTION;
Data           :   constant 299 int SKID_SA_GRAVITY;
Data           :   constant 300 int SKID_SA_LEVELUP;
Data           :   constant 301 int SKID_SA_INSTANTDEATH;
Data           :   constant 302 int SKID_SA_FULLRECOVERY;
Data           :   constant 303 int SKID_SA_COMA;
Data           :   constant 304 int SKID_BD_ADAPTATION;
Data           :   constant 305 int SKID_BD_ENCORE;
Data           :   constant 306 int SKID_BD_LULLABY;
Data           :   constant 307 int SKID_BD_RICHMANKIM;
Data           :   constant 308 int SKID_BD_ETERNALCHAOS;
Data           :   constant 309 int SKID_BD_DRUMBATTLEFIELD;
Data           :   constant 310 int SKID_BD_RINGNIBELUNGEN;
Data           :   constant 311 int SKID_BD_ROKISWEIL;
Data           :   constant 312 int SKID_BD_INTOABYSS;
Data           :   constant 313 int SKID_BD_SIEGFRIED;
Data           :   constant 314 int SKID_BD_RAGNAROK;
Data           :   constant 315 int SKID_BA_MUSICALLESSON;
Data           :   constant 316 int SKID_BA_MUSICALSTRIKE;
Data           :   constant 317 int SKID_BA_DISSONANCE;
Data           :   constant 318 int SKID_BA_FROSTJOKER;
Data           :   constant 319 int SKID_BA_WHISTLE;
Data           :   constant 320 int SKID_BA_ASSASSINCROSS;
Data           :   constant 321 int SKID_BA_POEMBRAGI;
Data           :   constant 322 int SKID_BA_APPLEIDUN;
Data           :   constant 323 int SKID_DC_DANCINGLESSON;
Data           :   constant 324 int SKID_DC_THROWARROW;
Data           :   constant 325 int SKID_DC_UGLYDANCE;
Data           :   constant 326 int SKID_DC_SCREAM;
Data           :   constant 327 int SKID_DC_HUMMING;
Data           :   constant 328 int SKID_DC_DONTFORGETME;
Data           :   constant 329 int SKID_DC_FORTUNEKISS;
Data           :   constant 330 int SKID_DC_SERVICEFORYOU;
Data           :   constant 331 int SKID_NPC_RANDOMMOVE;
Data           :   constant 332 int SKID_NPC_SPEEDUP;
Data           :   constant 333 int SKID_NPC_REVENGE;
Data           :   constant 334 int SKID_WE_MALE;
Data           :   constant 335 int SKID_WE_FEMALE;
Data           :   constant 336 int SKID_WE_CALLPARTNER;
Data           :   constant 337 int SKID_ITM_TOMAHAWK;
Data           :   constant 338 int SKID_NPC_DARKCROSS;
Data           :   constant 339 int SKID_NPC_GRANDDARKNESS;
Data           :   constant 340 int SKID_NPC_DARKSTRIKE;
Data           :   constant 341 int SKID_NPC_DARKTHUNDER;
Data           :   constant 342 int SKID_NPC_STOP;
Data           :   constant 343 int SKID_NPC_WEAPONBRAKER;
Data           :   constant 344 int SKID_NPC_ARMORBRAKE;
Data           :   constant 345 int SKID_NPC_HELMBRAKE;
Data           :   constant 346 int SKID_NPC_SHIELDBRAKE;
Data           :   constant 347 int SKID_NPC_UNDEADATTACK;
Data           :   constant 348 int SKID_NPC_CHANGEUNDEAD;
Data           :   constant 349 int SKID_NPC_POWERUP;
Data           :   constant 350 int SKID_NPC_AGIUP;
Data           :   constant 351 int SKID_NPC_SIEGEMODE;
Data           :   constant 352 int SKID_NPC_CALLSLAVE;
Data           :   constant 353 int SKID_NPC_INVISIBLE;
Data           :   constant 354 int SKID_NPC_RUN;
Data           :   constant 355 int SKID_LK_AURABLADE;
Data           :   constant 356 int SKID_LK_PARRYING;
Data           :   constant 357 int SKID_LK_CONCENTRATION;
Data           :   constant 358 int SKID_LK_TENSIONRELAX;
Data           :   constant 359 int SKID_LK_BERSERK;
Data           :   constant 360 int SKID_LK_FURY;
Data           :   constant 361 int SKID_HP_ASSUMPTIO;
Data           :   constant 362 int SKID_HP_BASILICA;
Data           :   constant 363 int SKID_HP_MEDITATIO;
Data           :   constant 364 int SKID_HW_SOULDRAIN;
Data           :   constant 365 int SKID_HW_MAGICCRASHER;
Data           :   constant 366 int SKID_HW_MAGICPOWER;
Data           :   constant 367 int SKID_PA_PRESSURE;
Data           :   constant 368 int SKID_PA_SACRIFICE;
Data           :   constant 369 int SKID_PA_GOSPEL;
Data           :   constant 370 int SKID_CH_PALMSTRIKE;
Data           :   constant 371 int SKID_CH_TIGERFIST;
Data           :   constant 372 int SKID_CH_CHAINCRUSH;
Data           :   constant 373 int SKID_PF_HPCONVERSION;
Data           :   constant 374 int SKID_PF_SOULCHANGE;
Data           :   constant 375 int SKID_PF_SOULBURN;
Data           :   constant 376 int SKID_ASC_KATAR;
Data           :   constant 377 int SKID_ASC_HALLUCINATION;
Data           :   constant 378 int SKID_ASC_EDP;
Data           :   constant 379 int SKID_ASC_BREAKER;
Data           :   constant 380 int SKID_SN_SIGHT;
Data           :   constant 381 int SKID_SN_FALCONASSAULT;
Data           :   constant 382 int SKID_SN_SHARPSHOOTING;
Data           :   constant 383 int SKID_SN_WINDWALK;
Data           :   constant 384 int SKID_WS_MELTDOWN;
Data           :   constant 385 int SKID_WS_CREATECOIN;
Data           :   constant 386 int SKID_WS_CREATENUGGET;
Data           :   constant 387 int SKID_WS_CARTBOOST;
Data           :   constant 388 int SKID_WS_SYSTEMCREATE;
Data           :   constant 389 int SKID_ST_CHASEWALK;
Data           :   constant 390 int SKID_ST_REJECTSWORD;
Data           :   constant 391 int SKID_ST_STEALBACKPACK;
Data           :   constant 392 int SKID_CR_ALCHEMY;
Data           :   constant 393 int SKID_CR_SYNTHESISPOTION;
Data           :   constant 394 int SKID_CG_ARROWVULCAN;
Data           :   constant 395 int SKID_CG_MOONLIT;
Data           :   constant 396 int SKID_CG_MARIONETTE;
Data           :   constant 397 int SKID_LK_SPIRALPIERCE;
Data           :   constant 398 int SKID_LK_HEADCRUSH;
Data           :   constant 399 int SKID_LK_JOINTBEAT;
Data           :   constant 400 int SKID_HW_NAPALMVULCAN;
Data           :   constant 401 int SKID_CH_SOULCOLLECT;
Data           :   constant 402 int SKID_PF_MINDBREAKER;
Data           :   constant 403 int SKID_PF_MEMORIZE;
Data           :   constant 404 int SKID_PF_FOGWALL;
Data           :   constant 405 int SKID_PF_SPIDERWEB;
Data           :   constant 406 int SKID_ASC_METEORASSAULT;
Data           :   constant 407 int SKID_ASC_CDP;
Data           :   constant 408 int SKID_WE_BABY;
Data           :   constant 409 int SKID_WE_CALLPARENT;
Data           :   constant 410 int SKID_WE_CALLBABY;
Data           :   constant 411 int SKID_TK_RUN;
Data           :   constant 412 int SKID_TK_READYSTORM;
Data           :   constant 413 int SKID_TK_STORMKICK;
Data           :   constant 414 int SKID_TK_READYDOWN;
Data           :   constant 415 int SKID_TK_DOWNKICK;
Data           :   constant 416 int SKID_TK_READYTURN;
Data           :   constant 417 int SKID_TK_TURNKICK;
Data           :   constant 418 int SKID_TK_READYCOUNTER;
Data           :   constant 419 int SKID_TK_COUNTER;
Data           :   constant 420 int SKID_TK_DODGE;
Data           :   constant 421 int SKID_TK_JUMPKICK;
Data           :   constant 422 int SKID_TK_HPTIME;
Data           :   constant 423 int SKID_TK_SPTIME;
Data           :   constant 424 int SKID_TK_POWER;
Data           :   constant 425 int SKID_TK_SEVENWIND;
Data           :   constant 426 int SKID_TK_HIGHJUMP;
Data           :   constant 427 int SKID_SG_FEEL;
Data           :   constant 428 int SKID_SG_SUN_WARM;
Data           :   constant 429 int SKID_SG_MOON_WARM;
Data           :   constant 430 int SKID_SG_STAR_WARM;
Data           :   constant 431 int SKID_SG_SUN_COMFORT;
Data           :   constant 432 int SKID_SG_MOON_COMFORT;
Data           :   constant 433 int SKID_SG_STAR_COMFORT;
Data           :   constant 434 int SKID_SG_HATE;
Data           :   constant 435 int SKID_SG_SUN_ANGER;
Data           :   constant 436 int SKID_SG_MOON_ANGER;
Data           :   constant 437 int SKID_SG_STAR_ANGER;
Data           :   constant 438 int SKID_SG_SUN_BLESS;
Data           :   constant 439 int SKID_SG_MOON_BLESS;
Data           :   constant 440 int SKID_SG_STAR_BLESS;
Data           :   constant 441 int SKID_SG_DEVIL;
Data           :   constant 442 int SKID_SG_FRIEND;
Data           :   constant 443 int SKID_SG_KNOWLEDGE;
Data           :   constant 444 int SKID_SG_FUSION;
Data           :   constant 445 int SKID_SL_ALCHEMIST;
Data           :   constant 446 int SKID_AM_BERSERKPITCHER;
Data           :   constant 447 int SKID_SL_MONK;
Data           :   constant 448 int SKID_SL_STAR;
Data           :   constant 449 int SKID_SL_SAGE;
Data           :   constant 450 int SKID_SL_CRUSADER;
Data           :   constant 451 int SKID_SL_SUPERNOVICE;
Data           :   constant 452 int SKID_SL_KNIGHT;
Data           :   constant 453 int SKID_SL_WIZARD;
Data           :   constant 454 int SKID_SL_PRIEST;
Data           :   constant 455 int SKID_SL_BARDDANCER;
Data           :   constant 456 int SKID_SL_ROGUE;
Data           :   constant 457 int SKID_SL_ASSASIN;
Data           :   constant 458 int SKID_SL_BLACKSMITH;
Data           :   constant 459 int SKID_BS_ADRENALINE2;
Data           :   constant 460 int SKID_SL_HUNTER;
Data           :   constant 461 int SKID_SL_SOULLINKER;
Data           :   constant 462 int SKID_SL_KAIZEL;
Data           :   constant 463 int SKID_SL_KAAHI;
Data           :   constant 464 int SKID_SL_KAUPE;
Data           :   constant 465 int SKID_SL_KAITE;
Data           :   constant 466 int SKID_SL_KAINA;
Data           :   constant 467 int SKID_SL_STIN;
Data           :   constant 468 int SKID_SL_STUN;
Data           :   constant 469 int SKID_SL_SMA;
Data           :   constant 470 int SKID_SL_SWOO;
Data           :   constant 471 int SKID_SL_SKE;
Data           :   constant 472 int SKID_SL_SKA;
Data           :   constant 473 int SKID_SM_SELFPROVOKE;
Data           :   constant 474 int SKID_NPC_EMOTION_ON;
Data           :   constant 475 int SKID_ST_PRESERVE;
Data           :   constant 476 int SKID_ST_FULLSTRIP;
Data           :   constant 477 int SKID_WS_WEAPONREFINE;
Data           :   constant 478 int SKID_CR_SLIMPITCHER;
Data           :   constant 479 int SKID_CR_FULLPROTECTION;
Data           :   constant 480 int SKID_PA_SHIELDCHAIN;
Data           :   constant 481 int SKID_HP_MANARECHARGE;
Data           :   constant 482 int SKID_PF_DOUBLECASTING;
Data           :   constant 483 int SKID_HW_GANBANTEIN;
Data           :   constant 484 int SKID_HW_GRAVITATION;
Data           :   constant 485 int SKID_WS_CARTTERMINATION;
Data           :   constant 486 int SKID_WS_OVERTHRUSTMAX;
Data           :   constant 487 int SKID_CG_LONGINGFREEDOM;
Data           :   constant 488 int SKID_CG_HERMODE;
Data           :   constant 489 int SKID_CG_TAROTCARD;
Data           :   constant 490 int SKID_CR_ACIDDEMONSTRATION;
Data           :   constant 491 int SKID_CR_CULTIVATION;
Data           :   constant 492 int SKID_ITEM_ENCHANTARMS;
Data           :   constant 493 int SKID_TK_MISSION;
Data           :   constant 494 int SKID_SL_HIGH;
Data           :   constant 495 int SKID_KN_ONEHAND;
Data           :   constant 496 int SKID_AM_TWILIGHT1;
Data           :   constant 497 int SKID_AM_TWILIGHT2;
Data           :   constant 498 int SKID_AM_TWILIGHT3;
Data           :   constant 499 int SKID_HT_POWER;
Data           :   constant 500 int SKID_GS_GLITTERING;
Data           :   constant 501 int SKID_GS_FLING;
Data           :   constant 502 int SKID_GS_TRIPLEACTION;
Data           :   constant 503 int SKID_GS_BULLSEYE;
Data           :   constant 504 int SKID_GS_MADNESSCANCEL;
Data           :   constant 505 int SKID_GS_ADJUSTMENT;
Data           :   constant 506 int SKID_GS_INCREASING;
Data           :   constant 507 int SKID_GS_MAGICALBULLET;
Data           :   constant 508 int SKID_GS_CRACKER;
Data           :   constant 509 int SKID_GS_SINGLEACTION;
Data           :   constant 510 int SKID_GS_SNAKEEYE;
Data           :   constant 511 int SKID_GS_CHAINACTION;
Data           :   constant 512 int SKID_GS_TRACKING;
Data           :   constant 513 int SKID_GS_DISARM;
Data           :   constant 514 int SKID_GS_PIERCINGSHOT;
Data           :   constant 515 int SKID_GS_RAPIDSHOWER;
Data           :   constant 516 int SKID_GS_DESPERADO;
Data           :   constant 517 int SKID_GS_GATLINGFEVER;
Data           :   constant 518 int SKID_GS_DUST;
Data           :   constant 519 int SKID_GS_FULLBUSTER;
Data           :   constant 520 int SKID_GS_SPREADATTACK;
Data           :   constant 521 int SKID_GS_GROUNDDRIFT;
Data           :   constant 522 int SKID_NJ_TOBIDOUGU;
Data           :   constant 523 int SKID_NJ_SYURIKEN;
Data           :   constant 524 int SKID_NJ_KUNAI;
Data           :   constant 525 int SKID_NJ_HUUMA;
Data           :   constant 526 int SKID_NJ_ZENYNAGE;
Data           :   constant 527 int SKID_NJ_TATAMIGAESHI;
Data           :   constant 528 int SKID_NJ_KASUMIKIRI;
Data           :   constant 529 int SKID_NJ_SHADOWJUMP;
Data           :   constant 530 int SKID_NJ_KIRIKAGE;
Data           :   constant 531 int SKID_NJ_UTSUSEMI;
Data           :   constant 532 int SKID_NJ_BUNSINJYUTSU;
Data           :   constant 533 int SKID_NJ_NINPOU;
Data           :   constant 534 int SKID_NJ_KOUENKA;
Data           :   constant 535 int SKID_NJ_KAENSIN;
Data           :   constant 536 int SKID_NJ_BAKUENRYU;
Data           :   constant 537 int SKID_NJ_HYOUSENSOU;
Data           :   constant 538 int SKID_NJ_SUITON;
Data           :   constant 539 int SKID_NJ_HYOUSYOURAKU;
Data           :   constant 540 int SKID_NJ_HUUJIN;
Data           :   constant 541 int SKID_NJ_RAIGEKISAI;
Data           :   constant 542 int SKID_NJ_KAMAITACHI;
Data           :   constant 543 int SKID_NJ_NEN;
Data           :   constant 544 int SKID_NJ_ISSEN;
Data           :   constant 545 int SKID_MB_FIGHTING;
Data           :   constant 546 int SKID_MB_NEUTRAL;
Data           :   constant 547 int SKID_MB_TAIMING_PUTI;
Data           :   constant 548 int SKID_MB_WHITEPOTION;
Data           :   constant 549 int SKID_MB_MENTAL;
Data           :   constant 550 int SKID_MB_CARDPITCHER;
Data           :   constant 551 int SKID_MB_PETPITCHER;
Data           :   constant 552 int SKID_MB_BODYSTUDY;
Data           :   constant 553 int SKID_MB_BODYALTER;
Data           :   constant 554 int SKID_MB_PETMEMORY;
Data           :   constant 555 int SKID_MB_M_TELEPORT;
Data           :   constant 556 int SKID_MB_B_GAIN;
Data           :   constant 557 int SKID_MB_M_GAIN;
Data           :   constant 558 int SKID_MB_MISSION;
Data           :   constant 559 int SKID_MB_MUNAKKNOWLEDGE;
Data           :   constant 560 int SKID_MB_MUNAKBALL;
Data           :   constant 561 int SKID_MB_SCROLL;
Data           :   constant 562 int SKID_MB_B_GATHERING;
Data           :   constant 563 int SKID_MB_M_GATHERING;
Data           :   constant 564 int SKID_MB_B_EXCLUDE;
Data           :   constant 565 int SKID_MB_B_DRIFT;
Data           :   constant 566 int SKID_MB_B_WALLRUSH;
Data           :   constant 567 int SKID_MB_M_WALLRUSH;
Data           :   constant 568 int SKID_MB_B_WALLSHIFT;
Data           :   constant 569 int SKID_MB_M_WALLCRASH;
Data           :   constant 570 int SKID_MB_M_REINCARNATION;
Data           :   constant 571 int SKID_MB_B_EQUIP;
Data           :   constant 572 int SKID_SL_DEATHKNIGHT;
Data           :   constant 573 int SKID_SL_COLLECTOR;
Data           :   constant 574 int SKID_SL_NINJA;
Data           :   constant 575 int SKID_SL_GUNNER;
Data           :   constant 576 int SKID_AM_TWILIGHT4;
Data           :   constant 577 int SKID_DA_RESET;
Data           :   constant 578 int SKID_DE_BERSERKAIZER;
Data           :   constant 579 int SKID_DA_DARKPOWER;
Data           :   constant 580 int SKID_DE_PASSIVE;
Data           :   constant 581 int SKID_DE_PATTACK;
Data           :   constant 582 int SKID_DE_PSPEED;
Data           :   constant 583 int SKID_DE_PDEFENSE;
Data           :   constant 584 int SKID_DE_PCRITICAL;
Data           :   constant 585 int SKID_DE_PHP;
Data           :   constant 586 int SKID_DE_PSP;
Data           :   constant 587 int SKID_DE_RESET;
Data           :   constant 588 int SKID_DE_RANKING;
Data           :   constant 589 int SKID_DE_PTRIPLE;
Data           :   constant 590 int SKID_DE_ENERGY;
Data           :   constant 591 int SKID_DE_NIGHTMARE;
Data           :   constant 592 int SKID_DE_SLASH;
Data           :   constant 593 int SKID_DE_COIL;
Data           :   constant 594 int SKID_DE_WAVE;
Data           :   constant 595 int SKID_DE_REBIRTH;
Data           :   constant 596 int SKID_DE_AURA;
Data           :   constant 597 int SKID_DE_FREEZER;
Data           :   constant 598 int SKID_DE_CHANGEATTACK;
Data           :   constant 599 int SKID_DE_PUNISH;
Data           :   constant 600 int SKID_DE_POISON;
Data           :   constant 601 int SKID_DE_INSTANT;
Data           :   constant 602 int SKID_DE_WARNING;
Data           :   constant 603 int SKID_DE_RANKEDKNIFE;
Data           :   constant 604 int SKID_DE_RANKEDGRADIUS;
Data           :   constant 605 int SKID_DE_GAUGE;
Data           :   constant 606 int SKID_DE_GTIME;
Data           :   constant 607 int SKID_DE_GPAIN;
Data           :   constant 608 int SKID_DE_GSKILL;
Data           :   constant 609 int SKID_DE_GKILL;
Data           :   constant 610 int SKID_DE_ACCEL;
Data           :   constant 611 int SKID_DE_BLOCKDOUBLE;
Data           :   constant 612 int SKID_DE_BLOCKMELEE;
Data           :   constant 613 int SKID_DE_BLOCKFAR;
Data           :   constant 614 int SKID_DE_FRONTATTACK;
Data           :   constant 615 int SKID_DE_DANGERATTACK;
Data           :   constant 616 int SKID_DE_TWINATTACK;
Data           :   constant 617 int SKID_DE_WINDATTACK;
Data           :   constant 618 int SKID_DE_WATERATTACK;
Data           :   constant 619 int SKID_DA_ENERGY;
Data           :   constant 620 int SKID_DA_CLOUD;
Data           :   constant 621 int SKID_DA_FIRSTSLOT;
Data           :   constant 622 int SKID_DA_HEADDEF;
Data           :   constant 623 int SKID_DA_SPACE;
Data           :   constant 624 int SKID_DA_TRANSFORM;
Data           :   constant 625 int SKID_DA_EXPLOSION;
Data           :   constant 626 int SKID_DA_REWARD;
Data           :   constant 627 int SKID_DA_CRUSH;
Data           :   constant 628 int SKID_DA_ITEMREBUILD;
Data           :   constant 629 int SKID_DA_ILLUSION;
Data           :   constant 630 int SKID_DA_NUETRALIZE;
Data           :   constant 631 int SKID_DA_RUNNER;
Data           :   constant 632 int SKID_DA_TRANSFER;
Data           :   constant 633 int SKID_DA_WALL;
Data           :   constant 634 int SKID_DA_ZENY;
Data           :   constant 635 int SKID_DA_REVENGE;
Data           :   constant 636 int SKID_DA_EARPLUG;
Data           :   constant 637 int SKID_DA_CONTRACT;
Data           :   constant 638 int SKID_DA_BLACK;
Data           :   constant 639 int SKID_DA_DREAM;
Data           :   constant 640 int SKID_DA_MAGICCART;
Data           :   constant 641 int SKID_DA_COPY;
Data           :   constant 642 int SKID_DA_CRYSTAL;
Data           :   constant 643 int SKID_DA_EXP;
Data           :   constant 644 int SKID_DA_CARTSWING;
Data           :   constant 645 int SKID_DA_REBUILD;
Data           :   constant 646 int SKID_DA_JOBCHANGE;
Data           :   constant 647 int SKID_DA_EDARKNESS;
Data           :   constant 648 int SKID_DA_EGUARDIAN;
Data           :   constant 649 int SKID_DA_TIMEOUT;
Data           :   constant 650 int SKID_ALL_TIMEIN;
Data           :   constant 651 int SKID_DA_ZENYRANK;
Data           :   constant 652 int SKID_DA_ACCESSORYMIX;
Data           :   constant 653 int SKID_NPC_EARTHQUAKE;
Data           :   constant 654 int SKID_NPC_FIREBREATH;
Data           :   constant 655 int SKID_NPC_ICEBREATH;
Data           :   constant 656 int SKID_NPC_THUNDERBREATH;
Data           :   constant 657 int SKID_NPC_ACIDBREATH;
Data           :   constant 658 int SKID_NPC_DARKNESSBREATH;
Data           :   constant 659 int SKID_NPC_DRAGONFEAR;
Data           :   constant 660 int SKID_NPC_BLEEDING;
Data           :   constant 661 int SKID_NPC_PULSESTRIKE;
Data           :   constant 662 int SKID_NPC_HELLJUDGEMENT;
Data           :   constant 663 int SKID_NPC_WIDESILENCE;
Data           :   constant 664 int SKID_NPC_WIDEFREEZE;
Data           :   constant 665 int SKID_NPC_WIDEBLEEDING;
Data           :   constant 666 int SKID_NPC_WIDESTONE;
Data           :   constant 667 int SKID_NPC_WIDECONFUSE;
Data           :   constant 668 int SKID_NPC_WIDESLEEP;
Data           :   constant 669 int SKID_NPC_WIDESIGHT;
Data           :   constant 670 int SKID_NPC_EVILLAND;
Data           :   constant 671 int SKID_NPC_MAGICMIRROR;
Data           :   constant 672 int SKID_NPC_SLOWCAST;
Data           :   constant 673 int SKID_NPC_CRITICALWOUND;
Data           :   constant 674 int SKID_NPC_EXPULSION;
Data           :   constant 675 int SKID_NPC_STONESKIN;
Data           :   constant 676 int SKID_NPC_ANTIMAGIC;
Data           :   constant 677 int SKID_NPC_WIDECURSE;
Data           :   constant 678 int SKID_NPC_WIDESTUN;
Data           :   constant 679 int SKID_NPC_VAMPIRE_GIFT;
Data           :   constant 680 int SKID_NPC_WIDESOULDRAIN;
Data           :   constant 681 int SKID_ALL_INCCARRY;
Data           :   constant 682 int SKID_NPC_TALK;
Data           :   constant 683 int SKID_NPC_HELLPOWER;
Data           :   constant 684 int SKID_NPC_WIDEHELLDIGNITY;
Data           :   constant 685 int SKID_NPC_INVINCIBLE;
Data           :   constant 686 int SKID_NPC_INVINCIBLEOFF;
Data           :   constant 687 int SKID_NPC_ALLHEAL;
Data           :   constant 688 int SKID_GM_SANDMAN;
Data           :   constant 689 int SKID_CASH_BLESSING;
Data           :   constant 690 int SKID_CASH_INCAGI;
Data           :   constant 691 int SKID_CASH_ASSUMPTIO;
Data           :   constant 692 int SKID_ALL_CATCRY;
Data           :   constant 693 int SKID_ALL_PARTYFLEE;
Data           :   constant 694 int SKID_ALL_ANGEL_PROTECT;
Data           :   constant 695 int SKID_ALL_DREAM_SUMMERNIGHT;
Data           :   constant 696 int SKID_NPC_CHANGEUNDEAD2;
Data           :   constant 697 int SKID_ALL_REVERSEORCISH;
Data           :   constant 698 int SKID_ALL_WEWISH;
Data           :   constant 699 int SKID_ALL_SONKRAN;
Data           :   constant 700 int SKID_NPC_WIDEHEALTHFEAR;
Data           :   constant 701 int SKID_NPC_WIDEBODYBURNNING;
Data           :   constant 702 int SKID_NPC_WIDEFROSTMISTY;
Data           :   constant 703 int SKID_NPC_WIDECOLD;
Data           :   constant 704 int SKID_NPC_WIDE_DEEP_SLEEP;
Data           :   constant 705 int SKID_NPC_WIDESIREN;
Data           :   constant 706 int SKID_NPC_VENOMFOG;
Data           :   constant 707 int SKID_NPC_MILLENNIUMSHIELD;
Data           :   constant 708 int SKID_NPC_COMET;
Data           :   constant 709 int SKID_NPC_ICEMINE;
Data           :   constant 710 int SKID_NPC_ICEEXPLO;
Data           :   constant 711 int SKID_NPC_FLAMECROSS;
Data           :   constant 712 int SKID_NPC_PULSESTRIKE2;
Data           :   constant 713 int SKID_NPC_DANCINGBLADE;
Data           :   constant 714 int SKID_NPC_DANCINGBLADE_ATK;
Data           :   constant 715 int SKID_NPC_DARKPIERCING;
Data           :   constant 716 int SKID_NPC_MAXPAIN;
Data           :   constant 717 int SKID_NPC_MAXPAIN_ATK;
Data           :   constant 718 int SKID_NPC_DEATHSUMMON;
Data           :   constant 719 int SKID_NPC_HELLBURNING;
Data           :   constant 720 int SKID_NPC_JACKFROST;
Data           :   constant 1000 int SKID_2NDJOB_QUESTBEGIN;
Data           :   constant 1001 int SKID_KN_CHARGEATK;
Data           :   constant 1002 int SKID_CR_SHRINK;
Data           :   constant 1003 int SKID_AS_SONICACCEL;
Data           :   constant 1004 int SKID_AS_VENOMKNIFE;
Data           :   constant 1005 int SKID_RG_CLOSECONFINE;
Data           :   constant 1006 int SKID_WZ_SIGHTBLASTER;
Data           :   constant 1007 int SKID_SA_CREATECON;
Data           :   constant 1008 int SKID_SA_ELEMENTWATER;
Data           :   constant 1009 int SKID_HT_PHANTASMIC;
Data           :   constant 1010 int SKID_BA_PANGVOICE;
Data           :   constant 1011 int SKID_DC_WINKCHARM;
Data           :   constant 1012 int SKID_BS_UNFAIRLYTRICK;
Data           :   constant 1013 int SKID_BS_GREED;
Data           :   constant 1014 int SKID_PR_REDEMPTIO;
Data           :   constant 1015 int SKID_MO_KITRANSLATION;
Data           :   constant 1016 int SKID_MO_BALKYOUNG;
Data           :   constant 1017 int SKID_SA_ELEMENTGROUND;
Data           :   constant 1018 int SKID_SA_ELEMENTFIRE;
Data           :   constant 1019 int SKID_SA_ELEMENTWIND;
Data           :   constant 1020 int SKID_2NDJOB_QUESTEND;
Data           :   constant 2000 int SKID_THIRDJOB_BEGIN;
Data           :   constant 2001 int SKID_RK_ENCHANTBLADE;
Data           :   constant 2002 int SKID_RK_SONICWAVE;
Data           :   constant 2003 int SKID_RK_DEATHBOUND;
Data           :   constant 2004 int SKID_RK_HUNDREDSPEAR;
Data           :   constant 2005 int SKID_RK_WINDCUTTER;
Data           :   constant 2006 int SKID_RK_IGNITIONBREAK;
Data           :   constant 2007 int SKID_RK_DRAGONTRAINING;
Data           :   constant 2008 int SKID_RK_DRAGONBREATH;
Data           :   constant 2009 int SKID_RK_DRAGONHOWLING;
Data           :   constant 2010 int SKID_RK_RUNEMASTERY;
Data           :   constant 2011 int SKID_RK_MILLENNIUMSHIELD;
Data           :   constant 2012 int SKID_RK_CRUSHSTRIKE;
Data           :   constant 2013 int SKID_RK_REFRESH;
Data           :   constant 2014 int SKID_RK_GIANTGROWTH;
Data           :   constant 2015 int SKID_RK_STONEHARDSKIN;
Data           :   constant 2016 int SKID_RK_VITALITYACTIVATION;
Data           :   constant 2017 int SKID_RK_STORMBLAST;
Data           :   constant 2018 int SKID_RK_FIGHTINGSPIRIT;
Data           :   constant 2019 int SKID_RK_ABUNDANCE;
Data           :   constant 2020 int SKID_RK_PHANTOMTHRUST;
Data           :   constant 2021 int SKID_GC_VENOMIMPRESS;
Data           :   constant 2022 int SKID_GC_CROSSIMPACT;
Data           :   constant 2023 int SKID_GC_DARKILLUSION;
Data           :   constant 2024 int SKID_GC_RESEARCHNEWPOISON;
Data           :   constant 2025 int SKID_GC_CREATENEWPOISON;
Data           :   constant 2026 int SKID_GC_ANTIDOTE;
Data           :   constant 2027 int SKID_GC_POISONINGWEAPON;
Data           :   constant 2028 int SKID_GC_WEAPONBLOCKING;
Data           :   constant 2029 int SKID_GC_COUNTERSLASH;
Data           :   constant 2030 int SKID_GC_WEAPONCRUSH;
Data           :   constant 2031 int SKID_GC_VENOMPRESSURE;
Data           :   constant 2032 int SKID_GC_POISONSMOKE;
Data           :   constant 2033 int SKID_GC_CLOAKINGEXCEED;
Data           :   constant 2034 int SKID_GC_PHANTOMMENACE;
Data           :   constant 2035 int SKID_GC_HALLUCINATIONWALK;
Data           :   constant 2036 int SKID_GC_ROLLINGCUTTER;
Data           :   constant 2037 int SKID_GC_CROSSRIPPERSLASHER;
Data           :   constant 2038 int SKID_AB_JUDEX;
Data           :   constant 2039 int SKID_AB_ANCILLA;
Data           :   constant 2040 int SKID_AB_ADORAMUS;
Data           :   constant 2041 int SKID_AB_CLEMENTIA;
Data           :   constant 2042 int SKID_AB_CANTO;
Data           :   constant 2043 int SKID_AB_CHEAL;
Data           :   constant 2044 int SKID_AB_EPICLESIS;
Data           :   constant 2045 int SKID_AB_PRAEFATIO;
Data           :   constant 2046 int SKID_AB_ORATIO;
Data           :   constant 2047 int SKID_AB_LAUDAAGNUS;
Data           :   constant 2048 int SKID_AB_LAUDARAMUS;
Data           :   constant 2049 int SKID_AB_EUCHARISTICA;
Data           :   constant 2050 int SKID_AB_RENOVATIO;
Data           :   constant 2051 int SKID_AB_HIGHNESSHEAL;
Data           :   constant 2052 int SKID_AB_CLEARANCE;
Data           :   constant 2053 int SKID_AB_EXPIATIO;
Data           :   constant 2054 int SKID_AB_DUPLELIGHT;
Data           :   constant 2055 int SKID_AB_DUPLELIGHT_MELEE;
Data           :   constant 2056 int SKID_AB_DUPLELIGHT_MAGIC;
Data           :   constant 2057 int SKID_AB_SILENTIUM;
Data           :   constant 2200 int SKID_WL_STARTMARK;
Data           :   constant 2201 int SKID_WL_WHITEIMPRISON;
Data           :   constant 2202 int SKID_WL_SOULEXPANSION;
Data           :   constant 2203 int SKID_WL_FROSTMISTY;
Data           :   constant 2204 int SKID_WL_JACKFROST;
Data           :   constant 2205 int SKID_WL_MARSHOFABYSS;
Data           :   constant 2206 int SKID_WL_RECOGNIZEDSPELL;
Data           :   constant 2207 int SKID_WL_SIENNAEXECRATE;
Data           :   constant 2208 int SKID_WL_RADIUS;
Data           :   constant 2209 int SKID_WL_STASIS;
Data           :   constant 2210 int SKID_WL_DRAINLIFE;
Data           :   constant 2211 int SKID_WL_CRIMSONROCK;
Data           :   constant 2212 int SKID_WL_HELLINFERNO;
Data           :   constant 2213 int SKID_WL_COMET;
Data           :   constant 2214 int SKID_WL_CHAINLIGHTNING;
Data           :   constant 2215 int SKID_WL_CHAINLIGHTNING_ATK;
Data           :   constant 2216 int SKID_WL_EARTHSTRAIN;
Data           :   constant 2217 int SKID_WL_TETRAVORTEX;
Data           :   constant 2218 int SKID_WL_TETRAVORTEX_FIRE;
Data           :   constant 2219 int SKID_WL_TETRAVORTEX_WATER;
Data           :   constant 2220 int SKID_WL_TETRAVORTEX_WIND;
Data           :   constant 2221 int SKID_WL_TETRAVORTEX_GROUND;
Data           :   constant 2222 int SKID_WL_SUMMONFB;
Data           :   constant 2223 int SKID_WL_SUMMONBL;
Data           :   constant 2224 int SKID_WL_SUMMONWB;
Data           :   constant 2225 int SKID_WL_SUMMON_ATK_FIRE;
Data           :   constant 2226 int SKID_WL_SUMMON_ATK_WIND;
Data           :   constant 2227 int SKID_WL_SUMMON_ATK_WATER;
Data           :   constant 2228 int SKID_WL_SUMMON_ATK_GROUND;
Data           :   constant 2229 int SKID_WL_SUMMONSTONE;
Data           :   constant 2230 int SKID_WL_RELEASE;
Data           :   constant 2231 int SKID_WL_READING_SB;
Data           :   constant 2232 int SKID_WL_FREEZE_SP;
Data           :   constant 2232 int SKID_WL_ENDMARK;
Data           :   constant 2233 int SKID_RA_ARROWSTORM;
Data           :   constant 2234 int SKID_RA_FEARBREEZE;
Data           :   constant 2235 int SKID_RA_RANGERMAIN;
Data           :   constant 2236 int SKID_RA_AIMEDBOLT;
Data           :   constant 2237 int SKID_RA_DETONATOR;
Data           :   constant 2238 int SKID_RA_ELECTRICSHOCKER;
Data           :   constant 2239 int SKID_RA_CLUSTERBOMB;
Data           :   constant 2240 int SKID_RA_WUGMASTERY;
Data           :   constant 2241 int SKID_RA_WUGRIDER;
Data           :   constant 2242 int SKID_RA_WUGDASH;
Data           :   constant 2243 int SKID_RA_WUGSTRIKE;
Data           :   constant 2244 int SKID_RA_WUGBITE;
Data           :   constant 2245 int SKID_RA_TOOTHOFWUG;
Data           :   constant 2246 int SKID_RA_SENSITIVEKEEN;
Data           :   constant 2247 int SKID_RA_CAMOUFLAGE;
Data           :   constant 2248 int SKID_RA_RESEARCHTRAP;
Data           :   constant 2249 int SKID_RA_MAGENTATRAP;
Data           :   constant 2250 int SKID_RA_COBALTTRAP;
Data           :   constant 2251 int SKID_RA_MAIZETRAP;
Data           :   constant 2252 int SKID_RA_VERDURETRAP;
Data           :   constant 2253 int SKID_RA_FIRINGTRAP;
Data           :   constant 2254 int SKID_RA_ICEBOUNDTRAP;
Data           :   constant 2255 int SKID_NC_MADOLICENCE;
Data           :   constant 2256 int SKID_NC_BOOSTKNUCKLE;
Data           :   constant 2257 int SKID_NC_PILEBUNKER;
Data           :   constant 2258 int SKID_NC_VULCANARM;
Data           :   constant 2259 int SKID_NC_FLAMELAUNCHER;
Data           :   constant 2260 int SKID_NC_COLDSLOWER;
Data           :   constant 2261 int SKID_NC_ARMSCANNON;
Data           :   constant 2262 int SKID_NC_ACCELERATION;
Data           :   constant 2263 int SKID_NC_HOVERING;
Data           :   constant 2264 int SKID_NC_F_SIDESLIDE;
Data           :   constant 2265 int SKID_NC_B_SIDESLIDE;
Data           :   constant 2266 int SKID_NC_MAINFRAME;
Data           :   constant 2267 int SKID_NC_SELFDESTRUCTION;
Data           :   constant 2268 int SKID_NC_SHAPESHIFT;
Data           :   constant 2269 int SKID_NC_EMERGENCYCOOL;
Data           :   constant 2270 int SKID_NC_INFRAREDSCAN;
Data           :   constant 2271 int SKID_NC_ANALYZE;
Data           :   constant 2272 int SKID_NC_MAGNETICFIELD;
Data           :   constant 2273 int SKID_NC_NEUTRALBARRIER;
Data           :   constant 2274 int SKID_NC_STEALTHFIELD;
Data           :   constant 2275 int SKID_NC_REPAIR;
Data           :   constant 2276 int SKID_NC_TRAININGAXE;
Data           :   constant 2277 int SKID_NC_RESEARCHFE;
Data           :   constant 2278 int SKID_NC_AXEBOOMERANG;
Data           :   constant 2279 int SKID_NC_POWERSWING;
Data           :   constant 2280 int SKID_NC_AXETORNADO;
Data           :   constant 2281 int SKID_NC_SILVERSNIPER;
Data           :   constant 2282 int SKID_NC_MAGICDECOY;
Data           :   constant 2283 int SKID_NC_DISJOINT;
Data           :   constant 2284 int SKID_SC_STARTMARK;
Data           :   constant 2284 int SKID_SC_FATALMENACE;
Data           :   constant 2285 int SKID_SC_REPRODUCE;
Data           :   constant 2286 int SKID_SC_AUTOSHADOWSPELL;
Data           :   constant 2287 int SKID_SC_SHADOWFORM;
Data           :   constant 2288 int SKID_SC_TRIANGLESHOT;
Data           :   constant 2289 int SKID_SC_BODYPAINT;
Data           :   constant 2290 int SKID_SC_INVISIBILITY;
Data           :   constant 2291 int SKID_SC_DEADLYINFECT;
Data           :   constant 2292 int SKID_SC_ENERVATION;
Data           :   constant 2293 int SKID_SC_GROOMY;
Data           :   constant 2294 int SKID_SC_IGNORANCE;
Data           :   constant 2295 int SKID_SC_LAZINESS;
Data           :   constant 2296 int SKID_SC_UNLUCKY;
Data           :   constant 2297 int SKID_SC_WEAKNESS;
Data           :   constant 2298 int SKID_SC_STRIPACCESSARY;
Data           :   constant 2299 int SKID_SC_MANHOLE;
Data           :   constant 2300 int SKID_SC_DIMENSIONDOOR;
Data           :   constant 2301 int SKID_SC_CHAOSPANIC;
Data           :   constant 2302 int SKID_SC_MAELSTROM;
Data           :   constant 2303 int SKID_SC_BLOODYLUST;
Data           :   constant 2304 int SKID_SC_FEINTBOMB;
Data           :   constant 2306 int SKID_SC_ENDMARK;
Data           :   constant 2307 int SKID_LG_CANNONSPEAR;
Data           :   constant 2308 int SKID_LG_BANISHINGPOINT;
Data           :   constant 2309 int SKID_LG_TRAMPLE;
Data           :   constant 2310 int SKID_LG_SHIELDPRESS;
Data           :   constant 2311 int SKID_LG_REFLECTDAMAGE;
Data           :   constant 2312 int SKID_LG_PINPOINTATTACK;
Data           :   constant 2313 int SKID_LG_FORCEOFVANGUARD;
Data           :   constant 2314 int SKID_LG_RAGEBURST;
Data           :   constant 2315 int SKID_LG_SHIELDSPELL;
Data           :   constant 2316 int SKID_LG_EXEEDBREAK;
Data           :   constant 2317 int SKID_LG_OVERBRAND;
Data           :   constant 2318 int SKID_LG_PRESTIGE;
Data           :   constant 2319 int SKID_LG_BANDING;
Data           :   constant 2320 int SKID_LG_MOONSLASHER;
Data           :   constant 2321 int SKID_LG_RAYOFGENESIS;
Data           :   constant 2322 int SKID_LG_PIETY;
Data           :   constant 2323 int SKID_LG_EARTHDRIVE;
Data           :   constant 2324 int SKID_LG_HESPERUSLIT;
Data           :   constant 2325 int SKID_LG_INSPIRATION;
Data           :   constant 2326 int SKID_SR_DRAGONCOMBO;
Data           :   constant 2327 int SKID_SR_SKYNETBLOW;
Data           :   constant 2328 int SKID_SR_EARTHSHAKER;
Data           :   constant 2329 int SKID_SR_FALLENEMPIRE;
Data           :   constant 2330 int SKID_SR_TIGERCANNON;
Data           :   constant 2331 int SKID_SR_HELLGATE;
Data           :   constant 2332 int SKID_SR_RAMPAGEBLASTER;
Data           :   constant 2333 int SKID_SR_CRESCENTELBOW;
Data           :   constant 2334 int SKID_SR_CURSEDCIRCLE;
Data           :   constant 2335 int SKID_SR_LIGHTNINGWALK;
Data           :   constant 2336 int SKID_SR_KNUCKLEARROW;
Data           :   constant 2337 int SKID_SR_WINDMILL;
Data           :   constant 2338 int SKID_SR_RAISINGDRAGON;
Data           :   constant 2339 int SKID_SR_GENTLETOUCH;
Data           :   constant 2340 int SKID_SR_ASSIMILATEPOWER;
Data           :   constant 2341 int SKID_SR_POWERVELOCITY;
Data           :   constant 2342 int SKID_SR_CRESCENTELBOW_AUTOSPELL;
Data           :   constant 2343 int SKID_SR_GATEOFHELL;
Data           :   constant 2344 int SKID_SR_GENTLETOUCH_QUIET;
Data           :   constant 2345 int SKID_SR_GENTLETOUCH_CURE;
Data           :   constant 2346 int SKID_SR_GENTLETOUCH_ENERGYGAIN;
Data           :   constant 2347 int SKID_SR_GENTLETOUCH_CHANGE;
Data           :   constant 2348 int SKID_SR_GENTLETOUCH_REVITALIZE;
Data           :   constant 2349 int SKID_WA_STARTMARK;
Data           :   constant 2350 int SKID_WA_SWING_DANCE;
Data           :   constant 2351 int SKID_WA_SYMPHONY_OF_LOVER;
Data           :   constant 2352 int SKID_WA_MOONLIT_SERENADE;
Data           :   constant 2379 int SKID_WA_ENDMARK;
Data           :   constant 2380 int SKID_MI_STARTMARK;
Data           :   constant 2381 int SKID_MI_RUSH_WINDMILL;
Data           :   constant 2382 int SKID_MI_ECHOSONG;
Data           :   constant 2383 int SKID_MI_HARMONIZE;
Data           :   constant 2410 int SKID_MI_ENDMARK;
Data           :   constant 2411 int SKID_WM_STARTMARK;
Data           :   constant 2412 int SKID_WM_LESSON;
Data           :   constant 2413 int SKID_WM_METALICSOUND;
Data           :   constant 2414 int SKID_WM_REVERBERATION;
Data           :   constant 2415 int SKID_WM_REVERBERATION_MELEE;
Data           :   constant 2416 int SKID_WM_REVERBERATION_MAGIC;
Data           :   constant 2417 int SKID_WM_DOMINION_IMPULSE;
Data           :   constant 2418 int SKID_WM_SEVERE_RAINSTORM;
Data           :   constant 2419 int SKID_WM_POEMOFNETHERWORLD;
Data           :   constant 2420 int SKID_WM_VOICEOFSIREN;
Data           :   constant 2421 int SKID_WM_DEADHILLHERE;
Data           :   constant 2422 int SKID_WM_LULLABY_DEEPSLEEP;
Data           :   constant 2423 int SKID_WM_SIRCLEOFNATURE;
Data           :   constant 2424 int SKID_WM_RANDOMIZESPELL;
Data           :   constant 2425 int SKID_WM_GLOOMYDAY;
Data           :   constant 2426 int SKID_WM_GREAT_ECHO;
Data           :   constant 2427 int SKID_WM_SONG_OF_MANA;
Data           :   constant 2428 int SKID_WM_DANCE_WITH_WUG;
Data           :   constant 2429 int SKID_WM_SOUND_OF_DESTRUCTION;
Data           :   constant 2430 int SKID_WM_SATURDAY_NIGHT_FEVER;
Data           :   constant 2431 int SKID_WM_LERADS_DEW;
Data           :   constant 2432 int SKID_WM_MELODYOFSINK;
Data           :   constant 2433 int SKID_WM_BEYOND_OF_WARCRY;
Data           :   constant 2434 int SKID_WM_UNLIMITED_HUMMING_VOICE;
Data           :   constant 2441 int SKID_WM_ENDMARK;
Data           :   constant 2442 int SKID_SO_STARTMARK;
Data           :   constant 2443 int SKID_SO_FIREWALK;
Data           :   constant 2444 int SKID_SO_ELECTRICWALK;
Data           :   constant 2445 int SKID_SO_SPELLFIST;
Data           :   constant 2446 int SKID_SO_EARTHGRAVE;
Data           :   constant 2447 int SKID_SO_DIAMONDDUST;
Data           :   constant 2448 int SKID_SO_POISON_BUSTER;
Data           :   constant 2449 int SKID_SO_PSYCHIC_WAVE;
Data           :   constant 2450 int SKID_SO_CLOUD_KILL;
Data           :   constant 2451 int SKID_SO_STRIKING;
Data           :   constant 2452 int SKID_SO_WARMER;
Data           :   constant 2453 int SKID_SO_VACUUM_EXTREME;
Data           :   constant 2454 int SKID_SO_VARETYR_SPEAR;
Data           :   constant 2455 int SKID_SO_ARRULLO;
Data           :   constant 2456 int SKID_SO_EL_CONTROL;
Data           :   constant 2457 int SKID_SO_SUMMON_AGNI;
Data           :   constant 2458 int SKID_SO_SUMMON_AQUA;
Data           :   constant 2459 int SKID_SO_SUMMON_VENTUS;
Data           :   constant 2460 int SKID_SO_SUMMON_TERA;
Data           :   constant 2461 int SKID_SO_EL_ACTION;
Data           :   constant 2462 int SKID_SO_EL_ANALYSIS;
Data           :   constant 2463 int SKID_SO_EL_SYMPATHY;
Data           :   constant 2464 int SKID_SO_EL_CURE;
Data           :   constant 2465 int SKID_SO_FIRE_INSIGNIA;
Data           :   constant 2466 int SKID_SO_WATER_INSIGNIA;
Data           :   constant 2467 int SKID_SO_WIND_INSIGNIA;
Data           :   constant 2468 int SKID_SO_EARTH_INSIGNIA;
Data           :   constant 2472 int SKID_SO_ENDMARK;
Data           :   constant 2473 int SKID_GN_START_MARK;
Data           :   constant 2474 int SKID_GN_TRAINING_SWORD;
Data           :   constant 2475 int SKID_GN_REMODELING_CART;
Data           :   constant 2476 int SKID_GN_CART_TORNADO;
Data           :   constant 2477 int SKID_GN_CARTCANNON;
Data           :   constant 2478 int SKID_GN_CARTBOOST;
Data           :   constant 2479 int SKID_GN_THORNS_TRAP;
Data           :   constant 2480 int SKID_GN_BLOOD_SUCKER;
Data           :   constant 2481 int SKID_GN_SPORE_EXPLOSION;
Data           :   constant 2482 int SKID_GN_WALLOFTHORN;
Data           :   constant 2483 int SKID_GN_CRAZYWEED;
Data           :   constant 2484 int SKID_GN_CRAZYWEED_ATK;
Data           :   constant 2485 int SKID_GN_DEMONIC_FIRE;
Data           :   constant 2486 int SKID_GN_FIRE_EXPANSION;
Data           :   constant 2487 int SKID_GN_FIRE_EXPANSION_SMOKE_POWDER;
Data           :   constant 2488 int SKID_GN_FIRE_EXPANSION_TEAR_GAS;
Data           :   constant 2489 int SKID_GN_FIRE_EXPANSION_ACID;
Data           :   constant 2490 int SKID_GN_HELLS_PLANT;
Data           :   constant 2491 int SKID_GN_HELLS_PLANT_ATK;
Data           :   constant 2492 int SKID_GN_MANDRAGORA;
Data           :   constant 2493 int SKID_GN_SLINGITEM;
Data           :   constant 2494 int SKID_GN_CHANGEMATERIAL;
Data           :   constant 2495 int SKID_GN_MIX_COOKING;
Data           :   constant 2496 int SKID_GN_MAKEBOMB;
Data           :   constant 2497 int SKID_GN_S_PHARMACY;
Data           :   constant 2498 int SKID_GN_SLINGITEM_RANGEMELEEATK;
Data           :   constant 2513 int SKID_GN_ENDMARK;
Data           :   constant 2514 int SKID_ETC_THIRDJOB_SKILL_START;
Data           :   constant 2515 int SKID_AB_SECRAMENT;
Data           :   constant 2516 int SKID_WM_SEVERE_RAINSTORM_MELEE;
Data           :   constant 2517 int SKID_SR_HOWLINGOFLION;
Data           :   constant 2518 int SKID_SR_RIDEINLIGHTNING;
Data           :   constant 2519 int SKID_LG_OVERBRAND_BRANDISH;
Data           :   constant 2520 int SKID_LG_OVERBRAND_PLUSATK;
Data           :   constant 2531 int SKID_ETC_THIRDJOB_SKILL_END;
Data           :   constant 2532 int SKID_THIRDJOB_END;
Data           :   constant 2533 int SKID_ALL_ODINS_RECALL;
Data           :   constant 2534 int SKID_RETURN_TO_ELDICASTES;
Data           :   constant 2535 int SKID_ALL_BUYING_STORE;
Data           :   constant 2536 int SKID_ALL_GUARDIAN_RECALL;
Data           :   constant 2537 int SKID_ALL_ODINS_POWER;
Data           :   constant 2538 int SKID_XX_BEER_BOTTLE_CAP;
Data           :   constant 2539 int SKID_NPC_ASSASSINCROSS;
Data           :   constant 2540 int SKID_NPC_DISSONANCE;
Data           :   constant 2541 int SKID_NPC_UGLYDANCE;
Data           :   constant 2542 int SKID_ALL_TETANY;
Data           :   constant 2543 int SKID_ALL_RAY_OF_PROTECTION;
Data           :   constant 2544 int SKID_MC_CARTDECORATE;
Data           :   constant 2545 int SKID_GM_ITEM_ATKMAX;
Data           :   constant 2546 int SKID_GM_ITEM_ATKMIN;
Data           :   constant 2547 int SKID_GM_ITEM_MATKMAX;
Data           :   constant 2548 int SKID_GM_ITEM_MATKMIN;
Data           :   constant 3000 int SKID_UPPER_EXTENDED_JOB_START;
Data           :   constant 3001 int SKID_KO_YAMIKUMO;
Data           :   constant 3002 int SKID_KO_RIGHT;
Data           :   constant 3003 int SKID_KO_LEFT;
Data           :   constant 3004 int SKID_KO_JYUMONJIKIRI;
Data           :   constant 3005 int SKID_KO_SETSUDAN;
Data           :   constant 3006 int SKID_KO_BAKURETSU;
Data           :   constant 3007 int SKID_KO_HAPPOKUNAI;
Data           :   constant 3008 int SKID_KO_MUCHANAGE;
Data           :   constant 3009 int SKID_KO_HUUMARANKA;
Data           :   constant 3010 int SKID_KO_MAKIBISHI;
Data           :   constant 3011 int SKID_KO_MEIKYOUSISUI;
Data           :   constant 3012 int SKID_KO_ZANZOU;
Data           :   constant 3013 int SKID_KO_KYOUGAKU;
Data           :   constant 3014 int SKID_KO_JYUSATSU;
Data           :   constant 3015 int SKID_KO_KAHU_ENTEN;
Data           :   constant 3016 int SKID_KO_HYOUHU_HUBUKI;
Data           :   constant 3017 int SKID_KO_KAZEHU_SEIRAN;
Data           :   constant 3018 int SKID_KO_DOHU_KOUKAI;
Data           :   constant 3019 int SKID_KO_KAIHOU;
Data           :   constant 3020 int SKID_KO_ZENKAI;
Data           :   constant 3021 int SKID_KO_GENWAKU;
Data           :   constant 3022 int SKID_KO_IZAYOI;
Data           :   constant 3023 int SKID_KG_KAGEHUMI;
Data           :   constant 3024 int SKID_KG_KYOMU;
Data           :   constant 3025 int SKID_KG_KAGEMUSYA;
Data           :   constant 3026 int SKID_OB_ZANGETSU;
Data           :   constant 3027 int SKID_OB_OBOROGENSOU;
Data           :   constant 3028 int SKID_OB_OBOROGENSOU_TRANSITION_ATK;
Data           :   constant 3029 int SKID_OB_AKAITSUKI;
Data           :   constant 3030 int SKID_UPPER_EXTENDED_JOB_END;
Data           :   constant 3031 int SKID_ECL_SNOWFLIP;
Data           :   constant 3032 int SKID_ECL_PEONYMAMY;
Data           :   constant 3033 int SKID_ECL_SADAGUI;
Data           :   constant 3034 int SKID_ECL_SEQUOIADUST;
Data           :   constant 3035 int SKID_ECLAGE_RECALL;
Data           :   constant 5000 int SKID_LEVEL_EXPANSION_START;
Data           :   constant 5001 int SKID_GC_DARKCROW;
Data           :   constant 5002 int SKID_RA_UNLIMIT;
Data           :   constant 5003 int SKID_GN_ILLUSIONDOPING;
Data           :   constant 5004 int SKID_RK_DRAGONBREATH_WATER;
Data           :   constant 5005 int SKID_RK_LUXANIMA;
Data           :   constant 5006 int SKID_NC_MAGMA_ERUPTION;
Data           :   constant 5007 int SKID_WM_FRIGG_SONG;
Data           :   constant 5008 int SKID_SO_ELEMENTAL_SHIELD;
Data           :   constant 5009 int SKID_SR_FLASHCOMBO;
Data           :   constant 5010 int SKID_SC_ESCAPE;
Data           :   constant 5011 int SKID_AB_OFFERTORIUM;
Data           :   constant 5012 int SKID_WL_TELEKINESIS_INTENSE;
Data           :   constant 5013 int SKID_LG_KINGS_GRACE;
Data           :   constant 5014 int SKID_ALL_FULL_THROTTLE;
Data           :   constant 5015 int SKID_SR_FLASHCOMBO_ATK_STEP1;
Data           :   constant 5016 int SKID_SR_FLASHCOMBO_ATK_STEP2;
Data           :   constant 5017 int SKID_SR_FLASHCOMBO_ATK_STEP3;
Data           :   constant 5018 int SKID_SR_FLASHCOMBO_ATK_STEP4;
Data           :   constant 5300 int SKID_LEVEL_EXPANSION_END;
Data           :   constant 5301 int SKID_LAST;
Data           :   constant 8000 int SKID_HOMUN_BEGIN;
Data           :   constant 8001 int SKID_HLIF_HEAL;
Data           :   constant 8002 int SKID_HLIF_AVOID;
Data           :   constant 8003 int SKID_HLIF_BRAIN;
Data           :   constant 8004 int SKID_HLIF_CHANGE;
Data           :   constant 8005 int SKID_HAMI_CASTLE;
Data           :   constant 8006 int SKID_HAMI_DEFENCE;
Data           :   constant 8007 int SKID_HAMI_SKIN;
Data           :   constant 8008 int SKID_HAMI_BLOODLUST;
Data           :   constant 8009 int SKID_HFLI_MOON;
Data           :   constant 8010 int SKID_HFLI_FLEET;
Data           :   constant 8011 int SKID_HFLI_SPEED;
Data           :   constant 8012 int SKID_HFLI_SBR44;
Data           :   constant 8013 int SKID_HVAN_CAPRICE;
Data           :   constant 8014 int SKID_HVAN_CHAOTIC;
Data           :   constant 8015 int SKID_HVAN_INSTRUCT;
Data           :   constant 8016 int SKID_HVAN_EXPLOSION;
Data           :   constant 8017 int SKID_MUTATION_BASEJOB;
Data           :   constant 8018 int SKID_MH_SUMMON_LEGION;
Data           :   constant 8019 int SKID_MH_NEEDLE_OF_PARALYZE;
Data           :   constant 8020 int SKID_MH_POISON_MIST;
Data           :   constant 8021 int SKID_MH_PAIN_KILLER;
Data           :   constant 8022 int SKID_MH_LIGHT_OF_REGENE;
Data           :   constant 8023 int SKID_MH_OVERED_BOOST;
Data           :   constant 8024 int SKID_MH_ERASER_CUTTER;
Data           :   constant 8025 int SKID_MH_XENO_SLASHER;
Data           :   constant 8026 int SKID_MH_SILENT_BREEZE;
Data           :   constant 8027 int SKID_MH_STYLE_CHANGE;
Data           :   constant 8028 int SKID_MH_SONIC_CLAW;
Data           :   constant 8029 int SKID_MH_SILVERVEIN_RUSH;
Data           :   constant 8030 int SKID_MH_MIDNIGHT_FRENZY;
Data           :   constant 8031 int SKID_MH_STAHL_HORN;
Data           :   constant 8032 int SKID_MH_GOLDENE_FERSE;
Data           :   constant 8033 int SKID_MH_STEINWAND;
Data           :   constant 8034 int SKID_MH_HEILIGE_STANGE;
Data           :   constant 8035 int SKID_MH_ANGRIFFS_MODUS;
Data           :   constant 8036 int SKID_MH_TINDER_BREAKER;
Data           :   constant 8037 int SKID_MH_CBC;
Data           :   constant 8038 int SKID_MH_EQC;
Data           :   constant 8039 int SKID_MH_MAGMA_FLOW;
Data           :   constant 8040 int SKID_MH_GRANITIC_ARMOR;
Data           :   constant 8041 int SKID_MH_LAVA_SLIDE;
Data           :   constant 8042 int SKID_MH_PYROCLASTIC;
Data           :   constant 8043 int SKID_MH_VOLCANIC_ASH;
Data           :   constant 8044 int SKID_MH_LAST;
Data           :   constant 8045 int SKID_HOMUN_LAST;
Data           :   constant 8200 int SKID_MERCENARY_BEGIN;
Data           :   constant 8201 int SKID_MS_BASH;
Data           :   constant 8202 int SKID_MS_MAGNUM;
Data           :   constant 8203 int SKID_MS_BOWLINGBASH;
Data           :   constant 8204 int SKID_MS_PARRYING;
Data           :   constant 8205 int SKID_MS_REFLECTSHIELD;
Data           :   constant 8206 int SKID_MS_BERSERK;
Data           :   constant 8207 int SKID_MA_DOUBLE;
Data           :   constant 8208 int SKID_MA_SHOWER;
Data           :   constant 8209 int SKID_MA_SKIDTRAP;
Data           :   constant 8210 int SKID_MA_LANDMINE;
Data           :   constant 8211 int SKID_MA_SANDMAN;
Data           :   constant 8212 int SKID_MA_FREEZINGTRAP;
Data           :   constant 8213 int SKID_MA_REMOVETRAP;
Data           :   constant 8214 int SKID_MA_CHARGEARROW;
Data           :   constant 8215 int SKID_MA_SHARPSHOOTING;
Data           :   constant 8216 int SKID_ML_PIERCE;
Data           :   constant 8217 int SKID_ML_BRANDISH;
Data           :   constant 8218 int SKID_ML_SPIRALPIERCE;
Data           :   constant 8219 int SKID_ML_DEFENDER;
Data           :   constant 8220 int SKID_ML_AUTOGUARD;
Data           :   constant 8221 int SKID_ML_DEVOTION;
Data           :   constant 8222 int SKID_MER_MAGNIFICAT;
Data           :   constant 8223 int SKID_MER_QUICKEN;
Data           :   constant 8224 int SKID_MER_SIGHT;
Data           :   constant 8225 int SKID_MER_CRASH;
Data           :   constant 8226 int SKID_MER_REGAIN;
Data           :   constant 8227 int SKID_MER_TENDER;
Data           :   constant 8228 int SKID_MER_BENEDICTION;
Data           :   constant 8229 int SKID_MER_RECUPERATE;
Data           :   constant 8230 int SKID_MER_MENTALCURE;
Data           :   constant 8231 int SKID_MER_COMPRESS;
Data           :   constant 8232 int SKID_MER_PROVOKE;
Data           :   constant 8233 int SKID_MER_AUTOBERSERK;
Data           :   constant 8234 int SKID_MER_DECAGI;
Data           :   constant 8235 int SKID_MER_SCAPEGOAT;
Data           :   constant 8236 int SKID_MER_LEXDIVINA;
Data           :   constant 8237 int SKID_MER_ESTIMATION;
Data           :   constant 8238 int SKID_MER_KYRIE;
Data           :   constant 8239 int SKID_MER_BLESSING;
Data           :   constant 8240 int SKID_MER_INCAGI;
Data           :   constant 8241 int SKID_MER_INVINCIBLEOFF2;
Data           :   constant 8242 int SKID_MERCENARY_LAST;
Data           :   constant 8400 int SKID_ELEMENTAL_BEGIN;
Data           :   constant 8401 int SKID_EL_CIRCLE_OF_FIRE;
Data           :   constant 8402 int SKID_EL_FIRE_CLOAK;
Data           :   constant 8403 int SKID_EL_FIRE_MANTLE;
Data           :   constant 8404 int SKID_EL_WATER_SCREEN;
Data           :   constant 8405 int SKID_EL_WATER_DROP;
Data           :   constant 8406 int SKID_EL_WATER_BARRIER;
Data           :   constant 8407 int SKID_EL_WIND_STEP;
Data           :   constant 8408 int SKID_EL_WIND_CURTAIN;
Data           :   constant 8409 int SKID_EL_ZEPHYR;
Data           :   constant 8410 int SKID_EL_SOLID_SKIN;
Data           :   constant 8411 int SKID_EL_STONE_SHIELD;
Data           :   constant 8412 int SKID_EL_POWER_OF_GAIA;
Data           :   constant 8413 int SKID_EL_PYROTECHNIC;
Data           :   constant 8414 int SKID_EL_HEATER;
Data           :   constant 8415 int SKID_EL_TROPIC;
Data           :   constant 8416 int SKID_EL_AQUAPLAY;
Data           :   constant 8417 int SKID_EL_COOLER;
Data           :   constant 8418 int SKID_EL_CHILLY_AIR;
Data           :   constant 8419 int SKID_EL_GUST;
Data           :   constant 8420 int SKID_EL_BLAST;
Data           :   constant 8421 int SKID_EL_WILD_STORM;
Data           :   constant 8422 int SKID_EL_PETROLOGY;
Data           :   constant 8423 int SKID_EL_CURSED_SOIL;
Data           :   constant 8424 int SKID_EL_UPHEAVAL;
Data           :   constant 8425 int SKID_EL_FIRE_ARROW;
Data           :   constant 8426 int SKID_EL_FIRE_BOMB;
Data           :   constant 8427 int SKID_EL_FIRE_BOMB_ATK;
Data           :   constant 8428 int SKID_EL_FIRE_WAVE;
Data           :   constant 8429 int SKID_EL_FIRE_WAVE_ATK;
Data           :   constant 8430 int SKID_EL_ICE_NEEDLE;
Data           :   constant 8431 int SKID_EL_WATER_SCREW;
Data           :   constant 8432 int SKID_EL_WATER_SCREW_ATK;
Data           :   constant 8433 int SKID_EL_TIDAL_WEAPON;
Data           :   constant 8434 int SKID_EL_WIND_SLASH;
Data           :   constant 8435 int SKID_EL_HURRICANE;
Data           :   constant 8436 int SKID_EL_HURRICANE_ATK;
Data           :   constant 8437 int SKID_EL_TYPOON_MIS;
Data           :   constant 8438 int SKID_EL_TYPOON_MIS_ATK;
Data           :   constant 8439 int SKID_EL_STONE_HAMMER;
Data           :   constant 8440 int SKID_EL_ROCK_CRUSHER;
Data           :   constant 8441 int SKID_EL_ROCK_CRUSHER_ATK;
Data           :   constant 8442 int SKID_EL_STONE_RAIN;
Data           :   constant 8443 int SKID_ELEMENTAL_LAST;
Data           :   constant 9999 int SKID_FOLLOWER_NPC_RESET;
Data           :   constant 10000 int SKID_GD_APPROVAL;
Data           :   constant 10001 int SKID_GD_KAFRACONTRACT;
Data           :   constant 10002 int SKID_GD_GUARDRESEARCH;
Data           :   constant 10003 int SKID_GD_GUARDUP;
Data           :   constant 10004 int SKID_GD_EXTENSION;
Data           :   constant 10005 int SKID_GD_GLORYGUILD;
Data           :   constant 10006 int SKID_GD_LEADERSHIP;
Data           :   constant 10007 int SKID_GD_GLORYWOUNDS;
Data           :   constant 10008 int SKID_GD_SOULCOLD;
Data           :   constant 10009 int SKID_GD_HAWKEYES;
Data           :   constant 10010 int SKID_GD_BATTLEORDER;
Data           :   constant 10011 int SKID_GD_REGENERATION;
Data           :   constant 10012 int SKID_GD_RESTORE;
Data           :   constant 10013 int SKID_GD_EMERGENCYCALL;
Data           :   constant 10014 int SKID_GD_DEVELOPMENT;
Data           :   constant 10015 int SKID_GD_ITEMEMERGENCYCALL;
Data           :   constant 10016 int SKID_GD_LAST;
Data           :   constant 10100 int SKID_SYS_FIRSTJOBLV;
Data           :   constant 10101 int SKID_SYS_SECONDJOBLV;
Data           :   constant 11000 int SKID_SCRIPT_000;
Data           :   constant 11000 int SKID_ITEM_SAVAGE_STEAK;
Data           :   constant 11001 int SKID_ITEM_COCKTAIL_WARG_BLOOD;
Data           :   constant 11002 int SKID_ITEM_MINOR_BBQ;
Data           :   constant 11003 int SKID_ITEM_SIROMA_ICE_TEA;
Data           :   constant 11004 int SKID_ITEM_DROCERA_HERB_STEAMED;
Data           :   constant 11005 int SKID_ITEM_PUTTI_TAILS_NOODLES;
Data           :   constant 11006 int SKID_ITEM_BANANA_BOMB;
Data           :   constant 11999 int SKID_SCRIPT_999;
};
*/
