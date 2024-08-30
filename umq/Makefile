CC = gcc
CFLAGS += -Wall -Werror -std=c17

SOURCES := server.c
SOURCES += client.c
SOURCES += helpers.c
SOURCES += options.c

OBJECTS := $(SOURCES:.c=.o)

all : server client

client : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(filter-out server.o, $^)

server : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(filter-out client.o, $^)

%.o: %.c %.h

clean:
	@rm -f client server $(OBJECTS)

.PHONY: all clean

