#include "SkillTypeBaseInfo.h"
#include "enum.hpp"


CSkillTypeBaseInfo::CSkillTypeBaseInfo(void) // line 56
{
}


CSkillTypeBaseInfo::~CSkillTypeBaseInfo(void) // line 60
{
}


hook_method<void (CSkillTypeBaseInfo::*)(CSkillTypeInfo* skinfo)> CSkillTypeBaseInfo::_AddSkillType(SERVER, "CSkillTypeBaseInfo::AddSkillType");
void CSkillTypeBaseInfo::AddSkillType(CSkillTypeInfo* skinfo) // line 65
{
	return (this->*_AddSkillType)(skinfo);

	skinfo->Init();
	m_skillTypeInfo[skinfo->CSkillTypeInfo::GetSKID()] = skinfo;
}


hook_method<void (CSkillTypeBaseInfo::*)(void)> CSkillTypeBaseInfo::_SetSKTyepBase(SERVER, "CSkillTypeBaseInfo::SetSKTyepBase");
void CSkillTypeBaseInfo::SetSKTyepBase(void) // line 74
{
	return (this->*_SetSKTyepBase)();

	//TODO
}


hook_method<void (CSkillTypeBaseInfo::*)(void)> CSkillTypeBaseInfo::_InitGDSkill(SERVER, "CSkillTypeBaseInfo::InitGDSkill");
void CSkillTypeBaseInfo::InitGDSkill(void) // line 1236
{
	return (this->*_InitGDSkill)();
/*
	m_skillName["GD_APPROVAL"]          = SKID_GD_APPROVAL;          this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_APPROVAL());
	m_skillName["GD_KAFRACONTRACT"]     = SKID_GD_KAFRACONTRACT;     this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_KAFRACONTRACT());
	m_skillName["GD_GUARDRESEARCH"]     = SKID_GD_GUARDRESEARCH;     this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_GUARDRESEARCH());
	m_skillName["GD_GUARDUP"]           = SKID_GD_GUARDUP;           this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_GUARDUP());
	m_skillName["GD_EXTENSION"]         = SKID_GD_EXTENSION;         this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_EXTENSION());
	m_skillName["GD_LEADERSHIP"]        = SKID_GD_LEADERSHIP;        this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_LEADERSHIP());
	m_skillName["GD_GLORYWOUNDS"]       = SKID_GD_GLORYWOUNDS;       this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_GLORYWOUNDS());
	m_skillName["GD_SOULCOLD"]          = SKID_GD_SOULCOLD;          this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_SOULCOLD());
	m_skillName["GD_HAWKEYES"]          = SKID_GD_HAWKEYES;          this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_HAWKEYES());
	m_skillName["GD_BATTLEORDER"]       = SKID_GD_BATTLEORDER;       this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_BATTLEORDER());
	m_skillName["GD_REGENERATION"]      = SKID_GD_REGENERATION;      this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_REGENERATION());
	m_skillName["GD_RESTORE"]           = SKID_GD_RESTORE;           this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_RESTORE());
	m_skillName["GD_EMERGENCYCALL"]     = SKID_GD_EMERGENCYCALL;     this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_EMERGENCYCALL());
	m_skillName["GD_DEVELOPMENT"]       = SKID_GD_DEVELOPMENT;       this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_DEVELOPMENT());
	m_skillName["GD_ITEMEMERGENCYCALL"] = SKID_GD_ITEMEMERGENCYCALL; this->CSkillTypeBaseInfo::AddSkillType(new SK_GD_ITEMEMERGENCYCALL());
*/
}


