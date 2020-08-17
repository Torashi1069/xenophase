#include "CharacterMgr.h"
#include "Enum.h"
#include "MonParameterMgr.h"
#include "Path.h"
#include "ScriptCompiler.h"
#include "SkillScriptHandler.h"
#include "SkillTypeInfo.h"
#include "SkillTypeInfo2.h"
#include "SkillTypeInfo3rd2_ShadowChaser.h"
#include "SkillTypeInfoMgr.h"
#include "ZoneProcess.h"
#include "ScriptLib/BinBuf.h"
#include "shared/shared.h"


CSkillTypeInfoMgr::CSkillTypeInfoMgr()
{
}


CSkillTypeInfoMgr::~CSkillTypeInfoMgr()
{
	this->CSkillTypeInfoMgr::Reset();
}


void CSkillTypeInfoMgr::Init()
{
	this->CSkillTypeInfoMgr::Reset();
	this->CSkillTypeBaseInfo::SetSKTyepBase();
	this->CSkillTypeInfoMgr::LoadSKInfoFromDB();
	this->CSkillTypeInfoMgr::LoadSkillTree(g_pathData.CPathData::SetFileName("SkillTree.txt"));
	this->CSkillTypeInfoMgr::LoadSkillTree(g_pathData.CPathData::SetFileName("SkillTree_ThirdJob.txt"));
	if( !this->CSkillTypeInfoMgr::LoadGDSkillTree()
	 || !this->CSkillTypeInfoMgr::LoadSKTree_Homun(g_pathData.CPathData::SetFileName("SKTree_Homun.txt"))
	 || !this->CSkillTypeInfoMgr::LoadSKTree_Merce(g_pathData.CPathData::SetFileName("SKTree_Merce.txt")) )
	{
		ExitProcess(EXIT_SUCCESS);
	}

	this->CSkillTypeInfoMgr::LoadSkillDelay(g_pathData.CPathData::SetFileName(".\\Skill\\SkillSinglePostDelay.txt"), &CSkillTypeInfo::SetSinglePostDelay);
	this->CSkillTypeInfoMgr::LoadSkillDelay(g_pathData.CPathData::SetFileName(".\\Skill\\SkillGlobalPostDelay.txt"), &CSkillTypeInfo::SetGlobalPostDelay);
	this->CSkillTypeInfoMgr::LoadSkillDelay(g_pathData.CPathData::SetFileName(".\\Skill\\SkillCastFixedDelay.txt"), &CSkillTypeInfo::SetCastFixedDelay);
	this->CSkillTypeInfoMgr::LoadSkillDelay(g_pathData.CPathData::SetFileName(".\\Skill\\SkillCastStatDelay.txt"), &CSkillTypeInfo::SetCastStatDelay);

	SK_SC_AUTOSHADOWSPELL* cpSC_AUTOSHADOWSPELL = (SK_SC_AUTOSHADOWSPELL*)this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID_SC_AUTOSHADOWSPELL);
	if( cpSC_AUTOSHADOWSPELL == NULL )
	{
		MessageBoxA(NULL, "SC_AUTOSHADOWSPELL error!! Check fileName", "SC_AUTOSHADOWSPELL", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}

	cpSC_AUTOSHADOWSPELL->SK_SC_AUTOSHADOWSPELL::LoadAllowSkillListFile();
}


void CSkillTypeInfoMgr::Reset()
{
	for( std::map<unsigned short,CSkillTypeInfo*>::iterator it = m_skillTypeInfo.begin(); it != m_skillTypeInfo.end(); it = m_skillTypeInfo.erase(it) )
		delete it->second;

	for( std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator it = m_skillTreeInfo.begin(); it != m_skillTreeInfo.end(); ++it )
		it->second.clear();
	m_skillTreeInfo.clear();

	for( std::map<unsigned short,std::map<unsigned short,int>>::iterator it = m_GDSkillTreeInfo.begin(); it != m_GDSkillTreeInfo.end(); ++it )
		it->second.clear();
	m_GDSkillTreeInfo.clear();

	for( std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator it = m_SKTree_Homun.begin(); it != m_SKTree_Homun.end(); ++it )
		it->second.clear();
	m_SKTree_Homun.clear();
}


unsigned short CSkillTypeInfoMgr::GetSKID(const char* skName) const
{
	std::map<std::string,unsigned short>::const_iterator it = m_skillName.find(skName);
	if( it == m_skillName.end() )
		return 0;
	
	return it->second;
}


void CSkillTypeInfoMgr::LoadSKInfoFromDB()
{
	for( std::map<std::string,unsigned short>::iterator it = m_skillName.begin(); it != m_skillName.end(); ++it )
	{
		const char* skName = it->first.c_str();
		const unsigned short SKID = it->second;

		CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
		if( info == NULL )
			continue;

		info->CSkillTypeInfo::SetName(skName);
	}
}


int CSkillTypeInfoMgr::SendMsg(CCharacter* sender, int SKID, int MsgID, int skLevel, int targetID, int par3, MSGpar::CVar par4)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->OnMsg(sender, SKID, MsgID, skLevel, targetID, par3, par4);
}


