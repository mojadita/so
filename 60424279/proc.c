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

int process(const char *str)
{
    int l = strlen(str);
    const char *p = str + l;
    int res = 0;
    enum {
        ODD_DIGIT,
        EVEN_DIGIT,
    } pos = ODD_DIGIT;

    DEB("processing: [%s]\n", str);

    while (--p >= str) {
        if (!isdigit(*p)) {
            WARN("%s\n", str);
            WARN("%*s^: is not a digit\n", (int)(p-str), "");
            return -1;
        }
        int dig = *p - '0';
        switch (pos) {
        case ODD_DIGIT: pos = EVEN_DIGIT;
            DEB("Add dig(%d) to res(%d)\n", dig, res);
            res += dig; break;
        case EVEN_DIGIT: pos = ODD_DIGIT;
            DEB("Add double(dig(%d)) to res(%d)\n", dig, res);
            dig <<= 1;
            if (dig >= 10)
                dig -= 9;
            res += dig; break;
        }
        if (res >= 10)
            res -= 10;
        DEB("res <= %d\n", res);
    }
    DEB("Returning => %d\n", res);
    if ((flags & FLAG_QUIET) == 0) {
        printf("%s: %d\n", str, res);
    }
    return res;
}
