CC = gcc
CFLAGS = -O1 -g -Wall

MFILES := main.c

main: $(MFILES)
	$(CC) $^ -o $@ $(CFLAGS)

test: $(TFILES)
	$(CC) $^ -o $@ $(CFLAGS)

analyze: $(AFILES)
	$(CC) $^ -o $@ $(CFLAGS)

clean:
	rm -f main