CC = gcc
CFLAGS = -O1 -g -Wall

CFILES := qsort.c stack.c check.c
TFILES := qsort.c stack.c test.c

check: $(CFILES)
	$(CC) $^ -o $@ $(CFLAGS)

test: $(TFILES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f check test