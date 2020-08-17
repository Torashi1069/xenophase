#include "AsyncDBWork/NODBCHandler.h"
#include "AsyncDBWork/SaveAllADBWork.h"
#include "AsyncDBWork/Skill3rd.inl"
#include "shared/NCriticalErrorLog.h"


CSaveAllADBWork::CSaveAllADBWork()
: NAsyncDBWork(TYPE_SAVE_ALL),
  m_AID(0),
  m_GID(0),
  m_Result(RESULT_ERROR_UNKNOWN),
  m_AfterAction(AFTER_ACTION_NONE)
{
}


void CSaveAllADBWork::Init(const enumAfterAction in_AfterAction, const unsigned long in_AID, const unsigned long in_GID)
{
	this->NAsyncDBWork::Init(in_AID);
	m_AfterAction = in_AfterAction;
	m_GID = in_GID;
	m_AID = in_AID;
	m_Result = RESULT_ERROR_UNKNOWN;

	m_CharacterData.CSaveAllADBWork::CCharacterData::Init();
	m_MapMoveOtherSvr.CSaveAllADBWork::CMapMoveOtherSvr::Init();
	m_BodyItemData.CSaveAllADBWork::CBodyItemData::Init();
	m_StoreItemData.CSaveAllADBWork::CStoreItemData::Init();
	m_Effect3rd.CSaveAllADBWork::CEffect3rd::Init();
	m_CartItemData.CSaveAllADBWork::CCartItemData::Init();
	m_StateData.CSaveAllADBWork::CStateData::Init();
	m_MercenaryData.CSaveAllADBWork::CMercenaryData::Init();
	m_questEventData.CSaveAllADBWork::CQuestEventData::Init();
	m_Skill.CSaveAllADBWork::CSkill3rdData::Init();
	m_ElementalData.CSaveAllADBWorkStuff::CElementalData::Init();
	m_HomunData.Init();
	m_WaprpInfoData.CSaveAllADBWork::CWarpInfoData::Init();
}


CSaveAllADBWork::~CSaveAllADBWork()
{
}


const unsigned long CSaveAllADBWork::GetGID() const
{
	return m_GID;
}


const unsigned long CSaveAllADBWork::GetAID() const
{
	return m_AID;
}


const CSaveAllADBWork::enumAfterAction CSaveAllADBWork::GetAfterAction() const
{
	return m_AfterAction;
}


namespace {
NAsyncDBWork::enumRETURN UpdateElemental(NODBCCtrl& in_ODBCCtrl, unsigned long in_GID, const ElementalStuff::ESummaryData& in_ElementalSummaryData)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_GID, sizeof(in_GID), 0);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&in_ElementalSummaryData.m_hp), sizeof(in_ElementalSummaryData.m_hp), &cbInt);
	Handler.NODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, const_cast<int*>(&in_ElementalSummaryData.m_sp), sizeof(in_ElementalSummaryData.m_sp), &cbInt);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_elemental_update(?,?,?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
}; // namespace


namespace {
NAsyncDBWork::enumRETURN UpdateElementalEffect(NODBCCtrl& in_ODBCCtrl, unsigned long in_GID, const std::vector<Effect3rd::tagEffect3rdDBFmt>& in_List)
{
	if( in_List.size() == 0 )
		return NAsyncDBWork::RETURN_SUCCESS;

	NODBCHandler Handler(in_ODBCCtrl);

	Effect3rd::tagEffect3rdDBFmt Effect;
	SQLINTEGER cbInt = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_GID, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.ID, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.TimeMS, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.Data1, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.Data2, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &Effect.Data3, 0, &cbInt);

	for( std::vector<Effect3rd::tagEffect3rdDBFmt>::const_iterator iter = in_List.begin(); iter != in_List.end(); ++iter )
	{
		memcpy(&Effect, &*iter, sizeof(Effect));

		SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_elemental_update_effect(?, ?, ?, ?, ?, ?)}");
		if( !SQL_SUCCEEDED(sqlRet) )
		{
			Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return NAsyncDBWork::RETURN_ERROR_ODBC;
		}
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
}; // namespace


