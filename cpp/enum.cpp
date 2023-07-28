//
// Derived enumerations
//
#include <iostream>

using namespace std;



// Enumerations can be derived from an "integral type"
enum Error : unsigned int
{
	NONE = 0,
	FIRST_ERROR = 1000,

	TYPE_ERROR,
	VALUE_ERROR,
	DIVIDE_BY_ZERO_ERROR,
	NULL_POINTER_ERROR,

	LAST_ERROR
};

enum Warning : unsigned int
{
	WARN_FIRST = Error::LAST_ERROR + 1,

	WARN_LOW_MEM,
	WARN_TIMEOUT,
	WARN_ELVIS_HAS_LEFT_THE_BUILDING,

	WARN_LAST
};

// Enumerations are NOT themselves an "integral type" so the following
// construct is an error.  That is, an enumeration cannot derive from
// another enumeration.
//
// g++ says:
//
// num.cpp:42:10: error: underlying type ‘A’ of ‘B’ must be an integral type
//
#if 0
enum A : int {
	AAAAA,
	AAAAB,
	AAAAC
};

enum B : A {
	BBBBB,
	BBBBC,
	BBBBD
};
#endif

int main( int argc, char **argv )
{
	cout << "NONE         : " << NONE << endl;
	cout << "FIRST_ERROR  : " << FIRST_ERROR << endl;
	cout << "LAST_ERROR   : " << LAST_ERROR << endl;
	cout << "WARN_FIRST   : " << WARN_FIRST << endl;
	cout << "WARN_LAST    : " << WARN_LAST << endl;

	return 0;
}
