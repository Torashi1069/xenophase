#pragma once
#include "Base/Res.h"


struct ImfData
{
	/* this+ 0 */ mystd::vector<int> m_Priority;
	/* this+16 */ mystd::vector<int> m_cx;
	/* this+32 */ mystd::vector<int> m_cy;
};


class CImfRes : public CRes
{
	struct vtable_t
	{
		void* (CImfRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (CImfRes::* Clone)(void) const;
		bool (CImfRes::* Load)(const char* fName);
		void (CRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ protected: mystd::vector< mystd::vector<ImfData> > m_ImfData;
	/* this+288 */ protected: int m_maxAction[15];
	/* this+348 */ protected: int m_maxMotion[15][104];

	public: CImfRes::CImfRes(Exemplar __formal, const char* resid, const char* baseDir);
	public: CImfRes::CImfRes(void);
	public: virtual CRes* CImfRes::Clone(void) const;
	public: virtual bool CImfRes::Load(const char* fName);
	public: void CImfRes::Create(void);
	public: int CImfRes::CheckSum(int MaxLayer);
	public: int CImfRes::GetNumLayer(void);
	public: int CImfRes::GetNumAction(int NumLayer);
	public: int CImfRes::GetNumMotion(int NumLayer, int NumAction);
	public: int CImfRes::GetLongestMotion(int NumLayer);
	public: int CImfRes::GetLayer(int Priority, int Act, int Mot);
	public: int CImfRes::GetPriority(int Layer, int Act, int Mot);
	public: POINT CImfRes::GetPoint(int Layer, int Act, int Mot);

private:
	static hook_method<CRes* (CImfRes::*)(void) const> CImfRes::_Clone;
	static hook_method<void (CImfRes::*)(void)> CImfRes::_Create;
	static hook_method<bool (CImfRes::*)(const char* fName)> CImfRes::_Load;
	static hook_method<int (CImfRes::*)(int MaxLayer)> CImfRes::_CheckSum;
	static hook_method<int (CImfRes::*)(void)> CImfRes::_GetNumLayer;
	static hook_method<int (CImfRes::*)(int NumLayer)> CImfRes::_GetNumAction;
	static hook_method<int (CImfRes::*)(int NumLayer, int NumAction)> CImfRes::_GetNumMotion;
	static hook_method<int (CImfRes::*)(int NumLayer)> CImfRes::_GetLongestMotion;
	static hook_method<int (CImfRes::*)(int Priority, int Act, int Mot)> CImfRes::_GetLayer;
	static hook_method<int (CImfRes::*)(int Layer, int Act, int Mot)> CImfRes::_GetPriority;
	static hook_method<POINT (CImfRes::*)(int Layer, int Act, int Mot)> CImfRes::_GetPoint;
};
