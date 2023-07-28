#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	cout << "--- Type Size Info\n"
		 << "char          : " << sizeof(char) << '\n'
		 << "short int     : " << sizeof(short int) << '\n'
		 << "int           : " << sizeof(int) << '\n'
		 << "long int      : " << sizeof(long int) << '\n'
		 << "long long int : " << sizeof(long long int) << '\n'
		 << "float         : " << sizeof(float) << '\n'
		 << "double        : " << sizeof(double) << '\n'
		 << "long double   : " << sizeof(long double) << '\n'
		 << endl;


	return 0;
}
