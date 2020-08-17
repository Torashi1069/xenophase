#pragma once
#include "ODBC.h"


struct _STORE_PASSWORD_INFO
{
	/* this+ 0 */ int Password;
	/* this+ 4 */ int ErrorCount;
	/* this+ 8 */ DWORD PanaltyTime;
	/* this+12 */ int MapID;
	/* this+16 */ int X;
	/* this+20 */ int Y;

	_STORE_PASSWORD_INFO()
	{
		this->_STORE_PASSWORD_INFO::Init();
	}

	void Init()
	{
		this->Password = 0;
		this->ErrorCount = 0;
		this->PanaltyTime = 0;
		this->MapID = 0;
		this->X = 0;
		this->Y = 0;
	}

	void InitPosition()
	{
		this->MapID = 0;
		this->X = 0;
		this->Y = 0;
	}
};


struct _CASHSHOP_PASSWORD_INFO
{
	/* this+ 0 */ int Password;
	/* this+ 4 */ int ErrorCount;
	/* this+ 8 */ DWORD PanaltyTime;
	/* this+12 */ int MapID;
	/* this+16 */ int X;
	/* this+20 */ int Y;

	_CASHSHOP_PASSWORD_INFO()
	{
		this->_CASHSHOP_PASSWORD_INFO::Init();
	}

	void Init()
	{
		this->Password = 0;
		this->ErrorCount = 0;
		this->PanaltyTime = 0;
		this->MapID = 0;
		this->X = 0;
		this->Y = 0;
	}

	void InitPosition()
	{
		this->MapID = 0;
		this->X = 0;
		this->Y = 0;
	}
};


class CStorePasswordDB : public CODBC
{
public:
	CStorePasswordDB();
	~CStorePasswordDB();
	int GetStorePassword(int aid, _STORE_PASSWORD_INFO& info);
	int UpdateStorePassword(int aid, _STORE_PASSWORD_INFO& info);
	int GetCashPassword(int aid, _CASHSHOP_PASSWORD_INFO& info);
	int UpdateCashPassword(int aid, _CASHSHOP_PASSWORD_INFO& info);

private:
	int InsertStorePassword(int aid);
	int InsertCashPassword(int aid);
};
