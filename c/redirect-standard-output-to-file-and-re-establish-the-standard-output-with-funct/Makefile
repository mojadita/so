# Makefile --- Makefile for the test program.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Sat Oct 12 13:43:03 EEST 2019
# Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
# License: BSD.

targets = redirect
toclean = $(targets)
RM		?= rm -f

all: $(targets)
clean:
	$(RM) $(toclean)

redirect_objs = main.o redirect.o
toclean += $(redirect_objs)

redirect: $(redirect_deps) $(redirect_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_ldflags) $($@_ldlibs)
