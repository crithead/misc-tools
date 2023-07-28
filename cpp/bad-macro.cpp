//
// Test misbeavior in macros used as functions
//
#include <iostream>

using namespace std;

static bool _enable = true;

// Bad: does not protect if-block
#define PRINT1(A) \
    if (_enable) { cout << (A) << endl; }

#define PRINT2(A,B) \
    do { \
        if (_enable) { cout << (A) << ", " << (B) << endl; } \
    } while (false)

int main(int argc, char **argv)
{
    // With the semi-colon, this first part does not compile.
    // Without the semi-colon, the compiler give a warning
    //     warning: suggest explicit braces to avoid ambiguous
    //     "else" [-Wparentheses]
    // And the else binds to the 'if' in the macro so it depends on the
    // value of '_enable', not argc
    if (argc > 1)
        PRINT1(argv[1]) // ; (semi-colon) prevents this from compiling
    else
        cout << "No arguments present" << endl;

    if (argc > 2)
        PRINT2(argv[1], argv[2]);
    else
        cout << "At most one argument present" << endl;

    return 0;
}

