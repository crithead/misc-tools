// Modified word frequencies -- using map
// Fred Swartz 2001-12-11

#include <iostream>
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>


// ----------------------------------------------------------------------------
class thing
{
public:
    thing();
    thing(int, std::string &);
    thing(const thing&);
    ~thing();
    const std::string &name(void) const;
    int number(void) const;
private:
    std::string _name;
    int _number;
};

// std::map requires parameter-less constructor
thing::thing() {
    std::cout << "thing::thing()" << '\n';
    _number = 0;
    _name = "";
}

thing::thing(int number, std::string &name) {
    std::cout << "thing::thing(int,string)" << '\n';
    _number = number;
    _name = name;
}

thing::thing(const thing& that) {
    std::cout << "thing::thing(thing&)" << '\n';
    _number = that.number();
    _name = that.name();
}

thing::~thing() {
    std::cout << "thing::~thing()" << '\n';
}

const std::string &thing::name(void) const {
    std::cout << "thing::name()" << '\n';
    return _name;
}

int thing::number(void) const {
    std::cout << "thing::number()" << '\n';
    return _number;
}

// ----------------------------------------------------------------------------


int main(int argc, char *argv[])
{
    std::map<int, thing> *things; // map of things key on numbers
    std::string word;        // input buffer for words.

    srandom(time(0));

    std::cout << "new map<int,thing>" << std::endl;
    things = new std::map<int, thing>;

    //--- Read words/tokens from input stream
    while (std::cin >> word) {
        int key = (int)random();
        thing t(key, word);
        (*things)[key] = t;
    }

    //--- Write the number and the word.
    std::map<int, thing>::const_iterator iter;
    for (iter = things->begin(); iter != things->end(); ++iter) {
        // iterator->first is of type 'int' (the first map parameter type)
        int key = iter->first;
        // iterator->second is of type 'thing' (the second map parameter type)
        std::string na = iter->second.name();
        int nu = iter->second.number();
        std::cout
            << "key ............ : " << key << '\n'
            << "    thing.number : " << nu << '\n'
            << "    thing.name   : " << na << std::endl;
    }

    delete things;

    return 0;
} //end main

