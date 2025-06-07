// bases.cpp
// (C) 2014 Donald Perkovich. All rights reserved.
// Convert numbers to their representation in multiple base systems.
//
// Command line arguments:
// -a       Enable all output types (binary)
// -b       Force following args to be interpreted as binary.
// -d       Force following args to be interpreted as decimal.
// -h       Force following args to be interpreted as hexidecimal.
// -n       Unset the force flag.
// -o       Force following args to be interpreted as octal.
//
// Compile with: --std=c++11

#include <cstdlib>
#include <cctype>
#include <iostream>
#include <iomanip>

enum arg_type_t { NONE, FLAG, HELP, BIN, OCT, DEC, HEX };

static arg_type_t force_type;
static bool print_binary;

static void print_help( void );
static arg_type_t get_type( const char * );
static void set_flag( const char * );
static int bin_str_to_int( const char * );
static int oct_str_to_int( const char * );
static int dec_str_to_int( const char * );
static int hex_str_to_int( const char * );
static const char *int_to_bin_str( int );

/// Convert numbers to their representation in various bases (2, 8, 10, 16).
/// @param argc The number of command line arguments.
/// @param argv An array of C strings containing command line arguments.
/// @return 0
int main( int argc, char *argv[] ) 
{
	force_type = NONE;
	print_binary = false;

	for ( int i = 1; i < argc; i++ ) {
		int n = 0;
		switch ( get_type( argv[ i ] ) ) {
		case NONE:
			std::cout << "Unrecognized argument: " << argv[ i ] << std::endl;
			break;
		case FLAG:
			set_flag( argv[ i ] );
			continue;
			break;
		case HELP:
			print_help();
			return 0;
			break;
		case BIN:
			n = bin_str_to_int( argv[ i ] );
			break;
		case OCT:
			n = oct_str_to_int( argv[ i ] );
			break;
		case DEC:
			//n = std::atoi( argv[ i ] );
			n = dec_str_to_int( argv[ i ] );
			break;
		case HEX:
			n = hex_str_to_int( argv[ i ] );
			break;
		default:
			break;
		}
		std::cout << argv[ i ] << ": 0x" << std::setbase( 16 ) << n
				<< " " << std::setbase( 10 ) << n
				<< " 0" << std::setbase( 8 ) << n;
		if ( print_binary )
			std::cout << " " << int_to_bin_str( n );
		std::cout << std::endl;
	}

	return 0;
}

/// get_type - Get the type of argument.
/// @param arg The argument string from the command line.
/// @return An appropriate 'arg_type_t' value.
/// Global: force_type (r)
///
/// Flags begin with '-'.
/// Binary numbers end in 'b' or 'B'.
/// Octal numbers start with a zero (0) followed by a digit in [0-7]
///     or end in 'o' or 'O'.
/// Decimal numbers are the default if it is not any other type.
/// Hex numbers begin with a zero (0) followed by a 'x' or 'X'
///     or end in 'h' or 'H' 
///
static arg_type_t get_type( const char *arg )
{
	arg_type_t type = NONE;

	if ( std::string( "--help" ).compare( arg ) == 0 ) {
		type = HELP;
	} else if ( arg[0] == '-' ) {
		type = FLAG;
	} else if ( force_type != NONE ) {
		type = force_type;
	} else {
		std::string s( arg );
		if ( s[0] == '0' && (s[1] == 'x' || s[1] == 'X') ) {
			type = HEX;
		} else if ( s[0] == '0' && (s[1] >= '0' && s[1] <=  '7') ) {
			type = OCT;
		} else if ( isalpha( s.back() ) ) {
			char last = tolower( s.back() );
			if ( last == 'h' )
				type = HEX;
			else if ( last == 'o' )
				type = OCT;
			else if ( last == 'b' )
				type = BIN;
			else
				type = NONE;
		} else {
			type = DEC;
		}
	}

	return type;
}

/// set_flag - Set the appropriate global flag for the given argument.
/// @param arg A C string argument.
/// Global: force_type (w), print_binary (w)
static void set_flag( const char *arg )
{
	if ( arg[1] == 'a' )
		print_binary = true;
	else if ( arg[1] == 'b' )
		force_type = BIN;
	else if ( arg[1] == 'o' )
		force_type = OCT;
	else if ( arg[1] == 'd' )
		force_type = DEC;
	else if ( arg[1] == 'h' )
		force_type = HEX;
	else if ( arg[1] == 'n' )
		force_type = NONE;
	else
		std::cerr << "Unknown flag: " << arg << std::endl;
}

