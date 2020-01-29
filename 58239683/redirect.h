/* redirect.h --- definitions for the module redirect.c
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Sat Oct 12 13:24:54 EEST 2019
 * Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD.
 */
#ifndef _REDIRECT_H
#define _REDIRECT_H

/* our redirect_and_call will return int, as fputs(3) returns
 * int, and will need an extra parameter, so it can call
 * fputs, and pass it the proper parameter. */
typedef ssize_t RET_TYPE;

RET_TYPE redirect_and_call(
	RET_TYPE (*funct_to_be_called)(const char*s), 
	int fd_to_write_to,
	int fd_funct_uses_as_output,
	const char *parameter_for_the_call);

#endif /* _REDIRECT_H */
