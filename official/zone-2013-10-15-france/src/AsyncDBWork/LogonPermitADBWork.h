#pragma once
#include "HomunDataStuff.h"
#include "MercenaryDB.h"
#include "MercenaryDBV2.h"
#include "NPCElemental.h"
#include "PCBattleMercenary.h"
#include "Struct.h"
#include "AsyncDBWork/Effect3rd.h"
#include "AsyncDBWork/NAsyncDBWork.h"


namespace CLogonPermitADBWorkStuff {
class CElementalData
{
public:
	/* this+ 0 */ int m_Kind;
	/* this+ 4 */ int m_Scale;
	/* this+ 8 */ ElementalStuff::ESummaryData m_SummaryData;
	/* this+52 */ std::vector<Effect3rd::tagEffect3rdDBFmt> m_EfstList;

public:
	void Init() { m_Kind = 0; m_Scale = 0; }
	bool isExist(); //TODO

public:
	CElementalData() { }
	~CElementalData() { }
};
}; // namespace


class CLogonPermitADBWork : public NAsyncDBWork
{
public:
	enum enumResult
	{
		RESULT_SUCCESS                        = 0,
		RESULT_ERROR_UNKNOWN                  = 1,
		RESULT_ERROR_LOAD_BODYITEM            = 2,
		RESULT_ERROR_LOAD_BODYITEM_INSERT     = 3,
		RESULT_ERROR_LOAD_CHARACTERINFO       = 4,
		RESULT_ERROR_LOAD_MERCENARY_OWNER     = 5,
		RESULT_ERROR_LOAD_MERCENARY_INFO      = 6,
		RESULT_ERROR_LOAD_MERCENARY_EFFECT    = 7,
		RESULT_ERROR_LOAD_MERCENARY_STATE     = 8,
		RESULT_ERROR_LOAD_SKILL               = 9,
		RESULT_ERROR_LOAD_SKILL_INSERT        = 10,
		RESULT_ERROR_LOAD_EFFECITVE           = 11,
		RESULT_ERROR_LOAD_EFFECTIVE_INSERT    = 12,
		RESULT_ERROR_LOAD_STATE               = 13,
		RESULT_ERROR_LOAD_STATE_INSERT        = 14,
		RESULT_ERROR_LOAD_HOMUN               = 15,
		RESULT_ERROR_LOAD_HOMUN_EFFECT        = 16,
		RESULT_ERROR_LOAD_HOMUN_EFFECT_DELETE = 17,
		RESULT_ERROR_LOAD_HOMUN_SKILL         = 18,
		RESULT_ERROR_LOAD_QUESTEVENT          = 19,
		RESULT_ERROR_LOAD_QUESTEVENT_INSERT   = 20,
		RESULT_ERROR_LOAD_BATTLEFIELD         = 21,
		RESULT_ERROR_LOAD_ELEMENTAL           = 22,
		RESULT_ERROR_LOAD_IRINVENTORY         = 23,
		RESULT_ERROR_LOAD_IRQUEST             = 24,
		RESULT_ERROR_LOAD_USERCONFIGDATA      = 25,
		REULST_ERROR_INSERT_ZENY_LOG          = 26,
	};
///
	class CBodyItemData
	{
	public:
		/* this+0 */ int m_length;
		/* this+4 */ unsigned char m_Data[16300];

	public:
		void Init() { m_length = 0; }

	public:
		CBodyItemData() { Init(); }
		~CBodyItemData() { }
	};
///
	class CCharacterInfoData
	{
	public:
		/* this+0 */ CHARINFO_FROM_CHARACTERDB m_data;

	public:
		CCharacterInfoData() { }
		~CCharacterInfoData() { }
	};
///
	class CSkill3rdData
	{
	public:
		struct tagSkill
		{
			/* this+ 0 */ int ID;
			/* this+ 4 */ int Level;
			/* this+ 8 */ int RemainMS;
			/* this+12 */ int Data;

			tagSkill(); //TODO
		};

		typedef std::vector<tagSkill> SKILL3RDLIST;
		/* this+0 */ SKILL3RDLIST m_List;

	public:
		int GetTotalFirstJobSkillLevel(const int in_Job);
		int GetTotalSecondJobSkillLevel(const int in_Job);

	public:
		void Init() { m_List.clear(); }

	public:
		CSkill3rdData() { Init(); }
	};
///
	class CEffect3rd
	{
	public:
		/* this+ 0 */ std::vector<Effect3rd::tagEffect3rdDBFmt> m_List;
		/* this+16 */ bool m_bConvertLowerVer;

