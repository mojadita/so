# Makefile --build script for lex1 and lex2.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Tue May 12 13:27:43 EEST 2020
# Copyright: (C) 2020 Luis Colorado.  All rights reserved.
# License: BSD.

targets = lex1 lex2
toclean = $(targets)
RM	   ?= rm -f

lex1_objs = lex1.o
lex1_libs = -lfl
toclean  += $(lex1_objs)

lex2_objs = lex2.o
lex2_libs = -lfl
toclean  += $(lex2_objs)

all: $(targets)
clean:
	$(RM) $(toclean)

lex1: $(lex1_deps) $(lex1_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_libs)

lex2: $(lex2_deps) $(lex2_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_libs)
