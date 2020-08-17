#pragma once


///@see CMapTypeProperty::IsItPossible()
enum enumMAPPROPERTY
{
	MAPPROPERTY_PK                          = 0,
	MAPPROPERTY_TELEPORT                    = 1,
	MAPPROPERTY_NOTREMEMBER                 = 2,
	MAPPROPERTY_ITEMDROP                    = 3,
	MAPPROPERTY_EXP                         = 4,
	MAPPROPERTY_DISCONNECT_NOTREMEMBER      = 5,
	MAPPROPERTY_CALLMONSTER                 = 6,
	MAPPROPERTY_PARTY                       = 7,
	MAPPROPERTY_GUILD                       = 8,
	MAPPROPERTY_SIEGE                       = 9,
	MAPPROPERTY_PKSERVER                    = 10,
	MAPPROPERTY_PVPSERVER                   = 11,
	MAPPROPERTY_DENYSKILL                   = 12,
	MAPPROPERTY_TURBOTRACK                  = 13,
	MAPPROPERTY_DENY_BUTTERFLY              = 14,
	MAPPROPERTY_USE_SIMPLE_EFFECT           = 15,
	MAPPROPERTY_DISABLE_LOCKON              = 16,
	MAPPROPERTY_COUNT_PK                    = 17,
	MAPPROPERTY_NO_PARTY_FORMATION          = 18,
	MAPPROPERTY_BATTLEFIELD                 = 19,
	MAPPROPERTY_DISABLE_COSTUMEITEM         = 20,
	MAPPROPERTY_PREVENT_PARTY_MAKE          = 21,
	MAPPROPERTY_PREVENT_PARTY_JOIN          = 22,
	MAPPROPERTY_PREVENT_PARTY_LEAVE         = 23,
	MAPPROPERTY_PREVENT_PARTY_EXPEL         = 24,
	MAPPROPERTY_SHOW_HP_BAR                 = 25,
	MAPPROPERTY_PREVENT_PARTY_MASTER_CHANGE = 26,
	MAPPROPERTY_LAST                        = 27,
	MAPPROPERTY_HIDING_DAMAGE               = 28,
	MAPPROPERTY_DISABLE_KNOCKBACK           = 29,
	MAPPROPERTY_LONG_INSUPERABLE_TIME       = 30,
	MAPPROPERTY_NAMED_BOOTY                 = 31,
	MAPPROPERTY_SIEGETIME_VERSION           = 32,
	MAPPROPERTY_GOTOTOWN                    = 33,
	MAPPROPERTY_NORMAL_DAMAGE               = 34,
	MAPPROPERTY_RANGE_DAMAGE                = 35,
	MAPPROPERTY_BLOCK_EQUIPITEM             = 36,
	MAPPROPERTY_BLOCK_BUFF                  = 37,
	MAPPROPERTY_NO_CHATTING                 = 38,
	MAPPROPERTY_EXCHANGEITEM                = 39,
	MAPPROPERTY_USECART                     = 40,
	MAPPROPERTY_SUNMOONSTAR_MIRACLE         = 41,
	MAPPROPERTY_INEFFECT_EQUIPITEM          = 42,
};


class CMapTypeProperty
{
private:
	/* this+  0 */ //const CMapTypeProperty::`vftable';
	/* this+  4 */ bool m_bOK;

	struct tagSelectedObject
	{
		/* this(bf)+0:0 len( 1) */ int bPlayer    :  1;
		/* this(bf)+0:1 len( 1) */ int bMonster   :  1;
		/* this(bf)+0:2 len( 1) */ int bHomun     :  1;
		/* this(bf)+0:3 len( 1) */ int bMercenary :  1;
		/* this(bf)+4:0 len(32) */ int unused     : 32;
	};

	typedef std::map<int,tagSelectedObject> BLOCKSKILL_CONTAINER;
	typedef std::map<int,tagSelectedObject>::iterator BLOCKSKILL_CONTAINER_ITER;
	/* this+  8 */ BLOCKSKILL_CONTAINER m_BlockSkillContainer;

	typedef std::vector<int> BLOCKITEM_CONTAINER;
	typedef std::vector<int>::iterator BLOCKITEM_CONTAINER_ITER;
	/* this+ 24 */ BLOCKITEM_CONTAINER m_BlockItemContainer;

	typedef std::map<int,int> TRAPDURATION_CONTAINER;
	typedef std::map<int,int>::iterator TRAPDURATION_CONTAINER_ITER;
	/* this+ 40 */ TRAPDURATION_CONTAINER m_TrapDurationContainer;

	typedef std::map<int,int> SKILLDAMAGE_CONTAINER;
	typedef std::map<int,int>::iterator SKILLDAMAGE_CONTAINER_ITER;
	/* this+ 56 */ SKILLDAMAGE_CONTAINER m_SkillDamageContainer;

