#include "AsyncDBWork/NODBCHandler.h"
#include "AsyncDBWork/SaveAllADBWork.h"


CSaveAllADBWork::CSaveAllADBWork() // 26-27
: NAsyncDBWork(TYPE_SAVE_ALL)
{
	//TODO
}


void CSaveAllADBWork::Init(const enumAfterAction in_AfterAction, const unsigned long in_AID, const unsigned long in_GID) // 35-101
{
	//TODO
}


CSaveAllADBWork::~CSaveAllADBWork() // 123-125
{
	//TODO
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
NAsyncDBWork::enumRETURN UpdateElemental(NODBCCtrl& in_ODBCCtrl, unsigned long in_GID, const ElementalStuff::ESummaryData& in_List) // 131-145
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}
}; // namespace


namespace {
NAsyncDBWork::enumRETURN UpdateElementalEffect(NODBCCtrl& in_ODBCCtrl, unsigned long in_GID, const std::vector<Effect3rd::tagEffect3rdDBFmt>& in_List) // 153-176
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}
}; // namespace


namespace {
std::pair<bool,bool> ExecQuery_Elemental(NODBCCtrl& in_ODBCCtrl, unsigned long in_GID, CSaveAllADBWorkStuff::CElementalData& in_ElemenalData) // 187-212
{
	return std::pair<bool,bool>(false,false);
	//TODO
}
}; // namespace


void CSaveAllADBWork::CWarpInfoData::Init() // 269-271
{
	m_WarpInfo.clear();
}


void CSaveAllADBWork::CWarpInfoData::SetWarpInfo(const std::deque<WARP_POSITION>& in_WarpInfo) // 274-284
{
	//TODO
}


const std::vector<WARP_POSITION>& CSaveAllADBWork::CWarpInfoData::GetWarpInfo()
{
	return m_WarpInfo;
}


namespace {
NAsyncDBWork::enumRETURN UpdateWarpInfoData(NODBCCtrl& in_ODBCCtrl, unsigned long in_GID, const std::vector<WARP_POSITION>& in_WarpList) // 289-329
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}
}; // namespace


bool CSaveAllADBWork::ExecQuery(NODBCCtrl& in_ODBCCtrl) // 352-743
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


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveSkill(NODBCCtrl& in_ODBCCtrl) // 749-798
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveStateData(NODBCCtrl& in_ODBCCtrl) // 811-834
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


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_Owner(NODBCCtrl& in_ODBCCtrl) // 844-873
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_Info(NODBCCtrl& in_ODBCCtrl) // 881-920
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_Effect(NODBCCtrl& in_ODBCCtrl) // 966-991
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}


NAsyncDBWork::enumRETURN CSaveAllADBWork::SaveMercenaryData_State(NODBCCtrl& in_ODBCCtrl) // 936-955
{
	return NAsyncDBWork::RETURN_ERROR;
	//TODO
}
