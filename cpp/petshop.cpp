/// @ingroup cppexp
/// @{

/* C++ class experiments.
 *
 */
#include <iostream>
#include <iomanip>
#include <string>

#include "pet.hpp"

enum e1 {
    E_VAL1,
    E_VAL2 = 20,
    E_VAL3,
    E_VAL4 = E_VAL1,
    E_LAST
};

using namespace std;

int main(int argc, char *argv[])
{
    Pet *p = 0;

    cout << "*** Test Pet" << endl;
    
    p = new Pet();
    p->SetAge(4);
    p->SetName(new string("Fluffy"));
    string& s = p->AsString();
    cout << "Pet is " << s << endl;
    delete &s;
    delete p;

    p = new Pet();
    p->SetAge(6);
    p->SetName(new string("Fido"));
    s = p->AsString();
    cout << "Pet is " << s << endl;
    delete &s;
    delete p;

    p = new Pet();
    p->SetAge(1);
    p->SetName(new string("Polly"));
    s = p->AsString();
    cout << "Pet is " << s << endl;
    delete &s;
    delete p;

    cout << "E_VAL1 = " << E_VAL1 << endl;
    cout << "E_VAL2 = " << E_VAL2 << endl;
    cout << "E_VAL3 = " << E_VAL3 << endl;
    cout << "E_VAL4 = " << E_VAL4 << endl;
    cout << "E_LAST = " << E_LAST << endl;

    return 0;
}

/// @}

