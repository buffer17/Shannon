#pragma once
#include <fstream>
#include <string>
#include "decoder.h"

class ZIP_ {
	std::ifstream f_decoder_read; //чтение декодера
	std::ofstream f_decoder_write; //запись декодера

	std::ifstream f_bin_file_read; //чтение бинарного файла
	std::ofstream f_bin_file_write; //запись бинарного файла

	std::string decoder_path; //путь к декодеру
	std::string bin_file_path; //путь к бинарному файлу
	
	std::string line; //строка данных
	bool correct_bin_code; //если кодовая строка не кратна 8
	char correct_bin_code_size = 0; //число отставания кода
public:
	DECODER& dec_; //ссылка для однозначного декодера
	ZIP_(std::string decoder_pth, DECODER& dec,
		std::string bin_file_pth);
	~ZIP_();

	void in_zip(); //записать в битовый файл
	void out_zip(); //вывод из файла

	void in_decoder(); //записать класса декодера в файл
	void out_decoder(); //чтение из декодер файла в класс
};