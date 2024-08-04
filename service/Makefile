EXE = templated
CFLAGS += -Wall -Werror -std=c11

$(EXE): service.c options.c
	$(CC) $(CFLAGS) -o $@ $? -lc

clean:
	@rm -f $(EXE)

.PHONY: all clean

