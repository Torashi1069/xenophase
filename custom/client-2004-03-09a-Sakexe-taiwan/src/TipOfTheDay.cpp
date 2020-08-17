#include "Globals.h"
#include "TipOfTheDay.h"


CTipOfTheDay::CTipOfTheDay() // line 8 (TipOfTheDay.h)
{
	m_bTryLoading = false;
}


CTipOfTheDay::~CTipOfTheDay() // line 9 (TipOfTheDay.h)
{
}


hook_func<int (CTipOfTheDay::*)()> CTipOfTheDay::_Load(SAKEXE, "CTipOfTheDay::Load");
int CTipOfTheDay::Load() // line 8-67
{
	return (this->*_Load)();

	m_bTryLoading = true;

	const char* fileName = ( g_serviceType == ServiceAmerica ) ? "tipOfTheday_e.txt"
	                     : ( g_serviceType == ServiceJapan   ) ? "tipOfTheday_j.txt"
	                     :                                       "tipOfTheday.txt";

	FILE* fp = fopen(fileName, "r");
	if( fp == NULL )
		return 0;
	fseek(fp, 0, SEEK_END);
	long fileSize = ftell(fp);
	char* buf = new char[fileSize + 1];
	fseek(fp, 0, SEEK_SET);
	fread(buf, fileSize, 1, fp);
	buf[fileSize] = '\0';
	fclose(fp);

	mystd::vector<mystd::string> tmpList;
	char* base = buf;

	for( int i = 0; i < fileSize; ++i )
	{
		if( buf[i] == '\n' )
		{
			buf[i] = '\0';
			tmpList.push_back(base);
			base = &buf[i + 1];
		}
		else
		if( buf[i] == '#' )
		{
			buf[i] = '\0';
			tmpList.push_back(base);
			m_tipList.push_back(tmpList);
			tmpList.clear();
			base = &buf[i + 1];
		}
	}

	if( buf )
		delete[] buf;

	return 1;
}


//hook_func<int (CTipOfTheDay::*)()> CTipOfTheDay::_Size(SAKEXE, "CTipOfTheDay::Size");
int CTipOfTheDay::Size() // line ??
{
//	return (this->*_Size)();

	if( !m_bTryLoading )
		this->CTipOfTheDay::Load();

	return m_tipList.size();
}


hook_func<mystd::vector<mystd::string>& (CTipOfTheDay::*)(int index)> CTipOfTheDay::_GetTip(SAKEXE, "CTipOfTheDay::GetTip");
mystd::vector<mystd::string>& CTipOfTheDay::GetTip(int index) // line 70-76
{
	return (this->*_GetTip)(index);

	if( !m_bTryLoading )
		this->CTipOfTheDay::Load();

	if( index < 0 || index >= (int)m_tipList.size() )
		index = 0; // default for out-of-range index
	
	return m_tipList[index];
}
