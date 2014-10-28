CC=gcc
CFLAGS=-c -Wall -o3 -g
LDFLAGS=
SOURCES=server.c customDefinitions.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=p2mpserver


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o $(EXECUTABLE)
