CC=gcc
CFLAGS=-c -Wall -o3 -g
LDFLAGS=
SOURCES=main.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=client


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *o client