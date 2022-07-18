#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "resource.h"
#include "zip_file.h"
#include "decoder.h"
#include "archive.h"
#include "interface.h"

using namespace std;

static OPENFILENAMEA ofn;
archive arc;

WNDCLASS NewWindowClass(HBRUSH, HCURSOR, HINSTANCE, HICON, LPCWSTR, WNDPROC);
LRESULT CALLBACK SoftwareMainProcedure(HWND, UINT, WPARAM, LPARAM);
void SetOpenFileParams(HWND hWnd);
string decoder_name(string);
string txtTObin_convert(string);
string binTOtxt_convert(string);



int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	arc.read(); //чтение архива бинарных файлов

	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCEW(IDI_ICON1)),
		L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) return -1;
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"Кодировщик Шеннона", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 200, 600, 400, NULL, NULL, NULL, NULL);
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
		case OnLoadFile: //контекстное меню - Закодировать
			if (GetOpenFileNameA(&ofn)) {
				//decoder
				ifstream file_beg(filename); //получаем файл для кодировки
				DECODER dec;
				dec._array_fill(file_beg);
				dec._sort_array();
				dec._сumulat_a_code();
				dec._bin_merge(file_beg);
				//zip
				ZIP_ zip("arc\\" + arc.file_name(decoder_name(filename)), dec, "arc\\" + arc.file_name(txtTObin_convert(filename)));
				zip.in_zip();
				zip.in_decoder();
				//delete old files
				file_beg.close();
				remove(filename);
				//archive
				arc.push_back("arc\\" + arc.file_name(txtTObin_convert(filename).c_str())); //добавляем файл в архив
				arc.write(); //сохраняем файл архива
			}
			break;
		case OnSaveFile: //контекстное меню - Раскодировать
			if (GetOpenFileNameA(&ofn)) { //открыть для раскодировки
				//decoder
				string filename_ = binTOtxt_convert(filename);
				ofstream file_end(filename_);
				DECODER dec;
				ZIP_ zip(decoder_name(filename_), dec, txtTObin_convert(filename_));
				zip.out_decoder();
				zip.out_zip();
				dec._sym_merge(file_end);
				file_end.close();
				//delete old file
				remove(filename);
				remove(decoder_name(filename_).c_str());
				if (GetSaveFileNameA(&ofn)) { //сохранить в архив
					bool res = rename(filename_.c_str(), binTOtxt_convert(filename).c_str());
					if (res) //если файл не сохранён
						MessageBoxA(hWnd, "Error", "File not saved", MB_OK);
				} 
				//archive
				arc.pop_by_name(txtTObin_convert(filename_).c_str()); //удаление из архива
				arc.write();
			}
			break;
		case AboutUs: //о нас
			MessageBoxA(hWnd, "Интерфейс - Лоншаков Максим, гр.1041\nКодировщик - Колмыкова Алена, гр.1041\nСжатие - Мочалов Артем, гр.1041\n\n2022, СПбГУАП", "О нас", MB_OK);
			break;
		case OnExitSoftware: //выход из приложения
			PostQuitMessage(0);
			break;
		default: break;
		}
		break;
	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddText(hWnd);
		SetOpenFileParams(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}


void SetOpenFileParams(HWND hWnd) {
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = filename;
	ofn.nMaxFile = sizeof(filename);
	ofn.lpstrFilter = ".txt";
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
}

string decoder_name(string last) {
	int ln = last.length();
	string new_path = last;
	new_path.resize(ln + 4);
	new_path[ln - 4] = '_';
	new_path[ln - 3] = 'd';
	new_path[ln - 2] = 'e';
	new_path[ln - 1] = 'c';
	new_path[ln] = '.';
	new_path[ln + 1] = 't';
	new_path[ln + 2] = 'x';
	new_path[ln + 3] = 't';
	return new_path;
}

string txtTObin_convert(string last) {
	string new_path = last;
	int ln = new_path.length();
	new_path[ln - 1] = 'n';
	new_path[ln - 2] = 'i';
	new_path[ln - 3] = 'b';
	return new_path;
}

string binTOtxt_convert(string last) {
	string new_path = last;
	int ln = new_path.length();
	new_path[ln - 1] = 't';
	new_path[ln - 2] = 'x';
	new_path[ln - 3] = 't';
	return new_path;
}