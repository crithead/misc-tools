/**
 * @file  three_bits.c
 * @brief Print the sum of numbers from 1 to 100 that have only three bits on.
 *
 * This is a solution program to an interview test question.  The Problem
 * statement is "Write a program that prints the sum of the numbers from 1
 * to 100 that have only three bits set to 1."  This tests the applicant's
 * understanding of binary data structure and ability to write a small C
 * program.
 */
#include <stdio.h>

/**
 * @def   DEBUG
 * @brief Enable/Disable debug print messages.
 */
#define DEBUG if(0)

static int number_of_bits_on(int);

/**
 * @brief Print sum of digits in [1,100] with 3 bits on.
 * @param argc Ignored.
 * @param argv Ignored.
 */
int main(int argc, char *argv[])
{
	int sum = 0;
	int i;
	for (i = 1; i <= 100; i++) {
		if (number_of_bits_on(i) == 3)
			sum += i;
		DEBUG printf("%4d,  bits on %4d\n", i, number_of_bits_on(i));
	}
	printf("sum %d\n", sum);
	return 0;
}

/**
 *  @brief  Count the number of 1 bits in a number.
 *  @param  n The number whose 1 bits are to be counted.
 *  @return The number of 1 bits in the input number.
 */
static int number_of_bits_on(int n)
{
	unsigned int count = 0;
	unsigned int n_bits = 8 * sizeof(int);
	unsigned int i;
	for (i = 0; i < n_bits; i++) {
		if (((unsigned int)n >> i) & 1)
			count++;
	}
	return count;
}
