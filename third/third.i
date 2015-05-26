%module third
%{
#include "second.h"
%}

class  BIGNUMBER {
public:
	BIGNUMBER();
	~BIGNUMBER();
	BIGNUMBER(unsigned long long);
	BIGNUMBER(char*);
	BIGNUMBER (const BigNumber& t);
	BIGNUMBER(const BIGNUMBER& t); //copy constructor
	const BIGNUMBER operator=(const BIGNUMBER&);
	const BIGNUMBER operator+(const BIGNUMBER&);
	const BIGNUMBER operator-(const BIGNUMBER&);
	const BIGNUMBER operator*(const BIGNUMBER&);
	const BIGNUMBER operator/(const BIGNUMBER&);
	const BIGNUMBER operator%(const BIGNUMBER&);
	const BIGNUMBER operator+(const unsigned long long&);
	const BIGNUMBER operator-(const unsigned long long&);
	const BIGNUMBER operator/(const unsigned long long&);
	const BIGNUMBER operator*(const unsigned long long&);
	const unsigned long long operator%(const unsigned long long&);
	bool operator>(const BIGNUMBER&);
	bool operator<(const BIGNUMBER&);
	bool operator==(const BIGNUMBER&);
	bool operator<=(const BIGNUMBER&);
	bool operator>=(const BIGNUMBER&);
	bool operator>(const unsigned long long&);
	bool operator<(const unsigned long long&);
	bool operator==(const unsigned long long&);
	bool operator<=(const unsigned long long&);
	bool operator>=(const unsigned long long&);
	const BIGNUMBER PowMod(const BIGNUMBER& pow, const BIGNUMBER& mod);
	const BIGNUMBER PowMod(const unsigned long long& pow, const BIGNUMBER& mod);
	const BIGNUMBER PowMod(const unsigned long long& pow, const unsigned long long& mod);
	void ReadText(char* file);
	void ReadBin(char* file);
	bool WriteBin(char* file);
	bool WriteText(char* file);
	char* Print();
private:
	BigNumber number;
	void FreeMem();
};

%extend BIGNUMBER
{
	const char* __str__()
	{
    	 return self->Print();
	}
	const char* __repr__()
	{
     	return self->Print();
	}	
};
