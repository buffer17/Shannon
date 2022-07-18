#include <Windows.h>
#include "interface.h"

void MainWndAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"����");
	AppendMenu(RootMenu, MF_POPUP, AboutUs, L"� ���");
	/*AppendMenu(SubMenu, MF_STRING, OnSaveFile, L"���������...");
	AppendMenu(SubMenu, MF_STRING, OnLoadFile, L"���������...");*/
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"�����");

	SetMenu(hWnd, RootMenu);
}

void MainWndAddText(HWND hWnd) {
	CreateWindowA("button", "������������", WS_VISIBLE | WS_CHILD, 100, 50, 400, 80, hWnd, (HMENU)OnLoadFile, NULL, NULL);
	CreateWindowA("button", "�������������", WS_VISIBLE | WS_CHILD, 100, 200, 400, 80, hWnd, (HMENU)OnSaveFile, NULL, NULL);
}

//void LoadData(LPCSTR path) {
//	HANDLE FileToLoad = CreateFileA(path, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
//	DWORD bytesIterated;
//	ReadFile(FileToLoad, Buffer_, TextBufferSize, &bytesIterated, NULL);
//	SetWindowTextA(hEditControl, Buffer_);
//	CloseHandle(FileToLoad);
//}

void SaveData(LPCSTR path) {
	HANDLE FileToSave = CreateFileA(path, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	int saveLength = GetWindowTextLength(hEditControl);
	char* data = new char[saveLength];

	saveLength = GetWindowTextA(hEditControl, data, saveLength);
	DWORD bytesIterated;
	WriteFile(FileToSave, data, saveLength, &bytesIterated, NULL);
	CloseHandle(FileToSave);
	delete[] data;
}