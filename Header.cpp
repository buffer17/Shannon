#include <Windows.h>
#include "Header.h"

void MainWndAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();
	HMENU SubMenu = CreateMenu();

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMenu, L"Файл");
	AppendMenu(RootMenu, MF_POPUP, AboutUs, L"О нас");
	AppendMenu(SubMenu, MF_STRING, OnSaveFile, L"Загрузить...");
	AppendMenu(SubMenu, MF_STRING, OnLoadFile, L"Сохранить...");
	AppendMenu(SubMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(SubMenu, MF_STRING, OnExitSoftware, L"Выйти");

	SetMenu(hWnd, RootMenu);
}

void MainWndAddText(HWND hWnd) {
	CreateWindowA("button", "Кнопка 1", WS_VISIBLE | WS_CHILD, 100, 50, 400, 80, hWnd, (HMENU)OnLoadFile, NULL, NULL);
	CreateWindowA("button", "Кнопка 2", WS_VISIBLE | WS_CHILD, 100, 200, 400, 80, hWnd, (HMENU)OnSaveFile, NULL, NULL);
}

void LoadData(LPCSTR path) {
	HANDLE FileToLoad = CreateFileA(path, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD bytesIterated;
	ReadFile(FileToLoad, Buffer, TextBufferSize, &bytesIterated, NULL);
	SetWindowTextA(hEditControl, Buffer);
	CloseHandle(FileToLoad);
}

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

void SetOpenFIleParams(HWND hWnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = ".txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = "D:\\Max\\guap\\win\\win\\";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}