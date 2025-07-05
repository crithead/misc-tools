
#include <cstdlib>
#include <iostream>
#include "math.hpp"

static constexpr int DEFAULT_A = 12;
static constexpr int DEFAULT_B = 5;

int main(int argc, char **argv)
{
    int a = DEFAULT_A;
    int b = DEFAULT_B;

    if (argc > 1) {
        a = std::atoi(argv[1]);
    }
    if (argc > 2) {
        b = std::atoi(argv[2]);
    }

    std::cout << "Plus: " << a << " plus " << b << "is " << Plus(a, b) << std::endl;
    std::cout << "Minus: " << a << " minus " << b << " is " << Minus(a, b) << std::endl;
    std::cout << "Times: " << a << " times " << b << " is " << Times(a, b) << std::endl;

    try {
        int quotient = DividedBy(a, b);
        std::cout << "DividedBy: " << a << " divided by " << b << " = "
            << quotient << std::endl;
    } catch (const std::invalid_argument &e) {
        std::cout << "DividedBy: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
