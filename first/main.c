#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "first.h"

void Error()
{
	printf("Incorrect input");
	printf("Input format: Filename1 Operation(+,-,/,%%,m) Filename2 Result");
	printf("or");
	printf("Filename1 ^ Filename2 Modul Result");
	printf("Add -b if files are binary");
}

int main(int argc, char * argv[])
{

	if (argc < 5 || argc > 7)
	{
		Error();
		return 0;
	}

	BigNumber a;
	BigNumber b;
	BigNumber res;
	BigNumber mod;
	BigNumber ost;

	char* name_a = argv[1];
	char* name_res;
	char* operation = argv[2];
	char* name_b = argv[3];
	char* name_mod;

	if (operation == "^")
	{

		name_mod = argv[4];
		if (argc > 5 && argv[5] != "-b")
			name_res = argv[5];

		else
		{
			Error();
			return 0;
		}
	}
	else
	{
		name_mod = 0;
		name_res = argv[4];
	}

	if (argv[-1] == "-b")
	{
		a = ReadBinFile(name_a);
		b = ReadBinFile(name_b);
		if (name_mod != 0)
		{
			mod = ReadBinFile(name_mod);
		}

		else
		{
			a = ReadTextFile(name_a);
			b = ReadTextFile(name_b);
			if (name_mod != 0)
			{
				mod = ReadTextFile(name_mod);
			}
		}


		if (operation == "+")
		{
			res = Sum(a, b);
		}
		if (operation == "-")
		{
			res = Sub(a, b);
		}
		if (operation == "m")
		{
			res = Mul (a, b);
		}
		if (operation == "/")
		{
			res = Divide(a, b, &mod);
			FreeMemory(&res);
		}
		if (operation == "%")
		{
			mod = Divide(a, b, &res);
			FreeMemory(&mod);
		}
		if (operation == "^")
		{
			res = Pow(a, b, mod);
		}


		if (argv[-1] == "-b")
		{
			WriteBinFile(name_res, res);
		}
		else
		{
			WriteTextFile(name_res, res);
		}
	}
}
