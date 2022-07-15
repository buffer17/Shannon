#include <iostream>
#include <fstream>
#include "decoder.h"
#include "zip_file.h"

using namespace std;

int main() {
	//process file to zip

	ifstream file_beg("message.txt");

	//decoder
	DECODER dec;
	dec._array_fill(file_beg);
	dec._sort_array();
	dec._�umulat_a_code();
	dec._bin_merge(file_beg); //�������� �������� ������ � ������ DECODER
	//dec._out();

	//zip
	ZIP_ zip("message_decoder.txt", dec, "message.bin"); //��������� ����� ZIP_
	zip.in_zip(); //�������� �������� ������ �� �������� � �������� ����
	zip.in_decoder(); //�������� ������� � ����

	//archive
	//�������� � ����� ���� � ��������� ����� � ��������
	//��������� ��� ����� � �����

	//process zip to file

	//����� ���� �� ������
	//����� ������� ���� �� ������

	//zip - decoder
	ofstream file_end("message_end.txt");
	DECODER dec; //������ �������
	ZIP_ zip("message_decoder.txt", dec, "message.bin");
	zip.out_decoder(); //������ ������� &dec == &zip_.dec_
	//dec._out();
	zip.out_zip(); //����������� �� ��������� ����� ���
	dec._sym_merge(file_end);
	
	
	file_beg.close();
	file_end.close();
	system("pause > nul");
	return 0;
}