#pragma once
#include<fstream>
#include <string>

class DECODER {
private:
	char*			sym;						// ������ �������� �� �����
	double*			count;						// ������-������� ���������� ���� � �����
	long double*	cumul;						// ������ ������������ ������������
	std::string*	code;						// ������ �������� ����� �_�
	int				size;						// ��� ������ ������� � �����?
	std::string		fin_code;					//�������� ���
	
public:
	DECODER();
	DECODER(int);
	DECODER(const DECODER&);
	~DECODER();

	void _array_fill(std::ifstream& mess_file);	// ��������� ������ ��������
	void _sort_array();							// ��������� ������� ��������� � ������� �� �����������
	void _to_binary(long double, int, int);		// ������ ���������� � �������� ��� ������������ �����������
	void _�umulat_a_code();						// ������� ������������ ����������� � ����� ����� ��� ������� ������
	void _bin_merge(std::ifstream& mess_file);	//������������� ������ � �������� ���
	void _sym_merge(std::ofstream& mess_file);	//������������� ��������� ���� � ������

	std::string& _get_code();
	void _put_code(std::string&);
	int _get_size();
	void _put_size(int);
	char& r_sym();
	std::string& r_code();

	DECODER& operator=(const DECODER&);

};