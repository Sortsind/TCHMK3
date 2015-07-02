#include "long_numeric.h"

unsigned int x[2];
int r = 0;

struct long_numeric create_from_string(char* string)
{
	int strSize = strlen(string);
	int strSign = 0;
	if (string[0] == '-')
	{
		strSize--;
		strSign = 1;
	}

	char* pStr = string + strSize + strSign;

	// ������� ��������� ���������, � ������� ������� ��������� ��������
	struct long_numeric res;
	res.size = ((strSize + strSign + 8) / 9);
	res.sign = strSign;
	res.digits = (unsigned int*)malloc((res.size)*sizeof(unsigned int));

	// ��������� ������ �� ����� �� 9 ��������
	int i;
	for (i = 0; i < (strSize + strSign) / 9; i++)
	{
		pStr -= 9;
		char splStr[10];
		memcpy(splStr, pStr, 9);
		splStr[9] = '\0'; // �������� ��������� ������ �� 9 ��������
		unsigned int digitI = atol(splStr);

		res.digits[i] = digitI;
	}

	// ������������ ���������� ������� (���� ����� ������ �� ������ 9)
	char ost[10];
	memset(ost, 0, 10);
	memcpy(ost, string + strSign, pStr - string - strSign); // �������� ������ - �������������� �����
	if (strlen(ost) > 0)
	{
		unsigned int lastDigit = atol(ost);
		res.digits[res.size - 1] = lastDigit;
	}

	res = delete_zero(res);
	return res;
}

long_numeric create_from_int(long long int value)
{
	long_numeric res;
	// �������� ������ ��� 3-� ���������
	res.digits = (unsigned int*)malloc((3)*sizeof(unsigned int));
	res.size = 0;
	res.sign = 0;

	if (value < 0)
	{
		res.sign = 1;
		value = -value;
	}
	do
	{
		res.size++;
		res.digits[res.size - 1] = value % BASIS;
		value = value / BASIS;
	} while (value);

	return res;
}

char* get_string(long_numeric a)
{
	char* strBuffer = (char*)malloc((a.size * 9 + 1 + a.sign) * sizeof(char));
	char* pString = strBuffer + a.size * 9 + a.sign; // ��������� �� ������� ������� ��� ������ �����
	*pString = '\0'; // ��������� ������ ����� ������


	int i;
	for (i = 0; i < a.size; i++)
	{
		// �������� ��������� ������������� ���������� �������
		char splStr[10];
		sprintf(splStr, "%09u", a.digits[i]);

		pString -= 9;
		memcpy(pString, splStr, 9);
	}

	// �������� ������� �����
	while (*pString == '0' && *(pString + 1))
		pString++;

	if (a.sign)
	{
		pString--;
		*pString = '-';
	}

	char* string = (char*)malloc((strlen(pString) + 1) * sizeof(char));
	strcpy(string, pString);
	free(strBuffer);

	return string;
}

long_numeric copy(long_numeric from)
{
	long_numeric cpy;
	cpy.size = from.size;
	cpy.digits = (unsigned int*)malloc((cpy.size)*sizeof(unsigned int));
	cpy.sign = from.sign;
	memcpy(cpy.digits, from.digits, cpy.size * sizeof(unsigned int));
	return cpy;
}

long_numeric delete_zero(long_numeric a)
{
	while ((a.size - 1) && a.digits && a.digits[a.size - 1] == 0)
		a.size--;

	if (a.size == 1 && a.digits[0] == 0)
		a.sign = 0;

	return a;
}

long long int compare(long_numeric A, long_numeric B)
{
	// ������� ��������� ���� ������� �����
	// ������� ����������
	// 0 - ���� ����� �����,
	// >0 - ���� A ������
	// <0 - ���� A ������

	int aSign = 1;
	if (A.sign == 1)
		aSign = -1;

	if (A.sign != B.sign)
		return aSign;

	if (A.size > B.size)
		return aSign;

	if (A.size < B.size)
		return -aSign;

	int i = A.size - 1;

	while (A.digits[i] == B.digits[i] && i > 0)
	{
		i--;
	}
	return ((long long int) A.digits[i] - (long long int)B.digits[i]) * aSign;

}

