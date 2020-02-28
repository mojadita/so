# Makefile -- build file for cs50 algorithm.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Fri Feb 28 21:19:12 EET 2020
# Copyright: (C) 2020 Luis Colorado.  All rights reserved.
# License: BSD

RM	   	   ?= rm -f

targets		= cs50
toclean		= $(targets)

cs50_objs	= main.o pl.o proc.o
toclean	   += $(cs50_objs)

all: $(targets)
clean:
	$(RM) $(toclean)

cs50: $(cs50_deps) $(cs50_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_ldflags) $($@_libs)
