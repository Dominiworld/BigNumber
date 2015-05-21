#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "second.h"

void Error()
{
	printf("Incorrect input");
	printf("Input format: Filename1 Operation(+,-,/,%,m) Filename2 Result");
	printf("or");
	printf("Filename1 ^ Filename2 Modul Result");
	printf ("Add -b if files are binary");
}

int main(int argc, char * argv[])
{


	if (argc < 5 || argc > 7)
	{
		Error();
		return 0;
	}

	BIGNUMBER a;
	BIGNUMBER b;
	BIGNUMBER res;
	BIGNUMBER mod;
	BIGNUMBER ost;

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
		a.ReadBin(name_a);
		b.ReadBin(name_b);

		if (name_mod != 0)
		{
			mod.ReadBin(name_mod);
		}

		else
		{
			a.ReadText(name_a);
			b.ReadText(name_b);

			if (name_mod != 0)
			{
				mod.ReadText(name_mod);
			}
		}


		if (operation == "+")
		{
			res = a + b;
		}
		if (operation == "-")
		{
			res = a - b;
		}
		if (operation == "m")
		{
			res = a * b;
		}
		if (operation == "/")
		{
			res = a / b;
		}
		if (operation == "%")
		{
			res = a % b;
		}
		if (operation == "^")
		{
			res = a.PowMod(b, mod);
		}

		if (argv[-1] == "-b")
		{
			res.WriteBin(name_res);
		}
		else 
		{
			res.WriteText(name_res);
		}

}
}
