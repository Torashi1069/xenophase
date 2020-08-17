#include "CharacterMgr.h"
#include "Enum.h"
#include "ITPMgr.h"
#include "QuestArlimi.h"
#include "ZoneProcess.h"
#include "Common/Packet.h"


CQuestArlimi::CQuestArlimi()
{
}


CQuestArlimi::~CQuestArlimi()
{
	this->CQuestArlimi::Filnalize();
}


bool CQuestArlimi::Initialize()
{
	this->CQuestArlimi::Filnalize();

	if( !m_proviso.CQuestProviso::Init() )
		return false;
	
	if( !m_arlimiMap.CArlimiMap::Initialize() )
		return false;

	return true;
}


void CQuestArlimi::Filnalize()
{
	m_pcQueue.clear();
	m_pcMap.clear();
}


void CQuestArlimi::Process()
{
	if( m_pcQueue.size() < 1 )
		return;

	unsigned long aid = m_pcQueue.front();
	m_pcQueue.pop_front();
	m_pcMap.erase(aid);

	CPC* pc = (CPC*)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(aid, PC_TYPE);
	if( pc == NULL )
		return;

	int effect = PACKET_ZC_QUEST_NOTIFY_EFFECT::EFFECT_OFF;
	int qType = PACKET_ZC_QUEST_NOTIFY_EFFECT::QTYPE_YELLOW;

	unsigned long index = pc->m_questEvent.CPCQuestEvent::GetArlimiList();
	T_ARLIMI_DATA* data = m_arlimiMap.CArlimiMap::GetArlimiData(index);
	if( data == NULL )
		return;

	for( size_t i = 0; i < data->t_questList.size(); ++i )
	{
		int ret = this->CQuestArlimi::ProvisoCalulation(pc, data->t_questList[i], qType);
		if( ret == -1 )
			return;

		if( effect < ret )
			effect = ret;

		if( effect == PACKET_ZC_QUEST_NOTIFY_EFFECT::EFFECT_QUE )
			break;
	}

	if( data->t_npcID == 0 )
		qType = PACKET_ZC_QUEST_NOTIFY_EFFECT::QTYPE_PURPLE;

	this->CQuestArlimi::SendQuestEffect(pc, data->t_npcID, data->t_xPos, data->t_yPos, effect, qType);

	m_pcQueue.push_back(aid);
	m_pcMap.insert(std::pair<const unsigned long,int>(aid, 1));
}


