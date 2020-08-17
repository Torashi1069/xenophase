#include "WndProc.h"
#include "Patcher.h"
#include "patchclient.h" // PMC_*
#include "resource.h" // ID*
#include <commctrl.h> // PBM_*
#include <platform/stdc.h> // vsnprintf()
#include <platform/macro.h> // countof()
////////////////////////////////////////


#define PMC_SETNOTICE 15000
#define PMC_SETSTATUS 15001
#define PMC_SETPROGRESS 15002
#define PMC_PERMITSTART 15003
#define PMC_DENYSTART 15004
#define PMC_SETSTATUSFOOT 15005
#define PMC_SETDLTIMELEFT 15006
#define PMC_SETDLSPEED 15007

#define PMC_PERMITEXIT 15100
#define PMC_DENYEXIT 15101
#define PMC_SHOWABOUT 15055

WNDPROC g_wndpStatic = NULL;
WNDPROC g_vwndpStatic = NULL;
HWND g_MainhWnd = NULL;
HINSTANCE g_hInstance = NULL;
HANDLE g_WorkerThread = NULL;
bool g_bExitAllowed = true;


////////////////////////////////////////


void pmc_setprogress(unsigned int progress)
{
	SendMessage(g_MainhWnd, WM_COMMAND, PMC_SETPROGRESS, (LPARAM)progress);
}


void pmc_setnotice(const char* notice)
{
	SendMessage(g_MainhWnd, WM_COMMAND, PMC_SETNOTICE, (LPARAM)notice);	
}


void pmc_setstatusmsg(const char* format, ...)
{
	char buf[256];
	va_list args;
	va_start(args, format);
	vsnprintf(buf, countof(buf), format, args);
	va_end(args);

	SendMessage(g_MainhWnd, WM_COMMAND, PMC_SETSTATUS, (LPARAM)&buf);	
}


void pmc_setstatusfootmsg(const char* format, ...)
{
	char buf[256];
	va_list args;
	va_start(args, format);
	vsnprintf(buf, countof(buf), format, args);
	va_end(args);

	SendMessage(g_MainhWnd, WM_COMMAND, PMC_SETSTATUSFOOT, (LPARAM)&buf);	
}


void pmc_setdltimeleft(const char* format, ...)
{
	char buf[256];
	va_list args;
	va_start(args, format);
	vsnprintf(buf, countof(buf), format, args);
	va_end(args);

	SendMessage(g_MainhWnd, WM_COMMAND, PMC_SETDLTIMELEFT, (LPARAM)&buf);	
}


void pmc_setdlspeed(const char* format, ...)
{
	char buf[256];
	va_list args;
	va_start(args, format);
	vsnprintf(buf, countof(buf), format, args);
	va_end(args);

	SendMessage(g_MainhWnd, WM_COMMAND, PMC_SETDLSPEED, (LPARAM)&buf);	
}


void pmc_permitstart(void)
{
	SendMessage(g_MainhWnd, WM_COMMAND, PMC_PERMITSTART, 0);
}


void pmc_denystart(void)
{
	SendMessage(g_MainhWnd, WM_COMMAND, PMC_DENYSTART, 0);
}


void pmc_permitexit(void)
{
	SendMessage(g_MainhWnd, WM_COMMAND, PMC_PERMITEXIT, 0);
}


void pmc_denyexit(void)
{
	SendMessage(g_MainhWnd, WM_COMMAND, PMC_DENYEXIT, 0);
}


void pmc_exit(void)
{
	SendMessage(g_MainhWnd, WM_DESTROY, 0, 0);
}


////////////////////////////////////////


DWORD WINAPI Worker(LPVOID data)
{
	Patcher p;
	p.Run();
	return 0;
}