hook_method<void (CSkillTypeBaseInfo::*)(void)> CSkillTypeBaseInfo::_InitHomunSkill(SERVER, "CSkillTypeBaseInfo::InitHomunSkill");
void CSkillTypeBaseInfo::InitHomunSkill(void) // line 1259
{
	return (this->*_InitHomunSkill)();
/*
	m_skillName["HLIF_HEAL"]      = SKID_HLIF_HEAL;      this->CSkillTypeBaseInfo::AddSkillType(new SK_HLIF_HEAL());
	m_skillName["HLIF_AVOID"]     = SKID_HLIF_AVOID;     this->CSkillTypeBaseInfo::AddSkillType(new SK_HLIF_AVOID());
	m_skillName["HLIF_BRAIN"]     = SKID_HLIF_BRAIN;     this->CSkillTypeBaseInfo::AddSkillType(new SK_HLIF_BRAIN());
	m_skillName["HLIF_CHANGE"]    = SKID_HLIF_CHANGE;    this->CSkillTypeBaseInfo::AddSkillType(new SK_HLIF_CHANGE());
	m_skillName["HAMI_CASTLE"]    = SKID_HAMI_CASTLE;    this->CSkillTypeBaseInfo::AddSkillType(new SK_HAMI_CASTLE());
	m_skillName["HAMI_DEFENCE"]   = SKID_HAMI_DEFENCE;   this->CSkillTypeBaseInfo::AddSkillType(new SK_HAMI_DEFENCE());
	m_skillName["HAMI_SKIN"]      = SKID_HAMI_SKIN;      this->CSkillTypeBaseInfo::AddSkillType(new SK_HAMI_SKIN());
	m_skillName["HAMI_BLOODLUST"] = SKID_HAMI_BLOODLUST; this->CSkillTypeBaseInfo::AddSkillType(new SK_HAMI_BLOODLUST());
	m_skillName["HFLI_MOON"]      = SKID_HFLI_MOON;      this->CSkillTypeBaseInfo::AddSkillType(new SK_HFLI_MOON());
	m_skillName["HFLI_FLEET"]     = SKID_HFLI_FLEET;     this->CSkillTypeBaseInfo::AddSkillType(new SK_HFLI_FLEET());
	m_skillName["HFLI_SPEED"]     = SKID_HFLI_SPEED;     this->CSkillTypeBaseInfo::AddSkillType(new SK_HFLI_SPEED());
	m_skillName["HFLI_SBR44"]     = SKID_HFLI_SBR44;     this->CSkillTypeBaseInfo::AddSkillType(new SK_HFLI_SBR44());
	m_skillName["HVAN_CAPRICE"]   = SKID_HVAN_CAPRICE;   this->CSkillTypeBaseInfo::AddSkillType(new SK_HVAN_CAPRICE());
	m_skillName["HVAN_CHAOTIC"]   = SKID_HVAN_CHAOTIC;   this->CSkillTypeBaseInfo::AddSkillType(new SK_HVAN_CHAOTIC());
	m_skillName["HVAN_INSTRUCT"]  = SKID_HVAN_INSTRUCT;  this->CSkillTypeBaseInfo::AddSkillType(new SK_HVAN_INSTRUCT());
	m_skillName["HVAN_EXPLOSION"] = SKID_HVAN_EXPLOSION; this->CSkillTypeBaseInfo::AddSkillType(new SK_HVAN_EXPLOSION());
*/
}


