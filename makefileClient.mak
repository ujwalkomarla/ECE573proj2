CC=gcc
CFLAGS=-c -Wall


all: client

client: main.o
	$(CC) main.o -o client
main.o: main.c
	$(CC) $(CFLAGS) main.c
	
clean:
	rm -rf *o client