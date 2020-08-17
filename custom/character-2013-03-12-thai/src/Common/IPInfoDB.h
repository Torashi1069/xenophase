#pragma once
#include "Common/Database.h"
#include "Common/Singleton.h"


class CIPInfoDB : public CDatabase, public CSingleton<CIPInfoDB>
{
private:
	/* this+ 0 */ //CDatabase baseclass_0;
	/* this+37 */ //CSingleton<CIPInfoDB> baseclass_37;
	/* this+40 */ std::string m_strPwd;
	/* static  */ static const std::string m_strFileDSNfileName;

public:
	CIPInfoDB();
	~CIPInfoDB();
	void InitMapInfoList();
	void SetPwd(const char* in_szPwd);
	bool Connect();
};
