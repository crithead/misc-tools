#  Bases Makefile
# (C) 2014 Donald Perkovich. All rights reserved.
CC = g++
CFLAGS = -Wall -pedantic --std=c++11

OUTPUT_DIR = output

SRC = bases.cpp
OBJ = bases.o
EXE = bases
DOC = bases.1.txt

all : $(EXE)

$(EXE) : $(SRC)
	$(CC) $(CFLAGS) -O2 $(SRC) -o $(EXE)

debug : $(SRC)
	$(CC) $(CFLAGS) -g $(SRC) -o $(EXE)

check : $(SRC)
	cppcheck -v --enable=style $(SRC)

doc : $(DOC)
	asciidoc -d manpage $<
	a2x --doctype manpage --format manpage $<

test : $(EXE)
	@echo "=== Running Bases Tests"
	@./test_bases
	@echo "=== Done"

.PHONY : clean
clean:
	rm -f *.o $(EXE) $(EXE).1 $(EXE).1.html $(EXE).1.pdf

bases.o: bases.cpp

# End

