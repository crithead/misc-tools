// LookupTable example program

#include <iostream>

#include "table.hpp"

// This is the enumeration that needs to be translated into strings so 
// intelligible messages can be printed from these values (for example).
enum number_t {
    ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN
};

// This is the table defintion.  It is very clear what this table constains.
// It is easy to read and easy to change.  There is no runtime cost for 
// building it.
static lookupTableItem<number_t, const char *> numberTable[] = {
    { ONE,      "ONE" },
    { TWO,      "TWO" },
    { THREE,    "THREE" },
    { FOUR,     "FOUR" },
    { FIVE,     "FIVE" },
    { SIX,      "SIX" },
    { SEVEN,    "SEVEN" },
    { EIGHT,    "EIGHT" },
    { NINE,     "NINE" },
    { TEN,      "TEN" }
};

// This is the class that contains the table and performs lookups when a
// translation from Index to Value or Value to Index is needed.
static LookupTable<number_t, const char *> numbers(numberTable);

int main(void)
{
    std::cout << "Enum Value: " << (int)THREE << "\tAs string: "
            << numbers.GetValueFromIndex(THREE) << std::endl;

    std::cout << "Enum Value: " << (int)FIVE << "\tAs string: "
            << numbers.GetValueFromIndex(FIVE) << std::endl;

    std::cout << "String: " << "SIX" << "\tEnum value: "
            << numbers.GetIndexFromValue("SEVEN") << std::endl;

    std::cout << "String: " << "EIGHT" << "\tEnum value: "
            << (int)numbers.GetIndexFromValue("EIGHT") << std::endl;

    return 0;
}

