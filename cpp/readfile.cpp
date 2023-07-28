// Read File
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main (int argc, char *argv[])
{
    for (int f = 1; f < argc; f++) {
        cout << "---------- " << argv[f] << " ----------" << endl;

        ifstream in;
        in.open (argv[1], ifstream::in);

        for (int i = 1; !in.eof(); i++) {
            string line;
            getline(in, line);
            cout << setw(6) << i << ": " << line << endl;
        }

        cout << '\n' << endl;

        in.close();
    }

    return 0;
}
