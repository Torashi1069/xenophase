#include "patchclient.h"
#include "resource.h" // IDC_PATCHCLIENT
#include "wndproc.h" // PCMain()
#include <commctrl.h> // InitCommonControls()


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//Check for Multiple instances on one computer running the same time
	HANDLE hAppMutex = CreateMutex(NULL, FALSE, "RagPatchClient");
	if( hAppMutex == NULL )
		exit(0);

	InitCommonControls();

	DialogBox(hInstance, (LPCTSTR)IDD_PC_MAINWINDOW, NULL, (DLGPROC)&PCMain);

	// Main message loop:
	HACCEL hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_PATCHCLIENT);
	MSG msg;
	while( GetMessage(&msg, NULL, 0, 0) ) 
	{
		if( !TranslateAccelerator(msg.hwnd, hAccelTable, &msg) ) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	CloseHandle(hAppMutex);
	return msg.wParam;
}
