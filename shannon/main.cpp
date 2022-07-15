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
	dec._сumulat_a_code();
	dec._bin_merge(file_beg); //получаем бинарную строку в классе DECODER
	//dec._out();

	//zip
	ZIP_ zip("message_decoder.txt", dec, "message.bin"); //заполняем класс ZIP_
	zip.in_zip(); //кодируем бинарную строку из декодера в бинарный файл
	zip.in_decoder(); //записать декодер в файл

	//archive
	//передать в архив путь к бинарному файлу и декодеру
	//сохранить два файла в архив

	//process zip to file

	//взять файл из архива
	//взять декодер файл из архива

	//zip - decoder
	ofstream file_end("message_end.txt");
	DECODER dec; //пустой декодер
	ZIP_ zip("message_decoder.txt", dec, "message.bin");
	zip.out_decoder(); //достаём декодер &dec == &zip_.dec_
	//dec._out();
	zip.out_zip(); //вытаскиваем из бинарного файла код
	dec._sym_merge(file_end);
	
	
	file_beg.close();
	file_end.close();
	system("pause > nul");
	return 0;
}