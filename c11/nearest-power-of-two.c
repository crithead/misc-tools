/* find the nearest power of two to the give number */

#include <stdio.h>
#include <assert.h>

unsigned int nearest_power_of_two(unsigned int n)
{
    unsigned int value = 0;
    unsigned int lower = 0, upper = 0;
    unsigned int i;

    for (i = 1; i < 32; i++)
    {
        value = ((unsigned int)1 << i);
        if (value >= n)
        {
            upper = i;
            lower = i - 1;
            break;
        }
    }

    if ((1 << upper) - n <= n - (1 << lower))
    {
        value = upper;
    }
    else
    {
        value = lower;
    }

    //printf("lower %d, n %d, upper %d\n", lower, n, upper);
    assert((1 << lower) <= n && n <= (1 << upper));

    return value;
}

#define MAX 20

int main(void)
{
    int i, n;
    int a = 0, b = 1, c;

    for (i = 1; i < MAX; i++)
    {
        c = a + b;
        a = b;
        b = c;

        n = nearest_power_of_two(a);
        printf("N = %6d\t%6d\n", a, n);
    }

    return 0;
}

