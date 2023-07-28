//
// Run Time Type Identification
//
// RTTI only works on polymorphic objects.
// Polymorphic objects have at least one  virtual function.
//
// https://stackoverflow.com/questions/351845/finding-the-type-of-an-object-in-c
//
#include <iostream>
#include <typeinfo>

using namespace std;

class A {
public:
    explicit A(int v = 0) : value(v) {}
    virtual ~A() = default;
    int value;
};

class B : public A {};
class C : public A {};

static void DynamicCast(void);
static void TypeId(void);

int main( void )
{
    DynamicCast();
    TypeId();
    return 0;
}

//
// TYPE& dynamic_cast<TYPE&> (object);
// TYPE* dynamic_cast<TYPE*> (object);
//
static void DynamicCast(void)
{
    cout << __FUNCTION__ << endl;

}

//
// #include <typeinfo>
// string s = typeid(YourClass).name()
//
static void TypeId(void)
{
    cout << __FUNCTION__ << endl;

    B b;
    A& a = b;
    C c;
    A *a1 = &c;

    cout << "a is A: " << boolalpha << (typeid(a) == typeid(A)) << endl;
    cout << "a is B: " << boolalpha << (typeid(a) == typeid(B)) << endl;
    cout << "a is C: " << boolalpha << (typeid(a) == typeid(C)) << endl;

    cout << "b is A: " << boolalpha << (typeid(b) == typeid(A)) << endl;
    cout << "b is B: " << boolalpha << (typeid(b) == typeid(B)) << endl;
    cout << "b is C: " << boolalpha << (typeid(b) == typeid(C)) << endl;

    cout << "*a1 is A: " << boolalpha << (typeid(*a1) == typeid(A)) << endl;
    cout << "*a1 is B: " << boolalpha << (typeid(*a1) == typeid(B)) << endl;
    cout << "*a1 is C: " << boolalpha << (typeid(*a1) == typeid(C)) << endl;
}

