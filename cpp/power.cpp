//
// Raise a number to a power.
//
#include <iostream>

static int raise1(int n, int p)
{
	if (p < 0)
		return 0;
	if (p == 0)
		return 1;
	if (p == 1)
		return n;
	return n * raise1(n, p - 1);
}

static const int NUM_NUMS = 18;

static const int NUMBERS[NUM_NUMS] = {
	-1, 0, 1, 2, 3, 4,
	-1, 0, 1, 2, 3, 4,
	 2, 2, 2, 2, 2, 2
};

static const int POWERS[NUM_NUMS] = {
	 2, 2, 2, 2, 2, 2,
	 3, 3, 3, 3, 3, 3,
	-1, 0, 1, 2, 3, 4
};

int main(int argc, char **argv)
{
	int i;
	for (i = 0; i < NUM_NUMS;  i++) {
		int n = NUMBERS[i];
		int p = POWERS[i];
		int r = raise1(n, p);
		std::cout << n << '^' << p << " = " << r << std::endl;
	}
}


