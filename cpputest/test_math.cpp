#include <stdexcept>
#include "CppUTest/TestHarness.h"
#include "math.hpp"

TEST_GROUP(MathLib)
{
};

TEST(MathLib, Plus)
{
   CHECK_EQUAL(7, Plus(2, 5));
   CHECK_EQUAL(0, Plus(0, 0));
   CHECK_EQUAL(-2, Plus(-1, -1));
   CHECK_EQUAL(0, Plus(-9, 9));
}

TEST(MathLib, Minus)
{
   CHECK_EQUAL(-3, Minus(2, 5));
   CHECK_EQUAL(0, Minus(0, 0));
   CHECK_EQUAL(0, Minus(-1, -1));
   CHECK_EQUAL(-18, Minus(-9, 9));
}

TEST(MathLib, Times)
{
   CHECK_EQUAL(10, Times(2, 5));
   CHECK_EQUAL(0, Times(0, 5));
   CHECK_EQUAL(1, Times(-1, -1));
   CHECK_EQUAL(-81, Times(-9, 9));
}

TEST(MathLib, DividedBy)
{
   CHECK_EQUAL(2, DividedBy(10, 5));
   CHECK_EQUAL(0, DividedBy(0, 5));
   CHECK_EQUAL(1, DividedBy(-1, -1));
   CHECK_EQUAL(-3, DividedBy(-9, 3));

   CHECK_THROWS(std::invalid_argument, DividedBy(10, 0));
   CHECK_THROWS( std::invalid_argument, DividedBy(0, 0));
}
