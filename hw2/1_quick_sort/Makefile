CC = gcc
CFLAGS = -O1 -g -Wall

CFILES := qsort.c qlist.c check.c

check: $(CFILES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f $(CFILES)
	rm -f *.dSYM