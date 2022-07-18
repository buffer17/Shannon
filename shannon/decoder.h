#pragma once
#include<fstream>
#include <string>

class DECODER {
private:
	char*			sym;						// массив символов из файла
	double*			count;						// массив-счетчик повторений букв в файле
	long double*	cumul;						// массив кумулятивных вероятностей
	std::string*	code;						// массив бинарных кодов Т_Т
	int				size;						// два разных размера а зачем?
	std::string		fin_code;					//бинарный код
	
public:
	DECODER();
	DECODER(int);
	DECODER(const DECODER&);
	~DECODER();

	void _array_fill(std::ifstream& mess_file);	// заполняет массив символов
	void _sort_array();							// сортирует массивы симоволов и счетчик по вероятности
	void _to_binary(long double, int, int);		// должно переводить в бинарный вид кумулятивные вероятности
	void _сumulat_a_code();						// считает кумулятивные вероятности и много какие еще приколы делает
	void _bin_merge(std::ifstream& mess_file);	//представление строки в бинарный код
	void _sym_merge(std::ofstream& mess_file);	//представление бинарного кода в строку

	std::string& _get_code();
	void _put_code(std::string&);
	int _get_size();
	void _put_size(int);
	char& r_sym();
	std::string& r_code();

	DECODER& operator=(const DECODER&);

};