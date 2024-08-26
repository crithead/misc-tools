CC = gcc
CFLAGS += -Wall -Werror -std=c17
LIBS := -lzmq

PROGRAMS := server
PROGRAMS += client

SOURCES := $(PROGRAMS:=.c)

all : $(PROGRAMS)

#$(EXEC): $(OBJECTS)
#	$(CC) $(CFLAGS) -o $@ $^ -lc

#%.o: %.c %.h
%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	@rm -f $(PROGRAMS)

print:
	@echo "SOURCES = $(SOURCES)"
	@echo "PROGRAMS = $(PROGRAMS)"

.PHONY: all clean print

