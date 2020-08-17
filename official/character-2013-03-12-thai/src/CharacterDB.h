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
	/* this+228 */ int m_bIsChangedCharName;
	/* this+232 */ int m_nRobe;
};


class CCharacterDBBase : public CDatabase
{
public:
	CCharacterDBBase(const char* in_szpFileDSNFileName);
	virtual ~CCharacterDBBase();
	int GetCharInfo(int nAID, SCHARINFO* pCharInfo, bool bTranslateOpt, int nMaxCharInfoCount);
	BOOL DeleteCharInfo(int nGID);
	void SetPwd(const char* in_szPwd);
	bool Connect();
	void VeryfyConnection();
	bool IsConnected();

protected:
	bool IsOnline();

protected:
	/* this+  0 */ //const CCharacterDBBase::`vftable';
	/* this+  4 */ //CDatabase baseclass_4;
	/* this+ 40 */ const std::string m_strFileDSNfileName;
	/* this+ 68 */ std::string m_strPwd;
	/* this+ 96 */ bool m_bIsConnected;
	/* this+100 */ int m_bExistColumn_bIsChangedCharName;
	/* this+104 */ CCriticalSection m_csCharacterDB;
};


class CCharacterDB : public CCharacterDBBase, public CSingleton<CCharacterDB>
{
public:
	CCharacterDB();
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
//	int GetAllGIDs(unsigned long, unsigned long*, int);
//	int GetAID(unsigned long);
	void DelegateGuildMaster(int nGDID);
//	void DeleteGuildMInfoByGDID(int);
//	void DeleteGuild(int);
//	void DeleteGuildAllyInfo(int);
//	void DeleteGuildBanishInfo(int);
//	void DeleteGuildMPosition(int);
//	void DeleteGuildNotice(int);
//	void DeleteGuildSkill(int);
	void DeleteGuildMInfo(int nGDID);
//	bool UpdateDeleteReservedDate(const int, const int, const long);
	void UpdateCharStartMap(int nGID);
//	void UpdateMapInfo(int, const char *, int, int);
//	void UpdateRestartMapInfo(int, const char *, int, int);
//	void UpdateCharNum(unsigned long, int);
//	void UpdateChangedCharName(unsigned long &, int);
//	int UpdateCharName(unsigned long &, char *);
//	int GetCharBlock(int, struct TAG_CHARACTER_BLOCK_INFO *, const int);
//	void DeleteCharBlock(int);
//	bool GetCharacterNameByGID(int, char *);
//	int GetIsChangedCharName(unsigned long);
	bool IsUsingCharacterPassword();
//	int IsValidCharName(char *, int *);
	bool CheckCharacterPassword(const int iGID, const int iCharacterPassword);
	bool UpdateCharacterPassword(const int iGID, const int iOldPassword, const int iNewPassword);
//	int CharCopyWorldToWorld(char *, int, int);
//	void UpdateMapName(const int, const char *, const int, const int);
//	void UpdateMapName(int);
//	void UpdateMapName(int, const char *);
//	bool UpdateAccessibleMapName(int, const char *, unsigned int, unsigned int);
//	int IsExistColumn(const char *, const char *);
//	int IsExistColumn_bIsChangedCharName();
//	int GetCharacterCount(unsigned long);

private:
	/* this+  0 */ //CCharacterDBBase baseclass_0;
	/* this+128 */ //CSingleton<CCharacterDB> baseclass_128;
};


class CPVPCharacterDB : public CCharacterDBBase, public CSingleton<CPVPCharacterDB>
{
public:
	CPVPCharacterDB();
	void MakeSkill(int nGID, char* skillInfo, long SkillSize);
	void MakeItem(int nGID, char* itemInfo, long ItemSize);
	BOOL CopyCharInfo(SCHARINFO* pCharInfo);

private:
	/* this+  0 */ //CCharacterDBBase baseclass_0;
	/* this+128 */ //CSingleton<CPVPCharacterDB> baseclass_128;
};


class CPvPPointDB : public CDatabase, public CSingleton<CPvPPointDB>
{
public:
	BOOL InitPoint(unsigned long AID, const char* newCharName);
	void SetPwd(const char* in_szPwd);
	bool Connect();

private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+37 */ //CSingleton<CPvPPointDB> baseclass_37;
	/* this+40 */ CCriticalSection m_CS;
	/* this+64 */ std::string m_strPwd;
	/* static  */ static const std::string m_strFileDSNfileName;
};
