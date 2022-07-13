#pragma once
#include<fstream>
#include <string>

class DECODER {
private:
	char* sym;// массив символов из файла
	double* count;// массив-счетчик повторений букв в файле
	long double* cumul;// массив кумулятивных вероятностей
	std::string* code;// массив бинарных кодов Т_Т
	int size;// два разных размера а зачем?
	std::string fin_code; //бинарный код
	
public:
	DECODER();
	~DECODER();

	void _array_fill(std::ifstream& mess_file);// заполняет массив символов
	void _sort_array();// сортирует массивы симоволов и счетчик по вероятности
	void _to_binary(long double, int, int);// должно переводить в бинарный вид кумулятивные вероятности
	void _сumulat_a_code();// считает кумулятивные вероятности и много какие еще приколы делает
	void _bin_merge(std::ifstream& mess_file); //представление строки в бинарный код

	std::string& _get_line();
	void _put_line(std::string&);

	void _out();// в семье не без урода, быстрая проверка, точка останова для лохов - вывод в консоль для пацанов

};