RM      ?= rm -f

targets  =  count multiple
toclean  = $(targets)

all: $(targets)
clean:
	$(RM) $(toclean)

count_objs=count.o
multiple_objs=multiple.o

toclean+=$(count_objs)
count: $(count_deps) $(count_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_ldflags) $($@_libs) $(LIBS)

toclean+=$(multiple_objs)
multiple: $(multiple_deps) $(multiple_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_ldflags) $($@_libs) $(LIBS)
