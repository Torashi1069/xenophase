#include "Globals.h" // Trace()
#include "Base/File.h" // CFile
#include "Base/ResMgr.h"
#include "Resource/ImfRes.h"


CImfRes::CImfRes(Exemplar __formal, const char* resid, const char* baseDir) // line 23 (Resource/ImfRes.h)
{
	g_resMgr().CResMgr::RegisterType(resid, baseDir, this);
}


CImfRes::CImfRes(void) // line 18
{
	for( int i = 0; i < 15; ++i )
	{
		m_maxAction[i] = 0;
		memset(m_maxMotion[i], 0, sizeof(m_maxMotion[i]));
	}
}


hook_method<CRes* (CImfRes::*)(void) const> CImfRes::_Clone(SAKEXE, "CImfRes::Clone");
CRes* CImfRes::Clone(void) const // line 23 (Resource/ImfRes.h)
{
	return (this->*_Clone)();

	return new CImfRes();
}


hook_method<void (CImfRes::*)(void)> CImfRes::_Create(SAKEXE, "CImfRes::Create");
void CImfRes::Create(void) // line 29
{
	return (this->*_Create)();

	;
}


hook_method<bool (CImfRes::*)(const char* fName)> CImfRes::_Load(SAKEXE, "CImfRes::Load");
bool CImfRes::Load(const char* fName) // line 34
{
	return (this->*_Load)(fName);

	CFile fp;
	if( !fp.CFile::Open(fName, CFile::modeRead) )
	{
		Trace("야, %s 파일이 없는거 같애.", fName);
		return false;
	}

	float Ver;
	fp.CFile::Read(&Ver, 4);

	if( Ver < 1.01f )
	{
		Trace("%s 읽기 실패! 이전 버전의 포맷임. 새 버전으로 다시 저장한 후 부를것.", fName);
		return false;
	}

	int Sum;
	fp.CFile::Read(&Sum, 4);

	int MaxLayer;
	fp.CFile::Read(&MaxLayer, 4);

	for( int layerId = 0; layerId < MaxLayer + 1; ++layerId )
	{
		mystd::vector<ImfData> ImfArBuf;

		int actioncount;
		fp.CFile::Read(&actioncount, 4);
		m_maxAction[layerId] = actioncount;

		for( int actionId = 0; actionId < actioncount; ++actionId )
		{
			ImfData ImfBuf;

			int motioncount;
			fp.CFile::Read(&motioncount, 4);
			m_maxMotion[layerId][actionId] = motioncount;

			for( int motionId = 0; motionId < motioncount; ++motionId )
			{
				int priority;
				fp.CFile::Read(&priority, 4);
				ImfBuf.m_Priority.push_back(priority);

				int cx;
				fp.CFile::Read(&cx, 4);
				ImfBuf.m_cx.push_back(cx);

				int cy;
				fp.CFile::Read(&cy, 4);
				ImfBuf.m_cy.push_back(cy);
			}

			ImfArBuf.push_back(ImfBuf);
		}

		m_ImfData.push_back(ImfArBuf);
	}

	return true;
}


hook_method<int (CImfRes::*)(int MaxLayer)> CImfRes::_CheckSum(SAKEXE, "CImfRes::CheckSum");
int CImfRes::CheckSum(int MaxLayer) // line 107
{
	return (this->*_CheckSum)(MaxLayer);

	int* buf = new int[MaxLayer]; //FIXME: should be MaxLayer+1, causes buffer overrun
	int Sum = 0;

	int exp10 = 1;
	int d = MaxLayer * ((MaxLayer < 4) + 1);
	for( int i = 0; i < d + 1; ++i )
		exp10 *= 10;

	for( int layerId = 0; layerId < MaxLayer + 1; ++layerId )
	{
		int pri = 0;
		int sub = 0;

		for( int actionId = 0; actionId < (int)m_ImfData[layerId].size(); ++actionId )
		{
			ImfData& imf = m_ImfData[layerId][actionId];

			for( int motionId = 0; motionId < (int)imf.m_Priority.size(); ++motionId )
			{
				pri += imf.m_Priority[motionId];
				sub += pri * imf.m_cx[motionId]; //NOTE: official skips this if multiplying by zero
				sub += pri * imf.m_cy[motionId]; //NOTE: official skips this if multiplying by zero
			}
		}

		int val = pri * exp10 + sub;
		buf[layerId] = val;
		Sum += val;
	}

	return Sum; //FIXME: memory leak on 'buf'
}


hook_method<int (CImfRes::*)(void)> CImfRes::_GetNumLayer(SAKEXE, "CImfRes::GetNumLayer");
int CImfRes::GetNumLayer(void) // line 137
{
	return (this->*_GetNumLayer)();

	return (int)m_ImfData.size();
}


hook_method<int (CImfRes::*)(int NumLayer)> CImfRes::_GetNumAction(SAKEXE, "CImfRes::GetNumAction");
int CImfRes::GetNumAction(int NumLayer) // line 142
{
	return (this->*_GetNumAction)(NumLayer);

	return (int)m_ImfData[NumLayer].size();
}


hook_method<int (CImfRes::*)(int NumLayer, int NumAction)> CImfRes::_GetNumMotion(SAKEXE, "CImfRes::GetNumMotion");
int CImfRes::GetNumMotion(int NumLayer, int NumAction) // line 147
{
	return (this->*_GetNumMotion)(NumLayer, NumAction);

	return (int)m_ImfData[NumLayer][NumAction].m_cx.size();
}


hook_method<int (CImfRes::*)(int NumLayer)> CImfRes::_GetLongestMotion(SAKEXE, "CImfRes::GetLongestMotion");
int CImfRes::GetLongestMotion(int NumLayer) // line 152
{
	return (this->*_GetLongestMotion)(NumLayer);

	int longestMotioncount = 0;

	for( int actionId = 0; actionId < (int)m_ImfData[NumLayer].size(); ++actionId )
	{
		int motioncount = (int)m_ImfData[NumLayer][actionId].m_cx.size();
		if( longestMotioncount < motioncount )
			longestMotioncount = motioncount;
	}

	return longestMotioncount;
}


hook_method<int (CImfRes::*)(int Priority, int Act, int Mot)> CImfRes::_GetLayer(SAKEXE, "CImfRes::GetLayer");
int CImfRes::GetLayer(int Priority, int Act, int Mot) // line 163
{
	return (this->*_GetLayer)(Priority, Act, Mot);

	if( Act >= m_maxAction[Priority] )
		return -1;

	if( Mot >= m_maxMotion[Priority][Act] )
		return -1;

	for( int layerId = 0; layerId < (int)m_ImfData.size(); ++layerId )
		if( m_ImfData[layerId][Act].m_Priority[Mot] == Priority )
			return layerId;

	return -1;
}


hook_method<int (CImfRes::*)(int Layer, int Act, int Mot)> CImfRes::_GetPriority(SAKEXE, "CImfRes::GetPriority");
int CImfRes::GetPriority(int Layer, int Act, int Mot) // line 189
{
	return (this->*_GetPriority)(Layer, Act, Mot);

	return m_ImfData[Layer][Act].m_Priority[Mot];
}


hook_method<POINT (CImfRes::*)(int Layer, int Act, int Mot)> CImfRes::_GetPoint(SAKEXE, "CImfRes::GetPoint");
POINT CImfRes::GetPoint(int Layer, int Act, int Mot) // line 194
{
	return (this->*_GetPoint)(Layer, Act, Mot);

	POINT point;
	point.x = m_ImfData[Layer][Act].m_cx[Mot];
	point.y = m_ImfData[Layer][Act].m_cy[Mot];
	return point;
}
