#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>

std::string _return_exe();

class archive {
	int				file_cnt;					//����� ������
	std::vector		<std::string> data;			//���� � ������ ������
	std::string		arc_path;					//���� � ����� ������
	std::string		arc_folder_path = "arc";	//���� � ����� ������
	std::ifstream	file_arc_read;
	std::ofstream	file_arc_write;
public:
	archive();

	bool read();								//������ �� ������
	void write();								//������ � �����

	void push_back(std::string);				//���������� � �����
	void pop_back();							//�������� � �����
	void pop_by_name(std::string);				//�������� �� �����
	void pop_by_index(int);						//�������� �� ������ �� ������� //� 0

	std::string file_name(std::string);
	std::string get_arc_path();
};