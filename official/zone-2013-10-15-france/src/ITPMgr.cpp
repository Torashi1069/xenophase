#include "Enum.h"
#include "FTLexicalAnaysis.h"
#include "ITPMgr.h"
#include "Path.h"
#include "ZoneProcess.h"
#include "shared/NCriticalErrorLog.h"


/// globals
CItemListV2& g_NotDisappearAfterUsingItemList = VTOR<CItemListV2>(DetourFindFunction(EXEPATH(), "g_NotDisappearAfterUsingItemList"));
CBuyingStoreItemList& g_BuyingStoreItemList = VTOR<CBuyingStoreItemList>(DetourFindFunction(EXEPATH(), "g_BuyingStoreItemList"));


////////////////////////////////////////



CITPMgr::CITPMgr()
{
}


CITPMgr::~CITPMgr()
{
	for( std::map<unsigned short,CITP*>::iterator iter = m_itp.begin(); iter != m_itp.end(); iter = m_itp.erase(iter) )
		delete iter->second;

	m_effect.clear();
	m_itemName.clear();
}


void CITPMgr::DBClose()
{
	SQLCloseCursor(m_hstmt);
	if( m_hstmt != SQL_NULL_HSTMT )
		SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
}


std::map<std::string,unsigned short>& CITPMgr::GetNameMap()
{
	return m_itemName;
}


std::map<unsigned short,std::vector<unsigned short>>& CITPMgr::GetCombiItemList()
{
	return m_combiItem;
}


bool CITPMgr::Save(const char* fName)
{
	FILE* fp = fopen(fName, "w");
	if( fp == NULL )
		return false;

	for( ITEMNAMEIDXMAP_ITER iter = m_itemName.begin(); iter != m_itemName.end(); ++iter )
		fprintf(fp, "%s %d\n", iter->first.c_str(), iter->second);

	fclose(fp);
	return true;
}


