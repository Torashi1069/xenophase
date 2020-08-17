#pragma once
#include "Actor.h" // EFFECTIVE_INFO
#include "EStateTypeInfo.h"
#include "ScriptLib/BinBuf.h"


class EStateTypeInfoMgr
{
private:
	/* static  */ static EStateTypeInfoMgr*& m_cpSelf; //TODO
	/* this+ 0 */ //const EStateTypeInfoMgr::`vftable';
	/* this+ 4 */ bool m_bOK;
	typedef std::map<int,ESTATE*> ESTATETYPEINFO_CONTAINER;
	/* this+ 8 */ ESTATETYPEINFO_CONTAINER m_ESateTypeInfoList;
	typedef std::map<std::string,ESTATE*> ESTATETYPEINFO_NAME_CONTAINER;
	/* this+24 */ ESTATETYPEINFO_NAME_CONTAINER m_EStateTypeInfoNameList;
	/* this+40 */ CBinBuf m_binBuf;

private:
	bool Create();
	bool LoadConfigFile();
	void Destroy();

public:
	bool isOK() const;
	bool InitScript();
	bool IsSave(const unsigned long in_CurTM, const int in_Efst, const EFFECTIVE_INFO& in_Data);
	bool IsSaveInfinitTimeEfst(const int in_Efst) const;
	void SetComplete(const int in_EStateID, CActor* in_cpActor, const int in_Time, const int in_Val1, const int in_Val2, const int in_Val3);
	bool SetCheckup(const int in_EStateID, CActor* in_cpActor, int& io_Time, int& io_Val1, int& io_Val2, int& io_Val3);
	bool ResetCheckup(const int in_EStateID, CActor* in_cpActor, const int in_Val, EFFECTIVE_INFO* io_pInfo);
	void ResetComplete(const int in_EStateID, CActor* in_cpActor, const int in_Val1, const int in_Val2, const int in_Val3);
	void Process(const int in_EStateID, CActor* in_cpActor, EFFECTIVE_INFO* io_pInfo);
	ESTATE* GetPtr(const int in_EStateID);
	ESTATE* GetPtr(const char* in_EStateName);
	bool RunScript(const unsigned long in_AID, const int in_EventType, const int in_EStateID);
	int GetEStateID(const char* in_EStateName);

public:
	static bool CreateInstance();
	static void DestoryInstance();
	static EStateTypeInfoMgr* GetObj(); /// @custom

private:
	EStateTypeInfoMgr();
	virtual ~EStateTypeInfoMgr();
};
