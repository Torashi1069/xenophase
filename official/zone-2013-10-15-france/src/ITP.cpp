#include "Enum.h"
#include "ITP.h"
#include "shared/shared.h"
////////////////////////////////////////


CITP::CITP()
{
//	m_ITID = 0;
	m_bCashItem = false;
	m_isUseEvent = false;
	m_weight = 0;
	m_price = 0;
	m_isRefinable = FALSE;
	m_isDamagable = FALSE;
	m_isMovable = 0;
	m_availableJob = 0;
	m_isBindOnEquip = false;
	m_location = 0;
	m_name[0] = '\0';
	m_minLevel = 1;
	m_maxLevel = 150;
}


////////////////////////////////////////


void CITP::Init()
{
	m_weight = 0;
	m_price = 0;
	m_isRefinable = FALSE;
	m_isDamagable = FALSE;
	m_isMovable = 0;
	m_availableJob = 0;
	m_isBindOnEquip = false;
	m_minLevel = 1;
	m_maxLevel = 150;
}


void CITPHeal::Init()
{
}


void CITPSpecial::Init()
{
}


void CITPEvent::Init()
{
}


void CITPArrow::Init()
{
}


void CITPArmor::Init()
{
}


void CITPWeapon::Init()
{
}


void CITPBothhand::Init()
{
}


void CITPBow::Init()
{
}


void CITPGun::Init()
{
}


void CITPCard::Init()
{
}


void CITPQuest::Init()
{
	this->CITP::Init();
	m_isMovable = NOTMOVE_ALL;
}


void CITPCashPointItem::Init()
{
	return this->CITP::Init();
}


////////////////////////////////////////


BOOL CITP::IsApparel()
{
	return FALSE;
}


BOOL CITPHeal::IsApparel()
{
	return FALSE;
}


BOOL CITPSpecial::IsApparel()
{
	return FALSE;
}


BOOL CITPEvent::IsApparel()
{
	return FALSE;
}


BOOL CITPArrow::IsApparel()
{
	return FALSE;
}


BOOL CITPAmmo::IsApparel()
{
	return FALSE;
}


BOOL CITPThrow::IsApparel()
{
	return FALSE;
}


BOOL CITPArmor::IsApparel()
{
	return TRUE;
}


BOOL CITPWeapon::IsApparel()
{
	return TRUE;
}


BOOL CITPBothhand::IsApparel()
{
	return TRUE;
}


BOOL CITPBow::IsApparel()
{
	return TRUE;
}


BOOL CITPGun::IsApparel()
{
	return TRUE;
}


BOOL CITPCard::IsApparel()
{
	return FALSE;
}


BOOL CITPQuest::IsApparel()
{
	return FALSE;
}


BOOL CITPCashPointItem::IsApparel()
{
	return FALSE;
}


BOOL CITPCannonball::IsApparel()
{
	return FALSE;
}


////////////////////////////////////////


unsigned short CITP::GetType()
{
	return 0; // TYPE_HEAL
}


unsigned short CITPHeal::GetType()
{
	return TYPE_HEAL;
}


unsigned short CITPSpecial::GetType()
{
	return TYPE_SPECIAL;
}


unsigned short CITPEvent::GetType()
{
	return TYPE_EVENT;
}


unsigned short CITPArrow::GetType()
{
	return TYPE_ARROW;
}


unsigned short CITPAmmo::GetType()
{
	return TYPE_AMMO;
}


unsigned short CITPThrow::GetType()
{
	return TYPE_THROWWEAPON;
}


unsigned short CITPArmor::GetType()
{
	return TYPE_ARMOR;
}


unsigned short CITPArmorTM::GetType()
{
	return TYPE_ARMORTM;
}


unsigned short CITPArmorTB::GetType()
{
	return TYPE_ARMORTB;
}


unsigned short CITPArmorMB::GetType()
{
	return TYPE_ARMORMB;
}


unsigned short CITPArmorTMB::GetType()
{
	return TYPE_ARMORTMB;
}


unsigned short CITPWeapon::GetType()
{
	return TYPE_WEAPON;
}


unsigned short CITPBothhand::GetType()
{
	return TYPE_BOTHHAND;
}


unsigned short CITPBow::GetType()
{
	return TYPE_BOW;
}


unsigned short CITPGun::GetType()
{
	return TYPE_GUN;
}


