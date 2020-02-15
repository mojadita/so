targets=  count multiple
toclean= $(targets)

all: $(targets)
clean:
	$(RM) $(toclean)

count_objs=count.o
toclean+=$(count_objs)
multiple_objs=multiple.o
toclean+=$(multiple_objs)

.for t in $(targets)
toclean+=$($t_objs)
$t: $($t_deps) $($t_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_ldflags) $($@_libs) $(LIBS)
.endfor
