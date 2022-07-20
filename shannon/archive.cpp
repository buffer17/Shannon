#include <iostream>
#include "archive.h"

using namespace std;

archive::archive() : arc_path(_return_exe() + "arc\\main_arc.txt") { CreateDirectory(L"arc", NULL); }

void archive::write() {
	//переоткрываем файл для записи
	//
	if (this->file_arc_write.is_open())
		this->file_arc_write.close();
	this->file_arc_write.open(this->arc_path.c_str());

	//запись в архив
	//
	file_arc_write << file_cnt << "\n";
	for (int i = 0; i < file_cnt; i++)
		file_arc_write << data.at(i).c_str() << "\n";
	file_arc_write.close();
}

bool archive::read() {
	if (this->file_arc_read.is_open())
		this->file_arc_read.close();
	this->file_arc_read.open(this->arc_path.c_str());
	
	//чтение из архива
	//
	file_arc_read >> file_cnt;
	if (file_cnt == 0)
		return false;

	//выделение памяти и чтение
	//
	data.resize(file_cnt);
	for (int i = 0; i < file_cnt; i++)
		file_arc_read >> data.at(i);
	file_arc_read.close();

	if (file_cnt != 0 && data.empty())
		return false;
	return true;
}

void archive::push_back(std::string pth_file) {
	file_cnt += 1;
	data.push_back(pth_file);
}

void archive::pop_back() {
	if (!file_cnt || !data.size())
		return;
	file_cnt -= 1;
	data.pop_back();
}

void archive::pop_by_name(string remove_name) {
	if (!file_cnt || !data.size())
		return;

	for (int i = 0; i < file_cnt; i++)
		if (!strcmp(data.at(i).c_str(), remove_name.c_str())) {
			data.erase(data.begin() + i);
			file_cnt -= 1;
		}
}

void archive::pop_by_index(int index) {
	if (!file_cnt || !data.size())
		return;
	if (index < 0 || index >= file_cnt)
		return;

	data.erase(data.begin() + index);
	file_cnt -= 1;
}

string archive::file_name(string path) {
	string file;
	for (int i = path.length() - 1; i != 0; i--) {
		if (path[i] == '\\') break;
		file += path[i];
	}
	reverse(file.begin(), file.end());
	return file;
}

std::string archive::get_arc_path() { return this->arc_folder_path; }

std::string _return_exe() {
	WCHAR buffer[MAX_PATH];
	string path;
	int let_cnt = 0;

	GetModuleFileName(NULL, buffer, sizeof(buffer) / sizeof(buffer[0]));

	while (buffer[let_cnt] != '\0') {
		path += buffer[let_cnt];
		let_cnt++;
	}
	path = std::string(path, 0, let_cnt);
	for (int i = let_cnt; path[i - 1] != '\\'; i--) {
		path.pop_back();
	}
	return path;
}