// stringy.cpp
// test std:string behavior

#include <iostream>
#include <string>

using namespace std;

int main()
{
    //string s(0); // not legal -- throws std::logic_error
    string s("");
    cout << "s: " << s << endl;

    return 0;
}
