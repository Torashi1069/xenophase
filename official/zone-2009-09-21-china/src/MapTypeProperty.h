#pragma once
#include "std/map"
#include "std/vector"


class CMapTypeProperty
{
	struct tagSelectedObject
	{
		int bPlayer : 1,
		    bMonter : 1,
		    bHomun : 1,
		    bMercenary : 1;
	};

	/* this+  0 */ public: //const CMapTypeProperty::`vftable';
	/* this+  4 */ private: bool m_bOK;
	/* this+  8 */ private: mystd::map<int,CMapTypeProperty::tagSelectedObject> m_BlockSkillContainer;
	/* this+ 20 */ private: mystd::vector<int> m_BlockItemContainer;
	/* this+ 36 */ private: mystd::map<int,int> m_TrapDurationContainer;
	/* this+ 48 */ private: mystd::map<int,int> m_SkillDamageContainer;
	/* this+ 60 */ private: mystd::vector<int> m_BlockEquipItemContainer;
	/* this+ 76 */ private: mystd::vector<int> m_BlockBuffContainer;
	/* this+ 92 */ private: bool m_MAPPROPERTY_PK;
	/* this+ 93 */ private: bool m_MAPPROPERTY_TELEPORT;
	/* this+ 94 */ private: bool m_MAPPROPERTY_NOTREMEMBER;
	/* this+ 95 */ private: bool m_MAPPROPERTY_ITEMDROP;
	/* this+ 96 */ private: bool m_MAPPROPERTY_EXP;
	/* this+ 87 */ private: bool m_MAPPROPERTY_DISCONNECT_NOTREMEMBER;
	/* this+ 98 */ private: bool m_MAPPROPERTY_CALLMONSTER;
	/* this+ 99 */ private: bool m_MAPPROPERTY_PARTY;
	/* this+100 */ private: bool m_MAPPROPERTY_GUILD;
	/* this+101 */ private: bool m_MAPPROPERTY_SIEGE;
	/* this+102 */ private: bool m_MAPPROPERTY_PKSERVER;
	/* this+103 */ private: bool m_MAPPROPERTY_PVPSERVER;
	/* this+104 */ private: bool m_MAPPROPERTY_DENYSKILL;
	/* this+105 */ private: bool m_MAPPROPERTY_TURBOTRACK;
	/* this+106 */ private: bool m_MAPPROPERTY_DENY_BUTTERFLY;
	/* this+107 */ private: bool m_MAPPROPERTY_USE_SIMPLE_EFFECT;
	/* this+108 */ private: bool m_MAPPROPERTY_DISABLE_LOCKON;
	/* this+109 */ private: bool m_MAPPROPERTY_COUNT_PK;
	/* this+110 */ private: bool m_MAPPROPERTY_NO_PARTY_FORMATION;
	/* this+111 */ private: bool m_MAPPROPERTY_BATTLEFIELD;
	/* this+112 */ private: bool m_MAPPROPERTY_HIDING_DAMAGE;
	/* this+113 */ private: bool m_MAPPROPERTY_DISABLE_KNOCKBACK;
	/* this+114 */ private: bool m_MAPPROPERTY_LONG_INSUPERABLE_TIME;
	/* this+115 */ private: bool m_MAPPROPERTY_NO_CHATTING;
	/* this+116 */ private: int m_MAPPROPERTY_NAMED_BOOTY;
	/* this+120 */ private: int m_MAPPROPERTY_SIEGETIME_VERSION;
	/* this+124 */ private: int m_MAPPROPERTY_GOTOTOWN;
	/* this+128 */ private: int m_MAPPROPERTY_NORMAL_DAMAGE;
	/* this+132 */ private: int m_MAPPROPERTY_RANGE_DAMAGE;
	/* this+136 */ private: int m_MAPPROPERTY_ALL_SKILL_DAMAGE;
	/* this+140 */ private: const int m_mapType;

