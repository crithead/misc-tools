// Calculate the Golden Ratio with the Fibonacci sequence
//
// Golden Ratio phi = (a + b) / a = a / b
//
#include <iomanip>
#include <iostream>
#include <cmath>

using namespace std;

double goldenRatio;

// Calculate the Golden Ratio directly
double CalcGoldenRatio(void)
{
    return (1.0 + sqrt(5.0)) / 2.0;
}

// Print the fibonacci sequence terms, the quotient of the second divided
// by the first, and the differnce between the quotient and the calculated
// Golden Mean.
void PrintTerm(int f1, int f2)
{
    double r = (double)f2 / (double)f1;
    cout << setw(12) << f1 << "\t"
         << setw(12) << f2 << "\t"
         << setprecision(16) << r << "\t"
         << setprecision(3) << (goldenRatio - r) << endl;
}

// Calculate the fibonacci sequence terms and print them in pairs.  Quit when
// the integer sum overflows.  Note that the ratio reaches the limit of a
// double precision floating point value before the integer values overflow.
void FibonacciSequence(void)
{
    int f1 = 1;
    int f2 = 1;

    PrintTerm(f1, f2);
    for (;;) {
        int sum = f1 + f2;
        f1 = f2;
        f2 = sum;
        if (f2 < f1) // int overflow
            break;
        PrintTerm(f1, f2);
    }
}

//////////////////////////////////////////////////////////////////////////////

int main (int argc, char * const argv[]) {

    // detect the number of significant digits in a double
    //    cout << "1/3 = " << setprecision(16)
    //         << ((double)1.0/(double)3.0) << endl;

    goldenRatio = CalcGoldenRatio();
    cout << "Calutaled Golden Ratio = " 
         << setprecision(16)
         << goldenRatio
         << endl;

    FibonacciSequence();

    return 0;
}

