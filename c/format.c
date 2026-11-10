/**
 * Print format examples.
 */

#include <stdio.h>

#define LEN(A) (sizeof(A)/sizeof(A[0]))

static void decimal_precision(void);

int main(void)
{
    decimal_precision();

    return 0;
}

/**
 * Demonstrate how setting a precision on a decimal field affects the output.
 */
static void decimal_precision(void)
{
    int numbers[] = { 0, 1, 22, 333, 4444, 55555, 666666, 7777777, 88888888, 999999999 };

    for (int i = 0; i < LEN(numbers); i++ ) {
        printf("%%1.1d\t%1.1d\n", numbers[i]);
        printf("%%2.2d\t%2.2d\n", numbers[i]);
        printf("%%3.3d\t%3.3d\n", numbers[i]);
        printf("%%4.4d\t%4.4d\n", numbers[i]);
        printf("%%2.4d\t%2.4d\n", numbers[i]);
        printf("%%4.2d\t%4.2d\n\n", numbers[i]);
    }
}

