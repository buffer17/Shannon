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

ZIP_::ZIP_(std::string decoder_pth, std::string code_listTXT_pth,
	std::string bin_file_pth) : bin_file_path(bin_file_pth), correct_bin_code(true), 
								correct_bin_code_size(0) {
	this->decoder.open(decoder_pth.c_str());
	this->code_listTXT.open(code_listTXT_pth.c_str());
	if (!this->bin_file_write.is_open())
		this->bin_file_write.open(bin_file_pth.c_str(), ios::binary);
	if (!this->decoder.is_open())
		throw runtime_error("file decoder not found");
	if (!this->code_listTXT.is_open())
		throw runtime_error("file code_list not found");
}

ZIP_::~ZIP_() {
	this->decoder.close();
	this->code_listTXT.close();
	if (this->bin_file_write.is_open())
		this->bin_file_write.close();
	if (this->bin_file_read.is_open())
		this->bin_file_read.close();
}

void ZIP_::in_zip() {
	//cout << "========================INzip\n";
	if (bin_file_read.is_open())
		bin_file_read.close();
	string bin_line; //������� ������
	vector <char> byte_v;
	char byte_ = 0; //������������ ����
	int shift = 8; //�����
	getline(code_listTXT, bin_line); //��������� ������
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
	char len = byte_v.size();
	this->bin_file_write.write((char*)&len, sizeof(char)); //������ ����� ������
	this->bin_file_write.write((char*)&correct_bin_code_size, sizeof(char));
	for (size_t i = 0; i < byte_v.size(); i++)
		this->bin_file_write.write((char*)&byte_v[i], sizeof(char));
}

void ZIP_::out_zip() {
	//cout << "========================UNzip\n";
	//��������� ���� ��� ������, ������������� ��� ������
	if (this->bin_file_write.is_open())
		this->bin_file_write.close();
	this->bin_file_read.open(this->bin_file_path.c_str(), ios::binary);

	//��������� ������
	if (!line.empty()) //������� ������
		line.clear();

	char size_byte;
	bin_file_read.read(&size_byte, sizeof(char));
	bin_file_read.read(&correct_bin_code_size, sizeof(char));
	!correct_bin_code_size ? correct_bin_code = false : correct_bin_code = true;

	char data_byte; //������ ��������� �����
	while (!bin_file_read.eof()) { //������ �����
		bin_file_read.read(&data_byte, sizeof(char));	
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
	//cout << line;
}