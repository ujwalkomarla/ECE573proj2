CC=gcc
CFLAGS=-c -Wall -g 
LDFLAGS= -pthread
SOURCES=client.c customDefinitions.c ClientSenderThreadFunc.c ClientReceiverThreadFunc.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=p2mpclient


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	
clean:
	rm -rf *.o $(EXECUTABLE)
