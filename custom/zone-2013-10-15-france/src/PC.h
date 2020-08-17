#pragma once
#include "Actor.h"
#include "AsyncDBWork/Effect3rd.h"


struct CLASS_INFO
{
	/* this+0 */ int ignoreDEFCount;
	/* this+4 */ short plusMDamagePercent;
	/* this+6 */ short ignoreMDEFPercent;
	/* this+8 */ short ignoreDEFPercent;
};


struct USER_TARGET_INFO
{
	/* this+ 0 */ int destroySPProbability;
	/* this+ 4 */ int destroySPPercent;
	/* this+ 8 */ int plusDamageByClass[3];
	/* this+20 */ int SPAmount_Action;
};


#pragma pack(push,1)
struct tagShortCutKey
{
	/* this+0 */ char isSkill;
	/* this+1 */ unsigned long ID;
	/* this+5 */ short count;
};
#pragma pack(pop)


struct CharacterInfo
{
	/* this+   0 */ unsigned long roomID;
	/* this+   4 */ int accountID;
	/* this+   8 */ int characterID;
	/* this+  12 */ int speed;
	/* this+  16 */ int plusCartspeed;
	/* this+  20 */ int AuthCode;
	/* this+  24 */ int isSendable;
	/* this+  28 */ int mapID;
	/* this+  32 */ int GuildID;
	/* this+  36 */ int GroupID;
	/* this+  40 */ int isGroupMaster;
	/* this+  44 */ short NotifyPositionX;
	/* this+  46 */ short NotifyPositionY;
	/* this+  48 */ unsigned long GroupExpOption;
	/* this+  52 */ int PartyItemPickupRule;
	/* this+  56 */ int PartyItemDivisionRule;
	/* this+  60 */ int exp;
	struct tagParty
	{
		union
		{
			struct tagConfig
			{
				/* this(bf)+0:0 len(1) */ unsigned char bRefuseJoinMsg : 1,
				/* this(bf)+0:1 len(7) */	            bReserved : 7;
			};

