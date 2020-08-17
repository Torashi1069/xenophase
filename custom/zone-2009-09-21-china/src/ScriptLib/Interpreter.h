#pragma once
#include "std/map"
#include "std/stack"
#include "struct.hpp"
class CInterpretHandler;


struct VarMap
{
	/* this+0 */ mystd::map<mystd::string,TokenData> data;

	public: VarMap::VarMap(void);
	//public: bool VarMap::IsEmpty(void);
	public: void VarMap::Clear(void);
	public: void VarMap::Set(const char* str, const struct TokenData& t);
	public: bool VarMap::Get(const char* str, struct TokenData& t);
	//public: bool VarMap::IsExist(const char* str);
};


class CInterpreter
{
	public: struct vtable_t // const CInterpreter::`vftable'
	{
		bool (CInterpreter::* CodeFunc)(TokenData& ret);
		bool (CInterpreter::* CodeMov)(void);
		bool (CInterpreter::* CodeAdd)(void);
		bool (CInterpreter::* CodeSub)(void);
		bool (CInterpreter::* CodeMul)(void);
		bool (CInterpreter::* CodeDiv)(void);
		bool (CInterpreter::* CodeMod)(void);
		bool (CInterpreter::* CodeInc)(void);
		bool (CInterpreter::* CodeDec)(void);
		bool (CInterpreter::* CodeCmp)(void);
		bool (CInterpreter::* CodeGoto)(void);
		bool (CInterpreter::* CodePush)(void);
		bool (CInterpreter::* CodePop)(void);
		bool (CInterpreter::* CodeCase)(void);
	};

	/* this+ 0 */ public: //const CInterpreter::`vftable';
	/* this+ 4 */ protected: VarMap m_varMap;
	/* this+16 */ private: mystd::stack<TokenData> m_tokenDataStack;
	/* this+48 */ private: CInterpretHandler* m_handler;
	/* this+52 */ private: char* m_bin;
	/* this+56 */ private: int m_pos;
	/* this+60 */ private: int m_size;
	/* this+64 */ private: bool m_scan;
	/* this+65 */ private: bool m_gotoLock;

	//public: CInterpreter::CInterpreter(void);
	//public: CInterpreter::~CInterpreter(void);
	//public: void CInterpreter::Clear();
	//public: void CInterpreter::RegisterHandler(CInterpretHandler *);
	//public: bool CInterpreter::Scan(CBinBuf *, int);
	//public: bool CInterpreter::Run(CBinBuf *, int, bool);
	public: bool CInterpreter::Proc(void);
	public: int CInterpreter::GetCurPos(void);
	//public: void CInterpreter::SetVar(const char *, int);
	protected: virtual bool CInterpreter::CodeFunc(TokenData& ret);
	protected: virtual bool CInterpreter::CodeMov(void);
	protected: virtual bool CInterpreter::CodeAdd(void);
	protected: virtual bool CInterpreter::CodeSub(void);
	protected: virtual bool CInterpreter::CodeMul(void);
	protected: virtual bool CInterpreter::CodeDiv(void);
	protected: virtual bool CInterpreter::CodeMod(void);
	protected: virtual bool CInterpreter::CodeInc(void);
	protected: virtual bool CInterpreter::CodeDec(void);
	protected: virtual bool CInterpreter::CodeCmp(void);
	protected: virtual bool CInterpreter::CodeGoto(void);
	protected: virtual bool CInterpreter::CodePush(void);
	protected: virtual bool CInterpreter::CodePop(void);
	protected: virtual bool CInterpreter::CodeCase(void);
	//protected: bool CInterpreter::CheckType(char);
	protected: bool CInterpreter::ReadCode(int& c);
	//protected: bool CInterpreter::ReadNum(int &);
	//protected: bool CInterpreter::ReadStr(char *);
	protected: bool CInterpreter::ReadValue(TokenData& ret);
	//protected: bool CInterpreter::ReadVar(char *);
	protected: void CInterpreter::Error(char* str, ...);
	//private: bool CInterpreter::Goto(int);
	//private: bool CInterpreter::PeekByte(unsigned char &);
	private: bool CInterpreter::GetByte(unsigned char& data);
	private: bool CInterpreter::GetWord(unsigned short& data);
	//private: bool CInterpreter::GetDword(unsigned long &);
	//private: bool CInterpreter::GetNum(int &);
	//private: bool CInterpreter::GetStr(char *);

private:
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_Proc;
	static hook_method<int (CInterpreter::*)(void)> CInterpreter::_GetCurPos;
	static hook_method<bool (CInterpreter::*)(TokenData& ret)> CInterpreter::_CodeFunc;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeMov;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeAdd;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeSub;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeMul;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeDiv;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeMod;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeInc;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeDec;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeCmp;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeGoto;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodePush;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodePop;
	static hook_method<bool (CInterpreter::*)(void)> CInterpreter::_CodeCase;
	static hook_method<bool (CInterpreter::*)(int& c)> CInterpreter::_ReadCode;
	static hook_method<bool (CInterpreter::*)(TokenData& ret)> CInterpreter::_ReadValue;
	static hook_method<void (CInterpreter::*)(char* str, ...)> CInterpreter::_Error;
	static hook_method<bool (CInterpreter::*)(unsigned char& data)> CInterpreter::_GetByte;
	static hook_method<bool (CInterpreter::*)(unsigned short& data)> CInterpreter::_GetWord;
};
