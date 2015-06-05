typedef struct //Ìëàäøàÿ ÷àñòü â 0 áëîêå
{
	unsigned long long* block;
	unsigned long long size;
}BigNumber;

void MemoryAllocation(BigNumber *a, unsigned long long size);
void FreeMemory(BigNumber *a);
BigNumber Copy(BigNumber a);

BigNumber Sum(BigNumber a, BigNumber b);
BigNumber Sub(BigNumber a, BigNumber b);
BigNumber Mul(BigNumber a, BigNumber b);
BigNumber Divide(BigNumber a, BigNumber b, BigNumber *mod);
BigNumber Pow(BigNumber a, BigNumber p, BigNumber m);
unsigned long long ShortPow(BigNumber a, BigNumber p, unsigned long long m);
int Compare(BigNumber a, BigNumber b);
BigNumber Normalize(BigNumber *a);

BigNumber ShortMul(BigNumber a, unsigned long long b);
BigNumber ShortDivide(BigNumber a, unsigned long long b, unsigned long long *ost);
int ShortCompare(BigNumber a, unsigned long long b);

BigNumber shiftLeft(BigNumber *a, unsigned long long s);

BigNumber ReadTextFile(char* file);
BigNumber ReadBinFile(char* file);
int WriteTextFile(char* file, BigNumber number);
int WriteBinFile(char* file, BigNumber number);
char* toString(BigNumber number);
BigNumber ReadFromString(char* buffer);