unsigned short CITPCard::GetType()
{
	return TYPE_CARD;
}


unsigned short CITPQuest::GetType()
{
	return TYPE_QUEST;
}


unsigned short CITPCashPointItem::GetType()
{
	return TYPE_CASH_POINT_ITEM;
}


unsigned short CITPCannonball::GetType()
{
	return TYPE_CANNONBALL;
}


////////////////////////////////////////


short CITP::GetClass()
{
	return 0;
}


short CITPArmor::GetClass()
{
	return m_class;
}


short CITPWeapon::GetClass()
{
	return m_class;
}


short CITPBothhand::GetClass()
{
	return m_class;
}


short CITPBow::GetClass()
{
	return m_class;
}


short CITPGun::GetClass()
{
	return m_class;
}


////////////////////////////////////////


int CITP::GetStatus()
{
	return 0;
}


int CITPHeal::GetStatus()
{
	return m_states;
}


////////////////////////////////////////


int CITP::GetAttRange()
{
	return 1;
}


int CITPWeapon::GetAttRange()
{
	return m_AR;
}


int CITPBothhand::GetAttRange()
{
	return m_AR;
}


int CITPBow::GetAttRange()
{
	return m_AR;
}


int CITPGun::GetAttRange()
{
	return m_AR;
}


////////////////////////////////////////


short CITP::PlusDexValue()
{
	return 0;
}


short CITP::PlusStrValue()
{
	return 0;
}


short CITP::PlusIntValue()
{
	return 0;
}


short CITP::PlusLukValue()
{
	return 0;
}


short CITP::PlusAgiValue()
{
	return 0;
}


short CITP::PlusVitValue()
{
	return 0;
}


short CITPArmor::PlusDexValue()
{
	return m_dex;
}


short CITPArmor::PlusStrValue()
{
	return m_str;
}


short CITPArmor::PlusIntValue()
{
	return m_int;
}


short CITPArmor::PlusLukValue()
{
	return m_luk;
}


short CITPArmor::PlusAgiValue()
{
	return m_agi;
}


short CITPArmor::PlusVitValue()
{
	return m_vit;
}


short CITPWeapon::PlusDexValue()
{
	return m_dex;
}


short CITPWeapon::PlusStrValue()
{
	return m_str;
}


short CITPWeapon::PlusIntValue()
{
	return m_int;
}


short CITPWeapon::PlusLukValue()
{
	return m_luk;
}


short CITPWeapon::PlusAgiValue()
{
	return m_agi;
}


short CITPWeapon::PlusVitValue()
{
	return m_vit;
}


short CITPBothhand::PlusDexValue()
{
	return m_dex;
}


short CITPBothhand::PlusStrValue()
{
	return m_str;
}


short CITPBothhand::PlusIntValue()
{
	return m_int;
}


short CITPBothhand::PlusLukValue()
{
	return m_luk;
}


short CITPBothhand::PlusAgiValue()
{
	return m_agi;
}


short CITPBothhand::PlusVitValue()
{
	return m_vit;
}


short CITPBow::PlusDexValue()
{
	return m_dex;
}


short CITPBow::PlusStrValue()
{
	return m_str;
}


short CITPBow::PlusIntValue()
{
	return m_int;
}


short CITPBow::PlusLukValue()
{
	return m_luk;
}


short CITPBow::PlusAgiValue()
{
	return m_agi;
}


short CITPBow::PlusVitValue()
{
	return m_vit;
}


short CITPGun::PlusDexValue()
{
	return m_dex;
}


short CITPGun::PlusStrValue()
{
	return m_str;
}


short CITPGun::PlusIntValue()
{
	return m_int;
}


short CITPGun::PlusLukValue()
{
	return m_luk;
}


short CITPGun::PlusAgiValue()
{
	return m_agi;
}


short CITPGun::PlusVitValue()
{
	return m_vit;
}


////////////////////////////////////////


void CITP::GetAttackValue(short& attackPower)
{
	attackPower = 0;
}


void CITPArrow::GetAttackValue(short& ATKPower)
{
	ATKPower = static_cast<short>(m_ATK);
}


void CITPAmmo::GetAttackValue(short& ATKPower)
{
	ATKPower = static_cast<short>(m_ATK);
}


