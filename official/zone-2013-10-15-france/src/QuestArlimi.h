#pragma once
#include "ArlimiMap.h"
#include "QuestProviso.h"
class CPC;


class CQuestArlimi
{
private:
	typedef std::list<unsigned long> T_PCLIST;
	typedef std::map<unsigned long,int> T_PCMAP;

public:
	CQuestArlimi();
	virtual ~CQuestArlimi();

private:
	/* this+ 0 */ //const CQuestArlimi::`vftable';
	/* this+ 4 */ T_PCLIST m_pcQueue;
	/* this+16 */ T_PCMAP m_pcMap;
	/* this+32 */ CQuestProviso m_proviso;
	/* this+88 */ CArlimiMap m_arlimiMap;

public:
	bool Initialize();
	void Filnalize();
	void Process();
	int ProvisoCalulation(CPC* pPC, unsigned long qid, int& qType);
	void SendQuestEffect(CPC* pc, unsigned long npcID, unsigned long xPos, unsigned long yPos, int effect, unsigned long qType);
	void InsertPCQuest(unsigned long aid);
	void UpdatePCQuest(unsigned long , unsigned long ); //TODO
	bool FindArimiPC(unsigned long AID);
};
