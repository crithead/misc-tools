// primes.cpp
//
// Functions to find the prime numbers.
// g++ -Wall primes.cpp -o primes --std=c++11
//
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <stdexcept>

struct options {
	bool show_help;
	bool show_factors;
	unsigned int min_value;
	unsigned int max_value;

	options( int argc, char **argv ) :
			show_help( false ), show_factors( false ),
			min_value( 0 ), max_value( 0 )
	{
		for ( int i = 1; i < argc; i++ ) {
			if ( strncmp( argv[ i ], "--help", 6 ) == 0 )
				show_help = true;
			else if ( strncmp( argv[ i ], "--factor", 8 ) == 0 )
				show_factors = true;
			else if ( min_value == 0 )
				min_value = static_cast<unsigned int>( atoi( argv[ i ] ) );
			else
				max_value = static_cast<unsigned int>( atoi( argv[ i ] ) );
		}
		if ( min_value == 0 )
			min_value = 1;
		if ( max_value == 0 || max_value < min_value )
			max_value = min_value;
	}
};

static bool is_prime( unsigned int n );
static std::list<unsigned int>& prime_factors_of( unsigned int n );

static void print_primes( unsigned int min, unsigned int max );
static void print_prime_factors( unsigned int min, unsigned int max );

static void show_help( void );

int main( int argc, char **argv )
{
	options args( argc, argv );

	if ( args.show_help ) {
		show_help();
		exit( 0 );
	}

	if ( args.show_factors )
		print_prime_factors( args.min_value, args.max_value );
	else
		print_primes( args.min_value, args.max_value );

	return 0;
}

bool is_prime( unsigned int n )
{
	if ( n < 2 )
		return false;
	if ( n % 2 == 0 )
		return false;
	if ( n % 3 == 0 )
		return false;

	unsigned int sqrt_n = static_cast<unsigned int>( sqrt( n ) );
	for ( unsigned int i = 5; i <= sqrt_n; i++ ) {
		if ( n % i == 0 )
			return false;
	}

	return true;
}

#if 0
static unsigned int smallest_prime_factor_of( unsigned int n )
{
	// TODO implement this
	return 0;
}
#endif//0

std::list<unsigned int>& prime_factors_of( unsigned int n )
{
	std::list<unsigned int> *factors = new std::list<unsigned int>;
	if ( factors == nullptr )
		throw std::runtime_error( "new failed on list" );

	// Exit immediately if N is 0 or 1
	if ( n < 2 )
		return *factors;

	const unsigned int sqrt_n = static_cast<unsigned int>( sqrt( n ) );

	// Factor out all 2s
	while ( n % 2 == 0 ) {
		factors->push_back( 2 );
		n /= 2;
	}

	// Check all odd numbers between 3 and SQRT(N)
	for ( unsigned int i = 3; i <= sqrt_n; i += 2 ) {
		if ( n % i == 0 ) {
			factors->push_back( i );
			n /= i;
		}
	}

	// If N > 1, then it is a prime factor so add it to the list
	if ( n > 2 )
		factors->push_back( n );

	return *factors;
}

void print_primes( unsigned int min, unsigned int max )
{
	if ( min < 1 )
		throw std::invalid_argument( "invalid min");
	if ( max < 1 )
		throw std::invalid_argument( "invalid max" );
	if ( min > max )
		throw std::invalid_argument( "min greater than max" );

	for ( unsigned int i = min; i <= max; i++ ) {
		if ( is_prime( i ) )
			std::cout << std::setw(8) << i;
	}
	std::cout << std::endl;
}

void print_prime_factors( unsigned int min, unsigned int max )
{
	if ( min < 1 )
		throw std::invalid_argument( "invalid min");
	if ( max < 1 )
		throw std::invalid_argument( "invalid max" );
	if ( min > max )
		throw std::invalid_argument( "min greater than max" );

	for ( unsigned int i = min; i <= max; i++ ) {
		std::cout << std::setw(8) << i << ": ";
		std::list<unsigned int>& factors = prime_factors_of( i );
		for ( auto i = factors.begin(); i != factors.end(); ++i ) {
			std::cout << std::setw(8) << *i;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void show_help( void )
{
	std::cout << "\n\t" << "primes [ --help ] [ --factor ] MIN MAX" << '\n'
			<< std::endl; 
}
