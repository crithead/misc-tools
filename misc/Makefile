CC = g++
CXXFLAGS = -Wall -pedantic --std=c++17
CFLAGS = -Wall -pedantic --std=c17

ifeq (DEBUG, 1)
CFLAGS += -g
endif

OUTPUT_DIR = output

SRC = letters-to-numbers.cpp
OBJ = letters-to-numbers.o
EXE = letters-to-numbers

DOC := grayscale.1 create-index.1 letters-to-numbers.1
DOC += grayscale.1.html create-index.1.html letters-to-numbers.1.html

all: $(EXE) errno

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -O2 $(SRC) -o $(EXE)

debug: $(SRC)
	$(CC) $(CFLAGS) -g $(SRC) -o $(EXE)

check: $(SRC)
	cppcheck -v --enable=style $(SRC)

letters-to-numbers.o: letters-to-numbers.cpp

docs: $(DOC)
#	asciidoc -d manpage $<
#	a2x --doctype manpage --format manpage $<

%.1.html: %.1.txt
	asciidoc -d manpage -o $@ $<

%.1: %.1.txt
	a2x --doctype manpage --format manpage $<

grayscale.1 grayscale.1.html: grayscale.1.txt
letters-to-numbers.1 letters-to-numbers.1.html: letters-to-numbers.1.txt
create-index.1 create-index.1.html: create-index.1.txt

errno: errno.c
	gcc $(CFLAGS) -o $@ $^

.PHONY : clean
clean:
	rm -f $(OBJ) $(EXE) $(DOC) errno

# End