long_numeric shift_left(long_numeric a, int s)
{
	// �������� ����� a �� s �������� ������
	// �� ����, �� ����, ��� ��������� �� BASIS^s

	unsigned int* newDig = (unsigned int*)malloc((a.size + s)*sizeof(unsigned int));

	// ��������� ������� ������� ������
	memset(newDig, 0, s * sizeof(unsigned int));

	// �������� ������� �������
	memcpy(newDig + s, a.digits, a.size * sizeof(unsigned int));
	free(a.digits);
	a.digits = newDig;
	a.size += s;

	return a;
}

long_numeric sum_and_sub(long_numeric left, long_numeric right)
{
	// ����� � � ����� �� ������ �� ������, ��� � B
	long_numeric A = left, B = right;
	A.sign = 0;
	B.sign = 0;
	if (compare(A, B) > 0)
	{
		A.sign = left.sign;
		B.sign = right.sign;
	}
	else
	{
		A = right;
		B = left;
	}

	// ���� ����� ������ ����� - ���������� �� (� ������������ ������� �����)
	if (A.sign == B.sign)
		return sum(A, B);
	else // ����� ��������
		return sub(A, B);
}

long_numeric sum(long_numeric A, long_numeric B)
{
	// ��������� ���� �����, ������ A - �� ������ B

	long_numeric res;
	res.sign = 0;
	res.size = A.size + 1;
	res.digits = (unsigned int*)malloc((A.size + 1)*sizeof(unsigned int));

	unsigned int carry = 0;
	int i;
	for (i = 0; i < A.size; i++)
	{
		unsigned int tmp = A.digits[i] + carry;
		if (i < B.size)
			tmp += B.digits[i];

		res.digits[i] = tmp % BASIS;
		carry = tmp / BASIS;
	}

	res.digits[A.size] = carry;
	res.sign = A.sign;
	res = delete_zero(res);
	return res;
}

long_numeric sub(long_numeric A, long_numeric B)
{
	// ��������� ���� �����, ������ A ������ B �� ������
	long_numeric res;
	res.sign = 0;
	res.size = A.size;
	res.digits = (unsigned int*)malloc((A.size)*sizeof(unsigned int));

	unsigned int carry = 0;
	int i;
	for (i = 0; i < A.size; i++)
	{
		int tmp = A.digits[i] - carry;
		if (i < B.size)
			tmp -= B.digits[i];

		carry = 0;
		if (tmp < 0)
		{
			carry = 1;
			tmp += BASIS;
		}
		res.digits[i] = tmp;
	}

	res.sign = A.sign;
	//res = delete_zero(res);
	return res;
}

long_numeric minus(long_numeric a)
{
	// ������ ����� ����� a, �� � ��������������� ������
	long_numeric res = copy(a);
	res.sign = !a.sign;
	return res;
}

long_numeric multiplication(long_numeric A, long_numeric B)
{
	long_numeric res;
	res.size = A.size + B.size;
	res.digits = (unsigned int*)malloc((res.size)*sizeof(unsigned int));
	memset(res.digits, 0, res.size * sizeof(unsigned int));
	unsigned int carry = 0;
	int i;
	for (i = 0; i < B.size; i++)
	{
		carry = 0;
		int j;
		for (j = 0; j < A.size; j++)
		{
			// ����� �������� � ������� ������ ������, ��� ������� ����� ��� int, ��� ��������� ������� ����� ��������� ������������. 
			// ��� ����� �� ���� ������������ ���������� ����� ���������� �����
			unsigned long long int tmp = (unsigned long long int) B.digits[i] * (unsigned long long int) A.digits[j]
				+ carry + (unsigned long long int) res.digits[i + j];
			carry = tmp / BASIS;
			res.digits[i + j] = tmp % BASIS;
		}
		res.digits[i + A.size] = carry;
	}

	res.sign = (A.sign != B.sign);
	res = delete_zero(res);
	return res;
}

