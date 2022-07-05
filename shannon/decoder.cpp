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

DECODER::~DECODER() {
	delete[] sym, count, cumul, code;
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

	size = size;

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

void DECODER::_out() {
	for (size_t i = 0; i < size; i++) {
		std::cout << this->sym[i]<<this->cumul[i]<<" ";
	}
	std::cout << std::endl;
	for (size_t i = 0; i < size; i++) {
		std::cout << this->code[i] << std::endl;
	}
}