// int_types.cpp
// 

#include <iostream>

void print_sizes(void);

int main(int argc, char **argv)
{
    int errors = 0;

    print_sizes();

    return errors;
}

void print_sizes(void)
{
    std::cout << "char\t" << sizeof(char) << std::endl;
    std::cout << "short int\t" << sizeof(short int) << std::endl;
    std::cout << "int\t" << sizeof(int) << std::endl;
    std::cout << "long int\t" << sizeof(long int) << std::endl;
    std::cout << "long long\t" << sizeof(long long) << std::endl;
}

