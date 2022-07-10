#pragma once

#define OnMenuAction1 1
#define OnMenuAction2 2
#define OnMenuAction3 3
#define OnMenuAction4 4
#define OnButtonClick1 5
#define OnButtonClick2 6
#define OnExitSoftware 7

LRESULT CALLBACK SoftwareMainProcedure(HWND Hwnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);

void MainWndAddMenus(HWND hWnd);
void MainWndAddText(HWND hWnd);