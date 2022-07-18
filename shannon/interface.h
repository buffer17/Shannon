#pragma once
#include <Windows.h>

#define OnLoadFile			1
#define OnSaveFile			2
#define AboutUs				3
#define OpenArchive			4
#define OnExitSoftware		5	

#define TextBufferSize		256

static char Buffer_[TextBufferSize];
static HWND hEditControl;
static char filename[256];

void MainWndAddMenus(HWND hWnd);
void MainWndAddText(HWND hWnd);
void SaveData(LPCSTR path);

