// ‘акториал
long int fact(long int x)
{
	if (x==0 || x==1)
		return 1;
	return x * fact(x - 1);
}
// ќтношение факториалов
long int fact_relation(long int N, long int m)
{
	if (N == m)
		return 1;
	if (N > m)
		return N * fact_relation(N - 1, m);
	return 0;
}
// Ѕиноминальные коэффициенты
long int BinominalQuotient(long int n, long int N)
{
	long int m = N - n;
	if (m > n)
		return fact_relation(N, m) / fact(n);
	else
		return fact_relation(N, n) / fact(m);
}
// ‘акториал
int fact(int x)
{
	if (x==0 || x==1)
		return 1;
	return x * fact(x - 1);
}
// ќтношение факториалов
int fact_relation(int N, int m)
{
	if (N == m)
		return 1;
	if (N > m)
		return N * fact_relation(N - 1, m);
	return 0;
}
// Ѕиноминальные коэффициенты
int BinominalQuotient(int n, int N)
{
	int m = N - n;
	if (m > n)
		return fact_relation(N, m) / fact(n);
	else
		return fact_relation(N, n) / fact(m);
}
