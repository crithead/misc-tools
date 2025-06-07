/*
 * Check if a number is a power of two.
 */

/*
gcov use:

$ gcc -Wall -fprofile-arcs -ftest-coverage poweroftwo.c -fPIC -O0 -o poweroftwo
$ ./poweroftwo -1 0 1 2 3 4 5 6 7 8 9 10
$ gcov poweroftwo.c

The file "poweroftwo.c.gcov" will contain the source file with usage
statistics for each line.
*/

#include <stdio.h>
#include <stdlib.h>

/*
 * Count the number of 1 bits in an integer.
 */
static int num_bits_on(int n)
{
	int i;
	int num_bits = 0;
	int bits_per_int = 8 * sizeof(int);
	for (i = 0; i < bits_per_int; i++) {
		int mask = ((unsigned int)1 << i);
		if (n & mask)
			num_bits++;
	}
	return num_bits;
}

/*
 * Print all powers of two from min to max.
 */
static void print_powers_of_two(int min, int max)
{
	int i, n;
	for (n = min, i = 0; n <= max; n++) {
		if (num_bits_on(n) == 1) {
			printf("%10d", n);
			if (i++ % 8 == 7)
				putchar('\n');
			fflush(stdout);
		}
	}
}

int main(int argc, char **argv)
{
	int i;
	for (i = 1; i < argc; i++) {
		int n = atoi(argv[i]);
		if (n <= 0) {
			puts("Number must be a positive integer");
		} else if (num_bits_on(n) == 1) {
			printf("%8d is a power of two\n", n);
		} else {
			printf("%8d is NOT a power of two\n", n);
		}
	}
	if (argc == 1) {
		print_powers_of_two(1, 1000000);
	}
	return 0;
}

