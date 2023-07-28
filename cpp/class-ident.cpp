/* Class Ident
 * Class Identification in an inheritance hierarchy
 *
 * Note: The base class (Bird) MUST have at least one virtual method for RTTI
 * to correctly identify classes in an inheritance hierarchy.  This applies
 * to the use of typeid() as well as the dynamic_cast<> operator.
 */

#include <iostream>
#include <string>
#include <typeinfo>


#define USE_CAST 1

#define BOOLTOSTR(B) ((B)?"true":"false")

class Bird
{
public:
    Bird() {
        name = "birdy";
    }
    virtual ~Bird() {} // This definition is neccessary for RTTI to work.
    friend std::ostream& operator<<(std::ostream& s, Bird& b) {
        s << b.name;
        return s;
    }
    std::string name;
};

class Duck : public Bird
{
public:
    Duck() {
        name = "ducky";
    }
};

class Goose : public Bird
{
public:
   Goose() {
        name = "goosey";
    }
};

bool IsADuck(Bird *b)
{
#if USE_CAST
    return dynamic_cast<Duck*>(b) != NULL;
#else
    std::cout << __FUNCTION__ << " [" << typeid(*b).name()
            << "] == [" << typeid(Duck).name() << "]" << std::endl;
    return typeid(*b) == typeid(Duck);
#endif
}

bool IsAGoose(Bird *b)
{
#if USE_CAST
    return dynamic_cast<Goose*>(b) != NULL;
#else
    std::cout << __FUNCTION__ << " [" << typeid(*b).name()
            << "] == [" << typeid(Goose).name() << "]" << std::endl;
    return typeid(*b) == typeid(Goose);
#endif
}

int main(int argc, char *argv[])
{
    Bird *bird = new Bird;
    Duck *duck = new Duck;
    Goose *goose = new Goose;

    std::cout << (*bird) << std::endl;
    std::cout << "IsADuck: " << BOOLTOSTR(IsADuck(bird)) << std::endl;
    std::cout << "IsAGoose: " << BOOLTOSTR(IsAGoose(bird)) << std::endl;

    std::cout << (*duck) << std::endl;
    std::cout << "IsADuck: " << BOOLTOSTR(IsADuck(duck)) << std::endl;
    std::cout << "IsAGoose: " << BOOLTOSTR(IsAGoose(duck)) << std::endl;

    std::cout << (*goose) << std::endl;
    std::cout << "IsADuck: " << BOOLTOSTR(IsADuck(goose)) << std::endl;
    std::cout << "IsAGoose: " << BOOLTOSTR(IsAGoose(goose)) << std::endl;

    delete bird;
    delete duck;
    delete goose;

    return 0;
}
