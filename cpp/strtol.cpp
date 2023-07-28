// How does strtol() work?
//
#include <cstdlib>
#include <cctype>
#include <iostream>

int main(int argc, char **argv)
{
    char *end;
    int n;

    // match agaist a string on only digits
    // end points to the string terminator '\0'
    const char *s1 = "12345";
    n = strtol(s1, &end, 10);
    std::cout << "n = " << n << std::endl;
    if (*end != 0)
        std::cout << "End not NULL" << std::endl;

    const char *s2 = "12R45";
    n = strtol(s2, &end, 10);
    std::cout << "n = " << n << std::endl;
    if (*end != 0)
        std::cout << "End not NULL" << std::endl;

    // end points at first character (not '\0')
    const char *s3 = "abcde";
    n = strtol(s3, &end, 10);
    std::cout << "n = " << n << std::endl;
    if (*end != 0)
        std::cout << "End not NULL" << std::endl;

    return 0;
}
