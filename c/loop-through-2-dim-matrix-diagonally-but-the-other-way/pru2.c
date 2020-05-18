#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

int N = 10;

int main(int argc, char **argv)
{
	int opt;
	while ((opt = getopt(argc, argv, "n:")) != EOF) {
		switch(opt) {
		case 'n': N = atoi(optarg); break;
		}
	} /* while */

	int dif;
	/* maximum value is (N-1) + (N-1) = 2N-2 */
	for (dif = -N+1; dif <= N-1; dif++) {
		/* initial values, dif = i - j ==> dif + j = i */
		int i = dif > 0 ?   0 : -dif; /* will be decremented */
		int j = dif > 0 ? dif :    0; /* must add to sum, will be incremented */
		char *sep = "";
		for (; i < N && j < N; i++, j++) {
			printf("%sA[%d, %d]", sep, i, j);
			sep = " -> ";
		}
		printf("\n");
	}
}
