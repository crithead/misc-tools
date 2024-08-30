CC = gcc
CFLAGS += -Wall -Werror -std=c17

SOURCES := server.c
SOURCES += client.c
SOURCES += helpers.c
SOURCES += options.c

OBJECTS := $(SOURCES:.c=.o)

all : server client

client server : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(filter-out $@.o, $^)

%.o: %.c %.h

clean:
	@rm -f client server $(OBJECTS)

.PHONY: all clean

