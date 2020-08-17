#pragma once
#include "CPCBattleMercenary.hpp"
#include "AsyncDBWork/NAsyncDBWork.h"
#include "AsyncDBWork/NODBCCtrl.h"
#include "struct.hpp"


class CLogonPermitADBWork : public NAsyncDBWork
{
	enum enumResult
	{
		RESULT_SUCCESS                      = 0x0,
		RESULT_ERROR_UNKNOWN                = 0x1,
		RESULT_ERROR_LOAD_BODYITEM          = 0x2,
		RESULT_ERROR_LOAD_BODYITEM_INSERT   = 0x3,
		RESULT_ERROR_LOAD_CHARACTERINFO     = 0x4,
		RESULT_ERROR_LOAD_MERCENARY_OWNER   = 0x5,
		RESULT_ERROR_LOAD_MERCENARY_INFO    = 0x6,
		RESULT_ERROR_LOAD_MERCENARY_EFFECT  = 0x7,
		RESULT_ERROR_LOAD_MERCENARY_STATE   = 0x8,
		RESULT_ERROR_LOAD_SKILL             = 0x9,
		RESULT_ERROR_LOAD_SKILL_INSERT      = 0xA,
		RESULT_ERROR_LOAD_EFFECITVE         = 0xB,
		RESULT_ERROR_LOAD_EFFECTIVE_INSERT  = 0xC,
		RESULT_ERROR_LOAD_STATE             = 0xD,
		RESULT_ERROR_LOAD_STATE_INSERT      = 0xE,
		RESULT_ERROR_LOAD_HOMUN             = 0xF,
		RESULT_ERROR_LOAD_QUESTEVENT        = 0x10,
		RESULT_ERROR_LOAD_QUESTEVENT_INSERT = 0x11,
		RESULT_ERROR_LOAD_BATTLEFIELD       = 0x12,
	};

	class CBodyItemData
	{
		/* this+0x0 */ public: int m_length;
		/* this+0x4 */ public: unsigned char m_Data[16300];

		public: CBodyItemData()
		{
			m_length = 0;
		}

		public: ~CBodyItemData()
		{
		}
	};

	class CCharacterInfoData
	{
		/* this+0x0 */ public: CHARINFO_FROM_CHARACTERDB m_data;

		public: CCharacterInfoData()
		{
		}

		public: ~CCharacterInfoData()
		{
		}
	};

	class CSkillData
	{
		/* this+0x0   */ public: unsigned char m_Data[256];
		/* this+0x100 */ public: int m_Length;

		public: CSkillData()
		{
			m_Length = 0;
		}

		public: ~CSkillData()
		{
		}
	};

	class CEffectiveData
	{
		/* this+0x0   */ public: unsigned char m_Data2[512];
		/* this+0x200 */ public: int m_Length;

		public: CEffectiveData()
		{
			m_Length = 0;
		}

		public: ~CEffectiveData()
		{
		}
	};

	class CStateData
	{
		/* this+0x0   */ public: unsigned char m_Data[512];
		/* this+0x200 */ public: int m_Length;

		public: CStateData()
		{
			m_Length = 0;
		}

		public: ~CStateData()
		{
		}
	};

	class CMercenaryData
	{
		/* this+0x0   */ public: CPCBattleMercenary::tagDBData m_Owner;
		/* this+0x1C  */ public: CMercenaryDBV2::DBINFO m_Info;
		/* this+0x44  */ public: unsigned char m_EffectData[512];
		/* this+0x244 */ public: int m_EffectLength;
		/* this+0x248 */ public: unsigned char m_StateData[512];
		/* this+0x448 */ public: int m_StateLength;

		public: CMercenaryData()
		{
		}

		public: ~CMercenaryData()
		{
		}
	};