// Mesage handler for our main window
LRESULT CALLBACK PCMain(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HFONT hFont = NULL; // for PMC_SHOWHEADURL
	static HFONT vhFont = NULL; // for PMC_SHOWVOTELINK

	switch( message )
	{
		case WM_INITDIALOG:
		{
			g_MainhWnd = hWnd;
			g_hInstance = (HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE);

			SendMessage(hWnd, WM_SETTEXT, NULL, (LPARAM)PMC_TITLE);

			if( PMC_ADDABOUTWINDOW ) {
			HMENU hSysMenu = GetSystemMenu(hWnd, FALSE);
			InsertMenu (hSysMenu, 2, MF_SEPARATOR, 0, NULL);
			AppendMenu(hSysMenu, 0, PMC_SHOWABOUT, "About");
			} //PMC_ADDABOUTWINDOW

			HICON hIcon = LoadIcon(g_hInstance, (LPCTSTR)IDI_PATCHCLIENT);
			if( hIcon != NULL ) {
				SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
				SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			} else {
				MessageBox(NULL, "ICON FAIL?!", "..", NULL);
			}

			if( PMC_SHOWHEADURL ) {
			hFont = (HFONT)SendDlgItemMessage(hWnd, IDC_YRABOUT, WM_GETFONT, 0, 0);
			if(hFont == NULL)
				hFont = (HFONT)GetStockObject(SYSTEM_FONT);

			SetDlgItemText(hWnd, IDC_YRABOUT, PMC_HEADURLTEXT);

			LOGFONT lf;
			GetObject((HGDIOBJ)hFont, sizeof(lf), &lf);
			lf.lfUnderline = TRUE;
			hFont = CreateFontIndirect(&lf);
			SendDlgItemMessage(hWnd, IDC_YRABOUT, WM_SETFONT, (WPARAM)hFont, (LPARAM)TRUE);

			g_wndpStatic = (WNDPROC)SetWindowLong(GetDlgItem(hWnd, IDC_YRABOUT), -4, (long)UrlProc);
			} //PMC_SHOWHEADURL

			if( PMC_SHOWVOTELINK ) {
			vhFont = (HFONT)SendDlgItemMessage(hWnd, IDC_VOTELINK, WM_GETFONT, 0, 0);
			if(vhFont == NULL)
				vhFont = (HFONT)GetStockObject(SYSTEM_FONT);

			SetDlgItemText(hWnd, IDC_VOTELINK, PMC_VOTELINKTEXT);

			LOGFONT vf;
			GetObject((HGDIOBJ)vhFont, sizeof(vf), &vf);
			vf.lfUnderline = TRUE;
			vhFont = CreateFontIndirect(&vf);
			SendDlgItemMessage(hWnd, IDC_VOTELINK, WM_SETFONT, (WPARAM)vhFont, (LPARAM)TRUE);

			g_vwndpStatic = (WNDPROC)SetWindowLong(GetDlgItem(hWnd, IDC_VOTELINK), -4, (long)UrlProcVote);
			} //PMC_SHOWVOTELINK

			//StatusBar Initialize - 0 - 100 %!
			SendDlgItemMessage(hWnd, IDC_PROGRESS, PBM_SETRANGE, 0, MAKELPARAM(0,100));
			SendDlgItemMessage(hWnd, IDC_PROGRESS, PBM_SETSTEP, 1, 0);
			SendDlgItemMessage(hWnd, IDC_PROGRESS, PBM_SETPOS, 0, 0);

			//Window text on buttons etc initialize!
			SetDlgItemText(hWnd, IDC_HEADER, PMC_HEADLINE); //Headline
			SetDlgItemText(hWnd, IDC_NOTICE, PMC_NOTICE_BLANK); //The contents of editbox for patch Notice at the start ..
			SetDlgItemText(hWnd, IDC_STATUSTEXT, PMC_STATUS_BLANK); //The content of 'status text'
			SetDlgItemText(hWnd, IDC_START, PMC_SGBUTTON); //Text of the 'Start Game' button
			SetDlgItemText(hWnd, IDC_EXIT, PMC_EXITBUTTON); //Text of the 'Exit' button

			//Start Game button to clear!
			EnableWindow(GetDlgItem(hWnd, IDC_START), FALSE);

			g_WorkerThread = CreateThread(NULL, 0, &Worker, NULL, 0, NULL);

			ShowWindow(hWnd, TRUE);
			UpdateWindow(hWnd);
			return TRUE;
		}
		break;
		case WM_NCDESTROY:
		{
			if( hFont != NULL )
				DeleteObject((HGDIOBJ)hFont);

			if( vhFont != NULL )
				DeleteObject((HGDIOBJ)vhFont);
		}
		break;
		case WM_CTLCOLORSTATIC:
		{
			if( GetDlgItem(hWnd, IDC_YRABOUT) == (HWND)lParam )
			{
				SetTextColor((HDC)wParam, GetSysColor(COLOR_HIGHLIGHT));
				SetBkMode((HDC)wParam, TRANSPARENT);
				return (BOOL)GetStockObject(NULL_BRUSH);
			}

			if( GetDlgItem(hWnd, IDC_VOTELINK) == (HWND)lParam )
			{
				SetTextColor((HDC)wParam, GetSysColor(COLOR_HIGHLIGHT));
				SetBkMode((HDC)wParam, TRANSPARENT);
				return (BOOL)GetStockObject(NULL_BRUSH);
			}
		}
		break;
		case WM_SYSCOMMAND:
		{
			if( wParam == PMC_SHOWABOUT )
				DialogBox(g_hInstance, (LPCTSTR)IDD_ABOUTBOX, NULL, (DLGPROC)&AboutMain);
		}
		break;
		case WM_COMMAND:
		{
			if( LOWORD(wParam) == IDC_EXIT || LOWORD(wParam) == IDCANCEL ) 
			{
				if( !g_bExitAllowed )
					return TRUE;

				PostQuitMessage(0);
				return TRUE;
			}

			if( LOWORD(wParam) == IDC_START )
			{
				char cmdline[] = PMC_GAMEEXE;
				STARTUPINFOA si = { sizeof(si), 0 };
				PROCESS_INFORMATION pi = { 0 };
				if( CreateProcessA(NULL, cmdline, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == 0 )
				{// failed, display error
					pmc_setstatusmsg("Failed to start Ragnarok");
				}
				else
				{// success, shut down
					PostQuitMessage(0);
				}
			}

			if(LOWORD(wParam) == IDC_YRABOUT)
			{
				if(HIWORD(wParam) == STN_CLICKED)
					ShellExecute(hWnd, NULL, TEXT(PMC_HEADURL),NULL, NULL, SW_SHOW);
			}

			if(LOWORD(wParam) == IDC_VOTELINK)
			{
				if(HIWORD(wParam) == STN_CLICKED)
					ShellExecute(hWnd, NULL, TEXT(PMC_VOTELINK),NULL, NULL, SW_SHOW);
			}

			switch( wParam )
			{
			case PMC_SETNOTICE: //pointer (address) to notice in lParam
				SetDlgItemText(hWnd, IDC_NOTICE, (const char*)lParam);
			break;
			case PMC_SETSTATUS:
				SetDlgItemText(hWnd, IDC_STATUSTEXT, (const char*)lParam);
			break;
			case PMC_SETSTATUSFOOT:
				SetDlgItemText(hWnd, IDC_STATUSFOOT, (const char*)lParam);
			break;
			case PMC_SETPROGRESS:
				SendDlgItemMessage(hWnd, IDC_PROGRESS, PBM_SETPOS, lParam, 0);
			break;
			case PMC_PERMITSTART:
				EnableWindow(GetDlgItem(hWnd, IDC_START), TRUE);
				SendMessage(hWnd, DM_SETDEFID, IDC_START, NULL); //default setzen
				SetFocus(GetDlgItem(hWnd, IDC_START));
			break;
			case PMC_PERMITEXIT:
				g_bExitAllowed = true;
				EnableWindow(GetDlgItem(hWnd, IDC_EXIT), TRUE);
			break;
			case PMC_DENYEXIT:
				g_bExitAllowed = false;
				EnableWindow(GetDlgItem(hWnd, IDC_EXIT), FALSE);
			break;
			case PMC_DENYSTART:
				EnableWindow(GetDlgItem(hWnd, IDC_START), FALSE);
			break;
			case PMC_SETDLTIMELEFT:
				SetDlgItemText(hWnd, IDC_DL_TIMELEFT, (const char*)lParam);
			break;
			case PMC_SETDLSPEED:
				SetDlgItemText(hWnd, IDC_DL_SPEED, (const char*)lParam);
			break;
			}
		}
		break;
		case WM_DESTROY:
		{
			if( g_WorkerThread != NULL )
				TerminateThread(g_WorkerThread, 0);

			PostQuitMessage(0);
		}
		break;
	}

	return FALSE;
}


////////////////////////////////////////


// Mesage handler for about box.
LRESULT CALLBACK AboutMain(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch( message )
	{
		case WM_INITDIALOG:					
		{
			HICON hIcon = LoadIcon(g_hInstance, (LPCTSTR)IDI_PATCHCLIENT);
			if( hIcon )
			{
				SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
				SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			}
			SetDlgItemText(hDlg, IDC_ABB_BUILDON, PMC_BUILDON_STR);
			return TRUE;
		}
		break;
		case WM_COMMAND:
		{
			if( LOWORD(wParam) == IDC_ABB_OK )
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
		}
		break;
	}

	return FALSE;
}


////////////////////////////////////////


//Handler für die URL (about)
LRESULT CALLBACK UrlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch( uMsg )
	{
		case WM_SETCURSOR:
			SetCursor(LoadCursor(NULL, IDC_HAND));
			return TRUE;
		break;
	}

	return CallWindowProc(g_wndpStatic, hWnd, uMsg, wParam, lParam);
}


////////////////////////////////////////


//Handler für die URL (Vote)
LRESULT CALLBACK UrlProcVote(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch( uMsg )
	{
		case WM_SETCURSOR:
			SetCursor(LoadCursor(NULL, IDC_HAND));
			return TRUE;
		break;
	}

	return CallWindowProc(g_vwndpStatic, hWnd, uMsg, wParam, lParam);
}


////////////////////////////////////////
