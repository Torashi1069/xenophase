#pragma once
#include "CMercenaryDBV2.hpp"
#include "CPCBattleMercenary.hpp"
#include "AsyncDBWork/NAsyncDBWork.h"
#include "struct.hpp"


class CSaveAllADBWork : public NAsyncDBWork
{
public:
	class CCartItemData
	{
		/* this+    0 */ public: unsigned char m_Data[16300];
		/* this+16300 */ public: int m_Length;
		/* this+16304 */ public: bool m_bActive;

		public: CCartItemData(void) : m_Length(0), m_bActive(false) {};
		public: ~CCartItemData(void) {};
	};

	class CStoreItemData
	{
		/* this+    0 */ public: unsigned char m_Data[16300];
		/* this+16300 */ public: int m_Length;
		/* this+16304 */ public: bool m_bActive;

		public: CStoreItemData(void) : m_Length(0), m_bActive(false) {};
		public: ~CStoreItemData(void) {};
	};

	class CBodyItemData
	{
		/* this+    0 */ public: int m_Length;
		/* this+    4 */ public: unsigned char m_data[16300];
		/* this+16304 */ public: bool m_bActive;

		public: CBodyItemData(void) : m_Length(0), m_bActive(false) {};
		public: ~CBodyItemData(void) {};
	};

	class CCharacterData
	{
		/* this+  0 */ public: bool m_bActive;
		/* this+  1 */ public: CHARINFO_TO_CHARACTERDB m_data;
		/* this+130 */ public: char m_characterName[24];

		public: CCharacterData(void) : m_bActive(0) {};
		public: ~CCharacterData(void) {};
	};

	class CMercenaryData
	{
		class COwner
		{
			/* this+ 0 */ public: CPCBattleMercenary::tagDBData m_data;
			/* this+28 */ public: bool m_bActive;

			public: COwner(void) : m_bActive(false) {};
			public: ~COwner(void) {};
		};

		class CCharacter
		{
			/* this+   0 */ public: bool m_bActive;
			/* this+   4 */ public: CMercenaryDBV2::DBINFO m_Info;
			/* this+  44 */ public: unsigned char m_EffectData[256];
			/* this+ 556 */ public: int m_EffectLength;
			/* this+ 560 */ public: unsigned char m_StateData[256];
			/* this+1072 */ public: int m_StateLength;

			public: CCharacter(void) : m_bActive(false) {};
			public: ~CCharacter(void) {};
		};

		/* this+ 0 */ public: CSaveAllADBWork::CMercenaryData::COwner m_Owner;
		/* this+32 */ public: CSaveAllADBWork::CMercenaryData::CCharacter m_Character;

		public: CMercenaryData(void) {};
		public: ~CMercenaryData(void) {};
	};

	class CEffectiveData
	{
		/* this+  0 */ public: bool m_bActive;
		/* this+  1 */ public: unsigned char m_Data[256];
		/* this+516 */ public: int m_Length;

		public: CEffectiveData(void) : m_bActive(false), m_Length(0) {};
		public: ~CEffectiveData(void) {};
	};

	class CStateData
	{
		/* this+  0 */ public: bool m_bActive;
		/* this+  1 */ public: unsigned char m_Data[256];
		/* this+516 */ public: int m_Length;

		public: CStateData(void) : m_bActive(false), m_Length(0) {};
		public: ~CStateData(void) {};
	};

	class CQuestEventData
	{
		/* this+    0 */ public: bool m_isUpdate;
		/* this+    4 */ public: int m_length_quest;
		/* this+    8 */ public: int m_length_hunt;
		/* this+   12 */ public: int m_length_time;
		/* this+   16 */ public: int m_length_complete;
		/* this+   20 */ public: unsigned char m_data_quset[8000];
		/* this+ 8020 */ public: unsigned char m_data_hunt[8000];
		/* this+16020 */ public: unsigned char m_data_time[8000];
		/* this+24020 */ public: unsigned char m_data_complete[4000];

		public: CQuestEventData(void) : m_isUpdate(false), m_length_quest(0), m_length_hunt(0), m_length_time(0), m_length_complete(0) {};
		public: ~CQuestEventData(void) {};
	};

	class CMapMoveOtherSvr
	{
		/* this+0 */ public: unsigned long m_NID;
		/* this+4 */ public: unsigned long m_TargetSvrID;

		public: CMapMoveOtherSvr(void) : m_NID(0), m_TargetSvrID(0) {};
		public: ~CMapMoveOtherSvr(void) {};
	};

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

	struct vtable_t //const CSaveAllADBWork::`vftable'
	{
		bool (CSaveAllADBWork::* ExecQuery)(NODBCCtrl& in_ODBCCtrl);
		void* (CSaveAllADBWork::* scalar_deleting_destructor)(unsigned int);
	};

	/* this+    0 */ public: //NAsyncDBWork baseclass_0;
	/* this+   20 */ private: const unsigned long m_AID;
	/* this+   24 */ private: const unsigned long m_GID;
	/* this+   28 */ private: enum CSaveAllADBWork::enumResult m_Result;
	/* this+   32 */ private: const enum CSaveAllADBWork::enumAfterAction m_AfterAction;
	/* this+   36 */ public: CSaveAllADBWork::CCharacterData m_CharacterData;
	/* this+  192 */ public: CSaveAllADBWork::CMapMoveOtherSvr m_MapMoveOtherSvr;
	/* this+  200 */ public: CSaveAllADBWork::CBodyItemData m_BodyItemData;
	/* this+16508 */ public: CSaveAllADBWork::CStoreItemData m_StoreItemData;
	/* this+32816 */ public: CSaveAllADBWork::CEffectiveData m_EffectiveData;
	/* this+33336 */ public: CSaveAllADBWork::CCartItemData m_CartItemData;
	/* this+49644 */ public: CSaveAllADBWork::CStateData m_StateData;
	/* this+50164 */ public: CSaveAllADBWork::CMercenaryData m_MercenaryData;
	/* this+51272 */ public: CSaveAllADBWork::CQuestEventData m_questEventData;

	private: virtual bool CSaveAllADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl);
	//private: enum NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_Owner(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_Info(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_Effect(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_State(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveStateData(NODBCCtrl &);
	//public: const unsigned long GetGID();
	//public: const unsigned long GetAID();
	//public: const enum CSaveAllADBWork::enumAfterAction GetAfterAction();
	public: CSaveAllADBWork::CSaveAllADBWork(const enum CSaveAllADBWork::enumAfterAction in_AfterAction, const unsigned long in_AID, const unsigned long in_GID);
	public: virtual CSaveAllADBWork::~CSaveAllADBWork(void);

private:
	static hook_method<bool (CSaveAllADBWork::*)(NODBCCtrl& in_ODBCCtrl)> CSaveAllADBWork::_ExecQuery;
};
