#pragma once
#include <fstream>
#include <string>

class ZIP_ {
	std::ifstream f_decoder_read; //������ ��������
	std::ofstream f_decoder_write; //������ ��������

	std::ifstream f_tmpTXT_read; //������ ������������ �����
	std::ofstream f_tmpTXT_write; //������ ���������� �����

	std::ifstream f_bin_file_read; //������ ��������� �����
	std::ofstream f_bin_file_write; //������ ��������� �����

	std::string decoder_path; //���� � ��������
	std::string tmpTXT_path; //���� � ���������� �����
	std::string bin_file_path; //���� � ��������� �����
	
	std::string line; //������ ������
	bool correct_bin_code; //���� ������� ������ �� ������ 8
	char correct_bin_code_size = 0; //����� ���������� ����
public:
	ZIP_(std::string decoder_pth, std::string tmpTXT_pth,
		std::string bin_file_pth);
	~ZIP_();
	void in_zip();
	void out_zip();
};