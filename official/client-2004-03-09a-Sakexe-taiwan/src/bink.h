/// @custom
/// @version 1.9.3 (?)
#pragma once


struct BINKIO; // 20
typedef unsigned long (__stdcall* BINKIOREADHEADER)   (BINKIO* Bnkio, long Offset, void* Dest, unsigned long Size);
typedef unsigned long (__stdcall* BINKIOREADFRAME)    (BINKIO* Bnkio, unsigned long Framenum, long origofs, void* dest, unsigned long size);
typedef unsigned long (__stdcall* BINKIOGETBUFFERSIZE)(BINKIO* Bnkio, unsigned long Size);
typedef void          (__stdcall* BINKIOSETINFO)      (BINKIO* Bnkio, void* BUf, unsigned long Size, unsigned long FileSize, unsigned long simulate);
typedef unsigned long (__stdcall* BINKIOIDLE)         (BINKIO* Bnkio);
typedef void          (__stdcall* BINKIOCLOSE)        (BINKIO* Bnkio);


typedef void (__stdcall* BINKCBSUSPEND)    (BINKIO* Bnkio);
typedef long (__stdcall* BINKCBTRYSUSPEND) (BINKIO* Bnkio);
typedef void (__stdcall* BINKCBRESUME)     (BINKIO* Bnkio);
typedef void (__stdcall* BINKCBIDLE)       (BINKIO* Bnkio);


struct BINKIO // 35
{
	/* this+0x0  */ BINKIOREADHEADER ReadHeader;
	/* this+0x4  */ BINKIOREADFRAME ReadFrame;
	/* this+0x8  */ BINKIOGETBUFFERSIZE GetBufferSize;
	/* this+0xC  */ BINKIOSETINFO SetInfo;
	/* this+0x10 */ BINKIOIDLE Idle;
	/* this+0x14 */ BINKIOCLOSE Close;
	/* this+0x18 */ struct BINK* bink;
	/* this+0x1C */ volatile unsigned long ReadError;
	/* this+0x20 */ volatile unsigned long DoingARead;
	/* this+0x24 */ volatile unsigned long BytesRead;
	/* this+0x28 */ volatile unsigned long Working;
	/* this+0x2C */ volatile unsigned long TotalTime;
	/* this+0x30 */ volatile unsigned long ForegroundTime;
	/* this+0x34 */ volatile unsigned long IdleTime;
	/* this+0x38 */ volatile unsigned long ThreadTime;
	/* this+0x3C */ volatile unsigned long BufSize;
	/* this+0x40 */ volatile unsigned long BufHighUsed;
	/* this+0x44 */ volatile unsigned long CurBufSize;
	/* this+0x48 */ volatile unsigned long CurBufUsed;
	/* this+0x4C */ volatile unsigned char iodata[128+32];
	/* this+0xEC */ BINKCBSUSPEND suspend_callback;
	/* this+0xF0 */ BINKCBTRYSUSPEND try_suspend_callback;
	/* this+0xF4 */ BINKCBRESUME resume_callback;
	/* this+0xF8 */ BINKCBIDLE idle_on_callback;
	/* this+0xFC */ volatile unsigned long callback_control[16];
};


struct BINKSND; // 67
typedef long (__stdcall* BINKSNDREADY)(BINKSND* BnkSnd);
typedef long (__stdcall* BINKSNDLOCK)(BINKSND* BnkSnd, unsigned char** addr, unsigned long* len);
typedef long (__stdcall* BINKSNDUNLOCK)(BINKSND* BnkSnd, unsigned long filled);
typedef void (__stdcall* BINKSNDVOLUME)(BINKSND* BnkSnd, long volume);
typedef void (__stdcall* BINKSNDPAN)(BINKSND* BnkSnd, long pan);
typedef long (__stdcall* BINKSNDPAUSE)(BINKSND* BnkSnd, long status);
typedef long (__stdcall* BINKSNDONOFF)(BINKSND* BnkSnd, long status);
typedef void (__stdcall* BINKSNDCLOSE)(BINKSND* BnkSnd);
typedef void (__stdcall* BINKSNDMIXBINS)(BINKSND* BnkSnd, unsigned long* mix_bins, unsigned long total);
typedef void (__stdcall* BINKSNDMIXBINVOLS)(BINKSND* BnkSnd, unsigned long* vol_mix_bins, long* volumes, unsigned long total);


