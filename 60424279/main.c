/* main.c -- Main program.
 * Author: Luis Colorado.
 * Date: Fri Feb 28 20:23:32 EET 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "main.h"
#include "pl.h"
#include "proc.h"

int flags;
int exit_code;

void do_help()
{
    fprintf(stderr,
        "Usage: cs50 [ -hiqsv ] [ -n number ... ] [ file ... ]\n"
        "where file is a file containing card numbers, one per\n"
        "line.  If it cannot be open, it is tried to verify, as\n"
        "if it was a single card number.  The command prints out\n"
        "the valid numbers seen, or the invalid ones, in case\n"
        "they are selected.\n"
        "\n"
        "Options:\n"
        " -f file: Processes a file of numbers.\n"
        "     Format is one number per line\n"
        " -h  Help.  Prints this help text.\n"
        " -q  Be quiet.  Only an exit error code is given.\n"
        " -s  Prints a summary at the end.  The number of\n"
        "    good keys / total keys is printed at the end.\n"
        " -v  Be verbose.  Traces of each calculation are \n"
        "    printed on stderr.\n");
    exit_code |= EXIT_HELP;
}

int main(int argc, char **argv)
{
    size_t files_cap = 10;
    char **files = malloc(files_cap * sizeof(*files));
    size_t files_n = 0;
    int opt;

    while ((opt = getopt(argc, argv, "f:hqsv")) >= 0) {
        switch (opt) {
        case 'f': flags |= FLAG_FILES;
            if (files_n == files_cap) {
                files_cap <<= 1;
                files = realloc(files, files_cap * sizeof(*files));
                if (!files) {
					ERR("ERROR: realloc(files_cap = %zd): %s\n",
							files_cap,
							strerror(errno));
                    exit_code |= EXIT_EMALLOC;
        			exit(exit_code);
                }
            }
			files[files_n++] = optarg;
			break;
        case 'h': flags |= FLAG_HELP; break;
        case 'q': flags |= FLAG_QUIET; break;
        case 's': flags |= FLAG_SUMMARY; break;
        case 'v': flags |= FLAG_VERBOSE; break;
        }
    }

    if (flags & FLAG_HELP) {
        do_help();
		exit(exit_code);
    }

    argc -= optind; argv += optind;

    int total = 0, ok = 0;

    if (flags & FLAG_FILES) {
        int i;
        for (i = 0; i < files_n; i++) {
			bool is_file = strcmp(files[i], "-");
            FILE *in = is_file
				? fopen(files[i], "rt")
				: stdin ;
            if (!in) {
                exit_code |= EXIT_EOPEN;
                WARN("%s: %s\n", files[i], strerror(errno));
                continue;
            }
            process_file(in, files[i], &ok, &total);
			if (is_file) fclose(in);
        }
    }

    if (argc) { /* arguments in command line */
        while (argc--) {
            if (process(*argv++) == 0) { /* ok */
                ok++;
            }
            total++;
        }
    } else if (~flags & FLAG_FILES) {
            process_file(stdin, "stdin", &ok, &total);
    }
    
	if (flags & FLAG_SUMMARY) {
		printf("%d/%d ok\n", ok, total);
	}

    exit(exit_code);
}
