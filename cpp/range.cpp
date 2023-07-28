// This utility works like the Python range function in that is
// produces a string of space separated number on stdout from
// A (inclusive) to B (exclusive).
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

static void print_help(void)
{
	cout << "Print a space-separated list of numbers from A (inclusive)" << endl;
	cout << "to B (exclusive) at intervals of C to the standard output." << endl;
	cout << endl;
	cout << "    range B | A B | A B C | --help | -h" << endl;
	cout << endl;
	cout << "    A     start of range (default = 0)" << endl;
	cout << "    B     end of range (default = 1)" << endl;
	cout << "    C     increment (default = 1)" << endl;
	cout << "   -h     print a help message and exit" << endl;
	cout << endl;
	cout << "It is like the Python range function for bash for loops." << endl;
	cout << "i.e. for i in $(range A B C); do ... done" << endl;
	cout << endl;
}

int main(int argc, char *argv[])
{
	int a = 0, b = 1, c = 1;

	if (argc == 2) {
		if (strncmp(argv[1], "-h", 2) == 0 ||
			strncmp(argv[1], "--help", 6) == 0) {
			print_help();
			return 0;
		}
		else {
			a = 0;
			b = atoi(argv[1]);
			c = 1;
		}
	}
	else if (argc == 3) {
		a = atoi(argv[1]);
		b = atoi(argv[2]);
		c = 1;
	}
	else if (argc >= 4) {
		a = atoi(argv[1]);
		b = atoi(argv[2]);
		c = atoi(argv[3]);
	}

	if (c == 0)
		c = 1;

	if (c > 0) {
		for (int i = a; i < b; i += c) {
			cout << i;
			if (i < b - c)
				cout << ' ';
		}
	}
	else { // c < 0
		for (int i = a; i > b; i += c) {
			cout << i;
			if (i > b + c)
				cout << ' ';
		}
	}

	return 0;
}
