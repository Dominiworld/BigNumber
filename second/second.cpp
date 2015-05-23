#include "stdio.h"
#include "second.h"


BIGNUMBER::BIGNUMBER(){ this->number.size = 0;}

BIGNUMBER::BIGNUMBER(unsigned long long t)
{
	BIGNUMBER res;
	MemoryAllocation(&res.number,1);
	res.number.block[0]=t;
	this->number = res.number;
}

BIGNUMBER::BIGNUMBER(char* str)
{
	BIGNUMBER res;
	res.number = ReadFromString(str);
	this->number = res.number;
}


BIGNUMBER BIGNUMBER::operator+(BIGNUMBER t)
{
	BIGNUMBER res;
	res.number = Sum(this->number, t.number);
	return res;
}

BIGNUMBER BIGNUMBER::operator-(BIGNUMBER t)
{
	BIGNUMBER res;
	res.number = Sub(this->number, t.number);
	return res;
}


BIGNUMBER BIGNUMBER::operator*(BIGNUMBER t)
{
	BIGNUMBER res;
	res.number = Mul(this->number, t.number);
	return res;
}

BIGNUMBER BIGNUMBER::operator/(BIGNUMBER t)
{
	BigNumber ost;
	BIGNUMBER res;
	res.number = Divide(this->number, t.number, &ost);
	FreeMemory(&ost);
	return res;
}

BIGNUMBER BIGNUMBER::operator%(BIGNUMBER t)
{
	BigNumber ost;
	BigNumber res = Divide(this->number, t.number, &ost);
	FreeMemory(&res);
	BIGNUMBER result;
	result.number = ost;
	return result;
}

BIGNUMBER BIGNUMBER::operator+(unsigned long long t)
{
	BIGNUMBER res;
	BIGNUMBER right;
	MemoryAllocation(&right.number, 1);
	right.number.block[0] = t;
	res.number = Sum(this->number, right.number);
	return res;
}

BIGNUMBER BIGNUMBER::operator-(unsigned long long t)
{
	BIGNUMBER res;
	BIGNUMBER right;
	MemoryAllocation(&right.number, 1);
	right.number.block[0] = t;
	res.number = Sub(this->number, right.number);
	return res;
}


BIGNUMBER BIGNUMBER::operator*(unsigned long long t)
{
	BIGNUMBER res;
	res.number = ShortMul(this->number, t);
	return res;
}

BIGNUMBER BIGNUMBER::operator/(unsigned long long t)
{
	unsigned long long ost;
	BIGNUMBER res;
	res.number = ShortDivide(this->number, t, &ost);
	return res;
}

unsigned long long BIGNUMBER::operator%(unsigned long long t)
{
	unsigned long long ost;
	BIGNUMBER res;
	res.number = ShortDivide(this->number, t, &ost);
	res.FreeMem();
	return ost;
}

bool BIGNUMBER::operator>(BIGNUMBER t)
{
	return Compare(this->number, t.number) == 1;
}


bool BIGNUMBER::operator>(unsigned long long t)
{
	return ShortCompare(this->number, t) == 1;
}

bool BIGNUMBER::operator<(BIGNUMBER t)
{
	return Compare(this->number, t.number) == -1;
}
bool BIGNUMBER::operator<(unsigned long long t)
{
	return ShortCompare(this->number, t) == -1;
}

bool BIGNUMBER::operator==(BIGNUMBER t)
{
	return Compare(this->number, t.number) == 0;
}

bool BIGNUMBER::operator==(unsigned long long t)
{
	return ShortCompare(this->number, t) == 0;
}

bool BIGNUMBER::operator>=(BIGNUMBER t)
{
	return Compare(this->number, t.number) != -1;
}

bool BIGNUMBER::operator>=(unsigned long long t)
{
	return ShortCompare(this->number, t) != -1;
}

bool BIGNUMBER::operator<=(BIGNUMBER t)
{
	return Compare(this->number, t.number) != 1;
}

bool BIGNUMBER::operator<=(unsigned long long t)
{
	return ShortCompare(this->number, t) != 1;
}

BIGNUMBER BIGNUMBER::PowMod(BIGNUMBER pow, BIGNUMBER mod)
{
	BIGNUMBER res;
	res.number = Pow(this->number, pow.number, mod.number);
	return res;
}

BIGNUMBER BIGNUMBER::PowMod(unsigned long long pow, BIGNUMBER mod)
{
	BIGNUMBER res;
	BIGNUMBER p;
	MemoryAllocation(&p.number,1);
	p.number.block[0]=pow;
	res.number = Pow(this->number, p.number, mod.number);
	p.FreeMem();
	return res;
}

BIGNUMBER BIGNUMBER::PowMod(unsigned long long pow, unsigned long long mod)
{
	BIGNUMBER res;
	BIGNUMBER p;
	MemoryAllocation(&p.number,1);
	p.number.block[0]=pow;
	BIGNUMBER m;
	MemoryAllocation(&m.number,1);
	m.number.block[0]=mod;
	res.number = Pow(this->number, p.number, m.number);
	p.FreeMem();
	m.FreeMem();
	return res;
}

bool BIGNUMBER::WriteBin(char* file)
{
	return WriteBinFile(file, this->number)==1;
}

bool BIGNUMBER::WriteText(char* file)
{
	return WriteTextFile(file, this->number)==1;
}
void BIGNUMBER::ReadText(char* file)
{
	BIGNUMBER res;
	res.number = ReadTextFile(file);

	*this = res;	
}
void BIGNUMBER::ReadBin(char* file)
{
	BIGNUMBER res;
	res.number = ReadBinFile(file);
	*this = res;
}
void BIGNUMBER::FreeMem()
{
	BigNumber t = this->number;
	FreeMemory(&t);
}

char* BIGNUMBER::Print()
{
  return toString(this->number);
}
