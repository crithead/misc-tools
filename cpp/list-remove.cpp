// Experiment with removing elements from a std::list.
//
// This experiment operates on a list of pointers to objects.  Not a list
// of objects.
//
// The list::erase function returns an iterator to the element AFTER the one
// erased so it is necessary to back up one element if traversing through the
// list in a for loop.  Otherwise the loop will skip the element after the one
// erased.  Erase returns a new iterator to the element following the one
// erased.  That iterator should be used to continue traversing the list.
//
// list::remove finds and removes all elements with the specified value.
//

#include <iomanip>
#include <iostream>
#include <list>

using namespace std;

class thing
{
public:
    explicit thing( int v = -1 ) : value ( v ) {}
    ~thing() { cout << '~' << value << endl; value = 0; }
    int get() const { return value; }
    void set( int v ) { value = v; }
private:
    int value;
};

void print_list( const list<thing *>& things )
{
    for ( const thing *t : things )
        cout << setw(4) << t->get();
    cout << endl;
}

void erase_middle( std::list<thing *>& things )
{
    size_t m = things.size() / 2;
    size_t i = 0;
    list<thing *>::iterator it = things.begin();
    while ( it != things.end() ) {
        if ( i == m ) {
            thing *t = *it;
            it = things.erase( it ); // iterator to next element
            delete t;
        } else {
            ++it; // next element
        }
        i++;
    }
}

void append_value( std::list<thing *>& things, int v )
{
    things.push_back(new thing(v));
}

void remove_value( std::list<thing *>& things, int v )
{
    thing *x = nullptr;
    for ( thing *t : things ) {
        if ( t->get() == v ) {
            x = t;
            break;
        }
    }
    if ( x != nullptr ) {
        things.remove(x);
        delete x;
    }
}

int main( int argc, char **argv )
{
    list<thing *> things;

    for (int i = 10; i < 30; i += 5 )
        things.emplace_back( new thing( i ) );
    cout << "things has " << things.size() << " elements" << endl;

    print_list(things);
    remove_value(things, 25);   // remove last
    print_list(things);
    append_value(things, 30);
    append_value(things, 35);
    remove_value(things, 30);   // remove next to last
    print_list(things);
    append_value(things, 40);
    append_value(things, 45);
    remove_value(things, 45);   // remove last
    print_list(things);
    append_value(things, 50);
    append_value(things, 55);
    append_value(things, 60);
    print_list(things);

    cout << "things has " << things.size() << " elements" << endl;

    // delete all elements
    while (!things.empty()) {
        thing *t = things.front();
        things.pop_front();
        delete t;
    }

    cout << "things has " << things.size() << " elements" << endl;

    return 0;
}

