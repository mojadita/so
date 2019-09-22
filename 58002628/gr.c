/* pru.c --- program to produce efficiently a desintegration decay
 * probabilistic distribution of floating point values.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sun Sep 22 17:15:40 EEST 2019
 * Copyright: (C) 2019 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "gr.h"

#ifndef DEBUG
#define DEBUG	(0)
#endif

#if DEBUG
# define P(_f, exp) do{                      \
		printf("%20s: "_f"\n", #exp, exp);  \
	} while(0)
#else
# define P(_f, exp)
#endif

double
geometric_random(void)
{
	double n = random();
	P("%lg", n);
	P("%lg", fabs(n));
	P("%lg", fabs(n) / INT_MAX);
	P("%lg", -log(fabs(n) / INT_MAX));

	return -log(fabs(n) / INT_MAX);
} /* geometric_random */
