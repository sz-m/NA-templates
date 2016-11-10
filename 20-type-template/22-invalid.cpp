#include <catch.hpp>

#include "implementation.h"

TEST_CASE("invalid case", "[container_wrapper]")
{
    container_wrapper<int> c1;
    (void)c1; // silence unused-variable
    REQUIRE(c1.size() == 0);

    container_wrapper<int> c2 = 1;
    (void)c2; // silence unused-variable
    REQUIRE(c2.size() == 1);
}

