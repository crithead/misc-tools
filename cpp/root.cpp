/*
    Print the end of a phrase that begin with the word "root"
*/

#include <iostream>
#include <random>

using namespace std;

static constexpr int NUM_PHRASES = 17;

static const char *PHRASES[NUM_PHRASES] = {
    "around",
    "canal",
    "cause analysis",
    "cause",
    "cellar",
    "complex",
    "directory",
    "for",
    "mean square",
    "nameserver",
    "of all evil",
    "of the matter",
    "of the problem",
    "out",
    "rot",
    "up",
    "vegetable",
};

int RandInt( int a, int b )
{
    static random_device generator;

    if (a > b) {
        int t = b;
        b = a;
        a = t;
    }

    uniform_int_distribution<int> distribution(a, b);
    return distribution(generator);
}


int main( int argc, char **argv )
{
    const int n = RandInt( 0, NUM_PHRASES - 1 );
    cout << PHRASES[ n ] << endl;

    return 0;
}

