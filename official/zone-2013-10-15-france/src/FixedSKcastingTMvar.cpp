#include "Enum.h"
#include "FixedSKcastingTMvar.h"
#include "shared/NCriticalErrorLog.h"


CFixedSKcastingTMvar::CFixedSKcastingTMvar()
{
}


CFixedSKcastingTMvar::~CFixedSKcastingTMvar()
{
}


void CFixedSKcastingTMvar::Init()
{
	m_Amount.CAmount::Init();
	m_Permill.CAmount::Init();
}


int CFixedSKcastingTMvar::Get(const int in_Value, const int in_SKID)
{
	if( in_SKID == SKID_SA_CASTCANCEL )
		return in_Value;

	int val = in_Value + m_Amount.Get(in_SKID);
	if( val < 0 )
		val = 0;

	int mil = m_Permill.Get(in_SKID);

	int result = int(val * (1000 + mil) / 1000.0);
	return result;
}


namespace FixedSKcastingTMvarStuff
{


namespace {
class APPLYfunctor
{
public:
	void operator()(const std::tr1::shared_ptr<CItem>& in_Item)
	{
		if( (*in_Item).m_cpApply->operator()(m_SKID) )
			m_ActiveDatas.push_back((*in_Item).m_Value);
	}

public:
	APPLYfunctor(const int in_SKID, std::vector<int>& in_ActiveDatas) : m_SKID(in_SKID), m_ActiveDatas(in_ActiveDatas)
	{
	}

private:
	/* this+0 */ std::vector<int>& m_ActiveDatas;
	/* this+4 */ const int m_SKID;
};
}; // namespace


namespace {
class ItemCompareFunctor : public std::binary_function<std::tr1::shared_ptr<CItem>,CIdentity,bool>
{
public:
	bool operator()(const std::tr1::shared_ptr<CItem>& , const CIdentity& ); //TODO
};
}; // namespace


CAmount::CAmount()
{
}


CAmount::~CAmount()
{
	m_Amounts.clear();
}


void CAmount::Init()
{
	m_Amounts.clear();
}


void CAmount::Add(const std::tr1::shared_ptr<CItem>& in_ItemPtr)
{
	CONTAINER::iterator iter;
	for( iter = m_Amounts.begin(); iter != m_Amounts.end(); ++iter )
	{
		if( (*iter)->m_Identity == (*in_ItemPtr).m_Identity )
			break;
	}

	if( iter == m_Amounts.end() )
		m_Amounts.push_back(in_ItemPtr);
	else
		(*iter)->m_Value += (*in_ItemPtr).m_Value;
}


void CAmount::Remove(const CIdentity& in_Identity)
{
	for( CONTAINER::iterator iter = m_Amounts.begin(); iter != m_Amounts.end(); )
	{
		if( (*iter)->m_Identity == in_Identity )
			iter = m_Amounts.erase(iter);
		else
			++iter;
	}
}


int CAmount::Get(const int in_SKID) const
{
	int Amount = 0;

	std::vector<int> ActiveDatas;
	std::for_each(m_Amounts.begin(), m_Amounts.end(), APPLYfunctor(in_SKID,ActiveDatas));

	for( std::vector<int>::iterator iter = ActiveDatas.begin(); iter != ActiveDatas.end(); ++iter )
		Amount += (*iter);

	return Amount;
}


CPermill::CPermill()
{
}


CPermill::~CPermill()
{
}


int CPermill::Get(const int in_SKID) const
{
	std::vector<int> ActiveDatas;
	std::for_each(m_Amounts.begin(), m_Amounts.end(), APPLYfunctor(in_SKID,ActiveDatas));

	std::vector<int>::iterator iterMax = std::max_element(ActiveDatas.begin(), ActiveDatas.end());
	std::vector<int>::iterator iterMin = std::min_element(ActiveDatas.begin(), ActiveDatas.end());
	int valMax = ( iterMax != ActiveDatas.end() && *iterMax > 0 ) ? *iterMax : 0;
	int valMin = ( iterMin != ActiveDatas.end() && *iterMin < 0 ) ? *iterMin : 0;

	return valMin + valMax;
}


void CPermill::Add(const std::tr1::shared_ptr<CItem>& in_ItemPtr)
{
	if( abs((*in_ItemPtr).m_Value) > 1000 )
	{
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "수치값의 절대값이 1000 보다 커서는 않됩니다.(%d)", (*in_ItemPtr).m_Value);
		NCriticalErrorLog::GetObj()->NFileLog::WriteFmt(__FILE__, __LINE__, "Kind(%d) ID(%d)", (*in_ItemPtr).m_Identity.CIdentity::GetKind(), (*in_ItemPtr).m_Identity.CIdentity::GetID());
		return;
	}

	this->FixedSKcastingTMvarStuff::CAmount::Add(in_ItemPtr);
}


}; // namespace FixedSKcastingTMvarStuff
