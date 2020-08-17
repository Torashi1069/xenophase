#pragma once
#include "ScriptLib/Interpreter.h"
#include "CInterpretHandler.hpp"
#include "std/string"
class CNPC;


class CScriptEventHandler : public CInterpretHandler
{
	struct vtable_t // const CScriptEventHandler::`vftable'
	{
		bool (CScriptEventHandler::* OnFunc)(int func, mystd::deque<TokenData>& parm, TokenData& ret);
		void (CScriptEventHandler::* OnError)(const char* str);
		void (CScriptEventHandler::* Free)(void);
		unsigned int (CScriptEventHandler::* Proc)(bool isOnce);
		bool (CScriptEventHandler::* FuncDialog)(char* str, int npcID);
		bool (CScriptEventHandler::* FuncCloseDialog)(int npcID);
		bool (CScriptEventHandler::* FuncWaitDialog)(int npcID);
		bool (CScriptEventHandler::* FuncDlgWriteStr)(int npcID);
		bool (CScriptEventHandler::* FuncMenu)(mystd::deque<TokenData>& parm, int npcID);
		bool (CScriptEventHandler::* FuncMapMove)(const char* zone, int x, int y);
		bool (CScriptEventHandler::* FuncSetEffectStatus)(int effectenum);
		void (CScriptEventHandler::* EventLog)(char* str, ...);
	};

	/* this+  0 */ public: //CInterpretHandler baseclass_0;
	/* this+  8 */ protected: int m_ownerID;
	/* this+ 12 */ protected: CInterpreter m_interpreter;
	/* this+ 80 */ protected: mystd::string m_inputstr;
	/* this+108 */ protected: int m_nParamSize;
	/* this+112 */ protected: int m_suspendType;
	/* this+116 */ protected: int m_suspendTime;
	/* this+120 */ protected: bool m_isQuit;