void CITPThrow::GetAttackValue(short& ATKPower)
{
	ATKPower = static_cast<short>(m_ATK);
}


void CITPWeapon::GetAttackValue(short& attackPower)
{
	attackPower = static_cast<short>(m_ATK);
}


void CITPBothhand::GetAttackValue(short& attackPower)
{
	attackPower = static_cast<short>(m_ATK);
}


void CITPBow::GetAttackValue(short& attackPower)
{
	attackPower = static_cast<short>(m_ATK);
}


void CITPGun::GetAttackValue(short& ATKPower)
{
	ATKPower = static_cast<short>(m_ATK);
}


void CITPCannonball::GetAttackValue(short& ATKPower)
{
	ATKPower = static_cast<short>(m_ATK);
}


////////////////////////////////////////


void CITP::GetDefence(short& defencePower)
{
	defencePower = 0;
}


void CITPArmor::GetDefence(short& defencePower)
{
	defencePower = m_defencePower;
}


////////////////////////////////////////


void CITP::GetMagicDefence(short& attackPower)
{
	attackPower = 0;
}


void CITPArmor::GetMagicDefence(short& defencePower)
{
	defencePower = m_mdef;
}


////////////////////////////////////////


unsigned short CITP::GetLocation(short job)
{
	return 0;
}


unsigned short CITPWeapon::GetLocation(short job)
{
	if( job == JT_ASSASSIN || job == JT_ASSASSIN_H || job == JT_ASSASSIN_B || job == JT_GUILLOTINE_CROSS || job == JT_GUILLOTINE_CROSS_H || job == JT_GUILLOTINE_CROSS_B )
		return LOCATION_LARM | LOCATION_RARM;

	return static_cast<unsigned short>(m_location);
}


unsigned short CITPBothhand::GetLocation(short job)
{
	return static_cast<unsigned short>(m_location);
}


unsigned short CITPBow::GetLocation(short job)
{
	return static_cast<unsigned short>(m_location);
}


unsigned short CITPArmor::GetLocation(short job)
{
	return static_cast<unsigned short>(m_location);
}


unsigned short CITPArmorTM::GetLocation(short job)
{
	return static_cast<unsigned short>(m_location);
}


unsigned short CITPArmorTB::GetLocation(short job)
{
	return static_cast<unsigned short>(m_location);
}


unsigned short CITPArmorMB::GetLocation(short job)
{
	return static_cast<unsigned short>(m_location);
}


unsigned short CITPArmorTMB::GetLocation(short job)
{
	return static_cast<unsigned short>(m_location);
}


unsigned short CITPArrow::GetLocation(short job)
{
	return LOCATION_ARROW;
}


unsigned short CITPAmmo::GetLocation(short job)
{
	return LOCATION_ARROW;
}


unsigned short CITPThrow::GetLocation(short job)
{
	return LOCATION_ARROW;
}


unsigned short CITPGun::GetLocation(short job)
{
	return static_cast<unsigned short>(m_location);
}


unsigned short CITPCannonball::GetLocation(short job)
{
	short jobGroup = GetThirdJobGroup(job);
	if( jobGroup == JT_MECHANIC || jobGroup == JT_GENETIC )
		return LOCATION_ARROW;

	return LOCATION_NOTHING;
}


////////////////////////////////////////


int CITP::GetItemLevel()
{
	return 0;
}


int CITPWeapon::GetItemLevel()
{
	if( m_level < 1 || m_level > 5 )
		return 0;

	return m_level;
}


int CITPBothhand::GetItemLevel()
{
	if( m_level < 1 || m_level > 5 )
		return 0;

	return m_level;
}


int CITPBow::GetItemLevel()
{
	if( m_level < 1 || m_level > 5 )
		return 0;

	return m_level;
}


int CITPGun::GetItemLevel()
{
	if( m_level < 1 || m_level > 5 )
		return 0;

	return m_level;
}


////////////////////////////////////////


BOOL CITP::IsRefinable()
{
	return m_isRefinable;
}


////////////////////////////////////////


BOOL CITP::IsDamagable()
{
	return m_isDamagable;
}


////////////////////////////////////////


int CITP::GetMaxSlot()
{
	return 0;
}


int CITPArmor::GetMaxSlot()
{
	return m_maxSlot;
}


int CITPWeapon::GetMaxSlot()
{
	return m_maxSlot;
}


