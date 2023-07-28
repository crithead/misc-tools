// C++11 Experiments
// Compile with "--std=c++11"

#include <cstdlib>
#include <algorithm>
#include <iostream>

void auto_type_1( void );
void auto_type_2( void );



int main( int argc, char **argv )
{
    auto_type_1();
    auto_type_2();

    return 0;
}

void printi( int i )
{
    std::cout << i << ' ';
}

// Demonstrate use of auto variable type.
void auto_type_1( void )
{
    std::vector<int> v;
    // Auto for int
    for ( auto i = 0; i < 10; i++ )
        v.push_back( std::rand() % 1000 );
    std::sort( v.begin(), v.end() );
    // Auto for iterators
    for ( auto it = v.begin(); it != v.end(); ++it )
        std::cout << *it << ' ';
    std::cout << std::endl;
    // Ranged-for
    for ( auto i: v )
        std::cout << i << ' ';
    std::cout << std::endl;
    // For-each loop with function
    std::for_each( v.begin(), v.end(), printi );
    std::cout << std::endl;
    // For-each loop with lambda
    std::for_each( v.begin(), v.end(), [](int i){ std::cout << i << ' '; } );
    std::cout << std::endl;
}

// ranged-for and auto type deduction on an array
void auto_type_2( void )
{
    //int a[] = { 11, 22, 33, 44, 55, 66 };
    float a[] = { 11.11, 22.22, 33.33, 44.44, 55.55, 66.66 };
    for ( auto i : a )
        std::cout << i << ' ';
    std::cout << std::endl;
    // iterate over elements in an array
    for ( auto it = std::begin( a ); it != std::end( a ); it++ )
        std::cout << *it << ' ';
    std::cout << std::endl;
}