namespace {
std::pair<bool,bool> ExecQuery_Elemental(NODBCCtrl& in_ODBCCtrl, unsigned long in_GID, CSaveAllADBWorkStuff::CElementalData& in_ElemenalData)
{
	if( in_ElemenalData.m_bExist )
	{
		NAsyncDBWork::enumRETURN ret = UpdateElemental(in_ODBCCtrl, in_GID, in_ElemenalData.m_SummaryData);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			if( ret == NAsyncDBWork::RETURN_ERROR_ODBC )
				return std::pair<bool,bool>(false, true);
			else
				return std::pair<bool,bool>(false, false);
		}

		NAsyncDBWork::enumRETURN ret2 = UpdateElementalEffect(in_ODBCCtrl, in_GID, in_ElemenalData.m_EfstList);
		if( ret2 != NAsyncDBWork::RETURN_SUCCESS )
		{
			if( ret2 == NAsyncDBWork::RETURN_ERROR_ODBC )
				return std::pair<bool,bool>(false, true);
			else
				return std::pair<bool,bool>(false, false);
		}
	}

	return std::pair<bool,bool>(true, false);
}
}; // namespace


void CSaveAllADBWork::CCartItemData::Init()
{
//	memset(m_Data, 0x00, sizeof(m_Data));
	m_Length = 0;
	m_bActive = false;
}


void CSaveAllADBWork::CStoreItemData::Init()
{
//	memset(m_Data, 0x00, sizeof(m_Data));
	m_Length = 0;
	m_bActive = false;
}


void CSaveAllADBWork::CBodyItemData::Init()
{
//	memset(m_Data, 0x00, sizeof(m_Data));
	m_Length = 0;
	m_bActive = false;
}


void CSaveAllADBWork::CCharacterData::Init()
{
	m_bActive = false;
//	memset(&m_data, 0x00, sizeof(m_data));
//	memset(m_characterName, '\0', sizeof(m_characterName));
}


void CSaveAllADBWork::CMercenaryData::Init()
{
	m_Owner.CMercenaryData::COwner::Init();
	m_Character.CMercenaryData::CCharacter::Init();
}


void CSaveAllADBWork::CEffect3rd::Init()
{
	m_List.clear();
}


void CSaveAllADBWork::CStateData::Init()
{
	m_bActive = false;
//	memset(m_Data, 0x00, sizeof(m_Data));
	m_Length = 0;
}


void CSaveAllADBWork::CQuestEventData::Init()
{
	m_isUpdate = false;
	m_length_quest = 0;
	m_length_hunt = 0;
	m_length_time = 0;
	m_length_complete = 0;
//	memset(m_data_quset, 0x00, sizeof(m_data_quset));
//	memset(m_data_hunt, 0x00, sizeof(m_data_hunt));
//	memset(m_data_time, 0x00, sizeof(m_data_time));
//	memset(m_data_complete, 0x00, sizeof(m_data_complete));
}


void CSaveAllADBWork::CMapMoveOtherSvr::Init()
{
	m_NID = 0;
	m_TargetSvrID = 0;
}


void CSaveAllADBWork::CSkill3rdData::Init()
{
	m_List.clear();
}


void CSaveAllADBWork::CWarpInfoData::Init()
{
	m_WarpInfo.clear();
}


void CSaveAllADBWork::CWarpInfoData::SetWarpInfo(const std::deque<WARP_POSITION>& in_WarpInfo)
{
	m_WarpInfo.assign(in_WarpInfo.begin(), in_WarpInfo.end());

	for( size_t i = m_WarpInfo.size(); i < 3; ++i )
	{
		static WARP_POSITION Zero_Info;
		m_WarpInfo.push_back(Zero_Info);
	}
}


const std::vector<WARP_POSITION>& CSaveAllADBWork::CWarpInfoData::GetWarpInfo()
{
	return m_WarpInfo;
}


namespace {
NAsyncDBWork::enumRETURN UpdateWarpInfoData(NODBCCtrl& in_ODBCCtrl, unsigned long in_GID, const std::vector<WARP_POSITION>& in_WarpList)
{
	if( in_WarpList.size() > 3 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "UpdateWarpInfoData() in_WarpList.size() = %d", in_WarpList.size());
		return NAsyncDBWork::RETURN_SUCCESS;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	NODBCHandler Handler(in_ODBCCtrl);
	int ParameterIdx = 1;

	Handler.NODBCHandler::BindParameter(ParameterIdx++, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &in_GID, 0, &cbInt);
	for( std::vector<WARP_POSITION>::const_iterator iter = in_WarpList.begin(); iter != in_WarpList.end(); ++iter )
	{
		Handler.NODBCHandler::BindParameter(ParameterIdx++, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, sizeof(iter->mapName), 0, const_cast<char*>(iter->mapName), 0, &cbChar);
		Handler.NODBCHandler::BindParameter(ParameterIdx++, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, const_cast<short*>(&iter->xPos), 0, &cbInt);
		Handler.NODBCHandler::BindParameter(ParameterIdx++, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_INTEGER, 0, 0, const_cast<short*>(&iter->yPos), 0, &cbInt);
	}

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call UpdateWarpInfo(?, ?, ?, ?,\t?, ?, ?, ?, ?, ?)}");
	if( sqlRet != SQL_SUCCESS && sqlRet != SQL_SUCCESS_WITH_INFO && sqlRet != SQL_NO_DATA )
	{
		char szTemp[256] = {};
		sprintf_s(szTemp, countof(szTemp), "ParameterIdx(%d)", ParameterIdx);
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, szTemp);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
}; // namespace


