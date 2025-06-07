/* square_root.c
 * Find the largest integer less than or equal to the square root of the 
 * given integer.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DOT putchar('.')

int isqrt(unsigned int n);
void test(void);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        test();
    } else {
        int n = atoi(argv[1]);
        printf("SQRT(%d)\t=%8d\t%f\n",
               n, isqrt(n), sqrt((double)n));
    }

    return 0;
}

int isqrt(unsigned int n)
{
    unsigned int result = 0;
    unsigned int stop = 1 << (8 * sizeof(unsigned int) - 2);
    unsigned int x = n;

    while (stop > x) {
        stop >>= 2;
        putchar('.');
    }

    while (stop != 0) {
        if (x >= result + stop) {
             x = x - (result + stop);
             result = result +  2 * stop;
        }
        result >>= 1;
        stop >>= 2;
        DOT;
    }

    return (int)result;
}

void test(void)
{
    int a = 0, b = 1, n, i;
    for (i = 0; i < 30; i++) {
        n = a + b;
        a = b;
        b = n;
        printf("SQRT(%d)\t= %8d\t%f\n",
               n, isqrt(n), sqrt((double)n));
    }
}