	//public: void CScriptEventHandler::CScriptEventHandler();
	public: virtual bool CScriptEventHandler::OnFunc(int func, mystd::deque<TokenData>& parm, TokenData& ret);
	public: virtual void CScriptEventHandler::OnError(const char* str);
	public: virtual void CScriptEventHandler::Free(void);
	public: virtual unsigned int CScriptEventHandler::Proc(bool isOnce);
	//public: void CScriptEventHandler::OnMsg(unsigned long, int, int, int);
	//public: void CScriptEventHandler::Init(int);
	//public: int CScriptEventHandler::GetOwnerID();
	//public: bool CScriptEventHandler::RunInterpreter(CBinBuf*, int);
	protected: bool CScriptEventHandler::CheckFixedVarNum(mystd::deque<TokenData>& parm, int n);
	//protected: void CScriptEventHandler::BanPlayer();
	protected: bool CScriptEventHandler::FuncPutMob(const char* zone, int x, int y, int w, int h, int num, int mobId, int regenMin, int regenMax, int regenType, char* name, bool isBoss);
	protected: bool CScriptEventHandler::FuncGetEquipIsSuccessRefinery(int part, TokenData& ret, bool isAdvanced);
	//protected: bool CScriptEventHandler::FuncResetSkill();
	//protected: bool CScriptEventHandler::FuncShowImage(char *, int);
	//protected: bool CScriptEventHandler::FuncPcName(TokenData &);
	//protected: bool CScriptEventHandler::FuncInputStr(TokenData &);
	//protected: bool CScriptEventHandler::FuncBroadcastServer(char *, int, int, int, int, char *);
	//protected: bool CScriptEventHandler::FuncReadBook(int, int);
	protected: bool CScriptEventHandler::FuncGetEquipPercentRefinery(int part, TokenData& ret, bool isAdvanced);
	//protected: bool CScriptEventHandler::FuncGetEquipWeaponLv(int, TokenData &);
	//protected: bool CScriptEventHandler::FuncGetWeaponClass(int, TokenData &);
	//protected: bool CScriptEventHandler::FuncGetEquipSlotAmount(int, TokenData &);
	//protected: bool CScriptEventHandler::FuncSetBuff(char *, int, int);
	//protected: bool CScriptEventHandler::FuncGetBuffValue(char *, TokenData &);
	//protected: bool CScriptEventHandler::FuncLoudSpeaker(char *, int, int, int, int, char *);
	//protected: bool CScriptEventHandler::FuncTargetAttackedBuff(int, int, int, char *, int, int);
	//protected: bool CScriptEventHandler::FuncGetMapName(TokenData &);
	//protected: bool CScriptEventHandler::FuncGetActivatedSkill(TokenData &);
	//protected: bool CScriptEventHandler::FuncGetDeactivatedSkill(TokenData &);
	//protected: bool CScriptEventHandler::FuncIsSuccessRuneUse(int, TokenData &);
	//protected: bool CScriptEventHandler::FuncGetPetRelationship(TokenData &);
	//protected: bool CScriptEventHandler::FuncIsEffectStatus(int, TokenData &);
	//protected: bool CScriptEventHandler::FuncRand(int, int, TokenData &);
	//protected: bool CScriptEventHandler::FuncIsPcCafe(TokenData &);
	//protected: bool CScriptEventHandler::FuncIsPremiumPcCafe(TokenData &);
	//protected: bool CScriptEventHandler::FuncGetExdEquipIsSuccessRefinery(int, bool, TokenData &);
	//protected: bool CScriptEventHandler::FuncDownRefItem(int, int);
	//protected: bool CScriptEventHandler::FuncDownAdvRefItem(int);
	//protected: bool CScriptEventHandler::FuncSuccessRandomRefItem(int, int, int, bool, TokenData &);
	protected: virtual bool CScriptEventHandler::FuncDialog(char* str, int npcID);
	protected: virtual bool CScriptEventHandler::FuncCloseDialog(int npcID);
	protected: virtual bool CScriptEventHandler::FuncWaitDialog(int npcID);
	protected: virtual bool CScriptEventHandler::FuncDlgWriteStr(int npcID);
	protected: virtual bool CScriptEventHandler::FuncMenu(mystd::deque<TokenData>& parm, int npcID);
	protected: virtual bool CScriptEventHandler::FuncMapMove(const char* zone, int x, int y);
	protected: virtual bool CScriptEventHandler::FuncSetEffectStatus(int effectenum);
	protected: HOOKED CNPC* CScriptEventHandler::AddNpc(int id, const char* mapName, NpcSvrNpcInfo* npcInfo);
	protected: virtual void CScriptEventHandler::EventLog(char* str, ...);
	//private: void CScriptEventHandler::Exit();
	//private: bool CScriptEventHandler::CheckSuspendType(int);
	//private: void CScriptEventHandler::Suspend(int, int);
	//private: short CScriptEventHandler::OnItemFunc(int, mystd::deque<TokenData> &, TokenData &);
	//private: short CScriptEventHandler::OnNpcFunc(int, mystd::deque<TokenData> &, TokenData &);
	//public: void CScriptEventHandler::~CScriptEventHandler();

private:
	static hook_method<bool (CScriptEventHandler::*)(int func, mystd::deque<TokenData>& parm, TokenData& ret)> CScriptEventHandler::_OnFunc;
	static hook_method<void (CScriptEventHandler::*)(const char* str)> CScriptEventHandler::_OnError;
	static hook_method<void (CScriptEventHandler::*)(void)> CScriptEventHandler::_Free;
	static hook_method<unsigned int (CScriptEventHandler::*)(bool isOnce)> CScriptEventHandler::_Proc;
	static hook_method<bool (CScriptEventHandler::*)(mystd::deque<TokenData>& parm, int n)> CScriptEventHandler::_CheckFixedVarNum;
	static hook_method<bool (CScriptEventHandler::*)(const char* zone, int x, int y, int w, int h, int num, int mobId, int regenMin, int regenMax, int regenType, char* name, bool isBoss)> CScriptEventHandler::_FuncPutMob;
	static hook_method<bool (CScriptEventHandler::*)(int part, TokenData& ret, bool isAdvanced)> CScriptEventHandler::_FuncGetEquipIsSuccessRefinery;
	static hook_method<bool (CScriptEventHandler::*)(int part, TokenData& ret, bool isAdvanced)> CScriptEventHandler::_FuncGetEquipPercentRefinery;
	static hook_method<bool (CScriptEventHandler::*)(char* str, int npcID)> CScriptEventHandler::_FuncDialog;
	static hook_method<bool (CScriptEventHandler::*)(int npcID)> CScriptEventHandler::_FuncCloseDialog;
	static hook_method<bool (CScriptEventHandler::*)(int npcID)> CScriptEventHandler::_FuncWaitDialog;
	static hook_method<bool (CScriptEventHandler::*)(int npcID)> CScriptEventHandler::_FuncDlgWriteStr;
	static hook_method<bool (CScriptEventHandler::*)(mystd::deque<TokenData>& parm, int npcID)> CScriptEventHandler::_FuncMenu;
	static hook_method<bool (CScriptEventHandler::*)(const char* zone, int x, int y)> CScriptEventHandler::_FuncMapMove;
	static hook_method<bool (CScriptEventHandler::*)(int effectenum)> CScriptEventHandler::_FuncSetEffectStatus;
	static hook_method<CNPC* (CScriptEventHandler::*)(int id, const char* mapName, NpcSvrNpcInfo* npcInfo)> CScriptEventHandler::_AddNpc;
	static hook_method<void (CScriptEventHandler::*)(char* str, ...)> CScriptEventHandler::_EventLog;
};
