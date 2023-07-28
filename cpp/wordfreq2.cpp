// Modified word frequencies -- using map
// Fred Swartz 2001-12-11

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main() {
    map<string, string> *freq; // map of words and their frequencies
    string word;            // input buffer for words.

    cout << "new map<...>" << endl;
    freq = new map<string, string>;

    if (freq) {
        cout << "delete map<...>" << endl;
        delete freq;
        cout << "new map<...>" << endl;
        freq = new map<string, string>;
    } else {
        cout << "new map<...> failed" << endl;
        return 1;
    }

    //--- Read words/tokens from input stream
    while (cin >> word) {
        (*freq)[word] = word;
    }

    //--- Write the count and the word.
    map<string, string>::const_iterator iter;
    for (iter=freq->begin(); iter != freq->end(); ++iter) {
        cout << iter->second << " " << iter->first << endl;
    }
    return 0;
} //end main
