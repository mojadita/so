/* mc.c --- distribution test.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Sep 22 18:09:16 EEST 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <float.h>
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	long n = 0;
	double sum_x = 0.0;
	double sum_x2 = 0.0;
	double min_x = +DBL_MAX;
	double max_x = -DBL_MAX;

	double A = 0.0, B = 10.0;
	long below_A = 0, above_B = 0;
	int N = 10;

	int opt;
	while ((opt = getopt(argc, argv, "a:b:n:")) != EOF) {
		switch (opt) {
		case 'a': sscanf(optarg, "%lg", &A); break;
		case 'b': sscanf(optarg, "%lg", &B); break;
		case 'n': sscanf(optarg, "%d", &N); break;
		}
	} /* while */

	long *freqs = calloc(N, sizeof *freqs);

	double x;
	while (scanf("%lg", &x) == 1) {
		n++;
		sum_x += x;
		sum_x2 += x * x; 
		if (x < min_x) min_x = x;
		if (x > max_x) max_x = x;
		if (x >= A && x < B) {
			int i = N * (x - A) / (B - A);
			freqs[i]++;
		} else if (x < A) {
			below_A++;
		} else {
			above_B++;
		}
	}
	double avg_x = sum_x / n;
	double sdev_x = sqrt((n*sum_x2 - (sum_x*sum_x)) / n / (n-1));

#define L "%6ld"
#define F "%.16f"
#define P(_fmt, exp) printf("%20.20s: "_fmt"\n", #exp, exp)

	P(L, n);
	P(F, sum_x);
	P(F, sum_x2);
	P(F, avg_x);
	P(F, sdev_x);
	P(F, min_x);
	P(F, max_x);
	P(L, below_A);

	double delta_x = (B - A) / N;
	int i;
	for (i = 0; i < N; i++) {
		B = A + delta_x;
		printf("[" F ", " F "]" L ,
			A, B, freqs[i]);
		if (i && freqs[i-1])
			printf(": "F,
				(double)freqs[i] / freqs[i-1]);
		printf("\n");
		A = B;
	}

	P(L, above_B);

	return 0;
}
