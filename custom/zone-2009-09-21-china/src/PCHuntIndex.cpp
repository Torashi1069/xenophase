#include "PCHuntIndex.h"
#include "ErrorLog.h"
#include "globals.hpp"
////////////////////////////////////////


CNode::CNode()
{
	this->CNode::Clear();
}


CNode::~CNode()
{
	this->CNode::Clear();
}


void CNode::Init(unsigned long mobGID)
{
	this->CNode::Clear();
	m_mobGID = mobGID;
}


void CNode::Clear()
{
	m_list.clear();
	m_mobGID = 0;
}


void CNode::DeleteNode(int huntIdent)
{
	m_list.remove(huntIdent);
}


bool CNode::Set(int huntIdent)
{
	if( huntIdent <= 0 )
		return false;

	m_list.push_back(huntIdent);
	return true;
}


int CNode::GetIdent(mystd::list<int>& identList)
{
	int count = 0;

	for( TNODE_LIST::const_iterator it = m_list.begin(); it != m_list.end(); ++it )
	{
		identList.push_back(*it);
		++count;
	}

	return count;
}


int CNode::GetCount()
{
	return static_cast<int>(m_list.size());
}


////////////////////////////////////////


CPCHuntIndex::CPCHuntIndex()
{
}


CPCHuntIndex::~CPCHuntIndex()
{
}


void CPCHuntIndex::Clear()
{
	for( THUNT_INDEX_MAP::iterator it = m_map.begin(); it != m_map.end(); ++it )
		delete it->second;
	m_map.clear();
}


void CPCHuntIndex::EraseHuntIdent(unsigned long mobGID, int huntIdent)
{
	THUNT_INDEX_MAP::iterator it = m_map.find(mobGID);
	if( it == m_map.end() )
		return; // not found.

	CNode* node = it->second;

	node->CNode::DeleteNode(huntIdent);
	if( node->CNode::GetCount() <= 0 )
	{
		delete node;
		m_map.erase(mobGID);
	}
}


bool CPCHuntIndex::AddHuntList(unsigned long mobGID, int huntIdent)
{
	THUNT_INDEX_MAP::iterator it = m_map.find(mobGID);
	if( it == m_map.end() )
	{// new entry
		CNode* node = new (std::nothrow) CNode();
		if( node == NULL )
		{
			g_errorLogs->CErrorLog::CriticalErrorLog("Memory Alloc Fail!!(q_21) \n", __LINE__, __FILE__);
			return false;
		}

		node->CNode::Init(mobGID);
		node->CNode::Set(huntIdent);
		m_map.insert(mystd::pair<unsigned long,CNode*>(mobGID, node));
		return true;
	}
	else
	{// existing entry
		CNode* node = it->second;
		if( node == NULL )
			return false;

		node->CNode::Set(huntIdent);
		return true;
	}
}


int CPCHuntIndex::GetHuntIdentList(unsigned long mobGID, mystd::list<int>& identList)
{
	THUNT_INDEX_MAP::iterator it = m_map.find(mobGID);
	if( it == m_map.end() )
		return 0;

	CNode* node = it->second;
	if( node == NULL )
		return 0;

	return node->CNode::GetIdent(identList);
}


////////////////////////////////////////
