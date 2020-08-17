#include "grfindex.h"


GrfIndex::GrfIndex()
{
	m_first_node = NULL;
	m_count = 0;
}


GrfIndex::~GrfIndex()
{
	// free nodes in the linked list
	GrfNode* node = m_first_node;
	while( node != NULL )
	{
		GrfNode* next = node->next;
		delete node;
		node = next;
	}
}


size_t GrfIndex::size() const
{
	return m_count;
}


GrfNode* GrfIndex::find(const std::string& name)
{
	return m_fast_table.find(name);
}


GrfNode* GrfIndex::insert(GrfEntry entry, GrfNode* anchor)
{
	GrfNode* node = new GrfNode(entry);
	if( !this->insert(node, anchor) )
	{
		delete node;
		return NULL;
	}
	return node;
}


bool GrfIndex::insert(GrfNode* node, GrfNode* anchor)
{
	if( !m_fast_table.insert(node->name, node) )
		return false; // entry with this name already exists
	this->attach(node, anchor);
	++m_count;
	return true;
}


bool GrfIndex::rename(GrfNode* node, const std::string& newname)
{
	if( !m_fast_table.insert(newname, node) )
		return false; // name already taken
	m_fast_table.remove(node->name);
	node->name = newname;
	return true;
}


void GrfIndex::erase(GrfNode* node)
{
	m_fast_table.remove(node->name); // best-effort
	this->detach(node);
	delete node;
	--m_count;
}


void GrfIndex::attach(GrfNode* node, GrfNode* anchor)
{
	if( anchor == NULL )
	{// prepend to the beginning of list
		node->next = m_first_node;
		node->prev = anchor;
		m_first_node = node;
		if( node->next != NULL )
			node->next->prev = node;
	}
	else
	{// insert after the specified anchor node
		node->next = anchor->next;
		node->prev = anchor;
		anchor->next = node;
		if( node->next != NULL )
			node->next->prev = node;
	}
}


void GrfIndex::detach(GrfNode* node)
{
	if( m_first_node == node )
		m_first_node = node->next;

	GrfNode* next = node->next;
	GrfNode* prev = node->prev;
	if( next != NULL ) next->prev = prev;
	if( prev != NULL ) prev->next = next;
}
