#pragma once

#define OnLoadFile 1
#define OnSaveFile 2
#define AboutUs 3
#define OnExitSoftware 4

#define TextBufferSize 256

char Buffer[TextBufferSize];

HWND hEditControl;

LRESULT CALLBACK SoftwareMainProcedure(HWND Hwnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void MainWndAddMenus(HWND hWnd);
void MainWndAddText(HWND hWnd);
void SaveData(LPCSTR path);
void LoadData(LPCSTR path);
void SetOpenFileParams(HWND hWnd);

char filename[256];
OPENFILENAMEA ofn;