	public: CMapTypeProperty::CMapTypeProperty(const int in_mapType);
	public: virtual CMapTypeProperty::~CMapTypeProperty(void);
	private: bool CMapTypeProperty::AddBlockSkill(const int in_SKID, const CMapTypeProperty::tagSelectedObject in_SelectedObject);
	private: bool CMapTypeProperty::AddBlockItem(const int in_ITID);
	private: bool CMapTypeProperty::AddProperty(const mystd::string in_PropertyName, const bool in_bEnable);
	private: bool CMapTypeProperty::AddPropertyValue(const mystd::string in_PropertyName, const int in_Value);
	private: bool CMapTypeProperty::AddTrapDurationPercent(const int in_SKID, const int in_Percent);
	private: bool CMapTypeProperty::AddSkillDamagePercent(const int in_SKID, const int in_Percent);
	private: bool CMapTypeProperty::AddBlockEquipItem(const int in_ITID);
	private: bool CMapTypeProperty::AddBlockBuff(const int in_BuffID);
	public: bool CMapTypeProperty::isOK(void);
	public: bool CMapTypeProperty::isBlockSkill(const int in_SKID, const int in_ObjectType);
	public: bool CMapTypeProperty::isBlockItem(const int in_ITID);
	public: bool CMapTypeProperty::isBlockEquipItem(const int in_ITID);
	public: bool CMapTypeProperty::isBlockBuff(const int in_BuffID);
	public: int CMapTypeProperty::IsItPossible(int property);
	public: int CMapTypeProperty::GetTrapDurationPercent(const int in_SKID);
	public: int CMapTypeProperty::GetSkillDamagePercent(const int in_SKID);
	public: void CMapTypeProperty::GetByteArray(unsigned char* out_pArray, const int in_MaxLength);

private:
	static hook_method<bool (CMapTypeProperty::*)(const int in_SKID, const CMapTypeProperty::tagSelectedObject in_SelectedObject)> CMapTypeProperty::_AddBlockSkill;
	static hook_method<bool (CMapTypeProperty::*)(const int in_ITID)> CMapTypeProperty::_AddBlockItem;
	static hook_method<bool (CMapTypeProperty::*)(const mystd::string in_PropertyName, const bool in_bEnable)> CMapTypeProperty::_AddProperty;
	static hook_method<bool (CMapTypeProperty::*)(const mystd::string in_PropertyName, const int in_Value)> CMapTypeProperty::_AddPropertyValue;
	static hook_method<bool (CMapTypeProperty::*)(const int in_SKID, const int in_Percent)> CMapTypeProperty::_AddTrapDurationPercent;
	static hook_method<bool (CMapTypeProperty::*)(const int in_SKID, const int in_Percent)> CMapTypeProperty::_AddSkillDamagePercent;
	static hook_method<bool (CMapTypeProperty::*)(const int in_ITID)> CMapTypeProperty::_AddBlockEquipItem;
	static hook_method<bool (CMapTypeProperty::*)(const int in_BuffID)> CMapTypeProperty::_AddBlockBuff;
	static hook_method<bool (CMapTypeProperty::*)(void)> CMapTypeProperty::_isOK;
	static hook_method<bool (CMapTypeProperty::*)(const int in_SKID, const int in_ObjectType)> CMapTypeProperty::_isBlockSkill;
	static hook_method<bool (CMapTypeProperty::*)(const int in_ITID)> CMapTypeProperty::_isBlockItem;
	static hook_method<bool (CMapTypeProperty::*)(const int in_ITID)> CMapTypeProperty::_isBlockEquipItem;
	static hook_method<bool (CMapTypeProperty::*)(const int in_BuffID)> CMapTypeProperty::_isBlockBuff;
	static hook_method<int (CMapTypeProperty::*)(int property)> CMapTypeProperty::_IsItPossible;
	static hook_method<int (CMapTypeProperty::*)(const int in_SKID)> CMapTypeProperty::_GetTrapDurationPercent;
	static hook_method<int (CMapTypeProperty::*)(const int in_SKID)> CMapTypeProperty::_GetSkillDamagePercent;
	static hook_method<void (CMapTypeProperty::*)(unsigned char* out_pArray, const int in_MaxLength)> CMapTypeProperty::_GetByteArray;
};