long_numeric dividing(long_numeric A, long_numeric B, long_numeric* remainder)
{
	*remainder = copy(A);
	remainder->sign = 0;

	long_numeric divider = copy(B);
	divider.sign = 0;

	// ���� �������� ����� ����
	if (1 == divider.size)
	{
		if (divider.digits[0] == 0)
		{
			remainder->size = 0;
			remainder->sign = 0;
			remainder->digits = NULL;

			long_numeric a;
			a.size = 0;
			a.sign = 0;
			a.digits = NULL;

			free(divider.digits);
			return a;
		}
	}

	// ���� ������� ������ ��������
	if (compare(*remainder, divider) < 0)
	{
		// ������� ����� ��������
		// ������� - ����
		remainder->sign = A.sign;
		long_numeric res;
		res.sign = 0;
		res.size = 1;
		res.digits = (unsigned int*)malloc((res.size)*sizeof(unsigned int));
		res.digits[0] = 0;
		free(divider.digits);
		return res;
	}

	// ���� ���������� ������ �� ������������� �����
	if (divider.size == 1)
	{
		long_numeric res;
		res.size = A.size;
		res.digits = (unsigned int*)malloc((res.size)*sizeof(unsigned int));

		unsigned long long int carry = 0;
		int i;
		for (i = A.size - 1; i >= 0; i--)
		{
			unsigned long long int temp = carry;
			temp *= BASIS;
			temp += A.digits[i];
			res.digits[i] = temp / divider.digits[0];
			carry = (unsigned long long int)  temp - (unsigned long long int) res.digits[i] * (unsigned long long int) divider.digits[0];
		}
		remainder->sign = (A.sign != B.sign);
		if (remainder->size > 0)
			free(remainder->digits);

		remainder->size = 1;
		remainder->digits = (unsigned int*)malloc((1)*sizeof(unsigned int));

		remainder->digits[0] = carry;
		*remainder = delete_zero(*remainder);
		res.sign = (A.sign != B.sign);
		res = delete_zero(res);
		free(divider.digits);
		return res;
	}

	// ������� �� �������������� �����

	long_numeric res;
	res.sign = 0;
	res.size = A.size - B.size + 1;
	res.digits = (unsigned int*)malloc((res.size)*sizeof(unsigned int));

	int i;
	for (i = A.size - B.size + 1; i != 0; i--)
	{
		long long int qGuessMax = BASIS; // ��� ����, ����� qGuessMin ����� ���� ����� BASIS - 1
		long long int qGuessMin = 0;
		long long int qGuess = qGuessMax;

		// ���� - ������ �������� ������� ����� qGuess
		while (qGuessMax - qGuessMin > 1)
		{
			qGuess = (qGuessMax + qGuessMin) / 2;

			// �������� tmp = qGuess * divider * BASIS^i;
			long_numeric qGuesslong_numeric = create_from_int(qGuess);
			long_numeric tmp = multiplication(divider, qGuesslong_numeric);
			free(qGuesslong_numeric.digits);
			tmp = shift_left(tmp, i - 1);	// �������� ����� �� (i - 1) �������� ������
			// �� ����, �� ����, ��� ��������� �� BASIS^(i - 1)

			if (compare(tmp, *remainder) > 0)
				qGuessMax = qGuess;
			else
				qGuessMin = qGuess;

			free(tmp.digits);
		}
		// tmp = qGuessMin * divider * B ^ (i - 1)
		long_numeric qGuessMinlong_numeric = create_from_int(qGuessMin);
		long_numeric tmp = multiplication(divider, qGuessMinlong_numeric);
		free(qGuessMinlong_numeric.digits);
		tmp = shift_left(tmp, i - 1);

		// remainder = remainder - tmp;
		long_numeric tmpRem = copy(*remainder);
		long_numeric minusTmp = minus(tmp);
		free(remainder->digits);
		*remainder = sum_and_sub(tmpRem, minusTmp);
		*remainder = delete_zero(*remainder);
		free(tmpRem.digits);
		free(minusTmp.digits);
		free(tmp.digits);

		res.digits[i - 1] = qGuessMin;
	}

	res.sign = (A.sign != B.sign);
	remainder->sign = (A.sign != B.sign);
	*remainder = delete_zero(*remainder);
	res = delete_zero(res);

	free(divider.digits);
	return res;
}

