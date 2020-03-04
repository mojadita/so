# Makefile -- build file for cs50 algorithm.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Fri Feb 28 21:19:12 EET 2020
# Copyright: (C) 2020 Luis Colorado.  All rights reserved.
# License: BSD

RM       ?= rm -f
USR		 ?= `id -u`
GRP	 	 ?= `id -g`
prefix   ?= $(HOME)
mandir	 ?= $(prefix)/man
man1dir	 ?= $(mandir)/man1
bindir	 ?= $(prefix)/bin
dmod	 ?= u+rwx,go+rx
fmod	 ?= u+rw,go+r
xmod	 ?= u+rwx,go+rx

targets   = cs50
toclean   = $(targets)

cs50_objs = main.o pl.o proc.o
toclean  += $(cs50_objs)

.PHONY: all clean install

all: $(targets)
clean:
	$(RM) $(toclean)
install: $(targets)
	-$(INSTALL) -o $(USR) -g $(GRP) -m $(fmod) cs50.1 $(man1dir)/cs50.1
	-$(INSTALL) -o $(USR) -g $(GRP) -m $(xmod) cs50 $(bindir)/cs50

cs50: $(cs50_deps) $(cs50_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_ldflags) $($@_libs)
