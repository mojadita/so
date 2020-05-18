# Makefile -- makefile for the test program.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Fri Aug  2 11:53:07 EEST 2019
# Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
# License: BSD.

targets=test_printbuf

RM ?= rm -f

all: $(targets)
clean:
	$(RM) $(toclean)

test_printbuf_objs = test_fprintbuf.o fprintbuf.o

toclean += test_printbuf $(test_printbuf_objs)
test_printbuf: $(test_printbuf_objs) $(test_printbuf_deps)
	$(CC) $(LDFLAGS) -o $@ $(test_printbuf_objs) 		\
		$(test_printbuf_ldflags) $(test_printbuf_libs) 	\
		$(LIBS)