CSkillTypeInfo* CSkillTypeInfoMgr::SearchSkillTypeInfo(const unsigned short in_SKID) const
{
	std::map<unsigned short,CSkillTypeInfo*>::const_iterator it = m_skillTypeInfo.find(in_SKID);
	if( it == m_skillTypeInfo.end() )
		return NULL;
	
	return it->second;
}


short CSkillTypeInfoMgr::GetSkillSPCost(unsigned short SKID, short sklevel)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->GetSPCost(sklevel);
}


char* CSkillTypeInfoMgr::GetSkillName(unsigned short SKID)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return NULL;

	return info->CSkillTypeInfo::GetName();
}


bool CSkillTypeInfoMgr::IsNextLevelUpgradable(unsigned short SKID, short curlevel, short job)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return false;

	if( this->CSkillTypeInfoMgr::IsGuildSkill(SKID) )
	{
		if( !info->IsAvailableJob(job) )
			return false;
	}
	else
	{
		if( !this->CSkillTypeInfoMgr::IsAvailableJob(job, SKID) )
			return false;
	}

	if( info->CSkillTypeInfo::IsEventSkill() )
		return false;

	if( curlevel >= info->GetMaxLevel() )
		return false;

	return true;
}


int CSkillTypeInfoMgr::GetSkillPattern(unsigned short skillID)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(skillID);
	if( info == NULL )
		return -1;


	return info->CSkillTypeInfo::GetPattern();
}


int CSkillTypeInfoMgr::GetSKClass(const int in_SKID) const
{
	if( in_SKID > SKID_HOMUN_BEGIN && in_SKID < SKID_HOMUN_LAST )
		return SKCLASS_HOMUN;
	else
	if( in_SKID > SKID_MERCENARY_BEGIN && in_SKID < SKID_MERCENARY_LAST )
		return SKCLASS_MERCE2;
	else
	if( in_SKID > SKID_ELEMENTAL_BEGIN && in_SKID < SKID_ELEMENTAL_LAST )
		return SKCLASS_ELEMENTAL;
	else
	if( in_SKID >= SKID_GD_APPROVAL )
		return SKCLASS_GUILD;
	else
	{
		return SKCLASS_NORMAL;
	}
}


void CSkillTypeInfoMgr::AddSkill(CCharacter* sender, short job)
{
	for( std::map<unsigned short,CSkillTypeInfo*>::iterator iter = m_skillTypeInfo.begin(); iter != m_skillTypeInfo.end(); ++iter )
	{
		unsigned short SKID = iter->first;
		if( SKID >= SKID_LAST )
			continue;

		if( !this->CSkillTypeInfoMgr::IsAvailableJob(job, SKID) )
			continue;

		const char* skillName = this->CSkillTypeInfoMgr::GetSkillName(SKID);
		if( skillName == NULL )
			continue;

		SKILLINFO data;
		data.SKID = SKID;
		memcpy_s(data.skillName, sizeof(data.skillName), skillName, 24);
		data.level = 0;
		data.spcost = this->CSkillTypeInfoMgr::GetSkillSPCost(data.SKID, 0);
		data.type = this->CSkillTypeInfoMgr::GetType(data.SKID);
		data.upgradable = this->CSkillTypeInfoMgr::IsNextLevelUpgradable(data.SKID, data.level, job);
		data.attackRange = this->CSkillTypeInfoMgr::GetAttackRange(data.SKID, data.level);
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, sender, CM_ADDSKILL, (int)&data, 0, 0, 0);
	}
}


void CSkillTypeInfoMgr::AddSkill_Homun(CCharacter* sender, short job)
{
	for( std::map<unsigned short,CSkillTypeInfo*>::iterator it = m_skillTypeInfo.begin(); it != m_skillTypeInfo.end(); ++it )
	{
		unsigned short SKID = it->first;
		if( SKID <= SKID_HOMUN_BEGIN || SKID >= SKID_HOMUN_LAST )
			continue;

		if( !this->CSkillTypeInfoMgr::IsAvailableJob(job, SKID) )
			continue;

		HO_SKINFO info;
		info.level = 0;
		info.type = 0;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, sender, CM_ADDSKILL, SKID, (int)&info, 0, 0);
	}
}


void CSkillTypeInfoMgr::AddSkill_Merce(CCharacter* sender, short job)
{
	for( std::map<unsigned short,CSkillTypeInfo*>::iterator it = m_skillTypeInfo.begin(); it != m_skillTypeInfo.end(); ++it )
	{
		unsigned short SKID = it->first;
		if( SKID >= SKID_LAST )
			continue;

		short skLevel = this->CSkillTypeInfoMgr::IsAvailable_Merce(job, SKID);
		if( skLevel <= 0 )
			continue;

		HO_SKINFO info;
		info.level = skLevel;
		info.type = 0;
		CCharacterMgr::GetObj()->CCharacterMgr::SendMsg(NULL, sender, CM_ADDSKILL, SKID, (int)&info, 0, 0);
	}
}


int CSkillTypeInfoMgr::GetType(unsigned short SKID)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->CSkillTypeInfo::GetType();
}


short CSkillTypeInfoMgr::GetAttackRange(unsigned short SKID, int level)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->GetAttackRange(level);
}


int CSkillTypeInfoMgr::GetProperty(unsigned short SkillID)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SkillID);
	if( info == NULL )
		return 0;

	return info->GetProperty();
}