long_numeric involution(long_numeric base, long_numeric exp)
{
	// ���������� base � ������� exp
	// ����� ��� ������, ��� ���� ����������� ������� � ����� �� ������,
	// � � �� ��������� � ����������� �������
	long_numeric res = create_from_int(1); // ���� ����� ������� ���������
	long_numeric zero = create_from_int(0);
	long_numeric i = copy(exp); // ������� ��� ��������� ���������� �������� �� exp
	long_numeric minusOne = create_from_int(-1); // -1

	// ���� ���������� ����������� ��������� ������ ����
	while (compare(i, zero) > 0)
	{
		// res = res * base
		long_numeric tmp = multiplication(res, base);
		free(res.digits);
		res = tmp;

		// ����� ��������� ��� �������: i = i -1
		tmp = sum_and_sub(i, minusOne); // ���������� i � (-1), �.�. tmp = i - 1
		tmp = delete_zero(tmp);
		free(i.digits); // ������� ������
		i = tmp;
	}

	// ������� ������
	free(i.digits);
	free(zero.digits);
	free(minusOne.digits);

	return res;
}

long_numeric involution_module(long_numeric base, long_numeric exp, long_numeric modulus)
{
	// ���������� base � ������� exp �� ������ modulus
	// ����� ������ �� ������� ���������� � �������, 
	// ������ ����� ����� ������� ��������� ���������� ��� ����� ������� �� ������� �� modulus
	long_numeric res = create_from_int(1); // ���� ����� ������� ���������
	long_numeric zero = create_from_int(0);
	long_numeric i = copy(exp); // ������� ��� ��������� ���������� �������� �� exp
	long_numeric minusOne = create_from_int(-1); // -1

	// ���� ���������� ����������� ��������� ������ ����
	while (compare(i, zero) > 0)
	{
		// tmp = res * base
		long_numeric tmp = multiplication(res, base);

		// res = tmp % base
		long_numeric modRem; // ���� ������� ������� �� �������
		long_numeric tmp2 = dividing(tmp, modulus, &modRem);
		free(tmp2.digits);
		free(tmp.digits);
		free(res.digits);
		res = modRem;

		// ����� ��������� ��� �������: i = i -1
		tmp = sum_and_sub(i, minusOne); // ���������� i � (-1), �.�. tmp = i - 1
		tmp = delete_zero(tmp);
		free(i.digits); // ������� ������
		i = tmp;
	}

	// ������� ������
	free(i.digits);
	free(zero.digits);
	free(minusOne.digits);

	return res;
}

long_numeric read_bin_file(char* filename)
{
	// ����� �������, ��� � �������� ����� �������� ������� ����� �� ������ 256.
	// ����� �������, ����� ������� ����� �� ��������� ����� ���������� ������ ���� 
	// �������� �� 256 ^ i, ��� i - ������� ����� � ����� � �� ��� �������

	FILE* pfSource = fopen(filename, "r+b");
	if (!pfSource)
	{
		// ���� ���� �� ��������
		long_numeric res;
		res.size = 0;
		res.sign = 0;
		res.digits = NULL;
		return res;
	}

	// ������ ������ �����
	fseek(pfSource, 0, SEEK_END);
	int fileSize = ftell(pfSource);
	fseek(pfSource, 0, SEEK_SET);

	// ��������� ���������� �����
	unsigned char* fileContent = (unsigned char*)malloc(fileSize);
	fread((char*)fileContent, sizeof(unsigned char), fileSize, pfSource);
	fclose(pfSource);

	long_numeric pow256 = create_from_int(1); // ����� ����� 256 ^ i
	long_numeric res = create_from_int(0); // ����� ���������� ���������
	long_numeric b256 = create_from_int(256); // ����� 256

	// ���� ��� ���� ������ � �����
	int i;
	for (i = 0; i < fileSize; i++)
	{
		long_numeric fi = create_from_int(fileContent[i]); // �������� ��������� ���� �����

		// res = res + pow256 * fi;

		// tmp = fi * 256 ^ i
		long_numeric tmp = multiplication(fi, pow256);
		free(fi.digits);

		// tmp2 = res + tmp = res + fi * 256^i
		long_numeric tmp2 = sum_and_sub(res, tmp);
		tmp2 = delete_zero(tmp2);
		free(tmp.digits);
		free(res.digits);
		res = tmp2; // res = res + pow256 * fi;

		// pow256 = pow256*256
		tmp = multiplication(pow256, b256);
		free(pow256.digits);
		pow256 = tmp;
	}
	x[r] = fileSize;
	r++;
	free(fileContent);
	free(pow256.digits);
	free(b256.digits);

	return res;
}

