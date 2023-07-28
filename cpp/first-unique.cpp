/* (phone) Interview question from Beth at Apple on 2011-01-13
 *
 * Write a function that returns the first number that appears only once in
 * in an array.
 */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>

int FirstUnique(int *array, int length)
{
	int i, j;
	for (i = 0; i < length; i++ ) {
		for (j = i + 1; j < length; j++) {
			if (array[i] == array[j])
				break;
		}
		if (j == length && i != length - 1)
			return array[i];
	}
	return -1;
}


int main (int argc, char *argv[])
{
	int i, a[200];
	srand(time(0));
	for (i = 0; i < 200; i++)
		a[i] = rand() % 100;
	for (i = 0; i < 200; i++)
		std::cout << std::setw(4) << a[i];
	std::cout << "\n\n\n" << FirstUnique(a, 200) << std::endl;

	for (i = 0; i < 100; i++)
		a[i] = i + 1;
	for (i = 0; i < 100; i++)
		std::cout << std::setw(4) << a[i];
	std::cout << "\n\n\n" << FirstUnique(a, 100) << std::endl;

	for (i = 0; i < 50; i++)
		a[i] = a[i+50] = 2 * (i + 1);
	for (i = 0; i < 100; i++)
		std::cout << std::setw(4) << a[i];
	std::cout << "\n\n\n" << FirstUnique(a, 100) << std::endl;
	return 0;
}

