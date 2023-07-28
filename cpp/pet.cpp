#include "pet.h"

Pet::Pet(void)
{
    age = 0;
    name = 0;
}

Pet::~Pet(void)
{
    if (name)
        delete name;
}

int Pet::GetAge(void)
{
    return age;
}

void Pet::SetAge(int n)
{
    if (n >= 0)
        age = n;
}

string* Pet::GetName(void)
{
    return name;
}

void Pet::SetName(string *s)
{
    name = s;
}

/* returns a ref to a dynamically allocated string; caller must delete. */
string& Pet::AsString(void)
{
    char n[32];
    sprintf(n, "%d", age);
    string &r = *(new string);
    r = "Name: " + *name + ", Age: " + n;
    return r;
 }
 
