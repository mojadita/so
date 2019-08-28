RM ?= rm -f

pru_objs = pru.o

toclean += pru $(pru_objs)

pru: $(pru_objs)
	$(CC) $(LDFLAGS) -o $@ $(pru_objs)
clean:
	$(RM) $(toclean)