bool CSaveAllADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl)
{
	m_Result = CSaveAllADBWork::RESULT_SUCCESS;

	if( m_CharacterData.m_bActive == true )
	{
		NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveCharacterInfo(in_ODBCCtrl, m_GID, m_CharacterData.m_characterName, m_CharacterData.m_data);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_CHARINFO;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}
	}

	if( m_BodyItemData.m_bActive == true )
	{
		NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveBodyItem(in_ODBCCtrl, m_GID, m_BodyItemData.m_data, m_BodyItemData.m_Length);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_BODYITEM;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}
	}

	if( m_Effect3rd.m_List.size() != 0 )
	{
		NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveEffect3rd(in_ODBCCtrl, m_GID, m_Effect3rd.m_List);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_EFFECTIVE;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}
	}

	if( m_StateData.m_bActive == true )
	{
		NAsyncDBWork::enumRETURN ret = this->CSaveAllADBWork::SaveStateData(in_ODBCCtrl);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_STATE;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}
	}

	if( m_StoreItemData.m_bActive == true )
	{
		NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveStoreItem(in_ODBCCtrl, m_AID, m_StoreItemData.m_Data, m_StoreItemData.m_Length);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_STOREITEM;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}
	}

	if( m_CartItemData.m_bActive == true )
	{
		NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveCartItem(in_ODBCCtrl, m_GID, m_CartItemData.m_Data, m_CartItemData.m_Length);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_CART;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}
	}

	if( m_MercenaryData.m_Owner.m_bActive == true )
	{
		NAsyncDBWork::enumRETURN ret = this->CSaveAllADBWork::SaveMercenaryData_Owner(in_ODBCCtrl);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_MERCENARY_OWNER;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}

		if( m_MercenaryData.m_Character.m_bActive == true )
		{
			NAsyncDBWork::enumRETURN ret1 = this->CSaveAllADBWork::SaveMercenaryData_Info(in_ODBCCtrl);
			if( ret1 != NAsyncDBWork::RETURN_SUCCESS )
			{
				m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_MERCENARY_INFO;
				return ( ret1 != NAsyncDBWork::RETURN_ERROR_ODBC );
			}

			NAsyncDBWork::enumRETURN ret2 = this->CSaveAllADBWork::SaveMercenaryData_Effect(in_ODBCCtrl);
			if( ret2 != NAsyncDBWork::RETURN_SUCCESS )
			{
				m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_MERCENARY_EFFECT;
				return ( ret2 != NAsyncDBWork::RETURN_ERROR_ODBC );
			}

			NAsyncDBWork::enumRETURN ret3 = this->CSaveAllADBWork::SaveMercenaryData_State(in_ODBCCtrl);
			if( ret3 != NAsyncDBWork::RETURN_SUCCESS )
			{
				m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_MERCENARY_STATE;
				return ( ret3 != NAsyncDBWork::RETURN_ERROR_ODBC );
			}
		}
	}

	if( m_questEventData.m_isUpdate == true )
	{
		NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveQuestEvent(in_ODBCCtrl, m_GID, m_questEventData.m_data_quset, m_questEventData.m_length_quest, m_questEventData.m_data_hunt, m_questEventData.m_length_hunt, m_questEventData.m_data_time, m_questEventData.m_length_time, m_questEventData.m_data_complete, m_questEventData.m_length_complete);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			if( ret == NAsyncDBWork::RETURN_ERROR_ODBC )
			{
				m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_QUESTEVENT;
				return false;
			}
			else
			if( ret == NAsyncDBWork::RETURN_ERROR )
			{
				m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_QUESTEVENT;
				return true;
			}
			else
			{
				m_Result = CSaveAllADBWork::RESULT_ERROR_UNKNOWN;
				return false;
			}
		}

		m_Result = CSaveAllADBWork::RESULT_SUCCESS;
	}

	if( m_Skill.m_List.size() != 0 )
	{
		NAsyncDBWork::enumRETURN ret = this->CSaveAllADBWork::SaveSkill(in_ODBCCtrl);
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_SKILL;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}

		m_Result = CSaveAllADBWork::RESULT_SUCCESS;
	}

	std::pair<bool,bool> eleRet = ExecQuery_Elemental(in_ODBCCtrl, m_GID, m_ElementalData);
	if( !eleRet.first )
	{
		m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_ELEMENTAL;
		return ( eleRet.second == false );
	}

	NAsyncDBWork::enumRETURN ret = this->NAsyncDBWork::SaveHomunData(in_ODBCCtrl, m_GID, m_HomunData);
