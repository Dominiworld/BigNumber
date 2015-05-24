#include <stdio.h>
#include <stdlib.h> 
#include <memory.h>
#include <string.h>
#include "first.h"

void MemoryAllocation(BigNumber *a, unsigned long long size)
{
	a->block = (unsigned long long*)malloc(sizeof(unsigned long long)*size);
	a->size = size;
	memset(a->block, 0, sizeof(unsigned long long)*(a->size));
}

BigNumber Copy(BigNumber a)
{
	BigNumber res;
	MemoryAllocation(&res, a.size);
	for (int i = 0; i < res.size; i++)
	{
		res.block[i] = a.block[i];
	}
}

void FreeMemory(BigNumber *a)
{
	free(a->block);
}

BigNumber Sum(BigNumber a, BigNumber b)//Числа в кусочно обратной последовательности в массивах 
{
	BigNumber result;
	BigNumber tmp;
	if (a.size >= b.size)
	{
		MemoryAllocation(&result,a.size + 1);
		for (int i = 0; i < a.size; i++)
		{
			result.block[i] = a.block[i];
		}
		MemoryAllocation(&tmp,b.size);
		tmp.block = b.block;
	}
	else
	{
		MemoryAllocation(&result,b.size + 1);
		for (int i = 0; i < b.size; i++)
		{
			result.block[i] = b.block[i];
		}
		MemoryAllocation(&tmp,a.size);
		tmp.block = a.block;
	}
	asm(	"clc\n"
		"pushf\n"
		"movq %0, %%rsi\n"
		"movq %1, %%rdi\n"
		"movq %2, %%rcx\n"
	"m : movq (%%rsi),%%rax\n"
		"popf\n"
		"adcq (%%rdi), %%rax\n"
		"pushf\n"
		"movq %%rax, (%%rsi)\n"
		"addq $8,%%rsi\n"
		"addq $8,%%rdi\n"
		"loop m\n"

		"movq (%%rsi),%%rax \n"
		"popf\n"
		"adcq $0,%%rax\n"
		"movq %%rax, (%%rsi)\n"
		:
		:"r"(result.block), "r"(tmp.block), "r"(tmp.size)
		: "rsi", "rdi", "rcx", "rax"
	);
	return Normalize(&result);//Возможен старший нулевой блок. Так он уберется
}

BigNumber Sub(BigNumber a, BigNumber b)
{
	BigNumber result;
	BigNumber tmp;
	if (a.size >= b.size)
	{
		MemoryAllocation(&result,a.size + 1);
		for (int i = 0; i < a.size; i++)
		{
			result.block[i] = a.block[i];
		}
		MemoryAllocation(&tmp,b.size);
		tmp.block = b.block;
	}
	else
	{
		MemoryAllocation(&result,b.size + 1);
		for (int i = 0; i < b.size; i++)  
		{
			result.block[i] = b.block[i];
		}
		MemoryAllocation(&tmp,a.size);
		tmp.block = a.block;
	}
	asm
	(
			"clc\n"
			"pushf\n"
			"movq %0, %%rsi\n"
			"movq %1, %%rdi\n"
			"movq %2, %%rcx\n"
			"mm : movq (%%rsi), %%rax\n"
			"popf\n"
			"sbbq  (%%rdi), %%rax\n"
			"pushf\n"
			"movq %%rax,(%%rsi)\n"
			"addq $8,%%rsi\n"
			"addq $8,%%rdi\n"
			"loop mm\n"

			"movq (%%rsi),%%rax \n"
			"popf\n"
			"sbbq $0,%%rax\n"
		:
		:"r"(result.block), "r"(tmp.block), "r"(tmp.size)
		: "rsi", "rdi", "rcx", "rax"
	);

		return Normalize(&result);//Возможен старший нулевой блок. Так он уберется
}