			/* this+0 */ tagConfig Bit;
			/* this+0 */ unsigned char Config;
		};
	};
	/* this+  64 */ tagParty Party;
	/* this+  65 */ bool bOpenEquipmentWin;
	/* this+  66 */ short font;
private:
	/* this+  68 */ int money;
public:
	int GetMoney(); //TODO
	int SetMoney(int ); //TODO
	int AddMoney(int ); //TODO
public:
	/* this+  72 */ int jobexp;
	/* this+  76 */ int joblevel;
	/* this+  80 */ int isWhisperAcceptable;
	/* this+  84 */ int virtue;
	/* this+  88 */ int honor;
	/* this+  92 */ int PKhonor;
	/* this+  96 */ int plusMaxHP;
	/* this+ 100 */ int MHP_Percent;
	/* this+ 104 */ int plusMaxSP;
	/* this+ 108 */ int MSP_Percent;
	/* this+ 112 */ short jobpoint;
	/* this+ 114 */ short sxPos;
	/* this+ 116 */ short syPos;
	/* this+ 118 */ short targetxPos;
	/* this+ 120 */ short targetyPos;
	/* this+ 122 */ short StrAmount;
	/* this+ 124 */ short AgiAmount;
	/* this+ 126 */ short VitAmount;
	/* this+ 128 */ short IntAmount;
	/* this+ 130 */ short DexAmount;
	/* this+ 132 */ short LukAmount;
	/* this+ 136 */ int ATKPercent;
	/* this+ 140 */ int DEFPercent;
	/* this+ 144 */ short ArcherDex;
	/* this+ 148 */ int plusAttRange;
	/* this+ 152 */ int recvBytes;
	/* this+ 156 */ int sendBytes;
	/* this+ 160 */ int IsLockOnMode;
	/* this+ 164 */ unsigned long targetAID;
	/* this+ 168 */ short job;
	/* this+ 170 */ short clevel;
	/* this+ 172 */ short sppoint;
	/* this+ 174 */ short head;
	/* this+ 176 */ int weapon;
	/* this+ 180 */ short accessory;
	/* this+ 184 */ int shoes;
	/* this+ 188 */ short headpalette;
	/* this+ 190 */ short bodypalette;
	/* this+ 192 */ short accessory2;
	/* this+ 194 */ short accessory3;
	/* this+ 196 */ short cookMastery;
	/* this+ 198 */ short headDir;
	/* this+ 200 */ unsigned char sex;
	/* this+ 201 */ char characterName[24];
	/* this+ 225 */ char accountName[24];
	/* this+ 249 */ char partyID[24];
	/* this+ 273 */ char mapName[16];
	/* this+ 289 */ char targetMapName[16];
	/* this+ 305 */ char restartMapName[16];
	/* this+ 321 */ char Str;
	/* this+ 322 */ char Agi;
	/* this+ 323 */ char Vit;
	/* this+ 324 */ char Int;
	/* this+ 325 */ char Dex;
	/* this+ 326 */ char Luk;
	/* this+ 327 */ char StrP;
	/* this+ 328 */ char AgiP;
	/* this+ 329 */ char VitP;
	/* this+ 330 */ char IntP;
	/* this+ 331 */ char DexP;
	/* this+ 332 */ char LukP;
	/* this+ 333 */ char xSize;
	/* this+ 334 */ char ySize;
	/* this+ 335 */ unsigned char haircolor;
	/* this+ 336 */ int extAttPower;
	/* this+ 340 */ int extItemDefPower;
	/* this+ 344 */ int extMagicAtkPercent;
	/* this+ 348 */ int extMagicDefPower;
	/* this+ 352 */ int extDodgePercent;
	/* this+ 356 */ int extDodgePercent2;
	/* this+ 360 */ int criPercent;
	/* this+ 364 */ int hitPercent;
	/* this+ 368 */ int extAttMPower;
	/* this+ 372 */ int isNeverBreakArmor;
	/* this+ 376 */ int isNeverBreakWeapon;
	/* this+ 380 */ int attackDamageWeapon[2];
	/* this+ 388 */ int attackDamageArmor[2];
	/* this+ 396 */ int resistHandicapState[41];
	/* this+ 560 */ int modifyDamge_RNGATK[2];
	/* this+ 568 */ int noDispel;
	/* this+ 572 */ int HPdrain[2];
	/* this+ 580 */ int SPdrain[2];
	/* this+ 588 */ int magicImmune;
	/* this+ 592 */ int noJamstone;
	/* this+ 596 */ int reflectPercent;
	/* this+ 600 */ int perfectDamage;
	/* this+ 604 */ int hasteAttack;
	/* this+ 608 */ int reinCarnation;
	/* this+ 612 */ int reduceSpellCastTime;
	/* this+ 616 */ int splashRange;
	/* this+ 620 */ int reducePercentSP;
	/* this+ 624 */ int reducePostDelay;
	/* this+ 628 */ CLASS_INFO classInfo[6];
	/* this+ 700 */ USER_TARGET_INFO userTarInfo[2];
	/* this+ 748 */ int plusAttackSpeed;
	/* this+ 752 */ int investigateCount;
	/* this+ 756 */ int guidedAttackPercent;
	/* this+ 760 */ int changeMonPercent;
	/* this+ 764 */ float extDEFPercent;
	/* this+ 768 */ float extMDEFPercent;
	/* this+ 772 */ int DEFFluctuation;
	/* this+ 776 */ int MDEFFluctuation;
	/* this+ 780 */ int neverDie;
	/* this+ 784 */ int MATKPercent;
	/* this+ 788 */ int MDEFPercent;
	/* this+ 792 */ int plusMakerPower;
	/* this+ 796 */ char LastOpenMailFromName[24];
	/* this+ 820 */ int isChangeShortCutKey;
	/* this+ 824 */ tagShortCutKey ShortCutKey[38];
	/* this+1092 */ int HPDrain_100;
	/* this+1096 */ short deadCount;
	/* this+1098 */ short m_Body;
	/* this+1100 */ short robe;
};
C_ASSERT( sizeof CharacterInfo == 1104 );


