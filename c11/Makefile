# Generated Makefile for Problems

BIN = bin

all: array nearest-power-of-two poweroftwo series-approx sizeof square-root three-bits

bin:
	mkdir -p bin

array: array.c | bin
	gcc -Wall -Wpedantic --std=c11 -o $(BIN)/array array.c -lm

nearest-power-of-two: nearest-power-of-two.c | bin
	gcc -Wall -Wpedantic --std=c11 -o $(BIN)/nearest-power-of-two nearest-power-of-two.c -lm

poweroftwo: poweroftwo.c | bin
	gcc -Wall -Wpedantic --std=c11 -o $(BIN)/poweroftwo poweroftwo.c -lm

series-approx: series-approx.c | bin
	gcc -Wall -Wpedantic --std=c11 -o $(BIN)/series-approx series-approx.c -lm

sizeof: sizeof.c | bin
	gcc -Wall -Wpedantic --std=c11 -o $(BIN)/sizeof sizeof.c -lm

square-root: square-root.c | bin
	gcc -Wall -Wpedantic --std=c11 -o $(BIN)/square-root square-root.c -lm

three-bits: three-bits.c | bin
	gcc -Wall -Wpedantic --std=c11 -o $(BIN)/three-bits three-bits.c -lm

.PHONY: clean
clean:
	rm -fr bin

