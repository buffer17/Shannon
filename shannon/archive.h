#pragma once
#include <vector>
#include <string>
#include <fstream>

class archive {
	int file_cnt; //����� ������
	std::vector <std::string> data; //���� � ������ ������
	std::string arc_path; //���� � ����� ������
	std::ifstream file_arc_read;
	std::ofstream file_arc_write;
public:
	archive();
	archive(std::string);

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
};