int CITPBothhand::GetMaxSlot()
{
	return m_maxSlot;
}


int CITPBow::GetMaxSlot()
{
	return m_maxSlot;
}


int CITPGun::GetMaxSlot()
{
	return m_maxSlot;
}


////////////////////////////////////////


int CITP::GetProperty()
{
	return 0;
}


int CITPArrow::GetProperty()
{
	return m_property;
}


int CITPAmmo::GetProperty()
{
	return m_property;
}


int CITPThrow::GetProperty()
{
	return m_property;
}


int CITPWeapon::GetProperty()
{
	return m_property;
}


int CITPBothhand::GetProperty()
{
	return m_property;
}


int CITPBow::GetProperty()
{
	return m_property;
}


int CITPGun::GetProperty()
{
	return m_property;
}


int CITPCard::GetProperty()
{
	return m_property;
}


int CITPCannonball::GetProperty()
{
	return m_property;
}


////////////////////////////////////////


int CITP::IsMovable()
{
	return m_isMovable;
}


////////////////////////////////////////


unsigned long CITP::GetAvailableJobCode()
{
	return m_availableJob;
}


unsigned long CITPAmmo::GetAvailableJobCode()
{
	return 0x49; //TODO
}


unsigned long CITPCannonball::GetAvailableJobCode()
{
	return JT_MECHANIC;
}


////////////////////////////////////////


bool CITP::IsCashItem()
{
	return m_bCashItem;
}


////////////////////////////////////////


bool CITP::IsWeapon()
{
	return false;
}


bool CITPWeapon::IsWeapon()
{
	return true;
}


bool CITPBothhand::IsWeapon()
{
	return true;
}


bool CITPBow::IsWeapon()
{
	return true;
}


bool CITPGun::IsWeapon()
{
	return true;
}


////////////////////////////////////////


bool CITP::IsRangeWeapon()
{
	return false;
}


bool CITPWeapon::IsRangeWeapon()
{
	return ( m_class == WEAPONTYPE_INSTRUMENT || m_class == WEAPONTYPE_WHIP );
}


bool CITPBothhand::IsRangeWeapon()
{
	return ( m_class == WEAPONTYPE_INSTRUMENT || m_class == WEAPONTYPE_WHIP );
}


bool CITPBow::IsRangeWeapon()
{
	return true;
}


bool CITPGun::IsRangeWeapon()
{
	return true;
}


////////////////////////////////////////


bool CITP::IsPickUpNotifyParty()
{
	return false;
}


bool CITPArmor::IsPickUpNotifyParty()
{
	return true;
}


bool CITPWeapon::IsPickUpNotifyParty()
{
	return true;
}


bool CITPBothhand::IsPickUpNotifyParty()
{
	return true;
}


bool CITPBow::IsPickUpNotifyParty()
{
	return true;
}


bool CITPGun::IsPickUpNotifyParty()
{
	return true;
}


bool CITPCard::IsPickUpNotifyParty()
{
	return true;
}


////////////////////////////////////////


short CITP::GetMATK()
{
	return 0;
}


short CITPWeapon::GetMATK()
{
	return m_MATK;
}


short CITPBothhand::GetMATK()
{
	return m_MATK;
}


////////////////////////////////////////


bool CITP::IsBothHandWeapon()
{
	return false;
}


bool CITPBothhand::IsBothHandWeapon()
{
	return true;
}


bool CITPBow::IsBothHandWeapon()
{
	return true;
}


bool CITPGun::IsBothHandWeapon()
{
	return true;
}


////////////////////////////////////////


void CITP::SetUseEvent(bool flag)
{
	m_isUseEvent = flag;
}


bool CITP::IsUsableLevel(const int in_Level)
{
	return ( in_Level >= m_minLevel && in_Level <= m_maxLevel );
}


