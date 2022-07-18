#include <iostream>
#include "archive.h"

using namespace std;

archive::archive() : arc_path("arc\\main_arc.txt") { CreateDirectory(L"arc", NULL); }

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
	write();
}

void archive::pop_back() {
	if (!file_cnt || !data.size())
		return;
	file_cnt -= 1;
	data.pop_back();
	write();
}

void archive::pop_by_name(string remove_name) {
	if (!file_cnt || !data.size())
		return;

	for (int i = 0; i < file_cnt; i++)
		if (!strcmp(data.at(i).c_str(), remove_name.c_str())) {
			data.erase(data.begin() + i);
			file_cnt -= 1;
		}
	write();
}

void archive::pop_by_index(int index) {
	if (!file_cnt || !data.size())
		return;
	if (index < 0 || index >= file_cnt)
		return;

	data.erase(data.begin() + index);
	file_cnt -= 1;
	write();
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