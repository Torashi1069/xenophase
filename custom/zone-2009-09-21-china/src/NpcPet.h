#pragma once
#include "NPC.h"
#include "PollTimer.h"
#include "struct.hpp"


class CNpcPet : public CNPC
{
	struct vtable_t // const CNpcPet::`vftable'
	{
		/*  0 */ void* (CNpcPet::* scalar_deleting_destructor)(unsigned int flags);
		/* 65 */ void (CNpcPet::* OnProcess)(void);
		/* 67 */ int (CNpcPet::* GetSpeed)(void);
		/* 92 */ void (CNpcPet::* InitCore)(void);
	};

	/* this+   0 */ public: //CNPC baseclass_0;
	/* this+1132 */ private: int m_modified;
	/* this+1136 */ private: int m_fullness;
	/* this+1140 */ private: int m_relationship;
	/* this+1144 */ private: PET_INFO* m_petInfo;
	/* this+1148 */ private: int m_dbkey;
	/* this+1152 */ private: int m_myOwnerAID;
	/* this+1156 */ private: int m_fullGrade;
	/* this+1160 */ private: CPollTimer m_timerF;
	/* this+1168 */ private: CPollTimer m_timerHunger;
	/* this+1176 */ private: CPollTimer m_timerDB;

	public: CNpcPet::CNpcPet(void);
	public: virtual CNpcPet::~CNpcPet(void);
	public: virtual void CNpcPet::OnProcess(void);
	public: virtual int CNpcPet::GetSpeed(void);
	public: void CNpcPet::SetOwnerAID(unsigned long AID);
	public: int CNpcPet::GetPetDBKey(void);
	public: void CNpcPet::ModifyFullness(int delta);
	public: void CNpcPet::ModifyRelationship(int delta);
	public: void CNpcPet::SendPetState(char type, int data);
	public: void CNpcPet::MultiCastPetState(char type, int data);
	public: void CNpcPet::ModifyAccessary(int item);
	public: int CNpcPet::GetPetRG(int i);
	public: int CNpcPet::GetPetFG(int fullness);
	public: int CNpcPet::GetPerformanceNo(int iRelationship);
	public: void CNpcPet::OnTimerPet(void);
	public: void CNpcPet::InitPetTimer(DWORD dwTick);
	public: void CNpcPet::SendPetProperty(void);
	public: void CNpcPet::UpdateDB(void);
	public: void CNpcPet::InitPetProperty(const PET_PROPERTY& property);
	public: unsigned short CNpcPet::GetPetFoodKind(void);
	public: int CNpcPet::GetPetJob(void);
	public: void CNpcPet::ModifyLocation(int x, int y);
	public: void CNpcPet::OnRenamePet(char* name);
	public: void CNpcPet::OnPetMsg(CPC* sender, int par1, int par2);
	public: int CNpcPet::IsWearable(unsigned short item);
	public: int CNpcPet::GetRelationship(void);
	public: void CNpcPet::ConvertInto_PET_PROPERTY(PET_PROPERTY& property);
	public: bool CNpcPet::UpdateDB_WithGID(void);
	public: void CNpcPet::AddLog(int logtype);
	public: int CNpcPet::GetNameModified(void);
	private: virtual void CNpcPet::InitCore(void);
	private: CPC* CNpcPet::GetOwner(void);
	private: unsigned long CNpcPet::GetOwnerAID(void);

private:
	static hook_method<void (CNpcPet::*)(void)> CNpcPet::_OnProcess;
	static hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetSpeed;
	static hook_method<void (CNpcPet::*)(unsigned long AID)> CNpcPet::_SetOwnerAID;
	static hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetPetDBKey;
	static hook_method<void (CNpcPet::*)(int delta)> CNpcPet::_ModifyFullness;
	static hook_method<void (CNpcPet::*)(int delta)> CNpcPet::_ModifyRelationship;
	static hook_method<void (CNpcPet::*)(char type, int data)> CNpcPet::_SendPetState;
	static hook_method<void (CNpcPet::*)(char type, int data)> CNpcPet::_MultiCastPetState;
	static hook_method<void (CNpcPet::*)(int item)> CNpcPet::_ModifyAccessary;
	static hook_method<int (CNpcPet::*)(int i)> CNpcPet::_GetPetRG;
	static hook_method<int (CNpcPet::*)(int fullness)> CNpcPet::_GetPetFG;
	static hook_method<int (CNpcPet::*)(int iRelationship)> CNpcPet::_GetPerformanceNo;
	static hook_method<void (CNpcPet::*)(void)> CNpcPet::_OnTimerPet;
	static hook_method<void (CNpcPet::*)(DWORD dwTick)> CNpcPet::_InitPetTimer;
	static hook_method<void (CNpcPet::*)(void)> CNpcPet::_SendPetProperty;
	static hook_method<void (CNpcPet::*)(void)> CNpcPet::_UpdateDB;
	static hook_method<void (CNpcPet::*)(const PET_PROPERTY& property)> CNpcPet::_InitPetProperty;
	static hook_method<unsigned short (CNpcPet::*)(void)> CNpcPet::_GetPetFoodKind;
	static hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetPetJob;
	static hook_method<void (CNpcPet::*)(int x, int y)> CNpcPet::_ModifyLocation;
	static hook_method<void (CNpcPet::*)(char* name)> CNpcPet::_OnRenamePet;
	static hook_method<void (CNpcPet::*)(CPC* sender, int par1, int par2)> CNpcPet::_OnPetMsg;
	static hook_method<int (CNpcPet::*)(unsigned short item)> CNpcPet::_IsWearable;
	static hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetRelationship;
	static hook_method<void (CNpcPet::*)(PET_PROPERTY& property)> CNpcPet::_ConvertInto_PET_PROPERTY;
	static hook_method<bool (CNpcPet::*)(void)> CNpcPet::_UpdateDB_WithGID;
	static hook_method<void (CNpcPet::*)(int logtype)> CNpcPet::_AddLog;
	static hook_method<int (CNpcPet::*)(void)> CNpcPet::_GetNameModified;
	static hook_method<void (CNpcPet::*)(void)> CNpcPet::_InitCore;
	static hook_method<CPC* (CNpcPet::*)(void)> CNpcPet::_GetOwner;
	static hook_method<unsigned long (CNpcPet::*)(void)> CNpcPet::_GetOwnerAID;
};