void CITPMgr::Init(const char* Script)
{
	this->CODBC::Init(Script, g_GlobaldbPWD);

	m_effect["EFFECT01"] = EFFECT01;
	m_effect["EFFECT02"] = EFFECT02;
	m_effect["EFFECT03"] = EFFECT03;
	m_effect["EFFECT04"] = EFFECT04;
	m_effect["EFFECT05"] = EFFECT05;
	m_effect["EFFECT06"] = EFFECT06;
	m_effect["EFFECT07"] = EFFECT07;
	m_effect["EFFECT08"] = EFFECT08;
	m_effect["EFFECT09"] = EFFECT09;
	m_effect["EFFECT10"] = EFFECT10;
	m_effect["EFFECT11"] = EFFECT11;
	m_effect["EFFECT12"] = EFFECT12;
	m_effect["EFFECT13"] = EFFECT13;
	m_effect["EFFECT14"] = EFFECT14;
	m_effect["EFFECT15"] = EFFECT15;
	m_effect["EFFECT16"] = EFFECT16;
	m_effect["EFFECT17"] = EFFECT17;
	m_effect["EFFECT18"] = EFFECT18;
	m_effect["EFFECT19"] = EFFECT19;
	m_effect["EFFECT20"] = EFFECT20;
	m_effect["EFFECT21"] = EFFECT21;
	m_effect["EFFECT22"] = EFFECT22;
	m_effect["EFFECT23"] = EFFECT23;

	this->CITPMgr::LoadITP();
	this->CODBC::Reset();
	this->CITPMgr::LoadCombiItemList(g_pathData.CPathData::SetFileName(".\\itemdata\\combiItem.sc"));
	this->CITPMgr::LoadItemMoveInfo();
	this->CITPMgr::LoadCashItemList();
	this->CITPMgr::LoadScrollItemList();
	this->CITPMgr::LoadItemBindOnEquip();

	if( !g_NotDisappearAfterUsingItemList.CItemListV2::Load("NotDisappearAfterUsingItemList.lua") )
	{
		MessageBoxA(NULL, __FUNCTION__", Fail NotDisappearAfterUsingItemList.lua", "Error", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}
}


bool CITPMgr::LoadCashItemList()
{
	CCashItemList List;
	if( !List.CCashItemList::Load() )
	{
		MessageBoxA(NULL, "Cash Item List Loading error", "syntax error", MB_OK);
		ExitProcess(EXIT_SUCCESS);
		return false;
	}

	return true;
}


void CITPMgr::LoadITP()
{
	this->CITPMgr::GetHeal();
	this->CITPMgr::GetSpecial();
	this->CITPMgr::GetEvent();
	this->CITPMgr::GetCard();
	this->CITPMgr::GetArmor(TYPE_ARMOR);
	this->CITPMgr::GetArmor(TYPE_ARMORTM);
	this->CITPMgr::GetArmor(TYPE_ARMORTB);
	this->CITPMgr::GetArmor(TYPE_ARMORMB);
	this->CITPMgr::GetArmor(TYPE_ARMORTMB);
	this->CITPMgr::GetWeapon();
	this->CITPMgr::GetQuest();
	this->CITPMgr::GetArrow();
	this->CITPMgr::GetBothhand();
	this->CITPMgr::GetBow();
	this->CITPMgr::GetAmmo();
	this->CITPMgr::GetGun();
	if( !this->CITPMgr::GetThrow() )
		MessageBoxA(NULL, "fail GetThrow()", "LoadITP", MB_OK);
	this->CITPMgr::GetCashPointItem();
	this->CITPMgr::GetCannonball();
}


BOOL CITPMgr::LoadCombiItemList(const char* fileName)
{
	FILE* fp = fopen(fileName, "rt");
	if( fp == NULL )
	{
		char buf[256];
		sprintf_s(buf, countof(buf), "File not found! (%s)", fileName);
		MessageBoxA(NULL, buf, "Error", MB_OK);
		return FALSE;
	}

	int blockCount = 0;
	unsigned short combiITID = 30000;
	std::vector<unsigned short> itemList;

	for( ; ; )
	{
		char buf[256];
		if( fscanf(fp, "%s", buf) == EOF )
			break;

		if( strstr(buf, "//") != NULL )
		{
			fgets(buf, countof(buf), fp);
		}
		else
		if( strcmp(buf, "{") == 0 )
		{
			if( blockCount > 0 )
			{
				sprintf_s(buf, countof(buf), "Check this file.(%s)", fileName);
				MessageBoxA(NULL, buf, "syntax error", MB_OK);
				return false;
			}

			++blockCount;
			itemList.clear();
		}
		else
		if( strcmp(buf, "}") == 0 )
		{
			if( blockCount <= 0 )
			{
				sprintf_s(buf, countof(buf), "Check this file.(%s)", fileName);
				MessageBoxA(NULL, buf, "syntax error", MB_OK);
				return false;
			}

			--blockCount;
			m_combiItem.insert(std::make_pair(combiITID, itemList));
			++combiITID;
		}
		else
		{
			if( blockCount == 0 )
			{
				m_itemName[buf] = combiITID;
			}
			else
			{
				unsigned short ITID = this->CITPMgr::GetITID(buf);
				if( ITID == 0 )
				{
					char msg[256];
					_snprintf_s(msg, countof(msg), _TRUNCATE, "file: %s\nNot exist Item! (%s)", fileName, buf);
					MessageBoxA(NULL, msg, "LoadCombiItemList ERROR", MB_OK);
					return FALSE;
				}

				itemList.push_back(ITID);
			}
		}
	}

	fclose(fp);
	return TRUE;
}


CITP* CITPMgr::GetITP(unsigned short ITID)
{
	ITEMPROTOTYPEMAP_ITER iter = m_itp.find(ITID);
	if( iter == m_itp.end() )
		return NULL;

	return iter->second;
}


short CITPMgr::GetItemWeight(unsigned short ITID)
{
	CITP* itp = this->CITPMgr::GetITP(ITID);
	if( itp == NULL )
		return -1;

	return static_cast<short>(itp->m_weight);
}


BOOL CITPMgr::AddITP(CITP* itp)
{
	if( itp->m_ITID == 0 )
		return TRUE;

	std::pair<ITEMPROTOTYPEMAP_ITER,bool> ret = m_itp.insert(std::make_pair(itp->m_ITID, itp));
	if( !ret.second )
	{
		char buffer[1024] = {};
		sprintf_s(buffer, countof(buffer), "ERROR [duplicate item id] - (name:%s, id:%d type:%d)", itp->m_name, itp->m_ITID, itp->GetType());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", buffer);

		ITEMPROTOTYPEMAP_ITER iter = m_itp.find(itp->m_ITID);
		if( iter != m_itp.end() )
		{
			CITP* dupitp = iter->second;

			char temp_buffer[1024] = {};
			sprintf_s(temp_buffer, countof(temp_buffer), "\n(name:%s, id:%d type:%d)", dupitp->m_name, dupitp->m_ITID, dupitp->GetType());
			NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", temp_buffer);
			strcat(buffer, temp_buffer);
		}

		MessageBoxA(NULL, buffer, "AddITP()", MB_OK);
		return FALSE;
	}

	std::pair<ITEMNAMEIDXMAP_ITER,bool> ret2 = m_itemName.insert(std::make_pair(itp->m_name, itp->m_ITID));
	if( !ret2.second )
	{
		char buffer[1024] = {};
		sprintf_s(buffer, countof(buffer), "ERROR [duplicate item id] - (name:%s, id:%d type:%d)", itp->m_name, itp->m_ITID, itp->GetType());
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", buffer);

		ITEMNAMEIDXMAP_ITER iter = m_itemName.find(itp->m_name);
		if( iter != m_itemName.end() )
		{
			ITEMPROTOTYPEMAP_ITER protoIter = m_itp.find(iter->second);
			if( protoIter != m_itp.end() )
			{
				CITP* dupitp = protoIter->second;

				char temp_buffer[1024] = {};
				sprintf_s(temp_buffer, countof(temp_buffer), "\n(name:%s, id:%d type:%d)", dupitp->m_name, dupitp->m_ITID, dupitp->GetType());
				NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s", temp_buffer);
				strcat(buffer, temp_buffer);
			}
		}

		m_itp.erase(ret.first);

		MessageBoxA(NULL, buffer, "AddITP()", MB_OK);
		return FALSE;
	}

	return TRUE;
}


unsigned short CITPMgr::GetITID(const char* itemName)
{
	ITEMNAMEIDXMAP_ITER iter = m_itemName.find(itemName);
	if( iter == m_itemName.end() )
		return 0;

	return iter->second;
}


int CITPMgr::FindITID(const char* itemName, unsigned long* pItemIDList)
{
	std::string ItemName;

	ITEMNAMEIDXMAP_ITER iter;
	int i;
	for( iter = m_itemName.begin(), i = 0; iter != m_itemName.end(), i < 10; ++iter, ++i )
	{
		ItemName.assign(iter->first.c_str());
		if( ItemName.find(itemName) != ItemName.npos )
			pItemIDList[i] = iter->second;
	}

	return i;
}


unsigned long CITPMgr::GetEffectID(const char* effectName)
{
	std::map<std::string,unsigned long>::iterator iter = m_effect.find(effectName);
	if( iter == m_effect.end() )
		return -1;

	return iter->second;
}


namespace {
class lcDBHandler
{
public:
	lcDBHandler(const SQLHDBC in_hDBC)
	{
		m_hstmt = SQL_NULL_HSTMT;
		m_bOK = true;

		if( !SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, in_hDBC, &m_hstmt)) )
			m_bOK = false;
	}

	~lcDBHandler()
	{
		if( m_hstmt != SQL_NULL_HSTMT )
		{
			SQLCloseCursor(m_hstmt);
			SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt);
		}
	}

public:
	operator SQLHSTMT() { return m_hstmt; }
	bool isOK() const { return m_bOK; }

private:
	/* this+0 */ SQLHSTMT m_hstmt;
	/* this+4 */ bool m_bOK;
};
}; // namespace


namespace {
void FailLoadItemDB(const char* in_Text, const char* in_Caption)
{
	MessageBoxA(NULL, in_Text, in_Caption, MB_OK);
	ExitProcess(EXIT_SUCCESS);
}
}; // namespace


