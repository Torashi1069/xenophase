#pragma once
#include "std/map"
#include "CMercenaryDBV2.hpp"


class CPCBattleMercenary
{
public:
	struct TypicalJobInfo
	{
		/* this+0x0 */ public: int tatal_call_number;
		/* this+0x4 */ public: int faith;

		public: TypicalJobInfo::TypicalJobInfo(void)
		{
			tatal_call_number = 0;
			faith = 0;
		}
	};

	struct tagDBData
	{
		/* this+0x0  */ public: int m_Call;
		/* this+0x4  */ public: CPCBattleMercenary::TypicalJobInfo m_arch;
		/* this+0xC  */ public: CPCBattleMercenary::TypicalJobInfo m_spear;
		/* this+0x14 */ public: CPCBattleMercenary::TypicalJobInfo m_sword;

		public: tagDBData::tagDBData(void)
		{
			m_arch.tatal_call_number = 0;
			m_arch.faith = 0;
			m_spear.tatal_call_number = 0;
			m_spear.faith = 0;
			m_sword.tatal_call_number = 0;
			m_sword.faith = 0;
		}
	};

	typedef mystd::map<int,CPCBattleMercenary::TypicalJobInfo> TYPICALJOBINFOCONTAINERITOR;

	enum enumWorkStep
	{
		WORKSTEP_NONE = 0x0,
		WORKSTEP_DELETE = 0x1,
		WORKSTEP_CREATE = 0x2,
	};

	class CProxyDB
	{
		/* this+0x0   */ public: bool m_bLoad;
		/* this+0x4   */ public: CMercenaryDBV2::DBINFO m_Info;
		/* this+0x2C  */ public: unsigned char m_EffectData[512];
		/* this+0x22C */ public: int m_EffectLength;
		/* this+0x230 */ public: unsigned char m_StateData[512];
		/* this+0x430 */ public: int m_StateLength;

		public: CProxyDB::CProxyDB(void)
		{
			m_bLoad = false;
		}

		public: CProxyDB::~CProxyDB(void)
		{
		}
	};

	/* this+0x0  */ //const CPCBattleMercenary::`vftable'
	/* this+0x4  */ private: bool m_bCall;
	/* this+0x5  */ private: bool m_bModify;
	/* this+0x8  */ private: mystd::map<int,CPCBattleMercenary::TypicalJobInfo> m_TypicalJobInfoContainer;
	/* this+0x14 */ private: enum CPCBattleMercenary::enumWorkStep m_WorkStep;
	/* this+0x18 */ public: CPCBattleMercenary::CProxyDB m_ProxyDB;

	public: CPCBattleMercenary::CPCBattleMercenary(void);
	public: virtual CPCBattleMercenary::~CPCBattleMercenary(void);
	public: void CPCBattleMercenary::Clear(void);
	//public: const enum CPCBattleMercenary::enumWorkStep CPCBattleMercenary::GetWorkStep();
	//public: void CPCBattleMercenary::SetWorkStep(const enum CPCBattleMercenary::enumWorkStep);
	public: bool CPCBattleMercenary::isCall(void);
	//public: bool CPCBattleMercenary::GetTypicalJobInfo(const int, CPCBattleMercenary::TypicalJobInfo &);
	//public: bool CPCBattleMercenary::InsertTypicalJobInfo(const int, CPCBattleMercenary::TypicalJobInfo);
	//public: void CPCBattleMercenary::UpdateTypicalJobInfo(const int, CPCBattleMercenary::TypicalJobInfo);
	//public: void CPCBattleMercenary::SetCall(int);
	//public: int CPCBattleMercenary::GetTotalSummonNum(const int);
	//public: int CPCBattleMercenary::GetFaith(const int);
	//public: void CPCBattleMercenary::SubFaith(const int, const int);
	//public: void CPCBattleMercenary::AddFaith(const int, const int);
	public: CPCBattleMercenary& CPCBattleMercenary::operator=(const CPCBattleMercenary::tagDBData& in_rhs);
	public: operator CPCBattleMercenary::tagDBData(void);

private:
	static hook_method<void (CPCBattleMercenary::*)(void)> CPCBattleMercenary::_Clear;
	static hook_method<bool (CPCBattleMercenary::*)(void)> CPCBattleMercenary::_isCall;
	static hook_method<CPCBattleMercenary& (CPCBattleMercenary::*)(const CPCBattleMercenary::tagDBData& in_rhs)> CPCBattleMercenary::_operator_assign;
	static hook_method<CPCBattleMercenary::tagDBData (CPCBattleMercenary::*)(void)> CPCBattleMercenary::_operator_tagDBData;
};
