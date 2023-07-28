//
// Random Password Generator
//
#include <cstring>
#include <iostream>
#include <random>
#include <string>

using namespace std;

struct Options;

static string Generate(const Options&);
static void GetOptions(int, char **, Options&);
static void PrintHelp(void);
static int RandInt(int, int);

static const char DIGIT[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'
};

static const char UPPER[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
    'U', 'V', 'W', 'X', 'Y', 'Z'
};

static const char LOWER[] = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
    'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
    'u', 'v', 'w', 'x', 'y', 'z'
};

static const char SYMBOL[] = {
    '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*',
    '+', ',', '-', '.', '/', ':', ';', '<', '=', '>',
    '?', '@', '[', '\\', ']', '^', '_', '`', '{', '|',
    '}', '~'
};

static const size_t DIGIT_WEIGHT = 2;
static const size_t LOWER_WEIGHT = 4;
static const size_t UPPER_WEIGHT = 4;
static const size_t SYMBOL_WEIGHT = 1;

static const size_t NUM_DIGIT = sizeof(DIGIT) / sizeof(DIGIT[0]);
static const size_t NUM_LOWER = sizeof(LOWER) / sizeof(LOWER[0]);
static const size_t NUM_UPPER = sizeof(UPPER) / sizeof(UPPER[0]);
static const size_t NUM_SYMBOL = sizeof(SYMBOL) / sizeof(SYMBOL[0]);
static const size_t NUM_THING = DIGIT_WEIGHT * NUM_DIGIT + 
        LOWER_WEIGHT * NUM_LOWER + SYMBOL_WEIGHT * NUM_SYMBOL +
        UPPER_WEIGHT * NUM_UPPER;


struct Options
{
    static const size_t MAX_WORD_LENGTH = 128;

    Options() : printHelp(false), useDigits(false), useLowers(false),
            useSymbols(false), useUppers(false), useWeights(false),
            digitsWeight(1), lowersWeight(1), symbolsWeight(1),
            uppersWeight(1), length(8), number(1) {}

    void Check(void) {
        if ( !(useDigits || useLowers || useUppers || useSymbols) )
            useLowers = true;   // the default is just lower case letters
        if ( useWeights ) {
            digitsWeight = DIGIT_WEIGHT;
            lowersWeight = LOWER_WEIGHT;
            symbolsWeight = SYMBOL_WEIGHT;
            uppersWeight = UPPER_WEIGHT;
        }
        if (length > MAX_WORD_LENGTH)
            length = MAX_WORD_LENGTH;
    }

    bool printHelp;
    bool useDigits;
    bool useLowers;
    bool useSymbols;
    bool useUppers;
    bool useWeights;
    size_t digitsWeight;
    size_t lowersWeight;
    size_t symbolsWeight;
    size_t uppersWeight;
    size_t length;
    size_t number;
};

string Generate( const Options& opts )
{
    char buffer[ Options::MAX_WORD_LENGTH + 1 ] = {0};

    char things[ NUM_THING ] = {0};
    size_t num_things = 0;

    if (opts.useDigits) {
        for ( size_t i = 0; i < DIGIT_WEIGHT; i++ ) {
            memcpy( things + num_things, DIGIT, NUM_DIGIT * sizeof(DIGIT[0]) );
            num_things += NUM_DIGIT;
        }
    }
    if (opts.useLowers) {
        for ( size_t i = 0; i < LOWER_WEIGHT; i++ ) {
            memcpy( things + num_things, LOWER, NUM_LOWER * sizeof(LOWER[0]) );
            num_things += NUM_LOWER;
        }
    }
    if (opts.useSymbols) {
        for ( size_t i = 0; i < SYMBOL_WEIGHT; i++ ) {
            memcpy( things + num_things, SYMBOL, NUM_SYMBOL * sizeof(SYMBOL[0]) );
            num_things += NUM_SYMBOL;
        }
    }
    if (opts.useUppers) {
        for ( size_t i = 0; i < UPPER_WEIGHT; i++ ) {
            memcpy( things + num_things, UPPER, NUM_UPPER * sizeof(UPPER[0]) );
            num_things += NUM_UPPER;
        }
    }
    //cout << "num_things " << num_things <<  ", NUM_THING " << NUM_THING << endl;

    for (size_t i = 0; i < opts.length; i++) {
        int index = RandInt( 1, num_things ) - 1;
        buffer[ i ] = things[ index ];
    }

    return string(buffer);
}

void GetOptions( int argc, char **argv, Options& opts)
{
    // TODO Convert to use getopt(3)
    // TODO Add option to not print the newline if only one word generated
    for (int i = 1; i < argc; i++ ) {
        if (argv[i][0] != '-')
            continue;

        if (argv[i][1] == 'h')
            opts.printHelp = true;
        else if (argv[i][1] == 'a')
            opts.useDigits = opts.useUppers = opts.useLowers = opts.useSymbols = true;
        else if (argv[i][1] == 'b')
            opts.useDigits = opts.useUppers = opts.useLowers = true;
        else if (argv[i][1] == 'c')
            opts.useUppers = opts.useLowers = true;
        else if (argv[i][1] == 'd')
            opts.useDigits = true;
        else if (argv[i][1] == 'u')
            opts.useUppers = true;
        else if (argv[i][1] == 'l')
            opts.useLowers = true;
        else if (argv[i][1] == 's')
            opts.useSymbols = true;
        else if (argv[i][1] == 'w')
            opts.useWeights = true;
        else if (argv[i][1] == 'n' && i + 1 < argc)
            opts.number = atoi( argv[ ++i ] );
        else if (argv[i][1] == 'L' && i + 1 < argc)
            opts.length = atoi( argv[ ++i ] );
        else
            cerr << "Unknown: " << argv[i] << endl;
    }
    opts.Check();
}

void PrintHelp(void )
{
    cout << endl;
    cout << "pwgen [-h] | [-dlsu] [-n N] [-m M]" << endl;
    cout << "    -h     Print help and exit" << endl;
    cout << "    -a     Use all (digit, lower, upper, symbol)" << endl;
    cout << "    -b     Use letters and digits (digit, lower, upper)" << endl;
    cout << "    -c     Use letters (lower, upper)" << endl;
    cout << "    -d     Use digits" << endl;
    cout << "    -l     Use lower case letters" << endl;
    cout << "    -s     Use symbols" << endl;
    cout << "    -u     Use upper case letters" << endl;
    cout << "    -n N   Generate N passwords" << endl;
    cout << "    -L M   Password length (max " << Options::MAX_WORD_LENGTH
         << ")" << endl;
    cout << "    -w     Use weights" << endl;
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

    if ( opts.printHelp) {
        PrintHelp();
        return 0;
    }

    for ( size_t i = 0; i < opts.number; i++ ) {
        string word = Generate( opts );
        cout << word << endl;
    }

    return 0;
}

