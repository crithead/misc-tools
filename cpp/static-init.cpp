//
// initialization of static objects
//

// https://en.cppreference.com/w/cpp/language/initialization
// Static initialization
// 1)   If permitted, Constant initialization takes place first (see Constant
//      initialization for the list of those situations). In practice,
//      constant initialization is usually performed at compile time, and
//      pre-calculated object representations are stored as part of the
//      program image. If the compiler doesn't do that, it still has to
//      guarantee that this initialization happens before any dynamic
//      initialization.
// 2)   For all other non-local static and thread-local variables, Zero
//      initialization takes place. In practice, variables that are going
//      to be zero-initialized are placed in the .bss segment of the program
//      image, which occupies no space on disk, and is zeroed out by the OS
//      when loading the program.

#include <cassert>
#include <iostream>
#include <vector>

using namespace std;

// A class that provides tables of lower case and upper case letters.
// This is a static class, but is not immutable (const), however it can
// run code to initialize the vectors.
class alphabet
{
public:
    static vector<char> lowers;
    static vector<char> uppers;

    static struct _init {
        _init() {
            for (int i = 0; i < 26; i++) {
                lowers.push_back('a' + i);
                uppers.push_back('A' + i);
            }
        }
    } _initializer;
};

// exec vector constructor for class member lowers
vector<char> alphabet::lowers;

// exec vector constructor for class member uppers
vector<char> alphabet::uppers;

// exec _init constructor for class member _initializer
alphabet::_init alphabet::_initializer;


// A class that provides immutable tables of digits.
class digits
{
public:
    // Since these are const, it should be safe to make them public.
    static const vector<char> octal;
    static const vector<char> decimal;

    // Since the hexidecimal vector is private, create some public
    // accessor functions.
    static size_t hexidecimal_size(void) {
        return hexidecimal.size();
    }
    static char hexidecimal_value(size_t index) {
        assert(0 <= index && index < hexidecimal.size());
        return hexidecimal[index];
    }
private:
    static const vector<char> hexidecimal;
};

// Initialize the vectors -- Cannot run code here to initialize const members.
const vector<char> digits::octal { '0', '1', '2', '3', '4', '5', '6', '7' };
const vector<char> digits::decimal {
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
const vector<char> digits::hexidecimal {
        '0', '1', '2', '3', '4', '5', '6', '7',
        '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };


static void every_other_lower(bool even = true);
static void every_other_hex(bool even = true);
static void every_other_octal(bool even = true);
static void every_other_upper(bool even = true);

int main( void )
{
    every_other_lower();
    every_other_lower(false);
    every_other_upper();
    every_other_upper(false);

    every_other_octal();
    every_other_octal(false);

    every_other_hex();
    every_other_hex(false);

    return 0;
}

void every_other_lower(bool evens)
{
    cout << "Every other letter : ";

    for (size_t i = evens ? 0 : 1;
            i < alphabet::lowers.size();
            i += 2 ) {
        cout << alphabet::lowers[i];
    }
    cout << endl;
}

void every_other_hex(bool evens)
{
    cout << "Every other octal  : ";

    for (size_t i = evens ? 0 : 1;
            i < digits::hexidecimal_size();
            i += 2 ) {
        cout << digits::hexidecimal_value(i);
    }
    cout << endl;
}

void every_other_octal(bool evens)
{
    cout << "Every other octal  : ";

    for (size_t i = evens ? 0 : 1;
            i < digits::octal.size();
            i += 2 ) {
        cout << digits::octal[i];
    }
    cout << endl;
}

void every_other_upper(bool evens)
{
    cout << "Every other letter : ";

    for (size_t i = evens ? 0 : 1;
            i < alphabet::uppers.size();
            i += 2 ) {
        cout << alphabet::uppers[i];
    }
    cout << endl;
}