unsigned long CSkillTypeInfoMgr::GetFlag(unsigned short SKID)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->CSkillTypeInfo::GetFlag();
}


void CSkillTypeInfoMgr::LoadSkillTree(const char* fileName)
{
	FILE* fp = fopen(fileName, "r");
	if( fp == NULL )
	{
		MessageBoxA(NULL, "error!! Check fileName", "error", MB_OK);
		ExitProcess(EXIT_SUCCESS);
	}

	std::map<unsigned short,std::map<unsigned short,int>> skillTree;
	std::map<unsigned short,int> lowerSkill;

	//FIXME: all error paths leak fp
	while( !feof(fp) )
	{
		char buf[256];
		fscanf(fp, "%s", buf);

		if( strstr(buf, "//") != NULL )
		{
			fgets(buf, countof(buf), fp);
			continue;
		}

		if( strcmp(buf, "#END") == 0 )
			break; // done.

		if( strcmp(buf, "Inherit") == 0 )
		{
			fscanf(fp, "%s", buf);
			short secondJob = (short)g_monParameter.CMonParameterMgr::SearchKeyword(buf);
			fscanf(fp, "%s", buf);
			short firstJob = (short)g_monParameter.CMonParameterMgr::SearchKeyword(buf);

			if( secondJob == -1 || firstJob == -1 )
			{
				char szTemp[256] = {};
				wsprintfA(szTemp, "error!! Skill Tree!! Inherit!! (Name:%s)", buf); //FIXME: deprecated API
				MessageBoxA(NULL, szTemp, "error", MB_OK);
				return;
			}

			this->CSkillTypeInfoMgr::InheritFirstJobSkill(secondJob, firstJob);
			fgets(buf, countof(buf), fp);
			continue;
		}

		int job = g_monParameter.CMonParameterMgr::SearchKeyword(buf);
		if( job == -1 )
		{
			char szTemp[256] = {};
			wsprintfA(szTemp, "error!! Skill Tree!! (Name:%s)", buf); //FIXME: deprecated API
			MessageBoxA(NULL, szTemp, "error", MB_OK);
			return;
		}

		skillTree.clear();

		fscanf(fp, "%s", buf);
		while( strstr(buf, "//") != NULL && !feof(fp) )
		{
			fgets(buf, countof(buf), fp);
			fscanf(fp, "%s", buf);
		}

		if( strcmp(buf, "{") == 0 )
		{
			while( !feof(fp) )
			{
				fscanf(fp, "%s", buf);
				while( strstr(buf, "//") != NULL && !feof(fp) )
				{
					fgets(buf, countof(buf), fp);
					fscanf(fp, "%s", buf);
				}

				if( strcmp(buf, "}") == 0 )
					break; // done.

				unsigned short skid = this->CSkillTypeInfoMgr::GetSKID(buf);
				if( skid == 0 )
				{
					char szTemp[256] = {};
					wsprintfA(szTemp, "error!! Skill Tree!! (Name:%s)", buf); //FIXME: deprecated API
					MessageBoxA(NULL, szTemp, "error", MB_OK);
					return;
				}

				fscanf(fp, "%s", buf);
				while( strstr(buf, "//") != NULL && !feof(fp) )
				{
					fgets(buf, countof(buf), fp);
					fscanf(fp, "%s", buf);
				}

				if( strcmp(buf, "begin") != 0 )
				{
					char szTemp[256] = {};
					wsprintfA(szTemp, "error!! Skill Tree!! (Name:%s)", buf); //FIXME: deprecated API
					MessageBoxA(NULL, szTemp, "error", MB_OK);
					return;
				}

				lowerSkill.clear();

				CSkillTypeInfo* skillInfo = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(skid);

				while( !feof(fp) )
				{
					fscanf(fp, "%s", buf);
					while( strstr(buf, "//") != NULL && !feof(fp) )
					{
						fgets(buf, countof(buf), fp);
						fscanf(fp, "%s", buf);
					}

					if( strcmp(buf, "end") == 0 )
						break;

					if( strcmp(buf, "JOBLEVEL") == 0 )
					{
						fscanf(fp, "%s", buf);
						skillInfo->CSkillTypeInfo::SetAvailableJobLevel(job, atoi(buf));
					}
					else
					{
						unsigned short lowerskid = this->CSkillTypeInfoMgr::GetSKID(buf);
						if( lowerskid == 0 )
						{
							char szTemp[256] = {};
							wsprintfA(szTemp, "error!! Skill Tree!! (Name:%s)", buf); //FIXME: deprecated API
							MessageBoxA(NULL, szTemp, "error", MB_OK);
							return;
						}

						fscanf(fp, "%s", buf);
						lowerSkill.insert(std::pair<const unsigned short,int>(lowerskid, atoi(buf)));
					}
				}

				if( skid >= SKID_SL_DEATHKNIGHT && skid <= SKID_SL_GUNNER )
					continue;

				skillTree.insert(std::pair<const unsigned short,std::map<unsigned short,int>>(skid, lowerSkill));
			}
		}

		m_skillTreeInfo.insert(std::make_pair(job, skillTree));
	}

	fclose(fp);
	return;
}