	typedef std::vector<int> BLOCKEQUIPITEM_CONTAINER;
	typedef std::vector<int>::iterator BLOCKEQUIPITEM_CONTAINER_ITER;
	/* this+ 72 */ BLOCKEQUIPITEM_CONTAINER m_BlockEquipItemContainer;

	typedef std::vector<int> BLOCKBUFF_CONTAINER;
	typedef std::vector<int>::iterator BLOCKBUFF_CONTAINER_ITER;
	/* this+ 88 */ BLOCKBUFF_CONTAINER m_BlockBuffContainer;

	/* this+104 */ bool m_MAPPROPERTY_PK;
	/* this+105 */ bool m_MAPPROPERTY_TELEPORT;
	/* this+106 */ bool m_MAPPROPERTY_NOTREMEMBER;
	/* this+107 */ bool m_MAPPROPERTY_ITEMDROP;
	/* this+108 */ bool m_MAPPROPERTY_EXP;
	/* this+109 */ bool m_MAPPROPERTY_DISCONNECT_NOTREMEMBER;
	/* this+110 */ bool m_MAPPROPERTY_CALLMONSTER;
	/* this+111 */ bool m_MAPPROPERTY_PARTY;
	/* this+112 */ bool m_MAPPROPERTY_GUILD;
	/* this+113 */ bool m_MAPPROPERTY_SIEGE;
	/* this+114 */ bool m_MAPPROPERTY_PKSERVER;
	/* this+115 */ bool m_MAPPROPERTY_PVPSERVER;
	/* this+116 */ bool m_MAPPROPERTY_DENYSKILL;
	/* this+117 */ bool m_MAPPROPERTY_TURBOTRACK;
	/* this+118 */ bool m_MAPPROPERTY_DENY_BUTTERFLY;
	/* this+119 */ bool m_MAPPROPERTY_USE_SIMPLE_EFFECT;
	/* this+120 */ bool m_MAPPROPERTY_DISABLE_LOCKON;
	/* this+121 */ bool m_MAPPROPERTY_COUNT_PK;
	/* this+122 */ bool m_MAPPROPERTY_NO_PARTY_FORMATION;
	/* this+123 */ bool m_MAPPROPERTY_BATTLEFIELD;
	/* this+124 */ bool m_MAPPROPERTY_HIDING_DAMAGE;
	/* this+125 */ bool m_MAPPROPERTY_DISABLE_KNOCKBACK;
	/* this+126 */ bool m_MAPPROPERTY_LONG_INSUPERABLE_TIME;
	/* this+127 */ bool m_MAPPROPERTY_NO_CHATTING;
	/* this+128 */ bool m_MAPPROPERTY_DISABLE_COSTUMEITEM;
	/* this+129 */ bool m_MAPPROPERTY_PREVENT_PARTY_MAKE;
	/* this+130 */ bool m_MAPPROPERTY_PREVENT_PARTY_JOIN;
	/* this+131 */ bool m_MAPPROPERTY_PREVENT_PARTY_LEAVE;
	/* this+132 */ bool m_MAPPROPERTY_PREVENT_PARTY_EXPEL;
	/* this+133 */ bool m_MAPPROPERTY_PREVENT_PARTY_MASTER_CHANGE;
	/* this+136 */ int m_MAPPROPERTY_NAMED_BOOTY;
	/* this+140 */ int m_MAPPROPERTY_SIEGETIME_VERSION;
	/* this+144 */ int m_MAPPROPERTY_GOTOTOWN;
	/* this+148 */ int m_MAPPROPERTY_NORMAL_DAMAGE;
	/* this+152 */ int m_MAPPROPERTY_RANGE_DAMAGE;
	/* this+156 */ int m_MAPPROPERTY_ALL_SKILL_DAMAGE;
	/* this+160 */ const int m_mapType;

private:
	bool AddBlockSkill(const int in_SKID, const tagSelectedObject in_SelectedObject);
	bool AddBlockItem(const int in_ITID);
	bool AddProperty(const std::string in_PropertyName, const bool in_bEnable);
	bool AddPropertyValue(const std::string in_PropertyName, const int in_Value);
	bool AddTrapDurationPercent(const int in_SKID, const int in_Percent);
	bool AddSkillDamagePercent(const int in_SKID, const int in_Percent);
	bool AddBlockEquipItem(const int in_ITID);
	bool AddBlockBuff(const int in_BuffID);

public:
	bool isOK() const;
	bool isBlockSkill(const int in_SKID, const int in_ObjectType);
	bool isBlockItem(const int in_ITID);
	bool isBlockEquipItem(const int in_ITID);
	bool isBlockBuff(const int in_BuffID);
	int IsItPossible(int property);
	int GetTrapDurationPercent(const int in_SKID);
	int GetSkillDamagePercent(const int in_SKID);
	void GetByteArray(BYTE* out_pArray, const int in_MaxLength);

public:
	CMapTypeProperty(const int in_mapType);
	virtual ~CMapTypeProperty();
};
