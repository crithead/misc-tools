/// Builder Pattern in C++

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

class PersonBuilder;

/// Person data object.
class Person {
public:
    /// Get a builder object.
    static PersonBuilder& Builder();

    /// Constructor
    Person(std::string& na, int nu);

    /// Destructor
    ~Person();

    /// Get the Person's name.
    std::string Name() const;

    /// Get the Person's number.
    int Number() const;

    /// Get a string representaiton of a Person.
    std::string AsString() const;

private:
    /// Name
    std::string name;
    /// Number
    int number;
    /// Store the string representation.
    mutable std::string str;
};

/// The builder class knows how to assemble a Person object.
class PersonBuilder {
public:
    /// Construst a PersonBuilder.
    PersonBuilder();
    ~PersonBuilder();

    /// Assign the Person's name.
    PersonBuilder& Name(const char *n);

    /// Assign the Person's number.
    PersonBuilder& Number(int n);

    /// Build the Person object.
    Person& Build();

private:
    std::string name;
    int number;
};

// PersonBuilder implementation

PersonBuilder::PersonBuilder() : name(""), number(0)
{
}

PersonBuilder::~PersonBuilder()
{
}

PersonBuilder& PersonBuilder::Name(const char *n)
{
    name = std::string(n);
    return *this;
}

PersonBuilder& PersonBuilder::Number(int n)
{
    number = n;
    return *this;
}

Person& PersonBuilder::Build() {
    return *(new Person(name, number));
}

// Person implementation

Person::Person(std::string& na, int nu) : name(na), number(nu), str("")
{
}

Person::~Person()
{
}

PersonBuilder& Person::Builder()
{
    return *(new PersonBuilder());
}

std::string Person::Name() const
{
    return name;
}

int Person::Number() const
{
    return number;
}

std::string Person::AsString() const
{
    if (str.empty()) {
        std::stringstream ss;
        ss << "Person { name = '" << name << "', number = " << number << " }";
        str = ss.str();
    }
    return str;
}


/// Print the Person.
/// @param argc Argument count
/// @param argv Argument vector
/// @retval 0 Always
int main(int argc, char **argv)
{
    const char *n1 = (argc >= 2) ? argv[1] : "<name>";
    int n2 = (argc >= 3) ? atoi(argv[2]) : 0;

    Person& person = Person::Builder().Name(n1).Number(n2).Build();
    std::cout << person.AsString() << std::endl;

    return 0;
}

