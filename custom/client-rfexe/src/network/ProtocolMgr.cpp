#include "Protocol.h"
#include "ProtocolMgr.h"


ProtocolMgr& ProtocolMgr::getInstance()
{
	static ProtocolMgr s_mgr;
	return s_mgr;
}


void ProtocolMgr::Register(std::string name, Protocol* proto)
{
	ProtocolMgr& self = getInstance();

	self.m_map.insert(std::pair<std::string,Protocol*>(name, proto));
}


const Protocol* ProtocolMgr::Get(std::string name)
{
	ProtocolMgr& self = getInstance();

	std::map<std::string,Protocol*>::iterator it = self.m_map.find(name);
	if( it == self.m_map.end() )
		return NULL;

	Protocol* p = it->second;
	p->Init();
	return p;
}