BOOL CSkillTypeInfoMgr::LoadGDSkillTree()
{
	FILE* fp = fopen(g_pathData.CPathData::SetFileName("GDSkillTree.txt"), "r");
	if( fp == NULL )
	{
		MessageBoxA(NULL, "File not found! (GDSkillTree.txt)", "error", MB_OK);
		return FALSE;
	}

	int blockCount = 0;
	unsigned short SKID;
	std::map<unsigned short,int> lowerSkill;

	//FIXME: all error paths leak fp
	while( 1 )
	{
		char buf[256];
		if( fscanf(fp, "%s", buf) == -1 )
			break; // done.

		if( strstr(buf, "//") != NULL )
		{
			fgets(buf, countof(buf), fp);
			continue;
		}

		if( strcmp(buf, "begin") == 0 )
		{
			if( blockCount > 0 )
			{
				MessageBoxA(NULL, "syntax error!", "GuildSkill Tree", MB_OK);
				return FALSE;
			}

			++blockCount;
			lowerSkill.clear();
			continue;
		}

		if( strcmp(buf, "end") == 0 )
		{
			if( blockCount <= 0 )
			{
				MessageBoxA(NULL, "syntax error!", "GuildSkill Tree", MB_OK);
				return FALSE;
			}

			--blockCount;
			m_GDSkillTreeInfo.insert(std::make_pair(SKID, lowerSkill));
			continue;
		}

		if( blockCount == 0 )
		{// parse main SKID
			unsigned short SKID = this->CSkillTypeInfoMgr::GetSKID(buf);
			if( SKID == 0 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "not exist SKID!! (%s)", buf);
				MessageBoxA(NULL, msg, "GuildSkill Tree", MB_OK);
				return FALSE;
			}
		}
		else
		{// parse lower SKID and Level
			unsigned short lowerSKID = this->CSkillTypeInfoMgr::GetSKID(buf);
			if( lowerSKID == 0 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "not exist lowerSKID!! (%s)", buf);
				MessageBoxA(NULL, msg, "GuildSkill Tree", MB_OK);
				return FALSE;
			}

			fscanf(fp, "%s", buf);
			lowerSkill.insert(std::make_pair(lowerSKID, atoi(buf)));
		}
	}

	fclose(fp);
	return TRUE;
}


BOOL CSkillTypeInfoMgr::LoadSKTree_Homun(const char* fileName)
{
	FILE* fp = fopen(fileName, "r");
	if( fp == NULL )
	{
		char msg[256];
		sprintf_s(msg, countof(msg), "File not found! (%s)", fileName);
		MessageBoxA(NULL, msg, "BOOL CSkillTypeInfoMgr :: LoadSKTree_Homun()", MB_OK);
		return FALSE;
	}

	BOOL result = TRUE;
	int blkCnt1 = 0;
	int blkCnt2 = 0;
	short job;
	unsigned short SKID;
	std::map<unsigned short,std::map<unsigned short,int>> TreeInfo;
	std::map<unsigned short,int> lowSkill;

	while( 1 )
	{
		char buf[256];
		if( fscanf(fp, "%s", buf) == -1 )
			break; // done.

		if( strstr(buf, "//") != NULL )
		{
			fgets(buf, countof(buf), fp);
			continue;
		}

		if( strcmp(buf, "{") == 0 )
		{
			++blkCnt1;
			TreeInfo.clear();
			continue;
		}

		if( strcmp(buf, "}") == 0 )
		{
			--blkCnt1;
			m_SKTree_Homun.insert(std::make_pair(job, TreeInfo));
			continue;
		}

		if( strcmp(buf, "begin") == 0 )
		{
			++blkCnt2;
			lowSkill.clear();
			continue;
		}

		if( strcmp(buf, "end") == 0 )
		{
			--blkCnt2;
			TreeInfo.insert(std::make_pair(SKID, lowSkill));
			continue;
		}

		if( strcmp(buf, "inherit") == 0 )
		{
			if( fscanf(fp, "%s", buf) == -1 )
			{
				result = FALSE;
				break;
			}

			int nextJob = g_monParameter.CMonParameterMgr::SearchKeyword(buf);
			if( nextJob == -1 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "not exist this job! (%s)", buf);
				MessageBoxA(NULL, msg, "HOMUN_SKTree", MB_OK);
				result = FALSE;
				break;
			}

			if( fscanf(fp, "%s", buf) == -1 )
			{
				result = FALSE;
				break;
			}

			int preJob = g_monParameter.CMonParameterMgr::SearchKeyword(buf);
			if( preJob == -1 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "not exist this job! (%s)", buf);
				MessageBoxA(NULL, msg, "HOMUN_SKTree", MB_OK);
				result = FALSE;
				break;
			}

			this->CSkillTypeInfoMgr::InheritPreJobSkill_HO(nextJob, preJob);
		}

		if( blkCnt1 == 0 )
		{
			job = (short)g_monParameter.CMonParameterMgr::SearchKeyword(buf);
			if( job == -1 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "not exist this job! (%s)", buf);
				MessageBoxA(NULL, msg, "HOMUN_SKTree", MB_OK);
				result = FALSE;
				break;
			}

			continue;
		}

		if( blkCnt2 == 0 )
		{
			SKID = this->CSkillTypeInfoMgr::GetSKID(buf);
			if( SKID == 0 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "not exist SKID!! (%s)", buf);
				MessageBoxA(NULL, msg, "HOMUN_SKTree", MB_OK);
				result = FALSE;
				break;
			}

			continue;
		}

		if( strcmp(buf, "LEVEL") == 0 )
		{
			fscanf(fp, "%s", buf);
			SKTREE_BYCLEVEL_CONTAINER::iterator ret_iter = m_SKTree_Homun_ByCLevel.insert(std::make_pair(job, SKID_CLEVEL(SKID, atoi(buf))));
			if( ret_iter == m_SKTree_Homun_ByCLevel.end() ) //NOTE: will never happen
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "cannot Make SKTree SKID!! (%d)", SKID);
				MessageBoxA(NULL, msg, "HOMUN_SKTree", MB_OK);
				result = FALSE;
				//TODO: shouldn't this abort now?
			}

			continue;
		}

		unsigned short lowerSKID = this->CSkillTypeInfoMgr::GetSKID(buf);
		if( lowerSKID == 0 )
		{
			char msg[256];
			sprintf_s(msg, countof(msg), "not exist lowerSKID!! (%s)", buf);
			MessageBoxA(NULL, msg, "HOMUN_SKTree", MB_OK);
			result = FALSE;
			break;
		}

		fscanf(fp, "%s", buf);
		lowSkill.insert(std::make_pair(lowerSKID, atoi(buf)));
	}

	fclose(fp);
	return result;
}