#pragma pack(push,1)
struct CHARINFO_TO_CHARACTERDB
{
	/* this+  0 */ int exp;
	/* this+  4 */ int GuildID;
	/* this+  8 */ int money;
	/* this+ 12 */ int jobexp;
	/* this+ 16 */ int joblevel;
	/* this+ 20 */ int bodystate;
	/* this+ 24 */ int healthstate;
	/* this+ 28 */ int effectstate;
	/* this+ 32 */ int virtue;
	/* this+ 36 */ int honor;
	/* this+ 40 */ int hp;
	/* this+ 44 */ short maxhp;
	/* this+ 46 */ short sp;
	/* this+ 48 */ short maxsp;
	/* this+ 50 */ short xPos;
	/* this+ 52 */ short yPos;
	/* this+ 54 */ short speed;
	/* this+ 56 */ short jobpoint;
	/* this+ 58 */ short sxPos;
	/* this+ 60 */ short syPos;
	/* this+ 62 */ short job;
	/* this+ 64 */ short clevel;
	/* this+ 66 */ short sppoint;
	/* this+ 68 */ short head;
	/* this+ 70 */ short weapon;
	/* this+ 72 */ short accessory;
	/* this+ 74 */ short accessory2;
	/* this+ 76 */ short accessory3;
	/* this+ 78 */ short headpalette;
	/* this+ 80 */ short bodypalette;
	/* this+ 82 */ short cookMastery;
	/* this+ 84 */ char mapname[16];
	/* this+100 */ char restartMapName[16];
	/* this+116 */ unsigned char Str;
	/* this+117 */ unsigned char Agi;
	/* this+118 */ unsigned char Vit;
	/* this+119 */ unsigned char Int;
	/* this+120 */ unsigned char Dex;
	/* this+121 */ unsigned char Luk;
	/* this+122 */ unsigned char haircolor;
	/* this+123 */ struct tagParty { unsigned char Config; } Party;
	/* this+124 */ bool bOpenEquipmentWin;
	/* this+125 */ short font;
	/* this+127 */ char ZenyCheckSum[4];
	/* this+131 */ short robe;
};
C_ASSERT( sizeof CHARINFO_TO_CHARACTERDB == 133 );
#pragma pack(pop)


#pragma pack(push,1)
struct CHARINFO_FROM_CHARACTERDB
{
	/* this+  0 */ int GID;
	/* this+  4 */ int exp;
	/* this+  8 */ int AID;
	/* this+ 12 */ int GuildID;
	/* this+ 16 */ int money;
	/* this+ 20 */ int jobexp;
	/* this+ 24 */ int joblevel;
	/* this+ 28 */ int bodystate;
	/* this+ 32 */ int healthstate;
	/* this+ 36 */ int effectstate;
	/* this+ 40 */ int virtue;
	/* this+ 44 */ int honor;
	/* this+ 48 */ int hp;
	/* this+ 52 */ short maxhp;
	/* this+ 54 */ short sp;
	/* this+ 56 */ short maxsp;
	/* this+ 58 */ short xPos;
	/* this+ 60 */ short yPos;
	/* this+ 62 */ short speed;
	/* this+ 64 */ short jobpoint;
	/* this+ 66 */ short sxPos;
	/* this+ 68 */ short syPos;
	/* this+ 70 */ short head;
	/* this+ 72 */ short weapon;
	/* this+ 74 */ short accessory;
	/* this+ 76 */ short accessory2;
	/* this+ 78 */ short accessory3;
	/* this+ 80 */ short headpalette;
	/* this+ 82 */ short bodypalette;
	/* this+ 84 */ short cookMastery;
	/* this+ 86 */ char name[24];
	/* this+110 */ char mapname[16];
	/* this+126 */ char restartMapName[16];
	/* this+142 */ short job;
	/* this+144 */ short clevel;
	/* this+146 */ short sppoint;
	/* this+148 */ char Str;
	/* this+149 */ char Agi;
	/* this+150 */ char Vit;
	/* this+151 */ char Int;
	/* this+152 */ char Dex;
	/* this+153 */ char Luk;
	/* this+154 */ char CharNum;
	/* this+155 */ unsigned char haircolor;
	/* this+156 */ struct tagParty { unsigned char Config; } Party;
	/* this+157 */ bool bOpenEquipmentWin;
	/* this+158 */ short font;
	/* this+160 */ char ZenyCheckSum[4];
	/* this+164 */ short robe;
};
C_ASSERT( sizeof CHARINFO_FROM_CHARACTERDB == 166 );
#pragma pack(pop)


