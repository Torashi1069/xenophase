#pragma once


extern class CFileMgr& g_fileMgr;
extern class CPacketLengthExMgr& g_packetLenMapEx;

extern HWND& g_hMainWnd;
extern char(& g_baseDir)[128];
extern char(& g_baseDir3)[128];
extern bool& g_readFolderFirst;


// global functions
void Trace(const char* str, ...);
void ErrorMsg(const char* msg);
void ErrorMsg(int msg);