int write_bin_file(char* filename, long_numeric A, bool flag, bool flag_mul, bool flag_sum, bool flag_sub)
{
	// ����� �������, ��� � �������� ���� ���������� �������� ����� �� ��������� 256
	// �� ���� ���������� ������� �� BASIS � 256 (256 - ������ ��� ������������ �������� ����� - 255)
	// ��� ����� ���� �������� ������� �� ������� �� 256
	// ���� ����� �� ����������� �� 0
	// ���������� 0 � ������ �������� ������
	// �� 0 - � ������ ������

	FILE* pfDestination = fopen(filename, "w+b");
	if (!pfDestination)
		return 1;

	struct long_numeric tmp = copy(A); // �����, ������� ����� ������ �� 256
	tmp.sign = 0; // �� ����� �������� �������� �� ����
	long_numeric zero = create_from_int(0);
	long_numeric b256 = create_from_int(256);
	unsigned int fileSize = 0;
	// ���� ����� �� ������ ������ 0
	while (compare(tmp, zero) != 0)
	{
		long_numeric remainder; // ���� ����� ������� ������� �� ������� �� 256

		// tmp = tmp / 256
		long_numeric tmp2 = dividing(tmp, b256, &remainder);
		free(tmp.digits);
		tmp = tmp2;

		// ������ � remainder ��������� ������� �� ������� �� 256
		// ������� ��� � ����
		unsigned char ost = remainder.digits[0];
		fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
		free(remainder.digits);
		fileSize++;
	}

	if (flag_sum == 1)
	{
		unsigned int love = 0;
		if (x[0] >= x[1])
			love = x[0] + 1;
		else
			love = x[1] + 1;
		for (int i = tmp.size; i <= love - fileSize; i++)
		{
			unsigned char ost = NULL;
			fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
		}
	}

	if (flag == 1)
	{
		for (int i = tmp.size; i < x[0] - x[1] - fileSize + 1; i++)
		{
			unsigned char ost = NULL;
			fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
		}
	}
	if (flag_sub == 1)
	{
		unsigned int love = 0;
		if (x[0] >= x[1])
			love = x[0];
		else
			love = x[1];
		for (int i = tmp.size; i <= love - fileSize; i++)
		{
			unsigned char ost = NULL;
			fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
		}
	}

	if (flag_mul == 1)
	{
		for (int i = tmp.size; i < x[0] + x[1] - fileSize + 1; i++)
		{
			unsigned char ost = NULL;
			fwrite((char*)&ost, sizeof(unsigned char), 1, pfDestination);
		}
	}

	free(tmp.digits);
	free(b256.digits);
	free(zero.digits);

	fclose(pfDestination);
	return 0;
}

long_numeric read_file(char *fileName)
{
	FILE *fp = fopen(fileName, "r");
	if (!fp)
	{
		// ���� ���� �� ��������
		long_numeric res;
		res.size = 0;
		res.sign = 0;
		res.digits = NULL;
		return res;
	}

	// ������ ������ �����
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// ��������� ���������� �����
	char* fileContent = (char*)malloc(fileSize + 1);
	fscanf(fp, "%s", fileContent);
	fileContent[fileSize] = '\0';
	fclose(fp);
	long_numeric res = create_from_string(fileContent);
	free(fileContent);
	return res;
}

int write_file(char *fileName, long_numeric A)
{
	FILE *fp = fopen(fileName, "w");
	if (!fp)
		return 1;

	char *res = get_string(A);

	fprintf(fp, "%s", res);
	fclose(fp);
	free(res);

	return 0;
}
