/*
    Series Approximation of 1 + 1/96
    
    1 + 1/96 = 1 + (1/64) - (1/256) - (1/1024) - (1/4096) - ...
             = 1 + (2^-6) - (2^-8) - (2^-10) - (2^-12) - ...
*/
#include "stdio.h"

double X = 1.0 + (1.0 / 96.0);

int main(int argc, char *argv[])
{
    int i;
    double diff, value = 1.0;

    printf("Calc Value:     %8e\n", X);
    diff = 100.0 * (X - value) / X;
    printf("%2d\tApprox: %8e\t%% diff: %8e\n", 0, value, diff);

    value += (double)(1.0 / (1 << (2*3)));
    diff = 100.0 * (X - value) / X;
    printf("%2d\tApprox: %8e\t%% diff: %8e\n", 3, value, diff);

    for (i = 4; i < 13; i++) {
        value += (double)(-1.0 / (1 << (2*i)));
        diff = 100.0 * (X - value) / X;
        printf("%2d\tApprox: %8e\t%% diff: %8e\n", i, value, diff);
    }

    return 0;
}
