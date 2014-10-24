CC=gcc
CFLAGS=-c -Wall -o3 -g
LDFLAGS=
SOURCES=server.c customFunctions.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=server


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o $(EXECUTABLE)