unsigned long CITP::GetBitExpressionJob(short job)
{
	switch( job )
	{
	case JT_NOVICE:
	case JT_NOVICE_H:
	case JT_NOVICE_B:
		return 0x01; // (1 << 0)
	case JT_SUPERNOVICE:
	case JT_SUPERNOVICE_B:
		return 0x01; // (1 << 0)
	case JT_SWORDMAN:
	case JT_SWORDMAN_H:
	case JT_SWORDMAN_B:
		return 0x02; // (1 << 1)
	case JT_MAGICIAN:
	case JT_MAGICIAN_H:
	case JT_MAGICIAN_B:
		return 0x04; // (1 << 2)
	case JT_ARCHER:
	case JT_ARCHER_H:
	case JT_ARCHER_B:
		return 0x08; // (1 << 3)
	case JT_ACOLYTE:
	case JT_ACOLYTE_H:
	case JT_ACOLYTE_B:
		return 0x10; // (1 << 4)
	case JT_MERCHANT:
	case JT_MERCHANT_H:
	case JT_MERCHANT_B:
		return 0x20; // (1 << 5)
	case JT_THIEF:
	case JT_THIEF_H:
	case JT_THIEF_B:
		return 0x40; // (1 << 6)
	case JT_KNIGHT:
	case JT_KNIGHT_H:
	case JT_KNIGHT_B:
		return 0x80; // (1 << 7)
	case JT_WIZARD:
	case JT_WIZARD_H:
	case JT_WIZARD_B:
		return 0x100; // (1 << 8)
	case JT_HUNTER:
	case JT_HUNTER_H:
	case JT_HUNTER_B:
		return 0x200; // (1 << 9)
	case JT_PRIEST:
	case JT_PRIEST_H:
	case JT_PRIEST_B:
		return 0x400; // (1 << 10)
	case JT_BLACKSMITH:
	case JT_BLACKSMITH_H:
	case JT_BLACKSMITH_B:
		return 0x800; // (1 << 11)
	case JT_ASSASSIN:
	case JT_ASSASSIN_H:
	case JT_ASSASSIN_B:
		return 0x1000; // (1 << 12)
	case JT_CRUSADER:
	case JT_CRUSADER_H:
	case JT_CRUSADER_B:
		return 0x2000; // (1 << 13)
	case JT_SAGE:
	case JT_SAGE_H:
	case JT_SAGE_B:
		return 0x4000; // (1 << 14)
	case JT_BARD:
	case JT_BARD_H:
	case JT_BARD_B:
		return 0x8000; // (1 << 15)
	case JT_DANCER:
	case JT_DANCER_H:
	case JT_DANCER_B:
		return 0x10000; // (1 << 16)
	case JT_MONK:
	case JT_MONK_H:
	case JT_MONK_B:
		return 0x20000; // (1 << 17)
	case JT_ALCHEMIST:
	case JT_ALCHEMIST_H:
	case JT_ALCHEMIST_B:
		return 0x40000; // (1 << 18)
	case JT_ROGUE:
	case JT_ROGUE_H:
	case JT_ROGUE_B:
		return 0x80000; // (1 << 19)
	default:
		return 0xFFFFFFFF;
	};
}


void CITP::SetBindOnEquip()
{
	m_isBindOnEquip = true;
}


bool CITP::IsBindOnEquip()
{
	return m_isBindOnEquip;
}


////////////////////////////////////////


int CITPCard::GetCompositionType()
{
	return m_compositionType;
}


int CITPCard::GetCompositionPos()
{
	return m_compositionPos;
}


BOOL CITPCard::IsCompositionable(CITP* equipItp)
{
	if( equipItp == NULL )
		return FALSE;

	if( m_compositionType == 1 )
	{
		unsigned short type = equipItp->GetType();

		if( type == TYPE_WEAPON || type == TYPE_BOW || type == TYPE_BOTHHAND || type == TYPE_GUN )
			return TRUE;

		return FALSE;
	}
	else
	if( m_compositionType == 2 )
	{
		if( m_compositionPos & equipItp->m_location )
			return TRUE;

		return FALSE;
	}
	else
	{
		unsigned short type = equipItp->GetType();

		if( !(type == TYPE_WEAPON || type == TYPE_BOW || type == TYPE_BOTHHAND || type == TYPE_GUN) )
			if( m_compositionPos & equipItp->m_location )
				return TRUE;

		return FALSE;
	}
}


////////////////////////////////////////


CITPCashPointItem::CITPCashPointItem()
{
}


CITPCashPointItem::~CITPCashPointItem()
{
}


short CITPCashPointItem::GetChangeItemID()
{
	return m_ChangeItemID;
}


short CITPCashPointItem::GetCount()
{
	return static_cast<short>(m_Count);
}


////////////////////////////////////////
