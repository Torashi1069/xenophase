#pragma once
#include "Common/EnterTraceLog.h"
class CProcess;


template<typename T> class CProcessFactory
{
public:
	CProcessFactory();
	~CProcessFactory();
	bool CreateProcessList(std::list<CProcess*>* pList, int ObjNum);

private:
	/* this+0 */ std::list<CProcess*> m_ProcessObjList;
};


template<typename T> CProcessFactory<T>::CProcessFactory()
{
}


template<typename T> CProcessFactory<T>::~CProcessFactory()
{
	for( std::list<CProcess*>::iterator it = m_ProcessObjList.begin(); it != m_ProcessObjList.end(); ++it )
		delete *it;

	m_ProcessObjList.clear();
}


template<typename T> bool CProcessFactory<T>::CreateProcessList(std::list<CProcess*>* pList, int ObjNum)
{
	for( int i = 0; i < ObjNum; ++i )
	{
		CProcess* p = new T();
		if( p == NULL )
		{
			CEnterTraceLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "%s - CProcessFactory<%s>::CreateProcessListerror, not enough memory\n", __FUNCTION__, typeid(T).name()); //NOTE: RTTI
			return false;
		}

		pList->push_back(p);
		m_ProcessObjList.push_back(p);
	}

	return true;
}
