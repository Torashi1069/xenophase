#pragma once
#include "Resource/Bitmap.h"


class CEmblemRes : public CRes
{
	struct vtable_t
	{
		void* (CEmblemRes::* scalar_deleting_destructor)(unsigned int flags);
		bool (CRes::* LoadFromBuffer)(const char* fName, const unsigned char* buffer, int size);
		CRes* (CEmblemRes::* Clone)(void) const;
		bool (CEmblemRes::* Load)(const char* fName);
		void (CEmblemRes::* Reset)(void);
		void (CEmblemRes::* OnLoadError)(const char* fName);
	};

	/* this+  0 */ public: //CRes baseclass_0;
	/* this+272 */ private: CBitmapRes m_bitmap;

	public: CEmblemRes::CEmblemRes(Exemplar __formal, const char* resid, const char* baseDir);
	public: CEmblemRes::CEmblemRes(void);
	public: virtual CRes* CEmblemRes::Clone(void) const;
	public: virtual bool CEmblemRes::Load(const char* fName);
	public: virtual void CEmblemRes::Reset(void);
	public: CBitmapRes* CEmblemRes::GetBitmap(void);
	private: bool CEmblemRes::UnCompressEmblem(unsigned char* bitmap, unsigned long& bitmapSize, unsigned char* emblem, int emSize);
	private: virtual void CEmblemRes::OnLoadError(const char* fName);

private:
	static hook_method<CRes* (CEmblemRes::*)(void) const> CEmblemRes::_Clone;
	static hook_method<bool (CEmblemRes::*)(const char* fName)> CEmblemRes::_Load;
	static hook_method<void (CEmblemRes::*)(void)> CEmblemRes::_Reset;
	static hook_method<CBitmapRes* (CEmblemRes::*)(void)> CEmblemRes::_GetBitmap;
	static hook_method<bool (CEmblemRes::*)(unsigned char* bitmap, unsigned long& bitmapSize, unsigned char* emblem, int emSize)> CEmblemRes::_UnCompressEmblem;
	static hook_method<void (CEmblemRes::*)(const char* fName)> CEmblemRes::_OnLoadError;
};