hook_func<void (__stdcall *)()> CQuestArlimi__ProvisoCalulation(EXEPATH(), "CQuestArlimi::ProvisoCalulation");
int CQuestArlimi::ProvisoCalulation(CPC* pPC, unsigned long qid, int& qType)
{
	int result;
	void* hookptr = CQuestArlimi__ProvisoCalulation;
	__asm lea eax, qType
	__asm push eax
	__asm push qid
	__asm mov eax, pPC
	__asm call hookptr
	__asm mov result, eax
	return result;
/*
	TPROVISO* proviso = m_proviso.CQuestProviso::SelectProviso(qid);
	if( proviso == NULL )
		return -1;

	qType = proviso->t_questType;

	if( pPC == NULL )
		return 0;
	
	int questState = pPC->m_questEvent.CPCQuestEvent::IsBeginQuest(qid);
	switch( questState )
	{
	case 0:
	{
		bool levelCheck = true;
		bool sexCheck = true;
		bool jobCheck = true;
		bool itemCheck = true;
		bool homunLevel_Check = true;
		bool homunType_Check = true;

		int lv;
		int sex;
		int job;
		pPC->GetParameterValue(VAR_CLEVEL, lv);
		pPC->GetParameterValue(VAR_SEX, sex);
		pPC->GetParameterValue(VAR_JOB, job);

		if( lv < proviso->t_lowLV || lv > proviso->t_hiLV )
			levelCheck = false;

		if( proviso->t_sex != 0 && proviso->t_sex != sex )
			sexCheck = false;

		if( proviso->t_jobList.size() > 1 )
		{
			jobCheck = false;

			for( size_t i = 0; i < proviso->t_jobList.size(); ++i )
			{
				if( job == proviso->t_jobList[i] )
				{
					jobCheck = true;
					break;
				}
			}
		}

		for( std::map<unsigned long,int>::iterator iter = proviso->t_itemList.begin(); iter != proviso->t_itemList.end(); ++iter )
		{
			unsigned short reqITID = (unsigned short)iter->first;
			int reqCount = iter->second;

			if( reqCount == 0 )
				continue;

			int count = 0;
			pPC->GetBodyItemCount(reqITID, &count);
			if( count < reqCount )
			{
				itemCheck = false;
				break;
			}
		}

		if( proviso->t_homun_minLv != -1 || proviso->t_homun_evolution != -1 )
		{
			CNpcHomun* hom = pPC->m_pcBattle.CPCBattle::GetMyHomun();
			if( pPC->m_pcBattle.CPCBattle::IsHomunState() == 2 && hom != NULL )
			{
				if( proviso->t_homun_minLv != -1 )
				{
					int ho_level = 0;
					homunLevel_Check = false;

					hom->GetParameterValue(11, &ho_level);
					if( ho_level >= proviso->t_homun_minLv && ho_level <= proviso->t_homun_maxLv )
						homunLevel_Check = 1;
				}

				if( proviso->t_homun_evolution != -1 )
				{
					int ho_job = 0;
					homunType_Check = false;

					hom->GetParameterValue(VAR_JOB, &ho_job);
					short evo = ( ho_job >= JT_MER_EIRA && ho_job <= JT_MER_ELEANOR )        ? 2
					          : ( ho_job >= JT_MER_LIF_H && ho_job <= JT_MER_VANILMIRTH_H2 ) ? 1
					          :                                                                0;

					if( proviso->t_homun_evolution == hom )
						homunType_Check = true;
				}
			}
			else
			{
				homunLevel_Check = false;
				homunType_Check = false;
			}
		}

		if( !levelCheck || !sexCheck || !jobCheck || !itemCheck || !homunLevel_Check || !homunType_Check )
			return 0;

		return 1;
	}
	break;
	case 1:
	{
		if( pPC->m_questEvent.CPCQuestEvent::CheckQuest_Hunting(qid) == 1 )
			return 0;

		for( std::map<unsigned long,int>::iterator iter = proviso->t_completeItemList.begin(); iter != proviso->t_completeItemList.end(); ++iter )
		{
			unsigned short reqITID = iter->first;
			short reqCount = LOWORD(iter->second);

			CITP* itp = g_itpMgr.CITPMgr::GetITP(reqITID);
			if( itp == NULL )
				return 0;

			int count = 0;
			if( !pPC->GetBodyItemCount(reqITID, count) )
				return 0;

			if( itp->GetType() == TYPE_QUEST )
			{
				if( count != reqCount )
					return 0;
			}
			else
			{
				if( count < reqCount )
					return 0;
			}
		}

		return 2;
	}
	break;
	case 2:
	{
		return 0;
	}
	break;
	default:
	{
		return 0;
	}
	break;
	};
*/
}


void CQuestArlimi::InsertPCQuest(unsigned long aid)
{
	if( this->CQuestArlimi::FindArimiPC(aid) )
		return;

	CPC* pc = (CPC *)CCharacterMgr::GetObj()->CCharacterMgr::FindCharacter(aid, PC_TYPE);
	if( pc == NULL )
		return;

	pc->m_questEvent.CPCQuestEvent::ResetArlimiList();

	std::list<unsigned long> npcList;
	m_arlimiMap.CArlimiMap::GetQuestNpcList(pc->CPC::GetMapID(), npcList);
	if( npcList.size() == 0 )
		return;

	while( npcList.size() != 0 )
	{
		unsigned long npcID = npcList.front();
		npcList.pop_front();
		pc->m_questEvent.CPCQuestEvent::SetArlimiList(npcID);
	}

	m_pcQueue.push_back(aid);
	m_pcMap.insert(std::pair<const unsigned long,int>(aid, 1));
}


bool CQuestArlimi::FindArimiPC(unsigned long AID)
{
	return ( m_pcMap.find(AID) != m_pcMap.end() );
}


void CQuestArlimi::SendQuestEffect(CPC* pc, unsigned long npcID, unsigned long xPos, unsigned long yPos, int effect, unsigned long qType)
{
	pc->CPC::SendQuestNotifyEffect(npcID, static_cast<short>(xPos), static_cast<short>(yPos), effect, static_cast<short>(qType));
}
