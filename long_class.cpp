#include "long_class.h"

long_class::long_class()
{
	this->me = create_from_int(0);
}
/*
long_class::long_class(long_class& rhv)
{
	this->me = copy(rhv.me);
}

long_class::long_class(char *string)
{
	this->me = create_from_string(string);
}

long_class::long_class(long long int v)
{
	this->me = create_from_int(v);
}
*/
long_class::~long_class()
{
	if (this->me.digits != NULL)
	{
		free(this->me.digits);
	}
}

long_class& long_class::operator=(const long_class& rhv)
{
	if (this->me.digits != NULL)
	{
		free(this->me.digits);
	}
	this->me = copy(rhv.me);
	return *this;
}

char * long_class::str()
{
	return get_string(this->me);
}

long_class long_class::operator+(long_class &right)
{
	long_class res;
	res.me = sum_and_sub(this->me, right.me);
	return res;
}

//long_class long_class::operator-()
//{
//	long_class res;
//	res.me = minus(this->me);
//	return res;
//}

long_class long_class::operator-(long_class &right)
{
	long_class res, tmp;
	tmp.me = minus(this->me);
	res.me = sum_and_sub(tmp.me, right.me);
	return res;
}

long_class long_class::operator*(long_class &right)
{
	long_class res;
	res.me = multiplication(this->me, right.me);
	return res;
}

long_class long_class::operator/(long_class &right)
{
	long_class ost;
	long_class res;
	res.me = dividing(this->me, right.me, &ost.me);
	return res;
}

long_class long_class::operator%(long_class &right)
{
	long_class ost;
	long_class res;
	res.me = dividing(this->me, right.me, &ost.me);
	return ost;
}

long_class long_class::operator^(long_class &right)
{
	long_class res;
	res.me = involution(this->me, right.me);
	return res;
}

bool long_class::read_file_class(char* filename)
{
	long_class res;
	res.me = read_file(filename);
	if (res.me.digits == NULL)
	{
		return false;
	}
	else
	{
		*this = res;
		return true;
	}
}

bool long_class::read_bin_file_class(char* filename)
{
	long_class res;
	res.me = read_bin_file(filename);
	if (res.me.digits == NULL)
	{
		return false;
	}
	else
	{
		*this = res;
		return true;
	}
}

bool long_class::write_file_class(char* filename)
{
	int res;
	res = write_file(filename, this->me);
	if (res != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool long_class::write_bin_file_class(char* filename, bool flag, bool flag_mul, bool flag_sum, bool flag_sub)
{
	return write_bin_file(filename, this->me, flag, flag_mul, flag_sum, flag_sub) == 0;
}

bool long_class::operator>(long_class &rhv)
{
	int res;
	res = compare(this->me, rhv.me);
	if (res > 0)
		return true;
	else
		return false;
}

bool long_class::operator<(long_class &rhv)
{
	return compare(this->me, rhv.me) < 0;
}

bool long_class::operator!=(long_class &rhv)
{
	int res;
	res = compare(this->me, rhv.me);
	if (res != 0)
		return true;
	else
		return false;
}

long_class involution_module_class(long_class &base, long_class &exp, long_class &mod)
{
	long_class res;
	res.me = involution_module(base.me, exp.me, mod.me);
	return res;
}