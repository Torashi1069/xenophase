#pragma once


extern void(*& Trace)(const char* str, ...); //TODO
void Decrypt(const char* encBuf, unsigned char* decBuf);
void InitializeSharedLib(BOOL isInstallFilter, int logOption);
short GetThirdJobGroup(short job);
