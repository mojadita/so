/* pru.c --- program to produce efficiently a desintegration decay
 * probabilistic distribution of floating point values.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Sep 22 17:27:27 EEST 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#include <stdio.h>
#include <getopt.h>

#include "gr.h"

int main(int argc, char **argv)
{
	int opt;
	int N = 100;

	while ((opt = getopt(argc, argv, "n:")) != EOF) {
		switch (opt) {
		case 'n': sscanf(optarg, "%d", &N); break;
		}
	}

	int i;
	for (i = 0; i < N; i++)
		printf("%.16lg\n", geometric_random());

	return 0;
} /* main */
