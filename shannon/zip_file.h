#pragma once
#include <fstream>
#include <string>

class ZIP_ {
	std::ifstream f_decoder_read; //чтение декодера
	std::ofstream f_decoder_write; //запись декодера

	std::ifstream f_tmpTXT_read; //чтение принимаемого файла
	std::ofstream f_tmpTXT_write; //запись временного файла

	std::ifstream f_bin_file_read; //чтение бинарного файла
	std::ofstream f_bin_file_write; //запись бинарного файла

	std::string decoder_path; //путь к декодеру
	std::string tmpTXT_path; //путь к временному файлу
	std::string bin_file_path; //путь к бинарному файлу
	
	std::string line; //строка данных
	bool correct_bin_code; //если кодовая строка не кратна 8
	char correct_bin_code_size = 0; //число отставания кода
public:
	ZIP_(std::string decoder_pth, std::string tmpTXT_pth,
		std::string bin_file_pth);
	~ZIP_();
	void in_zip();
	void out_zip();
};