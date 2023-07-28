//
// Vector operations
//
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

static void DoDelete( void );
static void DoPushBack( void );
static void DoRemove( void );

static int RandInt( int a, int b );
static void Delete( std::vector<int>& v );
static void Delete2( std::vector<int>& v );
static void Populate( std::vector<int>& v, int n );
static void Print( std::vector<int>& v );
static void PushBack( std::vector<int>& v, int x );
static void SwapRemove( std::vector<int>& v, int x );

int main( int argc, char **argv )
{
    (void)argc;
    (void)argv;

    DoDelete();
    DoPushBack();
    DoRemove();

    return 0;
}

void DoDelete( void )
{
    std::cout << "=== " << __FUNCTION__ << std::endl;

    std::vector<int> v;

    Populate( v, 10 );
    Print( v );
    Delete( v );
    Print( v );
    Delete( v );
    Print( v );
    Delete( v );
    Print( v );
    Delete( v );
    Print( v );
    Delete( v );
    Print( v );

    Populate( v, 1000 );
    for ( int i = 0; i < 990; i++ )
        Delete( v );
    Print( v );

    Populate( v, 1000 );
    for ( int i = 0; i < 990; i++ )
        Delete2( v );
    Print( v );
}

void DoPushBack( void )
{
    std::cout << "=== " << __FUNCTION__ << std::endl;

    std::vector<int> v;

    Print( v );
    PushBack( v, 1111 );
    Print( v );
    PushBack( v, 2222 );
    Print( v );
    PushBack( v, 3333 );
    Print( v );
}

void DoRemove( void )
{
    std::cout << "=== " << __FUNCTION__ << std::endl;

    int x;
    std::vector<int> v;

    Populate( v, 10 );
    Print( v );
    x = v[ RandInt(0, v.size() - 1 ) ];
    SwapRemove( v, x );
    Print( v );

    x = v[ RandInt(0, v.size() - 1 ) ];
    SwapRemove( v, x );
    Print( v );

    x = v[ RandInt(0, v.size() - 1 ) ];
    SwapRemove( v, x );
    Print( v );
}

// Delete one random elements from a vector
// v the Vector
void Delete( std::vector<int>& v )
{
    const int s = static_cast<int>( v.size() );
    const int j = RandInt( 1, s ) - 1;
    const int k = s - 1;
    const int t = v[ k ];
    v[ k ] = v[ j ];
    v[ j ] = t;
    v.pop_back();
}

// Delete one random elements from a vector
void Delete2( std::vector<int>& v )
{
    const int s = static_cast<int>( v.size() );
    const int j = RandInt( 1, s ) - 1;
    auto it = v.begin();
    std::advance( it, j );
    // Over-write the current element with the back of the vector,
    // then shrink the size of the vector by 1.
    (void)std::move( v.back() );
    // or if you need to save the iterator position
    //*it = std::move( v.back() );
    v.pop_back();
}

// Put 'n' randon values into the vector 'v'
void Populate( std::vector<int>& v, int n )
{
    v.clear();
    v.resize( n );
    for ( int i = 0; i < n; i++ )
        v[ i ] = RandInt( 1000, 9999 );
}

// Print a vector's contents to the console
void Print( std::vector<int>& v )
{
    for ( auto value : v )
        std::cout << std::setw(8) << value;
    std::cout << std::endl;
}

// Append the element 'x' to the end of vector 'v'
void PushBack( std::vector<int>& v, int x )
{
    v.insert( v.cend(), x );
}

// Returns a random integer in the range from 'a' to 'b', inclusive
int RandInt( int a, int b )
{
    static std::random_device generator;

    if (a > b) {
        int t = b;
        b = a;
        a = t;
    }

    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

// Remove element 'x' from the vector 'v' by moving the last element into
// the position occupied by 'x'
void SwapRemove( std::vector<int>& v, int x )
{
    // Find X
    auto i = v.begin();
    while ( *i != x && i != v.end() )
        ++i;
    if ( i != v.end() ) {
        std::cout << "--- found " << x << std::endl;
        *i = std::move( v.back() );
        v.pop_back();
    }
    else {
        std::cout << "--- can't find " << x << std::endl;
    }
}

