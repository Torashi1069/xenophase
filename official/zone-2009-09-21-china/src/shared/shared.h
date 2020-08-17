#pragma once


extern hook_val<void(__cdecl *)(char const *,...)> Trace;
void __cdecl TraceO(const char* str, ...);
void __cdecl TraceF(const char* str, ...);
void __cdecl TraceN(const char* str, ...);
