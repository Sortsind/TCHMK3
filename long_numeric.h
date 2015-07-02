#ifndef _LONG_NUMERIC_H_
#define _LONG_NUMERIC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <malloc/malloc.h>

#define BASIS 1000000000

struct long_numeric
{
	int size;
	int sign;
	unsigned int* digits;
};

typedef struct long_numeric long_numeric;

struct long_numeric create_from_string(char* string);
long_numeric create_from_int(long long int value);
char* get_string(struct long_numeric a);
long_numeric copy(long_numeric from);
long_numeric delete_zero(long_numeric a);
long long int compare(long_numeric A, long_numeric B);
long_numeric sum_and_sub(long_numeric left, long_numeric right);
long_numeric sum(long_numeric A, long_numeric B);
long_numeric sub(long_numeric A, long_numeric B);
long_numeric minus(long_numeric a);
long_numeric multiplication(long_numeric A, long_numeric B);
long_numeric dividing(long_numeric A, long_numeric B, long_numeric* remainder);
long_numeric shift_left(long_numeric a, int s);
long_numeric involution(long_numeric base, long_numeric exp);
long_numeric involution_module(long_numeric base, long_numeric exp, long_numeric modulus);
long_numeric read_bin_file(char* filename);
int write_bin_file(char* filename, long_numeric A, bool flag, bool flag_mul, bool flag_sum, bool flag_sub);
long_numeric read_file(char *fileName);
int write_file(char *fileName, long_numeric A);

#endif