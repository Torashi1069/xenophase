#pragma once
#include "AsyncDBWork/NODBCCtrl.h"
#include <sql.h>


class NODBCHandler
{
	/* this+0x0 */ //const NODBCHandler::`vftable'
	/* this+0x4 */ private: bool m_bOK;
	/* this+0x8 */ private: NODBCCtrl& m_vcODBCCtrl;
	/* this+0xC */ private: SQLHSTMT m_hStmt;

	private: bool NODBCHandler::Init(void);
	//public: bool isOK();
	//public: short NODBCHandler::ExecDirect(const mystd::string);
	//public: short UnBind();
	//public: short NODBCHandler::BindCol(unsigned short, short, void *, long, long *);
	//public: short NODBCHandler::BindParameter(unsigned short, short, short, short, unsigned long, short, void *, long, long *);
	//public: short GetData(unsigned short, short, void *, long, long *);
	//public: short CloseCursor();
	//public: short PutData(void *, long);
	//public: short NODBCHandler::Fetch();
	//public: short ParamData(void * *);
	//public: void * operator void *();
	//public: void NODBCHandler::OutputErrorString(const char *, const int, const char *);
	public: NODBCHandler::NODBCHandler(NODBCCtrl& in_cODBCCtrl);
	public: virtual NODBCHandler::~NODBCHandler(void);

private:
	static hook_method<bool (NODBCHandler::*)(void)> NODBCHandler::_Init;
};
