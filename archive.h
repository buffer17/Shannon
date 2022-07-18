#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>

class archive {
	int file_cnt; //число файлов
	std::vector <std::string> data; //пути к файлам архива
	std::string arc_path; //путь к файлу архива
	std::string arc_folder_path = "arc"; //путь к папке архива
	std::ifstream file_arc_read;
	std::ofstream file_arc_write;
public:
	archive();

	//чтение/запись в файл
	bool read(); //чтение из архива
	void write(); //запись в архив

	//вывод данных в консоль
	void out_arc();

	//добавление/удаление в архив
	void push_back(std::string);
	void pop_back(); //удаление с конца
	void pop_by_name(std::string); //удаление по имени
	void pop_by_index(int); //удаление из архива по индексу //с 0

	//void put_file_arc(string, string);
	std::string file_name(std::string);
};