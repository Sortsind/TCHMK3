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
	//������������
	long_class(); // ����������� �� ���������, ���������� ��� ����������
	~long_class();// ����������, ������� ������
	/*long_class(long_class& rhv);// ������-� �����������
	long_class(char *string); //����������� �� ������
	long_class(long long int v); */

	// �����
	char *str();

	// ���������
	long_class& operator=(const long_class& rhv); // �������� ���������
	long_class operator+(long_class &right);
//	long_class operator-(); // ������� ��������
	long_class operator-(long_class &right);
	long_class operator*(long_class &right);
	long_class operator/(long_class &right);
	long_class operator%(long_class &right);
	long_class operator^(long_class &right);

	bool operator>(long_class &rhv);
	bool operator<(long_class &rhv);
	bool operator!=(long_class &rhv);

	// ������
	bool read_file_class(char* filename);
	bool write_file_class(char* filename);
	bool read_bin_file_class(char* filename);
	bool write_bin_file_class(char* filename, bool flag, bool flag_mul, bool flag_sum, bool flag_sub);
	// ������������� �������
	friend long_class involution_module_class(long_class &base, long_class &exp, long_class &mod);
};

#endif