BigNumber Mul(BigNumber a, BigNumber b)
{
	BigNumber result;
	MemoryAllocation(&result, a.size + b.size);
		
asm("movq %0, %%rsi\n"
	"movq %1, %%rbx\n"
	"movq %2, %%rcx\n"
	"gnom: mov %3, %%rdi\n"
	"push %%rcx\n"
	"movq %4, %%rcx\n"
	"push %%rbx\n"
	"h: movq (%%rsi), %%rax\n"
	"mulq (%%rdi)\n"
	"addq %%rax, (%%rbx)\n"
	"adcq %%rdx, 8(%%rbx)\n"
	"push %%rbx\n"
	"h1:pushf\n"
	"addq $8, %%rbx\n"
	"popf\n"
	"adcq $0, 8(%%rbx)\n"
	"jc h1\n"
	"pop %%rbx\n"
	"addq $8, %%rdi\n"
	"addq $8, %%rbx\n"
	"loop h\n"
	"addq $8, %%rsi\n"
	"pop %%rbx\n"
	"addq $8, %%rbx\n"
	"pop %%rcx\n"
	"loop gnom\n"
	:
	:"r"(a.block), "r"(result.block), "r"(a.size), "r"(b.block), "r"(b.size)
	:"rax", "rbx", "rsi", "rdi", "rcx", "rdx");

	return Normalize(&result);
}
BigNumber Divide(BigNumber a, BigNumber b, BigNumber *mod)
{
	BigNumber null;
	MemoryAllocation(&null,1);

	if (b.block[b.size-1] == 0)
	{
		printf("Деление на ноль!");
		return null;
	}
	if (Compare(a, b)==-1)
	{
		*mod = Copy(a);
		return null;
	}
	
	BigNumber result;
	MemoryAllocation(&result, a.size - b.size + 1);

	BigNumber A;
	A = Copy(a);

	for (int i = result.size; i != 0; i--)
	{
		unsigned long long Max = 18446744073709551615LLU, Min = 0, Mid;

		Mid = Max;

		while (Max - Min > 1)
		{
			Mid = Max/2 + Min/2;//Возможна потеря 1. Не значащая, по идее

			BigNumber tmp = ShortMul(b, Mid);
			tmp = shiftLeft(&tmp, i - 1);

			if (Compare(tmp, A) == 1)
				Max = Mid;
			else
				Min = Mid;

			FreeMemory(&tmp);
		}

		BigNumber tmp = ShortMul(b, Min);
		tmp = shiftLeft(&tmp, i - 1);

		A = Sub(A, tmp);

		FreeMemory(&tmp);

		result.block[i - 1] = Min;
	}

	*mod = Normalize(&A);

	return result;
}
BigNumber Pow(BigNumber a, BigNumber p, BigNumber m)
{

	BigNumber result;
	MemoryAllocation(&result, m.size);
	result.block[0] = 1;

	BigNumber tmp;
	BigNumber tmp1;
	unsigned long long ost;

	BigNumber A;
	A = Copy(a);

	if (Compare(A, m) != -1)
	{
		tmp = Divide(A, m, &A);
		FreeMemory(&tmp);		
	}
	
	BigNumber pow;
	pow = Copy(p);

	for (int i = 0; i < result.size; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			if((pow.block[i] % 2) !=0)
			{
				tmp = Mul(result, A);
				tmp1 = Divide(tmp, m, &result);
				FreeMemory(&tmp1);
				FreeMemory(&tmp);
			}
			tmp = Mul(A, A);
			tmp1 = Divide(tmp,m,&A);
			FreeMemory(&tmp1);
			FreeMemory(&tmp);
			pow.block[i]/=2;	
		}
	}

	return Normalize(&result);
}
int Compare(BigNumber a, BigNumber b) //-1:a<b 1:a>b 0:a=b 
{
	if (a.size<b.size)
	{
		return -1;
	}
	if ((a.size > b.size))
	{
		return 1;
	}

	for (int i = a.size - 1; i > -1; i--)
	{
		if (a.block[i] > b.block[i])
		{
			return 1;
		}
		else if (a.block[i] < b.block[i])
		{
			return -1;
		}
	}
	return 0;
}

BigNumber ShortMul(BigNumber a, unsigned long long b)
{
	BigNumber result;
	MemoryAllocation(&result, a.size + 1);
	asm(
		"movq %0, %%rsi\n"
		"movq %1, %%rcx\n"
		"movq %2, %%rbx\n"
		"mt : movq (%%rsi), %%rax\n"
		"mulq %3\n"
		"addq %%rax, (%%rbx)\n"
		"adcq %%rdx, 8(%%rbx)\n"
		"adcq $0, 16(%%rbx)\n"
		"addq $8, %%rsi\n"
		"addq $8, %%rbx\n"
		"loop mt\n"
		:
		: "r"(a.block), "r"(a.size), "r"(result.block), "r"(b)
		: "rsi", "rcx", "rbx", "rax", "edx"
		);

		return Normalize(&result);
}