//	if( ret != NAsyncDBWork::RETURN_SUCCESS )
	{
		if( ret == NAsyncDBWork::RETURN_ERROR_ODBC )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_HOMUN;
			return false;
		}
		else
		if( ret == NAsyncDBWork::RETURN_ERROR )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_HOMUN;
			return true;
		}
	}

	if( m_WaprpInfoData.CWarpInfoData::GetWarpInfo().size() != 0 )
	{
		NAsyncDBWork::enumRETURN ret = UpdateWarpInfoData(in_ODBCCtrl, m_GID, m_WaprpInfoData.CWarpInfoData::GetWarpInfo());
		if( ret != NAsyncDBWork::RETURN_SUCCESS )
		{
			m_Result = CSaveAllADBWork::RESULT_ERROR_SAVE_WARPINFODATA;
			return ( ret != NAsyncDBWork::RETURN_ERROR_ODBC );
		}
	}

	return true;
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveSkill(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	CSaveAllADBWork::CSkill3rdData::tagSkill Skill(0, 0, 0, 0);
	int Attr;
	SQLINTEGER cbInt = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, 4, 0, 0, &m_GID, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, 4, 0, 0, &Skill.ID, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, 4, 0, 0, &Skill.Level, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, 4, 0, 0, &Skill.RemainMS, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(5, SQL_PARAM_INPUT, SQL_C_SLONG, 4, 0, 0, &Attr, 0, &cbInt);
	Handler.NODBCHandler::BindParameter(6, SQL_PARAM_INPUT, SQL_C_SLONG, 4, 0, 0, &Skill.Data, 0, &cbInt);

	for( CSkill3rdData::SKILL3RDLIST::iterator iter = m_Skill.m_List.begin(); iter != m_Skill.m_List.end(); ++iter )
	{
		Skill.ID = iter->ID;
		Skill.Level = iter->Level;
		Skill.RemainMS = iter->RemainMS;
		Attr = Skill3rd::GetAttr(Skill.ID);

		SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_Skill_Rebuild_update(?, ?, ?, ?, ?, ?)}");
		if( !SQL_SUCCEEDED(sqlRet) )
		{
			Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return NAsyncDBWork::RETURN_ERROR_ODBC;
		}
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveStateData(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	if( m_StateData.m_Length <= 0 )
	{
		SQLINTEGER cbGID = 0;
		Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_GID, 0, &cbGID);

		if( !SQL_SUCCEEDED(Handler.NODBCHandler::ExecDirect("{call UpdateStateInfo(NULL, ?)}")) )
		{
			Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return NAsyncDBWork::RETURN_ERROR_ODBC;
		}

		return NAsyncDBWork::RETURN_SUCCESS;
	}
	else
	{
		SQLINTEGER cbBin = m_StateData.m_Length;
		SQLINTEGER cbGID = 0;
		Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, m_StateData.m_Length, 0, m_StateData.m_Data, 0, &cbBin);
		Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_GID, 0, &cbGID);

		if( !SQL_SUCCEEDED(Handler.NODBCHandler::ExecDirect("{call UpdateStateInfo(?, ?)}")) )
		{
			Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
			return NAsyncDBWork::RETURN_ERROR_ODBC;
		}

		return NAsyncDBWork::RETURN_SUCCESS;
	}
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_Owner(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_GID, sizeof(m_GID), &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Owner.m_data.m_arch, sizeof(m_MercenaryData.m_Owner.m_data.m_arch), &cbInt);
	Handler.NODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Owner.m_data.m_arch.faith, sizeof(m_MercenaryData.m_Owner.m_data.m_arch.faith), &cbInt);
	Handler.NODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Owner.m_data.m_spear, sizeof(m_MercenaryData.m_Owner.m_data.m_spear), &cbInt);
	Handler.NODBCHandler::BindParameter(5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Owner.m_data.m_spear.faith, sizeof(m_MercenaryData.m_Owner.m_data.m_spear.faith), &cbInt);
	Handler.NODBCHandler::BindParameter(6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Owner.m_data.m_sword, sizeof(m_MercenaryData.m_Owner.m_data.m_sword), &cbInt);
	Handler.NODBCHandler::BindParameter(7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Owner.m_data.m_sword.faith, sizeof(m_MercenaryData.m_Owner.m_data.m_sword.faith), &cbInt);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_mercenary_owner_saveV2(?,?,?,?,?,?,?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_Info(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_GID, sizeof(m_GID), &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Character.m_Info.RemainLifeSECOND, sizeof(m_MercenaryData.m_Character.m_Info.RemainLifeSECOND), &cbInt);
	Handler.NODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Character.m_Info.BodyState, sizeof(m_MercenaryData.m_Character.m_Info.BodyState), &cbInt);
	Handler.NODBCHandler::BindParameter(4, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Character.m_Info.HealthState, sizeof(m_MercenaryData.m_Character.m_Info.HealthState), &cbInt);
	Handler.NODBCHandler::BindParameter(5, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Character.m_Info.EffectState, sizeof(m_MercenaryData.m_Character.m_Info.EffectState), &cbInt);
	Handler.NODBCHandler::BindParameter(6, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Character.m_Info.Property, sizeof(m_MercenaryData.m_Character.m_Info.Property), &cbInt);
	Handler.NODBCHandler::BindParameter(7, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Character.m_Info.approval_monster_kill_counter, sizeof(m_MercenaryData.m_Character.m_Info.approval_monster_kill_counter), &cbInt);
	Handler.NODBCHandler::BindParameter(8, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Character.m_Info.hp, sizeof(m_MercenaryData.m_Character.m_Info.hp), &cbInt);
	Handler.NODBCHandler::BindParameter(9, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Character.m_Info.sp, sizeof(m_MercenaryData.m_Character.m_Info.sp), &cbInt);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_mercenary_info_saveV2(?, ?, ?, ?, ?, ?, ?, ?, ?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	int ret_code = 0;
	Handler.NODBCHandler::BindCol(1, SQL_C_SLONG, &ret_code, sizeof(ret_code), NULL);

	SQLRETURN sqlRet2 = Handler.NODBCHandler::Fetch();
	if( !SQL_SUCCEEDED(sqlRet2) )
		return NAsyncDBWork::RETURN_ERROR;

	if( ret_code <= 0 )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "용병정보 디비 저장에러 charID=%d", m_GID);

	return NAsyncDBWork::RETURN_SUCCESS;
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_Effect(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbBinary = m_MercenaryData.m_Character.m_EffectLength;
	if( cbBinary < 1 )
		cbBinary = 1;

	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_GID, sizeof(m_GID), &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_MercenaryData.m_Character.m_EffectLength, sizeof(m_MercenaryData.m_Character.m_EffectLength), &cbInt);
	Handler.NODBCHandler::BindParameter(3, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, cbBinary, 0, m_MercenaryData.m_Character.m_EffectData, 0, &cbBinary);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_mercenary_effect_saveV2(?, ?, ?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	int ret_code = 0;
	Handler.NODBCHandler::BindCol(1, SQL_C_SLONG, &ret_code, sizeof(ret_code), NULL);

	SQLRETURN sqlRet2 = Handler.NODBCHandler::Fetch();
	if( !SQL_SUCCEEDED(sqlRet2) )
		return NAsyncDBWork::RETURN_ERROR;

	if( ret_code <= 0 )
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "용병효과정보 디비 저장에러 charID=%d", m_GID);

	return NAsyncDBWork::RETURN_SUCCESS;
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_State(NODBCCtrl& in_ODBCCtrl)
{
	NODBCHandler Handler(in_ODBCCtrl);

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbBinary = m_MercenaryData.m_Character.m_StateLength;
	if( cbBinary <= 0 )
		cbBinary = -1;

	Handler.NODBCHandler::BindParameter(1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &m_GID, sizeof(m_GID), &cbInt);
	Handler.NODBCHandler::BindParameter(2, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_VARBINARY, cbBinary, 0, m_MercenaryData.m_Character.m_StateData, 0, &cbBinary);

	SQLRETURN sqlRet = Handler.NODBCHandler::ExecDirect("{call usp_mercenary_state_save(?, ?)}");
	if( !SQL_SUCCEEDED(sqlRet) )
	{
		Handler.NODBCHandler::OutputErrorString(__FILE__, __LINE__, NULL);
		return NAsyncDBWork::RETURN_ERROR_ODBC;
	}

	return NAsyncDBWork::RETURN_SUCCESS;
}
