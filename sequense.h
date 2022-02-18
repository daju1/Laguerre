#if !defined(SEQUENSE_FUN_422_)
#define SEQUENSE_FUN_422_

Vector<int> sequense(int i1, int i2) // ¬озвращает последовательность целых чисел от i1 до i2
{
	int len, i;
	len = i2 - i1 + 1;
	Vector<int> seq(len);
	for (i = 0; i < len; i++)
		seq[i] = i1 + i;
	return seq;
}

#endif