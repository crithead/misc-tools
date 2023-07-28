// alt-token.cpp
//
// A Basic C++ program ...
// that displays how to use some of the "alternative tokens" defined in
// C and C++
//
#include <iostream>
#include <iomanip>

using namespace std;

static void c_alternative_tokens( void );

int main( int argc, char **argv )
{
	cout << __FUNCTION__ << endl;

	c_alternative_tokens();

	return 0;
}

// These macros are defined in iso646.h in C
// They are operator keywords in C++98
void c_alternative_tokens( void )
{
	cout << __FUNCTION__ << endl;

	// and &&
	cout << "true and false = " << (true and false) << endl;
	cout << "true and true = " << (true and true) << endl;

	// and_eq &=
	unsigned char x = 0xAA;
	x and_eq 0x5A;
	cout << "x = 0xAA; x and_eq 0x5A; x = " << static_cast<unsigned int>( x ) << endl;
	// bitand &
	cout << "0xAA bitand 0x55 = " << (0xAA bitand 0x55) << endl;
	// bitor |
	cout << "0xAA bitor 0x55 = " << (0xAA bitor 0x55) << endl;

	// compl ~
	cout << "compl 0xAAAAAAAA = 0x" << hex << (compl 0xAAAAAAAA) << endl;

	// not !
	// not_eq !=
	// or ||
	// or_eq
	// xor ^
	// xor_eq ^=
}

