#include <iostream>
#include <vector>
#include "zip_file.h"

using namespace std;

//void bit_output_console(char value) {
//	size_t size = sizeof(value) * 8;
//	for (int i = size - 1; i >= 0; i--)
//		cout << (int)((value >> i) & 1);
//}

char reverse_bit(char value) {
	char mirror_tmp = 0;
	for (char i_bit = CHAR_BIT * sizeof(char); i_bit > 0; --i_bit) {
		mirror_tmp <<= 1;
		mirror_tmp |= (value & 1);
		value >>= 1;
	}
	return mirror_tmp;
}

ZIP_::ZIP_(std::string decoder_pth, DECODER& dec,
	std::string bin_file_pth) : 
	decoder_path(decoder_pth), dec_(dec), bin_file_path(bin_file_pth),
	correct_bin_code(true), correct_bin_code_size(0) {}

ZIP_::~ZIP_() {
	f_decoder_read.close();
	f_decoder_write.close();
	f_bin_file_read.close();
	f_bin_file_write.close();
	//f_tmpTXT_read.close();
	//f_tmpTXT_write.close();
}

void ZIP_::in_zip() {
	//cout << "========================INzip\n";
	//f_tmpTXT_read.open(tmpTXT_path.c_str());
	string bin_line; //������� ������
	vector <char> byte_v;
	char byte_ = 0; //������������ ����
	int shift = 8; //�����
	//getline(f_tmpTXT_read, bin_line); //��������� ������
	bin_line = dec_._get_line();
	for (size_t i = 0; i < bin_line.length(); i++) { //����������� �� ������ 
		char bit = (char)(bin_line[i] - '0'); //��������� ���
		
		_asm { //bx - ������� ����� byte_, �������� ��� ������
			cmp bit, 1
			jne L
			mov cl, ~0
			jmp Q
			L: mov cl, 0
			Q: shrd bx, cl, 1
		}
		shift--;

		if (shift == 0 || i == bin_line.length() - 1) { //���� ���� �������� ��� ������ �����������
			_asm { //
				shr bx, 8
				mov byte_, bl
			}
			//���������� �����
			byte_ = reverse_bit(byte_);
			if (shift != 0) {//���� ���� �� �������� �� �����
				byte_ <<= shift; //����� �����
				correct_bin_code = false;
				correct_bin_code_size = shift;
			}
			//cout << (int)byte_ << " "; bit_output_console(byte_); cout << endl;
			byte_v.push_back(byte_);
			shift = 8;
		}
	}
	//������ � ������� ����
	f_bin_file_write.open(bin_file_path.c_str(), ios::binary);
	char len = byte_v.size();
	this->f_bin_file_write.write((char*)&len, sizeof(char)); //������ ����� ������
	this->f_bin_file_write.write((char*)&correct_bin_code_size, sizeof(char));
	for (size_t i = 0; i < byte_v.size(); i++)
		this->f_bin_file_write.write((char*)&byte_v[i], sizeof(char));

	//������� ������
	//f_tmpTXT_read.close();
	f_bin_file_write.close();
}

void ZIP_::out_zip() {
	//cout << "========================UNzip\n";
	//��������� ���� ��� ������, ������������� ��� ������
	f_bin_file_read.open(bin_file_path.c_str(), ios::binary);

	//��������� ������
	if (!line.empty()) //������� ������
		line.clear();

	char size_byte;
	f_bin_file_read.read(&size_byte, sizeof(char));
	f_bin_file_read.read(&correct_bin_code_size, sizeof(char));
	!correct_bin_code_size ? correct_bin_code = false : correct_bin_code = true;

	char data_byte; //������ ��������� �����
	while (!f_bin_file_read.eof()) { //������ �����
		f_bin_file_read.read(&data_byte, sizeof(char));	
		char bit;

		for (size_t i = 0; i < sizeof(char) * 8; i++) {
			_asm {
				shl data_byte, 1
				jc cf_1 //�������� ����� cf
				cf_0: mov bit, 0
				jmp Q
				cf_1: mov bit, 1
				Q:
			}
			line.push_back(bit + '0');
		}
	}
	line.resize(line.size() - 8/*������� ���*/ - (correct_bin_code ? correct_bin_code_size : 0)/*�������� ������ �����*/);
	
	//������ � tmp.txt
	//f_tmpTXT_write.open(tmpTXT_path.c_str());
	//f_tmpTXT_write << line;
	dec_._put_line(line);
	//������� ������ 
	//f_bin_file_read.close();
	//f_tmpTXT_write.close();
}