# Makefile for C++ Examples
CC := g++
CXXFLAGS := -O2 -Wall -Wpedantic -std=c++17
#CXXFLAGS += -Wextra
CXXFLAGS += -g

TARGETS :=
TARGETS += alpha
TARGETS += alt-tokens
TARGETS += auto
TARGETS += bad-macro
TARGETS += blobs
TARGETS += ch9vector
TARGETS += class-ident
TARGETS += combat3d
TARGETS += complex
TARGETS += constructor
#TARGETS += cpp11a
#TARGETS += cpp11b
TARGETS += cpp11c
TARGETS += cpp17demo
TARGETS += drifter3
TARGETS += drifter3dice
TARGETS += enum
TARGETS += fibonacci
TARGETS += fileio-char
TARGETS += fileio-int
TARGETS += first-unique
TARGETS += functor
TARGETS += global-object
TARGETS += golden-ratio
TARGETS += gnome
TARGETS += increment
TARGETS += int-except
TARGETS += int-types
TARGETS += letter-counter
TARGETS += list-iterator
TARGETS += list-remove
TARGETS += loopvars
TARGETS += markov
TARGETS += markov2
#TARGETS += messagequeue
TARGETS += momcombat
TARGETS += petshop
TARGETS += pointers
TARGETS += power
TARGETS += primes
TARGETS += pwgen
TARGETS += range
TARGETS += rawstring
TARGETS += readfile
TARGETS += read-write
TARGETS += redirect
TARGETS += replace-with-product
TARGETS += retirement
TARGETS += ringbuffer
TARGETS += robber
TARGETS += root
TARGETS += rtti
TARGETS += std-map
TARGETS += static-init
TARGETS += string-compare
TARGETS += string-wrap
TARGETS += strings
TARGETS += stringy
TARGETS += strtol
TARGETS += switch
TARGETS += tabcheck
TARGETS += table
TARGETS += text-to-numbers
TARGETS += trajectory
TARGETS += vector
TARGETS += wordfreq
TARGETS += wordfreq2


.PHONY: all
all: $(TARGETS)

alpha: alpha.o alpha-main.o

# an example of the bad behavior, not going to let the compiler spoil
# this surprise with a warning
bad-macro: CXXFLAGS += -Wno-dangling-else

complex: CXXFLAGS += -DTEST

cpp17demo: CXXFLAGS := -O2 -Wall -Wpedantic -std=c++17

global-object: global-object.o goblin.o

gnome: test-main.o test-gnome.o gnome.o
	$(CC) $(CXXFLAGS) -o $@ $? -lcppunit

# dynamic exception specifications are deprecated in C++11 and removed
# in C++17, but this is an example of one so don't warn
int-except: CXXFLAGS += -Wno-deprecated -std=c++14

increment: increment.o
	$(CC) $(CXXFLAGS) -o $@ $? -lpthread

petshop: petshop.cpp pet.o
	$(CC) $(CXXFLAGS) -o $@ $?

pointers: pointers.cpp
	$(CC) $(CXXFLAGS) -Wno-deprecated-declarations -o $@ $?

ringbuffer: CXXFLAGS += -DDEMO=1

string-compare: string-compare.cpp
	$(CC) $(CXXFLAGS) -Wno-write-strings -Wno-pedantic -o $@ $?

table: table-main.o table.hpp

.PHONY: clean
clean:
	rm -f *.o $(TARGETS)
	rm -f *.csv

# End