	public:
		void Init() { m_bConvertLowerVer = false; m_List.clear(); }

	public:
		CEffect3rd() { Init(); }
	};
///
	class CStateData
	{
	public:
		/* this+  0 */ unsigned char m_Data[512];
		/* this+512 */ int m_Length;

	public:
		void Init() { m_Length = 0; }

	public:
		CStateData() { Init(); }
		~CStateData() { }
	};
///
	class CMercenaryData
	{
	public:
		/* this+   0 */ CPCBattleMercenary::tagDBData m_Owner;
		/* this+  28 */ CMercenaryDBV2::DBINFO m_Info;
		/* this+  68 */ unsigned char m_EffectData[512];
		/* this+ 580 */ int m_EffectLength;
		/* this+ 584 */ unsigned char m_StateData[512];
		/* this+1096 */ int m_StateLength;

	public:
		void Init() { m_EffectLength = 0; m_StateLength = 0; }

	public:
		CMercenaryData() { }
		~CMercenaryData() { }
	};
///
	class CHomunLogonData : public HomunDataStuff::CHomunData
	{
	public:
		/* this+  0 */ //HomunDataStuff::CHomunData baseclass_0;
		/* this+ 40 */ HOMUN_DBINFO m_Data;
		/* this+116 */ bool m_bLowerVersion;

	public:
		void Init() { this->HomunDataStuff::CHomunData::Init(); memset(&m_Data, 0, sizeof(m_Data)); m_bLowerVersion = false; }

	public:
		CHomunLogonData() { }
		virtual ~CHomunLogonData() { }
	};
///
	class CQuestEventData
	{
	public:
		/* this+    0 */ int m_questEvent_Length;
		/* this+    4 */ int m_completeQuest_Length;
		/* this+    8 */ int m_quest_hunt_Length;
		/* this+   12 */ int m_quest_time_Length;
		/* this+   16 */ unsigned char m_questEvent_Data[8000];
		/* this+ 8016 */ unsigned char m_completeQuest_Data[4000];
		/* this+12016 */ unsigned char m_quest_hunt_Data[8000];
		/* this+20016 */ unsigned char m_quest_time_Data[4000];

	public:
		void Init() { m_questEvent_Length = 0; m_completeQuest_Length = 0; m_quest_hunt_Length = 0; m_quest_time_Length = 0; }

	public:
		CQuestEventData() { Init(); }
		~CQuestEventData() { }
	};
///
	class CBattleFieldData
	{
	public:
		/* this+0 */ char m_campID;
		/* this+2 */ short m_x;
		/* this+4 */ short m_y;

	public:
		void Init() { m_campID = 0; m_x = 0; m_y = 0; }

	public:
		CBattleFieldData() { Init(); }
		~CBattleFieldData() { }
	};
///
	struct CoupleInfo
	{
	public:
		/* this+ 0 */ unsigned long MaleGID;
		/* this+ 4 */ unsigned long FemaleGID;
		/* this+ 8 */ char MaleName[24];
		/* this+32 */ char FemaleName[24];
		/* this+56 */ SYSTEMTIME WeddingTime;

	public:
		void Init() { MaleGID = 0; FemaleGID = 0; memset(MaleName, '\0', sizeof(MaleName)); memset(FemaleName, '\0', sizeof(FemaleName)); memset(&WeddingTime, 0, sizeof(WeddingTime)); }

	public:
		CoupleInfo() { Init(); }
	};
///
	struct FamilyInfo
	{
	public:
		/* this+ 0 */ unsigned long index;
		/* this+ 4 */ unsigned long father_GID;
		/* this+ 8 */ unsigned long mother_GID;
		/* this+12 */ unsigned long baby_GID;
		/* this+16 */ char FatherName[24];
		/* this+40 */ char motherName[24];
		/* this+64 */ char babyName[24];
		/* this+88 */ SYSTEMTIME Time;

	public:
		void Init() { index = 0; father_GID = 0; mother_GID = 0; baby_GID = 0; memset(FatherName, '\0', sizeof(FatherName)); memset(motherName, '\0', sizeof(motherName)); memset(&Time, 0, sizeof(Time)); }