struct PCBANG_INFO
{
	/* this+ 0 */ BOOL isPCBang;
	/* this+ 4 */ int PayType;
	/* this+ 8 */ int ConnectionArea;
	/* this+12 */ int ConnectionState;
	/* this+16 */ int EventNum;
	/* this+20 */ unsigned long ConnectionTime;
	/* this+24 */ float ExpFactor;
	/* this+28 */ float ExpFactor2;
	/* this+32 */ float DropFactor;
	/* this+36 */ int NotifyToClientCnt;
	/* this+40 */ int PremiumType;
	/* this+44 */ int PremiumType2;
};


class CPC : public CActor
{
public:
	//...
	void AsyncSaveCart();
	//...
	void AsyncLoadCart(CCharacter* const in_pSender);
	//...
	void AsyncDBComplete_LoadCart(int in_SKLevel, const unsigned char* in_pData, int in_Length);
	//...
	virtual unsigned long GetAccountID();
	const char* GetAccountName() const;
	//...
	virtual int OnMsg(CCharacter* sender, CCharacter* receiver, unsigned long msgID, int par1, int par2, int par3, MSGpar::CVar par4);
	//...
	int IsSendable();
	bool IsSendable2(const int in_Bytes);
	//...
	unsigned long GetCharacterID();
	//...
	BOOL IsPKModeON();
	//...
	BOOL IsValid();
	void SetValid(const BOOL flag);
	//...
	virtual void Send(int len, const char* buf);
//	bool Send2(const unsigned char* , const int );
	void ForceSend(int len, char* buf);
	//...
	char* GetCharacterName();
	//...
	PCBANG_INFO* GetPcBangInfo();
	BOOL IsPcBang();
	//...
	virtual int SetEffective(int index, int time, int val1, int val2, int val3, int isSendClient);
	//...
private:
	void MultiCastStateInfo();
	//...
public:
	void GetEfstListDBFmt_And_UpdateResetFlag(std::vector<Effect3rd::tagEffect3rdDBFmt>& io_List, const bool in_bKeepDeleteDBWhenResetFlag);
	//...

public:
	/* this+   0 */ //CActor baseclass_0;
	/* this+1276 */ BYTE m_1276[664];
	/* this+1940 */ CharacterInfo m_characterInfo;
	/* this+3044 */ BYTE m_3044[148];
private:
	/* this+3192 */ BOOL m_isValid;
	/* this+3196 */ PCBANG_INFO m_PCBangInfo;
public:
	/* this+3244 */ BOOL m_isPKModeON;
	/* this+3248 */ BYTE m_3248[4632];
	/* this+7880 */ DWORD m_lastSendTime;
	/* this+7884 */ DWORD m_loadingCompleteTime;
	/* this+7888 */ DWORD m_DisconnetTime;
	/* this+7892 */ BYTE m_7892[684];
};
C_ASSERT( sizeof CPC == 8576 );
