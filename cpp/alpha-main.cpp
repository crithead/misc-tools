/// @ingroup cppexp
/// @{
/// Program to use the A, B, C class hierarchy defined in alpha.h/alpha.cpp.

#include <iostream>

#include "alpha.hpp"

/// Run class hierarchy demo.
/// @param argc Argument count
/// @param argv Argument vector
/// @retval 0 Always
int main(int argc, char **argv)
{
    // Give this instance of A a string
    A *a = new A;
    a->set_text("hammerhead");

    // Give the instance of B a number
    B *b = new B;
    b->set_number(576);

    // Give the instance of C and string and a number
    C *c = new C;
    c->set_text("hockeypuck");
    c->set_number(849);

    // Show the values stored in A, B, and C
    std::cout << "A::get_text() -> " << a->get_text() << std::endl;
    std::cout << "B::get_number() -> " << b->get_number() << std::endl;
    std::cout << "C::get_text() -> " << c->get_text() << std::endl;
    std::cout << "C::get_number() -> " << c->get_number() << std::endl;

    return 0;
}
/// @}

