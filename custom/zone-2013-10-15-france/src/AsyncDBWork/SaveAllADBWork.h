#pragma once
#include "HomunDataStuff.h" // HomunDataStuff::CHomunData
#include "MercenaryDBV2.h" // CMercenaryDBV2::DBINFO
#include "NPCElemental.h" // ElementalStuff::ESummaryData
#include "PC.h" // CHARINFO_TO_CHARACTERDB
#include "PCBattleMercenary.h" // CPCBattleMercenary::tagDBData
#include "ZoneProcess.h" // WARP_POSITION
#include "AsyncDBWork/Effect3rd.h" // Effect3rd::tagEffect3rdDBFmt
#include "AsyncDBWork/NAsyncDBWork.h"


namespace CSaveAllADBWorkStuff {
class CElementalData
{
public:
	/* this+ 0 */ bool m_bExist;
	/* this+ 4 */ class ElementalStuff::ESummaryData m_SummaryData;
	/* this+48 */ std::vector<Effect3rd::tagEffect3rdDBFmt> m_EfstList;

public:
	void Init()
	{
		m_bExist = false;
		m_EfstList.clear();
	}

	bool isExist()
	{
		return m_bExist;
	}

public:
//	CElementalData(); //TODO
//	~CElementalData(); //TODO
};
}; // namespace


class CSaveAllADBWork : public NAsyncDBWork
{
public:
	class CCartItemData
	{
	public:
		/* this+    0 */ unsigned char m_Data[16300];
		/* this+16300 */ int m_Length;
		/* this+16304 */ bool m_bActive;

	public:
//		void Init(); //TODO

	public:
//		CCartItemData(); //TODO
//		~CCartItemData(); //TODO
	};

	class CStoreItemData
	{
	public:
		/* this+    0 */ unsigned char m_Data[16300];
		/* this+16300 */ int m_Length;
		/* this+16304 */ bool m_bActive;

	public:
//		void Init(); //TODO

	public:
//		CStoreItemData(); //TODO
//		~CStoreItemData(); //TODO
	};

	class CBodyItemData
	{
	public:
		/* this+    0 */ int m_Length;
		/* this+    4 */ unsigned char m_data[16300];
		/* this+16304 */ bool m_bActive;

	public:
//		void Init(); //TODO

	public:
//		CBodyItemData(); //TODO
//		~CBodyItemData(); //TODO
	};

	class CCharacterData
	{
	public:
		/* this+  0 */ bool m_bActive;
		/* this+  1 */ CHARINFO_TO_CHARACTERDB m_data;
		/* this+134 */ char m_characterName[24];

	public:
//		void Init(); //TODO

	public:
//		CCharacterData(); //TODO
//		~CCharacterData(); //TODO
	};

	class CMercenaryData
	{
	public:
		class COwner
		{
		public:
			/* this+ 0 */ CPCBattleMercenary::tagDBData m_data;
			/* this+28 */ bool m_bActive;

		public:
//			void Init(); //TODO

		public:
//			COwner(); //TODO
//			~COwner(); //TODO
		};

		class CCharacter
		{
		public:
			/* this+   0 */ bool m_bActive;
			/* this+   4 */ CMercenaryDBV2::DBINFO m_Info;
			/* this+  44 */ unsigned char m_EffectData[512];
			/* this+ 556 */ int m_EffectLength;
			/* this+ 560 */ unsigned char m_StateData[512];
			/* this+1072 */ int m_StateLength;

		public:
//			void Init(); //TODO

		public:
//			CCharacter(); //TODO
//			~CCharacter(); //TODO
		};

	public:
		/* this+ 0 */ CMercenaryData::COwner m_Owner;
		/* this+32 */ CMercenaryData::CCharacter m_Character;

	public:
//		void Init(); //TODO

	public:
//		CMercenaryData(); //TODO
//		~CMercenaryData(); //TODO
	};

	class CEffect3rd
	{
	public:
		/* this+0 */ std::vector<Effect3rd::tagEffect3rdDBFmt> m_List;

	public:
//		void Init(); //TODO

	public:
//		CEffect3rd(); //TODO
//		~CEffect3rd(); //TODO
	};

	class CStateData
	{
	public:
		/* this+  0 */ bool m_bActive;
		/* this+  1 */ unsigned char m_Data[512];
		/* this+516 */ int m_Length;

	public:
//		void Init(); //TODO

	public:
//		CStateData(); //TODO
//		~CStateData(); //TODO
	};

	class CQuestEventData
	{
	public:
		/* this+    0 */ bool m_isUpdate;
		/* this+    4 */ int m_length_quest;
		/* this+    8 */ int m_length_hunt;
		/* this+   12 */ int m_length_time;
		/* this+   16 */ int m_length_complete;
		/* this+   20 */ unsigned char m_data_quset[8000];
		/* this+ 8020 */ unsigned char m_data_hunt[8000];
		/* this+16020 */ unsigned char m_data_time[8000];
		/* this+24020 */ unsigned char m_data_complete[4000];

	public:
//		void Init(); //TODO

	public:
//		CQuestEventData(); //TODO
//		~CQuestEventData(); //TODO
	};

