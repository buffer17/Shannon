#pragma once
#include <fstream>
#include <string>

class ZIP_ {
	std::ifstream decoder; //������ ��������
	std::ifstream code_listTXT; //������ ������������ �����
	std::ofstream bin_file_write; //������ ��������� �����
	std::ifstream bin_file_read; //������ ��������� �����
	std::string bin_file_path; //���� � ��������� �����
	std::string line;
	bool correct_bin_code; //���� ������� ������ �� ������ 8
	char correct_bin_code_size = 0; //����� ���������� ����
public:
	ZIP_(std::string decoder_pth, std::string code_listTXT_pth,
		std::string bin_file_pth);
	~ZIP_();
	void in_zip();
	void out_zip();
};