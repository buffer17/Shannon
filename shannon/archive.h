#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>

std::string _return_exe();

class archive {
	int				file_cnt;					//число файлов
	std::vector		<std::string> data;			//пути к файлам архива
	std::string		arc_path;					//путь к файлу архива
	std::string		arc_folder_path = "arc";	//путь к папке архива
	std::ifstream	file_arc_read;
	std::ofstream	file_arc_write;
public:
	archive();

	bool read();								//чтение из архива
	void write();								//запись в архив

	void push_back(std::string);				//добавление в конец
	void pop_back();							//удаление с конца
	void pop_by_name(std::string);				//удаление по имени
	void pop_by_index(int);						//удаление из архива по индексу //с 0

	std::string file_name(std::string);
	std::string get_arc_path();
};