	class CMapMoveOtherSvr
	{
	public:
		/* this+0 */ unsigned long m_NID;
		/* this+4 */ unsigned long m_TargetSvrID;

	public:
//		void Init(); //TODO

	public:
//		CMapMoveOtherSvr(); //TODO
//		~CMapMoveOtherSvr(); //TODO
	};

	class CSkill3rdData
	{
	public:
		struct tagSkill
		{
			/* this+ 0 */ int ID;
			/* this+ 4 */ int Level;
			/* this+ 8 */ int RemainMS;
			/* this+12 */ int Data;

//			tagSkill(const int, const int, const int, const int); //TODO
		};

	public:
		typedef class std::vector<tagSkill> SKILL3RDLIST;
		/* this+0 */ SKILL3RDLIST m_List;

	public:
//		void Init(); //TODOs

	public:
//		CSkill3rdData(); //TODO
//		~CSkill3rdData(); //TODO
	};

	class CWarpInfoData
	{
	public:
		void Init();

	public:
		void SetWarpInfo(const std::deque<WARP_POSITION>& in_WarpInfo);
		const std::vector<WARP_POSITION>& GetWarpInfo();

	public:
//		CWarpInfoData(); //TODO
//		~CWarpInfoData(); //TODO

	private:
		/* this+0 */ std::vector<WARP_POSITION> m_WarpInfo;
	};

public:
	enum enumResult
	{
		RESULT_SUCCESS                     = 0,
		RESULT_ERROR_UNKNOWN               = 1,
		RESULT_ERROR_SAVE_BODYITEM         = 2,
		RESULT_ERROR_SAVE_CHARINFO         = 3,
		RESULT_ERROR_SAVE_MERCENARY_OWNER  = 4,
		RESULT_ERROR_SAVE_MERCENARY_INFO   = 5,
		RESULT_ERROR_SAVE_MERCENARY_EFFECT = 6,
		RESULT_ERROR_SAVE_MERCENARY_STATE  = 7,
		RESULT_ERROR_SAVE_EFFECTIVE        = 8,
		RESULT_ERROR_SAVE_STATE            = 9,
		RESULT_ERROR_SAVE_STOREITEM        = 10,
		RESULT_ERROR_SAVE_CART             = 11,
		RESULT_ERROR_SAVE_QUESTEVENT       = 12,
		RESULT_ERROR_SAVE_SKILL            = 13,
		RESULT_ERROR_SAVE_ELEMENTAL        = 14,
		RESULT_ERROR_SAVE_HOMUN            = 15,
		RESULT_ERROR_SAVE_IRINVENTORY      = 16,
		RESULT_ERROR_SAVE_USERCONFIGDATA   = 17,
		RESULT_ERROR_SAVE_WARPINFODATA     = 18,
	};

	enum enumAfterAction
	{
		AFTER_ACTION_DISCONNECT          = 0,
		AFTER_ACTION_QUIT_EXIT           = 1,
		AFTER_ACTION_MAPMOVE_OTHERSERVER = 2,
		AFTER_ACTION_NONE                = 3,
		AFTER_ACTION_ANYTIME             = 4,
		AFTER_ACTION_XXX                 = 5,
	};

private:
	/* this+    0 */ //NAsyncDBWork baseclass_0;
	/* this+   20 */ unsigned long m_AID;
	/* this+   24 */ unsigned long m_GID;
	/* this+   28 */ enumResult m_Result;
	/* this+   32 */ enumAfterAction m_AfterAction;
public:
	/* this+   36 */ CCharacterData m_CharacterData;
	/* this+  196 */ CMapMoveOtherSvr m_MapMoveOtherSvr;
	/* this+  204 */ CWarpInfoData m_WaprpInfoData;
	/* this+  220 */ CBodyItemData m_BodyItemData;
	/* this+16528 */ CStoreItemData m_StoreItemData;
	/* this+32836 */ CEffect3rd m_Effect3rd;
	/* this+32852 */ CCartItemData m_CartItemData;
	/* this+49160 */ CStateData m_StateData;
	/* this+49680 */ CMercenaryData m_MercenaryData;
	/* this+50788 */ CSaveAllADBWorkStuff::CElementalData m_ElementalData;
	/* this+50852 */ CQuestEventData m_questEventData;
	/* this+78872 */ CSkill3rdData m_Skill;
	/* this+78888 */ HomunDataStuff::CHomunData m_HomunData;

private:
	virtual bool ExecQuery(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN SaveMercenaryData_Owner(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN SaveMercenaryData_Info(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN SaveMercenaryData_Effect(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN SaveMercenaryData_State(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN SaveStateData(NODBCCtrl& in_ODBCCtrl);
	NAsyncDBWork::enumRETURN SaveSkill(NODBCCtrl& in_ODBCCtrl);

public:
	const unsigned long GetGID() const;
	const unsigned long GetAID() const;
	const enumAfterAction GetAfterAction() const;

public:
	void Init(const enumAfterAction in_AfterAction, const unsigned long in_AID, const unsigned long in_GID);

private:
	CSaveAllADBWork();
	virtual ~CSaveAllADBWork();
};
C_ASSERT( sizeof CSaveAllADBWork == 78928 );
