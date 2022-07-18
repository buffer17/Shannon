#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <Windows.h>

class archive {
	int file_cnt; //����� ������
	std::vector <std::string> data; //���� � ������ ������
	std::string arc_path; //���� � ����� ������
	std::string arc_folder_path = "arc"; //���� � ����� ������
	std::ifstream file_arc_read;
	std::ofstream file_arc_write;
public:
	archive();

	//������/������ � ����
	bool read(); //������ �� ������
	void write(); //������ � �����

	//����� ������ � �������
	void out_arc();

	//����������/�������� � �����
	void push_back(std::string);
	void pop_back(); //�������� � �����
	void pop_by_name(std::string); //�������� �� �����
	void pop_by_index(int); //�������� �� ������ �� ������� //� 0

	//void put_file_arc(string, string);
	std::string file_name(std::string);
};