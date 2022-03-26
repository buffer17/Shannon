#pragma once
#include <fstream>
#include <string>

class ZIP_ {
	std::ifstream decoder; //чтение декодера
	std::ifstream code_listTXT; //чтение принимаемого файла
	std::ofstream bin_file_write; //запись бинарного файла
	std::ifstream bin_file_read; //запись бинарного файла
	std::string bin_file_path; //путь к бинарному файлу
	std::string line;
	bool correct_bin_code; //если кодовая строка не кратна 8
	char correct_bin_code_size = 0; //число отстования кода
public:
	ZIP_(std::string decoder_pth, std::string code_listTXT_pth,
		std::string bin_file_pth);
	~ZIP_();
	void in_zip();
	void out_zip();
};