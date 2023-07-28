// Experiment with erasing elements from the middle of a std::list.

// The list::erase function returns an iterator to the element AFTER the one
// erased so it is necessary to back up one element if traversing through the
// list in a for loop.  Otherwise the loop will skip the element after the one
// erased.  Erase "increments" the iterator in the act of removing the element
// it refers to.

#include <list>
#include <iostream>
#include <iomanip>


void print_int_list( const std::list<int>& lst )
{
    std::list<int>::const_iterator cit;
    for ( cit = lst.begin(); cit != lst.end(); ++cit )
        std::cout << std::setw(4) << *cit;
    std::cout << std::endl;
}

void print_or_erase_middle( std::list<int>& lst )
{
#if 0
    int i;
    int m = lst.size() / 2;
    std::list<int>::iterator it;
    for ( i = 0, it = lst.begin(); it != lst.end(); ++it, ++i ) {
        if ( i == m ) {
            it = lst.erase( it ); // "increments" the iterator
            --it; // decrement the iterator to undo the erase's "increment"
        } else {
            std::cout << std::setw(4) << *it;
        }
    }
    std::cout << std::endl;
#else
    int m = lst.size() / 2;
    int i = 0;
    std::list<int>::iterator it = lst.begin();
    while ( it != lst.end() ) {
        if ( i == m ) {
            it = lst.erase( it ); // "increments" the iterator
        } else {
            std::cout << std::setw(4) << *it;
            ++it; // next element
        }
        i++;
    }
    std::cout << std::endl;
#endif
}

int main( int argc, char **argv )
{
    std::list<int> L;
    for (int i = 11; i < 100; i+= 11 )
        L.push_back( i );
    print_int_list( L );
    print_or_erase_middle( L );
    print_int_list( L );

    return 0;
}

