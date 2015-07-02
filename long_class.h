#pragma once

#ifndef _LONG_CLASS_H_
#define _LONG_CLASS_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <malloc/malloc.h>
#include "long_numeric.h"
class long_class
{
	long_numeric me;

public:
	//конструкторы
	long_class(); // конструктор по умолчанию, вызывается без аргументов
	~long_class();// деструктор, очистка памяти
	/*long_class(long_class& rhv);// констр-р копирования
	long_class(char *string); //конструктор из строки
	long_class(long long int v); */

	// метод
	char *str();

	// операторы
	long_class& operator=(const long_class& rhv); // оператор присвания
	long_class operator+(long_class &right);
//	long_class operator-(); // унарный оператор
	long_class operator-(long_class &right);
	long_class operator*(long_class &right);
	long_class operator/(long_class &right);
	long_class operator%(long_class &right);
	long_class operator^(long_class &right);

	bool operator>(long_class &rhv);
	bool operator<(long_class &rhv);
	bool operator!=(long_class &rhv);

	// методы
	bool read_file_class(char* filename);
	bool write_file_class(char* filename);
	bool read_bin_file_class(char* filename);
	bool write_bin_file_class(char* filename, bool flag, bool flag_mul, bool flag_sum, bool flag_sub);
	// дружественная функция
	friend long_class involution_module_class(long_class &base, long_class &exp, long_class &mod);
};

#endif