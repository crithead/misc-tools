
EXEC = mounter
CFLAGS += -Wall -Werror -std=c17

ifeq ($(DEBUG), 1)
CFLAGS += -g
endif

SOURCES := mounter.c
SOURCES += helpers.c

OBJECTS := $(SOURCES:.c=.o)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ -lc

%.o: %.h %.c

clean:
	@rm -f $(EXEC) $(OBJECTS)

.PHONY: all clean
