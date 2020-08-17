#pragma once
#include <map>
#include <string>
class Protocol;


class ProtocolMgr
{
public:
	static void Register(std::string name, Protocol* proto);
	static const Protocol* Get(std::string name);

private:
	static ProtocolMgr& getInstance();

private:
	std::map<std::string,Protocol*> m_map;
};
