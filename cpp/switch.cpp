//
// Experiements with the switch construct.
//
#include <iostream>

using namespace std;

enum class OutputExpectedTo : bool { Change, NotChange };

static void f1( void );
static void f2( void );
static void check_change( OutputExpectedTo );

int main( int argc, char **argv )
{
	f1();
	f2();

	return 0;
}

void check_change( OutputExpectedTo change )
{
	switch (change)
	{
	case OutputExpectedTo::Change:
		cout << "Change" << endl;
		break;
	case OutputExpectedTo::NotChange:
		cout << "NotChange" << endl;
		break;
	default:
		cout << "Something Else" << endl;
		break;
	}
}

// Output:
//  Change
//  NotChange
//  Change
//  NotChange
//
// It appears that the cast reduces the input value to bit 0.
//
void f1( void )
{
	check_change( OutputExpectedTo::Change );
	check_change( OutputExpectedTo::NotChange );
	check_change( static_cast<OutputExpectedTo>( 2 ) );
	check_change( static_cast<OutputExpectedTo>( 3 ) );
}

// Initialize some variables with different syntax
void f2( void )
{
	int i { 11 };	// C++11
	int j (22);
	int k = 33;

	cout << i << '\t' << j << '\t' << k << endl;

	int a = int();
	int b {int(44)};
	int c = int(55);

	cout << a << '\t' << b << '\t' << c << endl;

	// a {66};  -- error: expected ‘;’ before ‘{’ token
	// b (77);  -- error: ‘b’ cannot be used as a function
}

