// Check that the dice functions from drifter v3 do what they are supposed to.
// Turns out, they do!

#include <fstream>
#include <iostream>
#include <random>

static void Save( const char *savefile, int *array, int a, int b )
{
    std::ofstream f( savefile );
    for ( int i = 0; i <= b - a + 1; i++ )
        f << a + i << '\t' << array[ i ] << '\n';
    f.close();
}

// Shared generator
static std::random_device generator;

static int RandInt( int a, int b )
{
    if (a > b) {
        int t = b;
        b = a;
        a = t;
    }

    std::uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}

static size_t RandUInt( size_t a, size_t b )
{
    if (a > b) {
        size_t t = b;
        b = a;
        a = t;
    }

    std::uniform_int_distribution<size_t> distribution(a, b);
    return distribution(generator);
}

static void GetDice( int step, int& a, int& b, int& c )
{
    if ( step > 3 ) {
        a = b = c = ( step / 3 ) * 2;
        if ( step % 3 == 0 )
            a -= 2;
        else if ( step % 3 == 2 )
            c += 2;
    }
    else {
        a = b = c = 1;
    }
}

static int Roll3d( int n )
{
    int value = 0;

    if ( n < 1 ) {
        value = 0;
    }
    else if ( n < 4 ) {
        value = n;
    }
    else {
        int d1, d2, d3;
        GetDice( n, d1, d2, d3 );
        value = RandInt( 1, d1 ) + RandInt( 1, d2 ) + RandInt( 1, d3 );
    }

    return value;
}

void DoRandInt( const int N )
{
    const int A = 10;
    const int B = 90;
    int counts[ B - A + 1 ] = {0};
    int under = 0;
    int over = 0;

    for ( int i = 0; i < N; i++ ) {
        int x = RandInt( A, B );
        if ( x < A )
            under++;
        else if ( x > B )
            over++;
        else
            counts[ x - A ]++;
    }

    std::cout << "--- DoRandInt" << std::endl;
    std::cout << "under " << under << std::endl;
    std::cout << "over  " << over << std::endl;

    Save( "ddri.csv", counts, A, B );
}

void DoRandUInt( const int N )
{
    const size_t A = 10;
    const size_t B = 90;
    int counts[ B - A + 1 ] = {0};
    int under = 0;
    int over = 0;

    for ( int i = 0; i < N; i++ ) {
        size_t x = RandUInt( A, B );
        if ( x < A )
            under++;
        else if ( x > B )
            over++;
        else
            counts[ x - A ]++;
    }

    std::cout << "--- DoRandUInt" << std::endl;
    std::cout << "under " << under << std::endl;
    std::cout << "over  " << over << std::endl;

    Save( "ddru.csv", counts, A, B );
}

void DoRoll3d( const int N )
{
    const int M = 100;
    const int A = 3;
    const int B = 2 * M;
    int counts[ B - A + 1 ] = {0};
    int under = 0;
    int over = 0;

    for ( int i = 0; i < N; i++ ) {
        size_t x = Roll3d( M );
        if ( x < A )
            under++;
        else if ( x > B )
            over++;
        else
            counts[ x - A ]++;
    }

    std::cout << "--- DoRandUInt" << std::endl;
    std::cout << "under " << under << std::endl;
    std::cout << "over  " << over << std::endl;

    Save( "ddr3.csv", counts, A, B );
}



int main( int argc, char **argv )
{
    (void)argc;
    (void)argv;
    const int N = 1000000;

    DoRandInt( N );
    DoRandUInt( N );
    DoRoll3d( N );

    return 0;
}