struct BINKSND // 82
{
	/* this+0x0  */ BINKSNDREADY Ready;
	/* this+0x4  */ BINKSNDLOCK Lock;
	/* this+0x8  */ BINKSNDUNLOCK Unlock;
	/* this+0xC  */ BINKSNDVOLUME Volume;
	/* this+0x10 */ BINKSNDPAN Pan;
	/* this+0x14 */ BINKSNDPAUSE Pause;
	/* this+0x18 */ BINKSNDONOFF SetOnOff;
	/* this+0x1C */ BINKSNDCLOSE Close;
	/* this+0x20 */ BINKSNDMIXBINS MixBins;
	/* this+0x24 */ BINKSNDMIXBINVOLS MixBinVols;
	/* this+0x28 */ unsigned longsndbufsize;
	/* this+0x2C */ unsigned char* sndbuf;
	/* this+0x30 */ unsigned char* sndend;
	/* this+0x34 */ unsigned char* sndwritepos;
	/* this+0x38 */ unsigned char* sndreadpos;
	/* this+0x3C */ unsigned long sndcomp;
	/* this+0x40 */ unsigned long sndamt;
	/* this+0x44 */ unsigned long sndconvert8;
	/* this+0x48 */ unsigned long sndendframe;
	/* this+0x4C */ unsigned long sndprime;
	/* this+0x50 */ unsigned long sndpad;
	/* this+0x54 */ unsigned long BestSizeIn16;
	/* this+0x58 */ unsigned long BestSizeMask;
	/* this+0x5C */ unsigned long SoundDroppedOut;
	/* this+0x60 */ long OnOff;
	/* this+0x64 */ unsigned long Latency;
	/* this+0x68 */ unsigned long VideoScale;
	/* this+0x6C */ unsigned long freq;
	/* this+0x70 */ long bits;
	/* this+0x74 */ long chans;
	/* this+0x78 */ unsigned char snddata[256];
};


struct BINKRECT // 137
{
	/* this+0x0 */ long Left;
	/* this+0x4 */ long Top;
	/* this+0x8 */ long Width;
	/* this+0xC */ long Height;
};


#define BINKMAXDIRTYRECTS 8 // 141


struct BUNDLEPOINTERS // 143
{
	/* this+0x0  */ void* typeptr;
	/* this+0x4  */ void* type16ptr;
	/* this+0x8  */ void* colorptr;
	/* this+0xC  */ void* bits2ptr;
	/* this+0x10 */ void* motionXptr;
	/* this+0x14 */ void* motionYptr;
	/* this+0x18 */ void* dctptr;
	/* this+0x1C */ void* mdctptr;
	/* this+0x20 */ void* patptr;
};


struct BINK // 184
{
	/* this+0x0   */ unsigned long Width;
	/* this+0x4   */ unsigned long Height;
	/* this+0x8   */ unsigned long Frames;
	/* this+0xC   */ unsigned long FrameNum;
	/* this+0x10  */ unsigned long LastFrameNum;
	/* this+0x14  */ unsigned long FrameRate;
	/* this+0x18  */ unsigned long FrameRateDiv;
	/* this+0x1C  */ unsigned long ReadError;
	/* this+0x20  */ unsigned long OpenFlags;
	/* this+0x24  */ unsigned long BinkType;
	/* this+0x28  */ unsigned long Size;
	/* this+0x2C  */ unsigned long FrameSize;
	/* this+0x30  */ unsigned long SndSize;
	/* this+0x34  */ struct BINKRECT FrameRects[BINKMAXDIRTYRECTS];
	/* this+0xB4  */ long NumRects;
	/* this+0xB8  */ unsigned long PlaneNum;
	/* this+0xBC  */ void* YPlane[2];
	/* this+0xC4  */ void* APlane[2];
	/* this+0xCC  */ unsigned long YWidth;
	/* this+0xD0  */ unsigned long YHeight;
	/* this+0xD4  */ unsigned long UVWidth;
	/* this+0xD8  */ unsigned long UVHeight;
	/* this+0xDC  */ void* MaskPlane;
	/* this+0xE0  */ unsigned long MaskPitch;
	/* this+0xE4  */ unsigned long MaskLength;
	/* this+0xE8  */ unsigned long LargestFrameSize;
	/* this+0xEC  */ unsigned long InternalFrames;
	/* this+0xF0  */ long NumTracks;
	/* this+0xF4  */ unsigned long Highest1SecRate;
	/* this+0xF8  */ unsigned long Highest1SecFrame;
	/* this+0xFC  */ long Paused;
	/* this+0x100 */ unsigned long BackgroundThread;
	/* this+0x104 */ void* compframe;
	/* this+0x108 */ void* preloadptr;
	/* this+0x10C */ unsigned long* frameoffsets;
	/* this+0x110 */ struct BINKIO bio;
	/* this+0x24C */ unsigned char* ioptr;
	/* this+0x250 */ unsigned long iosize;
	/* this+0x254 */ unsigned long decompwidth;
	/* this+0x258 */ unsigned long decompheight;
	/* this+0x25C */ long* trackindexes;
	/* this+0x260 */ unsigned long * tracksizes;
	/* this+0x264 */ unsigned long * tracktypes;
	/* this+0x268 */ long* trackIDs;
	/* this+0x26C */ unsigned long numrects;
	/* this+0x270 */ unsigned long playedframes;
	/* this+0x274 */ unsigned long firstframetime;
	/* this+0x278 */ unsigned long startframetime;
	/* this+0x27C */ unsigned long startblittime;
	/* this+0x280 */ unsigned long startsynctime;
	/* this+0x284 */ unsigned long startsyncframe;
	/* this+0x288 */ unsigned long twoframestime;
	/* this+0x28C */ unsigned long entireframetime;
	/* this+0x290 */ unsigned long slowestframetime;
	/* this+0x294 */ unsigned long slowestframe;
	/* this+0x298 */ unsigned long slowest2frametime;
	/* this+0x29C */ unsigned long slowest2frame;
	/* this+0x2A0 */ unsigned long soundon;
	/* this+0x2A4 */ unsigned long videoon;
	/* this+0x2A8 */ unsigned long totalmem;
	/* this+0x2AC */ unsigned long timevdecomp;
	/* this+0x2B0 */ unsigned long timeadecomp;
	/* this+0x2B4 */ unsigned long timeblit;
	/* this+0x2B8 */ unsigned long timeopen;
	/* this+0x2BC */ unsigned long fileframerate;
	/* this+0x2C0 */ unsigned long fileframeratediv;
	/* this+0x2C4 */ unsigned long runtimeframes;
	/* this+0x2C8 */ unsigned long runtimemoveamt;
	/* this+0x2CC */ unsigned long* rtframetimes;
	/* this+0x2D0 */ unsigned long* rtadecomptimes;
	/* this+0x2D4 */ unsigned long* rtvdecomptimes;
	/* this+0x2D8 */ unsigned long* rtblittimes;
	/* this+0x2DC */ unsigned long* rtreadtimes;
	/* this+0x2E0 */ unsigned long* rtidlereadtimes;
	/* this+0x2E4 */ unsigned long* rtthreadreadtimes;
	/* this+0x2E8 */ unsigned long lastblitflags;
	/* this+0x2EC */ unsigned long lastdecompframe;
	/* this+0x2F0 */ unsigned long playingtracks;
	/* this+0x2F4 */ unsigned long soundskips;
	/* this+0x2F8 */ struct BINKSND* bsnd;
	/* this+0x2FC */ unsigned long skippedlastblit;
	/* this+0x300 */ unsigned long skipped_this_frame;
	/* this+0x304 */ unsigned long skippedblits;
	/* this+0x308 */ struct BUNDLEPOINTERS bunp;
	/* this+0x32C */ unsigned long skipped_in_a_row;
	/* this+0x330 */ unsigned long big_sound_skip_adj;
	/* this+0x334 */ unsigned long big_sound_skip_reduce;
	/* this+0x338 */ unsigned long last_time_almost_empty;
	/* this+0x33C */ unsigned long last_read_count;
	/* this+0x340 */ unsigned long last_sound_count;
	/* this+0x344 */ unsigned long snd_callback_buffer[16];
};


