/// @ingroup cppexp
/// @{
/// Pet class.  Contains details about a pet.

#ifndef PET_H
#define PET_H

#include <string>

using namespace std;

/// @class Pet
class Pet
{
public:
    Pet();
    ~Pet();
    int GetAge();           /*!< Get the Pet's age. */
    void SetAge(int);       /*!< Set the Pet's age. */
    string* GetName();      /*!< Get the Pet's name. */
    void SetName(string*);  /*!< Set the Pet's name. */

    string& AsString();     /*!< Pet class data as a string. */

private:
    int age;
    string *name;
};

#endif

/// @}

