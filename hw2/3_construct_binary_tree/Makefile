CC = gcc
CFLAGS = -O1 -g -Wall

MFILES := main.c tree.c
TFILES := main.c tree_test.c
AFILES := analyze.c tree.c tree_test.c

main: $(MFILES)
	$(CC) $^ -o $@ $(CFLAGS)

test: $(TFILES)
	$(CC) $^ -o $@ $(CFLAGS)

analyze: $(AFILES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f main test analyze