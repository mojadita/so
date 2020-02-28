/* pl.h -- process lines.
 * Author: Luis Colorado.
 * Date: Fri Feb 28 20:48:24 EET 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */
#ifndef _PL_H
#define _PL_H

#include <stdio.h>

void process_file(FILE *in, char *fn, int *ok, int *total);

#endif /* _PL_H */
