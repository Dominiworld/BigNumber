#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "2.h"



int main(int argc, char * argv[])
{
printf("HEYEE!");
	setlocale(LC_ALL, "Rus");


	LONG a;
	LONG b;
	LONG res;
	LONG m;
	LONG ost;


	if (argc < 5 || argc > 7)
	{
		printf("�������� ������ ������!");
		printf("�������� ��������: file1 operation(+, -, / , m, %) file2 resultfile [-b]");
		printf("���������� � ������� �� ������: file1 file2 p file3 resultfile [-b]");
		getchar();
		return 0;
	}

	if (argv[argc - 1][1] == 'b' && argv[argc - 1][0] == '-')
	{
		a.FromBinFile(argv[1]);
		if (a.IsEmpty())
		{
			a.Kill();
			return 0;
		}
printf("size(a)=%llu", a.number.size);

		b.FromBinFile(argv[3]);

printf("size(b)=%llu", b.number.size);
		if (b.IsEmpty())
		{
			b.Kill();
			return 0;
		}


		if (argv[2][0] == 'p')
		{
			m.FromBinFile(argv[4]);
			if (m.IsEmpty())
			{
				m.Kill();
				return 0;
			}
		}
	}
	else
	{
printf("HEY!");
		a.FromTextFile(argv[1]);

printf("size(a)=%llu!", a.number.size);


		if (a.IsEmpty())
		{
printf("AisEMPTY!");
			a.Kill();
			return 0;
		}
printf("I'm HERE!");

		b.FromTextFile(argv[3]);

printf("size(b)=%llu!", b.number.size);


		if (b.IsEmpty())
		{
printf("BisEMPTY!");
			b.Kill();
			return 0;
		}

printf("BandARead");

		if (argv[2][0] == 'p')
		{
printf("ReadAll");
			m.FromTextFile(argv[4]);
			if (m.IsEmpty())
			{
				m.Kill();
				return 0;
			}

		}
	}

	if (strlen(argv[2]) != 1)
	{
		printf("������ �����. �������� - ���� ������!");
		return 0;
	}
	else
	{
		switch (argv[2][0]) //��������
		{
		case '+':
printf("HEE!!");
			res = a + b;
//res = a.PowMod(b,b);
			
			break;

		case '-': res = a - b;
			break;

		case 'm': res = a*b;
			break;

		case '/': res = a / b;
			break;

		case '%':
printf("HELLO!");
			res = a%b;
			break;

		case 'p':
			
			res = a.PowMod(b, m);
printf("!!F");

			break;

		default:

			printf("�������� ��������.\n '+' - �������� \n '-' - ���������\n 'm' - ���������\n '/' - �������\n 'p' - ���������� � ������� �� ������");
			return 0;
			break;
		}
	}

	if (argv[argc - 1][1] == 'b' && argv[argc - 1][0] == '-')
	{
		int k = 4;
		if (argv[2][0] == 'p')
		{
			k = 5;
		}
		if (k < argc)
		{

			if (!res.ToBinFile(argv[k]))
			{
				return 0;
			}
		}
		else
		{
			printf("�������� ������ ������!");
			return 0;
		}
	}
	else
	{

		int k = 4;
		if (argv[2][0] == 'p')
		{

			k = 5;
		}
		if (k < argc)
		{
			if (!res.ToTextFile(argv[k]))
			{
				return 0;
			}
		}
		else
		{
			printf("�������� ������ ������!");
			return 0;
		}
	}

	printf("�������� ��������� �������");

	return 0;
}
