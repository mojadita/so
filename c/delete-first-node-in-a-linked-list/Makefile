# Makefile for pru
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Wed Aug 28 17:57:12 EEST 2019
# Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
# License: BSD.

RM ?= rm -f

pru_objs = pru.o

toclean += pru $(pru_objs)

pru: $(pru_objs)
	$(CC) $(LDFLAGS) -o $@ $(pru_objs)
clean:
	$(RM) $(toclean)