/// bin_str_to_int - Converts a string represenation of a binary number to an
/// integer.
/// @param arg A String representing a binary number.
/// @return The integer value of the input string.
/// Note this function ignores any character not '0' or '1' so a separator can
/// be used to make the input more readable.  For example: 1010:1100
static int bin_str_to_int( const char *arg )
{
	int n = 0;
	std::string s( arg );

	for ( auto it = s.cbegin(); it != s.cend(); ++it ) {
		if ( *it == '0' )
			n = ( 2 * n );
		else if ( *it == '1' )
			n = ( 2 * n ) + 1;
	}

	return n;
}

/// oct_str_to_int - Converts a string represenation of a octal number to an
/// integer.
/// @param arg A String representing a octal number.
/// @return The integer value of the input string.
/// Note this function ignores any character not in [0-7] so a separator can
/// be used to make the input more readable.
static int oct_str_to_int( const char *arg )
{
	int n = 0;
	std::string s( arg );

	for ( auto it = s.cbegin(); it != s.cend(); ++it ) {
		if ( isdigit( *it ) && *it <= '7' )
			n = ( 8 * n ) + ( *it - '0' );
	}

	return n;
}

/// dec_str_to_int - Converts a string represenation of a decimal number to an
/// integer.
/// @param arg A String representing a decimal number.
/// @return The integer value of the input string.
/// Note this function ignores any non-digit character so a separator can
/// be used to make the input more readable. For example: 1,001,001
static int dec_str_to_int( const char *arg )
{
	int n = 0;
	std::string s( arg );

	for ( auto it = s.cbegin(); it != s.cend(); ++it ) {
		if ( isdigit( *it ) )
			n = ( 10 * n ) + ( *it - '0' );
	}

	return n;
}

/// hex_str_to_int - Converts a string represenation of a hexadecimal number to
/// an integer.
/// @param arg A String representing a hexadecimal number.
/// @return The integer value of the input string.
/// Note this function ignores any non-digit character so a separator can
/// be used to make the input more readable. For example: 0xABCD:E51A 
static int hex_str_to_int( const char *arg )
{
	int n = 0;
	std::string s( arg );

	if ( s[0] == '0' && (s[1] == 'x' || s[1] == 'X') )
		s = s.substr( 2 );

	for ( auto it = s.cbegin(); it != s.cend(); ++it ) {
		if ( isxdigit( *it ) ) {
			if ( *it <= '9' )
				n = ( 16 * n ) + ( *it - '0' );
			else if ( isupper( *it ) )
				n = ( 16 * n ) + ( 10 + *it - 'A' );
			else // islower
				n = ( 16 * n ) + ( 10 + *it - 'a' );
		}
	}

	return n;
}

/// int_to_bin_str - Convert an interger to a binary string.
/// This function maintains the string in an internal buffer and is therefore
/// not thread safe.
/// @param n An interger.
/// @return A pointer to a string (internal buffer) containg the string of
///         binary digits.
static const char *int_to_bin_str( int n )
{
	static std::string s;
	const int INTLEN = 8 * sizeof( int );
	bool seen_one = false;
	s.clear();
	for ( int i = INTLEN - 1; i >= 0; i-- ) {
		int mask = (1 << i);
		if ( n & mask ) {
			seen_one = true;
			s.push_back( '1' );
		} else if ( seen_one ) {
			s.push_back( '0' );
		}
	}
	return const_cast<const char *>( s.c_str() );
}

/// print_help - Prints a brief usage message.
static void print_help( void )
{
	std::cout << 
	"Convert numbers to their representation in multiple base systems.\n"
	<< "Command line arguments:\n"
	<< "  -a       Enable all output types (binary)\n"
	<< "  -b       Force following args to be interpreted as binary.\n"
	<< "  -d       Force following args to be interpreted as decimal.\n"
	<< "  -h       Force following args to be interpreted as hexidecimal.\n"
	<< "  -n       Unset the force flag.\n"
	<< "  -o       Force following args to be interpreted as octal.\n"
	<< std::endl;
}

