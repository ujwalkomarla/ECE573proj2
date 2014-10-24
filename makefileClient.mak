CC=gcc
CFLAGS=-c -Wall -g 
LDFLAGS= -pthread
SOURCES=client.c customDefinitions.c ClientSenderThreadFunc.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=client


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o $(EXECUTABLE)