BOOL CSkillTypeInfoMgr::LoadSKTree_Merce(const char* fileName)
{
	FILE* fp = fopen(fileName, "r");
	if( fp == NULL )
	{
		char msg[256];
		sprintf_s(msg, countof(msg), "File not found! (%s)", fileName);
		MessageBoxA(NULL, msg, "BOOL CSkillTypeInfoMgr :: LoadSKTree_Merce()", MB_OK);
		return FALSE;
	}

	BOOL result = TRUE;
	int blkCnt1 = 0;
	short job;
	unsigned short SKID;
	std::map<unsigned short,int> lowSkill;

	while( 1 )
	{
		char buf[256];
		if( fscanf(fp, "%s", buf) == -1 )
			break; // done.

		if( strstr(buf, "//") != NULL )
		{
			fgets(buf, countof(buf), fp);
			continue;
		}

		if( strcmp(buf, "{") == 0 )
		{
			++blkCnt1;
			lowSkill.clear();
			continue;
		}

		if( strcmp(buf, "}") == 0 )
		{
			--blkCnt1;
			m_SKTree_Merce.insert(std::make_pair(job, lowSkill));
			continue;
		}

		if( blkCnt1 == 0 )
		{
			job = (short)g_monParameter.CMonParameterMgr::SearchKeyword(buf);
			if( job == -1 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "not exist this job! (%s)", buf);
				MessageBoxA(NULL, msg, "Merce_SKTree", MB_OK);
				result = FALSE;
				break;
			}
		}
		else
		{
			SKID = this->CSkillTypeInfoMgr::GetSKID(buf);
			if( SKID == 0 )
			{
				char msg[256];
				sprintf_s(msg, countof(msg), "not exist lowerSKID!! (%s)", buf);
				MessageBoxA(NULL, msg, "Merce_SKTree", MB_OK);
				result = FALSE;
				break;
			}

			fscanf(fp, "%s", buf);
			lowSkill.insert(std::make_pair(SKID, atoi(buf)));
		}
	}

	fclose(fp);
	return result;
}


