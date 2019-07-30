#include <stdio.h>
#include <stdlib.h>
#define n 10
#define loop 5

void print(int x[], int y[], int z[])
{
	int i;
	printf("%12s%12s%12s%12s\n","i", "x[i]", "y[i]", "z[i]");
	for(i = 0; i < n; i++)
		printf("%12d%12d%12d%12d\n", i, x[i], y[i], z[i]);
}

int main()
{
	int x[n], y[n], *z = y;
	int i, l;
	for(i = 0; i < n; i++) {
		x[i] = rand();
		y[i] = rand();
		z[i] = rand();
	}

	printf("initial values:\n");
	print(x, y, z);

	for (l = 1; l <= loop; l++) {
        for (i = 1; i<n; i++) {
			x[i] = z[i] * (y[i] - x[i - 1]);
		}
		printf("after iteration %d:\n", l);
		print(x, y, z);
	}
}
