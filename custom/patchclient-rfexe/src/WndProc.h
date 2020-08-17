#pragma once
#include <windows.h>


void pmc_setprogress(unsigned int progress);
void pmc_setnotice(const char* notice);
void pmc_setstatusmsg(const char* format, ...);
void pmc_setstatusfootmsg(const char* format, ...);
void pmc_setdltimeleft(const char* format, ...);
void pmc_setdlspeed(const char* format, ...);
void pmc_permitstart(void);
void pmc_denystart(void);
void pmc_permitexit(void);
void pmc_denyexit(void);
void pmc_exit(void);


LRESULT CALLBACK PCMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK AboutMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK UrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK UrlProcVote(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
