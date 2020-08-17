#pragma once
#include "Common/CriticalSection.h"
#include "Common/Database.h"
#include "Common/Singleton.h"


struct SCHARINFO
{
	/* this+  0 */ int m_nGID;
	/* this+  4 */ int m_nExp;
	/* this+  8 */ int m_nAID;
	/* this+ 12 */ int m_nGuildID;
	/* this+ 16 */ int m_nMoney;
	/* this+ 20 */ int m_nJobExp;
	/* this+ 24 */ int m_nJobLevel;
	/* this+ 28 */ int m_nBodyState;
	/* this+ 32 */ int m_nHealthState;
	/* this+ 36 */ int m_nEffectState;
	/* this+ 40 */ int m_nVirtue;
	/* this+ 44 */ int m_nHonor;
	/* this+ 48 */ int m_nHp;
	/* this+ 52 */ int m_nMaxHp;
	/* this+ 56 */ int m_nSp;
	/* this+ 60 */ int m_nMaxSp;
	/* this+ 64 */ int m_nXPos;
	/* this+ 68 */ int m_nYPos;
	/* this+ 72 */ int m_nSpeed;
	/* this+ 76 */ int m_nJobPoint;
	/* this+ 80 */ int m_nSxPos;
	/* this+ 84 */ int m_nSyPos;
	/* this+ 88 */ int m_nHead;
	/* this+ 92 */ int m_nWeapon;
	/* this+ 96 */ int m_nAccessory;
	/* this+100 */ int m_nAccessory2;
	/* this+104 */ int m_nAccessory3;
	/* this+108 */ int m_nHeadPalette;
	/* this+112 */ int m_nBodyPalette;
	/* this+116 */ int m_nShield;
	/* this+120 */ char m_szName[26];
	/* this+146 */ char m_szMapName[18];
	/* this+164 */ char m_szRestartMapName[18];
	/* this+184 */ int m_nJob;
	/* this+188 */ int m_nCLevel;
	/* this+192 */ int m_nSpPoint;
	/* this+196 */ int m_nStr;
	/* this+200 */ int m_nAgi;
	/* this+204 */ int m_nVit;
	/* this+208 */ int m_nInt;
	/* this+212 */ int m_nDex;
	/* this+216 */ int m_nLuk;
	/* this+220 */ int m_nSlotIndex;
	/* this+224 */ int m_nHairColor;
};


class CCharacterDBBase : public CDatabase
{
public:
	CCharacterDBBase();
	virtual ~CCharacterDBBase();
	int GetCharInfo(int nAID, SCHARINFO* pCharInfo, bool bTranslateOpt);
	BOOL DeleteCharInfo(int nGID);
	void InitProp(const char* szID, const char* szPassWord, const char* szDSN);
	void VeryfyConnection();
	bool IsConnected();

protected:
	bool IsOnline();

protected:
	/* this+   0 */ //const CCharacterDBBase::`vftable';
	/* this+   4 */ //CDatabase baseclass_4;
	/* this+2060 */ char m_szID[255];
	/* this+2315 */ char m_szPassWord[255];
	/* this+2570 */ char m_szDSN[255];
	/* this+2825 */ bool m_bIsConnected;
	/* this+2828 */ CCriticalSection m_csCharacterDB;
};


class CCharacterDB : public CCharacterDBBase, public CSingleton<CCharacterDB>
{
public:
	BOOL GetCharInfoByGID(int nGID, SCHARINFO* pCharinfo);
	int DeleteGroupMember(int nGID);
	int GetGroupID(int nGID);
	void DeleteGroup(int nGRID);
	int GetGroupMemberCount(int nGRID);
	BOOL MakeCharInfo(SCHARINFO* pCharInfo);
	BOOL GetGuildMemberPositionID(int nGID, int* PositionID);
	BOOL GetGuildIDByGID(int nGID, int* GDID);
	BOOL GetSkill(int nGID, char* skillInfo, SQLINTEGER* outSkillSize);
	BOOL GetItem(int nGID, char* itemInfo, SQLINTEGER* outSkillSize);
	void DelegateGuildMaster(int nGDID);
//	void DeleteGuildMInfoByGDID(int);
//	void DeleteGuild(int);
//	void DeleteGuildAllyInfo(int);
//	void DeleteGuildBanishInfo(int);
//	void DeleteGuildMPosition(int);
//	void DeleteGuildNotice(int);
//	void DeleteGuildSkill(int);
	void DeleteGuildMInfo(int nGDID);
	void UpdateCharStartMap(int nGID);
//	void UpdateMapInfo(int, const char *, int, int);
//	void UpdateRestartMapInfo(int, const char *, int, int);
//	int UpdateCharName(unsigned long &, char *);
//	void UpdateChangedCharName(unsigned long &, int);
//	int GetCharBlock(int, TAG_CHARACTER_BLOCK_INFO *);
//	void DeleteCharBlock(int);
//	bool GetCharacterNameByGID(int, char *);
	bool IsUsingCharacterPassword();
//	int IsValidCharName(char *, int *);
//	int GetIsChangedCharName(unsigned long);
	bool CheckCharacterPassword(const int iGID, const int iCharacterPassword);
	bool UpdateCharacterPassword(const int iGID, const int iOldPassword, const int iNewPassword);
	void SetOnline(bool isOnline, int iAID = 0, int iGID = 0); /// @custom // [patch] update 'isonline' column

private:
	/* this+   0 */ //CCharacterDBBase baseclass_0;
	/* this+2852 */ //CSingleton<CCharacterDB> baseclass_2852;
};


class CPVPCharacterDB : public CCharacterDBBase, public CSingleton<CPVPCharacterDB>
{
public:
	void MakeSkill(int nGID, char* skillInfo, long SkillSize);
	void MakeItem(int nGID, char* itemInfo, long ItemSize);
	BOOL CopyCharInfo(SCHARINFO* pCharInfo);

private:
	/* this+   0 */ //CCharacterDBBase baseclass_0;
	/* this+2852 */ //CSingleton<CPVPCharacterDB> baseclass_2852;
};


class CPvPPointDB : public CDatabase, public CSingleton<CPvPPointDB>
{
public:
	BOOL InitPoint(unsigned long AID, const char* newCharName);

private:
	/* this+   0 */ //CDatabase baseclass_0;
	/* this+2056 */ //CSingleton<CPvPPointDB> baseclass_2056;
	/* this+2056 */ CCriticalSection m_CS;
};
