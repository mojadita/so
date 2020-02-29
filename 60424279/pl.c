/* pl.c -- process lines.
 * Author: Luis Colorado.
 * Date: Fri Feb 28 20:39:11 EET 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <stdio.h>
#include <string.h>

#include "main.h"
#include "proc.h"

void process_file(FILE *in, char *fn, int *ok, int *total)
{
	DEB("file %s\n", fn);
	char line[BUFSIZE];
	while (fgets(line, sizeof line, in)) {
		char *s = strtok(line, " \t\n");
		if (!s)
			continue;
		if (process(s) == 0 && ok)
			(*ok)++;
		if (total)
			(*total)++;
	}
}
