#pragma once
#include <fstream>
#include <string>
#include "decoder.h"

class ZIP_ {
	std::ifstream f_decoder_read; //������ ��������
	std::ofstream f_decoder_write; //������ ��������

	std::ifstream f_bin_file_read; //������ ��������� �����
	std::ofstream f_bin_file_write; //������ ��������� �����

	std::string decoder_path; //���� � ��������
	std::string bin_file_path; //���� � ��������� �����
	
	std::string line; //������ ������
	bool correct_bin_code; //���� ������� ������ �� ������ 8
	char correct_bin_code_size = 0; //����� ���������� ����
public:
	DECODER& dec_; //������ ��� ������������ ��������
	ZIP_(std::string decoder_pth, DECODER& dec,
		std::string bin_file_pth);
	~ZIP_();

	void in_zip(); //�������� � ������� ����
	void out_zip(); //����� �� �����

	void in_decoder(); //�������� ������ �������� � ����
	void out_decoder(); //������ �� ������� ����� � �����
};