BOOL CSkillTypeInfoMgr::IsAvailableJob(short job, unsigned short SKID)
{
	int skClass = this->CSkillTypeInfoMgr::GetSKClass(SKID);
	if( skClass == SKCLASS_NORMAL )
	{
		std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator it = m_skillTreeInfo.find(job);
		if( it == m_skillTreeInfo.end() )
			return FALSE;

		std::map<unsigned short,std::map<unsigned short,int>>::iterator it2 = it->second.find(SKID);
		if( it2 == it->second.end() )
			return FALSE;

		return TRUE;
	}
	else
	if( skClass == SKCLASS_HOMUN )
	{
		std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator it = m_SKTree_Homun.find(job);
		if( it == m_SKTree_Homun.end() )
			return FALSE;

		std::map<unsigned short,std::map<unsigned short,int>>::iterator it2 = it->second.find(SKID);
		if( it2 == it->second.end() )
			return FALSE;

		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


short CSkillTypeInfoMgr::IsAvailable_Merce(short job, unsigned short SKID)
{
	std::map<short,std::map<unsigned short,int>>::iterator it = m_SKTree_Merce.find(job);
	if( it == m_SKTree_Merce.end() )
		return 0;

	std::map<unsigned short,int>::iterator it2 = it->second.find(SKID);
	if( it2 == it->second.end() )
		return 0;

	return static_cast<short>(it2->second);
}


BOOL CSkillTypeInfoMgr::IsConditionalSkill(short job, unsigned short SKID)
{
	if( this->CSkillTypeInfoMgr::IsGuildSkill(SKID) )
	{
		std::map<unsigned short,std::map<unsigned short,int>>::iterator it = m_GDSkillTreeInfo.find(SKID);
		if( it == m_GDSkillTreeInfo.end() )
			return FALSE;

		if( it->second.size() == 0 )
			return FALSE;

		return TRUE;
	}
	else
	{
		if( this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID)->CSkillTypeInfo::GetAvailableJobLevel() != 0 )
			return TRUE;

		std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator iter = m_skillTreeInfo.find(job);
		if( iter == m_skillTreeInfo.end() )
			return FALSE;

		std::map<unsigned short,std::map<unsigned short,int>>::iterator iter2 = iter->second.find(SKID);
		if( iter2 == iter->second.end() )
			return FALSE;

		if( iter2->second.size() == 0 )
			return FALSE;
		
		return TRUE;
	}
}


BOOL CSkillTypeInfoMgr::IsConditionSkill_HO(short job, unsigned short SKID)
{
	std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator it = m_SKTree_Homun.find(job);
	if( it != m_SKTree_Homun.end() )
	{
		std::map<unsigned short,std::map<unsigned short,int>>::iterator it2 = it->second.find(SKID);
		if( it2 != it->second.end() )
		{
			if( it2->second.size() != 0 )
				return TRUE;
		}
	}

	return ( this->CSkillTypeInfoMgr::GetCLevel_SKTreeHomun(job, SKID) != 0 );
}


BOOL CSkillTypeInfoMgr::IsGuildSkill(int SKID)
{
	return ( SKID >= SKID_GD_APPROVAL );
}


std::map<unsigned short,int>* CSkillTypeInfoMgr::GetLowerSkillTreeInfo(short job, unsigned short SKID)
{
	if( this->CSkillTypeInfoMgr::IsGuildSkill(SKID) )
	{
		std::map<unsigned short,std::map<unsigned short,int>>::iterator it = m_GDSkillTreeInfo.find(SKID);
		if( it == m_GDSkillTreeInfo.end() )
			return NULL;
		
		return &it->second;
	}

	int skClass = this->CSkillTypeInfoMgr::GetSKClass(SKID);
	if( skClass == SKCLASS_NORMAL )
	{
		std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator it = m_skillTreeInfo.find(job);
		if( it == m_skillTreeInfo.end() )
			return NULL;

		std::map<unsigned short,std::map<unsigned short,int>>::iterator it2 = it->second.find(SKID);
		if( it2 == it->second.end() )
			return NULL;

		return &it2->second;
	}
	else
	if( skClass == SKCLASS_HOMUN )
	{
		std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator it = m_SKTree_Homun.find(job);
		if( it == m_SKTree_Homun.end() )
			return NULL;

		std::map<unsigned short,std::map<unsigned short,int>>::iterator it2 = it->second.find(SKID);
		if( it2 == it->second.end() )
			return NULL;

		return &it2->second;
	}
	else
	{
		return NULL;
	}
}


void CSkillTypeInfoMgr::InheritFirstJobSkill(short secondJob, short firstJob)
{
	std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator itS = m_skillTreeInfo.find(secondJob);
	std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator itF = m_skillTreeInfo.find(firstJob);

	if( itF == m_skillTreeInfo.end() )
		return;

	if( itS == m_skillTreeInfo.end() )
	{
		std::map<unsigned short,std::map<unsigned short,int>> treeInfo;
		treeInfo.clear();
		m_skillTreeInfo.insert(std::make_pair(secondJob, treeInfo));
		itS = m_skillTreeInfo.find(secondJob);
	}

	for( std::map<unsigned short,std::map<unsigned short,int>>::iterator it = itF->second.begin(); it != itF->second.end(); ++it )
		if( itS->second.find(it->first) == itS->second.end() )
			itS->second.insert(*it);
}


void CSkillTypeInfoMgr::InheritPreJobSkill_HO(short nextJob, short preJob)
{
	std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator itP = m_SKTree_Homun.find(preJob);
	std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator itN = m_SKTree_Homun.find(nextJob);

	if( itP == m_SKTree_Homun.end() )
		return;

	if( itN == m_SKTree_Homun.end() )
	{
		std::map<unsigned short,std::map<unsigned short,int>> treeInfo;
		treeInfo.clear();
		m_SKTree_Homun.insert(std::make_pair(nextJob, treeInfo));
		itN = m_SKTree_Homun.find(nextJob);
	}

	for( std::map<unsigned short,std::map<unsigned short,int>>::iterator it = itP->second.begin(); it != itP->second.end(); ++it )
		if( itN->second.find(it->first) == itN->second.end() )
			itN->second.insert(*it);
}


std::map<unsigned short,std::map<unsigned short,int>>* CSkillTypeInfoMgr::GetAllAvailableSkill(short job)
{
	std::map<short,std::map<unsigned short,std::map<unsigned short,int>>>::iterator iter = m_skillTreeInfo.find(job);
	if( iter == m_skillTreeInfo.end() )
		return NULL;

	return &iter->second;
}


static std::map<int,int> GetSkillCategoryTbl()
{
	std::map<int,int> result;
	result.insert(std::pair<const int,int>(SKID_RA_WUGSTRIKE, SKILL_WUGATTACK));
	result.insert(std::pair<const int,int>(SKID_RA_WUGDASH, SKILL_WUGATTACK));
	result.insert(std::pair<const int,int>(SKID_RA_WUGBITE, SKILL_WUGATTACK));
	return result;
}


BOOL CSkillTypeInfoMgr::IsSkillCategory(unsigned short SKID, int type)
{
	switch( type )
	{
	case SKILL_TRAP:
	{
		switch( SKID )
		{
		case SKID_HT_ANKLESNARE:
		case SKID_HT_SKIDTRAP:
		case SKID_HT_SANDMAN:
		case SKID_HT_CLAYMORETRAP:
		case SKID_HT_FREEZINGTRAP:
		case SKID_HT_LANDMINE:
		case SKID_HT_SHOCKWAVE:
		case SKID_HT_FLASHER:
		case SKID_HT_TALKIEBOX:
		case SKID_HT_BLASTMINE:
		case SKID_MA_SKIDTRAP:
		case SKID_MA_SANDMAN:
		case SKID_MA_FREEZINGTRAP:
		case SKID_RA_MAGENTATRAP:
		case SKID_RA_COBALTTRAP:
		case SKID_RA_MAIZETRAP:
		case SKID_RA_VERDURETRAP:
		case SKID_RA_ELECTRICSHOCKER:
		case SKID_RA_CLUSTERBOMB:
		case SKID_RA_FIRINGTRAP:
		case SKID_RA_ICEBOUNDTRAP:
		case SKID_GN_THORNS_TRAP:
			return TRUE;
		default:
			return FALSE;
		};
	}
	break;
	case SKILL_TRAP_DAMAGE:
	{
		switch( SKID )
		{
		case SKID_HT_BLASTMINE:
		case SKID_HT_CLAYMORETRAP:
		case SKID_HT_SANDMAN:
		case SKID_HT_TALKIEBOX:
		case SKID_RA_CLUSTERBOMB:
		case SKID_RA_FIRINGTRAP:
		case SKID_RA_ICEBOUNDTRAP:
			return TRUE;
		default:
			return FALSE;
		};
	}
	break;
	case SKILL_BOLT:
	{
		switch( SKID )
		{
		case SKID_MG_COLDBOLT:
		case SKID_MG_FIREBOLT:
		case SKID_MG_LIGHTNINGBOLT:
			return TRUE;
		default:
			return FALSE;
		};
	}
	break;
	case SKILL_PLAYING:
	{
		switch( SKID )
		{
		case SKID_BD_LULLABY:
		case SKID_BD_RICHMANKIM:
		case SKID_BD_ETERNALCHAOS:
		case SKID_BD_DRUMBATTLEFIELD:
		case SKID_BD_RINGNIBELUNGEN:
		case SKID_BD_ROKISWEIL:
		case SKID_BD_INTOABYSS:
		case SKID_BD_SIEGFRIED:
//		case SKID_BD_RAGNAROK:
		case SKID_BA_DISSONANCE:
		case SKID_BA_WHISTLE:
		case SKID_BA_ASSASSINCROSS:
		case SKID_BA_POEMBRAGI:
		case SKID_BA_APPLEIDUN:
		case SKID_DC_UGLYDANCE:
		case SKID_DC_HUMMING:
		case SKID_DC_DONTFORGETME:
		case SKID_DC_FORTUNEKISS:
		case SKID_DC_SERVICEFORYOU:
		case SKID_CG_MOONLIT:
			return TRUE;
		default:
			return FALSE;
		};
	}
	case SKILL_PASSIVE_RESET:
	{
		switch( SKID )
		{
		case SKID_BS_HILTBINDING:
		case SKID_BS_SKINTEMPER:
		case SKID_CR_TRUST:
		case SKID_SA_DRAGONOLOGY:
		case SKID_HP_MEDITATIO:
		case SKID_HW_SOULDRAIN:
		case SKID_HP_MANARECHARGE:
			return TRUE;
		default:
			return FALSE;
		};
	}
	case SKILL_TYPE2_1:
	{
		if( SKID >= SKID_LK_AURABLADE && SKID <= SKID_PF_SOULBURN
		 || SKID >= SKID_LK_SPIRALPIERCE && SKID <= SKID_PF_SPIDERWEB
		 || SKID >= SKID_WE_BABY && SKID <= SKID_SL_SKA
		 || SKID >= SKID_PA_SHIELDCHAIN && SKID <= SKID_HW_GRAVITATION
		 || SKID >= SKID_CR_TRUST && SKID <= SKID_SA_COMA
		 || SKID >= SKID_TK_MISSION && SKID < SKID_LAST )
			return TRUE;
		return FALSE;
	}
	break;
	case SKILL_TYPE2_2:
	{
		if( SKID >= SKID_ASC_KATAR && SKID <= SKID_CG_MARIONETTE
		 || SKID >= SKID_ASC_METEORASSAULT && SKID <= SKID_ASC_CDP
		 || SKID >= SKID_ST_PRESERVE && SKID <= SKID_CR_FULLPROTECTION
		 || SKID >= SKID_WS_CARTTERMINATION && SKID <= SKID_CR_CULTIVATION
		 || SKID >= SKID_RG_SNATCHER && SKID <= SKID_AM_RESURRECTHOMUN
		 || SKID >= SKID_BD_ADAPTATION && SKID <= SKID_DC_SERVICEFORYOU )
			return TRUE;
		return FALSE;
	}
	break;
	case SKILL_MADOGEAR:
	{
		return ( SKID >= SKID_NC_MADOLICENCE && SKID <= SKID_NC_REPAIR );
	}
	break;
	case SKILL_IGNORE_BY_HOVERING:
	{
		switch( SKID )
		{
		case SKID_WZ_QUAGMIRE:
		case SKID_HT_SKIDTRAP:
		case SKID_HT_LANDMINE:
		case SKID_HT_ANKLESNARE:
		case SKID_HT_SHOCKWAVE:
		case SKID_HT_SANDMAN:
		case SKID_HT_FLASHER:
		case SKID_HT_FREEZINGTRAP:
		case SKID_HT_BLASTMINE:
		case SKID_HT_CLAYMORETRAP:
		case SKID_SA_VOLCANO:
		case SKID_SA_DELUGE:
		case SKID_SA_VIOLENTGALE:
		case SKID_HW_GRAVITATION:
		case SKID_NJ_SUITON:
		case SKID_SO_FIREWALK:
		case SKID_SO_ELECTRICWALK:
		case SKID_SO_VACUUM_EXTREME:
			return TRUE;
		default:
			return FALSE;
		};
	}
	break;
	case SKILL_EDP_PENALTY:
	{
		switch( SKID )
		{
		case SKID_AS_SONICBLOW:
		case SKID_ASC_BREAKER:
		case SKID_GC_CROSSIMPACT:
		case SKID_GC_COUNTERSLASH:
			return TRUE;
		default:
			return FALSE;
		};
	}
	break;
	case SKILL_WUGATTACK:
	{
		static std::map<int,int> Tbl = GetSkillCategoryTbl();

		std::map<int,int>::iterator iter = Tbl.find(SKID);
		if( iter == Tbl.end() )
			return FALSE;

		return ( iter->second == SKILL_WUGATTACK );
	}
	break;
	default:
	{
		return FALSE;
	}
	break;
	};
}


short CSkillTypeInfoMgr::GetPostDelayTM(unsigned short SKID, short level)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->GetPostDelayTM(level);
}


