#pragma once


bool __cdecl IsEnableOldKeycrypt(void);
bool __cdecl IsEnableNewKeycrypt(void);
int __cdecl ProcessFindHack1(void);
int __cdecl ProcessFindHack2(void);
void __cdecl DeleteHack(void);
int __cdecl NpKeyMyLoadLibrary(void);
void __cdecl WinMainNpKeyStartEncryption(void);
void __cdecl WinMainNpKeyStopEncryption(void);
void __cdecl CloseKeyCrypt(void);
int __cdecl NKCStartKeycrypt(void);


extern int  (__cdecl*& MyGetIMEHangulMode)(void *);
extern int  (__cdecl*& MyGetAthKbdObject)(char *);
extern int  (__cdecl*& MyGetInitError)(void);
extern int  (__cdecl*& MyLoadKindDriver)(void);
extern int  (__cdecl*& MyCheckReg)(void);
extern void (__cdecl*& MyUninstallReg)(void);
extern void (__cdecl*& MyInstallReg)(void);
extern int  (__cdecl*& MyInitReg)(void);
extern void (__cdecl*& MyRegisterHWNDForEdit)(unsigned long, void *);
extern int  (__cdecl*& MyGetCryptData)(unsigned char *);
extern int  (__cdecl*& MyCloseDriver)(void);
extern int  (__cdecl*& MyStopEncryption)(void);
extern int  (__cdecl*& MyStartEncryption)(void);
extern int  (__cdecl*& MyInitialize)(void);
