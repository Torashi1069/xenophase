#pragma once
#include "std/map"
#include "std/string"
#include "std/vector"
#include "struct.hpp"


class CNPCAddSkillInfo
{
public:
	struct vtable_t
	{
		//TODO
	};

	/* this+0x0  */ void* vtable;
	/* this+0x4  */ mystd::map<mystd::string,unsigned long> m_scriptKeyword;
	/* this+0x10 */ mystd::map<unsigned long,mystd::map<unsigned long,mystd::vector<NPCSKILLINFO *> *> > m_map;
	/* this+0x1C */ mystd::map<unsigned long,NPC_CHAT_INFO> m_chat;

	//public: void CNPCAddSkillInfo::~CNPCAddSkillInfo(void);
	public: mystd::vector<NPCSKILLINFO *>* CNPCAddSkillInfo::Find(int spriteType, int state);
	public: int CNPCAddSkillInfo::Load(const char* file);
	public: const char* CNPCAddSkillInfo::GetNPCChat(int chatNo, unsigned long& color);
	private: int CNPCAddSkillInfo::LoadEntry(char* mob, char* status, char* skill, int level, int percent, int casttime, unsigned long cooldowntime, char* stTemp1, char* stTemp2, char* stTemp3, char* stTemp4, char* stTemp5, char* stTemp6);
	private: int CNPCAddSkillInfo::SetSkillInfo(NPCSKILLINFO* info, char** stTemp);
	private: void CNPCAddSkillInfo::InitKeyword(void);
	private: unsigned long CNPCAddSkillInfo::GetKeyWord(const char* strKeyWord);
	private: mystd::vector<NPCSKILLINFO *>* CNPCAddSkillInfo::InsertNewSkill(int spriteType, int state);
	private: void CNPCAddSkillInfo::Free(void);
	private: bool CNPCAddSkillInfo::LoadNPCChat(void);
	//public: void CNPCAddSkillInfo::CNPCAddSkillInfo(void);
private:
	static hook_method<mystd::vector<NPCSKILLINFO *>* (CNPCAddSkillInfo::*)(int spriteType, int state)> CNPCAddSkillInfo::_Find;
	static hook_method<int (CNPCAddSkillInfo::*)(const char* file)> CNPCAddSkillInfo::_Load;
	static hook_method<const char* (CNPCAddSkillInfo::*)(int chatNo, unsigned long& color)> CNPCAddSkillInfo::_GetNPCChat;
	static hook_method<int (CNPCAddSkillInfo::*)(char* mob, char* status, char* skill, int level, int percent, int casttime, unsigned long cooldowntime, char* stTemp1, char* stTemp2, char* stTemp3, char* stTemp4, char* stTemp5, char* stTemp6)> CNPCAddSkillInfo::_LoadEntry;
	static hook_method<int (CNPCAddSkillInfo::*)(NPCSKILLINFO* info, char** stTemp)> CNPCAddSkillInfo::_SetSkillInfo;
	static hook_method<void (CNPCAddSkillInfo::*)(void)> CNPCAddSkillInfo::_InitKeyword;
	static hook_method<unsigned long (CNPCAddSkillInfo::*)(const char* strKeyWord)> CNPCAddSkillInfo::_GetKeyWord;
	static hook_method<mystd::vector<NPCSKILLINFO *>* (CNPCAddSkillInfo::*)(int spriteType, int state)> CNPCAddSkillInfo::_InsertNewSkill;
	static hook_method<void (CNPCAddSkillInfo::*)(void)> CNPCAddSkillInfo::_Free;
	static hook_method<bool (CNPCAddSkillInfo::*)(void)> CNPCAddSkillInfo::_LoadNPCChat;
	static hook_method<void (CNPCAddSkillInfo::*)(void)> CNPCAddSkillInfo::_CNPCAddSkillInfo;
};
