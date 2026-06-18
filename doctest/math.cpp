/// @file A Library of useless math functions

#include <stdexcept>
#include "math.hpp"

// A plus B
int Plus(int a, int b) noexcept
{
    return a + b;
}

// A minus B
int Minus(int a, int b) noexcept
{
    return a - b;
}

// A times B
int Times(int a, int b) noexcept
{
    return a * b;
}

// A divided by B
int DividedBy(int a, int b)
{
    if (b == 0) {
        throw std::invalid_argument("Division by zero");
    }
    return a / b;
}
