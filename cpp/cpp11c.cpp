// C++11 Experiment with lambdas and function variables.
// GCC: Compile with "-std=c++11"

#include <iostream>

int main( int argc, char **argv )
{
    const int X = 11;
    const int Y = 22;

    auto f  = [](int x, int y) { return x + y; };

    int z = f( X, Y );
    std::cout << "X = " << X << std::endl;
    std::cout << "Y = " << Y << std::endl;
    std::cout << "X + Y = " << z << std::endl;

    return 0;
}

