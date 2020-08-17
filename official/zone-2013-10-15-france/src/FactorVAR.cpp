#include "FactorVAR.h"
namespace FactorVAR {
////////////////////////////////////////


int INDvar::operator()(const int in_IndividualFactor) const // 20-23
{
	std::map<int,int>::const_iterator iter = m_Tbl.find(in_IndividualFactor);
	if( iter == m_Tbl.end() )
		return 0;

	return iter->second;
}


void INDvar::Set(const int in_IndividualFactor, const int in_Value) // 26-28
{
	m_Tbl[in_IndividualFactor] += in_Value;
}


////////////////////////////////////////


void SUMvar::Set(const int in_Key, const int in_Amount) // 55-59
{
	m_Sum -= m_Tbl[in_Key];
	m_Tbl[in_Key] = in_Amount;
	m_Sum += in_Amount;
}


void SUMvar::Reset(const int in_Key)
{
	std::map<int,int>::iterator iter = m_Tbl.find(in_Key);
	if( iter == m_Tbl.end() )
		return;

	m_Sum -= iter->second;
	m_Tbl.erase(iter);
}


////////////////////////////////////////


void MINvar::Set(const int in_Key, const int in_Amount)
{
	m_Tbl[in_Key] = in_Amount;

	std::map<int,int>::iterator iter = std::min_element(m_Tbl.begin(), m_Tbl.end());
	m_Min = ( iter != m_Tbl.end() ) ? iter->second : 0;
}


void MINvar::Reset(const int in_Key)
{
	if( m_Tbl.find(in_Key) == m_Tbl.end() )
		return;

	m_Tbl.erase(in_Key);

	std::map<int,int>::iterator iter = std::min_element(m_Tbl.begin(), m_Tbl.end());
	m_Min = ( iter != m_Tbl.end() ) ? iter->second : 0;
}


////////////////////////////////////////


void MAXvar::Set(const int in_Key, const int in_Amount) // 75-79
{
	m_Tbl[in_Key] = in_Amount;

	std::map<int,int>::iterator iter = std::max_element(m_Tbl.begin(), m_Tbl.end());
	m_Max = ( iter != m_Tbl.end() ) ? iter->second : 0;
}


void MAXvar::Reset(const int in_Key) // 82-89
{
	if( m_Tbl.find(in_Key) == m_Tbl.end() )
		return;

	m_Tbl.erase(in_Key);

	std::map<int,int>::iterator iter = std::max_element(m_Tbl.begin(), m_Tbl.end());
	m_Max = ( iter != m_Tbl.end() ) ? iter->second : 0;
}


////////////////////////////////////////


bool BOOLvar::operator()() const
{
	return ( m_RefCnt != 0 );
}


void BOOLvar::Set(const int in_Key) // 95-98
{
	++m_Tbl[in_Key];
	++m_RefCnt;
}


void BOOLvar::Reset(const int in_Key) // 100-106
{
	std::map<int,int>::iterator iter = m_Tbl.find(in_Key);
	if( iter == m_Tbl.end() )
		return;

	m_RefCnt -= iter->second;
	m_Tbl.erase(iter);
}


////////////////////////////////////////


void INDHISTORYvar::Set(const int in_IndividualFactor, const int in_HistoryFactor, const int in_Value) // 119-121
{
	m_Tbl[in_IndividualFactor].push_back(tagData(in_HistoryFactor, in_Value));
}


void INDHISTORYvar::Reset(const int in_IndividualFactor, const int in_HistoryFactor) // 125-131
{
	std::map<int,std::vector<tagData>>::iterator iter = m_Tbl.find(in_IndividualFactor);
	if( iter == m_Tbl.end() )
		return;

	std::vector<tagData>& history = iter->second;

	std::vector<tagData>::iterator i;

	for( i = history.begin(); i != history.end(); ++i )
		if( i->history == in_HistoryFactor )
			break;

	if( i == history.end() )
		return;

	history.erase(i);
}


std::pair<bool,int> INDHISTORYvar::operator()(const int in_IndividualFactor) const
{
	std::map<int,std::vector<tagData>>::const_iterator iter = m_Tbl.find(in_IndividualFactor);
	if( iter == m_Tbl.end() )
		return std::pair<bool,int>(false, 0);

	const std::vector<tagData>& history = iter->second;
	if( history.size() == 0 )
		return std::pair<bool,int>(false, 0);

	return std::pair<bool,int>(true, history.back().value);
}


////////////////////////////////////////


std::pair<bool,int> FactorVAR::HISTORYvar::operator()() const // 230-232
{
	if( m_History.size() == 0 )
		return std::pair<bool,int>(false, 0);

	return std::pair<bool,int>(true, m_Value);
}


void FactorVAR::HISTORYvar::Set(const int in_HistoryFactor, const int in_Value) // 235-238
{
	m_History.push_back(tagHistory(in_HistoryFactor, in_Value));
	m_Value = in_Value;
}


void FactorVAR::HISTORYvar::Reset(const int in_HistoryFactor) // 241-247
{
	std::vector<tagHistory>::iterator iter;

	for( iter = m_History.begin(); iter != m_History.end(); ++iter )
		if( iter->HistoryFactor == in_HistoryFactor )
			break; // found.

	if( iter == m_History.end() )
		return; // not found.

	m_History.erase(iter);

	if( m_History.size() != 0 )
		m_Value = m_History.back().Value;
	else
		m_Value = 0;
}


////////////////////////////////////////


int SUMHISTORYvar::operator()() const
{
	return m_Value;
}


void SUMHISTORYvar::Set(const int in_HistoryFactor, const int in_Value) // 307-310
{
	m_History.push_back(tagHistory(in_HistoryFactor, in_Value));

	int sum = 0;
	for( std::vector<tagHistory>::iterator iter = m_History.begin(); iter != m_History.end(); ++iter )
		sum += iter->Value;

	m_Value = sum;
}


void SUMHISTORYvar::Reset(const int in_HistoryFactor) // 299-305
{
	std::vector<tagHistory>::iterator iter;
	for( iter = m_History.begin(); iter != m_History.end(); ++iter )
		if( iter->HistoryFactor == in_HistoryFactor )
			break;

	if( iter == m_History.end() )
		return;

	m_History.erase(iter);

	int sum = 0;
	for( std::vector<tagHistory>::iterator iter = m_History.begin(); iter != m_History.end(); ++iter )
		sum += iter->Value;

	m_Value = sum;
}


////////////////////////////////////////


int INDSUMHISTORYvar::operator()(const int in_IndividualFactor) const // 330-333
{
	std::map<int,SUMHISTORYvar>::const_iterator iter = m_Tbl.find(in_IndividualFactor);
	if( iter == m_Tbl.end() )
		return 0;

	return iter->second.operator()();
}


////////////////////////////////////////
}; // namespace
