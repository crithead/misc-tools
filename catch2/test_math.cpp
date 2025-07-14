/// Math Tests

#include <catch2/catch.hpp>

#include "math.hpp"

TEST_CASE("Plus", "[MathLib]")
{
   CHECK(7 == Plus(2, 5));
   CHECK(0 == Plus(0, 0));
   CHECK(-2 == Plus(-1, -1));
   REQUIRE(0 == Plus(-9, 9));
}

TEST_CASE("Minus", "[MathLib]")
{
   CHECK(-3 == Minus(2, 5));
   CHECK(0 == Minus(0, 0));
   CHECK(0 == Minus(-1, -1));
   REQUIRE(-18 == Minus(-9, 9));
}

TEST_CASE("Times", "[MathLib]")
{
   CHECK(10 == Times(2, 5));
   CHECK(0 == Times(0, 5));
   CHECK(1 == Times(-1, -1));
   REQUIRE(-81 == Times(-9, 9));
}

TEST_CASE("DividedBy", "[MathLib]")
{
   CHECK(2 == DividedBy(10, 5));
   CHECK(0 == DividedBy(0, 5));
   CHECK(1 == DividedBy(-1, -1));
   REQUIRE(-3 == DividedBy(-9, 3));

   CHECK_THROWS(DividedBy(10, 0));
   REQUIRE_THROWS(DividedBy(0, 0));
}