void CITPMgr::GetHeal()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPHeal Item;
	SQLBindCol(handler,  1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler,  2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler,  3, SQL_C_SLONG, &Item.m_minHp, 0, &cbInt);
	SQLBindCol(handler,  4, SQL_C_SLONG, &Item.m_maxHp, 0, &cbInt);
	SQLBindCol(handler,  5, SQL_C_SLONG, &Item.m_minSp, 0, &cbInt);
	SQLBindCol(handler,  6, SQL_C_SLONG, &Item.m_maxSp, 0, &cbInt);
	SQLBindCol(handler,  7, SQL_C_SLONG, &Item.m_states, 0, &cbInt);
	SQLBindCol(handler,  8, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler,  9, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 10, SQL_C_SLONG, &Item.m_abuse_gause, 0, &cbInt);
	SQLBindCol(handler, 11, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 12, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getheal2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getheal2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getheal2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPHeal* itp = new(std::nothrow) CITPHeal();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPHeal failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_minHp = Item.m_minHp;
		itp->m_maxHp = Item.m_maxHp;
		itp->m_minSp = Item.m_minSp;
		itp->m_maxSp = Item.m_maxSp;
		itp->m_states = Item.m_states;
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_abuse_gause = Item.m_abuse_gause;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetSpecial()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPSpecial Item;
	char effectBuffer[32];
	SQLBindCol(handler, 1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler, 2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler, 3, SQL_C_CHAR, effectBuffer, sizeof(effectBuffer), &cbChar);
	SQLBindCol(handler, 4, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 5, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 6, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 7, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getspecial2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getspecial2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getspecial2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPSpecial* itp = new(std::nothrow) CITPSpecial();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPSpecial failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_effect = this->CITPMgr::GetEffectID(effectBuffer);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetCard()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPCard Item;
	SQLBindCol(handler, 1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler, 2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler, 3, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 4, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 5, SQL_C_SLONG, &Item.m_compositionType, 0, &cbInt);
	SQLBindCol(handler, 6, SQL_C_SLONG, &Item.m_compositionPos, 0, &cbInt);
	SQLBindCol(handler, 7, SQL_C_SLONG, &Item.m_class, 0, &cbInt);
	SQLBindCol(handler, 8, SQL_C_SLONG, &Item.m_property, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getcard2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getcard2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getcard2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPCard* itp = new(std::nothrow) CITPCard();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPCard failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_compositionType = Item.m_compositionType;
		itp->m_compositionPos = Item.m_compositionPos;
		itp->m_class = Item.m_class;
		itp->m_property = Item.m_property;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetEvent()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPEvent Item;
	SQLBindCol(handler, 1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler, 2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler, 3, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 4, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getevent2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getevent2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getevent2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPEvent* itp = new(std::nothrow) CITPEvent();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPEvent failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetQuest()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPQuest Item;
	SQLBindCol(handler, 1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler, 2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getguest2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getguest2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getguest2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPQuest* itp = new(std::nothrow) CITPQuest();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPQuest failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetCannonball()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPCannonball Item;
	SQLBindCol(handler, 1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler, 2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler, 3, SQL_C_SLONG, &Item.m_ATK, 0, &cbInt);
	SQLBindCol(handler, 4, SQL_C_SLONG, &Item.m_property, 0, &cbInt);
	SQLBindCol(handler, 5, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 6, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 7, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 8, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getcannonball2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getcannonball2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getcannonball2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPCannonball* itp = new(std::nothrow) CITPCannonball();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPCannonball failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_ATK = Item.m_ATK;
		itp->m_property = Item.m_property;
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetArrow()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPArrow Item;
	SQLBindCol(handler, 1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler, 2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler, 3, SQL_C_SLONG, &Item.m_ATK, 0, &cbInt);
	SQLBindCol(handler, 4, SQL_C_SLONG, &Item.m_property, 0, &cbInt);
	SQLBindCol(handler, 5, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 6, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 7, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 8, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getarrow2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getarrow2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getarrow2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPArrow* itp = new(std::nothrow) CITPArrow();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPArrow failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_ATK = Item.m_ATK;
		itp->m_property = Item.m_property;
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetAmmo()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPAmmo Item;
	SQLBindCol(handler, 1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler, 2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler, 3, SQL_C_SLONG, &Item.m_ATK, 0, &cbInt);
	SQLBindCol(handler, 4, SQL_C_SLONG, &Item.m_property, 0, &cbInt);
	SQLBindCol(handler, 5, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 6, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 7, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 8, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getammo2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getammo2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getammo2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPAmmo* itp = new(std::nothrow) CITPAmmo();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPAmmo failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_ATK = Item.m_ATK;
		itp->m_property = Item.m_property;
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetWeapon()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPWeapon Item;
	char effectBuffer[32];
	SQLBindCol(handler,  1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler,  2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler,  3, SQL_C_SLONG, &Item.m_ATK, 0, &cbInt);
	SQLBindCol(handler,  4, SQL_C_SLONG, &Item.m_MATK, 0, &cbInt);
	SQLBindCol(handler,  5, SQL_C_SLONG, &Item.m_AR, 0, &cbInt);
	SQLBindCol(handler,  6, SQL_C_SLONG, &Item.m_maxSlot, 0, &cbInt);
	SQLBindCol(handler,  7, SQL_C_SLONG, &Item.m_str, 0, &cbInt);
	SQLBindCol(handler,  8, SQL_C_SLONG, &Item.m_int, 0, &cbInt);
	SQLBindCol(handler,  9, SQL_C_SLONG, &Item.m_vit, 0, &cbInt);
	SQLBindCol(handler, 10, SQL_C_SLONG, &Item.m_dex, 0, &cbInt);
	SQLBindCol(handler, 11, SQL_C_SLONG, &Item.m_agi, 0, &cbInt);
	SQLBindCol(handler, 12, SQL_C_SLONG, &Item.m_luk, 0, &cbInt);
	SQLBindCol(handler, 13, SQL_C_SSHORT, &Item.m_class, 0, &cbInt);
	SQLBindCol(handler, 14, SQL_C_CHAR, effectBuffer, sizeof(effectBuffer), &cbChar);
	SQLBindCol(handler, 15, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 16, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 17, SQL_C_SLONG, &Item.m_sex, 0, &cbInt);
	SQLBindCol(handler, 18, SQL_C_SLONG, &Item.m_availableJob, 0, &cbInt);
	SQLBindCol(handler, 19, SQL_C_SLONG, &Item.m_level, 0, &cbInt);
	SQLBindCol(handler, 20, SQL_C_SLONG, &Item.m_location, 0, &cbInt);
	SQLBindCol(handler, 21, SQL_C_SLONG, &Item.m_property, 0, &cbInt);
	SQLBindCol(handler, 22, SQL_C_SLONG, &Item.m_isRefinable, 0, &cbInt);
	SQLBindCol(handler, 23, SQL_C_SLONG, &Item.m_isDamagable, 0, &cbInt);
	SQLBindCol(handler, 24, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 25, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getweapon2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getweapon2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getweapon2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPWeapon* itp = new(std::nothrow) CITPWeapon();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPWeapon failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_ATK = Item.m_ATK;
		itp->m_MATK = Item.m_MATK;
		itp->m_AR = Item.m_AR;
		itp->m_maxSlot = Item.m_maxSlot;
		itp->m_str = Item.m_str;
		itp->m_int = Item.m_int;
		itp->m_vit = Item.m_vit;
		itp->m_dex = Item.m_dex;
		itp->m_agi = Item.m_agi;
		itp->m_luk = Item.m_luk;
		itp->m_class = Item.m_class;
		itp->m_effect = this->CITPMgr::GetEffectID(effectBuffer);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_sex = Item.m_sex;
		itp->m_availableJob = Item.m_availableJob;
		itp->m_level = Item.m_level;
		itp->m_location = Item.m_location;
		itp->m_property = Item.m_property;
		itp->m_isRefinable = Item.m_isRefinable;
		itp->m_isDamagable = Item.m_isDamagable;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetBothhand()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPBothhand Item;
	char effectBuffer[32];
	SQLBindCol(handler,  1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler,  2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler,  3, SQL_C_SLONG, &Item.m_ATK, 0, &cbInt);
	SQLBindCol(handler,  4, SQL_C_SLONG, &Item.m_MATK, 0, &cbInt);
	SQLBindCol(handler,  5, SQL_C_SLONG, &Item.m_AR, 0, &cbInt);
	SQLBindCol(handler,  6, SQL_C_SLONG, &Item.m_maxSlot, 0, &cbInt);
	SQLBindCol(handler,  7, SQL_C_SLONG, &Item.m_str, 0, &cbInt);
	SQLBindCol(handler,  8, SQL_C_SLONG, &Item.m_int, 0, &cbInt);
	SQLBindCol(handler,  9, SQL_C_SLONG, &Item.m_vit, 0, &cbInt);
	SQLBindCol(handler, 10, SQL_C_SLONG, &Item.m_dex, 0, &cbInt);
	SQLBindCol(handler, 11, SQL_C_SLONG, &Item.m_agi, 0, &cbInt);
	SQLBindCol(handler, 12, SQL_C_SLONG, &Item.m_luk, 0, &cbInt);
	SQLBindCol(handler, 13, SQL_C_SSHORT, &Item.m_class, 0, &cbInt);
	SQLBindCol(handler, 14, SQL_C_CHAR, effectBuffer, sizeof(effectBuffer), &cbChar);
	SQLBindCol(handler, 15, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 16, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 17, SQL_C_SLONG, &Item.m_sex, 0, &cbInt);
	SQLBindCol(handler, 18, SQL_C_SLONG, &Item.m_availableJob, 0, &cbInt);
	SQLBindCol(handler, 19, SQL_C_SLONG, &Item.m_level, 0, &cbInt);
	SQLBindCol(handler, 20, SQL_C_SLONG, &Item.m_location, 0, &cbInt);
	SQLBindCol(handler, 21, SQL_C_SLONG, &Item.m_property, 0, &cbInt);
	SQLBindCol(handler, 22, SQL_C_SLONG, &Item.m_isRefinable, 0, &cbInt);
	SQLBindCol(handler, 23, SQL_C_SLONG, &Item.m_isDamagable, 0, &cbInt);
	SQLBindCol(handler, 24, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 25, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getbothhand2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getbothhand2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getbothhand2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPBothhand* itp = new(std::nothrow) CITPBothhand();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPBothhand failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_ATK = Item.m_ATK;
		itp->m_MATK = Item.m_MATK;
		itp->m_AR = Item.m_AR;
		itp->m_maxSlot = Item.m_maxSlot;
		itp->m_str = Item.m_str;
		itp->m_int = Item.m_int;
		itp->m_vit = Item.m_vit;
		itp->m_dex = Item.m_dex;
		itp->m_agi = Item.m_agi;
		itp->m_luk = Item.m_luk;
		itp->m_class = Item.m_class;
		itp->m_effect = this->CITPMgr::GetEffectID(effectBuffer);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_sex = Item.m_sex;
		itp->m_availableJob = Item.m_availableJob;
		itp->m_level = Item.m_level;
		itp->m_location = Item.m_location;
		itp->m_property = Item.m_property;
		itp->m_isRefinable = Item.m_isRefinable;
		itp->m_isDamagable = Item.m_isDamagable;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetBow()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPBow Item;
	char effectBuffer[32];
	SQLBindCol(handler,  1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler,  2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler,  3, SQL_C_SLONG, &Item.m_ATK, 0, &cbInt);
	SQLBindCol(handler,  4, SQL_C_SLONG, &Item.m_AR, 0, &cbInt);
	SQLBindCol(handler,  5, SQL_C_SLONG, &Item.m_maxSlot, 0, &cbInt);
	SQLBindCol(handler,  6, SQL_C_SLONG, &Item.m_str, 0, &cbInt);
	SQLBindCol(handler,  7, SQL_C_SLONG, &Item.m_int, 0, &cbInt);
	SQLBindCol(handler,  8, SQL_C_SLONG, &Item.m_vit, 0, &cbInt);
	SQLBindCol(handler,  9, SQL_C_SLONG, &Item.m_dex, 0, &cbInt);
	SQLBindCol(handler, 10, SQL_C_SLONG, &Item.m_agi, 0, &cbInt);
	SQLBindCol(handler, 11, SQL_C_SLONG, &Item.m_luk, 0, &cbInt);
	SQLBindCol(handler, 12, SQL_C_SSHORT, &Item.m_class, 0, &cbInt);
	SQLBindCol(handler, 13, SQL_C_CHAR, effectBuffer, sizeof(effectBuffer), &cbChar);
	SQLBindCol(handler, 14, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 15, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 16, SQL_C_SLONG, &Item.m_sex, 0, &cbInt);
	SQLBindCol(handler, 17, SQL_C_SLONG, &Item.m_availableJob, 0, &cbInt);
	SQLBindCol(handler, 18, SQL_C_SLONG, &Item.m_level, 0, &cbInt);
	SQLBindCol(handler, 19, SQL_C_SLONG, &Item.m_location, 0, &cbInt);
	SQLBindCol(handler, 20, SQL_C_SLONG, &Item.m_property, 0, &cbInt);
	SQLBindCol(handler, 21, SQL_C_SLONG, &Item.m_isRefinable, 0, &cbInt);
	SQLBindCol(handler, 22, SQL_C_SLONG, &Item.m_isDamagable, 0, &cbInt);
	SQLBindCol(handler, 23, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 24, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getbow2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getbow2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getbow2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPBow* itp = new(std::nothrow) CITPBow();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPBow failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_ATK = Item.m_ATK;
		itp->m_AR = Item.m_AR;
		itp->m_maxSlot = Item.m_maxSlot;
		itp->m_str = Item.m_str;
		itp->m_int = Item.m_int;
		itp->m_vit = Item.m_vit;
		itp->m_dex = Item.m_dex;
		itp->m_agi = Item.m_agi;
		itp->m_luk = Item.m_luk;
		itp->m_class = Item.m_class;
		itp->m_effect = this->CITPMgr::GetEffectID(effectBuffer);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_sex = Item.m_sex;
		itp->m_availableJob = Item.m_availableJob;
		itp->m_level = Item.m_level;
		itp->m_location = Item.m_location;
		itp->m_property = Item.m_property;
		itp->m_isRefinable = Item.m_isRefinable;
		itp->m_isDamagable = Item.m_isDamagable;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetGun()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPGun Item;
	char effectBuffer[32];
	SQLBindCol(handler,  1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler,  2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler,  3, SQL_C_SLONG, &Item.m_ATK, 0, &cbInt);
	SQLBindCol(handler,  4, SQL_C_SLONG, &Item.m_AR, 0, &cbInt);
	SQLBindCol(handler,  5, SQL_C_SLONG, &Item.m_maxSlot, 0, &cbInt);
	SQLBindCol(handler,  6, SQL_C_SLONG, &Item.m_str, 0, &cbInt);
	SQLBindCol(handler,  7, SQL_C_SLONG, &Item.m_int, 0, &cbInt);
	SQLBindCol(handler,  8, SQL_C_SLONG, &Item.m_vit, 0, &cbInt);
	SQLBindCol(handler,  9, SQL_C_SLONG, &Item.m_dex, 0, &cbInt);
	SQLBindCol(handler, 10, SQL_C_SLONG, &Item.m_agi, 0, &cbInt);
	SQLBindCol(handler, 11, SQL_C_SLONG, &Item.m_luk, 0, &cbInt);
	SQLBindCol(handler, 12, SQL_C_SSHORT, &Item.m_class, 0, &cbInt);
	SQLBindCol(handler, 13, SQL_C_CHAR, effectBuffer, sizeof(effectBuffer), &cbChar);
	SQLBindCol(handler, 14, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 15, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 16, SQL_C_SLONG, &Item.m_sex, 0, &cbInt);
	SQLBindCol(handler, 17, SQL_C_SLONG, &Item.m_availableJob, 0, &cbInt);
	SQLBindCol(handler, 18, SQL_C_SLONG, &Item.m_level, 0, &cbInt);
	SQLBindCol(handler, 19, SQL_C_SLONG, &Item.m_location, 0, &cbInt);
	SQLBindCol(handler, 20, SQL_C_SLONG, &Item.m_property, 0, &cbInt);
	SQLBindCol(handler, 21, SQL_C_SLONG, &Item.m_isRefinable, 0, &cbInt);
	SQLBindCol(handler, 22, SQL_C_SLONG, &Item.m_isDamagable, 0, &cbInt);
	SQLBindCol(handler, 23, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 24, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getgun2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getgun2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getgun2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPGun* itp = new(std::nothrow) CITPGun();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPGun failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_ATK = Item.m_ATK;
		itp->m_AR = Item.m_AR;
		itp->m_maxSlot = Item.m_maxSlot;
		itp->m_str = Item.m_str;
		itp->m_int = Item.m_int;
		itp->m_vit = Item.m_vit;
		itp->m_dex = Item.m_dex;
		itp->m_agi = Item.m_agi;
		itp->m_luk = Item.m_luk;
		itp->m_class = Item.m_class;
		itp->m_effect = this->CITPMgr::GetEffectID(effectBuffer);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_sex = Item.m_sex;
		itp->m_availableJob = Item.m_availableJob;
		itp->m_level = Item.m_level;
		itp->m_location = Item.m_location;
		itp->m_property = Item.m_property;
		itp->m_isRefinable = Item.m_isRefinable;
		itp->m_isDamagable = Item.m_isDamagable;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


namespace {
const char* GetITPArmorUSP(const unsigned long in_Type)
{
	switch( in_Type )
	{
	case TYPE_ARMORTM:
		return "usp_getarmorTM2";
	case TYPE_ARMORTB:
		return "usp_getarmorTB2";
	case TYPE_ARMORMB:
		return "usp_getarmorMB2";
	case TYPE_ARMORTMB:
		return "usp_getarmorTMB2";
	case TYPE_ARMOR:
	default:
		return "usp_getarmor2";
	};
}
}; // namespace


namespace {
std::tr1::tuple<CITPArmor*,std::string> GetITPAmorObject(const unsigned long in_Type)
{
	CITPArmor* ArmorObject;
	std::string ArmorTypeName;

	switch( in_Type )
	{
	case TYPE_ARMORTM:
		ArmorObject = new(std::nothrow) CITPArmorTM();
		ArmorTypeName = "CITPArmorTM";
	break;
	case TYPE_ARMORTB:
		ArmorObject = new(std::nothrow) CITPArmorTB();
		ArmorTypeName = "CITPArmorTB";
	break;
	case TYPE_ARMORMB:
		ArmorObject = new(std::nothrow) CITPArmorMB();
		ArmorTypeName = "CITPArmorMB";
	break;
	case TYPE_ARMORTMB:
		ArmorObject = new(std::nothrow) CITPArmorTMB();
		ArmorTypeName = "CITPArmorTMB";
	break;
	case TYPE_ARMOR:
	default:
		ArmorObject = new(std::nothrow) CITPArmor();
		ArmorTypeName = "CITPArmor";
	break;
	};

	return std::tr1::tuple<CITPArmor*,std::string>(ArmorObject, ArmorTypeName);
}
}; // namespace


void CITPMgr::GetArmor(unsigned long type)
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPArmor Item;
	char effectBuffer[32];
	SQLBindCol(handler,  1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler,  2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler,  3, SQL_C_SLONG, &Item.m_defencePower, 0, &cbInt);
	SQLBindCol(handler,  4, SQL_C_SLONG, &Item.m_maxSlot, 0, &cbInt);
	SQLBindCol(handler,  5, SQL_C_SLONG, &Item.m_str, 0, &cbInt);
	SQLBindCol(handler,  6, SQL_C_SLONG, &Item.m_int, 0, &cbInt);
	SQLBindCol(handler,  7, SQL_C_SLONG, &Item.m_vit, 0, &cbInt);
	SQLBindCol(handler,  8, SQL_C_SLONG, &Item.m_dex, 0, &cbInt);
	SQLBindCol(handler,  9, SQL_C_SLONG, &Item.m_agi, 0, &cbInt);
	SQLBindCol(handler, 10, SQL_C_SLONG, &Item.m_luk, 0, &cbInt);
	SQLBindCol(handler, 11, SQL_C_SLONG, &Item.m_maxHp, 0, &cbInt);
	SQLBindCol(handler, 12, SQL_C_SLONG, &Item.m_maxSp, 0, &cbInt);
	SQLBindCol(handler, 13, SQL_C_CHAR, effectBuffer, sizeof(effectBuffer), &cbChar);
	SQLBindCol(handler, 14, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 15, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 16, SQL_C_SLONG, &Item.m_sex, 0, &cbInt);
	SQLBindCol(handler, 17, SQL_C_SLONG, &Item.m_availableJob, 0, &cbInt);
	SQLBindCol(handler, 18, SQL_C_SLONG, &Item.m_location, 0, &cbInt);
	SQLBindCol(handler, 19, SQL_C_SLONG, &Item.m_mdef, 0, &cbInt);
	SQLBindCol(handler, 20, SQL_C_SSHORT, &Item.m_class, 0, &cbInt);
	SQLBindCol(handler, 21, SQL_C_SLONG, &Item.m_isRefinable, 0, &cbInt);
	SQLBindCol(handler, 22, SQL_C_SLONG, &Item.m_isDamagable, 0, &cbInt);
	SQLBindCol(handler, 23, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 24, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	char StatementText[128] = {};
	sprintf_s(StatementText, countof(StatementText), "{call %s}", GetITPArmorUSP(type));

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)StatementText, SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", %s, RET = %d\n", StatementText, ret);

		char errortext[128] = {};
		sprintf_s(errortext, countof(errortext), __FUNCTION__", %s failed", StatementText);
		FailLoadItemDB(errortext, "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			return;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		std::tr1::tuple<CITPArmor*,std::string> RetITPObj = GetITPAmorObject(type);
		CITPArmor* itp = std::tr1::get<0>(RetITPObj);
		std::string& name = std::tr1::get<1>(RetITPObj);
		if( itp == NULL )
		{
			char errortext[128] = {};
			sprintf_s(errortext, countof(errortext), __FUNCTION__", new %s failed", name.c_str());
			FailLoadItemDB(errortext, "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_defencePower = Item.m_defencePower;
		itp->m_maxSlot = Item.m_maxSlot;
		itp->m_str = Item.m_str;
		itp->m_int = Item.m_int;
		itp->m_vit = Item.m_vit;
		itp->m_dex = Item.m_dex;
		itp->m_agi = Item.m_agi;
		itp->m_luk = Item.m_luk;
		itp->m_maxHp = Item.m_maxHp;
		itp->m_maxSp = Item.m_maxSp;
		itp->m_effect = this->CITPMgr::GetEffectID(effectBuffer);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_sex = Item.m_sex;
		itp->m_availableJob = Item.m_availableJob;
		itp->m_location = Item.m_location;
		itp->m_mdef = Item.m_mdef;
		itp->m_class = Item.m_class;
		itp->m_isRefinable = Item.m_isRefinable;
		itp->m_isDamagable = Item.m_isDamagable;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


void CITPMgr::GetCashPointItem()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		FailLoadItemDB(__FUNCTION__" lcDBHandler false", "DB Load Error");
		return;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPCashPointItem Item;
	SQLBindCol(handler, 1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler, 2, SQL_C_CHAR, Item.m_name, sizeof(Item.m_name), &cbChar);
	SQLBindCol(handler, 3, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 4, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 5, SQL_C_SLONG, &Item.m_ChangeItemID, 0, &cbInt);
	SQLBindCol(handler, 6, SQL_C_SLONG, &Item.m_Count, 0, &cbInt);

	SQLRETURN ret = SQLExecDirectA(handler, (SQLCHAR*)"{call usp_getcashpointitem2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getcashpointitem2}, RET = %d\n", ret);
		FailLoadItemDB(__FUNCTION__", usp_getcashpointitem2 failed", "DB Load Error");
		return;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			break;

		if( ret == SQL_ERROR )
		{
			FailLoadItemDB(__FUNCTION__", ::SQLFetch failed", "DB Load Error");
			return;
		}

		CITPCashPointItem* itp = new(std::nothrow) CITPCashPointItem();
		if( itp == NULL )
		{
			FailLoadItemDB(__FUNCTION__", new CITPCashPointItem failed", "DB Load Error");
			return;
		}

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_price = Item.m_price;
		itp->m_weight = Item.m_weight;
		itp->m_ChangeItemID = Item.m_ChangeItemID;
		itp->m_Count = Item.m_Count;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			FailLoadItemDB(__FUNCTION__", AddITP failed", "DB Load Error");
			return;
		}
	}
}


bool CITPMgr::GetThrow()
{
	lcDBHandler handler(m_hdbc);
	if( !handler.lcDBHandler::isOK() )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", lcDBHandler, false");
		return false;
	}

	SQLINTEGER cbInt = 0;
	SQLINTEGER cbChar = SQL_NTS;

	CITPThrow Item;
	SQLBindCol(handler, 1, SQL_C_SSHORT, &Item.m_ITID, 0, &cbInt);
	SQLBindCol(handler, 2, SQL_C_CHAR, Item.m_name, 24, &cbChar);
	SQLBindCol(handler, 3, SQL_C_SLONG, &Item.m_ATK, 0, &cbInt);
	SQLBindCol(handler, 4, SQL_C_SLONG, &Item.m_property, 0, &cbInt);
	SQLBindCol(handler, 5, SQL_C_SLONG, &Item.m_price, 0, &cbInt);
	SQLBindCol(handler, 6, SQL_C_SLONG, &Item.m_weight, 0, &cbInt);
	SQLBindCol(handler, 7, SQL_C_SLONG, &Item.m_availableJob, 0, &cbInt);
	SQLBindCol(handler, 8, SQL_C_SSHORT, &Item.m_minLevel, 0, &cbInt);
	SQLBindCol(handler, 9, SQL_C_SSHORT, &Item.m_maxLevel, 0, &cbInt);

	SQLRETURN ret = SQLExecDirect(handler, (SQLCHAR*)"{call usp_getthrow2}", SQL_NTS);
	if( !SQL_SUCCEEDED(ret) )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, __FUNCTION__", {call usp_getthrow2}, RET = %d\n", ret);
		return false;
	}

	for( ; ; )
	{
		SQLRETURN ret = SQLFetch(handler);
		if( ret == SQL_NO_DATA )
			return true;

		if( ret == SQL_ERROR )
			return false;

		CITPThrow* itp = new(std::nothrow) CITPThrow();
		if( itp == NULL )
			return false;

		itp->m_ITID = Item.m_ITID;
		strcpy(itp->m_name, Item.m_name);
		itp->m_price = Item.m_price;
		itp->m_ATK = Item.m_ATK;
		itp->m_property = Item.m_property;
		itp->m_weight = Item.m_weight;
		itp->m_availableJob = Item.m_availableJob;
		itp->m_minLevel = Item.m_minLevel;
		itp->m_maxLevel = Item.m_maxLevel;

		if( !this->CITPMgr::AddITP(itp) )
		{
			delete itp;
			return false;
		}
	}
}


int CITPMgr::IsApparel(unsigned short ITID)
{
	CITP* itp = this->CITPMgr::GetITP(ITID);
	if( itp == NULL )
		return 0;

	return itp->IsApparel();
}


BOOL CITPMgr::IsCashPointItem(unsigned short ITID)
{
	CITP* itp = this->CITPMgr::GetITP(ITID);
	if( itp == NULL )
		return FALSE;

	return ( itp->GetType() == TYPE_CASH_POINT_ITEM );
}


char* CITPMgr::GetItemName(unsigned short ITID)
{
	CITP* itp = this->CITPMgr::GetITP(ITID);
	if( itp == NULL )
		return NULL;

	return itp->m_name;
}


void CITPMgr::LoadItemMoveInfo()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("ItemMoveInfoV4.txt"), "r");
	if( fp == NULL )
		return;

	while( !feof(fp) )
	{
		char buf[256];
		fscanf(fp, "%s", buf);

		if( strstr(buf, "//") == NULL )
		{
			CITP* itp = this->CITPMgr::GetITP(atoi(buf));
			if( itp != NULL )
			{
				for( int i = 0; i < 7; ++i )
				{
					int value;
					fscanf(fp, "%d", &value);

					if( value == 1 )
						itp->m_isMovable |= 1 << i;
				}
			}
		}

		fgets(buf, countof(buf), fp);
	}

	fclose(fp);
}


enumInventoryItemType CITPMgr::GetInventoryItemType(const unsigned short in_ITID)
{
	CITP* itp = this->CITPMgr::GetITP(in_ITID);
	if( itp == NULL )
		return INVENTORYITEMTYPE_UNNONE;

	switch( itp->GetType() )
	{
	case TYPE_HEAL:
	case TYPE_SCHANGE:
	case TYPE_SPECIAL:
	case TYPE_EVENT:
	case TYPE_CARD:
		return INVENTORYITEMTYPE_NORMALITEM;
	case TYPE_ARROW:
	case TYPE_AMMO:
	case TYPE_THROWWEAPON:
	case TYPE_CANNONBALL:
		return INVENTORYITEMTYPE_NORMALARROWITEM;
	case TYPE_ARMOR:
	case TYPE_WEAPON:
	case TYPE_BOW:
	case TYPE_BOTHHAND:
	case TYPE_ARMORTM:
	case TYPE_ARMORTB:
	case TYPE_ARMORMB:
	case TYPE_ARMORTMB:
	case TYPE_GUN:
		return INVENTORYITEMTYPE_EQUIPITEM;
	case TYPE_QUEST:
		return INVENTORYITEMTYPE_QUESTITEM;
	case TYPE_CASH_POINT_ITEM:
		return INVENTORYITEMTYPE_CASHPOINTITEM;
	default:
		return INVENTORYITEMTYPE_UNNONE;
	};
}


void CITPMgr::LoadScrollItemList()
{
	m_scrollItem.clear();

	FILE* fp = fopen(g_pathData.CPathData::SetFileName("ScrollItemList.txt"), "r");
	if( fp == NULL )
		return;

	while( !feof(fp) )
	{
		char buf[1024] = {};
		if( fgets(buf, 1024, fp) == NULL )
			continue;

		char* p = buf;
		for( ; ; )
		{
			char* str = strtok(p, " \t\n");
			if( str == NULL )
				break;

			if( strstr(str, "//") != NULL )
				break;

			unsigned short itemID = (unsigned short)atoi(str);
			m_scrollItem[itemID] = itemID;

			p = NULL;
		}
	}

	fclose(fp);
}


bool CITPMgr::IsScrollItem(unsigned short ITID)
{
	std::map<unsigned short,unsigned short>::iterator iter = m_scrollItem.find(ITID);
	return ( iter != m_scrollItem.end() );
}


void CITPMgr::LoadItemBindOnEquip()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("BindOnEquip.txt"), "r");
	if( fp == NULL )
		return;

	while( !feof(fp) )
	{
		char buf[256] = {};
		if( fgets(buf, countof(buf), fp) == NULL )
			break;

		char* key = strtok(buf, " \t\n");
		if( key == NULL )
			break;

		if( strstr(key, "//") != NULL )
			continue;

		unsigned short ITID = this->CITPMgr::GetITID(key);
		if( ITID == 0 )
			continue;

		CITP* itp = this->CITPMgr::GetITP(ITID);
		if( itp == NULL )
			continue;

		itp->m_isBindOnEquip = true;
	}

	fclose(fp);
}


const bool CITPMgr::IsCostumeItem(const unsigned long loc) const
{
	if( loc == LOCATION_COSTUME_HEAD2
	 || loc == LOCATION_COSTUME_HEAD3
	 || loc == LOCATION_COSTUME_HEAD
	 || loc == LOCATION_COSTUME_HEAD_TB
	 || loc == LOCATION_COSTUME_HEAD_TM
	 || loc == LOCATION_COSTUME_HEAD_MB
	 || loc == LOCATION_COSTUME_HEAD_TMB
	 || loc == LOCATION_COSTUME_ROBE )
		return true;

	return false;
}


////////////////////////////////////////


CItemList::CItemList()
{
	m_itemNum = 0;
}


CItemList::~CItemList()
{
	m_itemNum = 0;
}


void CItemList::LoadFromFile(const char* fileName, int verDate)
{
	FILE* fp = fopen(fileName, "r");
	if( fp == NULL )
	{
		char buf[255];
		sprintf_s(buf, countof(buf), "%s open error", fileName);
		MessageBoxA(NULL, buf, "error", MB_OK);
		return;
	}

	int date;
	fscanf(fp, "%d\n", &date);
	if( date != verDate )
	{
		char buf[255];
		sprintf_s(buf, countof(buf), "%s old version?", fileName);
//		MessageBoxA(NULL, buf, "error", MB_OK);
//		return;
	}

	int i = 0;
	while( !feof(fp) )
	{
		char buff[255];
		if( fgets(buff, countof(buff), fp) == NULL )
			continue;

		char buf[255] = {};
		sscanf(buff, "%s", buf);
		if( strlen(buf) == 0 )
			continue;

		unsigned short ITID = g_itpMgr.CITPMgr::GetITID(buf);
		if( ITID == 0 )
			continue;

		m_itemArray[i] = ITID;
		i += 2;
	}

	m_itemNum = i;
	fclose(fp);
}


int CItemList::GetNth(int n)
{
	if( n > m_itemNum - 1 )
		return -1;

	return m_itemArray[n];
}


////////////////////////////////////////


CItemListV2::CItemListV2()
{
	m_ItemList.clear();
}


CItemListV2::~CItemListV2()
{
	m_ItemList.clear();
}


namespace {
class CAutoLuaClose
{
public:
	CAutoLuaClose(lua_State* L)
	{
		m_L = L;
	}

	~CAutoLuaClose()
	{
		if( m_L != NULL )
		{
			lua_close(m_L);
			m_L = NULL;
		}
	}

private:
	lua_State* m_L;
};
}; // namespace


bool CItemListV2::Load(const char* in_FileName)
{
	lua_State* L = luaL_newstate();
	if( L == NULL )
		return false;

	CAutoLuaClose AutoLuaClose(L);

	if( luaL_loadfile(L, g_pathData.CPathData::SetFileName(in_FileName)) != 0 )
		return false;
	
	if( lua_pcall(L, 0, 0, 0) != 0 )
		return false;

	lua_getfield(L, LUA_GLOBALSINDEX, "ItemList");
	if( lua_type(L, -1) != LUA_TTABLE )
		return false;

	lua_pushnil(L);
	while( lua_next(L, -2) != 0 )
	{
		if( !lua_isnumber(L, -2) )
			return false;

		if( !lua_isstring(L, -1) )
			return false;

		int key = (int)lua_tonumber(L, -2);
		const char* value = lua_tolstring(L, -1, NULL);
		lua_settop(L, -2);

		unsigned short ITID = g_itpMgr.CITPMgr::GetITID(value);
		if( ITID == 0 )
			return false;

		m_ItemList.insert(ITID);
	}

	return true;
}


bool CItemListV2::IsPartOfItemList(const unsigned short in_ITID)
{
	return ( m_ItemList.find(in_ITID) != m_ItemList.end() );
}


////////////////////////////////////////


bool CBuyingStoreItemList::OpenFileBuyingStoreItemList()
{
	FILE* fp = NULL;
	if( fopen_s(&fp, "buyingstoreItemList.txt", "rt") || fp == NULL )
		return false;

	char szBuffer[512] = {};
	char szInfo[512] = {};

	while( !feof(fp) )
	{
		memset(szBuffer, '\0', sizeof(szBuffer));
		fgets(szBuffer, countof(szBuffer), fp);

		if( strlen(szBuffer) < 3 )
			continue;

		if( strstr(szBuffer, "//") != NULL )
			continue;

		sscanf(szBuffer, "%s#", szInfo);
		unsigned short dwItemID = (unsigned short)atoi(szInfo);

		m_BuyingStoreItemList.insert(dwItemID);
	}

	fclose(fp);
	_flushall();
	return true;
}


bool CBuyingStoreItemList::IsPossibleTradeItem(const unsigned short wITID)
{
	return ( m_BuyingStoreItemList.find(wITID) != m_BuyingStoreItemList.end() );
}


////////////////////////////////////////


CCashItemList::CCashItemList()
{
}


CCashItemList::~CCashItemList()
{
}


CCashItemList::ANAYSISRET CCashItemList::Anaysis(const std::string in_strFileName)
{
	CFTLexicalAnaysis LexicalAnaysis(in_strFileName);
	if( !LexicalAnaysis.CFTLexicalAnaysis::isOK() )
		return ANAYSISRET(ANAYSISRET::CODE_ERROR_LEXICALANALYSIS_INITIALIZE);

	CFTToken Token;
	for( ; ; )
	{
		if( !LexicalAnaysis.CFTLexicalAnaysis::GetToken(Token) )
			return ANAYSISRET(ANAYSISRET::CODE_ERROR_GET_TOKEN, Token);

		CFTToken::enumType type = Token.CFTToken::GetType();
		if( type == CFTToken::EOF_ )
			return ANAYSISRET(ANAYSISRET::CODE_SUCCESS, Token);

		if( type != CFTToken::STRING )
			return ANAYSISRET(ANAYSISRET::CODE_ERROR_SYNTAX, Token);

		unsigned short ItemID = g_itpMgr.CITPMgr::GetITID(Token.CFTToken::GetSTRING().c_str());
		if( ItemID == 0 )
			return ANAYSISRET(ANAYSISRET::CODE_ERROR_UNKNOWN_ITEMID, Token);

		CITP* itp = g_itpMgr.CITPMgr::GetITP(ItemID);
		if( itp == NULL )
			return ANAYSISRET(ANAYSISRET::CODE_ERROR_UNKNOWN_ITEMID, Token);

		itp->m_bCashItem = true;
	}
}


bool CCashItemList::Load()
{
	ANAYSISRET Ret = this->CCashItemList::Anaysis(g_pathData.CPathData::SetFileName("CashItemList.txt"));
	if( Ret.Code != ANAYSISRET::CODE_SUCCESS )
	{
		char buffer[260] = "unknown syntex error";

		switch( Ret.Code )
		{
		case ANAYSISRET::CODE_ERROR:
			_snprintf(buffer, countof(buffer), "error found\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING().c_str(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
		case ANAYSISRET::CODE_ERROR_LEXICALANALYSIS_INITIALIZE:
			_snprintf(buffer, countof(buffer), "lexical anaysis initialize error");
		break;
		case ANAYSISRET::CODE_ERROR_GET_TOKEN:
			_snprintf(buffer, countof(buffer), "can't get token\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING().c_str(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
		case ANAYSISRET::CODE_ERROR_SYNTAX:
			_snprintf(buffer, countof(buffer), "syntax error\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING().c_str(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
		case ANAYSISRET::CODE_ERROR_UNKNOWN_ITEMID:
			_snprintf(buffer, countof(buffer), "unknown item id\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
		case ANAYSISRET::CODE_ERROR_UNKNOWN:
		default:
			_snprintf(buffer, countof(buffer), "unknown error found\n \"%s\"(Line:%d,Col:%d)", Ret.Token.CFTToken::GetSTRING().c_str(), Ret.Token.CFTToken::GetLine(), Ret.Token.CFTToken::GetCol());
		break;
		};

		MessageBoxA(NULL, buffer, "CashItemList.txt", MB_OK);
		return false;
	}

	return true;
}


////////////////////////////////////////
