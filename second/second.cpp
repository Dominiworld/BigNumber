#include "stdio.h"
#include "second.h"


BIGNUMBER::BIGNUMBER(){ 
    this->number.block = NULL;
    this->number.size = 0;
}

BIGNUMBER::~BIGNUMBER(){
    printf("Уничтожаем \"%s\" указатель %llu\n", this->Print(), this->number.block);
    if(this->number.block != NULL){
    	FreeMem();}
};

BIGNUMBER::BIGNUMBER(unsigned long long t)
{
	MemoryAllocation(&(this->number), 1);
	this->number.block[0]=t;
}

BIGNUMBER::BIGNUMBER(const BigNumber& t)
{
	number = Copy(t);
}

BIGNUMBER::BIGNUMBER(const BIGNUMBER& t)
{
	this->number = Copy(t.number);
}

BIGNUMBER::BIGNUMBER(char* str)
{
	this->number = ReadFromString(str);
}

const BIGNUMBER BIGNUMBER::operator=(const BIGNUMBER& right)
{
	this->number = Copy(right.number);
	return *this;
}

const BIGNUMBER BIGNUMBER::operator+(const BIGNUMBER& t)
{
	return BIGNUMBER(Sum(this->number, t.number));
}

const BIGNUMBER BIGNUMBER::operator-(const BIGNUMBER& t)
{
	return BIGNUMBER(Sub(this->number, t.number));
}


const BIGNUMBER BIGNUMBER::operator*(const BIGNUMBER& t)
{
	return BIGNUMBER(Mul(this->number, t.number));
}

const BIGNUMBER BIGNUMBER::operator/(const BIGNUMBER& t)
{
	BigNumber ost;
	BIGNUMBER res;
	res.number = Divide(this->number, t.number, &ost);
	FreeMemory(&ost);
	return res;
}

const BIGNUMBER BIGNUMBER::operator%(const BIGNUMBER& t)
{
	BigNumber ost;
	BigNumber res = Divide(this->number, t.number, &ost);
	FreeMemory(&res);
	return BIGNUMBER(ost);
}

const BIGNUMBER BIGNUMBER::operator+(const unsigned long long& t)
{
	return BIGNUMBER(Sum(this->number, BIGNUMBER(t).number));
}

const BIGNUMBER BIGNUMBER::operator-(const unsigned long long& t)
{
	return BIGNUMBER(Sub(this->number, BIGNUMBER(t).number));
}

const BIGNUMBER BIGNUMBER::operator*(const unsigned long long& t)
{
	return BIGNUMBER(ShortMul(this->number, t));
}

const BIGNUMBER BIGNUMBER::operator/(const unsigned long long& t)
{
	unsigned long long ost;
	return BIGNUMBER(ShortDivide(this->number, t, &ost));
}

const unsigned long long BIGNUMBER::operator%(const unsigned long long& t)
{
	unsigned long long ost;
	BIGNUMBER res = BIGNUMBER(ShortDivide(this->number, t, &ost));
	return ost;
}

bool BIGNUMBER::operator>(const BIGNUMBER& t)
{
	return Compare(this->number, t.number) == 1;
}


bool BIGNUMBER::operator>(const unsigned long long& t)
{
	return ShortCompare(this->number, t) == 1;
}

bool BIGNUMBER::operator<(const BIGNUMBER& t)
{
	return Compare(this->number, t.number) == -1;
}
bool BIGNUMBER::operator<(const unsigned long long& t)
{
	return ShortCompare(this->number, t) == -1;
}

bool BIGNUMBER::operator==(const BIGNUMBER& t)
{
	return Compare(this->number, t.number) == 0;
}

bool BIGNUMBER::operator==(const unsigned long long& t)
{
	return ShortCompare(this->number, t) == 0;
}

bool BIGNUMBER::operator>=(const BIGNUMBER& t)
{
	return Compare(this->number, t.number) != -1;
}

bool BIGNUMBER::operator>=(const unsigned long long& t)
{
	return ShortCompare(this->number, t) != -1;
}

bool BIGNUMBER::operator<=(const BIGNUMBER& t)
{
	return Compare(this->number, t.number) != 1;
}

bool BIGNUMBER::operator<=(const unsigned long long& t)
{
	return ShortCompare(this->number, t) != 1;
}

const BIGNUMBER BIGNUMBER::PowMod(const BIGNUMBER& pow,const BIGNUMBER& mod)
{
	return BIGNUMBER(Pow(this->number, pow.number, mod.number));
}

const BIGNUMBER BIGNUMBER::PowMod(const unsigned long long& pow,const BIGNUMBER& mod)
{
	return BIGNUMBER(Pow(this->number, BIGNUMBER(pow).number, mod.number));
}

const BIGNUMBER BIGNUMBER::PowMod(const unsigned long long& pow, const unsigned long long& mod)
{
	return BIGNUMBER(ShortPow(this->number, BIGNUMBER(pow).number, mod));
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
	*this = BIGNUMBER(ReadTextFile(file));	
}
void BIGNUMBER::ReadBin(char* file)
{
	*this = BIGNUMBER(ReadBinFile(file));	
}
void BIGNUMBER::FreeMem()
{
	FreeMemory(&(this->number));
	this->number.block = NULL;
}

char* BIGNUMBER::Print()
{
  return toString(this->number);
}
