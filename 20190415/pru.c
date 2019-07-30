#include <stdlib.h>
#include <stdio.h>

int compare_int(const int *a, const int *b)
{
	return (*a > *b) - (*b > *a);
}

int reverse(const void *a, const void *b)
{
	return compare_int(b, a);
}

int main()
{
	int x[] = {500, 456, 18, 13, 3, 89, 800,
		6874};
	qsort(x,
		sizeof(x)/sizeof(x[0]),
		sizeof(x[0]),
		reverse);
	for (int i=0; i <
			sizeof(x)/sizeof(x[0]); i++) {
		printf("%d\n", x[i]);
	}

	return 0;
}
