EXEC = templated
CFLAGS += -Wall -Werror -std=c17

SOURCES := service.c
SOURCES += message.c
SOURCES += options.c

OBJECTS := $(SOURCES:.c=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lc

%.o: %.h %.c

clean:
	@rm -f $(EXEC) $(OBJECTS)

.PHONY: all clean

