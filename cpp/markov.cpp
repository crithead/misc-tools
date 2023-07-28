//
// TODO Finish the generator.
//
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef vector<string> string_vector_type;

static map<string,string_vector_type> *words = 0;

void Init(void)
{
    //cout << "--- " << __FUNCTION__ << endl;

    words = new map<string,string_vector_type>;
}

string *NextWord(ifstream &in)
{
    string *s = new string("");
    int c;

    if (!in) {
        delete s;
        return 0;
    }

    c = in.get();
    while (in && !isalpha(c))
        c = in.get();
    if (!in) {
        delete s;
        return 0;
    }
    s->append(1,c);

    c = in.get();
    while (in && isalpha(c)) {
        s->append(1,c);
        c = in.get();
    }

    //cout << __FUNCTION__ << " : s = " << *s << endl;
    return s;
}

// Read from file, parse into words and put into a map
void ReadWords(string &filename)
{
    //cout << "--- " << __FUNCTION__ << endl;

    ifstream file;
    file.open(filename.c_str(), ifstream::in);

    if (!file) {
        perror(filename.c_str());
        return;
    }

    string *first = NextWord(file);
    string *second = NextWord(file);

    while (first) {
        if (first->length() > 0 && second->length() > 0) {
            transform(first->begin(), first->end(), first->begin(),
                      static_cast<int(*)(int)>(tolower));
            transform(second->begin(), second->end(), second->begin(),
                      static_cast<int(*)(int)>(tolower));
            //string_vector_type *v = &((*words)[*first]);
            //if (v)
            //    v->push_back(*second);
            ((*words)[*second]).push_back(*first);
        }
        delete second;
        second = first;
        first = NextWord(file);
    }

    file.close();
    //cout << "--- " << __FUNCTION__ << endl;
}

void WriteWords(void)
{
    //cout << "--- " << __FUNCTION__ << endl;

    for (map<string,string_vector_type>::iterator i = words->begin();
         i != words->end();
         ++i)
    {
        cout << i->first << ":";
        for(string_vector_type::iterator j = i->second.begin();
            j != i->second.end();
            j++)
        {
            cout << " " << *j;
        }
        cout << endl;
    }

    //cout << "--- " << __FUNCTION__ << endl;
}




int main(int argc, char *argv[])
{
    Init();

    for (int i = 1; i < argc; i++) {
        string filename(argv[i]);
        ReadWords(filename);
    }

    WriteWords();

    return 0;
}
