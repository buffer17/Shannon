#pragma once
#include<fstream>
#include <string>

class DECODER {
private:
	char* sym;// ������ �������� �� �����
	double* count;// ������-������� ���������� ���� � �����
	long double* cumul;// ������ ������������ ������������
	std::string* code;// ������ �������� ����� �_�
	int size;// ��� ������ ������� � �����?
	std::string fin_code; //�������� ���
	
public:
	DECODER();
	~DECODER();

	void _array_fill(std::ifstream& mess_file);// ��������� ������ ��������
	void _sort_array();// ��������� ������� ��������� � ������� �� �����������
	void _to_binary(long double, int, int);// ������ ���������� � �������� ��� ������������ �����������
	void _�umulat_a_code();// ������� ������������ ����������� � ����� ����� ��� ������� ������
	void _bin_merge(std::ifstream& mess_file); //������������� ������ � �������� ���

	std::string& _get_line();
	void _put_line(std::string&);

	void _out();// � ����� �� ��� �����, ������� ��������, ����� �������� ��� ����� - ����� � ������� ��� �������

};