#pragma once
#include "ScriptLib/BinBuf.h"
#include "ScriptLib/TokenData.h"


struct VarMap
{
	/* this+0 */ std::map<std::string,TokenData> data;

	VarMap()
	{
		this->VarMap::Clear();
	}

	bool IsEmpty(); //TODO

	void Clear()
	{
		this->data.clear();
		this->data["NULL"] = 0;
	}

	void Set(const char* str, const TokenData& t)
	{
		this->data[str] = t;
	}

	bool Get(const char* str, TokenData& t)
	{
		std::map<std::string,TokenData>::const_iterator mapi = this->data.find(str);
		if( mapi == this->data.end() )
			return false;

		t = mapi->second;
		return true;
	}

	bool IsExist(const char* ); //TODO
};


class CInterpretHandler
{
public:
	CInterpretHandler();
	~CInterpretHandler();

public:
	void SetVarMap(VarMap* varMap);
	virtual bool OnFunc(int func, std::deque<TokenData>& parm, TokenData& ret) = 0;
	virtual void OnError(const char* str) = 0;

protected:
	/* this+0 */ //const CInterpretHandler::`vftable';
	/* this+4 */ struct VarMap* m_varMap;
};


class CInterpreter
{
public:
	CInterpreter();
	~CInterpreter();

public:
	void Clear();
	void RegisterHandler(CInterpretHandler* handler);
	bool Scan(CBinBuf* binBuf, int pos);
	bool Run(CBinBuf* binBuf, int pos, bool gotoLock);
	bool Proc();
	int GetCurPos();
	void SetVar(const char* var, int value);

protected:
	virtual bool CodeFunc(TokenData& ret);
	virtual bool CodeMov();
	virtual bool CodeAdd();
	virtual bool CodeSub();
	virtual bool CodeMul();
	virtual bool CodeDiv();
	virtual bool CodeMod();
	virtual bool CodeInc();
	virtual bool CodeDec();
	virtual bool CodeCmp();
	virtual bool CodeGoto();
	virtual bool CodePush();
	virtual bool CodePop();
	virtual bool CodeCase();
	bool CheckType(char c);
	bool ReadCode(int& c);
	bool ReadNum(int& num);
	bool ReadStr(char* str, const int in_nMaxBufSize);
	bool ReadValue(TokenData& ret);
	bool ReadVar(char* var, const int in_nMaxBufSize);
	void Error(char* str, ...);

protected:
	/* this+0 */ //const CInterpreter::`vftable';
	/* this+4 */ struct VarMap m_varMap;

private:
	bool Goto(int pos);
	bool PeekByte(BYTE& data);
	bool GetByte(BYTE& data);
	bool GetWord(WORD& data);
	bool GetDword(DWORD& data);
	bool GetNum(int& data);
	bool GetStr(char* str, const int in_nMaxBufSize);

private:
	/* this+20 */ std::stack<TokenData> m_tokenDataStack;
	/* this+44 */ CInterpretHandler* m_handler;
	/* this+48 */ char* m_bin;
	/* this+52 */ int m_pos;
	/* this+56 */ int m_size;
	/* this+60 */ bool m_scan;
	/* this+61 */ bool m_gotoLock;
};
