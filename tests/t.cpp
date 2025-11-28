#include <doctest/doctest.h>

int factorial(int number) { return number <= 1 ? number : factorial(number - 1) * number; }

TEST_CASE("testing the factorial function") {
    CHECK(factorial(1) == 1);
}

TEST_CASE("testing the factorial function 2") {
    CHECK(factorial(2) == 2);
}
