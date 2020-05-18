/* test_fprintbuf.c --- testing code for fprintbuf.c
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Aug  2 11:42:41 EEST 2019
 * Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD.
 */

#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "fprintbuf.h"

char *program_name;

void do_help()
{
    fprintf(stderr,
		"Uso: %s [-oxct] [-n nchars_per_row] [-O offset] [-f file] [-s string]...\n"
		"Options:\n"
		"   -o   switch PB_WRITEOFFSETS flag in options.\n"
		"   -x   switch PB_WRITEHEXPART flag in options.\n"
		"   -c   switch PB_WRITECHARPART flag in options.\n"
		"   -t   switch PB_WRITETRAILER flag in options.\n"
		"   -n nchar_per_row change the default(16) value of the number of\n"
		"        chars per row.\n"
		"   -O offset.  Set the new offset, to apply to the next par.\n"
		"   -f file.  Read from a file and print a full hex buffer of it.\n"
		"   -s string.  Print a buffer with the string used as argument.\n",
        program_name);
    exit(EXIT_SUCCESS);
} /* do_help() */

void process_file(const char *name, int flags, int npl)
{
    int fd = open(name, O_RDONLY);
    if (fd < 0) {
        fprintf(stderr,
                "ERROR: %s: %s\n",
                name, strerror(errno));
        return;
    }
    char buffer[10*BUFSIZ];
    /* adjust bufsiz to the last multiple of npl less than of equal than sizeof buff */
    size_t bufsiz = sizeof buffer - (sizeof buffer % npl);
    ssize_t n;
    char *fmt = "File: %s, bufsiz: %d";
    off_t offset = 0;
    while((n = read(fd, buffer, bufsiz)) > 0) {
		fprintbuf(stdout,
				(n < bufsiz
					? flags
					: flags & ~PB_WRITETRAILER),
				npl, offset, n, buffer,
				fmt, name, n);
		fmt = NULL;
		offset += n;
    }
} /* process_file */

int main(int argc, char **argv)
{
	int opt, i;
	off_t offset = 0;
    int npl = 16;
    int flags = PB_WRITEOFFSETS | PB_WRITEHEXPART | PB_WRITECHARPART | PB_WRITETRAILER;
    program_name = argv[0];

	while ((opt = getopt(argc, argv, "oxctn:O:f:s:")) != EOF) {
        switch(opt) {
        case 'h': do_help(); break;
        case 'o': flags ^= PB_WRITEOFFSETS; break;
        case 'x': flags ^= PB_WRITEHEXPART; break;
        case 'c': flags ^= PB_WRITECHARPART; break;
        case 't': flags ^= PB_WRITETRAILER; break;
        case 'n':
            sscanf(optarg, "%d", &npl);
            if (npl < 0 || npl >= 100)
                npl = 16;
            break;
        case 'O':
            sscanf(optarg, "%lld", &offset);
            break;
        case 'f': process_file(optarg, flags, npl); break;
        case 's':
            fprintbuf(
                    stdout,
                    flags, npl, offset,
                    strlen(optarg), optarg,
                    "argv[%d] = \"%s\"\n", optind-1, optarg);
            break;
        }
	}
    exit(EXIT_SUCCESS);
}
