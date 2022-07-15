#include<iostream>
#include<cmath>
#include<bitset>
#include"decoder.h"

DECODER::DECODER() {
	size = 0;
	sym = new char[size];
	count = new double[size];
	cumul = new long double[size];
	code = new std::string[size];
}

DECODER::DECODER(int sz) {
	size = sz;
	sym = new char[size];
	count = new double[size];
	cumul = new long double[size];
	code = new std::string[size];
}

DECODER::DECODER(const DECODER& tmp) {
	this->size = tmp.size;
	this->sym = tmp.sym;
	this->count = tmp.count;
	this->cumul = tmp.cumul;
	this->code = tmp.code;
}

DECODER& DECODER::operator=(const DECODER& tmp) {
	this->size = tmp.size;
	//необходимо выделить память для избежания утечки
	sym = new char[size];
	count = new double[size];
	cumul = new long double[size];
	code = new std::string[size];
	for (size_t i = 0; i < size; i++) {
		sym[i] = tmp.sym[i];
		count[i] = tmp.count[i];
		cumul[i] = tmp.cumul[i];
		code[i] = tmp.code[i];
	}

	return *this;
}

DECODER::~DECODER() {
	delete[] sym;
	delete[] count;
	delete[] cumul;
	delete[] code;
}

void DECODER::_array_fill(std::ifstream& mess_file) {
	bool flag; 
	char ch;
	int mem;
	while (mess_file.get(ch)) {
		flag = false;
		mem = 0;
		for (size_t i = 0; i <size;i++) {
			if (this->sym[i] == ch) {
				flag = true;
				mem = i;
			}
		}
		if (flag == false) {
			size++;
			char* temp_sym=this->sym;
			double* temp_count=this->count;
			this->sym = new char[size];
			this->count = new double[size];
			for (size_t i = 0; i < (size - 1); i++) {
				this->sym[i] = *temp_sym;
				this->count[i] = *temp_count;
				temp_sym++;
				temp_count++;
			}
			this->sym[size-1] = ch;
			this->count[size-1] = 1;
		}
		else 
			this->count[mem] += 1;
			
	}
}

void DECODER::_sort_array() {

	const double factor = 1.247; // Фактор уменьшения
	double step = size - 1;

	while (step >= 1) {
		for (int i = 0; i + step < size; ++i) {
			if (this->count[i]  < this->count[int(i + step)]) {
				std::swap(this->count[i], this->count[int(i + step)]);
				std::swap(this->sym[i], this->sym[int(i + step)]);
			}
		}
		step /= factor;
	}
	// сортировка пузырьком
	for (size_t idx_i = 0; idx_i + 1 <size; ++idx_i) {
		for (size_t idx_j = 0; idx_j + 1 < size - idx_i; ++idx_j) {
			if (this->count[idx_j + 1] > this->count[idx_j]) {
				std::swap(this->count[idx_j], this->count[idx_j + 1]);
				std::swap(this->sym[idx_j], this->sym[idx_j + 1]);
			}
		}
	}
}

void DECODER::_to_binary(long double num, int temp, int cnt) {

	long double frac_num;
	unsigned int int_num;

	char* buff= new char[temp];

	int_num = num;
	frac_num = num - floor(num);
	for (int i = 0; i < temp; i++)
	{
		frac_num *= 2;
		buff[i] = (char)(((int)'0')+floor(frac_num));
		frac_num -= floor(frac_num);
	}
	this->code[cnt] = std::string(buff,0,temp);
}

void DECODER::_сumulat_a_code() {

	this->cumul = new long double[size];
	this->code = new std::string[size];
	int* temp = new int[size];// длина кода
	double* prob = new double[size];// обычная вероятность 

	int value_summ = 0;

	for (size_t i = 0; i < size; i++) {
		value_summ += this->count[i];
	}

	for (size_t i = 0; i < size; i++) {
		prob[i] = ((this->count[i]) / value_summ);
	}

	this->cumul[0] = 0;
	for (size_t i = 1; i < size; i++) {
		this->cumul[i] = this->cumul[i - 1] + prob[i - 1];
	}
	for (size_t i = 0; i < size; i++) {
		temp[i] =ceil( - log2(prob[i]));
	}
	for (size_t i = 0; i < size; i++) {
		_to_binary(cumul[i], temp[i], i);
	}
}

void DECODER::_bin_merge(std::ifstream& mess_file) {
	std::string line;
	if (!mess_file.is_open())
		return;
	mess_file.clear();
	mess_file.seekg(0);
	char ch;
	while (mess_file.get(ch)) {
		int cmp = 0;
		for (; cmp < size; cmp++)
			if (ch == sym[cmp])
				fin_code += code[cmp];
	}
}

void DECODER::_sym_merge(std::ofstream& mess_file) {
	std::string tmp_bin_code;

	for (size_t i = 0; fin_code[i] != '\0'; i++) {
		tmp_bin_code.push_back(fin_code[i]);
		for (size_t j = 0; j < size; j++) 
			if (!std::strcmp(tmp_bin_code.c_str(), code[j].c_str())) { //нашли совпадение в декодере
				mess_file << sym[j]; //запись соотвветствующего символа
				tmp_bin_code.clear(); //очистка временной строки
				break;
			}
	}
}

void DECODER::_out() {
	for (size_t i = 0; i < size; i++)
		std::cout << this->sym[i] << " " << this->code[i] << std::endl;
	std::cout << std::endl <<  this->fin_code;
}

std::string& DECODER::_get_code() { return this->fin_code; }
void DECODER::_put_code(std::string& tmp) { this->fin_code = tmp; }

int DECODER::_get_size() { return this->size; }
void DECODER::_put_size(int sz) { this->size = sz; }

char& DECODER::r_sym() { return *sym; }
std::string& DECODER::r_code() { return *code; }