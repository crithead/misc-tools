//
// Given an array of numbers, replace each number with the product of all
// the numbers in the array except the number itself WITHOUT using
// division.
//
// ANSWER:
// The value at each position is the product of all of the numbers that
// come before times the product of all of the numbers that come after.
// Create two arrays: one contains the product of all numbers that come
// before I, the other contains the product of all numbers that come after.
// The final value in A is the product of B and C at each position.
// A[i] = B[i] * C[i]
//
// WITH DIVISION: Calculate the product of all values in A.  The final
// value at each position is that product divided by the value at that
// position.
// P + A[0] * A[1] * ... * A[n-1]
// A[i] = P / A[i]
//

#include <cstdlib>
#include <iostream>

static int *get_array(int argc, char **argv);
static void print_array(int *a, int n);

int main(int argc, char **argv)
{
	// Get a list of numbers from the command line
	int n = argc - 1;
	int *a = get_array(argc, argv);
	print_array(a, n);

	// Calculate the product of all values before i
	int *b = new int[n];
	b[0] = 1;
	for (int i = 1; i < n; i++)
		b[i] = b[i - 1] * a[i - 1];
	print_array(b, n);

	// Calculate the product of all values after i
	int *c = new int[n];
	c[n - 1] = 1;
	for (int i = n - 2; i >= 0; i--)
		c[i] = c[i + 1] * a[i + 1];
	print_array(c, n);

	// replace values in A with the corresponding values in B * C
	for (int i = 0; i < n; i++)
		a[i] = b[i] * c[i];
	print_array(a, n);

	delete[] a;
	delete[] b;
	delete[] c;
	return 0;
}

//
// Turn the list of program arguments into an array of intergers.
//
static int *get_array(int argc, char **argv)
{
	int *a = new int[argc - 1];
	if (a) {
		for (int i = 1; i < argc; i++)
			a[i - 1] = std::atoi(argv[i]);
	}
	return a;
}

static void print_array(int *a, int n)
{
	for (int i = 0; i < n; i++)
		std::cout << '\t' << a[i];
	std::cout << std::endl;
}
