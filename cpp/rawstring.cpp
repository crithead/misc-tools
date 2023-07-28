#include <iostream>
#include <string>

using namespace std;

int main( void )
{
    // This line is processes by the compiler so the '\n' characters are
    // turned into 0x0A (newline).  It prints out on three lines.
    string normal_str = "First line.\nSecond line.\nThird line.\n";
    cout << normal_str << endl;

    // This line is a raw string literal and the compiler does not process
    // the escaped characters so they appear as-is in the output.
    string raw_str = R"(First line.\nSecond line.\nThird line.\n)";
    cout << raw_str << endl;

    return 0;
}