	class CQuestEventData
	{
		/* this+0x0    */ public: int m_questEvent_Length;
		/* this+0x4    */ public: int m_completeQuest_Length;
		/* this+0x8    */ public: int m_quest_hunt_Length;
		/* this+0xC    */ public: int m_quest_time_Length;
		/* this+0x10   */ public: unsigned char m_questEvent_Data[8000];
		/* this+0x1F50 */ public: unsigned char m_completeQuest_Data[4000];
		/* this+0x2EF0 */ public: unsigned char m_quest_hunt_Data[8000];
		/* this+0x4E30 */ public: unsigned char m_quest_time_Data[4000];

		public: CQuestEventData()
		{
			m_questEvent_Length = 0;
			m_completeQuest_Length = 0;
			m_quest_hunt_Length = 0;
			m_quest_time_Length = 0;
		}

		public: ~CQuestEventData()
		{
		}
	};

	class CBattleFieldData
	{
		/* this+0x0 */ public: char m_campID;
		/* this+0x2 */ public: short m_x;
		/* this+0x4 */ public: short m_y;

		public: CBattleFieldData()
		{
			m_campID = 0;
			m_x = 0;
			m_y = 0;
		}

		public: ~CBattleFieldData()
		{
		}
	};

	struct vtable_t //const CLogonPermitADBWork::`vftable'
	{
		bool (CLogonPermitADBWork::* ExecQuery)(NODBCCtrl &);
		void* (CLogonPermitADBWork::* vector_deleting_destructor)(unsigned int);
	};

	/* this+0x0    */ //NAsyncDBWork
	/* this+0x14   */ private: const unsigned long m_AID;
	/* this+0x18   */ private: const unsigned long m_GID;
	/* this+0x1C   */ private: const short m_SelectedCharNum;
	/* this+0x1E   */ private: char m_IDstr[24];
	/* this+0x38   */ private: const unsigned long m_TotalUsingTime;
	/* this+0x3C   */ private: enum CLogonPermitADBWork::enumResult m_Result;
	/* this+0x40   */ public: CLogonPermitADBWork::CBodyItemData m_BodyItemInfo;
	/* this+0x3FF0 */ public: CLogonPermitADBWork::CCharacterInfoData m_CharacterInfo;
	/* this+0x4094 */ public: CLogonPermitADBWork::CSkillData m_SkillData;
	/* this+0x4198 */ public: CLogonPermitADBWork::CMercenaryData m_MercenaryData;
	/* this+0x45E4 */ public: CLogonPermitADBWork::CEffectiveData m_EffectiveData;
	/* this+0x47E8 */ public: CLogonPermitADBWork::CStateData m_StateData;
	/* this+0x49EC */ public: CLogonPermitADBWork::CQuestEventData m_questData;
	/* this+0xA7BC */ public: CLogonPermitADBWork::CBattleFieldData m_battleFieldData;

	//public: const unsigned long GetGID();
	//public: const unsigned long GetAID();
	//public: const char* GetIDstr();
	//public: const unsigned long GettotalUsingTime();
	//public: const int GetSelectedCharNum();
	//public: const enum CLogonPermitADBWork::enumResult GetResult();
	private: virtual bool CLogonPermitADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadBodyItemInfo(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::InsertBodyItem(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadCharacterInfo(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadSkillData(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::InsertSkillData(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadMercenaryData_Owner(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadMercenaryData_Info(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadMercenaryData_Effect(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadMercenaryData_State(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadEffectiveData(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::InsertEffectiveData(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadStateData(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::InsertStateData(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadQuestEventInfo(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::InsertQuestEvent(NODBCCtrl &);
	//private: enum NAsyncDBWork::enumRETURN CLogonPermitADBWork::LoadBattleFieldInfo(NODBCCtrl &);
	public: CLogonPermitADBWork::CLogonPermitADBWork(const unsigned long in_AID, const unsigned long in_GID, const int in_SelectedCharNum, const char* in_pIDstr, const unsigned long in_TotalUsingTime);
	public: virtual CLogonPermitADBWork::~CLogonPermitADBWork(void);

private:
	static hook_method<bool (CLogonPermitADBWork::*)(NODBCCtrl& in_ODBCCtrl)> CLogonPermitADBWork::_ExecQuery;
};