BigNumber ShortDivide(BigNumber a, unsigned long long b, unsigned long long *ost)
{
	BigNumber result;
	if (!b)
	{
		printf("Division by zero!");
		MemoryAllocation(&result, 1);
		ost = 0;
		result.size = 0;
		return result;
	}

	if (ShortCompare(a, b) == -1)
	{
		*ost = a.block[0];
		MemoryAllocation(&result, 1);
		return result;
	}

	MemoryAllocation(&result, a.size);

	unsigned long long s = (a.size - 1)*sizeof(unsigned long long);
	unsigned long long k = 0;
	BigNumber A;
	A = Copy(a);
	

	asm(
		"movq %1, %%rsi\n"
		"addq %2, %%rsi\n"
		"movq %3, %%rdi\n"
		"addq %2, %%rdi\n"
		"movq %4, %%rcx\n"
		"xor %%rdx, %%rdx\n"
		"m6 : movq (%%rsi), %%rax\n"
		"divq %5\n"
		"movq  %%rax, (%%rdi)\n"
		"subq $8, %%rsi\n"
		"subq  $8, %%rdi\n"
		"loop m6\n"
		"movq  %%rdx, %0\n"
		:"=r"(k)
		: "r"(A.block), "r"(s), "r"(result.block), "r"(A.size), "r"(b)
		: "rsi", "rdi", "rcx", "rdx", "rax"
		);

	*ost = k;
	return Normalize(&result);
}

int ShortCompare(BigNumber a, unsigned long long b)
{
	if (a.size > 1) return 1;
	if (a.size == 0) return -1;
	if (a.block[0] > b) return 1;
	if (a.block[0] < b) return -1;
	return 0;
}

BigNumber shiftLeft(BigNumber *a, unsigned long long i)
{
	BigNumber a1;

	MemoryAllocation(&a1, a->size + i);

	for (int j = i; j < a->size + i; j++)
		a1.block[j] = a->block[j - i];

	FreeMemory(a);
	return a1;
}
BigNumber Normalize(BigNumber *a)
{	
	while (a->block[a->size - 1] == 0) 
	{
		a->size--;
	}

	if (a->size == 0) a->size = 1;

	BigNumber result;
	result = Copy(*a);

	FreeMemory(a);

	return result;
}

int WriteBinFile(char* file, BigNumber number)
{
	FILE* out;

	if ((out = fopen(file,"wb")) != NULL)
	{
		for (int i = number.size - 1; i > -1; i--)
		{
			fwrite(&number.block[i], sizeof(unsigned long long*), 1, out);
		}
		fclose(out);
		return 1;
	}
	
		printf("Can't open file %s!", file);
		return 0;
}

