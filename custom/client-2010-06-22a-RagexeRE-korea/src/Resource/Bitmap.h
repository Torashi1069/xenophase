#pragma once
#include "Base/Res.h"


class CBitmapRes : public CRes
{
public:
	/* this+  0 */ //CRes baseclass_0;
	/* this+272 */ BOOL m_isAlpha;
	/* this+276 */ int m_width;
	/* this+280 */ int m_height;
	/* this+284 */ unsigned long* m_data;
	/* this+288 */ unsigned long* m_data2;

public:
	CBitmapRes();
	CBitmapRes(class Exemplar __formal, const char* resid, const char* baseDir);
	virtual ~CBitmapRes();
	virtual bool CBitmapRes::LoadFromBuffer(const char* fName, const char* buffer, int size);
	virtual CRes* CBitmapRes::Clone(void);
	virtual bool CBitmapRes::Load(const char* fName);
	virtual void CBitmapRes::Reset(void);

	void sub_4257C0_deldata2();
	bool sub_4257F0(int a2);

private:
	bool CBitmapRes::LoadBMPData(const char* bitmap, int size);
	bool CBitmapRes::LoadTGAData(const char* bitmap, int size);
	bool CBitmapRes::LoadJPGData(const char* bitmap, int size);

public:
	static hook_func<bool (CBitmapRes::*)(const char* fName)> CBitmapRes::_Load;
	static hook_func<bool (CBitmapRes::*)(const char* fName, const char* buffer, int size)> CBitmapRes::_LoadFromBuffer;
	static hook_func<CRes* (CBitmapRes::*)(void)> CBitmapRes::_Clone;
	static hook_func<void (CBitmapRes::*)(void)> CBitmapRes::_Reset;
	static hook_func<bool (CBitmapRes::*)(int a2)> CBitmapRes::_sub_4257F0;
	static hook_func<bool (CBitmapRes::*)(const char* bitmap, int size)> CBitmapRes::_LoadBMPData;
	static hook_func<bool (CBitmapRes::*)(const char* bitmap, int size)> CBitmapRes::_LoadTGAData;
	static hook_func<bool (CBitmapRes::*)(const char* bitmap, int size)> CBitmapRes::_LoadJPGData;
};
C_ASSERT( sizeof CBitmapRes == 292 );


struct CBitmapResVtbl
{
	void* (CBitmapRes::* scalar_deleting_destructor)(unsigned int __flags);
	bool (CBitmapRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
	CRes* (CBitmapRes::* Clone)(void);
	bool (CBitmapRes::* Load)(const char* fName);
	void (CBitmapRes::* Reset)(void);
	void (CRes::* OnLoadError)(const char* fName);
};
