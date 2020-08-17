#pragma once
#include "Base/Res.h"


class CBitmapRes : public CRes
{
	struct vtable_t // const CBitmapRes::`vftable'
	{
		void* (CBitmapRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CBitmapRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (CBitmapRes::* Clone)(void) const;
		bool (CBitmapRes::* Load)(const char* fName);
		void (CBitmapRes::* Reset)(void);
		void (CRes::* OnLoadError)(const char* fName);
	};

	/* this+  0 */ public: //CRes baseclaas_0;
	/* this+272 */ public: int m_isAlpha;
	/* this+276 */ public: int m_width;
	/* this+280 */ public: int m_height;
	/* this+284 */ public: unsigned long* m_data;

	public: CBitmapRes::CBitmapRes(Exemplar __formal, const char* resid, const char* baseDir);
	public: CBitmapRes::CBitmapRes(void);
	public: virtual CRes* CBitmapRes::Clone(void) const;
	public: virtual bool CBitmapRes::Load(const char* fName);
	public: virtual bool CBitmapRes::LoadFromBuffer(const char* fName, const unsigned char* buffer, int size);
	public: virtual void CBitmapRes::Reset(void);
	public: unsigned long CBitmapRes::GetColor(int x, int y);
	public: bool CBitmapRes::SetAlphaWithBMP(const char* fName);
	public: void CBitmapRes::CreateNull(int x, int y);
	private: bool CBitmapRes::LoadBMPData(const unsigned char* bitmap, int size);
	private: bool CBitmapRes::LoadTGAData(const unsigned char* bitmap, int size);
	private: bool CBitmapRes::LoadJPGData(const unsigned char* bitmap, int size);

private:
	static hook_method<CRes* (CBitmapRes::*)(void) const> CBitmapRes::_Clone;
	static hook_method<bool (CBitmapRes::*)(const char* fName)> CBitmapRes::_Load;
	static hook_method<bool (CBitmapRes::*)(const char* fName, const unsigned char* buffer, int size)> CBitmapRes::_LoadFromBuffer;
	static hook_method<void (CBitmapRes::*)(void)> CBitmapRes::_Reset;
	static hook_method<unsigned long (CBitmapRes::*)(int x, int y)> CBitmapRes::_GetColor;
	static hook_method<bool (CBitmapRes::*)(const char* fName)> CBitmapRes::_SetAlphaWithBMP;
	static hook_method<void (CBitmapRes::*)(int x, int y)> CBitmapRes::_CreateNull;
	static hook_method<bool (CBitmapRes::*)(const unsigned char* bitmap, int size)> CBitmapRes::_LoadBMPData;
	static hook_method<bool (CBitmapRes::*)(const unsigned char* bitmap, int size)> CBitmapRes::_LoadTGAData;
	static hook_method<bool (CBitmapRes::*)(const unsigned char* bitmap, int size)> CBitmapRes::_LoadJPGData;
};