bool CSkillTypeInfoMgr::InitSkillScript()
{
	CBinBuf binBuf;
	if( !binBuf.CBinBuf::Load(GetScriptFileName(BIN_SKILL)) )
		return false;

	CSkillScriptHandler handler;
	if( !handler.CSkillScriptHandler::Run(&binBuf) )
		return false;

	return true;
}


void CSkillTypeInfoMgr::LoadSkillDelay(const char* fileName, void (CSkillTypeInfo::* func)(short skLevel, int time))
{
	FILE* fp = fopen(fileName, "r");
	if( fp == NULL )
		return;

	while( !feof(fp) )
	{
		char buf[1024] = {};
		fgets(buf, countof(buf), fp);

		const char* skName = strtok(buf, " \t\n");
		if( skName == NULL )
			continue;

		unsigned short SKID = this->CSkillTypeInfoMgr::GetSKID(skName);
		if( SKID == 0 )
		{
			Trace("Can't Not Find SKILL, %s\n", skName);
			continue;
		}

		CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
		if( info == NULL )
		{
			Trace("Can't Not Find SKILL, %s\n", skName);
			continue;
		}

		short skLevel = 1;
		int delay = 0;

		for( ; ; )
		{
			const char* pszdelay = strtok(NULL, " \t\n");
			if( pszdelay == NULL )
				break;

			delay = atoi(pszdelay);
			(info->*func)(skLevel++, delay);
		}

		while( skLevel <= info->GetMaxLevel() )
			(info->*func)(skLevel++, delay);
	}

	fclose(fp);
}


