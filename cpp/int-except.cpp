// Integer Exception example program

// Show how exceptions can throw simple integers "objects" that can be caught
// and evaluated by the handler.
//
// Note: In C++11 this behavior is deprecated.
// GCC says: 
//     warning: dynamic exception specifications are deprecated in C++11

#include <iostream>

enum IntegerException {
    Invalid = 999,
    None = 0,
    GeneralError,
    DivideByZero,
    NullPointer
};

float divide(int x, int y) throw(IntegerException);

int main(int argc, char *argv[])
{
    for (int i = -10; i <= +10; i++) {
        try {
            const int N = 1000;
            float f = divide(N, i);
            std::cout << N << " divided by " << i << " equals "
                << f << std::endl;
        } catch (IntegerException e) {
            std::cout << "divide() failed: ";
            if (e == DivideByZero)
                std::cout << "DivideByZero" << std::endl;
            else
                std::cout << "[" << e << "]" << std::endl;
        }
    }
    return 0;
}

float divide(int x, int y) throw(IntegerException)
{
    if (y == 0)
        throw DivideByZero;
    return ((float)x / (float)y);
}

