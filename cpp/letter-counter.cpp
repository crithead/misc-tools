/**
 * Letter Counter 
 * Count letters in text and print a histogram of letter frequency.
 */

#include <cctype>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

static void count(ifstream& is);
static void normalize(void);
static void print(void);
static void stringify(void);

static int freq[26];
static int norm[26];

int main(int argc, char *argv[])
{
    bool freqstring = false;

    for (int i = 0; i < 26; i++)
           freq[i] = norm[i] = 0;

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i], "--string", 8) == 0) {
            freqstring = true;
            continue;
        }

        cout << "file: " << argv[i] << endl;
        ifstream in(argv[i]);
        if (in.is_open())
            count(in);
    }

    normalize();
    print();

    if (freqstring)
        stringify();

    return 0;
}

/**
 * Read characters from an open filestream and updating the frequency
 * information.  Freuency information is stored in a global array.
 * @param is An open ifstream.
 */
static void count(ifstream& is)
{
    while (!is.eof()) {
        char c;
        is >> c;
        if (isalpha(c)) {
            c = toupper(c);
            freq[c - 'A']++;
       }
    }
}

/**
 * Normailze the frequency data from raw count to percent of characters seen.
 * Operates on the global freuency array.
 */
static void normalize(void)
{
    int min = 0x7FFFFFFF;
    for (int i = 0; i < 26; i++) {
        if (freq[i] < min)
            min = freq[i];
    }

    if (min == 0) {
        cerr << __FUNCTION__ << ": min freq is zero, using 1" << endl;
        min = 1;
    }

    for (int i = 0; i < 26; i++)
        norm[i] = (int)((freq[i] / min) + 0.5); 
}
/**
 * Print frequency infomation.
 */
static void print(void)
{
    int total = 0;
    for (int i = 0; i < 26; i++)
        total += freq[i];
    for (int i = 0; i < 26; i++) {
        double f = (double)freq[i] / (double)total;
        cout << (char)('A' + i) << " : " 
             << setw(8) << setprecision(4) << f << '\t'
             << setw(8) << freq[i] << '\t' 
             << setw(8) << norm[i] << '\n'; 
    }
    cout << '[' << total << ']' << endl;
}

static void stringify(void)
{
    int n = 0;
    for (int i = 0; i < 26; i++)
        n += norm[i];
    cout << endl;
    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < norm[i]; j++) {
            cout << (char)('A' + i);
        }
    }
    cout << endl;
}

