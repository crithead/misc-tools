CC = g++
CFLAGS = -Wall -pedantic --std=c++11

OUTPUT_DIR = output

SRC = letters-to-numbers.cpp
OBJ = letters-to-numbers.o
EXE = letters-to-numbers

DOC = grayscale.1.txt create-index.1.txt letters-to-numbers.1.txt

all: $(EXE)

$(EXE): $(SRC)
	$(CC) $(CFLAGS) -O2 $(SRC) -o $(EXE)

debug: $(SRC)
	$(CC) $(CFLAGS) -g $(SRC) -o $(EXE)

check: $(SRC)
	cppcheck -v --enable=style $(SRC)

docs: $(DOC)
	asciidoc -d manpage $<
	a2x --doctype manpage --format manpage $<

.PHONY : clean
clean:
	rm -f *.o $(EXE) $(EXE).1 *.1.html *.1.pdf

letters-to-numbers.o: letters-to-numbers.cpp

%.1.html : %.1.txt
	asciidoc -d manpage -o $@ $<

%.1 : %.1.txt
	asciidoc -d manpage -o $@ $<

grayscale.1 grayscale.1.html: grayscale.1.txt
letters-to-numbers.1 letters-to-numbers.1.html: letters-to-numbers.1.txt
create-index.1 create-index.1.html: create-index.1.txt

# End

