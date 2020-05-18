/* main.c --- main program for the test of temporary redirection
 * of a file descriptor.
 * fputs(3) prints to stdout, but we are going to intersperse
 * printf(3) calls, with puts(3) calls (with temporary
 * redirection) to see that the temporary redirection actually
 * works. All the output will be \n terminated, so we are sure
 * that buffers are flushed out on each call.
 *
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Oct 12 13:28:54 EEST 2019
 * Copyright: (C) LUIS COLORADO.  All rights reserved.
 * License: BSD.
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "redirect.h"

/* this is our unbuffering simulation of the puts(3) function,
 * as trouble will come if we don't consider the flushing of
 * buffers properly, and I don't want to overcomplicate things
 * with stdio buffering idiosyncracies.  Function forcibly writes
 * its output to standard output, so to make it use a different
 * descriptor, we need to redirect standard output to a different
 * place before call, and restore it later.*/
ssize_t output_function(const char *s)
{
	/* ensure all output is flushed before returning back */
	return write(1, s, strlen(s));
}

void do_usage(const char *progname)
{
	fprintf(stderr,
		"Usage: %s [ file ... ]\n"
		"where 'file' is the output file to redirect output to.\n"
		"\n"
		"The program just uses a different string to output to both,\n"
		"standard output and the indicated filename, to thow the workings\n"
		"of output redirection.  I have wrapped the call to fputs(3) in a\n"
		"function in order to show that we need to call fflush to flush\n"
		"the buffers out to the file descriptor, before returning, or the\n"
		"wrong things will be written to the output descriptors. (this is\n"
		"specially true for files, that do full buffering)\n",
		progname);
}

int main(int argc, char **argv)
{
	int i;
	if (argc == 1) {
		do_usage(argv[0]);
	} else for (i = 1; i < argc; i++) {
		char buffer[1024];

		/* text we are going to write multiple times */
		snprintf(buffer, sizeof buffer,
			"%d: file = %s\n", i, argv[i]);

		/* we call our output function first, to see output going
		 * to it's normal output descriptor */
		output_function(buffer);

		/* create a file we are going to write message into */
		int fd_to_redirect_output = open(
				argv[i],
				O_WRONLY | O_CREAT | O_TRUNC,
				0666);

		/* call our function with the message and the redirection
		 * done before the call and restored after */
		int res = redirect_and_call(output_function,
					fd_to_redirect_output, /* descriptor to write
											* output to */
					1, /* stdout is file descriptor 1 */
					buffer); /* write the string to the file. */

		/* write another message to see redirection was restored
		 * properly */
		output_function("done\n");
	}
	exit(EXIT_SUCCESS);
} /* main */
