#pragma once
#include "std/map"
#include "std/vector"
#include "CFTToken.hpp"


class CMercenarySkillMgr
{
public:
	class SKILLINFO
	{
		/* this+0x0 */ int SKID;
		/* this+0x4 */ int Level;

		//public: void SKILLINFO();
	};

	class ANAYSISRET
	{
		enum enumCode
		{
			CODE_SUCCESS = 0x0,
			CODE_ERROR = 0x1,
			CODE_ERROR_LEXICALANALYSIS_INITIALIZE = 0x2,
			CODE_ERROR_GET_TOKEN = 0x3,
			CODE_ERROR_SYNTAX = 0x4,
			CODE_ERROR_UNKNOWN = 0x5,
			CODE_ERROR_INSERT_PACKAGE = 0x6,
			CODE_ERROR_INSERT_BOX = 0x7,
			CODE_ERROR_UNKNOWN_ITEMID = 0x8,
			CODE_ERROR_EQUIPTITEM_COUNT = 0x9,
		};

		/* this+0x0  */ CFTToken Token;
		/* this+0x2C */ enum CMercenarySkillMgr::ANAYSISRET::enumCode Code;

		//public: void CMercenarySkillMgr::ANAYSISRET::ANAYSISRET(const CMercenarySkillMgr::ANAYSISRET& __that);
		//public: void CMercenarySkillMgr::ANAYSISRET::ANAYSISRET(const enum CMercenarySkillMgr::ANAYSISRET::enumCode in_Code, CFTToken& in_Token);
		//public: void CMercenarySkillMgr::ANAYSISRET::ANAYSISRET(const enum CMercenarySkillMgr::ANAYSISRET::enumCode in_Code);
		//public: void CMercenarySkillMgr::ANAYSISRET::~ANAYSISRET(void);
	};

	/* this+0x0 */ //const CMercenarySkillMgr::`vftable'
	/* static   */ private: static hook_ptr<CMercenarySkillMgr *> m_cpSelf;
	/* this+0x4 */ private: bool m_bOK;
	/* this+0x8 */ private: mystd::map<int,mystd::vector<CMercenarySkillMgr::SKILLINFO> > m_JobSkillContainer;

	private: bool CMercenarySkillMgr::Create(void);
	private: void CMercenarySkillMgr::Destroy(void);
	//private: CMercenarySkillMgr::ANAYSISRET CMercenarySkillMgr::Anaysis(const mystd::string in_strFileName);
	//private: CMercenarySkillMgr::ANAYSISRET CMercenarySkillMgr::Anaysis_JobBlock(CFTLexicalAnaysis& result, const int in_Job);
	//public: bool CMercenarySkillMgr::isOK(void);
	//public: void CMercenarySkillMgr::AddSkill(const CNpcMercenary* in_cpMercenary);
	public: static bool __cdecl CMercenarySkillMgr::CreateInstance(void);
	public: static void __cdecl CMercenarySkillMgr::DestroyInstance(void);
	private: CMercenarySkillMgr::CMercenarySkillMgr(void);
	private: virtual CMercenarySkillMgr::~CMercenarySkillMgr(void);

private:
	static hook_method<bool (CMercenarySkillMgr::*)(void)> CMercenarySkillMgr::_Create;
	static hook_method<void (CMercenarySkillMgr::*)(void)> CMercenarySkillMgr::_Destroy;
	static hook_method<static bool (__cdecl *)(void)> CMercenarySkillMgr::_CreateInstance;
	static hook_method<static void (__cdecl *)(void)> CMercenarySkillMgr::_DestroyInstance;
};
