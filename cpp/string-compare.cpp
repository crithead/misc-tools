// String Compare

#include <iomanip>
#include <iostream>
#include <string>


int main(void)
{
    std::string a("abcdefg");
    std::string b("abcdefg");
    std::string c("TUVWXYZ");

    std::cout << "a(" << a << ") == b(" << b << ")";
    if (a == b)
        std::cout << " --> TRUE" << std::endl;
    else
        std::cout << " --> FALSE" << std::endl;

    std::cout << "a(" << a << ") == c(" << c << ")";
    if (a == c)
        std::cout << " --> TRUE" << std::endl;
    else
        std::cout << " --> FALSE" << std::endl;


    const char *x = "abcdefg";
    const char *y = "abcdefg";
    const char *z = "TUVWXYZ";

    std::cout << "a(" << a << ") == x(" << x << ")";
    if (a == x)
        std::cout << " --> TRUE" << std::endl;
    else
        std::cout << " --> FALSE" << std::endl;
    std::cout << "a = " << (size_t)a.c_str() << std::endl; 
    std::cout << "x = " << (size_t)x << std::endl;

    std::cout << "x(" << x << ") == y(" << y << ")";
    if (x == y)
        std::cout << " --> TRUE" << std::endl;
    else
        std::cout << " --> FALSE" << std::endl;
    std::cout << "x = " << (size_t)x << std::endl; 
    std::cout << "y = " << (size_t)y << std::endl;

    std::cout << "x(" << x << ") == z(" << z << ")";
    if (x == z)
        std::cout << " --> TRUE" << std::endl;
    else
        std::cout << " --> FALSE" << std::endl;

    char *p = "abcdefg";
    char *q = "abcdefg";
    char *r = "TUVWXYZ";

    std::cout << "a(" << a << ") == p(" << p << ")";
    if (a == p)
        std::cout << " --> TRUE" << std::endl;
    else
        std::cout << " --> FALSE" << std::endl;
    std::cout << "a = " << (size_t)a.c_str() << std::endl; 
    std::cout << "p = " << (size_t)p << std::endl;

    std::cout << "p(" << p << ") == q(" << q << ")";
    if (p == q)
        std::cout << " --> TRUE" << std::endl;
    else
        std::cout << " --> FALSE" << std::endl;
    std::cout << "p = " << (size_t)p << std::endl; 
    std::cout << "q = " << (size_t)q << std::endl;

    std::cout << "x(" << x << ") == p(" << p << ")";
    if (x == p)
        std::cout << " --> TRUE" << std::endl;
    else
        std::cout << " --> FALSE" << std::endl;
    std::cout << "x = " << (size_t)x << std::endl; 
    std::cout << "p = " << (size_t)p << std::endl;

    std::cout << "p(" << p << ") == r(" << r << ")";
    if (p == r)
        std::cout << " --> TRUE" << std::endl;
    else
        std::cout << " --> FALSE" << std::endl;

    return 0;
}