struct BINKBUFFER // 726
{
	/* this+0x0  */ unsigned long Width;
	/* this+0x4  */ unsigned long Height;
	/* this+0x8  */ unsigned long WindowWidth;
	/* this+0xC  */ unsigned long WindowHeight;
	/* this+0x10 */ unsigned long SurfaceType;
	/* this+0x14 */ void* Buffer;
	/* this+0x18 */ long BufferPitch;
	/* this+0x1C */ long ClientOffsetX;
	/* this+0x20 */ long ClientOffsetY;
	/* this+0x24 */ unsigned long ScreenWidth;
	/* this+0x28 */ unsigned long ScreenHeight;
	/* this+0x2C */ unsigned long ScreenDepth;
	/* this+0x30 */ unsigned long ExtraWindowWidth;
	/* this+0x34 */ unsigned long ExtraWindowHeight;
	/* this+0x38 */ unsigned long ScaleFlags;
	/* this+0x3C */ unsigned long StretchWidth;
	/* this+0x40 */ unsigned long StretchHeight;
	/* this+0x44 */ long surface;
	/* this+0x48 */ void* ddsurface;
	/* this+0x4C */ void* ddclipper;
	/* this+0x50 */ long destx;
	/* this+0x54 */ long desty;
	/* this+0x58 */ long wndx;
	/* this+0x5C */ long wndy;
	/* this+0x60 */ unsigned long wnd;
	/* this+0x64 */ long ddoverlay;
	/* this+0x68 */ long ddoffscreen;
	/* this+0x6C */ long lastovershow;
	/* this+0x70 */ long issoftcur;
	/* this+0x74 */ unsigned long cursorcount;
	/* this+0x78 */ void* buffertop;
	/* this+0x7C */ unsigned long type;
	/* this+0x80 */ long noclipping;
	/* this+0x84 */ long loadeddd;
	/* this+0x88 */ long loadedwin;
	/* this+0x8C */ void* dibh;
	/* this+0x90 */ void* dibbuffer;
	/* this+0x94 */ long dibpitch;
	/* this+0x98 */ void* dibinfo;
	/* this+0x9C */ unsigned long dibdc;
	/* this+0xA0 */ unsigned long diboldbitmap;
};
