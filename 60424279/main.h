/* main.h -- general definitions.
 * Author: Luis Colorado.
 * Date: Fri Feb 28 20:22:35 EET 2020
 * Copyright: (C) 2020 Luis Colorado.  All rights reserved.
 * License: BSD.
 */

#ifndef _MAIN_H
#define _MAIN_H

#define BUFSIZE				1024

#define F(_fmt) __FILE__":%d:%s: " _fmt, __LINE__, __func__

#define ERR(_fmt, ...) do {							\
		fprintf(stderr,								\
			F("ERROR: " _fmt), ##__VA_ARGS__);		\
	} while (0)

#define WARN(_fmt, ...) do {						\
		fprintf(stderr,								\
			F("WARN: "_fmt), ##__VA_ARGS__);		\
	} while (0)

#define INFO(_fmt, ...) do {						\
		fprintf(stderr,								\
			F("INFO: "_fmt), ##__VA_ARGS__);		\
	} while (0)

#define DEB(_fmt, ...) do {							\
		if (flags & FLAG_VERBOSE)					\
			fprintf(stderr,							\
				F("LOG: " _fmt), ##__VA_ARGS__);	\
	} while (0)


#define FLAG_HELP			(1 << 0)
#define FLAG_FILES			(1 << 1)
#define FLAG_INVALID		(1 << 2)
#define FLAG_QUIET			(1 << 3)
#define FLAG_SUMMARY		(1 << 4)
#define FLAG_VERBOSE		(1 << 5)

#define EXIT_HELP			(1 << 0)
#define EXIT_EMALLOC		(1 << 1)
#define EXIT_EOPEN			(1 << 2)


extern int flags;
extern int exit_code;

#endif /* _MAIN_H */
