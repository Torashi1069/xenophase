#include "LuaMonsterAI/NLuaMonsterAI.h"


NLuaMonsterAI::NLuaMonsterAI(const int in_ID, const unsigned long in_AID, const bool in_bForceProcessing)
: m_MessageQueue(),
  m_pThread(NULL),
//m_Ref(0),
  m_Name(""),
  m_ID(in_ID),
  m_ProcFuncStep(),
  m_AID(in_AID),
  m_bForceProcessing(in_bForceProcessing)
{
}


NLuaMonsterAI::~NLuaMonsterAI()
{
	if( m_pThread != NULL )
	{
		delete m_pThread;
		m_pThread = NULL;
	}
}


lua_State* NLuaMonsterAI::GetStatePtr()
{
	return m_pThread->NLuaThread::GetStatePtr();
}


std::pair<bool,NLuaMonsterAI::MSG_SHARDPTR> NLuaMonsterAI::GetAsyncMsg()
{
	if( m_MessageQueue.size() == 0 )
		return std::pair<bool,MSG_SHARDPTR>(false, MSG_SHARDPTR(NULL));

	MSG_SHARDPTR msg = m_MessageQueue.front();
	m_MessageQueue.pop_front();

	return std::pair<bool,MSG_SHARDPTR>(true, msg);
}


void NLuaMonsterAI::Init(const std::string in_Name, NLuaThread* in_pThread, const int in_Ref)
{
	m_Name = in_Name;
	m_pThread = in_pThread;
	m_Ref = in_Ref;
}


void NLuaMonsterAI::InsertMSG_ATTACKED(const unsigned long in_AID, const int in_Damage)
{
	MSG_SHARDPTR msg = MSG_SHARDPTR(new(std::nothrow) LuaMonsterAIStuff::NMSG_ATTACKED(in_AID, in_Damage));
	if( msg.get() != NULL )
		m_MessageQueue.push_back(msg);
}


void NLuaMonsterAI::InsertMSG_DEAD(const unsigned long in_AID)
{
	MSG_SHARDPTR msg = MSG_SHARDPTR(new(std::nothrow) LuaMonsterAIStuff::NMSG_DEAD(in_AID));
	if( msg.get() != NULL )
		m_MessageQueue.push_back(msg);
}


void NLuaMonsterAI::InsertMSG_LOG()
{
	MSG_SHARDPTR msg = MSG_SHARDPTR(new(std::nothrow) LuaMonsterAIStuff::NMSG_LOG());
	if( msg.get() != NULL )
		m_MessageQueue.push_back(msg);
}


void NLuaMonsterAI::InsertMSG_TELEPORT(const int in_xPos, const int in_yPos, const char* in_MapName)
{
	MSG_SHARDPTR msg = MSG_SHARDPTR(new(std::nothrow) LuaMonsterAIStuff::NMSG_TELEPORT(in_xPos, in_yPos, in_MapName));
	if( msg.get() != NULL )
		m_MessageQueue.push_back(msg);
}


void NLuaMonsterAI::SetProcessFuncStep(const NLuaMonsterAI::enumProcessFuncStep in_Step)
{
	m_ProcFuncStep.NLuaMonsterAI::NStep::Set(in_Step);
}


NLuaMonsterAI::enumProcessFuncStep NLuaMonsterAI::GetProcessFuncStep()
{
	return m_ProcFuncStep.NLuaMonsterAI::NStep::Get();
}


unsigned long NLuaMonsterAI::GetProcessFuncStepTime()
{
	return m_ProcFuncStep.NLuaMonsterAI::NStep::GetTime();
}


bool NLuaMonsterAI::IsForceProcessing()
{
	return m_bForceProcessing;
}


const int NLuaMonsterAI::GetID()
{
	return m_ID;
}


const char* NLuaMonsterAI::GetNamePtr()
{
	return m_Name.c_str();
}


const int NLuaMonsterAI::GetRef()
{
	return m_Ref;
}


unsigned long NLuaMonsterAI::GetAID()
{
	return m_AID;
}
