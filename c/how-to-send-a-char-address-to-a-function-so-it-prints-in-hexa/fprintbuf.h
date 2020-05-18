/* $Id: fprintbuf.h,v 2.1 2005/11/05 17:51:36 luis Exp $
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Fri Aug  2 07:58:12 EEST 2019
 * Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD.
 */

/* Do not include anything BEFORE the line below, as it would not be
 * protected against double inclusion from other files
 */
#ifndef FPRINTBUF_H
#define FPRINTBUF_H

#include <stdio.h> /* FILE */
#include <sys/types.h>

/* This is used only when the printing is to be done on several
 * calls to this function.  In that case, the first chunk carries
 * write header, and so needs a format string and the variadic
 * list of parameters to specify what to write in the header line
 * of code.  The PB_WRITETRAILER is to optionally print the
 * ending offset at the end of the chunk (only used in the last
 * chunk printed). */

#define PB_WRITETRAILER		(1 << 0)
#define PB_WRITEOFFSETS		(1 << 1)
#define PB_WRITEHEXPART		(1 << 2)
#define PB_WRITECHARPART	(1 << 3)

/* prototypes */
ssize_t 
vfprintbuf (FILE *f,	/* output file */
	int flags,			/* see above */
	int npl,			/* nbytes per line */
	off_t off,			/* offset of this buffer */
	size_t t,			/* buffer size */
	const char *b,	/* buffer contents */
	const char *fmt,	/* format string */
	va_list plist);		/* header message in printf format */

ssize_t 
fprintbuf (FILE *f,	/* output file */
	int flags,			/* see above */
	int npl,			/* nbytes per line */
	off_t off,			/* offset of this buffer */
	size_t t,			/* buffer size */
	const char *b,	/* buffer contents */
	const char *fmt,	/* format string */
	...);		/* header message in printf format */

#endif /* FPRINTBUF_H */
/* Do not include anything AFTER the line above, as it would not be
 * protected against double inclusion from other files.  */
