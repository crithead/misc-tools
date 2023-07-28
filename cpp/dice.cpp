//
// Dice -- Generate and print random numbers
//
#include <cassert>
#include <cctype>
#include <iostream>
#include <random>
#include <string>

using namespace std;

struct Options;

static void Generate(const Options&);
static void GetOptions(int, char **, Options&);
static void PrintHelp(void);
static int RandInt(int, int);

struct Options
{
    Options() : perLine(false), printHelp(false), verbose(false),
            multiple(1), number(1), sides(6), adjustment(0) {}
    void Check(void) {
        assert(multiple > 0);
        assert(number > 0);
        assert(sides > 0);
    }
    void Print(void) {
        cerr << "perLine    : " << (perLine ? "true" : "false") << endl;
        cerr << "printHelp  : " << (printHelp ? "true" : "false") << endl;
        cerr << "verbose    : " << (verbose ? "true" : "false") << endl;
        cerr << "adjustment : " << adjustment << endl;
        cerr << "multiple   : " << multiple << endl;
        cerr << "number     : " << number << endl;
        cerr << "sides      : " << sides << endl;
    }

    bool perLine;
    bool printHelp;
    bool verbose;
    int multiple;       // number of dice to roll
    int number;         // number of times to roll the dice
    int sides;          // number of sides per die
    int adjustment;     // add per roll
};

static const char SPACE = ' ';

void Generate( const Options& opts )
{
    for (int n = 0; n < opts.number; n++) {
        int sum = opts.adjustment;
        for (int m = 0; m < opts.multiple; m++)
            sum += RandInt( 1, opts.sides );
        cout << sum;
        if (opts.perLine)
            cout << endl;
        else if (n < opts.number - 1)
            cout << SPACE;
    }
}

void GetOptions( int argc, char **argv, Options& opts)
{
    bool ok = false;
    int adjustment = 0;
    int multiple = 0;
    int sides = 0;
    size_t pos = string::npos;

    for (int i = 1; i < argc; i++ ) {
        string value( argv[i] );

        if (value == "--help" || value == "-h") {
            opts.printHelp = true;
        }
        else if (value == "--line" || value == "-l") {
            opts.perLine = true;
        }
        else if (value == "--verbose" || value == "-v") {
            opts.verbose = true;
        }
        else if (value.find('x') != string::npos) {
            opts.number = stoi(value);
        }
        else {
            // Parse MdS+A
            // TODO Handle missing M
            pos = value.find('d');
            if (pos != string::npos) {
                multiple = stoi(value.substr(0, pos), nullptr, 10);
                sides = stoi(value.substr(pos + 1), nullptr, 10);
                ok = true;
            }
            pos = value.find('+');
            if (pos != string::npos) {
                adjustment = stoi(value.substr(pos), nullptr, 10);
            }
            else {
                pos = value.find('-');
                if (pos != string::npos)
                    adjustment = stoi(value.substr(pos), nullptr, 10);
            }
        }
    }

    if (ok) {
        opts.adjustment = adjustment;
        opts.multiple = multiple;
        opts.sides = sides;
    }
    opts.Check();
}

void PrintHelp(void )
{
    cout << endl;
    cout << "dice [--help] | [--line] [Nx] MdS [+-A]" << endl;
    cout << "    -h, --help     Print help and exit" << endl;
    cout << "    -l, --line     Print one value per line" << endl;
    cout << "    -v, --verbose  Print debugging information" << endl;
    cout << "    Nx             Roll the dice N times" << endl;
    cout << "    MdS+A          Roll [1, S] M times and add A" << endl;
    cout << "                   Default: 1x 1d6+0" << endl;
    cout << endl;
}

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

//
//
//
int main( int argc, char **argv )
{
    Options opts;
    GetOptions( argc, argv, opts );

    if (opts.verbose)
        opts.Print();

    if ( opts.printHelp) {
        PrintHelp();
        return 0;
    }

    Generate( opts );

    return 0;
}