	public:
		FamilyInfo() { Init(); }
	};
///
private:
	/* this+ 0 */ //NAsyncDBWork baseclass_0;
	/* this+20 */ unsigned long m_AID;
	/* this+24 */ unsigned long m_GID;
	/* this+28 */ short m_SelectedCharNum;
	/* this+30 */ char m_Sex;
	/* this+31 */ char m_IDstr[24];
	/* this+56 */ DWORD m_TotalUsingTime;
	/* this+60 */ enumResult m_Result;

public:
	const unsigned long GetGID() const;
	const unsigned long GetAID() const;
	char GetSex() const;
	const char* GetIDstr() const;
	const DWORD GettotalUsingTime() const;
	const int GetSelectedCharNum() const;
	const enumResult GetResult() const;

public:
	/* this+   64 */ CLogonPermitADBWork::CBodyItemData m_BodyItemInfo;
	/* this+16368 */ CLogonPermitADBWork::CCharacterInfoData m_CharacterInfo;
	/* this+16536 */ CLogonPermitADBWork::CSkill3rdData m_Skill3rdData;
	/* this+16552 */ CLogonPermitADBWork::CMercenaryData m_MercenaryData;
	/* this+17652 */ CLogonPermitADBWork::CEffect3rd m_Effect3rd;
	/* this+17672 */ CLogonPermitADBWork::CStateData m_StateData;
	/* this+18188 */ CLogonPermitADBWork::CHomunLogonData m_HomunData;
	/* this+18308 */ CLogonPermitADBWork::CQuestEventData m_questData;
	/* this+42324 */ CLogonPermitADBWork::CBattleFieldData m_battleFieldData;
	/* this+42332 */ CLogonPermitADBWorkStuff::CElementalData m_Elemental;
	/* this+42400 */ CLogonPermitADBWork::CoupleInfo m_CoupleInfo;
	/* this+42472 */ CLogonPermitADBWork::FamilyInfo m_FamilyInfo;

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);
//	enumRETURN LoadBodyItemInfo(NODBCCtrl& );
//	enumRETURN InsertBodyItem(NODBCCtrl& );
//	enumRETURN LoadCharacterInfo(NODBCCtrl& );
//	enumRETURN Skill3rd_Load(NODBCCtrl& );
//	enumRETURN Skill3rd_Load_LowerVer(NODBCCtrl& );
//	struct tagWARPPORTALINFO { struct { char mapName[16]; short xPos; short yPos; } Warp[3]; };
//	enumRETURN Skill3rd_Load_WarpInfo(NODBCCtrl& , const unsigned long , tagWARPPORTALINFO& );
//	enumRETURN Skill3rd_Delete_LowerVer(NODBCCtrl& );
//	enumRETURN Skill3rd_InsertAll(NODBCCtrl& );
//	enumRETURN InsertSkillData(NODBCCtrl& );
//	enumRETURN LoadMercenaryData_Owner(NODBCCtrl& );
//	enumRETURN LoadMercenaryData_Info(NODBCCtrl& );
//	enumRETURN LoadMercenaryData_Effect(NODBCCtrl& );
//	enumRETURN LoadMercenaryData_State(NODBCCtrl& );
//	enumRETURN Effect3rd_Load(NODBCCtrl& );
//	enumRETURN Effect3rd_Load_LowerVer(NODBCCtrl& );
//	enumRETURN Effect3rd_Delete_LowerVer(NODBCCtrl& );
//	enumRETURN LoadStateData(NODBCCtrl& );
//	enumRETURN InsertStateData(NODBCCtrl& );
//	std::pair<bool,bool> ExecQuery_Homun(NODBCCtrl& );
//	enumRETURN LoadHomunData(NODBCCtrl& );
//	enumRETURN LoadHomunData_Effect(NODBCCtrl& );
//	enumRETURN LoadHomunData_Skill(NODBCCtrl& );
//	enumRETURN LoadHomunData_Skill_LowerVer(NODBCCtrl& );
	enumRETURN LoadQuestEventInfo(NODBCCtrl& in_ODBCCtrl);
//	enumRETURN InsertQuestEvent(NODBCCtrl& );
//	enumRETURN LoadBattleFieldInfo(NODBCCtrl& );
//	enumRETURN LoadCoupleInfo(NODBCCtrl& );
//	enumRETURN LoadFamilyInfo(NODBCCtrl& );

public:
	void Init(const unsigned long in_AID, const unsigned long in_GID, const int in_SelectedCharNum, const char* in_pIDstr, const DWORD in_TotalUsingTime, const char in_Sex);

private:
	CLogonPermitADBWork();
	virtual ~CLogonPermitADBWork();

	template<typename T> friend class CObjectRecycleMgr;
};
