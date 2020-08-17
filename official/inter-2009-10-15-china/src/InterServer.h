#pragma once


int __cdecl InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
void __cdecl CleanUp(void);
bool __cdecl StartUp(void);
void __cdecl OnPaintMode0(HWND hWnd);
void __cdecl OnPaintMode1(HWND hWnd);
void __cdecl OnPaintMode2(HWND hWnd);
