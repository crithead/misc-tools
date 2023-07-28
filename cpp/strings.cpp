// std::string experiments

#include <cstring>
#include <exception>
#include <iostream>
#include <string>

void default_string( void );

int main( int argc, char** argv )
{
    default_string();

    return 0;
}

void default_string( void )
{
    try {
        std::string s;
        std::cout << "string.size() = " << s.size() << std::endl;
        std::cout << "\"" << s << "\"" << std::endl;
        const char *cstr = s.c_str();
        std::cout << "strlen(cstr) = " << (int)strlen(cstr) << std::endl;
        std::cout << "\"" << cstr << "\"" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

