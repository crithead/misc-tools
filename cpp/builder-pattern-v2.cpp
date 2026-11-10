/// Builder Pattern in C++
// This version of builder pattern is the result of running v1 through
// clang-tidy with modernize-* (mostly the trailing return type).

#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

class PersonBuilder;

/// Person data object.
class Person {
public:
    /// Get a builder object.
    static auto Builder() -> PersonBuilder&;

    /// Constructor
    Person(std::string& na, int nu);

    /// Destructor
    ~Person();

    /// Get the Person's name.
    auto Name() const -> std::string;

    /// Get the Person's number.
    auto Number() const -> int;

    /// Get a string representaiton of a Person.
    auto AsString() const -> std::string;

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
    auto Name(const char *n) -> PersonBuilder&;

    /// Assign the Person's number.
    auto Number(int n) -> PersonBuilder&;

    /// Build the Person object.
    auto Build() -> Person&;

private:
    std::string name;
    int number{0};
};

// Person implementation

Person::Person(std::string& na, int nu) : name(na), number(nu), str("")
{
}

Person::~Person() = default;

auto Person::Builder() -> PersonBuilder&
{
    return *(new PersonBuilder());
}

auto Person::Name() const -> std::string
{
    return name;
}

auto Person::Number() const -> int
{
    return number;
}

auto Person::AsString() const -> std::string
{
    if (str.empty()) {
        std::stringstream ss;
        ss << "Person { name = '" << name << "', number = " << number << " }";
        str = ss.str();
    }
    return str;
}

// PersonBuilder implementation

PersonBuilder::PersonBuilder() : name("")
{
}

auto PersonBuilder::Name(const char *n) -> PersonBuilder&
{
    name = n;
    return *this;
}

auto PersonBuilder::Number(int n) -> PersonBuilder&
{
    number = n;
    return *this;
}

auto PersonBuilder::Build() -> Person& {
    return *(new Person(name, number));
}

/// Print the Person.
/// @param argc Argument count
/// @param argv Argument vector
/// @retval 0 Always
auto main(int argc, char **argv) -> int
{
    const char *n1 = (argc >= 2) ? argv[1] : "<name>";
    int n2 = (argc >= 3) ? atoi(argv[2]) : 0;

    Person& person = Person::Builder().Name(n1).Number(n2).Build();
    std::cout << person.AsString() << '\n';

    return 0;
}

