CC = gcc
CFLAGS += -Wall -Werror -std=c17

ifeq ($(DEBUG), 1)
CFLAGS += -g
endif

SOURCES := server.c
SOURCES += client.c
SOURCES += helpers.c
SOURCES += options.c

OBJECTS := $(SOURCES:.c=.o)

all : server client relay

client : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(filter-out server.o, $^)

server : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(filter-out client.o, $^)

relay : relay.c
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h

clean:
	@rm -f client server relay $(OBJECTS)

.PHONY: all clean