int CSkillTypeInfoMgr::GetSkillSinglePostDelay(unsigned short SKID, int skLevel)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->CSkillTypeInfo::GetSinglePostDelay(skLevel);
}


int CSkillTypeInfoMgr::GetSkillGlobalPostDelay(unsigned short SKID, int skLevel)
{
	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return 0;

	return info->CSkillTypeInfo::GetGlobalPostDelay(skLevel);
}


bool CSkillTypeInfoMgr::GetSkillTypeInfo2_SkillData(unsigned short SKID, unsigned long tokenType, short skLevel, int& value)
{
	value = 0;

	CSkillTypeInfo* info = this->CSkillTypeInfoMgr::SearchSkillTypeInfo(SKID);
	if( info == NULL )
		return false;

	if( info->GetVersion() != 2 )
		return false;

	if( skLevel < 1 || skLevel > info->GetMaxLevel() )
		return false;

	CSkillTypeInfo2* info2 = static_cast<CSkillTypeInfo2*>(info);
	STRUCT_SK_INTVALUE* data = reinterpret_cast<STRUCT_SK_INTVALUE*>(info2->CSkillTypeInfo2::GetInfo(tokenType));
	if( data == NULL )
		return false;
	
	value = data->value[skLevel - 1];
	return true;
}


int CSkillTypeInfoMgr::GetCLevel_SKTreeHomun(const short in_HomunJob, const unsigned short in_SKID)
{
	for( SKTREE_BYCLEVEL_CONTAINER::iterator SKTreeIter = m_SKTree_Homun_ByCLevel.find(in_HomunJob); SKTreeIter != m_SKTree_Homun_ByCLevel.end(); ++SKTreeIter )
		if( SKTreeIter->second.SKID == in_SKID )
			return SKTreeIter->second.cLevel; // found.

	return 0; // not found.
}
