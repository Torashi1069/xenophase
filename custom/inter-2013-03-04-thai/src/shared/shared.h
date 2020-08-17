#pragma once


extern void(*& Trace)(const char* str, ...); //TODO
void TraceO(const char* str, ...);
void TraceF(const char* str, ...);
void TraceN(const char* str, ...);
void Decrypt(const char* encBuf, unsigned char* decBuf);
void InitializeSharedLib(BOOL isInstallFilter, int logOption);
