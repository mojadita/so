/* proc.c -- process.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Feb 28 20:53:16 EET 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "proc.h"

static char table[20][10] = {
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, /*  0 */
	11, 12, 13, 14, 15, 16, 17, 18, 19, 10, /*  1 */
	12, 13, 14, 15, 16, 17, 18, 19, 10, 11, /*  2 */
	13, 14, 15, 16, 17, 18, 19, 10, 11, 12, /*  3 */
	14, 15, 16, 17, 18, 19, 10, 11, 12, 13, /*  4 */
	15, 16, 17, 18, 19, 10, 11, 12, 13, 14, /*  5 */
	16, 17, 18, 19, 10, 11, 12, 13, 14, 15, /*  6 */
	17, 18, 19, 10, 11, 12, 13, 14, 15, 16, /*  7 */
	18, 19, 10, 11, 12, 13, 14, 15, 16, 17, /*  8 */
	19, 10, 11, 12, 13, 14, 15, 16, 17, 18, /*  9 */
	 0,  2,  4,  6,  8,  1,  3,  5,  7,  9, /* 10 */
	 1,  3,  5,  7,  9,  2,  4,  6,  8,  0, /* 11 */
	 2,  4,  6,  8,  0,  3,  5,  7,  9,  1, /* 12 */
	 3,  5,  7,  9,  1,  4,  6,  8,  0,  2, /* 13 */
	 4,  6,  8,  0,  2,  5,  7,  9,  1,  3, /* 14 */
	 5,  7,  9,  1,  3,  6,  8,  0,  2,  4, /* 15 */
	 6,  8,  0,  2,  4,  7,  9,  1,  3,  5, /* 16 */
	 7,  9,  1,  3,  5,  8,  0,  2,  4,  6, /* 17 */
	 8,  0,  2,  4,  6,  9,  1,  3,  5,  7, /* 18 */
	 9,  1,  3,  5,  7,  0,  2,  4,  6,  8, /* 19 */
};

int process(const char *str)
{
    int l = strlen(str);
    const char *p = str + l;
    char st = 0;

    DEB("processing: [%s]\n", str);

    while (--p >= str) {
		char dig;
		switch (*p) {
		case ' ' : case '\t': case '\n': case '\r': case '\f':
		case '\a': case '\b': case '\v': case '-' : case '.' :
		case '_' : case ',': continue;
		case '0' : dig = 0; break; case '1': dig = 1; break;
		case '2' : dig = 2; break; case '3': dig = 3; break;
		case '4' : dig = 4; break; case '5': dig = 5; break;
		case '6' : dig = 6; break; case '7': dig = 7; break;
		case '8' : dig = 8; break; case '9': dig = 9; break;
		default:
			if (!isdigit(*p)) {
				WARN("%s\n", str);
				WARN("%*s^: is not a digit\n", (int)(p-str), "");
				exit_code |= EXIT_ESYNTAX;
				return -1;
			}
		}

		char old_st = st;
		st = table[st][dig];

        DEB("st: %2d =%d=> %2d\n", old_st, dig, st);
    }

	if (st >= 10) st -= 10;

	if (st)
		exit_code |= EXIT_FAILED;

    DEB("Returning => %d\n", st);

    if (~flags & FLAG_QUIET) {
        printf("%s: %d\n", str, st);
    }

    return st;
}
