#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include "resource.h"
#include "zip_file.h"
#include "decoder.h"
#include "archive.h"
#include "interface.h"

using namespace std;

static OPENFILENAMEA	ofn;				//��� �������� txt
static OPENFILENAMEA	ofn_arc;			//��� �������� bin archive
archive					arc;				//����� ������

WNDCLASS NewWindowClass(HBRUSH, HCURSOR, HINSTANCE, HICON, LPCWSTR, WNDPROC);
LRESULT CALLBACK SoftwareMainProcedure(HWND, UINT, WPARAM, LPARAM);
void SetOpenFileParams(HWND hWnd);
void SetOpenFileParams_arc(HWND hWnd);
void SetOpenFileParams_arc(HWND);
string decoder_name(string);
string txtTObin_convert(string);
string binTOtxt_convert(string);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
	arc.read();								//������ ������ �������� ������
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(hInst, MAKEINTRESOURCEW(IDI_ICON1)),
		L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) return -1;
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"���������� �������", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 200, 200, 600, 400, NULL, NULL, NULL, NULL);
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
		case OnLoadFile:							//����������� ���� - ������������
			if (GetOpenFileNameA(&ofn)) {
				//decoder
				//
				ifstream file_beg(filename);		//�������� ���� ��� ���������
				DECODER dec;
				dec._array_fill(file_beg);
				dec._sort_array();
				dec._�umulat_a_code();
				dec._bin_merge(file_beg);

				//zip
				//
				ZIP_ zip(_return_exe() + "arc\\" +  arc.file_name(decoder_name(filename)), dec, _return_exe() + "arc\\" + arc.file_name(txtTObin_convert(filename)));
				zip.in_zip();
				zip.in_decoder();

				//delete old files
				//
				file_beg.close();
				remove(filename);

				//archive
				//
				arc.push_back(_return_exe() + "arc\\" + arc.file_name(txtTObin_convert(filename).c_str()));
				arc.write();					//��������� ���� ������
			}
			break;
		case OnSaveFile:						//����������� ���� - �������������
			if (GetOpenFileNameA(&ofn_arc)) {	//������� ��� ������������
				//decoder
				//
				string filename_ = binTOtxt_convert(filename);
				ofstream file_end(filename_);
				DECODER dec;
				ZIP_ zip(decoder_name(filename_), dec, txtTObin_convert(filename_));
				zip.out_decoder();
				zip.out_zip();
				dec._sym_merge(file_end);
				file_end.close();

				//delete old file
				//
				remove(filename);
				remove(decoder_name(filename_).c_str());
				SetOpenFileParams_arc(hWnd);

				//��������� � �����
				//
				if (GetSaveFileNameA(&ofn)) {	
					bool res = rename(filename_.c_str(), binTOtxt_convert(filename).c_str());
					if (res)					//���� ���� �� �������
						MessageBoxA(hWnd, "Error", "File not saved", MB_OK);
				} 
				//archive
				//
				arc.pop_by_name(_return_exe() + "arc\\" + arc.file_name(txtTObin_convert(filename_).c_str()));
				arc.write();
			}
			break;
		case AboutUs:							//� ���
			MessageBoxA(hWnd, "��������� - �������� ������, ��.1041\n���������� - ��������� �����, ��.1041\n������ - ������� �����, ��.1041\n\n2022, �������", "� ���", MB_OK);
			break;
		case OpenArchive:
			ShellExecuteA(NULL, "open", arc.get_arc_path().c_str(), NULL, NULL, SW_RESTORE);
			break;
		case OnExitSoftware:					//����� �� ����������
			PostQuitMessage(0);
			break;
		default: break;
		}
		break;

	case WM_CREATE:
		MainWndAddMenus(hWnd);
		MainWndAddText(hWnd);
		SetOpenFileParams(hWnd);
		SetOpenFileParams_arc(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void SetOpenFileParams(HWND hWnd) {
	ZeroMemory(&ofn, sizeof(ofn));									//��������� �������� � ���������
	ofn.lStructSize		=sizeof(ofn);								//������ ���������
	ofn.hwndOwner		=hWnd;										//������� ���� ����������
	ofn.lpstrFile		=filename;									//����� �������� ����� �����
	ofn.nMaxFile		=sizeof(filename);							//����� ������
	ofn.lpstrFilter		="��������� �������� (*.txt)\0*.txt\0";		//��� ������
	ofn.lpstrFileTitle	=NULL;										//��������� ��� �����
	ofn.nMaxFileTitle	=0;											//����� ���������� �����
	ofn.lpstrInitialDir	=NULL;										//��������� �����������
	ofn.Flags				=OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;		//���� ���� ����� � ��� ����
}

void SetOpenFileParams_arc(HWND hWnd) {
	ZeroMemory(&ofn_arc, sizeof(ofn_arc)); 
	ofn_arc.lStructSize		=sizeof(ofn_arc); 
	ofn_arc.hwndOwner		=hWnd;
	ofn_arc.lpstrFile		=filename;
	ofn_arc.nMaxFile		=sizeof(filename);
	ofn_arc.lpstrFilter		="���� \"BIN\"\0*.bin\0";
	ofn_arc.lpstrFileTitle	=NULL;
	ofn_arc.nMaxFileTitle	=0;
	ofn_arc.lpstrInitialDir =NULL;
	ofn_arc.Flags			=OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
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