#include <Windows.h>
#include "Header.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) return -1;
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"Кодировщик Шеннона (рабочее название)", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 200, 600, 400, NULL, NULL, NULL, NULL);
	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}

	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
	WNDCLASS NWC = { 0 };

	NWC.hCursor = Cursor;
	NWC.hIcon = Icon;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
	case WM_COMMAND:
		switch (wp) {
		case OnMenuAction1:
			MessageBoxA(hWnd, "MessageBoxText1", "MessageBoxName1", MB_OK);
			break;
		case OnMenuAction2:
			MessageBoxA(hWnd, "MessageBoxText2", "MessageBoxName2", MB_OK);
			break;
		case OnMenuAction3:
			MessageBoxA(hWnd, "MessageBoxText3", "MessageBoxName3", MB_OK);
			break;
		case OnMenuAction4:
			MessageBoxA(hWnd, "Команда умников из ГУАПа, 2022", "About us", MB_OK);
			break;
		case OnButtonClick1:
			MessageBoxA(hWnd, "ButtonText1", "ButtonTextName1", MB_OK);
			break;
		case OnButtonClick2:
			MessageBoxA(hWnd, "ButtonText2", "ButtonTextName2", MB_OK);
			break;
		case OnExitSoftware:
			PostQuitMessage(0);
			break;
		default: break;
		}
		break;
	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddText(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}