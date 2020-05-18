# Makefile --- makefile for gr program to generate a geometric
# distribution of floating point numbers.

RM		?= rm -f

targets = gr mc
toclean = $(targets)

gr_objs = gr.o main.o
mc_objs = mc.o
toclean += $(gr_objs) $(mc_objs)

gr_libs = -lm
mc_libs = -lm

all: $(targets)
clean:
	$(RM) $(toclean)

gr: $(gr_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_libs)

mc: $(mc_objs)
	$(CC) $(LDFLAGS) -o $@ $($@_objs) $($@_libs)

