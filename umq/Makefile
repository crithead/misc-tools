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

all : server client relay iclient iserver

client : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(filter-out server.o, $^)

server : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(filter-out client.o, $^)

relay : relay.c
	$(CC) $(CFLAGS) -o $@ $^

iclient: iclient.o helpers.o options.o
	$(CC) $(CFLAGS) -o $@ $^

iserver: iserver.o helpers.o options.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c %.h

format:
	clang-format --style file:./.clang-format -i *.c *.h

clean:
	@rm -f client server relay
	@rm -f iclient iserver
	@rm -f *.o

.PHONY: all clean format