hook_method<void (CSkillTypeBaseInfo::*)(void)> CSkillTypeBaseInfo::_InitMercenarySkill(SERVER, "CSkillTypeBaseInfo::InitMercenarySkill");
void CSkillTypeBaseInfo::InitMercenarySkill(void) // line 1285
{
	return (this->*_InitMercenarySkill)();
/*
	m_skillName["MS_BASH"]          = SKID_MS_BASH;          this->CSkillTypeBaseInfo::AddSkillType(new SK_MS_BASH());
	m_skillName["MS_MAGNUM"]        = SKID_MS_MAGNUM;        this->CSkillTypeBaseInfo::AddSkillType(new SK_MS_MAGNUM());
	m_skillName["MS_REFLECTSHIELD"] = SKID_MS_REFLECTSHIELD; this->CSkillTypeBaseInfo::AddSkillType(new SK_MS_REFLECTSHIELD());
	m_skillName["MS_BOWLINGBASH"]   = SKID_MS_BOWLINGBASH;   this->CSkillTypeBaseInfo::AddSkillType(new SK_MS_BOWLINGBASH());
	m_skillName["MS_PARRYING"]      = SKID_MS_PARRYING;      this->CSkillTypeBaseInfo::AddSkillType(new SK_MS_PARRYING());
	m_skillName["MS_BERSERK"]       = SKID_MS_BERSERK;       this->CSkillTypeBaseInfo::AddSkillType(new SK_MS_BERSERK());
	m_skillName["ML_DEFENDER"]      = SKID_ML_DEFENDER;      this->CSkillTypeBaseInfo::AddSkillType(new SK_ML_DEFENDER());
	m_skillName["ML_DEVOTION"]      = SKID_ML_DEVOTION;      this->CSkillTypeBaseInfo::AddSkillType(new SK_ML_DEVOTION());
	m_skillName["MER_MAGNIFICAT"]   = SKID_MER_MAGNIFICAT;   this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_MAGNIFICAT());
	m_skillName["MER_AUTOBERSERK"]  = SKID_MER_AUTOBERSERK;  this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_AUTOBERSERK());
	m_skillName["MA_DOUBLE"]        = SKID_MA_DOUBLE;        this->CSkillTypeBaseInfo::AddSkillType(new SK_MA_DOUBLE());
	m_skillName["MA_SHOWER"]        = SKID_MA_SHOWER;        this->CSkillTypeBaseInfo::AddSkillType(new SK_MA_SHOWER());
	m_skillName["MA_SKIDTRAP"]      = SKID_MA_SKIDTRAP;      this->CSkillTypeBaseInfo::AddSkillType(new SK_MA_SKIDTRAP());
	m_skillName["MA_SANDMAN"]       = SKID_MA_SANDMAN;       this->CSkillTypeBaseInfo::AddSkillType(new SK_MA_SANDMAN());
	m_skillName["MA_FREEZINGTRAP"]  = SKID_MA_FREEZINGTRAP;  this->CSkillTypeBaseInfo::AddSkillType(new SK_MA_FREEZINGTRAP());
	m_skillName["MA_CHARGEARROW"]   = SKID_MA_CHARGEARROW;   this->CSkillTypeBaseInfo::AddSkillType(new SK_MA_CHARGEARROW());
	m_skillName["MA_SHARPSHOOTING"] = SKID_MA_SHARPSHOOTING; this->CSkillTypeBaseInfo::AddSkillType(new SK_MA_SHARPSHOOTING());
	m_skillName["MA_LANDMINE"]      = SKID_MA_LANDMINE;      this->CSkillTypeBaseInfo::AddSkillType(new SK_MA_LANDMINE());
	m_skillName["MA_REMOVETRAP"]    = SKID_MA_REMOVETRAP;    this->CSkillTypeBaseInfo::AddSkillType(new SK_MA_REMOVETRAP());
	m_skillName["ML_PIERCE"]        = SKID_ML_PIERCE;        this->CSkillTypeBaseInfo::AddSkillType(new SK_ML_PIERCE());
	m_skillName["ML_BRANDISH"]      = SKID_ML_BRANDISH;      this->CSkillTypeBaseInfo::AddSkillType(new SK_ML_BRANDISH());
	m_skillName["ML_SPIRALPIERCE"]  = SKID_ML_SPIRALPIERCE;  this->CSkillTypeBaseInfo::AddSkillType(new SK_ML_SPIRALPIERCE());
	m_skillName["ML_AUTOGUARD"]     = SKID_ML_AUTOGUARD;     this->CSkillTypeBaseInfo::AddSkillType(new SK_ML_AUTOGUARD());
	m_skillName["MER_QUICKEN"]      = SKID_MER_QUICKEN;      this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_QUICKEN());
	m_skillName["MER_SIGHT"]        = SKID_MER_SIGHT;        this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_SIGHT());
	m_skillName["MER_PROVOKE"]      = SKID_MER_PROVOKE;      this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_PROVOKE());
	m_skillName["MER_DECAGI"]       = SKID_MER_DECAGI;       this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_DECAGI());
	m_skillName["MER_LEXDIVINA"]    = SKID_MER_LEXDIVINA;    this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_LEXDIVINA());
	m_skillName["MER_ESTIMATION"]   = SKID_MER_ESTIMATION;   this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_ESTIMATION());
	m_skillName["MER_KYRIE"]        = SKID_MER_KYRIE;        this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_KYRIE());
	m_skillName["MER_BLESSING"]     = SKID_MER_BLESSING;     this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_BLESSING());
	m_skillName["MER_INCAGI"]       = SKID_MER_INCAGI;       this->CSkillTypeBaseInfo::AddSkillType(new SK_MER_INCAGI());
*/
}


hook_method<int (CSkillTypeBaseInfo::*)(const char* fileName)> CSkillTypeBaseInfo::_SaveToFile(SERVER, "CSkillTypeBaseInfo::SaveToFile");
int CSkillTypeBaseInfo::SaveToFile(const char* fileName) // line 1336
{
	return (this->*_SaveToFile)(fileName);

	FILE* fp = fopen(fileName, "wt");
	if( fp == NULL )
		return 0;

	for( mystd::map<mystd::string,unsigned short>::iterator it = m_skillName.begin(); it != m_skillName.end(); ++it )
		fprintf(fp, "%s %d\n", it->first.c_str(), it->second);

	fclose(fp);
	return 1;
}
