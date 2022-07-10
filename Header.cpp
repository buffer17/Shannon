#include <Windows.h>
#include "Header.h"

void MainWndAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"File");
	AppendMenu(RootMenu, MF_POPUP, OnMenuAction4, L"About");
	AppendMenu(SubMenu, MF_STRING, OnMenuAction1, L"SubOption1");
	AppendMenu(SubMenu, MF_STRING, OnMenuAction2, L"SubOption2");
	AppendMenu(SubMenu, MF_STRING, OnMenuAction3, L"SubOption3");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Exit");

	SetMenu(hWnd, RootMenu);
}

void MainWndAddText(HWND hWnd) {
	CreateWindowA("button", "Кнопка 1", WS_VISIBLE | WS_CHILD, 100, 50, 400, 80, hWnd, (HMENU)OnButtonClick1, NULL, NULL);
	CreateWindowA("button", "Кнопка 2", WS_VISIBLE | WS_CHILD, 100, 200, 400, 80, hWnd, (HMENU)OnButtonClick2, NULL, NULL);
}