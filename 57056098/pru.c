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

	int sum;
	/* maximum value is (N-1) + (N-1) = 2N-2 */
	for (sum = 0; sum < 2*N - 1; sum++) {
		/* initial values */
		int i = sum < N ? sum : N-1; /* will be decremented */
		int j = sum - i; /* must add to sum, will be incremented */
		char *sep = "";
		for (; i >= 0 && j < N; i--, j++) {
			printf("%sA[%d, %d]", sep, i, j);
			sep = " -> ";
		}
		printf("\n");
	}
}
