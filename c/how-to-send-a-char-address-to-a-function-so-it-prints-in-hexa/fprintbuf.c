/* $Id: fprintbuf.c,v 2.1 2005/11/05 17:51:36 luis Exp $
 * AUTHOR: Luis Colorado <luiscoloradourcola@gmail.com>
 * DATE: 7.10.92.
 * DESC: muestra un buffer de datos en hexadecimal y ASCII.
 */

#include <sys/types.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>

#include "fprintbuf.h"

static char *id = "$Id: fprintbuf.c,v 2.1 2005/11/05 17:51:36 luis Exp $\n";

#define FMT_OFFSET_PART	"%08llx"
#define FMT_OFFSET_HDR	">>>>>>>>"
#define FMT_HEX_PART	" %02x"
#define LEN_HEX_CHAR	(3)

static ssize_t
print_header(FILE *out, const char *fmt, va_list plist)
{
	ssize_t res = 0, n;

	n = fprintf(out, "%s: ", FMT_OFFSET_HDR);	if (n < 0) return -1;
	res += n;
	n = vfprintf(out, fmt, plist);		if (n < 0) return -1;
	res += n;
	n = fprintf(out, "\n");				if (n < 0) return -1;
	res += n;

	return res;
}

ssize_t 
vfprintbuf (FILE *f,	/* output file */
	int flags,			/* see above */
	int npl,			/* nbytes per line */
	off_t off,			/* offset of this buffer */
	size_t t,			/* buffer size */
	const char *b,	/* buffer contents */
	const char *fmt,	/* format string */
	va_list plist)		/* header message in printf format */
{
	ssize_t written = 0;

/* this macro checks the return value n, if negative, returns
 * it (error), else adds it to written, as written is the final
 * returned value in case of no error */
#define CHK() do{if(n < 0)return n;written += n;}while(0)

	if (fmt) {
		ssize_t n = print_header(f, fmt, plist); CHK();
	}
		
	while (t > 0) {
		char *sep1 = "",
			 *sep2 = ":",
			 *sep3 = " :"; /* separators between parts */
		char *sep = sep1;

		if (flags & PB_WRITEOFFSETS) {
			ssize_t n = fprintf (f, FMT_OFFSET_PART, off); CHK();
			sep = sep2;
		}
		if (flags & PB_WRITEHEXPART) {
			int i;
			ssize_t n = fprintf(f, "%s", sep); CHK();
			for (i = 0; i < npl && i < t; i++) {
				n = fprintf (f, FMT_HEX_PART, b[i] & 0xff); CHK();
				sep = sep2;
			}
			if (flags & PB_WRITECHARPART) { /* blanks after
											 * hex part */
				n = fprintf(f, "%*s",
					LEN_HEX_CHAR*(npl - i), ""); CHK();
				sep = sep3;
			}
		}
		if (flags & PB_WRITECHARPART) {
			ssize_t n = fprintf(f, "%s", sep); CHK();
            int i;
			for (i = 0; i < npl && i < t; i++) {
				int c = b[i] & 0xff;
				n = fprintf(f, "%c", isprint(c) ? c : '.');
				CHK();
			}
		}
		if (flags & (PB_WRITEOFFSETS | PB_WRITEHEXPART
			| PB_WRITECHARPART)) { /* if we print something */
			ssize_t n = fprintf(f, "\n"); CHK();
		}
		if (t >= npl) {
			b += npl; t -= npl;
			off += npl;
		} else {
			off += t;
			t = 0;
		}
	}

	if (flags & PB_WRITETRAILER) {
		ssize_t n = fprintf (f, FMT_OFFSET_PART "\n", off); CHK();
	}
#undef CHK

	return written;
} /* vfprintbuf */

ssize_t 
fprintbuf (FILE *f,	/* output file */
	int flags,			/* see above */
	int npl,			/* nbytes per line */
	off_t off,			/* offset of this buffer */
	size_t t,			/* buffer size */
	const char *b,	/* buffer contents */
	const char *fmt,	/* format string */
	...)		/* header message in printf format */
{
	va_list l;
	ssize_t written;

	va_start(l, fmt);
	written = vfprintbuf(f, flags, npl, off, t, b, fmt, l);
	va_end(l);
	return written;
} /* fprintbuf */

/* $Id: fprintbuf.c,v 2.1 2005/11/05 17:51:36 luis Exp $ */
