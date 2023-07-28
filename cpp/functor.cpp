//
// Functor example
// A functor is a class that overrides operator() to make it callable.
// It is a function with state.
//
// See also: python/functor.py
//

#include <iostream>

using namespace std;

class Thingy
{
public:
    Thingy() {}
    ~Thingy() {}

    void operator()(void) {
        cout << "operator()" << endl;
        one("apple");
        two("banana", "cherry");
    }

    void one(const char *a = "alpha" ) {
        cout << "one (" << a << ")" << endl;
    }

    void two(const char *a = "alpha", const char *b = "beta" ) {
        cout << "two (" << a << ", " << b << ")" << endl;
    }
};


// Add a constant value to a number
class Adder
{
public:
    Adder(int v) : value(v) {}

    int operator()(int n) const {
        return n + value;
    }

private:
    int value;
};


int main(void)
{
    cout << __FUNCTION__ << endl;

    Thingy t;
    t();

    const Adder a(11);
    int x = 10;
    cout << "x0 = " << x << ", x1 = " << a(x) << endl;
    x = 20;
    cout << "x0 = " << x << ", x1 = " << a(x) << endl;

    return 0;
}