BigNumber ReadTextFile(char* file) 
{
	FILE* in;
	
	int size = 0;
	
	BigNumber result;
	MemoryAllocation(&result, 1);

	if ((in = fopen(file, "r")) != NULL)
	{		
		while (fgetc(in) != EOF)
		{
			size++;
		}
		if (size == 0)
		{
			MemoryAllocation(&result, 1);
			result.size = 0;
			return result;
		}

		BigNumber k;
		MemoryAllocation(&k, 1);
		k.block[0] = 1;
		
		BigNumber tmp1;

		unsigned long long tmp = 0;
		unsigned long long ost = 0;
		char ch;
		int offset = -1;

		BigNumber tmp2;

		fseek(in, offset, SEEK_END);

		while (offset!=-size-1)
		{
			ch = fgetc(in);
			if ((ch > '9') || (ch < '0'))
			{
				printf("File %s contains not only numbers!", file);
				result.size = 0;
				return result;
			}

			tmp = ch - '0';			
			tmp1 = ShortMul(k, tmp);
			tmp2 = Normalize(&tmp1);
			result = Sum(result, tmp2);
			FreeMemory(&tmp2);
			k = ShortMul(k,10);
			offset--;
			fseek(in, offset, SEEK_END);
		}	
		fclose(in);
		FreeMemory(&k);
	}
	else
	{

		printf("Can't open file %s!", file);
		result.size = 0;
	}


	return result;
}
int WriteTextFile(char* file, BigNumber number)
{
	FILE* out;

	if ((out = fopen(file, "w")) != NULL)
	{
		char* str = toString(number);	
		
		if(fputs(str, out)==EOF)
		{
			printf("Error by writing file %s", file);
			return 0;
		}

		fclose(out);
		return 1;
	}

	printf("Error by opening file %s!", file);
	return 0;

} 
BigNumber ReadBinFile(char* file)
{
	FILE* in;
	BigNumber number;
	int size = 0;
	
	if ((in = fopen(file, "rb")) != NULL)
	{
		while (fgetc(in) != EOF)
		{
			size++;
		}

		if (size == 0)
		{
			printf("File %s is empty!", file);
			MemoryAllocation(&number, 1);
			number.size = 0;
			return number;
		}

		MemoryAllocation(&number,(size - 1) / sizeof(unsigned long long) + 1);

		fseek(in, 0, 0);

		for (int i = number.size - 1; i >-1; i--)
		{
			fread(&number.block[i], sizeof(unsigned long long), 1, in);
		}

		fclose(in);
	}
	else
	{
		printf("Can't open file %s!", file);
		MemoryAllocation(&number, 1);
		number.size = 0;
	}
	return number;
}


char* toString(BigNumber number)
{
	BigNumber numcopy;
	numcopy = Copy(number);

	BigNumber tmp;

	unsigned long long ost;
	unsigned long long k = 1;

	if(ShortCompare(number,0)==0)
		return "0";	

	FILE* stream;

	if ((stream = tmpfile())==NULL)
	
	{
		printf("Temporary file wasn't created!");
		return "";
	}

	unsigned long long size = 0;

	while (ShortCompare(numcopy, 0) == 1)
	{
		tmp = numcopy;
		numcopy = ShortDivide(numcopy, 10000000000000000000ULL, &ost);
		FreeMemory(&tmp);

		char buffer[] = "0000000000000000000";
		int k = 18;
		while (ost > 0)
		{
			buffer[k--] = ost % 10 + '0';
			ost /= 10;	
		}
		fprintf(stream, "%s", buffer);
		size++;        
	}


	FreeMemory(&numcopy);

	long long offset = -19;

	fseek(stream, offset, SEEK_END);

	char* str = (char*)malloc(sizeof(char)*(size+1)*19);

	memset(str, '\0', (size+1)*19);

	char tmps [19];	
	fgets(tmps, 20, stream);
	int count = 0;
	while(tmps[count]=='0')
		count++;
	int s = 19-count;
	char sss[19];
	memset(sss, '\0', 19);
	int i = 0;
	while(i!=s)
		sss[i++]=tmps[count++];
	strcat(str,sss);
	offset-=19;
	fseek(stream, offset, SEEK_END);

	while(offset>-(size+1)*19)
	{
		fgets(tmps, 20, stream);
		strcat(str, tmps);
		offset-=19;
		fseek(stream, offset, SEEK_END);
	}


	fclose(stream);
	

	return str;
}	

BigNumber ReadFromString(char* buffer)
{
	int size = 0;
	
	BigNumber res;
	MemoryAllocation(&res, 1);

	if (buffer == NULL)
	{
		printf("Error by reading string!");
		res.size = 0;
		return res;
	}
	
	if (strlen(buffer) == 0)
	{
		res.size = 0;
		return res;
	}
	
	BigNumber k;
	MemoryAllocation(&k,1);
	k.block[0] = 1;
		
	BigNumber tmp1;
	BigNumber tmp2;

	unsigned long long tmp = 0;
	char ch;

	for (int i = strlen(buffer)-1; i>-1; i--)
	{
	        ch = buffer[i];
		if ((ch > '9') || (ch < '0'))
		{
			printf("Incorrect input!");
			res.size = 0;
			return res;
		}
		tmp = ch - '0';			
		tmp1 = ShortMul(k, tmp);
		tmp2 = Normalize(&tmp1);
		res = Sum(res, tmp2);
		FreeMemory(&tmp2);
		k = ShortMul(k,10);
	}
	
	FreeMemory(&k);
	return res;
}
