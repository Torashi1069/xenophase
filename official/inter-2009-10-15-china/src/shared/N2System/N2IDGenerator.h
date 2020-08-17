#pragma once
#include "std/deque"
#include "std/map"
#include "std/queue"


class N2IDGenerator
{
	/* this+0x0  */ void* vtable;
	/* this+0x4  */ private: const unsigned short m_MinID;
	/* this+0x6  */ private: const unsigned short m_MaxID;
	/* this+0x8  */ private: const unsigned short m_GroupID;
	/* this+0xC  */ private: mystd::queue< unsigned int,mystd::deque<unsigned int> > m_StandbyIDqueue;
	/* this+0x2C */ private: mystd::map<unsigned int,bool> m_IDContainer;
	/* this+0x38 */ private: bool m_bOK;

	typedef mystd::map<unsigned int,bool>::const_iterator IDCONTAINERITOR;

	//public: const bool N2IDGenerator::isOK();
	//public: unsigned int N2IDGenerator::Alloc();
	//public: void N2IDGenerator::Free(const unsigned int);
	//public: const int GetGroupID();
	//public: void N2IDGenerator::N2IDGenerator(const unsigned short, const unsigned short, const unsigned short);
	//public: void N2IDGenerator::~N2IDGenerator();
};
