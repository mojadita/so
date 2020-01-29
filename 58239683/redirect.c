/* redirect.c --- function to create a temporary redirect of a
 * file descriptor in order to execute a function (passed as a
 * parameter) with that descriptor redirected so it will output
 * to the redirected desriptor, instead of to the one it used to.
 * We'll use puts(3) as an example of a function that is
 * hard wired to print into stdout (fd = 1) and to make it to
 * write to a named file instead.
 *
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Oct 12 13:04:45 EEST 2019
 * Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "redirect.h"

#define F(_f) __FILE__":%d:%s: " _f, __LINE__, __func__

#define CHECK_ERR(var, status, name) do {     \
		if ((var) < 0) {                      \
			fprintf(stderr,                   \
				F("%s: %s\n"),                \
				name, strerror(errno));       \
			exit(status);                     \
		}                                     \
	} while(0)

RET_TYPE redirect_and_call(
	RET_TYPE (*funct_to_be_called)(const char*s), 
	int fd_to_write_to,
	int fd_funct_uses_as_output,
	const char *parameter_for_the_call)
{
   /* save a copy descriptor, so we can overwrite the fd the one
     * function uses to write */
    int saved_old_fd = dup(
			fd_funct_uses_as_output);
    CHECK_ERR(saved_old_fd, 1, "dup");

    /* now, we change the descriptor the function uses to write
	 * by the one we want it to be used for output */
    int res = dup2(
			fd_to_write_to,
			fd_funct_uses_as_output);
    CHECK_ERR(res, 2, "dup2");

    /* now, we call the function */
    RET_TYPE res2 = funct_to_be_called(parameter_for_the_call);

    /* now restore descriptors to what they where. For this, we
	 * use the saved file descriptor */
    res = dup2(saved_old_fd, fd_funct_uses_as_output);

    /* close the saved descriptor, as we dont need it anymore */
    close(saved_old_fd);

    /* and finally, return the funct_to_be_called return value */
    return res2;
} /* redirect_and_call */
